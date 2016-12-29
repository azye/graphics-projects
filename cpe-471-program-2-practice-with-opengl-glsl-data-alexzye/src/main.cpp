/* Lab 5 base code - transforms using local matrix functions 
   to be written by students - 
	CPE 471 Cal Poly Z. Wood + S. Sueda
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

using namespace std;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Shape> shape;
shared_ptr<Program> prog;
shared_ptr<Program> feat;
shared_ptr<Program> globe;
shared_ptr<Program> snow;


static float translation_data[3 * 15];

int g_width, g_height;
float angle = 0;

void printMat(float *A, const char *name = 0)
{
   // OpenGL uses col-major ordering:
   // [ 0  4  8 12]
   // [ 1  5  9 13]
   // [ 2  6 10 14]
   // [ 3  7 11 15]
   // The (i,j)th element is A[i+4*j].
   if(name) {
      printf("%s=[\n", name);
   }
   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
         printf("%- 5.2f ", A[i+4*j]);
      }
      printf("\n");
   }
   if(name) {
      printf("];");
   }
   printf("\n");
}

void createIdentityMat(float *M)
{
	//set all values to zero
   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
			M[i*4+j] = 0;
		}
	}
	//overwrite diagonal with 1s
	M[0] = M[5] = M[10] = M[15] = 1;
}

void createTranslateMat(float *T, float x, float y, float z)
{
    // (0 4 1 5 08 12 09 13 2 6 3 7 10 14 11 15 )
    T[0] = 1.0f;
    T[1] = 0.0f;
    T[2] = 0.0f;
    T[3] = 0.0f;
    T[4] = 0.0f;
    T[5] = 1.0f;
    T[6] = 0.0f;
    T[7] = 0.0f;
    T[8] = 0.0f;
    T[9] = 0.0f;
    T[10] = 1.0f;
    T[11] = 0.0f;
    T[12] = x;
    T[13] = y;
    T[14] = z;
    T[15] = 1.0f;
    // printMat(T, "T");
}


void createScaleMat(float *S, float x, float y, float z)
{
   // IMPLEMENT ME
    S[0] = x;
    S[1] = 0.0f;
    S[2] = 0.0f;
    S[3] = 0.0f;
    S[4] = 0.0f;
    S[5] = y;
    S[6] = 0.0f;
    S[7] = 0.0f;
    S[8] = 0.0f;
    S[9] = 0.0f;
    S[10] = z;
    S[11] = 0.0f;
    S[12] = 0.0f;
    S[13] = 0.0f;
    S[14] = 0.0f;
    S[15] = 1.0f;
    // printMat(S, "S");
}

void createRotateMatX(float *R, float radians)
{ 
   // IMPLEMENT ME
    R[0] = 1.0f;
    R[1] = 0.0f;
    R[2] = 0.0f;
    R[3] = 0.0f;
    R[4] = 0.0f;
    R[5] = cos(radians);
    R[6] = sin(radians);
    R[7] = 0.0f;
    R[8] = 0.0f;
    R[9] = -sin(radians);
    R[10] = cos(radians);
    R[11] = 0.0f;
    R[12] = 0.0f;
    R[13] = 0.0f;
    R[14] = 0.0f;
    R[15] = 1.0f;
}

void createRotateMatY(float *R, float radians)
{
    R[0] = cos(radians);
    R[1] = 0.0f;
    R[2] = -sin(radians);
    R[3] = 0.0f;
    R[4] = 0.0f;
    R[5] = 1.0f;
    R[6] = 0.0f;
    R[7] = 0.0f;
    R[8] = sin(radians);
    R[9] = 0.0f;
    R[10] = cos(radians);
    R[11] = 0.0f;
    R[12] = 0.0f;
    R[13] = 0.0f;
    R[14] = 0.0f;
    R[15] = 1.0f;
    // printMat(R, "R");
}

void createRotateMatZ(float *R, float radians)
{
    R[0] = cos(radians);
    R[1] = sin(radians);
    R[2] = 0.0f;
    R[3] = 0.0f;
    R[4] = -sin(radians);
    R[5] = cos(radians);
    R[6] = 0.0f;
    R[7] = 0.0f;
    R[8] = 0.0f;
    R[9] = 0.0f;
    R[10] = 1.0f;
    R[11] = 0.0f;
    R[12] = 0.0f;
    R[13] = 0.0f;
    R[14] = 0.0f;
    R[15] = 1.0f;
}

void multMat(float *C, const float *A, const float *B)
{
   float c = 0;
   for(int k = 0; k < 4; ++k) {
      // Process kth column of C
      for(int i = 0; i < 4; ++i) {
         // Process ith row of C.
         // The (i,k)th element of C is the dot product
         // of the ith row of A and kth col of B.
         c = 0;
         //vector dot
         for(int j = 0; j < 4; ++j) {
            // IMPLEMENT ME
            c += A[i+4*j] * B[j+4*k];
         }
         C[i+4*k] = c;
      }
   }
}

void createPerspectiveMat(float *m, float fovy, float aspect, float zNear, float zFar)
{
   // http://www-01.ibm.com/support/knowledgecenter/ssw_aix_61/com.ibm.aix.opengl/doc/openglrf/gluPerspective.htm%23b5c8872587rree
   float f = 1.0f/tan(0.5f*fovy);
   m[ 0] = f/aspect;
   m[ 1] = 0.0f;
   m[ 2] = 0.0f;
   m[ 3] = 0.0f;
   m[ 4] = 0;
   m[ 5] = f;
   m[ 6] = 0.0f;
   m[ 7] = 0.0f;
   m[ 8] = 0.0f;
   m[ 9] = 0.0f;
   m[10] = (zFar + zNear)/(zNear - zFar);
   m[11] = -1.0f;
   m[12] = 0.0f;
   m[13] = 0.0f;
   m[14] = 2.0f*zFar*zNear/(zNear - zFar);
   m[15] = 0.0f;
}

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_A && action == GLFW_PRESS) {
		// glfwSetWindowShouldClose(window, GL_TRUE);
    cout << "A pressed." << endl;
    angle += 0.2f;
	}
  if(key == GLFW_KEY_D && action == GLFW_PRESS) {
    //glfwSetWindowShouldClose(window, GL_TRUE);
    cout << "D pressed." << endl;
    angle -= 0.2f;
  }
}


static void mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
   double posX, posY;
   if (action == GLFW_PRESS) {
      glfwGetCursorPos(window, &posX, &posY);
      cout << "Pos X " << posX <<  " Pos Y " << posY << endl;
	}
}

static void resize_callback(GLFWwindow *window, int width, int height) {
   g_width = width;
   g_height = height;
   glViewport(0, 0, width, height);
}

float RandomFloat(float min, float max) {
  float r = (float)rand() / (float)RAND_MAX;
  return min + r * (max - min);
}

static void init() {
	GLSL::checkVersion();

  for(int i = 0; i < 15 * 3; i+=3) {
    translation_data[i] = RandomFloat(-1.0, 1.0);
    translation_data[i+1] = RandomFloat(-1.5, 1.5);
    translation_data[i+2] = RandomFloat(0.9, 1.2);
  }
	// Set background color.
	glClearColor(0.5529f, 0.5529f, 0.7647f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "sphere.obj");
	shape->resize();
	shape->init();

	// Initialize the GLSL program for snowman.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "snowman_vert.glsl", RESOURCE_DIR + "snowman_frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");

  // Create program for snowman features
  feat = make_shared<Program>();
  feat->setVerbose(true);
  feat->setShaderNames(RESOURCE_DIR + "features_vert.glsl", RESOURCE_DIR + "features_frag.glsl");
  feat->init();
  feat->addUniform("P");
  feat->addUniform("MV");
  feat->addAttribute("vertPos");
  feat->addAttribute("vertNor");

  // Create program for globe 
  globe = make_shared<Program>();
  globe->setVerbose(true);
  globe->setShaderNames(RESOURCE_DIR + "globe_vert.glsl", RESOURCE_DIR + "globe_frag.glsl");
  globe->init();
  globe->addUniform("P");
  globe->addUniform("MV");
  globe->addAttribute("vertPos");
  globe->addAttribute("vertNor");

  // Create program for snow
  snow = make_shared<Program>();
  snow->setVerbose(true);
  snow->setShaderNames(RESOURCE_DIR + "snow_vert.glsl", RESOURCE_DIR + "snow_frag.glsl");
  snow->init();
  snow->addUniform("P");
  snow->addUniform("MV");
  snow->addUniform("Time");
  snow->addAttribute("vertPos");
  snow->addAttribute("vertNor");
}



static void render()
{
	//local modelview matrix use this for lab 5
    float MV[16] = {0};
	  float P[16] = {0};
    float S[16] = {0};
    float T[16] = {0};
    float T2[16] = {0};
    float R[16] = {0};
    float temp[16] = {0};
    float temp2[16] = {0};
    float temp3[16] = {0};
    
    float GR[16] = {0};
    
	// Get current frame buffer size.
  	int width, height;
  	glfwGetFramebufferSize(window, &width, &height);
  	glViewport(0, 0, width, height);

  	// Clear framebuffer.
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  //Use the local matrices for lab 5
    float aspect = width/(float)height;
    createPerspectiveMat(P, 70.0f, aspect, 0.1, 100.0f);
    createRotateMatY(GR, angle);
    // Draw the snowman
    prog->bind();
    
    // Top circle
    createScaleMat(S, 1.0f, 1.0f, 1.0f);
    createTranslateMat(T, 0.0f, -1.0f, -5.0f);
    multMat(temp, T, GR);
    multMat(MV, temp, S);
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
	  glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
  	shape->draw(prog);
    fill(temp, temp + sizeof(temp), 0);
    
    // Middle circle
    createScaleMat(S, 0.75f, 0.75f, 0.75f);
    createTranslateMat(T, 0.0f, -0.1f, -5.0f); 
    multMat(temp, T, GR);
    multMat(MV, temp, S);

    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(prog);
    fill(temp, temp + sizeof(temp), 0);

    // Bottom Circle
    createScaleMat(S, 0.6f, 0.6f, 0.6f);
    createTranslateMat(T, 0.0f, 0.8f, -5.0f);
    multMat(temp, T, GR);
    multMat(MV, temp, S);
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(prog);
    fill(temp, temp + sizeof(temp), 0);
    
	  prog->unbind();


    feat->bind();
    // Right arm
    createScaleMat(S, 0.6f, 0.03f, 0.03f);
    createTranslateMat(T, 0.0f, 0.2f, -5.0f);
    createTranslateMat(T2, 1.15f, 0.12f, 0.0f);
    createRotateMatZ(R, 0.3);
    multMat(temp, T, GR);
    multMat(temp2, temp, T2);
    multMat(temp3, temp2, R);
    multMat(MV, temp3, S);
    glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(feat->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(feat);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);
    // Left arm
    createScaleMat(S, 0.6f, 0.03f, 0.03f);
    createTranslateMat(T, 0.0f, 0.0f, -5.0f);
    createTranslateMat(T2, -1.1f, 0.2f, 0.0f);
    multMat(temp, T, GR);
    multMat(temp2, temp, T2);
    multMat(MV, temp2, S);
    glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(feat->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(feat);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);
    // Left eye
    createScaleMat(S, 0.05f, 0.05f, 0.05f);
    createTranslateMat(T, 0.0f, 0.0f, -5.0f);
    createTranslateMat(T2, -0.2f, 1.0f, 0.55f);
    multMat(temp, T, GR);
    multMat(temp2, temp, T2);
    multMat(MV, temp2, S);
    glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(feat->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(feat);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);
    // right eye
    createScaleMat(S, 0.05f, 0.05f, 0.05f);
    createTranslateMat(T, 0.0f, 0.0f, -5.0f);
    createTranslateMat(T2, 0.2f, 1.0f, 0.55f);
    multMat(temp, T, GR);
    multMat(temp2, temp, T2);
    multMat(MV, temp2, S);
    glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(feat->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(feat);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);

    feat->unbind();


    globe->bind();

    createScaleMat(S, 2.0f, 2.0f, 2.0f);
    createTranslateMat(T, 0.0, -0.1, -5.0);
    multMat(MV, T, S);
    glUniformMatrix4fv(globe->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(globe->getUniform("MV"), 1, GL_FALSE, MV);
    shape->draw(globe);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);

    globe->unbind();
    
    snow->bind();
    
    createScaleMat(S, 0.05f, 0.05f, 0.05f);
    
    for(int i = 0; i < 45; i += 3) {
      float t = glfwGetTime();
      createTranslateMat(T, 0.0f, 0.0f, -5.0f);
      createTranslateMat(T2, translation_data[i], 
        translation_data[i+1], 
        translation_data[i+2]);
      
      multMat(temp, T, GR);
      multMat(temp2, temp, T2);
      multMat(MV, temp2, S);
      
      glUniform1f(snow->getUniform("Time"), t);
      glUniformMatrix4fv(snow->getUniform("P"), 1, GL_FALSE, P);
      glUniformMatrix4fv(snow->getUniform("MV"), 1, GL_FALSE, MV);
      shape->draw(snow);
    }
    snow->unbind();
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
   //request the highest possible version of OGL - important for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(1024, 720, "ALEX YE", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	//weird bootstrap of glGetError
    glGetError();
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
   //set the mouse call back
    glfwSetMouseButtonCallback(window, mouse_callback);
   //set the window resize call back
    glfwSetFramebufferSizeCallback(window, resize_callback);

	// Initialize scene. Note geometry initialized in init now
	init();

	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
