#include "BuildAndSurvive.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// cele 4 colturi ale labirintului
glm::vec3 BuildAndSurvive::initialCheckpoint = glm::vec3(-7.5, 0, -7.5);
glm::vec3 BuildAndSurvive::secondCheckpoint = glm::vec3(-initialCheckpoint.x, 0, initialCheckpoint.z);
glm::vec3 BuildAndSurvive::thirdCheckpoint = glm::vec3(initialCheckpoint.x, 0, -initialCheckpoint.z);
glm::vec3 BuildAndSurvive::fourthCheckpoint = glm::vec3(-initialCheckpoint.x, 0, -initialCheckpoint.z);

BuildAndSurvive::BuildAndSurvive()
{
	timeOfLastSpawn = 0;
	spawnInterval = 5;
	enemyHealth = 100;
	lifeAngle = 0;
	gameOver = false;
	build = false;
	timeOfLastMiniTower = 0;
	miniTowerSpawnInterval = 30;
	initialMiniCameraPosition = glm::vec3(0, 12, 0.05f);
	availableTowers = 0;
}

BuildAndSurvive::~BuildAndSurvive()
{
}

void BuildAndSurvive::Init()
{
	// creare jucator
	player = new Player("rabbit", glm::vec3(0), 2);

	// camera folosita pentru viewport-ul mare
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 1.5f, 3.5f), glm::vec3(0, 1.5f, 0), glm::vec3(0, 1, 0));

	// camera situata deasupra scenei (folosita la minimap)
	miniCamera = new Laborator::Camera();
	miniCamera->Set(initialMiniCameraPosition, player->getPosition(), glm::vec3(0, 1, 0));

	// camera folosita la modul build
	buildCamera = new Laborator::Camera();
	buildCamera->Set(initialMiniCameraPosition, glm::vec3(0), glm::vec3(0, 1, 0));

	cameraSpeed = 0.075f;

	// incarcare meshe
	LoadMeshes();

	// adaugare turnuri
	float scale = 0.0025f;
	towers.push_back((new Tower(glm::vec3(-3, 0, 0), scale)));
	towers.push_back((new Tower(glm::vec3(3, 0, 0), scale)));
	towers.push_back((new Tower(glm::vec3(0, 0, -3), scale)));

	// initializare checkpoints
	checkpoints.push_back(glm::vec3(initialCheckpoint.x, 0, initialCheckpoint.z));
	checkpoints.push_back(glm::vec3(secondCheckpoint.x, 0, secondCheckpoint.z));
	checkpoints.push_back(glm::vec3(thirdCheckpoint.x, 0, thirdCheckpoint.z));
	checkpoints.push_back(glm::vec3(fourthCheckpoint.x, 0, fourthCheckpoint.z));

	// initializare viata rotita in jurul axei OX
	Life* l = new Life();
	l->setDisplacement(glm::vec3(0, 0.9, 0));
	l->setAxis('X');
	lifes.push_back(l);

	// initializare viata rotita in jurul axei OZ
	l = new Life();
	l->setDisplacement(glm::vec3(0, 0.75, 0));
	l->setAxis('Z');
	lifes.push_back(l);

	// initializare viata rotita in jurul axei OY
	l = new Life();
	l->setDisplacement(glm::vec3(0.85, 0, 0));
	l->setAxis('Y');
	lifes.push_back(l);

	// setarea celor trei matrici de vizualizare (ortho este folosita la minimap)
	perspectiveMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	orthoMatrix = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, 0.1f, 100.0f);
	buildOrthoMatrix = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, 0.1f, 100.0f);
}

void BuildAndSurvive::LoadMeshes()
{
	Mesh* mesh = new Mesh("tower");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tower.obj");
	meshes[mesh->GetMeshID()] = mesh;

	Mesh* mesh2 = new Mesh("dog");
	mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "dog.obj");
	meshes[mesh2->GetMeshID()] = mesh2;

	Mesh* mesh3 = new Mesh("rabbit");
	mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "rabbit.obj");
	meshes[mesh3->GetMeshID()] = mesh3;

	Mesh* mesh4 = new Mesh("sphere");
	mesh4->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[mesh4->GetMeshID()] = mesh4;

	Mesh* mesh5 = new Mesh("plane");
	mesh5->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
	meshes[mesh5->GetMeshID()] = mesh5;

	Mesh* mesh6 = new Mesh("box");
	mesh6->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh6->GetMeshID()] = mesh6;
}

