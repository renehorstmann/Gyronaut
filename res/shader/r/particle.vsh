layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_tex_coord;

layout(location = 2) in mat4 in_pose;
// uses location [2:5] (for each col)

layout(location = 6) in mat4 in_pose_speed;
// uses location [6:9] (for each col)

layout(location = 10) in mat4 in_pose_acc;
// uses location [10:13] (for each col)

layout(location = 14) in mat4 in_uv;
// uses location [14:17] (for each col)

layout(location = 18) in vec4 in_color;
layout(location = 19) in vec4 in_color_speed;
layout(location = 20) in vec2 in_uv_offset_step;
layout(location = 21) in float in_uv_offset_time;
layout(location = 22) in float in_start_time;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;
uniform float time;

void main() {
  float dt = time - in_start_time;
  mat4 speed_shift = in_pose_speed * dt;
  mat4 acc_shift = in_pose_acc * (dt * dt);
  mat4 pose = acc_shift * speed_shift * in_pose;
  gl_Position = vp * pose * in_position;

  vec2 uv_step = in_uv_offset_step * floor(dt / in_uv_offset_step);
  v_tex_coord = (in_uv * in_tex_coord).xy + uv_step;

  v_color = in_color + (in_color_speed * dt);
}
