#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "main.h"

//
// OBJECT CREATION
//

//Pyramid* pyramid;
//TriangleSurface* triangle;
Heightmap* map;
Light* light;
Player* player;
Curve* Curve1;
Cube* texturedCube;
//Circle* circle;
Sphere* sphere;
Pickup* pickup;
Pickup* pickup1;
Pickup* pickup2;
Pickup* pickup3;
Pickup* pickup4;
Pickup* pickup5;
LightSwitch* lightswitch;
Enemy* enemy;

/* CONTROL SCHEME
*
* W = Move camera forward
* A = Move camera left
* S = Move camera backward
* D = Move camera Right
*
* Spacebar = Move camera upward
* C = Move camera downwards
* Shift = Increase camera movement speed
*
* O = Go to fixed camera position 1 (Requires camera to be locked)
* P = Go to fixed camera position 2 (Requires camera to be locked)
* 
* RELEVANT FOR THE EXAM:
* L = Lock/Unlock camera : SWITCHED TO CHANGE FIRST/THIRD PERSON FOR THE EXAM
*
* 1 = Full/Solid rendering mode
* 2 = Wireframe rendering mode
* 3 = Point rendering mode
*
* Left Arrow = Move player left
* Right Arrow = Move player right
* Up Arrow = Move player forward
* Down Arrow = Move player backward
*
* Escape = Quit application
*
*/

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bababooey", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	//
	// SHADER & TEXTURE CREATION
	//

	shaderPrograms.push_back(new Shader("Shaders/plainshader.vert", "Shaders/plainshader.frag"));
	shaderPrograms.push_back(new Shader("Shaders/textureshader.vert", "Shaders/textureshader.frag"));
	shaderPrograms.push_back(new Shader("Shaders/lightshader.vert", "Shaders/lightshader.frag"));

	// We initialize the shaders to draw fully, with no wireframes
	CurrentFillType = FULL;
	for (int i = 0; i < shaderPrograms.size(); i++)
	{
		shaderPrograms[i]->fillType = CurrentFillType;
	}


	// Shader setups
	SetupPlainShader(0);
	SetupTextureShader(1);
	SetupLightShader(2);

	shaderPrograms[0]->Activate();
	UpdateCurrentUniforms(shaderPrograms[0]);
	CurrentShader = shaderPrograms[0];

	// Texture setups
	allTextures.push_back(new Texture()); // Filler texture
	allTextures.push_back(new Texture((char*)"Textures/majima_crazy.jpg")); // Actual texture


	// Load textures

	for (int i = 1; i < allTextures.size(); i++)
	{
		allTextures[i]->LoadTexture();
	}

	// Init function for plain shaded objects

	map = new Heightmap(CurrentShader, (const char*)"Textures/Heightmap.jpg");
	map->init(mMatrixUniform);

	/*pyramid = new Pyramid(CurrentShader);
	pyramid->init(mMatrixUniform);
	pyramid->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));*/

	/*triangle = new TriangleSurface(CurrentShader);
	triangle->init(mMatrixUniform);
	triangle->setPosition(glm::vec3(0.0f, 2.0f, 6.0f));*/

	pickup = new Pickup(CurrentShader);
	pickup->init(mMatrixUniform);
	pickup->setPosition(0.0f, map->HeightFromBaryc(glm::vec2(pickup->position[0], pickup->position[2])) + pickup->LowestY, 0.0f);

	/*pickup1 = new Pickup(CurrentShader);
	pickup2 = new Pickup(CurrentShader);
	pickup3 = new Pickup(CurrentShader);
	pickup4 = new Pickup(CurrentShader);
	pickup5 = new Pickup(CurrentShader);
	pickup1->init(mMatrixUniform);
	pickup2->init(mMatrixUniform);
	pickup3->init(mMatrixUniform);
	pickup4->init(mMatrixUniform);
	pickup5->init(mMatrixUniform);*/


	PlainObjects.push_back(map);
	/*PlainObjects.push_back(pyramid);
	PlainObjects.push_back(triangle);*/
	/*PlainObjects.push_back(player);*/
	/*PlainObjects.push_back(pickup);
	PlainObjects.push_back(pickup1);
	PlainObjects.push_back(pickup2);
	PlainObjects.push_back(pickup3);
	PlainObjects.push_back(pickup4);
	PlainObjects.push_back(pickup5);
	pickup1->setPosition(-10.0f, map->HeightFromBaryc(glm::vec2(-10.0f, 7.0f)) + pickup->LowestY, 7.0);
	pickup2->setPosition( 15.0f, map->HeightFromBaryc(glm::vec2(15.0f, 5.0f)) + pickup->LowestY, 5.0f);
	pickup3->setPosition(-8.0f,  map->HeightFromBaryc(glm::vec2(-8.0f, 19.0f)) + pickup->LowestY, 19.0f);
	pickup4->setPosition( 20.0f, map->HeightFromBaryc(glm::vec2(20.0f, 3.0f)) + pickup->LowestY, 3.0f);
	pickup5->setPosition( 12.0f, map->HeightFromBaryc(glm::vec2(12.0f, 9.0f)) + pickup->LowestY, 9.0f);*/

	// Init function for light shaded objects
	UpdateCurrentUniforms(shaderPrograms[2]);
	CurrentShader = shaderPrograms[2];

	light = new Light(1.0f, 1.0f, 1.0f, 0.1f, 0.7f, CurrentShader);
	light->init(mMatrixUniform);
	light->SetLightPosition(glm::vec3(-10.f, 1.0f, 0.0f));

	pickup1 = new Pickup(CurrentShader);
	pickup2 = new Pickup(CurrentShader);
	pickup3 = new Pickup(CurrentShader);
	pickup4 = new Pickup(CurrentShader);
	pickup5 = new Pickup(CurrentShader);
	pickup1->init(mMatrixUniform);
	pickup2->init(mMatrixUniform);
	pickup3->init(mMatrixUniform);
	pickup4->init(mMatrixUniform);
	pickup5->init(mMatrixUniform);

	lightswitch = new LightSwitch(CurrentShader);
	lightswitch->init(mMatrixUniform);
	lightswitch->setPosition(10.0f, map->HeightFromBaryc(glm::vec2(10.0f, -20.0f)) + lightswitch->LowestY, -20.0f);

	enemy = new Enemy(CurrentShader);
	enemy->init(mMatrixUniform);
	enemy->setPosition(-10.0f, map->HeightFromBaryc(glm::vec2(-10.0f, -20.0f)) + lightswitch->LowestY, -20.0f);

	LightObjects.push_back(pickup);
	LightObjects.push_back(pickup1);
	LightObjects.push_back(pickup2);
	LightObjects.push_back(pickup3);
	LightObjects.push_back(pickup4);
	LightObjects.push_back(pickup5);
	pickup1->setPosition(-10.0f, map->HeightFromBaryc(glm::vec2(-10.0f, 7.0f)) + pickup->LowestY, 7.0);
	pickup2->setPosition(15.0f, map->HeightFromBaryc(glm::vec2(15.0f, 5.0f)) + pickup->LowestY, 5.0f);
	pickup3->setPosition(-8.0f, map->HeightFromBaryc(glm::vec2(-8.0f, 19.0f)) + pickup->LowestY, 19.0f);
	pickup4->setPosition(20.0f, map->HeightFromBaryc(glm::vec2(20.0f, 3.0f)) + pickup->LowestY, 3.0f);
	pickup5->setPosition(12.0f, map->HeightFromBaryc(glm::vec2(12.0f, 9.0f)) + pickup->LowestY, 9.0f);
	LightObjects.push_back(lightswitch);
	LightObjects.push_back(enemy);


	Curve1 = new Curve(CurrentShader, "Pathfiles/graph.txt");
	Curve1->init(mMatrixUniform);

	/*circle = new Circle(CurrentShader);
	circle->init(mMatrixUniform);

	sphere = new Sphere(CurrentShader, 3);
	sphere->init(mMatrixUniform);
	sphere->setPosition(1.0f, 10.0f, 0.0f);*/

	LightObjects.push_back(light);
	LightObjects.push_back(Curve1);
	/*LightObjects.push_back(circle);
	LightObjects.push_back(sphere);*/

	// Init function for textured objects

	UpdateCurrentUniforms(shaderPrograms[1]);
	CurrentShader = shaderPrograms[1];

	texturedCube = new Cube(Curve1, CurrentShader);
	texturedCube->init(mMatrixUniform);

	player = new Player(CurrentShader);
	player->init(mMatrixUniform);
	player->setPosition(3.0f, map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY, 2.0f);

	TexturedObjects.push_back(texturedCube);
	TexturedObjects.push_back(player);

	//
	// COLLISION SETUP
	//

	for (int i = 0; i < PlainObjects.size(); i++)
	{
		if (dynamic_cast<CollisionComponent*>(PlainObjects[i]))
		{
			CollisionObjects.push_back(PlainObjects[i]);
		}
	}

	for (int i = 0; i < TexturedObjects.size(); i++)
	{
		if (dynamic_cast<CollisionComponent*>(TexturedObjects[i]))
		{
			CollisionObjects.push_back(TexturedObjects[i]);
		}
	}

	for (int i = 0; i < LightObjects.size(); i++)
	{
		if (dynamic_cast<CollisionComponent*>(LightObjects[i]))
		{
			CollisionObjects.push_back(LightObjects[i]);
		}
	}

	//
	// SETTING COLLISION TARGETS
	//

	player->SetCollisionTarget(pickup);
	player->SetCollisionTarget(pickup1);
	player->SetCollisionTarget(pickup2);
	player->SetCollisionTarget(pickup3);
	player->SetCollisionTarget(pickup4);
	player->SetCollisionTarget(pickup5);
	player->SetCollisionTarget(lightswitch);
	enemy->SetCollisionTarget(player);
	
	
	std::cout << "Collision objects: " << CollisionObjects.size() << std::endl;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallBack);
	glEnable(GL_DEPTH_TEST);

	// Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		Tick();
		ProcessInput(window);
		CheckAllColliders();
		CheckLightSwitch();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < shaderPrograms.size(); i++)
		{
			shaderPrograms[i]->Activate();
			// pass projection matrix to shader (note that in this case it could change every frame)
			mPMatrixUniform = glm::perspective(glm::radians(Fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
			shaderPrograms[i]->SetMat4("pMatrix", mPMatrixUniform);

			// camera/view transformation
			mVMatrixUniform = glm::lookAt(camera->Position, camera->Position + camera->Front, camera->Up);
			shaderPrograms[i]->SetMat4("vMatrix", mVMatrixUniform);
		}


		if (CameraFirstPerson)
		{
			camera->Position = player->position + glm::vec3(0.0f, 0.0f, -1.0f);
			camera->Front = -player->right;
		}
		else
		{
			camera->Position = player->position + glm::vec3(0.0f, 24.0f, 30.0f);
			camera->Front = player->position - camera->Position;
		}


		//
		// LIGHT OBJECTS - Draws objects that do not use light
		//

		shaderPrograms[2]->Activate();
		UpdateCurrentUniforms(shaderPrograms[2]);
		CurrentShader = shaderPrograms[2];

		for (auto it = LightObjects.begin(); it != LightObjects.end(); it++)
		{
			//shaderPrograms[2]->SetMat4("mMatrix", glm::translate(glm::mat4(1.f), (*it)->position));
			(*it)->draw();
		}

		pickup->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));
		pickup1->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));
		pickup2->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));
		pickup3->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));
		pickup4->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));
		pickup5->setRotation((float)glfwGetTime() * 120, glm::vec3(0.0f, 1.0f, 0.0f));


		//
		// PLAIN OBJECTS - Draws regular objects
		//

		shaderPrograms[0]->Activate();
		UpdateCurrentUniforms(shaderPrograms[0]);
		CurrentShader = shaderPrograms[0];

		for (auto it = PlainObjects.begin(); it != PlainObjects.end(); it++)
		{
			//shaderPrograms[0]->SetMat4("mMatrix", glm::translate(glm::mat4(1.f), (*it)->position));
			(*it)->draw();
		}


		//
		// TEXTURED OBJECTS - Draws textured objects
		//

		shaderPrograms[1]->Activate(); 
		UpdateCurrentUniforms(shaderPrograms[1]);
		CurrentShader = shaderPrograms[1];

		glUniform1i(TextureUniform, 0);
		allTextures[0]->UseTexture();

		for (auto it = TexturedObjects.begin(); it != TexturedObjects.end(); it++)
		{
			//shaderPrograms[1]->SetMat4("mMatrix", glm::translate(glm::mat4(1.f), (*it)->position));
			(*it)->draw();
		}

		texturedCube->FollowCurve(DeltaTime);


		//
		// LIGHT MAGIC
		//

		shaderPrograms[0]->Activate();
		CurrentShader = shaderPrograms[0];

		//camera->SendCamPosToShader(mCameraPositionUniform);

		CurrentShader->SetVec3("viewPos", camera->Position);

		//light->UseLight(mAmbientIntensityUniform, mAmbientColorUniform, mDiffuseIntensityUniform, mLightPositionUniform);
		//pickup->setScale(glm::vec3(2.0, 2.0, 2.0));

		//if (lightswitch->bSwitchHasBeenFlipped == false)
		//{
		//	light->UseLight(mAmbientIntensityUniform, mAmbientColorUniform, mDiffuseIntensityUniform, mLightPositionUniform);
		//}
		if (lightswitch->bSwitchHasBeenFlipped == false)
		{
			light->UseLightDif(mAmbientIntensityUniform, mAmbientColorUniform, mDiffuseIntensityUniform, mLightPositionUniform);
		}
		else
		{
			light->UseLightAmb(mAmbientIntensityUniform, mAmbientColorUniform, mDiffuseIntensityUniform, mSpecIntensityUniform);
		}

		if (enemy->WillResetGame)
		{
			enemy->WillResetGame = false;
			ResetGame();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void SetupPlainShader(int shaderIndex)
{
	shaderPrograms[shaderIndex]->MMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "mMatrix");
	shaderPrograms[shaderIndex]->PMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "pMatrix");
	shaderPrograms[shaderIndex]->VMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "vMatrix");

	mAmbientColorUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "directionalLight.color");
	mAmbientIntensityUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "directionalLight.ambientIntensity");
	mDiffuseIntensityUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "directionalLight.diffuseIntensity");
	mCameraPositionUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "viewPos");
	mLightPositionUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "lightPos");
	mSpecIntensityUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "specularStrength");
}