void BuildAndSurvive::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BuildAndSurvive::AddEnemy()
{
	Enemy* e = new Enemy("dog", initialCheckpoint, Enemy::initialScale, RADIANS(90), enemyHealth);
	e->setSpeed(1.5f);
	enemies.push_back(e);
	timeOfLastSpawn = Engine::GetElapsedTime();
}

void BuildAndSurvive::DrawTowers()
{
	Tower* t;

	// Randare turnuri
	for (int i = 0; i < towers.size(); i++)
	{
		t = towers[i];
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, t->getPosition());
		t->setModelMatrix(modelMatrix);

		if (build)
			DrawOrthoTower(t, "build");
		else
		{
			modelMatrix = glm::scale(modelMatrix, glm::vec3(t->getScale()));
			RenderMesh(meshes["tower"], shaders["VertexNormal"], modelMatrix, "BigViewport");
		}
	}
}

void BuildAndSurvive::DrawMiniTowers()
{
	Tower* t;

	// Randare mini-turnuri
	for(std::vector<Tower*>::iterator it0 = miniTowers.begin(); it0 != miniTowers.end();)
	{
		t = (*it0);
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, t->getPosition());
		t->setModelMatrix(modelMatrix);

		// desenez mini-turnuri doar in viewport mare (nu si in modul build)
		if (!build)
		{
			modelMatrix = glm::scale(modelMatrix, glm::vec3(t->getScale()));
			RenderMesh(meshes["tower"], shaders["VertexNormal"], modelMatrix, "BigViewport");
		}

		// verific daca mini-turnul a fost colectat de player
		if (!gameOver && Collected(t))
		{
			it0 = miniTowers.erase(it0);
			availableTowers++;
		}
		else
			++it0;
	}
}

void BuildAndSurvive::DrawCheckpoints()
{
	// Randarea celor patru checkpoints
	for (int i = 0; i < checkpoints.size(); i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, checkpoints[i]);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f));
		RenderMesh(meshes["plane"], shaders["VertexNormal"], modelMatrix, "BigViewport");
	}
}

void BuildAndSurvive::DrawPlayer()
{
	float u = 270 - player->getAngle();

	// randare player + verificare sfarsit joc, astfel incat sa se realizeze caderea
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, player->getPosition());
	if (gameOver)
		modelMatrix = glm::rotate(modelMatrix, player->getFallingAngle(), glm::vec3(1, 1, 1));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(u), glm::vec3(0, 1, 0));
	player->setModelMatrix(modelMatrix);

	if (build)
		DrawOrthoPlayer("build");
	else
	{
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.25f));
		RenderMesh(meshes[player->getName()], shaders["VertexNormal"], modelMatrix, "BigViewport");
	}
}

void BuildAndSurvive::DrawLifes()
{
	glm::vec3 position;
	Life* l;
	char axis;

	for (int i = 0; i < lifes.size(); i++)
	{
		l = lifes[i];
		axis = l->getAxis();
		position = player->getPosition();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, 0.7, position.z));

		// rotatiile fata de axele jucatorului
		if (axis == 'X')
		{
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-player->getAngle()), glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(lifeAngle), glm::vec3(0, 0, 1));
		}
		else if (axis == 'Z') {
			modelMatrix = glm::rotate(modelMatrix, RADIANS(360 - player->getAngle()), glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(lifeAngle), glm::vec3(0, 0, 1));
		} 
		else
			modelMatrix = glm::rotate(modelMatrix, RADIANS(lifeAngle), glm::vec3(0, 1, 0));

		modelMatrix = glm::translate(modelMatrix, lifes[i]->getDisplacement());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
		RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix, "BigViewport");
	}
}

