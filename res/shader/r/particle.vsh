layout(location = 0) in mat4 in_pose;
// uses location [0:4] (for each col)

layout(location = 4) in mat4 in_uv;
// uses location [4:7] (for each col)

layout(location = 8) in vec4 in_speed;
layout(location = 9) in vec4 in_acc;
layout(location = 10) in vec4 in_rot_quat;

layout(location = 11) in vec4 in_color;
layout(location = 12) in vec4 in_color_speed;

layout(location = 13) in vec2 in_uv_step;
layout(location = 14) in float in_uv_time;

layout(location = 15) in float start_time;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;
uniform float time;

const vec4 vertices[6] = vec4[](
  vec4(-1, -1, 0, 1),
  vec4(+1, -1, 0, 1),
  vec4(-1, +1, 0, 1),
  vec4(-1, +1, 0, 1),
  vec4(+1, -1, 0, 1),
  vec4(+1, +1, 0, 1)
);

const vec4 tex_coords[6] = vec4[](
  vec4(0, 1, 0, 1),
  vec4(1, 1, 0, 1),
  vec4(0, 0, 0, 1),
  vec4(0, 0, 0, 1),
  vec4(1, 1, 0, 1),
  vec4(1, 0, 0, 1)
);

void main() {
  float dt = time - start_time;

  vec4 pos = vertices[gl_VertexID];
  // todo: slerp and rotate
  pos = in_pose * pos;
  pos += in_speed * dt;
  pos += in_acc * (dt * dt);
  gl_Position = vp * pos;

  vec2 uv_step = in_uv_step * floor(dt / in_uv_time);
  v_tex_coord = (in_uv * tex_coords[gl_VertexID]).xy + uv_step;

  v_color = in_color + (in_color_speed * dt);
}
