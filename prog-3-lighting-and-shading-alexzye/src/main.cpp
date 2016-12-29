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
string INPUT_OBJ = "";
shared_ptr<Program> gouraud;
shared_ptr<Program> normal;
shared_ptr<Program> phong;
shared_ptr<Program> border;
shared_ptr<Program> current_prog;
int current_index = 0;
shared_ptr<Shape> shape;

int g_width, g_height;
float angle = 0.0f;
float light = -2.0f;

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
  if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
    // glfwSetWindowShouldClose(window, GL_TRUE);
    cout << "Q pressed." << endl;
    light -= 1.0f;
  }
  if(key == GLFW_KEY_E && action == GLFW_PRESS) {
    //glfwSetWindowShouldClose(window, GL_TRUE);
    cout << "E pressed." << endl;
    light += 1.0f;
  }
  if(key == GLFW_KEY_P && action == GLFW_PRESS) {
    //glfwSetWindowShouldClose(window, GL_TRUE);
    cout << "P pressed." << endl;
    current_prog->unbind();
    if(current_index == 0) {
      cout << "Gouraud Mode" << endl;
      current_prog = gouraud;
      current_index = 1;
    } else if(current_index == 1) {
      cout << "Phong Mode" << endl;
      current_prog = phong;
      current_index = 2;
    } else if(current_index == 2) {
      cout << "Silhouette Mode" << endl;
      current_prog = border;
      current_index = 3;
    } else if(current_index == 3) {
      cout << "Normal Interpolation Mode" << endl;
      current_prog = normal;
      current_index = 0;
    }
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


static void init()
{
  GLSL::checkVersion();

  // Set background color.
  glClearColor(0.02f, 0.01f, 0.38f, 1.0f);
  // Enable z-buffer test.
  glEnable(GL_DEPTH_TEST);

  // Initialize mesh.
  shape = make_shared<Shape>();
  shape->loadMesh(RESOURCE_DIR + INPUT_OBJ);
  shape->resize();
  shape->init();

  // Initialize the GLSL program.
  gouraud = make_shared<Program>();
  gouraud->setVerbose(true);
  gouraud->setShaderNames(RESOURCE_DIR + "gouraud_vert.glsl", RESOURCE_DIR + "gouraud_frag.glsl");
  gouraud->init();
  gouraud->addUniform("P");
  gouraud->addUniform("MV");
  gouraud->addAttribute("vertPos");
  gouraud->addAttribute("vertNor");
  gouraud->addUniform("light");

  // Initialize the GLSL program.
  normal = make_shared<Program>();
  normal->setVerbose(true);
  normal->setShaderNames(RESOURCE_DIR + "normal_vert.glsl", RESOURCE_DIR + "normal_frag.glsl");
  normal->init();
  normal->addUniform("P");
  normal->addUniform("MV");
  normal->addAttribute("vertPos");
  normal->addAttribute("vertNor");
  normal->addUniform("light");

  phong = make_shared<Program>();
  phong->setVerbose(true);
  phong->setShaderNames(RESOURCE_DIR + "phong_vert.glsl", RESOURCE_DIR + "phong_frag.glsl");
  phong->init();
  phong->addUniform("P");
  phong->addUniform("MV");
  phong->addAttribute("vertPos");
  phong->addAttribute("vertNor");
  phong->addUniform("light");

  border = make_shared<Program>();
  border->setVerbose(true);
  border->setShaderNames(RESOURCE_DIR + "border_vert.glsl", RESOURCE_DIR + "border_frag.glsl");
  border->init();
  border->addUniform("P");
  border->addUniform("MV");
  border->addAttribute("vertPos");
  border->addAttribute("vertNor");
  border->addUniform("light");
  

  current_prog = normal;
}

static void render()
{
  //local modelview matrix use this for lab 5
    float MV[16] = {0};
    float P[16] = {0};
    float T[16] = {0};
    float T2[16] = {0};
    float S[16] = {0};
    float temp[16] = {0};
    float temp2[16] = {0};
    float temp3[16] = {0};
    float R[15] = {0};
    float RW[15] = {0};

  // Get current frame buffer size.
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Clear framebuffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     //Use the local matrices for lab 5
    float aspect = width/(float)height;
    
    createRotateMatY(RW, angle);

    current_prog->bind();

    createPerspectiveMat(P, 70.0f, aspect, 0.1, 100.0f);
    createTranslateMat(T, 0.0f, 0.0f, -5.0f);
    createTranslateMat(T2, -1.1f, 0.0f, 0.0f);
    createScaleMat(S, 1.0f, 1.0f, 1.0f);
    multMat(temp, T, RW);
    multMat(temp2, temp, T2);
    multMat(MV, temp2, S);
    
    glUniformMatrix4fv(current_prog->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(current_prog->getUniform("MV"), 1, GL_FALSE, MV);
    glUniform1f(current_prog->getUniform("light"), light);
    
    shape->draw(current_prog);
    fill(temp, temp + sizeof(temp), 0);
    fill(temp2, temp2 + sizeof(temp2), 0);
    

    current_prog->unbind();



    current_prog->bind();

    
    
    createTranslateMat(T, 0.0f, 0.0f, -5.0f);
    createTranslateMat(T2, 1.1f, 0.0f, 0.0f);
    createScaleMat(S, 1.0f, 1.0f, 1.0f);
    createRotateMatY(R, 0.4f);
    multMat(temp, T, R);
    multMat(temp2, temp, RW);
    multMat(temp3, temp2, T2);
    multMat(MV, temp3, S);

    // multMat(temp, T, RW);
    // multMat(temp2, temp, T2);
    // multMat(MV, temp2, S);
    
    glUniformMatrix4fv(current_prog->getUniform("P"), 1, GL_FALSE, P);
    glUniformMatrix4fv(current_prog->getUniform("MV"), 1, GL_FALSE, MV);
    glUniform1f(current_prog->getUniform("light"), light);
    shape->draw(current_prog);

    current_prog->unbind();
}

int main(int argc, char **argv)
{
  if(argc < 3) {
    cout << "Please specify the resource directory and obj." << endl;
    return 0;
  }
  RESOURCE_DIR = argv[1] + string("/");
  INPUT_OBJ = argv[2];

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
