#include <iostream>
#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader/shader.hpp"
#include "model/objload.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils/camera.h"
#include "utils/model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

using namespace glm;

#define NB_OBJECTS 10

GLuint tab_textures[NB_OBJECTS] ;

double mousePosX, mousePosY;

GLint ambientIntensityLocation;

vec3 lightColor(1.0f, 1.0f, 1.0f);
GLuint LightClrID ;

vec3 lightPos(7.0f, 1.0f, 15.0f) ;
GLuint LightPosID ;


GLuint TextureID;
GLfloat  YCamera = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 35.0f));
mat4 View = mat4(1.0);
mat4 Projection = mat4(1.0);


Object* car ;
Object* car2 ;

float CarSpeed = 1.0f;

GLfloat currentTime = 0.0f, deltaTime = 0.0f, lastFrame = 0.0f;

void mouse_button(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll (GLFWwindow* window, double xoffset, double yoffset);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void InitTexture( const char* image_path, int width, int height,GLuint tab_textures[], int n);
void LoadTextures();
void bindObj(char* path, int index);
void keyProcess(GLFWwindow *window);
void drawObj(GLuint modelID, Object* obj, int texture_index, GLenum texture);
void driveCar(Object* car, int forward,  int right);
void moveCars(Object* cars[]);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLuint shaderProgramId = LoadShaders("../shader/SimpleVertexShader.vertexshader", "../shader/SimpleFragmentShader.fragmentshader");
    GLuint shadowShaderId = LoadShaders("../shader/shadow.vs", "../shader/shadow.frag");

 ;

    LoadTextures();
//    bindObj("../model/road.obj", 0);

    auto road = new Object("../model/road.obj");
    road->Model = translate(road->Model,vec3(0.0f, 0.0f, -10.0f));
    road->Model = scale(road->Model,vec3(.25f, .25f, .25f)) ;
    road->Model = rotate(road->Model,radians(90.0f),vec3(0.0f,1.0f,0.0f)) ;

    auto road2 = new Object("../model/road.obj");
    road2->Model = translate(road2->Model,vec3(0.0f, 0.0f, -72.0f));
    road2->Model = scale(road2->Model,vec3(.25f, .25f, .25f)) ;
    road2->Model = rotate(road2->Model,radians(90.0f),vec3(0.0f,1.0f,0.0f)) ;


    auto grass = new Object("../model/grass.obj");
    grass->Model = translate(grass->Model,vec3(22.5f, -8.0f, -10.0f));
    grass->Model = rotate(grass->Model,radians(-90.0f),vec3(1.0f,0.0f,0.0f)) ;

    car = new Object("../model/car2.obj");
    car->Model = translate(car->Model,vec3(7.0f, 1.0f, 17.0f));

    car2 = new Object("../model/car2.obj");
    car2->Model = translate(car2->Model,vec3(-3.0f, 1.0f, 17.0f));

    auto wall = new Object("../model/wall.obj");
    wall->Model = translate(wall->Model,vec3(25.0f, 1.0f, 20.0f));
    wall->Model = scale(wall->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wall2 = new Object("../model/wall.obj");
    wall2->Model = translate(wall2->Model,vec3(25.0f, 1.0f, 0.0f));
    wall2->Model = scale(wall2->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wall3 = new Object("../model/wall.obj");
    wall3->Model = translate(wall3->Model,vec3(25.0f, 1.0f, -20.0f));
    wall3->Model = scale(wall3->Model,vec3(10.0f, 10.0f, 1.0f));


    auto wall4 = new Object("../model/wall.obj");
    wall4->Model = translate(wall4->Model,vec3(25.0f, 1.0f, -40.0f));
    wall4->Model = scale(wall4->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wallLeft = new Object("../model/wall.obj");
    wallLeft->Model = translate(wallLeft->Model,vec3(-25.0f, 1.0f, 20.0f));
    wallLeft->Model = scale(wallLeft->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wallLeft2 = new Object("../model/wall.obj");
    wallLeft2->Model = translate(wallLeft2->Model,vec3(-25.0f, 1.0f, 0.0f));
    wallLeft2->Model = scale(wallLeft2->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wallLeft3 = new Object("../model/wall.obj");
    wallLeft3->Model = translate(wallLeft3->Model,vec3(-25.0f, 1.0f, -20.0f));
    wallLeft3->Model = scale(wallLeft3->Model,vec3(10.0f, 10.0f, 1.0f));

    auto wallLeft4 = new Object("../model/wall.obj");
    wallLeft4->Model = translate(wallLeft4->Model,vec3(-25.0f, 1.0f, -40.0f));
    wallLeft4->Model = scale(wallLeft4->Model,vec3(10.0f, 10.0f, 1.0f));

    Object* trees[20];
    Object* treesLeft[20];
    for (int i=0; i < 20; i++){
         trees[i]= new Object("../model/treescaled.obj");
        trees[i]->Model = translate(trees[i]->Model,vec3(25.0f, 0.0f, -4.0f * (i-5)));

        treesLeft[i]= new Object("../model/treescaled.obj");
        treesLeft[i]->Model = translate(treesLeft[i]->Model,vec3(-5.0f, 0.0f, -4.0f * (i-5)));
    }

    Object* cars[10];
    for (int i=0; i<10; i++){

        cars[i] = new Object("../model/car2.obj");
        cars[i]->Model = translate(cars[i]->Model,vec3(rand() % 30 - 20, 1.0f, -rand() % 50 + 20));

       if(i%2){
           cars[i]->Model = rotate(cars[i]->Model,radians(180.0f),vec3(0.0f,1.0f,0.0f)) ;
        }

    }

    TextureID = glGetUniformLocation(shaderProgramId, "ourTexture");

     LightClrID = glGetUniformLocation(shaderProgramId, "lightColor");

     LightPosID = glGetUniformLocation(shaderProgramId, "lightPos");

    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwGetCursorPos (window, &mousePosX, &mousePosY );
    glfwSetMouseButtonCallback(window, mouse_button);

    ambientIntensityLocation= glGetUniformLocation(shaderProgramId, "ambientIntensity");


    while(!glfwWindowShouldClose(window)) {

        currentTime = float(glfwGetTime());
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        View = camera.GetViewMatrix();
        Projection = perspective(radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

        mat4 VP = Projection * View ;


        keyProcess(window);
        glClearColor(.53,.81,.93, .5);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

        glUseProgram(shaderProgramId);


        GLuint matrixID = glGetUniformLocation(shaderProgramId, "VP");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &VP[0][0]);

        GLuint modelID = glGetUniformLocation(shaderProgramId, "Model");

        GLuint viewID = glGetUniformLocation(shaderProgramId, "View");
        glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);

        glUniform3fv(LightClrID, 1, &lightColor[0]);
        glUniform3fv(LightPosID, 1, &lightPos[0]);

        drawObj(modelID, road, 1, GL_TEXTURE1);
        drawObj(modelID, road2, 1, GL_TEXTURE1);
        drawObj(modelID, car, 4, GL_TEXTURE4);
        drawObj(modelID, car2, 3, GL_TEXTURE3);
        drawObj(modelID, grass, 7, GL_TEXTURE7);

        drawObj(modelID, wall, 3, GL_TEXTURE3);
        drawObj(modelID, wall2, 4, GL_TEXTURE4);
        drawObj(modelID, wall3, 5, GL_TEXTURE5);
        drawObj(modelID, wall4, 3, GL_TEXTURE3);

        drawObj(modelID, wallLeft, 4, GL_TEXTURE4);
        drawObj(modelID, wallLeft2, 3, GL_TEXTURE3);
        drawObj(modelID, wallLeft3, 5, GL_TEXTURE5);
        drawObj(modelID, wallLeft4, 4, GL_TEXTURE4);



        for(int i=0; i<20; i++){
            drawObj(modelID, trees[i], 7, GL_TEXTURE7);
            drawObj(modelID, treesLeft[i], 7, GL_TEXTURE7);
        }

        for(int i=0; i<10;i++){
            drawObj(modelID, cars[i], 4, GL_TEXTURE4);
        }


        moveCars(cars);



        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &(road->VAO));
    glDeleteVertexArrays(1, &(road2->VAO));
    glDeleteVertexArrays(1, &(grass->VAO));
    glDeleteVertexArrays(1, &(car->VAO));

    glDeleteVertexArrays(1, &(road->VBO));
    glDeleteVertexArrays(1, &(road2->VBO));
    glDeleteVertexArrays(1, &(grass->VBO));
    glDeleteVertexArrays(1, &(car->VBO));

    glDeleteVertexArrays(1, &(road->VBONormal));
    glDeleteVertexArrays(1, &(road2->VBONormal));
    glDeleteVertexArrays(1, &(grass->VBONormal));
    glDeleteVertexArrays(1, &(car->VBONormal));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glfwTerminate();
    return 0;
}

void keyProcess(GLFWwindow *window) {

    if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey (window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey (window, GLFW_KEY_J) == GLFW_PRESS)
        driveCar(car, 0, -1);
    if (glfwGetKey (window, GLFW_KEY_L) == GLFW_PRESS)
        driveCar(car, 0, 1);
    if (glfwGetKey (window, GLFW_KEY_I) == GLFW_PRESS){
        driveCar(car, -1, 0);
        camera.ProcessKeyboard(FORWARD, deltaTime / 1.5);
    }
    if (glfwGetKey (window, GLFW_KEY_K) == GLFW_PRESS){
        driveCar(car, 1, 0);
        camera.ProcessKeyboard(BACKWARD, deltaTime / 1.5);
    }
     if (glfwGetKey (window, GLFW_KEY_U) == GLFW_PRESS)
        CarSpeed = 1 + CarSpeed;
    if (glfwGetKey (window, GLFW_KEY_O) == GLFW_PRESS)
        if(CarSpeed > 1)
        CarSpeed = CarSpeed - 1;


    if (glfwGetKey (window, GLFW_KEY_C) == GLFW_PRESS)
        driveCar(car2, 0, -1);
    if (glfwGetKey (window, GLFW_KEY_N) == GLFW_PRESS)
        driveCar(car2, 0, 1);
    if (glfwGetKey (window, GLFW_KEY_G) == GLFW_PRESS){
        driveCar(car2, -1, 0);
    }
    if (glfwGetKey (window, GLFW_KEY_B) == GLFW_PRESS){
        driveCar(car2, 1, 0);
    }

    if (glfwGetKey (window, GLFW_KEY_V) == GLFW_PRESS) {

        glClearColor(.07,.81,.88, .5);
        glUniform1f(ambientIntensityLocation, 0.2f);
    }
    if (glfwGetKey (window, GLFW_KEY_X) == GLFW_PRESS) {
        glClearColor(.53,.81,.93, .5);
        glUniform1f(ambientIntensityLocation, 0.8f);
    }
}

void mouse_button (GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_RIGHT :
                YCamera += 1.;
//                Model = scale(Model,vec3(2.0f, 2.0f ,2.0f));
                break;
            case GLFW_MOUSE_BUTTON_LEFT :
                YCamera -= 1.;
//                Model = scale(Model,vec3(.5f, .5f ,.5f));
                break;
            default:
                YCamera -= 1.;
//                Model = scale(Model,vec3(2.0f, 2.0f ,2.0f));
                break;
        }
//    if (action == GLFW_RELEASE)
//        glClearColor(0.3f, 0.4f, 0.3f, 0.5f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void InitTexture( const char* image_path, int width, int height,GLuint tab_textures[], int n) {
    int nrChannels;
    unsigned char* data;
    data = stbi_load(image_path, &width, &height, &nrChannels, 0);

        glGenTextures(1, &tab_textures[n]);
        glBindTexture(GL_TEXTURE_2D, tab_textures[n]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        if(n<=7 && n >= 3) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

    stbi_image_free(data);
}

void LoadTextures() {

    int width= 150;
    int height= 150;

    InitTexture( "../textures/Roads/z-direction.bmp", width, height, tab_textures, 0);
    InitTexture( "../textures/Roads/x-direction.bmp", width, height, tab_textures, 1);
    InitTexture( "../textures/Roads/crossing.bmp", width, height, tab_textures, 2);
    InitTexture( "../textures/Roads/left-front building-front.bmp", width, height, tab_textures, 3);
    InitTexture( "../textures/Roads/left-front building-back.bmp", width, height, tab_textures, 4);
    InitTexture( "../textures/Roads/left-front building-front-back.bmp", width, height, tab_textures, 5);
    InitTexture( "../textures/Roads/left-front building-roof.bmp", width, height, tab_textures, 6);
    InitTexture( "../textures/Roads/grass-texture.bmp", width, height, tab_textures, 7);
    InitTexture( "../textures/Roads/clock.bmp", width, height, tab_textures, 8);
    InitTexture( "../textures/Roads/grass.jpg", width, height, tab_textures, 9);

}

void drawObj(GLuint modelID, Object* obj, int texture_index, GLenum texture) {

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &obj->Model[0][0]);
    glBindVertexArray(obj->VAO);


    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, tab_textures[texture_index]);
    glUniform1i(TextureID, texture_index);
    glDrawArrays(GL_TRIANGLES, 0, obj->position.size());
}

void driveCar(Object* car, int forward,  int right){

    GLfloat velocity = CarSpeed * deltaTime;
    if(right){
        car->Model = rotate(car->Model,radians(sin( (-right * velocity))),vec3(0.0f,1.0f,0.0f)) ;
    }
    else
    car->Model = translate(car->Model,vec3(0 + sin( (right * velocity)),0.0f, 0 + (forward * velocity))) ;
}

void moveCars(Object* cars[]){
    GLfloat velocity =  deltaTime * 2;
    for(int i=0; i<10; i++) {
        if(i%2)
            velocity = -1 * velocity;
        cars[i]->Model = translate(cars[i]->Model,vec3(0.0f ,0.0f, 0 + (1 * velocity)));

        if(rand() % 10 == i) {
            cars[i]->Model = rotate(cars[i]->Model,radians(sin( (2 * velocity))),vec3(0.0f,1.0f,0.0f)) ;
        }
    }
}



