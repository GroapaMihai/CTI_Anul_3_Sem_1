#include "Laborator8.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator8::Laborator8()
{
}

Laborator8::~Laborator8()
{
}

void Laborator8::Init()
{
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 35, 22), glm::vec3(0, 0.15f, 0), glm::vec3(0, 1, 0));
	cameraSpeed = 0.16f;
	wire = false;
	gerstnerWaves = 0;
	waterDropsSource = glm::vec3(0, 5, 0);
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	wf = new WireFrame();
	wf->setName("WireFrame");
	AddMeshToList(wf->CreateMesh());

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("superplane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "superplane.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab8");
		shader->AddShader("Resources/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Resources/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 12, 0);
		lightDirection = glm::vec3(0, 1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
		spotLight = 1;
		cut_off = 40.0f;
	}
}

void Laborator8::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.658824, 0.658824, 0.658824, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator8::MoveWaterDrops(float deltaTimeSeconds)
{
	float waterDropSpeed = 3.5f;
	std::vector<glm::vec3>::iterator it;

	for (it = waterDrops.begin(); it != waterDrops.end();) {
		if ((*it).y <= 0) {
			CircularWave wave;
			wave.center = (*it);
			wave.creationTime = clock();
			waves.push_back(wave);
			it = waterDrops.erase(it);
		}
		else {
			(*it).y -= waterDropSpeed * deltaTimeSeconds;
			++it;
		}
	}
}

void Laborator8::removeWeakWaves()
{
	std::vector<CircularWave>::iterator it;

	for (it = waves.begin(); it != waves.end();)
		if ((clock() - (*it).creationTime) / CLOCKS_PER_SEC >= wavePeriod)
			it = waves.erase(it);
		else
			++it;
}

void Laborator8::attenuateWaves(float deltaTimeSeconds)
{
	std::vector<CircularWave>::iterator it;

	for (it = waves.begin(); it != waves.end(); ++it)
		(*it).A -= (*it).attenuation * deltaTimeSeconds;
}

void Laborator8::Update(float deltaTimeSeconds)
{
	removeWeakWaves();
	attenuateWaves(deltaTimeSeconds);

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.05, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["superplane"], shaders["ShaderLab8"], modelMatrix, glm::vec3(0.137255, 0.526863, 0.419608));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab8"], modelMatrix, glm::vec3(0.89, 0.47, 0.20));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, waterDropsSource);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab8"], modelMatrix, glm::vec3(0, 0, 1));
	}

	MoveWaterDrops(deltaTimeSeconds);

	for (int i = 0; i < waterDrops.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, waterDrops[i]);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab8"], modelMatrix, glm::vec3(0, 0, 1));
	}
}

