#include "Laborator9.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator9::Laborator9()
{
}

Laborator9::~Laborator9()
{
}

void Laborator9::Init()
{
	const string textureLoc = "Source/Laboratoare/Laborator9/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "ichigo.png").c_str(), GL_REPEAT);
		mapTextures["ichigo"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "menos.png").c_str(), GL_REPEAT);
		mapTextures["menos"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "background.gif").c_str(), GL_REPEAT);
		mapTextures["background"] = texture;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	
	ichigo = new Player(glm::vec3(-8, -2.8, 0));
	menos = new Player(glm::vec3(8, -2.8, 0));
	LoadAnimations(textureLoc + "ichigo.txt", ichigo);
	LoadAnimations(textureLoc + "menos.txt", menos);
	ichigo->computeAverageTextureWidthOfAnimations();
	menos->computeAverageTextureWidthOfAnimations();
	ichigo->computeScaleFactors();
	menos->computeScaleFactors();
	ichigo->setCurrentAnimation("IchigoStance");
	menos->setCurrentAnimation("MenosStance");
	ichigo->setDirection(1);
	menos->setDirection(0);

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(16,   8.75f, 0.0f),
		glm::vec3(16,  -8.75f, 0.0f),
		glm::vec3(-16, -8.75f, 0.0f),
		glm::vec3(-16,  8.75f, 0.0f)
	};

	std::vector<glm::vec3> normals =
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	std::vector<glm::vec2> textureCoords =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Mesh* mesh = new Mesh("background");
	mesh->InitFromData(vertices, normals, textureCoords, indices);

	meshes["background"] = mesh;
}

void Laborator9::LoadAnimations(std::string fileName, Player* player)
{
	ifstream animationsFile(fileName.c_str());
	std::string line;
	std::size_t found;
	bool foundAnimationName = false;
	bool foundFrameNumber = false;
	std::vector<glm::vec2> textureCoords;

	while(getline(animationsFile, line))
	{
		if (!foundAnimationName)
			found = line.find("Animation Name");
		else
			found = line.find("</Animation>");

		if (found != std::string::npos)
		{
			foundAnimationName = !foundAnimationName;
			if (foundAnimationName == true)
				player->addAnimation(getStringBetween(line, "\"", "\""));
		}

		if (foundAnimationName)
		{
			if (!foundFrameNumber)
				found = line.find("Frame Number");
			else
				found = line.find("</Frame>");

			if (found != std::string::npos)
				foundFrameNumber = !foundFrameNumber;
			
			if (foundFrameNumber == true)
			{
				found = line.find("UV Number");

				if (found != std::string::npos)
					textureCoords.push_back(getUV(line));

				if (textureCoords.size() == 4)
				{
					player->updateTextureCoords(textureCoords);
					player->addFrameToLastAnimation();
					textureCoords.clear();
				}
			}
		}
	}

	animationsFile.close();
}

glm::vec2 Laborator9::getUV(std::string line)
{
	float u = std::stof(getStringBetween(line, "U=\"", "\" "));
	float v = std::stof(getStringBetween(line, "V=\"", "\""));

	return glm::vec2(u, v);
}

std::string Laborator9::getStringBetween(std::string oStr, std::string left, std::string right)
{
	using namespace std::literals::string_literals;
	auto start = left;
	auto end = right;
	std::regex base_regex(start + "(.*)" + end);
	auto example = oStr;
	std::smatch base_match;
	std::string matched;

	if (std::regex_search(example, base_match, base_regex)) {
		if (base_match.size() == 2) {
			matched = base_match[1].str();
		}
	}

	return matched;
}

void Laborator9::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator9::Update(float deltaTimeSeconds)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.5, -1));
	RenderSimpleMesh(meshes["background"], shaders["ShaderLab9"], modelMatrix, mapTextures["background"]);
	glEnable(GL_DEPTH_TEST);

	RenderIchigo(deltaTimeSeconds);
	RenderMenos(deltaTimeSeconds);

	std::string ichigoAnimationName = ichigo->getCurrentAnimationName();
	std::string menosAnimationName = menos->getCurrentAnimationName();
	
	if(ichigoAnimationName != "IchigoFall" && menosAnimationName != "MenosFall")
		Collision(ichigoAnimationName == "IchigoAttack", menosAnimationName == "MenosAttack");

	if (ichigoAnimationName == "IchigoFall")
		MovePlayerBackwards(ichigo, deltaTimeSeconds);

	if (menosAnimationName == "MenosFall")
		MovePlayerBackwards(menos, deltaTimeSeconds);
}

