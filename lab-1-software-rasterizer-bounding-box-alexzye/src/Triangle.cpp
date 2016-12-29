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

int *Triangle::getBoundingBox() {
    int *bounds = new int[4];
    
    if(this->p1.getX() < min(this->p2.getX(), this->p3.getX())) {
        bounds[0] = p1.getX();
    } else {
        bounds[0] = min(this->p2.getX(), this->p3.getX());
    }

    if(this->p1.getX() > max(this->p2.getX(), this->p3.getX())) {
        bounds[1] = p1.getX();
    } else {
        bounds[1] = max(this->p2.getX(), this->p3.getX());
    }

    if(this->p1.getY() < min(this->p2.getY(), this->p3.getY())) {
        bounds[2] = p1.getY();
    } else {
        bounds[2] = min(this->p2.getY(), this->p3.getY());
    }

    if(this->p1.getY() > max(this->p2.getY(), this->p3.getY())) {
        bounds[3] = p1.getY();
    } else {
        bounds[3] = max(this->p2.getY(), this->p3.getY());
    }

    //cout << bounds[0] << " " << bounds[1] << " " << bounds[2] << " " << bounds[3];
    return bounds;
}