void SetupTextureShader(int shaderIndex)
{
	shaderPrograms[shaderIndex]->MMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "mMatrix");
	shaderPrograms[shaderIndex]->PMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "pMatrix");
	shaderPrograms[shaderIndex]->VMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "vMatrix");
	TextureUniform = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "theTexture");

	//std::cout << "Texture uni: " << TextureUniform << std::endl;
	// 
	//std::cout << "MMU: " << shaderPrograms[shaderIndex]->MMU << std::endl;
	//std::cout << "PMU: " << shaderPrograms[shaderIndex]->PMU << std::endl;
	//std::cout << "VMU: " << shaderPrograms[shaderIndex]->VMU << std::endl;

	//std::cout << "Acolor: " << mAmbientColorUniform << std::endl;
	//std::cout << "Aintensity: " << mAmbientIntensityUniform << std::endl;
	//std::cout << "dintensity: " << mDiffuseIntensityUniform << std::endl;
	//std::cout << "camera pos: " << mCameraPositionUniform << std::endl;
	//std::cout << "lightpos: " << mLightPositionUniform << std::endl;
}

void SetupLightShader(int shaderIndex)
{
	shaderPrograms[shaderIndex]->MMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "mMatrix");
	shaderPrograms[shaderIndex]->PMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "pMatrix");
	shaderPrograms[shaderIndex]->VMU = glGetUniformLocation(shaderPrograms[shaderIndex]->GetProgram(), "vMatrix");
}

