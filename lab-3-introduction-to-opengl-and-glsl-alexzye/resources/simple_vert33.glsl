#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec4 vertexColor;

uniform mat4 P;
uniform mat4 MV;
uniform float time;

out vec4 fragmentColor;
out vec3 coords;
out float t;

void main()
{
    gl_Position = P * MV * vec4(vertPos, 1.0);
    fragmentColor = vertexColor;
    coords = vertPos;
    t = time;
}
