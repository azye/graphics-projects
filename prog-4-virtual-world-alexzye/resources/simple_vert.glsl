#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec3 fragNor;
out vec4 pos;

void main()
{
    gl_Position = P * V * M * vertPos;
    fragNor = (vec4(vertNor, 0.0)).xyz;
    pos = vertPos;
}
