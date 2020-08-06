#ifndef R_PARTICLE_H
#define R_PARTICLE_H

#include <stdbool.h>
#include "cglm/types.h"
#include "core.h"

typedef struct rParticleRect_s {
    mat4 pose;
    mat4 uv;
    vec4 color;
    mat4 pose_speed;
    mat4 pose_acc;
    vec4 color_speed;
    vec2 uv_offset_step;
    float uv_offset_time;
    float start_time;
} rParticleRect_s;

typedef struct rParticle {
    struct rParticleRects_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint rects_bo;
    GLuint tex;
    bool owns_tex;
} rParticle;

void r_particle_init(rParticle *self, int num, const float *vp, GLuint tex_sink);

void r_particle_kill(rParticle *self);

void r_particle_update(rParticle *self);

void r_particle_render(rParticle *self);

void r_particle_set_texture(rParticle *self, GLuint tex);

#endif //R_PARTICLE_H
