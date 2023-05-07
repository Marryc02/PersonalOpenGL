#version 330 core

layout(location = 0) in vec4 positionIn;   // 1st attribute buffer = vertex positions
layout(location = 1) in vec3 colorIn;   // 2nd attribute buffer = colors
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 normalIn;

out vec3 color;                           //color sent to rest of pipeline
out vec3 normal;
out vec3 fragPos;

uniform mat4 pMatrix;                   // Leksjon 3
uniform mat4 vMatrix;                   // Leksjo4 3
uniform mat4 mMatrix;                   //the matrix for the model


void main() {
    color = colorIn;                       //passing on the vertex color
    gl_Position = pMatrix * vMatrix * mMatrix * positionIn;      //calculate the position of the model
    normal = mat3(transpose(inverse(mMatrix))) * normalIn;
    fragPos = vec3(mMatrix * positionIn);
}