void Laborator9::RenderIchigo(float deltaTimeSeconds)
{
	Animation* animation = ichigo->getCurrentAnimation();
	int framePeriod = animation->getFramePeriod();
	std::string name = animation->getName();
	int animationPeriod = framePeriod * animation->getNumberOfFrames();
	glm::vec3 position = ichigo->getPosition();
	int animationSpeed = getAnimationSpeed(name, Engine::GetElapsedTime() - movingTimeIchigo);
	bool animationEnd = (indexAnimation1 == (animationPeriod - 1));

	if (name == "IchigoGuard")
		indexAnimation1 = 0;
	else if (animationEnd && name == "IchigoAttack") {
		if (window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_D)) {
			ichigo->setCurrentAnimation("IchigoWalk");
			movingTimeIchigo += Engine::GetElapsedTime() - ichigo->getTimeOfAttack();
			ichigo->setTimeOfAttack(0);
		}
		else
			ichigo->setCurrentAnimation("IchigoStance");
		indexAnimation1 = 0;
	}
	else if (animationEnd && name == "IchigoFall") {
		ichigo->setCurrentAnimation("IchigoStance");
		indexAnimation1 = 0;
	}
	else
		indexAnimation1 = (indexAnimation1 + animationSpeed) % animationPeriod;

	ichigoScaleFactor = glm::vec3(5.5 * animation->getScaleFactorAt(indexAnimation1 / framePeriod), 5.5, 0);
	Mesh* mesh = animation->getFrameAt(indexAnimation1 / framePeriod);

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, ichigoScaleFactor);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(180 * ichigo->getDirection()), glm::vec3(0, 1, 0));
		RenderSimpleMesh(mesh, shaders["ShaderLab9"], modelMatrix, mapTextures["ichigo"]);
	}

	if (animationSpeed >= 3 && name == "IchigoWalk") {
		ichigo->setCurrentAnimation("IchigoRun");
		indexAnimation1 = 0;
	}
}

void Laborator9::RenderMenos(float deltaTimeSeconds)
{
	Animation* animation = menos->getCurrentAnimation();
	int framePeriod = animation->getFramePeriod();
	std::string name = animation->getName();
	int animationPeriod = framePeriod * animation->getNumberOfFrames();
	glm::vec3 position = menos->getPosition();
	int animationSpeed = getAnimationSpeed(name, Engine::GetElapsedTime() - movingTimeMenos + 0.8);
	bool animationEnd = (indexAnimation2 == (animationPeriod - 1));

	// mentine garda cat timp se apasa tasta "down"
	// cand se renunta la garda, se face animatie inversa si se revine la "stance"
	// animatia de atac se incheie si trec fie in "walk" fie in "stance"
	// daca se revine in walk, se scade din perioada de "walk" timpul animatiei de "attack"
	// altfel, randez fie frameul curent fie trec la urmatorul
	if (animationEnd && name == "MenosGuard")
		indexAnimation2 = framePeriod * animation->getNumberOfFrames() - 1;
	else if (animationEnd && name == "MenosGuardReversed") {
		indexAnimation2 = 0;
		menos->setCurrentAnimation("MenosStance");
	}
	else if (animationEnd && name == "MenosAttack") {
		if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_RIGHT)) {
			menos->setCurrentAnimation("MenosWalk");
			movingTimeMenos += Engine::GetElapsedTime() - menos->getTimeOfAttack();
			menos->setTimeOfAttack(0);
		}
		else
			menos->setCurrentAnimation("MenosStance");
		indexAnimation2 = 0;
	}
	else if (animationEnd && name == "MenosFall") {
		menos->setCurrentAnimation("MenosStance");
		indexAnimation2 = 0;
	}
	else
		indexAnimation2 = (indexAnimation2 + animationSpeed) % animationPeriod;

	menosScaleFactor = glm::vec3(5 * animation->getScaleFactorAt(indexAnimation2 / framePeriod), 5, 0);
	Mesh* mesh2 = animation->getFrameAt(indexAnimation2 / framePeriod);

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, menosScaleFactor);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(180 * menos->getDirection()), glm::vec3(0, 1, 0));
		RenderSimpleMesh(mesh2, shaders["ShaderLab9"], modelMatrix, mapTextures["menos"]);
	}
}

