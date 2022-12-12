/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "generate_primitive.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static double argInit_real_T(void);

static void main_FreeFlow(void);

static void main_PassPrimitive(void);

static void main_PassPrimitive_j0(void);

static void main_StopPrimitive(void);

static void main_StopPrimitive_j0(void);

static void main_a_opt(void);

static void main_j_opt(void);

static void main_s_opt(void);

static void main_v_opt(void);

/* Function Definitions */
static double argInit_real_T(void)
{
  return 0.0;
}

static void main_FreeFlow(void)
{
  double coeff[6];
  double T;
  double v;
  double v0_tmp;
  /* Initialize function 'FreeFlow' input arguments. */
  v0_tmp = argInit_real_T();
  /* Call the entry-point 'FreeFlow'. */
  FreeFlow(v0_tmp, v0_tmp, v0_tmp, v0_tmp, coeff, &v, &T);
}

static void main_PassPrimitive(void)
{
  double coeffsT1[6];
  double coeffsT2[6];
  double T1;
  double T2;
  double v0_tmp;
  double v1;
  double v2;
  /* Initialize function 'PassPrimitive' input arguments. */
  v0_tmp = argInit_real_T();
  /* Call the entry-point 'PassPrimitive'. */
  PassPrimitive(v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp,
                coeffsT2, &v2, &T2, coeffsT1, &v1, &T1);
}

static void main_PassPrimitive_j0(void)
{
  double coefsj0[6];
  double tfj0;
  double v0_tmp;
  double vfj0;
  /* Initialize function 'PassPrimitive_j0' input arguments. */
  v0_tmp = argInit_real_T();
  /* Call the entry-point 'PassPrimitive_j0'. */
  PassPrimitive_j0(v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp, coefsj0, &vfj0,
                   &tfj0);
}

static void main_StopPrimitive(void)
{
  double coefs[6];
  double maxsf;
  double tf;
  double v0_tmp;
  /* Initialize function 'StopPrimitive' input arguments. */
  v0_tmp = argInit_real_T();
  /* Call the entry-point 'StopPrimitive'. */
  StopPrimitive(v0_tmp, v0_tmp, v0_tmp, coefs, &maxsf, &tf);
}

static void main_StopPrimitive_j0(void)
{
  double coefsj0[6];
  double sfj0;
  double tfj0;
  double v0_tmp;
  /* Initialize function 'StopPrimitive_j0' input arguments. */
  v0_tmp = argInit_real_T();
  /* Call the entry-point 'StopPrimitive_j0'. */
  StopPrimitive_j0(v0_tmp, v0_tmp, coefsj0, &sfj0, &tfj0);
}

static void main_a_opt(void)
{
  double t_tmp;
  /* Initialize function 'a_opt' input arguments. */
  t_tmp = argInit_real_T();
  /* Call the entry-point 'a_opt'. */
  t_tmp = a_opt(t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp);
}

static void main_j_opt(void)
{
  double t_tmp;
  /* Initialize function 'j_opt' input arguments. */
  t_tmp = argInit_real_T();
  /* Call the entry-point 'j_opt'. */
  t_tmp = j_opt(t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp);
}

static void main_s_opt(void)
{
  double t_tmp;
  /* Initialize function 's_opt' input arguments. */
  t_tmp = argInit_real_T();
  /* Call the entry-point 's_opt'. */
  t_tmp = s_opt(t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp);
}

static void main_v_opt(void)
{
  double t_tmp;
  /* Initialize function 'v_opt' input arguments. */
  t_tmp = argInit_real_T();
  /* Call the entry-point 'v_opt'. */
  t_tmp = v_opt(t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp, t_tmp);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_a_opt();
  main_FreeFlow();
  main_j_opt();
  main_PassPrimitive();
  main_PassPrimitive_j0();
  main_s_opt();
  main_StopPrimitive();
  main_StopPrimitive_j0();
  main_v_opt();
  /* Terminate the application.
You do not need to do this more than one time. */
  generate_primitive_terminate();
  return 0;
}

/* End of code generation (main.c) */
