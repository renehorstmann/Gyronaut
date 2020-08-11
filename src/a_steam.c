#define DEBUG
#include "cglm/types.h"
#include "r/particle.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "astronaut.h"
#include "a_steam.h"

static const int max_particles = 1000;
static const float particles_ps = 400;
static const float particle_life = 2;

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

static void setup_particle(rParticleRect_s *p, vec2 pos, vec2 dir) {
	u_pose_set(p->pose,
	    noise(pos[0], 1), 
	    noise(pos[1], 1),
	    noise(0.5, 0.2), noise(0.5, 0.2),
	    noise(0, M_PI)
	);

	p->speed[0] = noise(dir[0] *5, 4);
	p->speed[1] = noise(dir[1] *5, 4);
	
	p->acc[0] = noise(-dir[0] *1, 0.1);
	p->acc[1] = noise(-dir[1] *1, 0.1);
	
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

void a_steam_update(float dtime, mat4 pose, float curve) {
	current_time += dtime;
	int add = (int) ceilf(dtime * particles_ps);
	
	vec4 pos = {
		-5/ASTRONAUT_W, 
		(5+10*curve)/ASTRONAUT_H, 
		0, 1};
	glm_mat4_mulv(pose, pos, pos);
	
	vec2 dir = {
		curve * pose[1][0]/ASTRONAUT_H 
		- (1-fabsf(curve)) * pose[0][0]/ASTRONAUT_W,
		curve * pose[1][1]/ASTRONAUT_H 
		- (1-fabsf(curve)) * pose[0][1]/ASTRONAUT_W
	};
	
	
	int offset = next;
	for(int i=0; i<add; i++)
	    setup_particle(get_next(), pos, dir);
	
	r_particle_update(&particles, offset, add);
}

void a_steam_render() {
	r_particle_render(&particles, current_time);
}
