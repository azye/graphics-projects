#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"

class Triangle 
{
public:
    Triangle();
    Triangle(Vertex p1, Vertex p2, Vertex p3);
    float *getBoundingBox();
    float *getXBounds();
    float *getYBounds();
    float *getZBounds();
    void toString();
    Vertex *getVertices();
    float *getCoords(int x, int y);
    Vertex getP1() {return p1;}
    Vertex getP2() {return p2;}
    Vertex getP3() {return p3;}
    void setP1(float x, float y) {p1.setX(x); p1.setY(y);}
    void setP2(float x, float y) {p2.setX(x); p2.setY(y);}
    void setP3(float x, float y) {p3.setX(x); p3.setY(y);}
    void setZ(float z1, float z2, float z3) {p1.setZ(z1); p2.setZ(z2); p3.setZ(z3);}

private:
    Vertex p1;
    Vertex p2;
    Vertex p3;
    
};


#endif