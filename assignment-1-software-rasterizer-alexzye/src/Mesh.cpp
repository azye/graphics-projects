#include <iostream>
#include "Mesh.h"

using namespace std;

Mesh::Mesh(vector<Triangle> tri) {
    triangles = tri;
}

float Mesh::normalize() {
    // Get max min z
    // add min to all values so its between 0 and 1.1 (for example)
    // multiply val to 255/1.1 for color
    float min = -99;
    
    for(int i=0; i< triangles.size(); i++) {
        float *zbounds = triangles[i].getZBounds();
        if(min == -99 || min > zbounds[0]) {
            min = zbounds[0];
        }
    }
    
    if(min < 0) {
        min *= -1;
    }

    for(int i=0; i< triangles.size(); i++) {
        triangles[i].setZ(triangles[i].getP1().getZ() + min, triangles[i].getP2().getZ() 
            + min, triangles[i].getP2().getZ() + min);
    }
    
    float max = -99;
    for(int i=0; i< triangles.size(); i++) {
        float *zbounds = triangles[i].getZBounds();
        if(max == -99 || max < zbounds[0]) {
            max = zbounds[0];
        }
    }
    return max;
}

void Mesh::scale(float scale) {    
    for(int i=0; i< triangles.size(); i++) {
        
        float p1x = triangles[i].getP1().getX() * scale;
        float p2x = triangles[i].getP2().getX() * scale;
        float p3x = triangles[i].getP3().getX() * scale;

        float p1y = triangles[i].getP1().getY() * scale;
        float p2y = triangles[i].getP2().getY() * scale;
        float p3y = triangles[i].getP3().getY() * scale;
        
        triangles[i].setP1(p1x, p1y);
        triangles[i].setP2(p2x, p2y);
        triangles[i].setP3(p3x, p3y);
    }
}

vector<Triangle>Mesh::getTriangles() {
    return triangles;
}

void Mesh::shift(float shiftx, float shifty) {
    for(int i=0; i< triangles.size(); i++) {
        
        float p1x = triangles[i].getP1().getX() + shiftx;
        float p2x = triangles[i].getP2().getX() + shiftx;
        float p3x = triangles[i].getP3().getX() + shiftx;

        float p1y = triangles[i].getP1().getY() + shifty;
        float p2y = triangles[i].getP2().getY() + shifty;
        float p3y = triangles[i].getP3().getY() + shifty;

        triangles[i].setP1(p1x, p1y);
        triangles[i].setP2(p2x, p2y);
        triangles[i].setP3(p3x, p3y);
    }
}


float *Mesh::getBox() {
    float *ret = new float[4];
    float min_x = -1, max_x = -1, min_y = -1, max_y = -1;

    for(int i=0; i< triangles.size(); i++) {
        // triangles[i].toString();
        float *t = triangles[i].getXBounds();
        float *r = triangles[i].getYBounds();

        if(min_x == -1 || t[0] < min_x) {
            min_x = t[0];
        }

        if(max_x == -1 || t[1] > max_x) {
            max_x = t[1];
        }

        if(min_y == -1 || r[0] < min_y) {
            min_y = r[0];
        }

        if(max_y == -1 || r[1] > max_y) {
            max_y = r[1];
        }
    }
    ret[0] = min_x;
    ret[1] = max_x;
    ret[2] = min_y;
    ret[3] = max_y;

    return ret;
}

