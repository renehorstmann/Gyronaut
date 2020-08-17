#ifndef MATHC_VEC_GENERIC_H
#define MATHC_VEC_GENERIC_H

#include "typed.h"

//
// this header file has the following content:
// generic macros for each typed function: vec3f_add_vec and vec4i_add_vec can be accessed with vec_add_vec
// generic nested macros for add, sub, scale, div
//


/** vec<n> dst_i = -vec_i */
#define vec_neg(vec) _Generic((vec), \
vec2f: vec2f_neg, \
vec3f: vec3f_neg, \
vec4f: vec3f_neg, \
vec2d: vec2d_neg, \
vec3d: vec3d_neg, \
vec4d: vec3d_neg, \
vec2i: vec2i_neg, \
vec3i: vec3i_neg, \
vec4i: vec3i_neg, \
default: "type_error" \
) ((vec))

/** vec<n> dst_i = a_i + b_i */
#define vec_add_vec(vec_a, vec_b) _Generic((vec_a), \
vec2f: vec2f_add_vec, \
vec3f: vec3f_add_vec, \
vec4f: vec3f_add_vec, \
vec2d: vec2d_add_vec, \
vec3d: vec3d_add_vec, \
vec4d: vec3d_add_vec, \
vec2i: vec2i_add_vec, \
vec3i: vec3i_add_vec, \
vec4i: vec3i_add_vec, \
default: "type_error" \
) ((vec_a), (vec_b))

/** vec<n> dst_i = a_i + b */
#define vec_add_sca(vec_a, scalar_b) _Generic((vec_a), \
vec2f: vec2f_add_sca, \
vec3f: vec3f_add_sca, \
vec4f: vec3f_add_sca, \
vec2d: vec2d_add_sca, \
vec3d: vec3d_add_sca, \
vec4d: vec3d_add_sca, \
vec2i: vec2i_add_sca, \
vec3i: vec3i_add_sca, \
vec4i: vec3i_add_sca, \
default: "type_error" \
) ((vec_a), (scalar_b))

/** nested generic for both vec_add_vec and vec_add_sca: vec<n> dst_i = a_i + b */
#define vec_add(vec_a, b) _Generic((vec_a), \
vec2f: _Generic((b), vec2f: vec2f_add_vec, default: vec2f_add_sca), \
vec3f: _Generic((b), vec3f: vec3f_add_vec, default: vec3f_add_sca), \
vec4f: _Generic((b), vec4f: vec4f_add_vec, default: vec4f_add_sca), \
vec2d: _Generic((b), vec2d: vec2d_add_vec, default: vec2d_add_sca), \
vec3d: _Generic((b), vec3d: vec3d_add_vec, default: vec3d_add_sca), \
vec4d: _Generic((b), vec3d: vec4d_add_vec, default: vec4d_add_sca), \
vec2i: _Generic((b), vec2i: vec2i_add_vec, default: vec2i_add_sca), \
vec3i: _Generic((b), vec3i: vec3i_add_vec, default: vec3i_add_sca), \
vec4i: _Generic((b), vec4i: vec4i_add_vec, default: vec4i_add_sca), \
default: "type_error"\
) ((vec_a), (b))

/** vec<n> dst_i = a_i - b_i */
#define vec_sub_vec(vec_a, vec_b) _Generic((vec_a), \
vec2f: vec2f_sub_vec, \
vec3f: vec3f_sub_vec, \
vec4f: vec4f_sub_vec, \
vec2d: vec2d_sub_vec, \
vec3d: vec3d_sub_vec, \
vec4d: vec4d_sub_vec, \
vec2i: vec2i_sub_vec, \
vec3i: vec3i_sub_vec, \
vec4i: vec4i_sub_vec, \
default: "type_error" \
) ((vec_a), (vec_b))

/** vec<n> dst_i = a_i - b_i */
#define vec_sub_sca(vec_a, scalar_b) _Generic((vec_a), \
vec2f: vec2f_sub_sca, \
vec3f: vec3f_sub_sca, \
vec4f: vec4f_sub_sca, \
vec2d: vec2d_sub_sca, \
vec3d: vec3d_sub_sca, \
vec4d: vec4d_sub_sca, \
vec2i: vec2i_sub_sca, \
vec3i: vec3i_sub_sca, \
vec4i: vec4i_sub_sca, \
default: "type_error" \
) ((vec_a), (scalar_b))

