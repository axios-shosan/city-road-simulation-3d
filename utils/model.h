#pragma once
#include <vector>

#include <glm/glm.hpp>


#include <iostream>
#include "../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../shader/shader.hpp"
#include "../model/objload.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


using namespace std;

using namespace glm;



class Object {
public:

    GLuint VAO, VBO, VBONormal;
    vector<vec3> position;
    vector<vec3> normals;
    vector<vec2> texture;
    mat4 Model;

    Object(char *path) {
        this->bindObj(path);
        this->Model = mat4(1.0);
    }




private:

    void bindObj(char *path) {

        loadOBJ(path, this->position, this->texture, this->normals);

        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->position.size() * sizeof(vec3), &this->position[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);

        glGenBuffers(1, &this->VBONormal);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBONormal);
        glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(vec3), &this->normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);

        glBufferData(GL_ARRAY_BUFFER, this->texture.size() * sizeof(vec2), &this->texture[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *) 0);
        glEnableVertexAttribArray(2);

    };
};