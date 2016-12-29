#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "Triangle.h"
#include "Vertex.h"

using namespace std;

Triangle::Triangle(Vertex p1, Vertex p2, Vertex p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Vertex *Triangle::getVertices() {
    Vertex *ret = new Vertex[3];
    ret[0] = this->p1;
    ret[1] = this->p2;
    ret[2] = this->p3;
    
    return ret;
}

float bary(float a, float b, float c, float d) {
   return (a * d) - (b * c);
}

float *Triangle::getCoords(int x, int y) {
    float area = 0.5 * bary(this->p3.getX() - this->p1.getX(), this->p2.getX() - this->p1.getX(), this->p3.getY() - this->p1.getY(), this->p2.getY() - this->p1.getY());
    float gamma = -0.5 * bary(this->p2.getX() - this->p1.getX(), x - this->p1.getX(), this->p2.getY() - this->p1.getY(), y - this->p1.getY()) / area;
    float beta = -0.5 * bary(this->p1.getX() - this->p3.getX(), x - this->p3.getX(), this->p1.getY() - this->p3.getY(), y - this->p3.getY()) / area;
    float alpha = 1. - beta - gamma;
    
    float *bary = new float[3];

    // cout << depth << endl;
    bary[0] = alpha;
    bary[1] = beta;
    bary[2] = gamma;
    // bary[3] = depth;

    return bary;
}

float *Triangle::getBoundingBox() {
    float *bounds = new float[4];

    bounds[0] = min({this->p1.getX(), this->p2.getX(), this->p3.getX()});
    bounds[1] = max({this->p1.getX(), this->p2.getX(), this->p3.getX()});
    bounds[2] = min({this->p1.getY(), this->p2.getY(), this->p3.getY()});
    bounds[3] = max({this->p1.getY(), this->p2.getY(), this->p3.getY()});

    return bounds;
}

float *Triangle::getZBounds() {
    float *bounds = new float[2];
    bounds[0] = min({p1.getZ(), p2.getZ(), p3.getZ()});
    bounds[1] = max({p1.getZ(), p2.getZ(), p3.getZ()});

    return bounds;
}

float *Triangle::getXBounds() {
    float *bounds = new float[2];

    bounds[0] = min({this->p1.getX(), this->p2.getX(), this->p3.getX()});
    bounds[1] = max({this->p1.getX(), this->p2.getX(), this->p3.getX()});

    return bounds;
}

float *Triangle::getYBounds() {
    float *bounds = new float[2];

    bounds[0] = min({this->p1.getY(), this->p2.getY(), this->p3.getY()});
    bounds[1] = max({this->p1.getY(), this->p2.getY(), this->p3.getY()});

    return bounds;
}

void Triangle::toString() {
    cout << this->p1.getX() << " " << this->p1.getY() << " " << this->p1.getZ() << endl;
    cout << this->p2.getX() << " " << this->p2.getY() << " " << this->p2.getZ() << endl;
    cout << this->p3.getX() << " " << this->p3.getY() << " " << this->p3.getZ() << endl;
}



