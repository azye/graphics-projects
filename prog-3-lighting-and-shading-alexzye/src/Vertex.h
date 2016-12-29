#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_

class Vertex 
{
public:
    Vertex() {};
    Vertex(float x, float y, float z);
    float getX();
    float getY();
    float getZ();
    // void setZ(float val);
    // void setX(float val);
    // void setY(float val);
    // int getR();
    // int getG();
    // int getB();
    // void shift();
    // void toString();
     

private:
    float x, y, z;
    // int r, g, b;
};

#endif