#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <regex>
#include "Player.h"
#include "Animation.h"

class Laborator9 : public SimpleScene
{
	public:
		Laborator9();
		~Laborator9();

		void Init() override;
		void LoadAnimations(std::string fileName, Player* player);
		glm::vec2 getUV(std::string line);
		std::string getStringBetween(std::string oStr, std::string left, std::string right);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void RenderIchigo(float deltaTimeSeconds);
		void RenderMenos(float deltaTimeSeconds);
		int getAnimationSpeed(std::string animationName, double movingTime);
		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* texture1 = NULL);
		void Collision(bool ichigoAttack, bool menosAttack);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void MovePlayerBackwards(Player* player, float deltaTimeSeconds);

		std::unordered_map<std::string, Texture2D*> mapTextures;
		Player* ichigo;
		Player* menos;
		int indexAnimation1 = 0;
		int indexAnimation2 = 0;
		double movingTimeIchigo = 0;
		double movingTimeMenos = 0;
		float sceneWidth = 14.5f;
		glm::vec3 ichigoScaleFactor;
		glm::vec3 menosScaleFactor;
};
