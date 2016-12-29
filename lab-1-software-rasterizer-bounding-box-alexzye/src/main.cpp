#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "Triangle.h"
#include "Vertex.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int main(int argc, char **argv)
{
	if(argc < 4) {
		cout << "Usage: L01 filename width height" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	// Triangle coordinates
	Vertex vertex[3];
	int idx=0;
	
	for(int i=4; i<argc-1; i+=2) {
		vertex[idx++] = Vertex(atoi(argv[i]), atoi(argv[i+1]));
	}

	Triangle t = Triangle(vertex[0], vertex[1], vertex[2]);
	int *bBox = t.getBoundingBox();

	

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

	// Draw a rectangle/bounding box
	for(int y = bBox[2]; y <= bBox[3]; ++y) {
		for(int x = bBox[0]; x <= bBox[1]; ++x) {
			if(!(x%2)) {
				unsigned char r = 255;
				unsigned char g = 0;
				unsigned char b = 0;
				image->setPixel(x, y, r, g, b);	
			} else {
				
				unsigned char r = 0;
				unsigned char g = 255;
				unsigned char b = 0;
				image->setPixel(x, y, r, g, b);
			}			
		}
	}
	// Draw triangle
	Vertex *vertices = t.getVertices();
	for(int i=0; i<3; i++) {
		image->setPixel(vertices[i].getX(), vertices[i].getY(), 255, 255, 255);
	}


	// Write image to file
	image->writeToFile(filename);
	return 0;
}