void UpdateCurrentUniforms(Shader* currentShader)
{
	currentShader->SetMat4("mMatrix", mMatrixUniform);
	currentShader->SetMat4("pMatrix", mPMatrixUniform);
	currentShader->SetMat4("vMatrix", mVMatrixUniform);
}

void ProcessInput(GLFWwindow* window)
{
	CameraSpeed *= DeltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// Camera inputs

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(FORWARD, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(LEFT, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(BACKWARD, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(RIGHT, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(UPWARD, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(DOWNWARD, DeltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera->MovementSpeed = 45;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		camera->MovementSpeed = 15;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera->Position = glm::vec3(-24.3609f, -12.1139f, 22.085f);
		camera->Pitch = 4.1f;
		camera->Yaw = -31.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		camera->Position = glm::vec3(1.17202f, 27.975f, 46.665f);
		camera->Pitch = -38.7f;
		camera->Yaw = -90.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		CameraFirstPerson = !CameraFirstPerson;
	}

	// Player inputs
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		player->ProcessKeyboard(LEFT, DeltaTime);
		player->setY(map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player->ProcessKeyboard(RIGHT, DeltaTime);
		player->setY(map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		player->ProcessKeyboard(FORWARD, DeltaTime);
		player->setY(map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		player->ProcessKeyboard(BACKWARD, DeltaTime);
		player->setY(map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY);
	}

	// For changing render type between: full/solid, wireframe and lastly points
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		CurrentFillType = FULL;
		for (int i = 0; i < shaderPrograms.size(); i++)
		{
			shaderPrograms[i]->fillType = CurrentFillType;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		CurrentFillType = WIREFRAME;
		for (int i = 0; i < shaderPrograms.size(); i++)
		{
			shaderPrograms[i]->fillType = CurrentFillType;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		CurrentFillType = POINTS;
		for (int i = 0; i < shaderPrograms.size(); i++)
		{
			shaderPrograms[i]->fillType = CurrentFillType;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{

	if (FirstMouse)
	{
		LastXPos = xpos;
		LastYPos = ypos;
		FirstMouse = false;
	}

	float xOffset = xpos - LastXPos;
	float yOffset = LastYPos - ypos; // reversed since y-coordinates range from bottom to top
	LastXPos = xpos;
	LastYPos = ypos;

	const float Sensitivity = 0.1f;
	xOffset *= Sensitivity;
	yOffset *= Sensitivity;

	camera->Pitch += yOffset;
	camera->Yaw += xOffset;

	// This if sentence here is to remove weird camera movement when the pitch gets above or belove 90 degrees
	// Weird movement includes flipping controlls
	if (camera->Pitch > 89.0f)
	{
		camera->Pitch = 89.0f;
	}
	else if (camera->Pitch < -89.0f)
	{
		camera->Pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
	direction.y = sin(glm::radians(camera->Pitch));
	direction.z = sin(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));

	camera->Front = glm::normalize(direction);
	camera->updateCameraVectors();
	
}

void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
{
	camera->Zoom -= (float)yOffset;
	if (camera->Zoom < 1.0f)
	{
		camera->Zoom = 1.0f;
	}
	else if (camera->Zoom < 45.0f)
	{
		camera->Zoom = 45.0f;
	}
}

void Tick()
{
	float CurrentFrame = glfwGetTime();
	DeltaTime = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;
}

void CheckAllColliders()
{
	for (int i = 0; i < CollisionObjects.size(); i++)
	{
		player->CheckCollision((VisualObject*)CollisionObjects[i]);
		enemy->CheckCollision((VisualObject*)CollisionObjects[i]);
		CullDeletedObjects();
	}
}

void CheckLightSwitch()
{
	if (lightswitch->bSwitchHasBeenFlipped)
	{
		lightswitch->lightSwitchResetCounter();
	}
}

// Removes objects that are to be deleted
void CullDeletedObjects()
{
	for (int i = 0; i < PlainObjects.size(); i++)
	{
		if (PlainObjects[i]->WillBeDeleted)
		{
			std::swap(PlainObjects[i], PlainObjects[PlainObjects.size() - 1]);
			PlainObjects.pop_back();
		}
	}

	for (int i = 0; i < TexturedObjects.size(); i++)
	{
		if (TexturedObjects[i]->WillBeDeleted)
		{
			std::swap(TexturedObjects[i], TexturedObjects[TexturedObjects.size() - 1]);
			TexturedObjects.pop_back();
		}
	}

	for (int i = 0; i < LightObjects.size(); i++)
	{
		if (LightObjects[i]->WillBeDeleted)
		{
			std::swap(LightObjects[i], LightObjects[LightObjects.size() - 1]);
			LightObjects.pop_back();
		}
	}

	for (int i = 0; i < CollisionObjects.size(); i++)
	{
		if (CollisionObjects[i]->WillBeDeleted)
		{
			std::swap(CollisionObjects[i], CollisionObjects[CollisionObjects.size() - 1]);
			CollisionObjects.pop_back();
		}
	}
}

void ResetGame()
{
	for (int i = 0; i < PlainObjects.size(); i++)
	{
		PlainObjects[i]->WillBeDeleted = false;
	}

	for (int i = 0; i < TexturedObjects.size(); i++)
	{
		TexturedObjects[i]->WillBeDeleted = false;
	}

	for (int i = 0; i < LightObjects.size(); i++)
	{
		LightObjects[i]->WillBeDeleted = false;
	}

	player->PickupScore = 0;
	player->setPosition(3.0f, map->HeightFromBaryc(glm::vec2(player->position[0], player->position[2])) + player->LowestY, 2.0f);

}