void BuildAndSurvive::DrawEnemies(float deltaTimeSeconds)
{
	Enemy* e;
	glm::vec3 position;
	bool erased;
	float distance, dX, dZ;

	// randare inamici + miscare in labirint + eliminare daca a ajuns la capatul culoarului
	for (std::vector<Enemy*>::iterator it0 = enemies.begin(); it0 != enemies.end();)
	{
		e = (*it0);
		position = e->getPosition();
		erased = false;

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, e->getPosition());
		modelMatrix = glm::rotate(modelMatrix, e->getAngle(), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, 0.5f * e->getFallingAngle(), glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, -e->getFallingAngle(), glm::vec3(1, 0, 0));
		e->setModelMatrix(modelMatrix);

		if (build)
			DrawOrthoEnemy(e, "build");
		else
		{
			modelMatrix = glm::scale(modelMatrix, glm::vec3(e->getScale()));
			RenderMesh(meshes[e->getName()], shaders["VertexNormal"], modelMatrix, "BigViewport");
		}

		if (!gameOver && !e->isDead())
		{
			if (e->getSegment() == 1)
			{
				// daca nu a ajuns la capatul segmentului, continua sa se miste
				// altfel, se roteste in directia urmatorului segment
				if (position.x <= secondCheckpoint.x)
				{
					position.x += e->getSpeed() * deltaTimeSeconds;
					e->setPosition(position);
				}
				else
					e->updateAngle(initialCheckpoint.x, initialCheckpoint.z);
			}
			else if (e->getSegment() == 2)
			{
				dX = thirdCheckpoint.x - position.x;
				dZ = thirdCheckpoint.z - position.z;
				distance = sqrt(dX * dX + dZ * dZ);

				dX /= distance;
				dZ /= distance;

				// daca nu a ajuns la capatul segmentului, continua sa se miste pe diagonala
				// altfel, se roteste in directia urmatorului segment
				if (position.x >= thirdCheckpoint.x && position.z <= thirdCheckpoint.z)
				{
					position.x += dX * e->getSpeed() * deltaTimeSeconds;
					position.z += dZ * e->getSpeed() * deltaTimeSeconds;
					e->setPosition(position);
				}
				else
					e->updateAngle(initialCheckpoint.x, initialCheckpoint.z);
			}
			else if (e->getSegment() == 3)
			{
				// daca nu a ajuns la capatul culoarului, continua sa se miste
				// altfel, dispare si scad o viata jucatorului
				// daca jucatorul are 0 vieti, realizez efectul de cadere laterala
				if (position.x <= fourthCheckpoint.x)
				{
					position.x += e->getSpeed() * deltaTimeSeconds;
					e->setPosition(position);
				}
				else
				{
					it0 = enemies.erase(it0);
					erased = true;
					
					if (!lifes.empty())
						lifes.erase(lifes.begin());
				}
			}
		}

		if (!erased)
			++it0;
	}
}

void BuildAndSurvive::TowerShoot()
{
	Tower* t;
	Enemy* e;
	Projectile* p;
	glm::vec3 towerPosition, enemyPosition, destination;
	int i, j;
	double dX, dZ, distance, angle, minDistance = 2 * fourthCheckpoint.x;

	// alegere inamic cel mai apropiat de turn + creare proiectil
	for (i = 0; i < towers.size(); i++)
	{
		t = towers[i];
		towerPosition = t->getPosition();

		// creez un proiectil nou si il adaug in scena
		if ((Engine::GetElapsedTime() - t->getTimeOfLastShoot()) >= Tower::shootingInterval)
		{
			// calculez distanta fata de inamici
			for (j = 0; j < enemies.size(); j++)
			{
				e = enemies[j];

				if (!e->isDead())
				{
					t->setTimeOfLastShoot(Engine::GetElapsedTime());
					enemyPosition = e->getPosition();

					dX = enemyPosition.x - towerPosition.x;
					dZ = enemyPosition.z - towerPosition.z;
					distance = sqrt(dX * dX + dZ * dZ);

					// am gasit un inamic mai apropiat, ii salvez pozitia
					if (distance < minDistance)
					{
						minDistance = distance;
						destination = enemyPosition;
					}
				}
			}

			// creare proiectil
			if (minDistance < (2 * fourthCheckpoint.x))
			{
				towerPosition = glm::vec3(towerPosition.x, 0.9, towerPosition.z);
				angle = atan2(destination.z - towerPosition.z, destination.x - towerPosition.x);
				p = new Projectile(towerPosition, angle, 25, 2.5f);
				p->setSpeed(3);
				p->setScale(0.2f);
				p->setType(0);
				projectiles.push_back(p);
			}
		}
	}
}