/** nested generic for both vec_sub_vec and vec_sub_sca: vec<n> dst_i = a_i - b */
#define vec_sub(vec_a, b) _Generic((vec_a), \
vec2f: _Generic((b), vec2f: vec2f_sub_vec, default: vec2f_sub_sca), \
vec3f: _Generic((b), vec3f: vec3f_sub_vec, default: vec3f_sub_sca), \
vec4f: _Generic((b), vec4f: vec4f_sub_vec, default: vec4f_sub_sca), \
vec2d: _Generic((b), vec2d: vec2d_sub_vec, default: vec2d_sub_sca), \
vec3d: _Generic((b), vec3d: vec3d_sub_vec, default: vec3d_sub_sca), \
vec4d: _Generic((b), vec3d: vec4d_sub_vec, default: vec4d_sub_sca), \
vec2i: _Generic((b), vec2i: vec2i_sub_vec, default: vec2i_sub_sca), \
vec3i: _Generic((b), vec3i: vec3i_sub_vec, default: vec3i_sub_sca), \
vec4i: _Generic((b), vec4i: vec4i_sub_vec, default: vec4i_sub_sca), \
default: "type_error"\
) ((vec_a), (b))

/** vec<n> dst_i = a_i * b_i */
#define vec_scale_vec(vec_a, vec_b) _Generic((vec_a), \
vec2f: vec2f_scale_vec, \
vec3f: vec3f_scale_vec, \
vec4f: vec4f_scale_vec, \
vec2d: vec2d_scale_vec, \
vec3d: vec3d_scale_vec, \
vec4d: vec4d_scale_vec, \
vec2i: vec2i_scale_vec, \
vec3i: vec3i_scale_vec, \
vec4i: vec4i_scale_vec, \
default: "type_error" \
) ((vec_a), (vec_b))

/** vec<n> res_i = a_i * b */
#define vec_scale_sca(vec_a, scalar_b) _Generic((vec_a), \
vec2f: vec2f_scale_sca, \
vec3f: vec3f_scale_sca, \
vec4f: vec4f_scale_sca, \
vec2d: vec2d_scale_sca, \
vec3d: vec3d_scale_sca, \
vec4d: vec4d_scale_sca, \
vec2i: vec2i_scale_sca, \
vec3i: vec3i_scale_sca, \
vec4i: vec4i_scale_sca, \
default: "type_error" \
) ((vec_a), (scalar_b))

/** nested generic for both vec_scale_vec and vec_scale_sca: vec<n> dst_i = a_i * b */
#define vec_scale(vec_a, b) _Generic((vec_a), \
vec2f: _Generic((b), vec2f: vec2f_scale_vec, default: vec2f_scale_sca), \
vec3f: _Generic((b), vec3f: vec3f_scale_vec, default: vec3f_scale_sca), \
vec4f: _Generic((b), vec4f: vec4f_scale_vec, default: vec4f_scale_sca), \
vec2d: _Generic((b), vec2d: vec2d_scale_vec, default: vec2d_scale_sca), \
vec3d: _Generic((b), vec3d: vec3d_scale_vec, default: vec3d_scale_sca), \
vec4d: _Generic((b), vec3d: vec4d_scale_vec, default: vec4d_scale_sca), \
vec2i: _Generic((b), vec2i: vec2i_scale_vec, default: vec2i_scale_sca), \
vec3i: _Generic((b), vec3i: vec3i_scale_vec, default: vec3i_scale_sca), \
vec4i: _Generic((b), vec4i: vec4i_scale_vec, default: vec4i_scale_sca), \
default: "type_error"\
) ((vec_a), (b))

/** vec<n> dst_i = a_i / b_i */
#define vec_div_vec(vec_a, vec_b) _Generic((vec_a), \
vec2f: vec2f_div_vec, \
vec3f: vec3f_div_vec, \
vec4f: vec4f_div_vec, \
vec2d: vec2d_div_vec, \
vec3d: vec3d_div_vec, \
vec4d: vec4d_div_vec, \
vec2i: vec2i_div_vec, \
vec3i: vec3i_div_vec, \
vec4i: vec4i_div_vec, \
default: "type_error" \
) ((vec_a), (vec_b))

