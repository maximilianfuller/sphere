#version 330 core

out vec4 fragColor;

uniform vec4 color;

uniform sampler2D data;
uniform int useTexture = 0;
uniform int useLighting = 1;

in vec4 normal_worldSpace;
in vec4 position_worldSpace;
in vec4 eye_worldSpace;
in vec2 texc;

/* Resolution */
uniform vec2 res;

void main(){
    vec4 lightData = texture(data, gl_FragCoord.xy / res);
    fragColor = lightData;
}
