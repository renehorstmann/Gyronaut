#include "mathc/float.h"
#include "r/particle.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/prandom.h"
#include "camera.h"
#include "astronaut.h"
#include "a_steam.h"

static const int max_particles = 1000;
static const float particles_ps = 400;
static const float particle_life = 2;

static rParticle particles;
static float current_time;
static int next;



static rParticleRect_s *get_next() {
    int use = next++;
    if(next >= max_particles)
        next = 0;
    return &particles.rects[use];
}

static void setup_particle(rParticleRect_s *p, vec2 pos, vec2 dir) {
	u_pose_set(&p->pose,
	    u_pnoise(pos.x, 1),
	    u_pnoise(pos.y, 1),
	    u_pnoise(0.5, 0.2), u_pnoise(0.5, 0.2),
	    u_pnoise(0, M_PI)
	);

	p->speed.x = u_pnoise(dir.x *5, 4);
	p->speed.y = u_pnoise(dir.y *5, 4);
	
	p->acc.x = u_pnoise(-dir.x *1, 0.1);
	p->acc.y = u_pnoise(-dir.y *1, 0.1);
	
	p->axis_angle.w = u_pnoise(0, M_PI);

	p->color = (vec4) {{
		u_pnoise(0.9, 0.1), u_pnoise(0.9, 0.1), u_pnoise(0.9, 0.1), 1
	}};

    p->color_speed = (vec4) {{
		0, 0, 0, -1.0f / particle_life
	}};
	
	p->start_time = current_time;
}


void a_steam_init() {
	r_particle_init(&particles, max_particles, &camera_vp.m00, r_texture_from_file("res/steam.png"));
}

void a_steam_update(float dtime, mat4 pose, float curve) {
	current_time += dtime;
	int add = (int) ceilf(dtime * particles_ps);
	
	vec4 pos = {{
		-5/ASTRONAUT_W, 
		(5+10*curve)/ASTRONAUT_H, 
		0, 1}};
	pos = mat4_mul_vec(pose, pos);

	vec2 dir = {{
		curve * pose.m10/ASTRONAUT_H
		- (1-fabsf(curve)) * pose.m00/ASTRONAUT_W,
		curve * pose.m11/ASTRONAUT_H
		- (1-fabsf(curve)) * pose.m01/ASTRONAUT_W
	}};
	
	
	int offset = next;
	for(int i=0; i<add; i++)
	    setup_particle(get_next(), pos.xy, dir);
	
	r_particle_update(&particles, offset, add);
}

void a_steam_render() {
	r_particle_render(&particles, current_time);
}
