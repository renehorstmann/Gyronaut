
#include "cglm/types.h"
#include "r/particle.h"
#include "r/texture.h"
#include "r/rect.h"
#include "camera.h"
#include "a_steam.h"

static const int max_particles = 1000;
static const float particles_ps = 200;
static const float particle_life = 4;

static rParticle particles;
static float current_time;
static int next;


static float randf() {
	return (float) rand() / RAND_MAX;
}

static float noise(float f, float amplitude) {
	return f - amplitude + 2*amplitude*randf();
}

static rParticleRect_s *get_next() {
    int use = next++;
    if(next >= max_particles)
        next = 0;
    return &particles.rects[use];
}

static void setup_particle(rParticleRect_s *p, mat4 pose) {
	r_pose_set(p->pose,
	    noise(R_PoseX(pose), 1), noise(R_PoseY(pose), 1),
	    noise(0.6, 0.2), noise(0.6, 0.2),
	    noise(0, M_PI)
	);
	
	glm_vec4_copy((vec4) {
		noise(-pose[0][0] *1, 3),
		noise(-pose[0][1] *1, 3)
	}, p->speed);
	
	glm_vec4_copy((vec4) {
		noise(pose[0][0] *0.1, 0.1),
		noise(pose[0][1] *0.1, 0.1)
	}, p->acc);
	
	p->axis_angle[3] = noise(0, M_PI);
	
	glm_vec4_copy((vec4) {
		noise(0.9, 0.1), noise(0.9, 0.1), noise(0.9, 0.1), 1
	}, p->color);
	
	glm_vec4_copy((vec4) {
		0, 0, 0, -1.0f / particle_life
	}, p->color_speed);
	
	p->start_time = current_time;
}

void a_steam_init() {
	r_particle_init(&particles, max_particles, &camera_vp.m00, r_texture_from_file("res/steam.png"));
}

void a_steam_update(float dtime, mat4 pose) {
	current_time += dtime;
	int add = (int) ceilf(dtime * particles_ps);
	
	printf("%d\n", add);
	
	int offset = next;
	for(int i=0; i<add; i++)
	    setup_particle(get_next(), pose);
	
	r_particle_update(&particles, offset, add);
}

void a_steam_render() {
	r_particle_render(&particles, current_time);
}
