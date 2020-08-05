layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_tex_coord;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 m;
uniform mat4 vp;
uniform mat4 uv;
uniform vec4 color;

void main() {
  gl_Position = vp * m * in_position;
  v_tex_coord = (uv * in_tex_coord).xy;
  v_color = color;
}
