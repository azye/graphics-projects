#version 330 core 
in vec3 fragNor;
in vec4 pos;
out vec4 color;

void main()
{
    vec3 normal = normalize(fragNor);
    vec3 toEye = -normalize(pos.xyz);
    float cross_product = abs(dot(normal, toEye));
    
    if (cross_product < 0.3) {
        color = vec4(0, 0, 0, 1);
    }
    else {    
        color = vec4(1, 1, 1, 1);
    }
}
