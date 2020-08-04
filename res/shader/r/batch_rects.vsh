layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_tex_coord;
layout(location = 2) in mat4 in_m;

out vec2 v_tex_coord;

uniform mat4 vp;

void main() {
  //gl_Position = vp * in_m * vec4(in_position.x, in_position.y, 0, 1);
  gl_Position = vp * in_m * vec4(in_position.x, in_position.y, 0, 1);
//  if(in_m[1][1] == 1)
//    gl_Position.x /= 4;
//  else
//    gl_Position.y /= 4;
  v_tex_coord = in_tex_coord;
}