void BuildAndSurvive::MoveProjectile(float deltaTimeSeconds)
{
	float dX, dZ, distance;
	Projectile *p;
	Enemy* e;
	glm::vec3 position;
	int i;
	bool collision;
	double time;

	// randare proiectile + verificare coliziuni + eliminarea proiectilelor ce ating tinta +
	// scadere viata / eliminare inamic lovit + eliminarea proiectilelor ce au parasit spatiul +
	// miscare proiectile (inclusiv grenadele trase cu bolta)
	for (std::vector<Projectile*>::iterator it0 = projectiles.begin(); it0 != projectiles.end();)
	{
		p = (*it0);
		position = p->getPosition();

		// desenez proiectilul
		if (!build)
		{
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(p->getScale()));
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, "BigViewport");
		}

		// daca player-ul a murit, nu mai verific coliziuni
		// altfel, parcurg vectorul de inamici si verific daca vreunul e lovit de proiectil
		if (gameOver)
			++it0;
		else
		{
			collision = false;
			for (i = 0; i < enemies.size(); i++)
			{
				e = enemies[i];

				// daca proiectilul loveste un inamic, il sterg sau ii scad viata
				if (!e->isDead() && Collision(e, p))
				{
					it0 = projectiles.erase(it0);
					collision = true;
					e->decreaseHealth(p->getDamage());

					if (e->isDead())
						e->setTimeOfDead(Engine::GetElapsedTime());
				}
			}

			if (!collision)
			{
				// daca proiectilul nu a lovit inamic si a iesit din scena, il sterg
				// altfel, ii calculez noua pozitie
				if (OutOfBounds(position, p->getBound()))
					it0 = projectiles.erase(it0);
				else
				{
					dX = (float)cos(p->getAngle());
					dZ = (float)sin(p->getAngle());

					distance = sqrt(dX * dX + dZ * dZ);
					dX /= distance;
					dZ /= distance;

					position.x += dX * p->getSpeed() * deltaTimeSeconds;
					position.z += dZ * p->getSpeed() * deltaTimeSeconds;

					// daca am grenada, trag cu "bolta"
					// Vy = Vy_0 - g * t
					// y = 0.5 * (Vy_0 + Vy) * t
					if (p->getType() == 3)
					{
						time = Engine::GetElapsedTime() - p->getTimeOfLaunch();
						position.y = (float) (0.75 + 0.5 * (Projectile::Vy_0 + p->getVelocity_Y(time)) * time);
					}

					p->setPosition(position);

					++it0;
				}
			}
		}
	}
}

bool BuildAndSurvive::OutOfBounds(glm::vec3 position, float bound)
{
	// verificare ca un proiectil a parasit cu un anumit factor spatiul
	if (position.y < 0)
		return true;

	if (position.x < (bound * initialCheckpoint.x))
		return true;

	if (position.x > (bound * fourthCheckpoint.x))
		return true;

	if (position.z < (bound * initialCheckpoint.z))
		return true;

	if (position.z > (bound * fourthCheckpoint.z))
		return true;

	return false;
}

bool BuildAndSurvive::Collision(Enemy* e, Projectile* p)
{
	// verificare coliziune proiectil - inamic
	// pentru inamic (caine) am ales ca raza diagonala obtinuta in planul XOZ
	// pentru proiectil (sfera) am ales-o in functie de dimensiunea initiala + scalare
	float rA = Enemy::diagonal / 2;
	float rB = p->getScale() / 2;
	glm::vec3 enemyPosition = e->getPosition();
	glm::vec3 projectilePosition = p->getPosition();

	float dX = enemyPosition.x - projectilePosition.x;
	float dZ = enemyPosition.z - projectilePosition.z;
	dX *= dX;	dZ *= dZ;

	if ((dX + dZ) < ((rA + rB) * (rA + rB)))
		return true;

	return false;
}

bool BuildAndSurvive::Collected(Tower* miniTower)
{
	float rA = 100 * miniTower->getScale();
	float rB = Player::radius;
	glm::vec3 playerPosition = player->getPosition();
	glm::vec3 miniTowerPosition = miniTower->getPosition();

	float dX = playerPosition.x - miniTowerPosition.x;
	float dZ = playerPosition.z - miniTowerPosition.z;
	dX *= dX;	dZ *= dZ;

	if ((dX + dZ) < ((rA + rB) * (rA + rB)))
		return true;

	return false;
}

