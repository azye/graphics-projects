#version 330 core 
in vec3 fragNor;
in vec4 pos;
out vec4 color;

void main()
{
    vec3 vColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 toLight = vec3(2.0, 2.0, 2.0);
    vec3 normal = normalize(fragNor);
    float diffuse = max(0.0, dot(normal, toLight));
    
    vec3 toEye = -normalize(vec3(pos.xyz));
    vec3 h = normalize(toEye + toLight);
    
    float phong_exp = 64.0;
    float specular = pow(max(0.0, dot(h, normal)), phong_exp);

    vec3 ambient = vec3(0.2,0.1,0.1);

    vec3 lightcolor = vec3(1.0f, 1.0f, 1.0f);

    vec3 i = (vColor * (ambient + lightcolor * diffuse) + (lightcolor * specular))/4;
    // Map normal in the range [-1, 1] to color in range [0, 1];
    
    color = vec4(i.x, i.y, i.z, 1.0);
}
