#pragma once

#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include "Tower.h"
#include "Enemy.h"
#include "Life.h"
#include "Player.h"
#include "Projectile.h"

class BuildAndSurvive : public SimpleScene
{
	public:
		BuildAndSurvive();
		~BuildAndSurvive();

		void Init() override;
		void LoadMeshes();

	private:
		void FrameStart() override;
		void AddEnemy();
		void DrawTowers();
		void DrawMiniTowers();
		void DrawCheckpoints();
		void DrawPlayer();
		void DrawLifes();
		void DrawEnemies(float deltaTimeSeconds);
		void TowerShoot();
		void MoveProjectile(float deltaTimeSeconds);
		bool OutOfBounds(glm::vec3 position, float bound);
		bool Collision(Enemy* e, Projectile* p);
		bool Collected(Tower* miniTower);
		void RotateThirdPerson_OY(int deltaX);
		void RotateFirstPerson_OY(int deltaX);
		void RemoveDeadEnemies(float deltaTimeSeconds);
		void DrawScene(float deltaTimeSeconds);
		void DrawOrthoPlayer(std::string ViewportName);
		void DrawOrthoTower(Tower* t, std::string ViewportName);
		void DrawOrthoEnemy(Enemy* e, std::string ViewportName);
		void DrawMinimap();
		void Update(float deltaTimeSeconds);

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, std::string ViewportName);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera *camera;
		Laborator::Camera *miniCamera;
		Laborator::Camera *buildCamera;
		glm::vec3 initialMiniCameraPosition;
		float cameraSpeed;
		glm::mat4 modelMatrix;
		glm::mat4 perspectiveMatrix;
		glm::mat4 orthoMatrix;
		glm::mat4 buildOrthoMatrix;
		std::vector<Tower*> towers;
		std::vector<Enemy*> enemies;
		std::vector<glm::vec3> checkpoints;
		double timeOfLastSpawn;
		double spawnInterval;
		double enemyHealth;
		int lifeAngle;
		std::vector<Life*> lifes;
		Player* player;
		bool gameOver;
		double timeOfGameOver;
		bool build;
		double timeOfLastMiniTower;
		double miniTowerSpawnInterval;
		std::vector<Tower*> miniTowers;
		std::vector<Projectile*> projectiles;
		int availableTowers;
		static glm::vec3 initialCheckpoint;
		static glm::vec3 secondCheckpoint;
		static glm::vec3 thirdCheckpoint;
		static glm::vec3 fourthCheckpoint;
};

