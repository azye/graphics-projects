/* Lab 6 base code - transforms using matrix stack built on glm 
	CPE 471 Cal Poly Z. Wood + S. Sueda
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog;
shared_ptr<Program> snowman;
shared_ptr<Program> feat;
shared_ptr<Program> ground;
shared_ptr<Shape> shape;
shared_ptr<Shape> sphere;
static float translation_data[3 * 15];

const int OBJ_NUM = 10;
int g_width, g_height;
float sTheta;

double posX, posY;
int width, height;


glm::vec3 position = glm::vec3(0, 0, 6);

float camera_yaw = M_PI;
float camera_pitch = 0.0f;

glm::vec3 direction;

float RandomFloat(float min, float max) {
  float r = (float)rand() / (float)RAND_MAX;
  return min + r * (max - min);
}

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void resize_callback(GLFWwindow *window, int width, int height) {
    g_width = width;
    g_height = height;
    glViewport(0, 0, width, height);
}

static void init()
{
	GLSL::checkVersion();

    for(int i = 0; i < OBJ_NUM * 3; i+=3) {
        translation_data[i] = RandomFloat(-20.0, 20.0);
        translation_data[i+1] = 0.0f;
        translation_data[i+2] = RandomFloat(-20.0, 20.0);
    }

	sTheta = 0;
	// Set background color.
	glClearColor(1.0f, 1.0f, 1.2f, 0.6f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "bunny.obj");
	shape->resize();
	shape->init();

    sphere = make_shared<Shape>();
    sphere->loadMesh(RESOURCE_DIR + "sphere.obj");
    sphere->resize();
    sphere->init();

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog->init();
	prog->addUniform("M");
    prog->addUniform("V");
    prog->addUniform("P");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");

    // Snowman
    snowman = make_shared<Program>();
    snowman->setVerbose(true);
    snowman->setShaderNames(RESOURCE_DIR + "snowman_vert.glsl", RESOURCE_DIR + "snowman_frag.glsl");
    snowman->init();
    snowman->addUniform("P");
    snowman->addUniform("V");
    snowman->addUniform("M");
    snowman->addAttribute("vertPos");
    snowman->addAttribute("vertNor");

    // Create program for snowman features
    feat = make_shared<Program>();
    feat->setVerbose(true);
    feat->setShaderNames(RESOURCE_DIR + "features_vert.glsl", RESOURCE_DIR + "features_frag.glsl");
    feat->init();
    feat->addUniform("P");
    feat->addUniform("V");
    feat->addUniform("M");
    feat->addAttribute("vertPos");
    feat->addAttribute("vertNor");

    ground = make_shared<Program>();
    ground->setVerbose(true);
    ground->setShaderNames(RESOURCE_DIR + "ground_vert.glsl", RESOURCE_DIR + "ground_frag.glsl");
    ground->init();
    ground->addUniform("M");
    ground->addUniform("V");
    ground->addUniform("P");
    ground->addAttribute("vertPos");
    ground->addAttribute("vertNor");
}


static void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    float aspect = width/(float)height;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, width/2, height/2);

    camera_yaw += 0.0005f * float(width/2 - xpos);
    camera_pitch += 0.0005f * float(height/2 - ypos);

    direction = glm::vec3(
        cos(camera_pitch) * sin(camera_yaw), 
        sin(camera_pitch),
        cos(camera_pitch) * cos(camera_yaw)
    );

    if(camera_pitch >= 1.39626f) {
        camera_pitch = 1.39626f;
    } else if(camera_pitch <= -1.39626f) {
        camera_pitch = -1.39626f;
    }

    glm::vec3 turn = glm::vec3(sin(camera_yaw - M_PI/2.0f), 0, cos(camera_yaw - M_PI/2.0f));
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        position += (direction * 3.0f)/50.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        position -= (direction * 3.0f)/50.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position += turn * 3.0f/50.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position -= turn * 3.0f/50.0f;
    }
    glm::mat4 P = glm::perspective(0.785398f, aspect, 0.1f, 100.0f);
    glm::mat4 V = glm::lookAt(position, position+direction, glm::vec3(0,1,0));
    glm::mat4 M = glm::mat4(1.0);
    glm::mat4 trans;
    glm::mat4 scale;
    ground->bind();

    trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    0.0f,
                    -1.0f,
                    0.0f
                )
            );

    scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                100.0f, 
                0.001f, 
                100.0f
            )
        );

    M = glm::mat4(1.0) * trans * scale;
    glUniformMatrix4fv(ground->getUniform("M"), 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(ground->getUniform("V"), 1, GL_FALSE, &V[0][0]);
    glUniformMatrix4fv(ground->getUniform("P"), 1, GL_FALSE, &P[0][0]);

    sphere->draw(ground);
   


    ground->unbind();


    // translation_data
    for(int i = 0; i<OBJ_NUM * 3; i+= 3) {
        prog->bind();
        
        glm::mat4 translate = glm::translate(
            glm::mat4(1.f), 
            glm::vec3(
                translation_data[i], 
                translation_data[i+1], 
                translation_data[i+2]
            )
        );

        M = glm::mat4(1.0) * translate;
        
        glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        shape->draw(prog);
        
        prog->unbind();
    

        snowman->bind();
        // Draw the snowman
        // Top circle
        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2], 
                    -0.2f,
                    translation_data[i]
                )
        );

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.75f, 
                0.75f, 
                0.75f
            )
        );

        M = glm::mat4(1.0) * trans * scale;
        glUniformMatrix4fv(snowman->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(snowman->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(snowman->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(snowman);

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.6f, 
                0.6f, 
                0.6f
            )
        );

        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2],  
                    0.6f,
                    translation_data[i]
                )
        );

        M = glm::mat4(1.0) * trans * scale;
        glUniformMatrix4fv(snowman->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(snowman->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(snowman->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(snowman);

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.4f, 
                0.4f, 
                0.4f
            )
        );

        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2],  
                    1.4f,
                    translation_data[i]
                )
        );

        M = glm::mat4(1.0) * trans * scale;
        glUniformMatrix4fv(snowman->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(snowman->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(snowman->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(snowman);

        snowman->unbind();
        

        feat->bind();


        // Arms
        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2], 
                    0.6f,
                    translation_data[i] 
                )
        );

        glm::mat4 trans2 = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    -0.8, 
                    0.0f,
                    0.0f
                )
        );

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.5f, 
                0.02f, 
                0.02f
            )
        );

        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 3.14f/1.5f, glm::vec3(0.0,0.0,1.0));

        M = glm::mat4(1.0) * trans * trans2 * scale * rotate;
        glUniformMatrix4fv(feat->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(feat->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(feat);

        trans2 = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    0.8, 
                    0.0f,
                    0.0f
                )
        );

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.5f, 
                0.02f, 
                0.02f
            )
        );

        rotate = glm::rotate(glm::mat4(1.0f), 3.14f/1.5f, glm::vec3(0.0,0.0,1.0));

        M = glm::mat4(1.0) * trans * trans2 * scale * rotate;
        glUniformMatrix4fv(feat->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(feat->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(feat);

        // // Eyes

        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2],  
                    1.5f,
                    translation_data[i] 
                )
        );

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.05f, 
                0.05f, 
                0.05f
            )
        );

        trans2 = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    0.25f, 
                    0.0f,
                    0.25f
                )
        );

        M = glm::mat4(1.0) * trans * trans2 * scale;
        glUniformMatrix4fv(feat->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(feat->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(feat);


        trans = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    translation_data[i+2],  
                    1.5f,
                    translation_data[i]
                )
        );

        scale = glm::scale(
            glm::mat4(1.f),
            glm::vec3(
                0.05f, 
                0.05f, 
                0.05f
            )
        );

        trans2 = glm::translate(
                glm::mat4(1.f), 
                glm::vec3(
                    -0.25f, 
                    0.0f,
                    0.25f
                )
        );

        M = glm::mat4(1.0) * trans * trans2 * scale;
        glUniformMatrix4fv(feat->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(feat->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(feat->getUniform("P"), 1, GL_FALSE, &P[0][0]);

        sphere->draw(feat);

        feat->unbind();
        }
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
	window = glfwCreateWindow(1024, 768, "ALEX YE", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);


    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	// glfwSetKeyCallback(window, key_callback);
    //set the mouse call back
    // glfwSetMouseButtonCallback(window, mouse_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
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
