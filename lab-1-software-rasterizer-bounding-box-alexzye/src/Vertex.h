#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_

class Vertex 
{
public:
    Vertex() {};
    Vertex(int x, int y);

    int getX();
    int getY();
    void toString();
     

private:
    int x, y;
};

#endif