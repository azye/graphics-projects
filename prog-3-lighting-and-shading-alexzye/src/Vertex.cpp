#include <iostream>
#include "Vertex.h"

using namespace std;

Vertex::Vertex (float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    // this->r = r;
    // this->g = g;
    // this->b = b;
}

// void Vertex::setX(float val) {
//     this->x = val;
// }

// void Vertex::setY(float val) {
//     this->y = val;
// }

// void Vertex::setZ(float val) {
//     this->z = val;
// }

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

float Vertex::getZ() {
    return z;
}

// int Vertex::getR() {
//     return r;
// }

// int Vertex::getG() {
//     return g;
// }

// int Vertex::getB() {
//     return b;
// }

// void Vertex::toString() {
//     cout << x << " " << y << " " << z << endl;
// }