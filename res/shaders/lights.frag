#version 330 core

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform sampler2D position;
uniform sampler2D normal;

void main(){
    vec2 res = vec2(800, 600);
    fragColor = vec4(vec3(texture(position, gl_FragCoord.xy / res)), 1);
}
