#ifndef MATHC_VEC_DVEC2_V_H
#define MATHC_VEC_DVEC2_V_H

#include "dvec2.h"


/** dst = -dvec */
static dvec2 dvec2_neg_v(const double *dvec) {
    dvec2 res;
    dvecN_neg(res.v, dvec, 2);
    return res;
}

/** dst = a + b */
static dvec2 dvec2_add_dvec_v(const double *dvec_a, const double *dvec_b) {
    dvec2 res;
    dvecN_add_dvec(res.v, dvec_a, dvec_b, 2);
    return res;
}

/** dst = a + b */
static dvec2 dvec2_add_sca_v(const double *dvec_a, double scalar_b) {
    dvec2 res;
    dvecN_add_sca(res.v, dvec_a, scalar_b, 2);
    return res;
}

/** dst = a - b */
static dvec2 dvec2_sub_dvec_v(const double *dvec_a, const double *dvec_b) {
    dvec2 res;
    dvecN_sub_dvec(res.v, dvec_a, dvec_b, 2);
    return res;
}

/** dst = a - b */
static dvec2 dvec2_sub_sca_v(const double *dvec_a, double scalar_b) {
    dvec2 res;
    dvecN_sub_sca(res.v, dvec_a, scalar_b, 2);
    return res;
}

/** dst = a * b */
static dvec2 dvec2_scale_dvec_v(const double *dvec_a, const double *dvec_b) {
    dvec2 res;
    dvecN_scale_dvec(res.v, dvec_a, dvec_b, 2);
    return res;
}

/** dst = a * b */
static dvec2 dvec2_scale_sca_v(const double *dvec_a, double scalar_b) {
    dvec2 res;
    dvecN_scale_sca(res.v, dvec_a, scalar_b, 2);
    return res;
}

/** dst = a / b */
static dvec2 dvec2_div_dvec_v(const double *dvec_a, const double *dvec_b) {
    dvec2 res;
    dvecN_div_dvec(res.v, dvec_a, dvec_b, 2);
    return res;
}

/** dst = a / b */
static dvec2 dvec2_div_sca_v(const double *dvec_a, double scalar_b) {
    dvec2 res;
    dvecN_div_sca(res.v, dvec_a, scalar_b, 2);
    return res;
}

/** returns dvec[0] + dvec[1] + ... + dvec[n-1] */
static double dvec2_sum_v(const double *dvec) {
    return dvecN_sum(dvec, 2);
}

/** returns a dot b */
static double dvec2_dot_v(const double *dvec_a, const double *dvec_b) {
    return dvecN_dot(dvec_a, dvec_b, 2);
}

/** returns ||dvec||_2 */
static double dvec2_norm_v(const double *dvec) {
    return dvecN_norm(dvec, 2);
}

/** returns ||dvec||_p */
static double dvec2_norm_p_v(const double *dvec, double p) {
    return dvecN_norm_p(dvec, p, 2);
}

/** returns ||dvec||_1 */
static double dvec2_norm_1_v(const double *dvec) {
    return dvecN_norm_1(dvec, 2);
}

/** returns ||dvec||_inf */
static double dvec2_norm_inf_v(const double *dvec) {
    return dvecN_norm_inf(dvec, 2);
}

/** dst = dvec / (norm(dvec) > 0 ? norm(dvec) : 1) */
static dvec2 dvec2_normalize_v(const double *dvec) {
    dvec2 res;
    dvecN_normalize(res.v, dvec, 2);
    return res;
}

/** dst = from + (to - from) * t */
static dvec2 dvec2_lerp_v(const double *from, const double *to, double t) {
    dvec2 res;
    dvecN_lerp(res.v, from, to, t, 2);
    return res;
}

#endif //MATHC_VEC_DVEC2_V_H
