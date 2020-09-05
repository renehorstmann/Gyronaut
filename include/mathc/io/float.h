#ifndef MATHC_IO_FLOAT_H
#define MATHC_IO_FLOAT_H

#include <stdio.h>
#include "../types/float.h"

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


static void vec2_print_f(vec2 vec, FILE *ostream) {
    fprintf(ostream, "vec2: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 2; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void vec2_print(vec2 vec) {
    vec2_print_f(vec, stdout);
}

static void mat2_print_f(mat2 mat, FILE *ostream) {
    fprintf(ostream, "mat2: " MATHC_PRINT_COLOR "\n");
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

static void mat2_print(mat2 matrix) {
    mat2_print_f(matrix, stdout);
}


static void vec3_print_f(vec3 vec, FILE *ostream) {
    fprintf(ostream, "vec3: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 3; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void vec3_print(vec3 vec) {
    vec3_print_f(vec, stdout);
}

static void mat3_print_f(mat3 mat, FILE *ostream) {
    fprintf(ostream, "mat3: " MATHC_PRINT_COLOR "\n");
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

static void mat3_print(mat3 matrix) {
    mat3_print_f(matrix, stdout);
}

static void vec4_print_f(vec4 vec, FILE *ostream) {
    fprintf(ostream, "vec4: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 4; v++) {
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void vec4_print(vec4 vec) {
    vec4_print_f(vec, stdout);
}

static void mat4_print_f(mat4 mat, FILE *ostream) {
    fprintf(ostream, "mat4: " MATHC_PRINT_COLOR "\n");
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

static void mat4_print(mat4 matrix) {
    mat4_print_f(matrix, stdout);
}


//
// quat
//

static void quat_print_f(quat quat, FILE *ostream) {
    fprintf(ostream, "quat: " MATHC_PRINT_COLOR "(");
    for (int v = 0; v < 4; v++) {
        if (quat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, quat.v[v]);
        else
            fprintf(ostream, " %g", quat.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET "\n");
}

static void quat_print(quat quat) {
    quat_print_f(quat, stdout);
}

#endif //MATHC_IO_FLOAT_H
