layout(location = 0) in mat4 in_pose;
// uses location [0:3] (for each col)

layout(location = 4) in mat4 in_uv;
// uses location [4:7] (for each col)

layout(location = 8) in vec4 in_color;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;

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
  gl_Position = vp * in_pose * position[gl_VertexID];
  v_tex_coord = (in_uv * tex_coord[gl_VertexID]).xy;
  v_color = in_color;
}
