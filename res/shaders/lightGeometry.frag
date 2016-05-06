#version 330 core

in vec4 gl_FragCoord;
in vec4 eye_worldSpace;

out vec4 fragColor;

uniform float time;

/* Lights uniforms */
uniform vec4 color;
uniform float lightRadius;
uniform vec3 lightPos;

/* G buffer */
uniform sampler2D position;

/* Resolution */
uniform vec2 res;

/* Vertex shader output */
in vec4 position_worldSpace;
in vec4 position_screenSpace;

void main()
{
    fragColor = color;
    vec2 ratio = normalize(res);

    // Fade based on proximity to scene geometry
    vec3 curFragPos = vec3(position_worldSpace);
    vec3 lastFragPos = vec3(texture(position, gl_FragCoord.xy / res));
    float depth = length(curFragPos - lastFragPos);
    float fadeDepth = smoothstep(0.2, 1.0, depth);

    // Fade out on the edges of the light
    float d = length((vec2(position_screenSpace) - vec2(lightPos)) * ratio);
    float startFade = lightRadius * 0.2;
    float endFade = lightRadius * (0.3 + 0.05 * cos(time));
    float fadeAtt = 1 - smoothstep(startFade, endFade, d);

    fragColor.w *= fadeDepth * fadeAtt;
}
