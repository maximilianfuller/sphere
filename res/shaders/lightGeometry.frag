#version 330 core

in vec4 gl_FragCoord;
in vec4 eye_worldSpace;

out vec4 fragColor;

/* Lights */
uniform vec3 lightInt;
uniform float ambCoeff = 0.1;
uniform float diffCoeff = 1.0;
uniform float specCoeff = 0.8;

/* Point Light */
uniform float time;
uniform float lightRadius;

uniform vec3 lightPos;

/* For conversion to screen space */
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

uniform vec2 res;

/* From vertex shader */
in vec4 position_worldSpace;
in vec4 position_screenSpace;

uniform sampler2D position;

void main()
{
    fragColor = vec4(lightInt, 1.0);
    vec2 ratio = normalize(res);

    vec3 curFragPos = vec3(position_worldSpace);
    vec3 lastFragPos = vec3(texture(position, gl_FragCoord.xy / res));
    float depth = length(curFragPos - lastFragPos);
    float fade = smoothstep(0, 1.0, depth);

    float d = length((vec2(position_screenSpace) - vec2(p * v * vec4(lightPos, 1.0))) * ratio);
    float t = 1 - smoothstep(lightRadius * 0.25, lightRadius * 0.4 + 0.1 * cos(time), d);
    fragColor.w *= t * fade;
}
