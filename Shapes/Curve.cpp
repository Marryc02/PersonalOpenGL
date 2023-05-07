#include "Curve.h"

#include <iostream>

Curve::Curve()
{
    ShaderRef = nullptr;
}

Curve::Curve(Shader* shader, std::string filepath)
{
    ShaderRef = shader;
    FilePath = filepath;

    ReadFile(FilePath, mVertices);
}

glm::vec3 Curve::GetVertexPosition(int index)
{
    return mVertices[index].pos;
}

int Curve::GetCurveVerticesSize()
{
    return mVertices.size();
}

void Curve::init(glm::mat4 matrixUniform)
{
    mMatrix = matrixUniform;

    //Vertex Array Object - VAO
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    // XYZ
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // RGB
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Curve::draw()
{
    glBindVertexArray(mVAO);
    ShaderRef->SetMat4("mMatrix", mMatrix);
    glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
}
