#version 330 core

out vec4 fragColor;
in vec4 gl_FragCoord;

uniform vec4 color;

/* Resolution */
uniform vec2 res;

/* Particle texture and position data */
uniform sampler2D tex;
uniform sampler2D position;

in vec4 position_worldSpace;
in vec2 texc;

void main()
{
    vec3 particlePos = vec3(position_worldSpace);
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));

    float depth = length(particlePos - fragPos);
    float t = smoothstep(0, 0.5, depth);

    vec4 color = clamp(texture(tex, texc), 0, 1);

    fragColor = t * color;
}

/*
void main(){
    vec3 base_color = vec3(0);
    fragColor = vec4(0);

    if(useTexture > 0)
    {
        base_color = clamp(texture(tex,texc).xyz,0,1);
    }
    else
    {
        base_color = vec3(color);
    }

    if(useLighting > 0)
    {
        vec4 vertexToLight = normalize(vec4(1,1,1,0));
        float diffuseIntensity = max(0.0, dot(vertexToLight, normal_worldSpace));
        fragColor += vec4(max(vec3(0), vec3(1,1,1) * base_color * diffuseIntensity),0.f);

        // Add specular component
        vec4 lightReflection = normalize(-reflect(vertexToLight, normal_worldSpace));
        vec4 eyeDirection = normalize(eye_worldSpace - position_worldSpace);
        float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), 150);
        fragColor += vec4(max(vec3(0), vec3(1,1,1) * base_color * specIntensity),1.f);
    }
    else
    {
        fragColor = vec4(base_color, color.w);
    }
}
*/
