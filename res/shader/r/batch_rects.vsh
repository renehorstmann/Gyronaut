layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_tex_coord;

// needs a location for each col -> 4 * vec4 [location 2:5]
layout(location = 2) in mat4 in_m;

layout(location = 6) in vec4 in_color;
layout(location = 7) in vec2 in_uv_offset;

out vec4 v_color;
out vec2 v_tex_coord;


uniform mat4 vp;

void main() {
  gl_Position = vp * in_m * vec4(in_position.x, in_position.y, 0, 1);
  v_color = in_color;
  v_tex_coord = in_tex_coord + in_uv_offset;
}
