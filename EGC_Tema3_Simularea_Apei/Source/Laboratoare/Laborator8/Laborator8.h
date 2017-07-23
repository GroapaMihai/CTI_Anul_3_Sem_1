#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <time.h>
#include "LabCamera.h"
#include "WireFrame.h"
#define wavePeriod 20
#define MAX_NUMBER_WAVES 10

class Laborator8 : public SimpleScene
{
	struct GerstnerWave
	{
		float A = 1.1f;
		float L = 10;
		float w = 2 * 3.14159265f / L;
		float S = 0.005f;
		float phi = S * w;
	};

	struct CircularWave
	{
		glm::vec3 center;
		float A = 1.1f;
		float L = 1.25f;
		float w = 2 * 3.14159265f / L;
		float S = 0.0015f;
		float phi = S * w;
		float extraSpeed = 0;
		clock_t creationTime;
		float attenuation = A / wavePeriod;	// trebuie inmultit cu deltaTimeSeconds

		void updatePhi() {
			phi = S * w;
		}
	};

public:
	Laborator8();
	~Laborator8();

	void Init() override;

private:
	void FrameStart() override;
	void MoveWaterDrops(float deltaTimeSeconds);
	void removeWeakWaves();
	void attenuateWaves(float deltaTimeSeconds);
	void Update(float deltaTimeSeconds) override;

	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	Laborator::Camera *camera;
	float cameraSpeed;
	glm::mat4 projectionMatrix;
	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
	int spotLight;
	float angle_x;
	float angle_y;
	float cut_off;
	WireFrame* wf;
	bool wire;
	glm::vec3 waterDropsSource;
	std::vector<glm::vec3> waterDrops;
	std::vector<CircularWave> waves;
	int gerstnerWaves;
	GerstnerWave gerstnerWave;
};
