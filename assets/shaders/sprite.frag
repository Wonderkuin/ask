#version 330 core

in vec2 v_uv;

uniform sampler2D image;
uniform vec4 tint;

out vec4 frag_color;

void main() {
    frag_color = texture(image, v_uv) * tint;
}
