/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generate_primitive.h
 *
 * Code generation for function 'generate_primitive'
 *
 */

#ifndef GENERATE_PRIMITIVE_H
#define GENERATE_PRIMITIVE_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void FreeFlow(double v0, double a0, double xf, double vr,
                     double coeff[6], double *v, double *T);

extern void PassPrimitive(double v0, double a0, double sf, double vfmin,
                          double vfmax, double Tmin, double Tmax,
                          double coeffsT2[6], double *v2, double *T2,
                          double coeffsT1[6], double *v1, double *T1);

extern void PassPrimitive_j0(double v0, double a0, double sf, double vfmin,
                             double vfmax, double coefsj0[6], double *vfj0,
                             double *tfj0);

extern void StopPrimitive(double v0, double a0, double sf, double coefs[6],
                          double *maxsf, double *tf);

extern void StopPrimitive_j0(double v0, double a0, double coefsj0[6],
                             double *sfj0, double *tfj0);

extern double a_opt(double t, double v0, double a0, double sf, double vf,
                    double af, double T);

extern void generate_primitive_initialize(void);

extern void generate_primitive_terminate(void);

extern double j_opt(double t, double v0, double a0, double sf, double vf,
                    double af, double T);

extern double s_opt(double t, double v0, double a0, double sf, double vf,
                    double af, double T);

extern double v_opt(double t, double v0, double a0, double sf, double vf,
                    double af, double T);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (generate_primitive.h) */
