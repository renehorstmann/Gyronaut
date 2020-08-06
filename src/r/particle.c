#define DEBUG

#include "cglm/cglm.h"
#include "utilc/alloc.h"
#include "utilc/assume.h"
#include "r/r.h"
#include "r/particle.h"


static void init_rects(rParticleRect_s *instances, int num) {
    for (int i = 0; i < num; i++) {
        rParticleRect_s *r = &instances[i];
        glm_mat4_identity(r->pose);
        glm_mat4_identity(r->uv);
        glm_mat4_identity(r->pose_speed);
        glm_vec4_zero(r->pose_acc);
        glm_vec4_one(r->color);
        glm_vec4_zero(r->color_speed);
        glm_vec2_zero(r->uv_step);
        r->uv_time = FLT_MAX;
        r->start_time = 0;
    }
}

void r_particle_init(rParticle *self, int num, const float *vp, GLuint tex_sink) {
    self->rects = New(rParticleRect_s, num);
    init_rects(self->rects, num);

    self->num = num;
    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/particle.vsh",
            "res/shader/r/particle.fsh",
            NULL});
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_pose_speed = 8;
    const int loc_pose_acc = 12;
    const int loc_color = 13;
    const int loc_color_speed = 14;
    const int loc_uvstep_uvtime_starttime = 15;
    assume(offsetof(rParticleRect_s, start_time)
           - offsetof(rParticleRect_s, uv_step)
           == 3 * sizeof(float),
           "particle struct error, uvstep_uvtime_starttime not packed");

    self->tex = tex_sink;
    self->owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture
        glUniform1i(glGetUniformLocation(self->program, "tex"), self->tex);

        // vbo
        {
            glGenBuffers(1, &self->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rParticleRect_s),
                         self->rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self->vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s),
                                      (void *) (offsetof(rParticleRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // pose_speed
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose_speed + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s),
                                      (void *) (offsetof(rParticleRect_s, pose_speed) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // pose_acc
            glEnableVertexAttribArray(loc_pose_acc);
            glVertexAttribPointer(loc_pose_acc, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, pose_acc));
            glVertexAttribDivisor(loc_pose_acc, 1);

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            // color_speed
            glEnableVertexAttribArray(loc_color_speed);
            glVertexAttribPointer(loc_color_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color_speed));
            glVertexAttribDivisor(loc_color_speed, 1);

            // uv_step__uv_time__starttime
            glEnableVertexAttribArray(loc_uvstep_uvtime_starttime);
            glVertexAttribPointer(loc_uvstep_uvtime_starttime, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, uv_step));
            glVertexAttribDivisor(loc_uvstep_uvtime_starttime, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
}

void r_particle_kill(rParticle *self) {
    free(self->rects);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    *self = (rParticle) {0};
}

void r_particle_update(rParticle *self) {
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    self->num * sizeof(rParticleRect_s), self->rects);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void r_particle_render(rParticle *self, float time) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glUniform1f(glGetUniformLocation(self->program, "time"), time);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, self->num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void r_particle_set_texture(rParticle *self, GLuint tex) {
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    self->tex = tex;
}

