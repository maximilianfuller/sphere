#version 330 core

out vec4 fragColor;
in vec4 gl_FragCoord;

/* Particle uniforms */
uniform float age;
uniform vec4 color;
uniform sampler2D tex;

/* Resolution */
uniform vec2 res;

/* G buffer */
uniform sampler2D position;

/* From vertex shader */
in vec4 position_worldSpace;
in vec2 texc;

void main()
{
    // Sample particle color from texture
    vec4 particleColor = clamp(texture(tex, texc), 0, 1) * color;

    // Fade based on proximity to scene geometry
    vec3 particlePos = vec3(position_worldSpace);
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));
    float depth = length(particlePos - fragPos);
    float depthFactor1 = smoothstep(0, 0.5, depth);

    // Fade based on age
    float ageFactor1 = smoothstep(0, 0.2, age);
    float ageFactor2 = smoothstep(0, 0.4, 1 - age);

    fragColor = depthFactor1 * ageFactor1 * ageFactor2 * particleColor;
}
