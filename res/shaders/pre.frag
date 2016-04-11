#version 330 core

layout (location = 0) out vec3 fragPosition;
layout (location = 1) out vec3 fragNormal;
layout (location = 2) out vec4 fragColor;

uniform vec4 color;

in vec4 normal_worldSpace;
in vec4 position_worldSpace;
in vec4 eye_worldSpace;

void main(){
     fragPosition = vec3(position_worldSpace);
     fragNormal = vec3(normal_worldSpace);
     fragColor = color;
}