void BuildAndSurvive::RotateThirdPerson_OY(int deltaX)
{
	float slowdown = 0.1f;
	float angle;

	player->updateAngle(slowdown * deltaX);
	angle = RADIANS(player->getAngle());

	// roteste camera TPS ai sa fie pozitionata in spatele player-ului si pe directia acestuia
	float pX = player->getPosition().x;
	float pZ = player->getPosition().z;
	float x = pX + camera->distanceToTarget * cos(angle);
	float z = pZ + camera->distanceToTarget * sin(angle);
	camera->Set(glm::vec3(x, 1.5f, z), glm::vec3(pX, 1.5f, pZ), glm::vec3(0, 1, 0));
}

void BuildAndSurvive::RotateFirstPerson_OY(int deltaX)
{
	float slowdown = 0.1f;
	float angle;

	player->updateAngle(slowdown * deltaX);
	angle = RADIANS(player->getAngle());

	// - camera FPS e situata putin in fata player-ului, rotita in directia sa si
	// are ca target un punct din fata, aflat la distanta 'camera->distanceToTarget'
	// - crearea efectului de zoom al camerei FPS
	float pX = player->getPosition().x - 0.5f * cos(angle);
	float pZ = player->getPosition().z - 0.5f * sin(angle);
	float x = pX - camera->distanceToTarget * cos(angle);
	float z = pZ - camera->distanceToTarget * sin(angle);
	camera->Set(glm::vec3(pX, 1.5f, pZ), glm::vec3(x, 1.5f, z), glm::vec3(0, 1, 0));
}

void BuildAndSurvive::RemoveDeadEnemies(float deltaTimeSeconds)
{
	Enemy* e;
	bool erased;
	float scale = 0.0010f;

	// updateaza unghiul de cadere al inamicilor morti si factorul de scalare +
	// eliminarea lor definitiva la finalul animatiei de cadere
	for (std::vector<Enemy*>::iterator it0 = enemies.begin(); it0 != enemies.end();)
	{
		e = (*it0);
		erased = false;

		// daca inamicul a ramas fara vieti, realizez animatia de cadere si scalare
		if (e->isDead())
		{
			if ((Engine::GetElapsedTime() - e->getTimeOfDead()) < Enemy::fallingInterval)
			{
				e->updateFallingAngle(Enemy::fallingSpeed * deltaTimeSeconds);
				e->shrink(Enemy::initialScale * deltaTimeSeconds / Enemy::fallingInterval);
			}
			else
			{
				// adaug un miniTower in locul inamicului mort
				if ((Engine::GetElapsedTime() - timeOfLastMiniTower) >= miniTowerSpawnInterval)
				{
					timeOfLastMiniTower = Engine::GetElapsedTime();
					miniTowers.push_back(new Tower(e->getPosition(), scale));
				}

				it0 = enemies.erase(it0);
				erased = true;
			}
		}

		if (!erased)
			++it0;
	}
}

void BuildAndSurvive::DrawScene(float deltaTimeSeconds)
{
	glm::vec3 position;

	// verificare incheiere joc
	if (lifes.empty() && !gameOver)
	{
		gameOver = true;
		timeOfGameOver = Engine::GetElapsedTime();
	}

	// asigura desfasurarea jocului in viewport-ul mare
	if (!gameOver)
	{
		// adaugare inamici
		if ((Engine::GetElapsedTime() - timeOfLastSpawn) >= spawnInterval)
			AddEnemy();

		lifeAngle = (lifeAngle + 2) % 360;

		// eliminare inamici morti
		RemoveDeadEnemies(deltaTimeSeconds);
	} 
	else
	{
		// setare unghi de cadere pentru player
		if (player->getFallingAngle() < 90)
			if ((Engine::GetElapsedTime() - timeOfGameOver) < Player::fallingInterval)
				player->updateFallingAngle(Player::fallingSpeed * deltaTimeSeconds);
	}

	// desenare turnuri
	DrawTowers();

	// desenare mini-turnuri
	DrawMiniTowers();

	// desenare checkpoints
	if(!build)
		DrawCheckpoints();

	// desenare personaj principal
	DrawPlayer();

	// desenare sfere care se rotesc in jurul personajului principal
	if(!gameOver && !build)
		DrawLifes();

	// desenare inamici
	DrawEnemies(deltaTimeSeconds);

	// turnurile trag in inamici
	if (!gameOver)
		TowerShoot();

	// miscare proiectile
	MoveProjectile(deltaTimeSeconds);

	// reduc treptat intervalul de spawn
	if (spawnInterval > 2.5 && !gameOver)
		spawnInterval -= 0.00015;

	// inamicii au viata din ce in ce mai mare
	if (enemyHealth < 500 && !gameOver)
		enemyHealth += 0.0005;
}

