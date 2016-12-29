#include <iostream>
#include "Vertex.h"

using namespace std;

Vertex::Vertex (int x, int y) {
    this->x = x;
    this->y = y;
}

int Vertex::getX() {
    return x;
}

int Vertex::getY() {
    return y;
}

void Vertex::toString() {
    cout << (this->x);
    cout << " ";
    cout << this->y;
}


