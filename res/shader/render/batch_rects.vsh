layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_tex_coord;

uniform MatrixBlock
{
  mat4 model;
} matrices[4];

out vec2 v_tex_coord;

uniform mat4 vp;

void main() {
  gl_Position = vp * matrices[0].model * vec4(in_position.x, in_position.y, 0, 1);
  v_tex_coord = in_tex_coord;
}