void BuildAndSurvive::DrawOrthoPlayer(string ViewportName)
{
	glm::mat4 matrix;
	matrix = player->getModelMatrix();
	matrix = glm::scale(matrix, glm::vec3(1.25f));
	matrix = glm::rotate(matrix, RADIANS(90), glm::vec3(1, 0, 0));
	RenderMesh(meshes["box"], shaders["VertexNormal"], matrix, ViewportName);
}

void BuildAndSurvive::DrawOrthoTower(Tower* t, string ViewportName)
{
	glm::mat4 matrix;
	matrix = t->getModelMatrix();
	RenderMesh(meshes["box"], shaders["VertexNormal"], matrix, ViewportName);
}

void BuildAndSurvive::DrawOrthoEnemy(Enemy* e, string ViewportName)
{
	glm::mat4 matrix;
	matrix = e->getModelMatrix();
	matrix = glm::rotate(matrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderMesh(meshes["box"], shaders["VertexNormal"], matrix, ViewportName);
}

void BuildAndSurvive::DrawMinimap()
{
	int i;
	glm::mat4 matrix;

	// desenare player in minimap
	DrawOrthoPlayer("minimap");

	// desenare turnuri in minimap
	for (i = 0; i < towers.size(); i++)
		DrawOrthoTower(towers[i], "minimap");

	// desenare inamici in minimap
	for (i = 0; i < enemies.size(); i++)
		DrawOrthoEnemy(enemies[i], "minimap");
}

void BuildAndSurvive::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// modul build consta intr-un singur viewport cu proiectie ortho
	if(build)
	{
		glViewport(0, 0, resolution.x, resolution.y);
		DrawScene(deltaTimeSeconds);
		DrawCoordinatSystem(buildCamera->GetViewMatrix(), buildOrthoMatrix);
	}
	else
	{
		// randare Viewport mare
		glViewport(0, 0, resolution.x, resolution.y);
		DrawScene(deltaTimeSeconds);
		DrawCoordinatSystem(camera->GetViewMatrix(), perspectiveMatrix);

		// setez Viewport-ul mic la "suprafata"
		glScissor(1070, 20, 180, 180);
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		// randare Viewport minimap
		glViewport(1070, 20, 180, 180);
		DrawMinimap();
		DrawCoordinatSystem(miniCamera->GetViewMatrix(), orthoMatrix);
	}
}

