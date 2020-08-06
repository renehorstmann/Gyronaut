layout(location = 0) in mat4 in_pose;
// uses location [0:4] (for each col)

layout(location = 4) in mat4 in_uv;
// uses location [4:7] (for each col)

layout(location = 8) in vec4 in_speed;
layout(location = 9) in vec4 in_acc;
layout(location = 10) in vec4 in_axis_angle;

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

vec4 quat_from_axis_angle(vec3 axis, float angle) {
  vec4 qr;
  float half_angle = angle * 0.5;
  qr.x = axis.x * sin(half_angle);
  qr.y = axis.y * sin(half_angle);
  qr.z = axis.z * sin(half_angle);
  qr.w = cos(half_angle);
  return qr;
}

vec4 quat_conj(vec4 q) {
  return vec4(-q.x, -q.y, -q.z, q.w);
}

vec4 quat_mult(vec4 q1, vec4 q2) {
  vec4 qr;
  qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
  qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
  qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
  qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
  return qr;
}

vec3 rotate_vertex_position(vec3 position, vec3 axis, float angle) {
  vec4 qr = quat_from_axis_angle(axis, angle);
  vec4 qr_conj = quat_conj(qr);
  vec4 q_pos = vec4(position.x, position.y, position.z, 0);

  vec4 q_tmp = quat_mult(qr, q_pos);
  qr = quat_mult(q_tmp, qr_conj);

  return vec3(qr.x, qr.y, qr.z);
}


void main() {
  float dt = time - start_time;

  vec4 pos = vertices[gl_VertexID];

  // only rotate if rotation is given
  if(abs(in_axis_angle.w) > 0)
    pos = vec4(rotate_vertex_position(pos.xyz, in_axis_angle.xyz, in_axis_angle.w * dt), 1);

  pos = in_pose * pos;
  pos += in_speed * dt;
  pos += in_acc * (dt * dt);
  gl_Position = vp * pos;

  vec2 uv_step = in_uv_step * floor(dt / in_uv_time);
  v_tex_coord = (in_uv * tex_coords[gl_VertexID]).xy + uv_step;

  v_color = in_color + (in_color_speed * dt);
}
