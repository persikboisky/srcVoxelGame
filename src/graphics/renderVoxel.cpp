#include <GL/glew.h>
#include "renderVoxel.hpp"
#include "Texture.hpp"

void renderVoxel::render(float x, float y, float z, int texture)
{

    float vertexs[] = {
        x, y, z, 0, 0,
        x, y - 1, z, 0, 1,
        x + 1, y - 1, z, 1, 1,
        x, y, z, 0, 0,
        x + 1, y - 1, z, 1, 1,
        x + 1, y, z, 1, 0,

        x, y, z - 1, 0, 0,
        x, y - 1, z - 1, 0, 1,
        x, y - 1, z, 1, 1,
        x, y, z - 1, 0, 0,
        x, y - 1, z, 1, 1,
        x, y, z, 1, 0,

        x + 1, y, z - 1, 0, 0,
        x + 1, y - 1, z - 1, 0, 1,
        x, y - 1, z - 1, 1, 1,
        x + 1, y, z - 1, 0, 0,
        x, y - 1, z - 1, 1, 1,
        x, y, z - 1, 1, 0,

        x + 1, y, z, 0, 0,
        x + 1, y - 1, z, 0, 1,
        x + 1, y - 1, z - 1, 1, 1,
        x + 1, y, z, 0, 0,
        x + 1, y - 1, z - 1, 1, 1,
        x + 1, y, z - 1, 1, 0,

        x, y, z - 1, 0, 0,
        x, y, z, 0, 1,
        x + 1, y, z, 1, 1,
        x, y, z - 1, 0, 0,
        x + 1, y, z, 1, 1,
        x + 1, y, z - 1, 1, 0,

        x, y - 1, z, 0, 0,
        x, y - 1, z - 1, 0, 1,
        x + 1, y - 1, z - 1, 1, 1,
        x, y - 1, z, 0, 0,
        x + 1, y - 1, z - 1, 1, 1,
        x + 1, y - 1, z, 1, 0
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    texture::useByID(texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &VAO);
} 