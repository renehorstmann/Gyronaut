#ifndef MATHC_IO_DOUBLE_H
#define MATHC_IO_DOUBLE_H

#include <stdio.h>
#include "../types/double.h"

//
// from cglm/io.h
//

#ifndef MATHC_PRINT_PRECISION
#  define MATHC_PRINT_PRECISION 5
#endif

#ifndef MATHC_PRINT_MAX_TO_SHORT
#  define MATHC_PRINT_MAX_TO_SHORT 1e5
#endif

#ifndef MATHC_PRINT_COLOR
#  define MATHC_PRINT_COLOR "\033[36m"
#endif

#ifndef MATHC_PRINT_COLOR_RESET
#  define MATHC_PRINT_COLOR_RESET "\033[0m"
#endif

static void dvec2_print_f(dvec2 vec, FILE *ostream) {
    fprintf(ostream, "dvec2: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 2; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void dvec2_print(dvec2 vec) {
    dvec2_print_f(vec, stdout);
}

static void dmat2_print_f(dmat2 mat, FILE *ostream) {
    fprintf(ostream, "dmat2: " MATHC_PRINT_COLOR "\n");
    for (int c = 0; c < 2; c++) {
        fprintf(ostream, "  |");
        for (int r = 0; r < 2; r++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[r][c]);
            else
                fprintf(ostream, " %g", mat.m[r][c]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET "\n");
}

static void dmat2_print(dmat2 matrix) {
    dmat2_print_f(matrix, stdout);
}


static void dvec3_print_f(dvec3 vec, FILE *ostream) {
    fprintf(ostream, "dvec3: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 3; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void dvec3_print(dvec3 vec) {
    dvec3_print_f(vec, stdout);
}

static void dmat3_print_f(dmat3 mat, FILE *ostream) {
    fprintf(ostream, "dmat3: " MATHC_PRINT_COLOR "\n");
    for (int c = 0; c < 3; c++) {
        fprintf(ostream, "  |");
        for (int r = 0; r < 3; r++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[r][c]);
            else
                fprintf(ostream, " %g", mat.m[r][c]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET "\n");
}

static void dmat3_print(dmat3 matrix) {
    dmat3_print_f(matrix, stdout);
}

static void dvec4_print_f(dvec4 vec, FILE *ostream) {
    fprintf(ostream, "dvec4: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 4; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void dvec4_print(dvec4 vec) {
    dvec4_print_f(vec, stdout);
}

static void dmat4_print_f(dmat4 mat, FILE *ostream) {
    fprintf(ostream, "dmat4: " MATHC_PRINT_COLOR "\n");
    for (int c = 0; c < 4; c++) {
        fprintf(ostream, "  |");
        for (int r = 0; r < 4; r++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[r][c]);
            else
                fprintf(ostream, " %g", mat.m[r][c]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET "\n");
}

static void dmat4_print(dmat4 matrix) {
    dmat4_print_f(matrix, stdout);
}


//
// quat
//

static void dquat_print_f(dquat quat, FILE *ostream) {
    fprintf(ostream, "dquat: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 4; v++) {
        if (quat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, quat.v[v]);
        else
            fprintf(ostream, " %g", quat.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void dquat_print(dquat quat) {
    dquat_print_f(quat, stdout);
}

#endif //MATHC_IO_DOUBLE_H
