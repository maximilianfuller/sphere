#version 330 core

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D color;

void main(){
    vec2 res = vec2(800, 600);
    fragColor = clamp(texture(position, gl_FragCoord.xy / res), 0, 1);
}
