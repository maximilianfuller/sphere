#version 330 core

out vec4 fragColor;
in vec4 gl_FragCoord;

uniform vec4 color;

/* Resolution */
uniform vec2 res;

/* Particle texture */
uniform sampler2D tex;

/* G buffeer position */
uniform sampler2D position;

/* From vertex shader */
in vec4 position_worldSpace;
in vec2 texc;

void main()
{
    // Fade based on proximity to g buffer
    vec3 particlePos = vec3(position_worldSpace);
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));
    float depth = length(particlePos - fragPos);
    float t = smoothstep(0, 0.5, depth);

    vec4 color = clamp(texture(tex, texc), 0, 1);

    fragColor = t * color;
}