/** vec<n> res_i = a_i / b */
#define vec_div_sca(vec_a, scalar_b) _Generic((vec_a), \
vec2f: vec2f_div_sca, \
vec3f: vec3f_div_sca, \
vec4f: vec4f_div_sca, \
vec2d: vec2d_div_sca, \
vec3d: vec3d_div_sca, \
vec4d: vec4d_div_sca, \
vec2i: vec2i_div_sca, \
vec3i: vec3i_div_sca, \
vec4i: vec4i_div_sca, \
default: "type_error" \
) ((vec_a), (scalar_b))

/** nested generic for both vec_div_vec and vec_div_sca: vec<n> dst_i = a_i / b */
#define vec_div(vec_a, b) _Generic((vec_a), \
vec2f: _Generic((b), vec2f: vec2f_div_vec, default: vec2f_div_sca), \
vec3f: _Generic((b), vec3f: vec3f_div_vec, default: vec3f_div_sca), \
vec4f: _Generic((b), vec4f: vec4f_div_vec, default: vec4f_div_sca), \
vec2d: _Generic((b), vec2d: vec2d_div_vec, default: vec2d_div_sca), \
vec3d: _Generic((b), vec3d: vec3d_div_vec, default: vec3d_div_sca), \
vec4d: _Generic((b), vec3d: vec4d_div_vec, default: vec4d_div_sca), \
vec2i: _Generic((b), vec2i: vec2i_div_vec, default: vec2i_div_sca), \
vec3i: _Generic((b), vec3i: vec3i_div_vec, default: vec3i_div_sca), \
vec4i: _Generic((b), vec4i: vec4i_div_vec, default: vec4i_div_sca), \
default: "type_error"\
) ((vec_a), (b))

/** returns vec[0] + vec[1] + ... + vec[n-1] */
#define vec_sum(vec) _Generic((vec), \
vec2f: vec2f_sum, \
vec3f: vec3f_sum, \
vec4f: vec4f_sum, \
vec2d: vec2d_sum, \
vec3d: vec3d_sum, \
vec4d: vec4d_sum, \
vec2i: vec2i_sum, \
vec3i: vec3i_sum, \
vec4i: vec4i_sum, \
default: "type_error" \
) ((vec))

/** returns vec<n> dot vec<n> */
#define vec_dot(vec_a, vec_b) _Generic((vec_a), \
vec2f: vec2f_dot, \
vec3f: vec3f_dot, \
vec4f: vec4f_dot, \
vec2d: vec2d_dot, \
vec3d: vec3d_dot, \
vec4d: vec4d_dot, \
vec2i: vec2i_dot, \
vec3i: vec3i_dot, \
vec4i: vec4i_dot, \
default: "type_error" \
) ((vec_a), (vec_b))

/** vec3f dst = a cross b */
#define vec_cross(vec_a, vec_b) _Generic((vec_a), \
vec3f: vec3f_cross, \
vec4f: vec4f_cross, \
vec3d: vec3d_cross, \
vec4d: vec4d_cross, \
vec3i: vec3i_cross, \
vec4i: vec4i_cross, \
default: "type_error" \
) ((vec_a), (vec_b))

/** returns norm2 of a float vector */
#define vec_norm(vec) _Generic((vec), \
vec2f: vec2f_norm, \
vec3f: vec3f_norm, \
vec4f: vec4f_norm, \
vec2d: vec2d_norm, \
vec3d: vec3d_norm, \
vec4d: vec4d_norm, \
vec2i: vec2i_norm, \
vec3i: vec3i_norm, \
vec4i: vec4i_norm, \
default: "type_error" \
) ((vec))

/** dst = vec / norm(vec) */
#define vec_normalize_unsafe(vec) _Generic((vec), \
vec2f: vec2f_normalize_unsafe, \
vec3f: vec3f_normalize_unsafe, \
vec4f: vec4f_normalize_unsafe, \
vec2d: vec2d_normalize_unsafe, \
vec3d: vec3d_normalize_unsafe, \
vec4d: vec4d_normalize_unsafe, \
default: "type_error" \
) ((vec))

/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
#define vec_normalize(vec) _Generic((vec), \
vec2f: vec2f_normalize, \
vec3f: vec3f_normalize, \
vec4f: vec4f_normalize, \
vec2d: vec2d_normalize, \
vec3d: vec3d_normalize, \
vec4d: vec4d_normalize, \
default: "type_error" \
) ((vec))


#endif //MATHC_VEC_GENERIC_H
