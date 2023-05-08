#pragma once

#include "shaderClass.h"
#include "TriangleSurface.h"
#include "Objects/Camera.h"
#include "Texture.h"
#include "Heightmap.h"

#include "Shapes/Cube.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Curve.h"
#include "Objects/Light.h"
#include "Objects/Player.h"
#include "Shapes/Circle.h"
#include "Shapes/Sphere.h"
#include "Objects/Pickup.h"
#include "Objects/LightSwitch.h"
#include "Objects/Enemy.h"

#include <glm/glm.hpp>

#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

float DeltaTime = 0.0f; // Time between current frame and the last
float LastFrame = 0.0f; // Time of last frame

Camera* camera = new Camera();
float CameraSpeed = 2.5f;
float Fov = 45.0f;

float LastXPos = SCREEN_WIDTH / 2;
float LastYPos = SCREEN_HEIGHT / 2;
bool FirstMouse = true;
bool IsCameraLocked = false;

std::vector<VisualObject*> PlainObjects;
std::vector<VisualObject*> TexturedObjects;
std::vector<VisualObject*> LightObjects;

std::vector<VisualObject*> CollisionObjects;


// Shaders and setup
std::vector<Shader*> shaderPrograms;

Shader* CurrentShader;

void SetupPlainShader(int shaderIndex);
void SetupTextureShader(int shaderIndex);
void SetupLightShader(int shaderIndex);

void UpdateCurrentUniforms(Shader* currentShader);

FillType CurrentFillType = FULL;

// Textures
std::vector<Texture*> allTextures;

void ProcessInput(GLFWwindow* window);
// xpos is the mouse's x-position, ypos is the mouse's y-position
void MouseCallback(GLFWwindow* window, double xpos, double ypos);

void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
void Tick();

void CheckAllColliders();
void CheckLightSwitch();
void CullDeletedObjects();

void ResetGame();

bool CameraFirstPerson = true;

// Uniforms
glm::mat4 mMatrixUniform = glm::mat4(1.0f);
glm::mat4 mPMatrixUniform = glm::mat4(1.0f);
glm::mat4 mVMatrixUniform = glm::mat4(1.0f);

GLint mAmbientColorUniform{ -1 };
GLint mAmbientIntensityUniform{ -1 };
GLint mDiffuseIntensityUniform{ -1 };
GLint mCameraPositionUniform{ -1 };
GLint mLightPositionUniform{ -1 };
GLint mSpecIntensityUniform{ -1 };
GLint TextureUniform;