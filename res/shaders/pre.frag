#version 330 core

layout (location = 0) out vec4 fragPosition;
layout (location = 1) out vec4 fragNormal;

uniform vec4 color;

in vec4 normal_worldSpace;
in vec4 position_worldSpace;
in vec4 eye_worldSpace;

void main(){
     fragPosition = vec4(vec3(position_worldSpace), 1);
     fragNormal = vec4(vec3(normal_worldSpace), 1);
}
