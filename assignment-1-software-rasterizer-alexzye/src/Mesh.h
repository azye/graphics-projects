#pragma once
#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "Triangle.h"

using namespace std;

class Mesh
{
public:
    Mesh(vector<Triangle> tri);
    float* getBox();
    void scale(float scale);
    float normalize();
    vector<Triangle>getTriangles();
    void shift(float shiftx, float shifty);
    
private:
    vector<Triangle>triangles;
    
};

#endif