/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generate_primitive_mex.h
 *
 * Code generation for function 'a_opt'
 *
 */

#ifndef _CODER_GENERATE_PRIMITIVE_MEX_H
#define _CODER_GENERATE_PRIMITIVE_MEX_H

/* Include files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_FreeFlow_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                                 const mxArray *prhs[4]);

void unsafe_PassPrimitive_j0_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                         int32_T nrhs, const mxArray *prhs[5]);

void unsafe_PassPrimitive_mexFunction(int32_T nlhs, mxArray *plhs[6],
                                      int32_T nrhs, const mxArray *prhs[7]);

void unsafe_StopPrimitive_j0_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                         int32_T nrhs, const mxArray *prhs[2]);

void unsafe_StopPrimitive_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                      int32_T nrhs, const mxArray *prhs[3]);

void unsafe_a_opt_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                              const mxArray *prhs[7]);

void unsafe_j_opt_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                              const mxArray *prhs[7]);

void unsafe_s_opt_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                              const mxArray *prhs[7]);

void unsafe_v_opt_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                              const mxArray *prhs[7]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_generate_primitive_mex.h) */
