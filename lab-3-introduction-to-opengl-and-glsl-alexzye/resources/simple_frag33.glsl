#version 330 core

in vec4 fragmentColor;
in vec3 coords;
layout(location=0) out vec4 fColor;
in float t;


void main()
{
    
    
    vec3 circle = vec3(cos(t) * .20,sin(t) * .20,0);

    vec4 white = vec4(0.1, 0.1, 0.1, 1.0);

    if(distance(circle, coords) < .20) {
        discard;
    }

    vec4 tColor = white * distance(circle, coords) * 7;

    fColor = (fragmentColor + tColor);


}