int Laborator9::getAnimationSpeed(std::string animationName, double movingTime)
{
	if (animationName != "MenosWalk" && animationName != "IchigoWalk" && animationName != "IchigoRun")
		return 1;

	return min(1 + (int) floor(movingTime), 4);
}

void Laborator9::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Laborator9::Collision(bool ichigoAttack, bool menosAttack)
{
	if (!ichigoAttack && !menosAttack)
		return ;

	glm::vec3 ichigoPosition = ichigo->getPosition();
	glm::vec3 menosPosition = menos->getPosition();
	double ichigoWidth = ichigo->getWidth() * ichigoScaleFactor.x - 0.5;
	double ichigoHeight = ichigo->getHeight() * ichigoScaleFactor.y;
	double menosWidth = menos->getWidth() * menosScaleFactor.x - 0.5;
	double menosHeight = menos->getHeight() * menosScaleFactor.y;

	// verific daca intra in coliziune
	if (!(ichigoPosition.x < menosPosition.x + menosWidth &&
		ichigoPosition.x + ichigoWidth > menosPosition.x &&
		ichigoPosition.y < menosPosition.y + menosHeight &&
		ichigoHeight + ichigoPosition.y > menosPosition.y))
			return;

	if (ichigoAttack && menosAttack) {
		if (Engine::GetElapsedTime() - ichigo->getTimeOfAttack() > 0.8) {
			movingTimeIchigo = Engine::GetElapsedTime();
			indexAnimation1 = 0;
			ichigo->setCurrentAnimation("IchigoFall");
		}

		if (Engine::GetElapsedTime() - menos->getTimeOfAttack() > 0.8) {
			movingTimeMenos = Engine::GetElapsedTime();
			indexAnimation2 = 0;
			menos->setCurrentAnimation("MenosFall");
		}
	}
	else if (ichigoAttack) {
		if(menos->getCurrentAnimationName() != "MenosGuard")
			if (Engine::GetElapsedTime() - ichigo->getTimeOfAttack() > 0.7) {
				movingTimeMenos = Engine::GetElapsedTime();
				indexAnimation2 = 0;
				menos->setCurrentAnimation("MenosFall");

				// atac pe la spate
				if (ichigo->getDirection() == menos->getDirection())
					menos->turnOppositeDirection();
			}
	}
	else
	{
		if(ichigo->getCurrentAnimationName() != "IchigoGuard")
			if (Engine::GetElapsedTime() - menos->getTimeOfAttack() > 1) {
				movingTimeIchigo = Engine::GetElapsedTime();
				indexAnimation1 = 0;
				ichigo->setCurrentAnimation("IchigoFall");

				// atac pe la spate
				if (ichigo->getDirection() == menos->getDirection())
					ichigo->turnOppositeDirection();
			}
	}
}

