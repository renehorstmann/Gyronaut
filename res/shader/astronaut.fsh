in vec2 v_tex_coord;
out vec4 out_frag_color;
uniform sampler2D tex;
void main() {
  out_frag_color = texture(tex, v_tex_coord);
}