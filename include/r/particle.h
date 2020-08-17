#ifndef R_PARTICLE_H
#define R_PARTICLE_H

#include <stdbool.h>
#include "mathc/types.h"
#include "core.h"

typedef struct rParticleRect_s {
    mat44f pose;
    mat44f uv;
    vec4f speed;
    vec4f acc;
    vec4f axis_angle;
    vec4f color;
    vec4f color_speed;
    vec2f uv_step;
    float uv_time;
    float start_time;
} rParticleRect_s;

typedef struct rParticle {
    rParticleRect_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} rParticle;

void r_particle_init(rParticle *self, int num, const float *vp, GLuint tex_sink);

void r_particle_kill(rParticle *self);

void r_particle_update(rParticle *self, int offset, int size);

void r_particle_render(rParticle *self, float time);

void r_particle_set_texture(rParticle *self, GLuint tex);

#endif //R_PARTICLE_H