void BuildAndSurvive::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, string ViewportName)
{
	if (!mesh || !shader)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	
	// pentru minimap, inlocuiesc personajele cu "boxes" si folosesc matricea "ortho"
	if (ViewportName == "minimap")
	{
		glUniformMatrix4fv(shader->loc_view_matrix, 1, false, glm::value_ptr(miniCamera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, false, glm::value_ptr(orthoMatrix));
	}
	else if(ViewportName == "build")
	{
		glUniformMatrix4fv(shader->loc_view_matrix, 1, false, glm::value_ptr(buildCamera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, false, glm::value_ptr(buildOrthoMatrix));
	}
	else
	{
		glUniformMatrix4fv(shader->loc_view_matrix, 1, false, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, false, glm::value_ptr(perspectiveMatrix));
	}

	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void BuildAndSurvive::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (!gameOver && !build && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float angle;
		glm::vec3 position;
		float speed = player->getSpeed();

		if (window->KeyHold(GLFW_KEY_W)) {
			angle = player->getAngle() - 90;
			player->updateCenterX(glm::sin(RADIANS(angle)) * speed * deltaTime);
			player->updateCenterZ(-glm::cos(RADIANS(angle)) * speed * deltaTime);
			camera->TranslateForward(speed * deltaTime);
			position = player->getPosition();
			miniCamera->Set(position + initialMiniCameraPosition, position, glm::vec3(0, 1, 0));
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			angle = player->getAngle();
			player->updateCenterX(-glm::sin(RADIANS(angle)) * speed * deltaTime);
			player->updateCenterZ(glm::cos(RADIANS(angle)) * speed * deltaTime);
			camera->TranslateRight(-speed * deltaTime);
			position = player->getPosition();
			miniCamera->Set(position + initialMiniCameraPosition, position, glm::vec3(0, 1, 0));
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			angle = player->getAngle() - 90;
			player->updateCenterX(-glm::sin(RADIANS(angle)) * speed * deltaTime);
			player->updateCenterZ(glm::cos(RADIANS(angle)) * speed * deltaTime);
			camera->TranslateForward(-speed * deltaTime);
			position = player->getPosition();
			miniCamera->Set(position + initialMiniCameraPosition, position, glm::vec3(0, 1, 0));
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			angle = player->getAngle();
			player->updateCenterX(glm::sin(RADIANS(angle)) * speed * deltaTime);
			player->updateCenterZ(-glm::cos(RADIANS(angle)) * speed * deltaTime);
			camera->TranslateRight(speed * deltaTime);
			position = player->getPosition();
			miniCamera->Set(position + initialMiniCameraPosition, position, glm::vec3(0, 1, 0));
		}
	}
}

void BuildAndSurvive::OnKeyPress(int key, int mods)
{
	// alegere arme
	if (!gameOver && !build)
	{
		if (key == GLFW_KEY_1) {
			player->setCurrentGun(1);
			RotateThirdPerson_OY(0);
		}
		else if (key == GLFW_KEY_2) {
			player->setCurrentGun(2);
			RotateFirstPerson_OY(0);
		}
		else if (key == GLFW_KEY_3) {
			player->setCurrentGun(3);
			RotateThirdPerson_OY(0);
		}
	}

	if (key == GLFW_KEY_B)
		build = !build;
}

void BuildAndSurvive::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void BuildAndSurvive::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (!gameOver && !build && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;
		
		if (player->getCurrentGun() == 2)
			RotateFirstPerson_OY(deltaX);
		else
			RotateThirdPerson_OY(deltaX);
	}
}

void BuildAndSurvive::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1 && !gameOver)
	{
		if (!build)
		{
			Projectile* p;
			double angle = player->getAngle() - 180;
			glm::vec3 position = player->getPosition();
			position = glm::vec3(position.x, 0.75f, position.z);

			// Pistol
			if (player->getCurrentGun() == 1)
				if ((Engine::GetElapsedTime() - player->getTimeOfLastPistolShoot()) > Projectile::pistolShootInterval)
				{
					player->setTimeOfLastPistolShoot(Engine::GetElapsedTime());
					p = new Projectile(position, RADIANS(angle), 30, 2.5f);
					p->setSpeed(4);
					p->setScale(0.2f);
					p->setType(1);
					projectiles.push_back(p);
				}

			// Pusca
			if (player->getCurrentGun() == 2)
				if ((Engine::GetElapsedTime() - player->getTimeOfLastSniperShoot()) > Projectile::sniperShootInterval)
				{
					player->setTimeOfLastSniperShoot(Engine::GetElapsedTime());
					p = new Projectile(position, RADIANS(angle), 15, 2.5f);
					p->setSpeed(6);
					p->setScale(0.2f);
					p->setType(2);
					projectiles.push_back(p);
				}

			// Grenada
			if (player->getCurrentGun() == 3)
				if ((Engine::GetElapsedTime() - player->getTimeOfLastGrenadeShoot()) > Projectile::grenadeShootInterval)
				{
					player->setTimeOfLastGrenadeShoot(Engine::GetElapsedTime());
					p = new Projectile(position, RADIANS(angle), 50, 2.5f);
					p->setSpeed(3);
					p->setScale(0.4f);
					p->setType(3);
					p->setTimeOfLaunch(Engine::GetElapsedTime());
					projectiles.push_back(p);
				}
		}
		else if(availableTowers > 0)
		{
			glm::ivec2 resolution = window->GetResolution();
			float size = 0.0025f;		
			float x = (float) (25 * mouseX) / (resolution.x / 2) - 25;
			float z = (float) (25 * mouseY) / (resolution.y / 2) - 25;
			towers.push_back(new Tower(glm::vec3(x, 0, z), size));
			availableTowers--;
		}
	}
}

void BuildAndSurvive::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void BuildAndSurvive::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BuildAndSurvive::OnWindowResize(int width, int height)
{
}