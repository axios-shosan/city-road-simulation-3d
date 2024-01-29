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

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        this->setupMesh();
    }

    void Draw(Shader shader)
    {
        GLuint diffuseNr = 1, specularNr = 1, reflectionNr = 1;

        for (GLuint i = 0; i < this->textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::stringstream ss;
            std::string number;
            std::string name = this->textures[i].type;
            if (name == "texture_diffuse")
                ss << diffuseNr++;
            else if (name == "texture_specular")
                ss << specularNr++;
            else if (name == "texture_reflection")
                ss << reflectionNr++;
            number = ss.str();

            glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
            TextureManager::Inst()->BindTexture(this->textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        //glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        /*
        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        */
    }


private:
    GLuint VAO, VBO, EBO;
    void setupMesh()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};
