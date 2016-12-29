#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
uniform mat4 P;
uniform mat4 MV;
uniform float Time;
out vec3 fragNor;
out vec4 pos;

void main()
{
    vec4 location = P * MV * vertPos;
    vec4 position = vec4(location.x, location.y - Time * 2, location.z, location.w);
    
    gl_Position = vec4(location.x + cos(Time * 2) * .20, location.y + sin(Time * 2) * .20, location.z, location.w);
    pos = position;
    fragNor = (MV * vec4(vertNor, 0.0)).xyz;
}
