layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_tex_coord;

layout(location = 2) in mat4 in_pose;
// uses location [2:5] (for each col)

layout(location = 6) in mat4 in_uv;
// uses location [6:9] (for each col)

layout(location = 10) in vec4 in_color;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;

void main() {
  gl_Position = vp * in_pose * in_position;
  v_tex_coord = (in_uv * in_tex_coord).xy;
  v_color = in_color;
}
