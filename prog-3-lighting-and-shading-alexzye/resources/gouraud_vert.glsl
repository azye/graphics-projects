#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
uniform mat4 P;
uniform mat4 MV;
uniform float light;


out vec4 vertexColor;

void main()
{
    gl_Position = P * MV * vertPos;
    vec3 fragNor = (MV * vec4(vertNor, 0.0)).xyz;
    
    vec3 vColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 toLight = vec3(light, 2.0, 2.0);
    vec3 normal = normalize(vertNor);
    float diffuse = max(0.0, dot(normal, toLight));
    
    vec3 toEye = -normalize(vec3(vertPos.xyz));
    vec3 h = normalize(toEye + toLight);
    
    vec3 ambient = vec3(0.2f,0.1f,0.1f);

    vec3 lightcolor = vec3( 1.0f, 1.0f, 1.0f);

    vec3 i = (vColor * (ambient + lightcolor * diffuse))/4;
    // Map normal in the range [-1, 1] to color in range [0, 1];
    
    vertexColor = vec4(i.x, i.y, i.z, 1.0);
}