void Laborator9::OnInputUpdate(float deltaTime, int mods)
{
	if (menos->getCurrentAnimationName() != "MenosFall")
	{
		if (window->KeyHold(GLFW_KEY_DOWN)) {
			menos->setCurrentAnimation("MenosGuard");
		}

		if (!window->KeyHold(GLFW_KEY_DOWN) && (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_RIGHT))) {
			if (menos->getCurrentAnimationName() == "MenosStance")
				menos->setCurrentAnimation("MenosWalk");

			double distance = min(6.0, menos->getSpeed() * (Engine::GetElapsedTime() - movingTimeMenos + 0.6));
			glm::vec3 oldPosition = menos->getPosition();

			if (menos->getDirection() == 0)
				distance = -distance;

			// incetineste miscarea cat timp ataci
			if (menos->getCurrentAnimationName() == "MenosAttack")
				distance /= 4;

			distance *= deltaTime;

			double newPositionX = oldPosition.x + distance;

			if (newPositionX <= -sceneWidth)
				menos->updatePosition(glm::vec3(sceneWidth, oldPosition.y, oldPosition.z));
			else if (newPositionX >= sceneWidth)
				menos->updatePosition(glm::vec3(-sceneWidth, oldPosition.y, oldPosition.z));
			else
				menos->updatePosition(glm::vec3(oldPosition.x + distance, oldPosition.y, oldPosition.z));
		}
	}

	if (ichigo->getCurrentAnimationName() != "IchigoFall")
	{
		if (window->KeyHold(GLFW_KEY_S)) {
			ichigo->setCurrentAnimation("IchigoGuard");
		}

		if (!window->KeyHold(GLFW_KEY_S) && (window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_D))) {
			if (ichigo->getCurrentAnimationName() == "IchigoStance")
				ichigo->setCurrentAnimation("IchigoWalk");

			double distance = min(7.5, ichigo->getSpeed() * (Engine::GetElapsedTime() - movingTimeIchigo + 0.6));
			glm::vec3 oldPosition = ichigo->getPosition();

			if (ichigo->getDirection() == 0)
				distance = -distance;

			// incetineste miscarea cat timp ataci
			if (ichigo->getCurrentAnimationName() == "IchigoAttack")
				distance /= 4;

			distance *= deltaTime;

			double newPositionX = oldPosition.x + distance;

			if (newPositionX <= -sceneWidth)
				ichigo->updatePosition(glm::vec3(sceneWidth, oldPosition.y, oldPosition.z));
			else if (newPositionX >= sceneWidth)
				ichigo->updatePosition(glm::vec3(-sceneWidth, oldPosition.y, oldPosition.z));
			else
				ichigo->updatePosition(glm::vec3(oldPosition.x + distance, oldPosition.y, oldPosition.z));
		}
	}
}

void Laborator9::OnKeyPress(int key, int mods)
{
	std::string ichigoAnimationName = ichigo->getCurrentAnimationName();
	std::string menosAnimationName = menos->getCurrentAnimationName();

	if (ichigoAnimationName != "IchigoFall") 
	{
		if (key == GLFW_KEY_W) {
			if (window->KeyHold(GLFW_KEY_S) || ichigoAnimationName == "IchigoFall") {
			}
			else if (!(ichigoAnimationName == "IchigoAttack")) {
				ichigo->setCurrentAnimation("IchigoAttack");
				indexAnimation1 = 0;
				ichigo->setTimeOfAttack(Engine::GetElapsedTime());
			}
		}

		if (key == GLFW_KEY_A) {
			if (!window->KeyHold(GLFW_KEY_D) && !window->KeyHold(GLFW_KEY_S)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoWalk");
					indexAnimation1 = 0;
				}
			}

			movingTimeIchigo = Engine::GetElapsedTime();
			ichigo->setDirection(0);
		}

		if (key == GLFW_KEY_S) {
			indexAnimation1 = 0;
		}

		if (key == GLFW_KEY_D) {
			if (!window->KeyHold(GLFW_KEY_A) && !window->KeyHold(GLFW_KEY_S)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoWalk");
					indexAnimation1 = 0;
				}
			}

			movingTimeIchigo = Engine::GetElapsedTime();
			ichigo->setDirection(1);
		}
	}

	if (menosAnimationName != "MenosFall")
	{
		if (key == GLFW_KEY_UP) {
			if (window->KeyHold(GLFW_KEY_DOWN) || menosAnimationName == "MenosFall") {
			}
			else if (!(menosAnimationName == "MenosAttack")) {
				menos->setCurrentAnimation("MenosAttack");
				indexAnimation2 = 0;
				menos->setTimeOfAttack(Engine::GetElapsedTime());
			}
		}

		if (key == GLFW_KEY_LEFT) {
			if (!window->KeyHold(GLFW_KEY_RIGHT) && !window->KeyHold(GLFW_KEY_DOWN)) {
				if (!(menosAnimationName == "MenosAttack")) {
					menos->setCurrentAnimation("MenosWalk");
					indexAnimation2 = 0;
				}
			}

			movingTimeMenos = Engine::GetElapsedTime();
			menos->setDirection(0);
		}

		if (key == GLFW_KEY_DOWN) {
			indexAnimation2 = 0;
		}

		if (key == GLFW_KEY_RIGHT) {
			if (!window->KeyHold(GLFW_KEY_LEFT) && !window->KeyHold(GLFW_KEY_DOWN)) {
				if (!(menosAnimationName == "MenosAttack")) {
					menos->setCurrentAnimation("MenosWalk");
					indexAnimation2 = 0;
				}
			}

			movingTimeMenos = Engine::GetElapsedTime();
			menos->setDirection(1);
		}
	}
}

