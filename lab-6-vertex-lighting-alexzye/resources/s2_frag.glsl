#version 330 core 
in vec3 fragNor;
in vec4 pos;
out vec4 color;

void main()
{
    vec3 vColor = vec3(0.50,0.25,0.69);
    vec3 toLight = vec3(1., 1., 0.);
    vec3 normal = normalize(fragNor);
    vec3 toEye = -normalize(vec3(pos.xyz));
    vec3 h = normalize(toEye + toLight);
    float diffuse = max(0.0, dot(normal, toLight));
    float phong_exp = 64.0;
    float specular = pow(max(0.0, dot(h, normal)), phong_exp);

    vec3 ambient = vec3(0.2,0.1,0.1);
    vec3 lightcolor = vec3( 0, 0, 1);
    vec3 i = ( vColor + ambient ) * diffuse + specular * lightcolor ;
    // Map normal in the range [-1, 1] to color in range [0, 1];
    vec3 Ncolor = 0.5*normal + 0.5;
    color = vec4(i.x, i.y, i.z, 1.0);
}