void Laborator8::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	glUniform3f(glGetUniformLocation(shader->program, "light_position"), lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(glGetUniformLocation(shader->program, "light_direction"), lightDirection.x, lightDirection.y, lightDirection.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->GetWorldPosition();
	glUniform3f(glGetUniformLocation(shader->program, "eye_position"), eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);
	glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
	glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);
	glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.r, color.g, color.b);

	// Bind model matrix
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform1i(glGetUniformLocation(shader->program, "SpotLight"), spotLight);
	glUniform1f(glGetUniformLocation(shader->program, "CutOff"), cut_off);
	glUniform1f(glGetUniformLocation(shader->program, "light"), lightPosition.y);
	glUniform1f(glGetUniformLocation(shader->program, "time"), (float)clock());

	if (gerstnerWaves == 1) {
		float amplitude[1] = {gerstnerWave.A};
		float phase[1] = {gerstnerWave.phi};

		glUniform1i(glGetUniformLocation(shader->program, "gerstnerWaves"), 1);
		glUniform1f(glGetUniformLocation(shader->program, "w"), gerstnerWave.w);
		glUniform1fv(glGetUniformLocation(shader->program, "amplitudes"), 1, amplitude);
		glUniform1fv(glGetUniformLocation(shader->program, "phases"), 1, phase);
	}
	else
		glUniform1i(glGetUniformLocation(shader->program, "gerstnerWaves"), 0);
	
	if (!waves.empty() && gerstnerWaves == 0) {
		float x[MAX_NUMBER_WAVES];
		float z[MAX_NUMBER_WAVES];
		float amplitudes[MAX_NUMBER_WAVES];
		float phases[MAX_NUMBER_WAVES];

		for (int i = 0; i < waves.size(); i++) {
			x[i] = waves[i].center.x;
			z[i] = waves[i].center.z;
			amplitudes[i] = waves[i].A;
			phases[i] = waves[i].phi;
		}

		int last = waves.size() - 1;
		glUniform1i(glGetUniformLocation(shader->program, "renderWaves"), 1);
		glUniform1f(glGetUniformLocation(shader->program, "centersY"), 15);
		glUniform1f(glGetUniformLocation(shader->program, "w"), waves[last].w);
		glUniform1i(glGetUniformLocation(shader->program, "numberOfWaves"), waves.size());
		glUniform1fv(glGetUniformLocation(shader->program, "phases"), waves.size(), phases);
		glUniform1fv(glGetUniformLocation(shader->program, "centersX"), waves.size(), x);
		glUniform1fv(glGetUniformLocation(shader->program, "centersZ"), waves.size(), z);
		glUniform1fv(glGetUniformLocation(shader->program, "amplitudes"), waves.size(), amplitudes);
	} else
		glUniform1i(glGetUniformLocation(shader->program, "renderWaves"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Laborator8::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 6;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = camera->getRight();
		glm::vec3 forward = camera->getForward();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

		// Control light position using on W, A, S, D, E, Q
		if (window->KeyHold(GLFW_KEY_W)) lightPosition += forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_S)) lightPosition -= forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;

		if (window->KeyHold(GLFW_KEY_1)) cut_off -= 3.0f;
		if (window->KeyHold(GLFW_KEY_2)) cut_off += 3.0f;

		if (window->KeyHold(GLFW_KEY_UP)) waterDropsSource += forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_LEFT)) waterDropsSource -= right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_DOWN)) waterDropsSource -= forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_RIGHT)) waterDropsSource += right * deltaTime * speed;

		glm::mat4 rotation = glm::mat4(1.0f);
		rotation = glm::rotate(rotation, RADIANS(angle_y), glm::vec3(1, 0, 0));
		rotation = glm::rotate(rotation, RADIANS(angle_x), glm::vec3(0, 0, 1));
		lightDirection = glm::vec3(rotation * glm::vec4(glm::vec3(0, 1, 0), 1));

		if (window->KeyHold(GLFW_KEY_KP_8))
			for (int i = 0; i < waves.size(); i++)
				waves[i].extraSpeed += 0.00005;

		if (window->KeyHold(GLFW_KEY_KP_2))
			for (int i = 0; i < waves.size(); i++)
				waves[i].extraSpeed -= 0.00005;
	}
	else {
		if (window->KeyHold(GLFW_KEY_W)) camera->TranslateForward(cameraSpeed);
		if (window->KeyHold(GLFW_KEY_A)) camera->TranslateRight(-cameraSpeed);
		if (window->KeyHold(GLFW_KEY_S)) camera->TranslateForward(-cameraSpeed);
		if (window->KeyHold(GLFW_KEY_D)) camera->TranslateRight(cameraSpeed);
		if (window->KeyHold(GLFW_KEY_Q)) camera->TranslateUpword(-cameraSpeed);
		if (window->KeyHold(GLFW_KEY_E)) camera->TranslateUpword(cameraSpeed);
	}
}

void Laborator8::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		wire = !wire;
		glPolygonMode(GL_FRONT_AND_BACK, (wire ? GL_LINE : GL_FILL));
	}

	if (key == GLFW_KEY_SPACE && gerstnerWaves == 0)
		waterDrops.push_back(waterDropsSource);

	if (key == GLFW_KEY_G) {
		waves.clear();

		if (gerstnerWaves == 0)
			gerstnerWaves = 1;
		else
			gerstnerWaves = 0;
	}
}

void Laborator8::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_KP_8 || key == GLFW_KEY_KP_2) {
		for (int i = 0; i < waves.size(); i++) {
			waves[i].S = max(0.0f, waves[i].S + waves[i].extraSpeed);
			waves[i].extraSpeed = 0;
			waves[i].updatePhi();
		}
	}
}

void Laborator8::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		camera->RotateThirdPerson_OY(-sensivityOX * deltaX);
		camera->RotateThirdPerson_OX(-sensivityOY * deltaY);
	}
}

void Laborator8::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator8::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator8::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator8::OnWindowResize(int width, int height)
{
}
