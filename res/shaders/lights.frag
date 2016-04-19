#version 330 core

in vec4 gl_FragCoord;
in vec4 eye_worldSpace;

out vec4 lightData;

uniform vec3 intensity;
uniform vec3 att;
uniform vec3 lightPos;

uniform sampler2D position;
uniform sampler2D normal;

void main()
{
    vec2 res = vec2(800, 600);
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));
    vec3 fragNormal = vec3(texture(normal, gl_FragCoord.xy / res));

    /* Lighting calculation */
    lightData = vec4(0);

    /* Diffuse component */
    vec3 vertexToLight = normalize(lightPos - fragPos);
    float diffuseFactor = max(dot(fragNormal, vertexToLight), 0.0);
    lightData += vec4(max(vec3(0), intensity * diffuseFactor), 0.0);

    /* Specular component */
    vec3 lightReflection = normalize(-reflect(vertexToLight, fragNormal));
    vec3 eyeDirection = normalize(vec3(eye_worldSpace) - fragPos);
    float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), 150);
    lightData += vec4(max(vec3(0), intensity * specIntensity), 0.0);

    /* Attenuation */
    float d = length(lightPos - fragPos);
    lightData /= (att.x + d * att.y + d * d * att.z);
    lightData.w = 1.0;
}
