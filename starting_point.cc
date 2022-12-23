//
// Created by Gastone Pietro Rosati Papini on 10/08/22.
//

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

extern "C" {
#include "log/screen_print_c.h"
}
#include "log/screen_print.h"
#include "lib/server_lib.h"
#include "log/logvars.h"

// --- MATLAB PRIMITIVES INCLUDE ---
#include "lib/MATLAB/generate_primitive/generate_primitive.h"

// --- MATLAB PRIMITIVES INCLUDE ---

#define DEFAULT_SERVER_IP    "127.0.0.1"
#define SERVER_PORT                30000  // Server port
#define DT 0.05

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

// Handler for CTRL-C
#include <csignal>
static uint32_t server_run = 1;
void intHandler(int signal) {
    server_run = 0;
}
bool check_array_null(double *a, int size){
    for(int i = 0; i < size; i++){
        if(a[i] != 0){
            return false;
        }
    }

    return true;
}

int main(int argc, const char * argv[]) {
    logger.enable(true);

    // Messages variables
    scenario_msg_t scenario_msg;
    manoeuvre_msg_t manoeuvre_msg;
    size_t scenario_msg_size = sizeof(scenario_msg.data_buffer);
    size_t manoeuvre_msg_size = sizeof(manoeuvre_msg.data_buffer);
    uint32_t message_id = 0;

#ifndef _MSC_VER
    // More portable way of supporting signals on UNIX
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);
#else
    signal(SIGINT, intHandler);
