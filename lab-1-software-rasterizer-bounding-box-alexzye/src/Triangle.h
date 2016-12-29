#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"

class Triangle 
{
public:
    Triangle(Vertex p1, Vertex p2, Vertex p3);
    int *getBoundingBox();
    Vertex *getVertices();

private:
    Vertex p1;
    Vertex p2;
    Vertex p3;
};


#endif