#version 330 core

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 uv_rect;

out vec2 v_uv;

void main() {
    gl_Position = projection * model * vec4(a_pos, 0.0, 1.0);
    v_uv = mix(uv_rect.xy, uv_rect.zw, a_uv);
}
