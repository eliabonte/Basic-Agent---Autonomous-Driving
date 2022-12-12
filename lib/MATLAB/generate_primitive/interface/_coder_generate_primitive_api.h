/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generate_primitive_api.h
 *
 * Code generation for function 'a_opt'
 *
 */

#ifndef _CODER_GENERATE_PRIMITIVE_API_H
#define _CODER_GENERATE_PRIMITIVE_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void FreeFlow(real_T v0, real_T a0, real_T xf, real_T vr, real_T coeff[6],
              real_T *v, real_T *T);

void FreeFlow_api(const mxArray *const prhs[4], int32_T nlhs,
                  const mxArray *plhs[3]);

void PassPrimitive(real_T v0, real_T a0, real_T sf, real_T vfmin, real_T vfmax,
                   real_T Tmin, real_T Tmax, real_T coeffsT2[6], real_T *v2,
                   real_T *T2, real_T coeffsT1[6], real_T *v1, real_T *T1);

void PassPrimitive_api(const mxArray *const prhs[7], int32_T nlhs,
                       const mxArray *plhs[6]);

void PassPrimitive_j0(real_T v0, real_T a0, real_T sf, real_T vfmin,
                      real_T vfmax, real_T coefsj0[6], real_T *vfj0,
                      real_T *tfj0);

void PassPrimitive_j0_api(const mxArray *const prhs[5], int32_T nlhs,
                          const mxArray *plhs[3]);

void StopPrimitive(real_T v0, real_T a0, real_T sf, real_T coefs[6],
                   real_T *maxsf, real_T *tf);

void StopPrimitive_api(const mxArray *const prhs[3], int32_T nlhs,
                       const mxArray *plhs[3]);

void StopPrimitive_j0(real_T v0, real_T a0, real_T coefsj0[6], real_T *sfj0,
                      real_T *tfj0);

void StopPrimitive_j0_api(const mxArray *const prhs[2], int32_T nlhs,
                          const mxArray *plhs[3]);

real_T a_opt(real_T t, real_T v0, real_T a0, real_T sf, real_T vf, real_T af,
             real_T T);

void a_opt_api(const mxArray *const prhs[7], const mxArray **plhs);

void generate_primitive_atexit(void);

void generate_primitive_initialize(void);

void generate_primitive_terminate(void);

void generate_primitive_xil_shutdown(void);

void generate_primitive_xil_terminate(void);

real_T j_opt(real_T t, real_T v0, real_T a0, real_T sf, real_T vf, real_T af,
             real_T T);

void j_opt_api(const mxArray *const prhs[7], const mxArray **plhs);

real_T s_opt(real_T t, real_T v0, real_T a0, real_T sf, real_T vf, real_T af,
             real_T T);

void s_opt_api(const mxArray *const prhs[7], const mxArray **plhs);

real_T v_opt(real_T t, real_T v0, real_T a0, real_T sf, real_T vf, real_T af,
             real_T T);

void v_opt_api(const mxArray *const prhs[7], const mxArray **plhs);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_generate_primitive_api.h) */
