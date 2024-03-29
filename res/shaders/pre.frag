#version 330 core

layout (location = 0) out vec4 fragPosition;
layout (location = 1) out vec4 fragNormal;
layout (location = 2) out vec4 fragColorSpecular;

uniform vec4 color;
uniform float shininess = 0.01;

uniform int useTexture = 0;
uniform sampler2D tex;

in vec4 normal_worldSpace;
in vec4 position_worldSpace;
in vec4 eye_worldSpace;
in vec2 texc;

void main(){
    /* Fragment color without texture */
    vec3 fragColor = vec3(color);

    /* Fragment color with texture */
    if(useTexture == 1)
    {
        fragColor = mix(fragColor, vec3(texture(tex, texc)), color.w);
    }

    /* G Buffer position, normal, and shininess */
    fragPosition = vec4(vec3(position_worldSpace) / position_worldSpace.w, 1);
    fragNormal = vec4(vec3(normal_worldSpace) / position_worldSpace.w, 1);
    fragColorSpecular = vec4(fragColor, shininess);

}
