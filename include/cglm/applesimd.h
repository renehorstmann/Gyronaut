/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_applesimd_h
#define cglm_applesimd_h
#if defined(__APPLE__)                                                        \
    && defined(SIMD_COMPILER_HAS_REQUIRED_FEATURES)                           \
    && defined(SIMD_BASE)                                                     \
    && defined(SIMD_TYPES)                                                    \
    && defined(SIMD_VECTOR_TYPES)

#include "common.h"

/*!
* @brief converts mat4 to Apple's simd type simd_float4x4
* @return simd_float4x4
*/
CGLM_INLINE
simd_float4x4
glm_mat4_applesimd(mat4 pose) {
  simd_float4x4 t;
  
  t.columns[0][0] = pose[0][0];
  t.columns[0][1] = pose[0][1];
  t.columns[0][2] = pose[0][2];
  t.columns[0][3] = pose[0][3];

  t.columns[1][0] = pose[1][0];
  t.columns[1][1] = pose[1][1];
  t.columns[1][2] = pose[1][2];
  t.columns[1][3] = pose[1][3];

  t.columns[2][0] = pose[2][0];
  t.columns[2][1] = pose[2][1];
  t.columns[2][2] = pose[2][2];
  t.columns[2][3] = pose[2][3];

  t.columns[3][0] = pose[3][0];
  t.columns[3][1] = pose[3][1];
  t.columns[3][2] = pose[3][2];
  t.columns[3][3] = pose[3][3];

  return t;
}

/*!
* @brief converts mat3 to Apple's simd type simd_float3x3
* @return simd_float3x3
*/
CGLM_INLINE
simd_float3x3
glm_mat3_applesimd(mat3 pose) {
  simd_float3x3 t;
  
  t.columns[0][0] = pose[0][0];
  t.columns[0][1] = pose[0][1];
  t.columns[0][2] = pose[0][2];

  t.columns[1][0] = pose[1][0];
  t.columns[1][1] = pose[1][1];
  t.columns[1][2] = pose[1][2];

  t.columns[2][0] = pose[2][0];
  t.columns[2][1] = pose[2][1];
  t.columns[2][2] = pose[2][2];

  return t;
}

/*!
* @brief converts vec4 to Apple's simd type simd_float4
* @return simd_float4
*/
CGLM_INLINE
simd_float4
glm_vec4_applesimd(vec4 v) {
  return (simd_float4){v[0], v[1], v[2], v[3]};
}

/*!
* @brief converts vec3 to Apple's simd type simd_float3
* @return v
*/
CGLM_INLINE
simd_float3
glm_vec3_applesimd(vec3 v) {
  return (simd_float3){v[0], v[1], v[2]};
}

#endif
#endif /* cglm_applesimd_h */
