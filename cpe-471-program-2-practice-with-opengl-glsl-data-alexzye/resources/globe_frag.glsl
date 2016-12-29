#version 330 core 
in vec3 fragNor;
out vec4 color;
in vec4 position;

uniform vec2 resolution;

void main()
{
    vec3 normal = normalize(fragNor);
    // Map normal in the range [-1, 1] to color in range [0, 1];
    if(position.z > 0.45) {
        discard;
    }

    vec3 Ncolor = 0.5*normal + 0.5;
    
    float dist = distance(vec2(0.0f, 0.0f), position.xy);

    color = vec4(abs(dist)/1.3f, abs(dist)/1.3, abs(dist)/1.3, 0.7);
}


