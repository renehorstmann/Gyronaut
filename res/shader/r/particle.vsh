layout(location = 0) in mat4 in_pose;
// uses location [0:4] (for each col)

layout(location = 4) in mat4 in_uv;
// uses location [4:7] (for each col)

layout(location = 8) in mat4 in_pose_speed;
// uses location [8:11] (for each col)

layout(location = 12) in vec4 in_pose_acc;

layout(location = 13) in vec4 in_color;
layout(location = 14) in vec4 in_color_speed;
layout(location = 15) in vec4 in_uvstep_uvtime_starttime;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;
uniform float time;

const vec4 position[6] = vec4[](
  vec4(-1, -1, 0, 1),
  vec4(+1, -1, 0, 1),
  vec4(-1, +1, 0, 1),
  vec4(-1, +1, 0, 1),
  vec4(+1, -1, 0, 1),
  vec4(+1, +1, 0, 1)
);

const vec4 tex_coord[6] = vec4[](
  vec4(0, 1, 0, 1),
  vec4(1, 1, 0, 1),
  vec4(0, 0, 0, 1),
  vec4(0, 0, 0, 1),
  vec4(1, 1, 0, 1),
  vec4(1, 0, 0, 1)
);

void main() {
  float dt = time - in_uvstep_uvtime_starttime[3];

//  mat4 speed_shift = in_pose_speed * dt;
//  speed_shift[3][3] = 1;
//  vec4 acc_shift = in_pose_acc * (dt * dt);
//  mat4 pose = in_pose * speed_shift;
//  pose[3] += acc_shift;
//  gl_Position = vp * pose * position[gl_VertexID];
  gl_Position = vp * in_pose * position[gl_VertexID];

  vec2 uv_step = in_uvstep_uvtime_starttime.xy * floor(dt / in_uvstep_uvtime_starttime[2]);
  v_tex_coord = (in_uv * tex_coord[gl_VertexID]).xy + uv_step;

  v_color = in_color + (in_color_speed * dt);
}