void Laborator9::OnKeyRelease(int key, int mods)
{
	std::string ichigoAnimationName = ichigo->getCurrentAnimationName();
	std::string menosAnimationName = menos->getCurrentAnimationName();

	if (ichigoAnimationName != "IchigoFall") {
		if (key == GLFW_KEY_S) {
			if (window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_D))
				ichigo->setCurrentAnimation("IchigoWalk");
			else
				ichigo->setCurrentAnimation("IchigoStance");
			indexAnimation1 = 0;
			movingTimeIchigo = Engine::GetElapsedTime();
		}

		if (key == GLFW_KEY_A) {
			if (!window->KeyHold(GLFW_KEY_D) && !window->KeyHold(GLFW_KEY_S)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoStance");
					indexAnimation1 = 0;
				}
			}
			else if (window->KeyHold(GLFW_KEY_D)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoWalk");
					indexAnimation1 = 0;
				}
				ichigo->setDirection(1);
				movingTimeIchigo = Engine::GetElapsedTime();
			}
		}

		if (key == GLFW_KEY_D) {
			if (!window->KeyHold(GLFW_KEY_A) && !window->KeyHold(GLFW_KEY_S)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoStance");
					indexAnimation1 = 0;
				}
			}
			else if (window->KeyHold(GLFW_KEY_A)) {
				if (!(ichigoAnimationName == "IchigoAttack")) {
					ichigo->setCurrentAnimation("IchigoWalk");
					indexAnimation1 = 0;
				}
				ichigo->setDirection(0);
				movingTimeIchigo = Engine::GetElapsedTime();
			}
		}
	}

	if (menosAnimationName != "MenosFall") {
		if (key == GLFW_KEY_DOWN) {
			if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_RIGHT))
				menos->setCurrentAnimation("MenosWalk");
			else
				menos->setCurrentAnimation("MenosGuardReversed");
			indexAnimation2 = 0;
			movingTimeMenos = Engine::GetElapsedTime();
		}

		if (key == GLFW_KEY_LEFT) {
			if (!window->KeyHold(GLFW_KEY_RIGHT) && !window->KeyHold(GLFW_KEY_DOWN)) {
				if (!(menosAnimationName == "MenosAttack")) {
					menos->setCurrentAnimation("MenosStance");
					indexAnimation2 = 0;
				}
			}
			else if (window->KeyHold(GLFW_KEY_LEFT)) {
				menos->setDirection(1);
				movingTimeMenos = Engine::GetElapsedTime();
			}
		}

		if (key == GLFW_KEY_RIGHT) {
			if (!window->KeyHold(GLFW_KEY_LEFT) && !window->KeyHold(GLFW_KEY_DOWN)) {
				if (!(menosAnimationName == "MenosAttack")) {
					menos->setCurrentAnimation("MenosStance");
					indexAnimation2 = 0;
				}
			}
			else if (window->KeyHold(GLFW_KEY_LEFT)) {
				menos->setDirection(0);
				movingTimeMenos = Engine::GetElapsedTime();
			}
		}
	}
}

void Laborator9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator9::OnWindowResize(int width, int height)
{
}

void Laborator9::MovePlayerBackwards(Player* player, float deltaTimeSeconds)
{
	double distance = player->getSpeed() * deltaTimeSeconds;

	if (player->getDirection() == 1)
		distance = -distance;

	glm::vec3 oldPosition = player->getPosition();
	double newPositionX = oldPosition.x + distance;

	if (newPositionX <= -sceneWidth)
		player->updatePosition(glm::vec3(sceneWidth, oldPosition.y, oldPosition.z));
	else if (newPositionX >= sceneWidth)
		player->updatePosition(glm::vec3(-sceneWidth, oldPosition.y, oldPosition.z));
	else
		player->updatePosition(glm::vec3(oldPosition.x + distance, oldPosition.y, oldPosition.z));
}