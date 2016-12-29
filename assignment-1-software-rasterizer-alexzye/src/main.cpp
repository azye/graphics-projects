/* Release code for program 1 CPE 471 Fall 2016 */

#include <iostream>
#include <string>
#include <vector>
#include "Triangle.h"
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

float g_width, g_height;
int color_mode;

/*
   Helper function you will want all quarter
   Given a vector of shapes which has already been read from an obj file
   resize all vertices to the range [-1, 1]
 */
void resize_obj(std::vector<tinyobj::shape_t> &shapes){
   float minX, minY, minZ;
   float maxX, maxY, maxZ;
   float scaleX, scaleY, scaleZ;
   float shiftX, shiftY, shiftZ;
   float epsilon = 0.001;

   minX = minY = minZ = 1.1754E+38F;
   maxX = maxY = maxZ = -1.1754E+38F;

   //Go through all vertices to determine min and max of each dimension
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
         if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];

         if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
         if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];

         if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
         if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
      }
   }

	//From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX-minX;
   yExtent = maxY-minY;
   zExtent = maxZ-minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
      maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
      maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
      maxExtent = zExtent;
   }
   scaleX = 2.0 /maxExtent;
   shiftX = minX + (xExtent/ 2.0);
   scaleY = 2.0 / maxExtent;
   shiftY = minY + (yExtent / 2.0);
   scaleZ = 2.0/ maxExtent;
   shiftZ = minZ + (zExtent)/2.0;

   //Go through all verticies shift and scale them
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
         assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
         assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
         assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
      }
   }
}

int main(int argc, char **argv)
{
	if(argc < 5) {
      cout << "Usage: Assignment1 meshfile imagefile" << endl;
      return 0;
   }


   std::string arg(argv[1]);
   std::size_t found = arg.find("obj");

   if(found == std::string::npos) {
      cout << "No file found" << endl;
      cout << "Usage: Assignment1 meshfile imagefile" << endl;
      exit(EXIT_FAILURE);
   }
	// OBJ filename
	string meshName(argv[1]);
	string imgName(argv[2]);

	//set g_width and g_height appropriately!
	g_width = stod(argv[3]);
   g_height = stod(argv[4]);
   color_mode = atoi(argv[5]);

   if(color_mode != 1 && color_mode != 2) {
      cout << "Invalid color mode" << endl;
      exit(EXIT_FAILURE);
   }

   //create an image
	auto image = make_shared<Image>(g_width, g_height);

	// triangle buffer
	vector<unsigned int> triBuf;
	// position buffer
	vector<float> posBuf;
	// Some obj files contain material information.
	// We'll ignore them for this assignment.
	vector<tinyobj::shape_t> shapes; // geometry
	vector<tinyobj::material_t> objMaterials; // material
	string errStr;
	
   bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());

	/* error checking on read */
	if(!rc) {
		cerr << errStr << endl;
	} else {
		posBuf = shapes[0].mesh.positions;
		triBuf = shapes[0].mesh.indices;
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;
	cout << "Number of triangles: " << triBuf.size()/3 << endl; 
   resize_obj(shapes);

   vector<Vertex> verts;

   for(int i = 0; i <= posBuf.size(); i+=3) {
      Vertex v = Vertex(posBuf[i],posBuf[i+1], posBuf[i+2], 0, 0, 0);
      verts.push_back(v);
   }

   vector<Triangle> triangles;


   for(int i=0; i<triBuf.size(); i+=3) {
      Triangle t = Triangle(verts[triBuf[i]], verts[triBuf[i+1]], verts[triBuf[i+2]]);
      triangles.push_back(t);
   }

   Mesh mesh = Mesh(triangles);
   float *box = mesh.getBox();

   mesh.shift(-box[0], -box[2]);

   int scale = 0;

   if(g_height < g_width) {
      scale = 1;
      mesh.scale(g_height/(box[3] - box[2]));
   } else {
      mesh.scale(g_width/(box[1] - box[0]));

   }

   box = mesh.getBox();
   if(scale == 1) {
      float h = g_width / 2;
      float b = (box[1]-box[0])/2;
      mesh.shift(h - b, 0);
   } else {
      
      float w = g_height / 2;
      float f = (box[3]-box[2])/2;
      mesh.shift(0, w - f);
   }

   vector<vector<float>> zBuf;
   zBuf.resize(g_height);

   for(int i = 0; i < g_height; i++) {
      zBuf[i].resize(g_width);
   }

   for(int i = 0; i < g_height; i++) {
      for(int j=0; j< g_width; j++) {
         
      }
   }

   float ydist = box[3] - box[2];

   float max = mesh.normalize();
   vector<Triangle> tria = mesh.getTriangles();
   
   for(int i = 0; i < tria.size(); i++) {
      Triangle tri = tria[i];
      
      float *bBox = tri.getBoundingBox();
      
      for(int y = bBox[2]; y < bBox[3]; ++y) {
         for(int x = bBox[0]; x < bBox[1]; ++x) {
            float *coords = tri.getCoords(x, y);
            float alpha = coords[0], beta = coords[1], gamma = coords[2];
            
            if(alpha >= 0 && beta >= 0 && gamma >= 0) {
               // z interpolation
               if(color_mode == 1) {
                  float t_area = alpha + beta + gamma;
                  alpha /= t_area;
                  beta /= t_area;
                  gamma /= t_area;
                  
                  float depth = (alpha * tri.getP1().getZ() + 
                     beta * tri.getP2().getZ() + gamma * tri.getP3().getZ());   

                  if(depth > zBuf[y][x]) {
                     image->setPixel(x, y, depth * (170/max), 0, 0);
                     zBuf[y][x] = depth;
                  }
               }
               // linear interpolation
               if(color_mode == 2) {                  
                  float r = (0-255) * ((y-box[2])/ydist) + 255;
                  float g = (255-0) * ((y-box[2])/ydist) + 0;
                  float b = (0-0) * ((y-box[2])/ydist) + 0;

                  image->setPixel(x, y, r, g, b);
               }
            }
         }
      }
   }
   
	//write out the image
   image->writeToFile(imgName);

	return 0;
}