#endif

    server_agent_init(DEFAULT_SERVER_IP, SERVER_PORT);

    // Start server of the Agent
    printLine();
    printTable("Waiting for scenario message...", 0);
    printLine();


    while (server_run == 1) {

        // Clean the buffer
        memset(scenario_msg.data_buffer, '\0', scenario_msg_size);

        // Receive scenario message from the environment
        if (server_receive_from_client(&server_run, &message_id, &scenario_msg.data_struct) == 0) {
            // Init time
            static auto start = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::now()-start;
            double num_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(time).count()/1000.0;
            printLogTitle(message_id, "received message");

            // Data struct
            input_data_str *in = &scenario_msg.data_struct;
            manoeuvre_msg.data_struct.CycleNumber = in->CycleNumber;
            manoeuvre_msg.data_struct.Status = in->Status;



            // ADD AGENT CODE HERE
            double v0, a0, lookahead, v_max_possible, Ts, v_min_possible, xs, Tp, xf, x_stop;
            double T_green, T_red;


            double optimalVel;
            double *coeff_FreeFlow, optimalTime; //FreeFlow function
            double *coeff_T1, *coeff_T2, vmin_passing, optimalTime_T1, vmax_passing, optimalTime_T2; //Passing Primitive
            double *coeffStop, max_xStop, T_stop; //StopPrimitive
            double *coeffPass_j0, vf_j0, tf_Passj0; //PassPrimitive_j0
            double *coeffStop_j0, sfj0, tf_Stopj0; //StopPrimitive_j0

            auto *bestCoeff = (double*)malloc(6 * sizeof(double));
            coeff_FreeFlow = (double*)malloc(6 * sizeof(double));
            coeffStop = (double*)malloc(6 * sizeof(double));
            coeff_T1 = (double*)malloc(6 * sizeof(double));
            coeff_T2 = (double*)malloc(6 * sizeof(double));
            coeffPass_j0 = (double*)malloc(6 * sizeof(double));
            coeffStop_j0 = (double*)malloc(6 * sizeof(double));

            v0 = in->VLgtFild;
            a0 = in->ALgtFild;

            double l1 = v0*10;
            double l2 = v0*v0;

            lookahead = MAX(MAX(50,l1),MAX(50,l2));
            v_max_possible = MIN(in->RequestedCruisingSpeed, 20);
            printLogTitle(message_id, "INFO INITIAL STATE VARIABLES");
            printLogVar(message_id, "v0", v0);
            printLogVar(message_id, "a0", a0);
            printLogVar(message_id, "vmax possible", v_max_possible);
            Ts = 0.5; //time safety margin to pass the traffic light

            v_min_possible = 5; //lower velocity

            //using Ts and considering the higher velocity v_max_possible we obtain a safety space xs
            xs = v_max_possible * Ts; //safety space to pass

            //considering the lower velocity v_min_possible and xs we get a time;
            //we want to be at the traffic light within the safety margin of time
            Tp = xs / v_min_possible; //time in which we need to pass through xs with min speed


            if(in->NrTrfLights != 0){
                xf = in->TrfLightDist - xs;
                x_stop = in->TrfLightDist - xs/2;
            }

            printLogTitle(message_id, "INFO DISTANCES");
            printLogVar(message_id, "Traffic Light Distance", in->TrfLightDist);
            printLogVar(message_id, "xs", xs);
            printLogVar(message_id, "Xf", xf);

            if(in->NrTrfLights == 0 || xf >= lookahead){
                FreeFlow(v0, a0, xf, v_max_possible, coeff_FreeFlow, &optimalVel, &optimalTime);
                bestCoeff = coeff_FreeFlow;
            }
            else{
                switch (in->TrfLightCurrState) {
                    case 1:
                        T_green = 0;
                        T_red = in->TrfLightFirstTimeToChange;
                        break;
                    case 2:
                        T_green = in->TrfLightSecondTimeToChange;
                        T_red = in->TrfLightThirdTimeToChange;
                        break;
                    case 3:
                        T_green = in->TrfLightFirstTimeToChange;
                        T_red = in->TrfLightSecondTimeToChange;
                        break;
                }
                printLogTitle(message_id, "INFO TRAFFIC LIGHT");
                printLogVar(message_id, "Current State Traffic Light", in->TrfLightCurrState);
                printLogVar(message_id, "T_green", T_green);
                printLogVar(message_id, "T_red", T_red);
                if(in->TrfLightCurrState == 1 && in->TrfLightDist <= xs){
                    v_max_possible = 15;
                    FreeFlow(v0, a0, xf, v_max_possible, coeff_FreeFlow, &optimalVel, &optimalTime);
                    bestCoeff = coeff_FreeFlow;
                    printLogTitle(message_id, "Best Coefficient - Free Flow");
                }
                else{
                    PassPrimitive(v0, a0, xf, v_min_possible, v_max_possible, T_green, T_red - Ts - Tp,
                                  coeff_T2, &optimalTime_T2, &vmax_passing,
                                  coeff_T1, &optimalTime_T1, &vmin_passing);

                    if(check_array_null(coeff_T1, 6) && check_array_null(coeff_T2, 6)){
                        StopPrimitive(v0, a0, x_stop,
                                      coeffStop, &max_xStop, &T_stop);
                        if(coeffStop[3] < -1){
                            StopPrimitive_j0(v0, a0,
                                             coeffStop_j0, &sfj0, &tf_Stopj0);
                            bestCoeff = coeffStop_j0;
                            printLogTitle(message_id, "Best Coefficient - Stop Primitive j0");
                        }
                        else{
                            bestCoeff = coeffStop;
                            printLogTitle(message_id, "Best Coefficient - Stop Primitive");
                        }
                    }
                    else{
                        if((coeff_T1[3]*coeff_T2[3]) < 0) {
                            PassPrimitive_j0(v0, a0, xf, v_min_possible, v_max_possible, coeffPass_j0, &vf_j0, &tf_Passj0);
                            bestCoeff = coeffPass_j0;
                            printLogTitle(message_id, "Best Coefficient - Pass Primitive j0");
                        }
                        else{
                            if(abs(coeff_T1[3]) < abs(coeff_T2[3])){
                                bestCoeff = coeff_T1;
                                printLogTitle(message_id, "Best Coefficient - Pass Primitive T1");
                            }
                            else{
                                bestCoeff = coeff_T2;
                                printLogTitle(message_id, "Best Coefficient - Pass Primitive T2");
                            }
                        }
                    }
                }
            }

            printLogVar(message_id, "v0", bestCoeff[1]);
            printLogVar(message_id, "a0", bestCoeff[2]);
            printLogVar(message_id, "bestCoeff[3]", bestCoeff[3]);
            printLogVar(message_id, "bestCoeff[4]", bestCoeff[4]);
            printLogVar(message_id, "bestCoeff[5]", bestCoeff[5]);


            // ADD LOW LEVEL CONTROL CODE HERE
            static double old_req_acc = a0;
            double req_acc;


            double j_T_0 = bestCoeff[3]; //jEval(t=0,bestCoeff);
            double j_T_dt = bestCoeff[3] + (bestCoeff[4] * DT) + (0.5*bestCoeff[5]*DT*DT); //jEval(t=dt,bestCoeff);
            double j_int = DT*0.5*(j_T_0 + j_T_dt);
            req_acc = old_req_acc + j_int;


            //req_acc saturate
            if(req_acc > 1.5){
                req_acc = 1.5;
            }
            else if(req_acc < -1.5){
                req_acc = -1.5;
            }

            //save the old acceleration
            old_req_acc = req_acc;

            //PID CONTROL
            double P_gain = 0.02;
            double I_gain = 1;
            static double e_integral = 0;
            double error = req_acc - a0;
            e_integral = e_integral + error*DT;
            double req_pedal = error*P_gain + e_integral * I_gain;

            manoeuvre_msg.data_struct.RequestedAcc = req_pedal;

            if(v0 < 0.1 && old_req_acc < 0 && j_int > 0){
                old_req_acc = 0;
                e_integral = 0;
            }


            //Save values in external file
            logger.log_var("Example", "cycle", in->CycleNumber);
            logger.log_var("Example", "time", num_seconds);
            logger.log_var("Example", "v0", v0);
            logger.log_var("Example", "a0", in->ALgtFild);
            logger.log_var("Example", "req_acc", req_acc);
            logger.log_var("Example", "coeff[3]", bestCoeff[3]);
            logger.log_var("Example", "coeff[4]", bestCoeff[4]);
            logger.log_var("Example", "coeff[5]", bestCoeff[5]);

            // Write log
            logger.write_line("Example");

            // Screen print
            printLogVar(message_id, "Status", in->Status);
            printLogVar(message_id, "CycleNumber", in->CycleNumber);

            // Send manoeuvre message to the environment
            if (server_send_to_client(server_run, message_id, &manoeuvre_msg.data_struct) == -1) {
                perror("error send_message()");
                exit(EXIT_FAILURE);
            } else {
                printLogTitle(message_id, "sent message");
            }
        }
    }

    // Close the server of the agent
    server_agent_close();
    return 0;
}