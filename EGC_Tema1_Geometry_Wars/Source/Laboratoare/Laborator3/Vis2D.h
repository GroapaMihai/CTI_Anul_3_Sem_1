#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Core/Engine.h>
#include "MyRectangle.h"
#include "Ship.h"
#include "PlayerShip.h"
#include "Bullet.h"
#include "Heart.h"
#include "Star.h"
#include "Shield.h"
#include "MyColor.h"
#include "Circle.h"

class Vis2D : public SimpleScene
{
	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

	public:
		Vis2D();
		~Vis2D();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void MoveShip();
		void SpawnEnemy();
		void DrawEnemies();
		void DrawLifes();
		void DrawStarGunIcon();
		void DrawCircle(std::vector<Point*> p, double centerX, double centerY, glm::vec3 col);
		void AddExtraLife();
		void AddStarGun();
		void AddShield();
		void AddBullets();
		void Collisions();
		void DrawScene();

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	protected:
		MyColor color;
		ViewportSpace viewSpace;
		glm::mat3 modelMatrix;
		glm::vec2 resolution;
		PlayerShip* playerShip;
		std::vector<Ship*> enemies;
		std::vector<Bullet*> bullets;
		std::vector<int> bulletsToRemove;
		std::vector<double> possibleEnemySpeeds;
		std::vector<bool> keyIsPressed;
		bool gameOver;
		double redIntensity;
		double timeOfGameOver;
		double timeOfLastSpawn;
		double spawnRadius;
		double spawnInterval;
		Heart* extraLife;
		Star* starGun;
		Shield* shield;
		int abilityType;
		double timeOfLastAbility;
		double abilitySpawnInterval;
};
