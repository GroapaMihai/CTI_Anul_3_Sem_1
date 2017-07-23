#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Vis2D.h"

using namespace std;

Vis2D::Vis2D()
{
	gameOver = false;
	redIntensity = 0;
	timeOfLastSpawn = 0;
	timeOfLastAbility = 0;
	spawnInterval = 2;
	abilitySpawnInterval = 4;
	srand((unsigned int)time(NULL));
    resolution = window->GetResolution();
	glm::vec2 center = glm::vec2(resolution.x / 2, resolution.y / 2);

	playerShip = new PlayerShip("ship", center, 3.75, color.cyan);
	extraLife = new Heart("heart", color.magenta);
	starGun = new Star("star", color.violet);
	shield = new Shield(color.orange);

	// vector in care retin posibile valori 
	// pentru viteza navelor inamice
	double value = 0.5;
	while (true)
	{
		if (value >= 1.6)
			break;

		possibleEnemySpeeds.push_back(value);
		value += 0.05;
	}

	// 0 -> W
	// 1 -> A
	// 2 -> S
	// 3 -> D
	// initial tastele de miscare nu sunt apasate
	for (int i = 0; i < 4; i++)
		keyIsPressed.push_back(false);
}

Vis2D::~Vis2D()
{
}

void Vis2D::Init()
{
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	cameraInput->SetActive(false);

	// calculez raza cercului virtual pe care o sa apara inamicii
	spawnRadius += resolution.x * resolution.x / 4;
	spawnRadius += resolution.y * resolution.y / 4;
	spawnRadius = sqrt(spawnRadius);

	// adaugare meshe
	AddMeshToList(playerShip->CreateMesh());
	AddMeshToList((new MyRectangle("life", 2 * Bullet::bulletLength, Bullet::bulletWidth, color.yellow))->CreateMesh());
	AddMeshToList((new Bullet("bullet", color.yellow))->CreateMesh());
	AddMeshToList(extraLife->CreateMesh());
	AddMeshToList(starGun->CreateMesh());
	AddMeshToList((new Point("point", Shield::smallPointRadius, color.orange))->CreateMesh());
}

void Vis2D::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	camera->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	camera->Update();
}

void Vis2D::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Vis2D::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	double duration, step;

	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);

	// daca jocul nu e incheiat, fundalul este negru
	// altfel, ecranul devine treptat rosu prin o animatie de 2s
	if(!gameOver)
		SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);
	else
	{
		// cresc intensitatea culorii rosu la fiecare cadru pana la pragul 1
		step = deltaTimeSeconds / 2;
		duration = Engine::GetElapsedTime() - timeOfGameOver;
		if (duration <= 2)
			redIntensity += step;
		else
			redIntensity = 1;

		SetViewportArea(viewSpace, glm::vec3(redIntensity, 0, 0), true);
	}

	DrawScene();
}

void Vis2D::FrameEnd()
{

}

void Vis2D::MoveShip()
{
	// aceasta functie asigura miscarea continua a navei la apasarea tastelor
	if (keyIsPressed[0])
		playerShip->updateCenterY(playerShip->getSpeed());
	if (keyIsPressed[1])
		playerShip->updateCenterX(-playerShip->getSpeed());
	if (keyIsPressed[2])
		playerShip->updateCenterY(-playerShip->getSpeed());
	if (keyIsPressed[3])
		playerShip->updateCenterX(playerShip->getSpeed());
}

void Vis2D::SpawnEnemy()
{
	int shipType;
	double enemySpeed, enemyCenterX, enemyCenterY;
	double duration, angle;
	glm::vec2 center;

	// daca este necesara aparitia unui nou inamic
	duration = Engine::GetElapsedTime() - timeOfLastSpawn;
	if (duration > spawnInterval)
	{
		// ii generez Random:
		// culoare (albastru sau galben)
		// viteza luata din vectorul de viteze posibile pentru inamici
		// o pozitie pe cercul virtual (in functie de unghi)
		timeOfLastSpawn = Engine::GetElapsedTime();
		shipType = std::rand() % 2;
		enemySpeed = std::rand() % possibleEnemySpeeds.size();
		enemySpeed = possibleEnemySpeeds.at(enemySpeed);
		angle = RADIANS(std::rand() % 360);
		enemyCenterX = resolution.x / 2 + spawnRadius * cos(angle);
		enemyCenterY = resolution.y / 2 + spawnRadius * sin(angle);
		center = glm::vec2(enemyCenterX, enemyCenterY);

		// adaug o nava albastra pentru 0 si galbena pentru 1
		if (shipType == 0)
			enemies.push_back(new Ship("blueShip", center, enemySpeed, color.blue));
		else
			enemies.push_back(new Ship("yellowShip", center, enemySpeed, color.yellow));
	}
}

void Vis2D::DrawEnemies()
{
	double enemyCenterX, enemyCenterY, angle;
	double dX, dY;
	double impactDistance = 4 * playerShip->getHeight() * playerShip->getHeight();
	double step = 0.032, scale;
	double enemyDistance;
	bool move;

	// parcurg tot vectorul de inamici si ii desenez
	for (std::vector<Ship*>::iterator it0 = enemies.begin(); it0 != enemies.end();)
	{
		// ii rotesc astfel incat sa fie cu fata spre nava jucator
		move = true;
		enemyCenterX = (*it0)->getCenterX();
		enemyCenterY = (*it0)->getCenterY();
		angle = atan2(playerShip->getCenterY() - enemyCenterY, playerShip->getCenterX() - enemyCenterX);

		modelMatrix = glm::mat3(1) * Transform2D::Translate(enemyCenterX, enemyCenterY);
		modelMatrix *= Transform2D::Rotate(angle);

		// scalez treptat pana la jumatate cu un step care depinde de durata unui frame
		if ((*it0)->getName() == "redShip") 
		{
			// daca nu au trecut cele 250ms scalez nava rosie pana la jumatate
			scale = (*it0)->getScaleFactor();
			if (((Engine::GetElapsedTime() - (*it0)->getTimeOfDestroy()) < 0.25) && scale > 0.5)
			{
				(*it0)->decrementScaleFactor(step);
				scale = (*it0)->getScaleFactor();
			}

			modelMatrix *= Transform2D::Scale(scale, scale);

			// pentru nava rosie, coliziunea are o raza mai mica
			impactDistance = playerShip->getHeight() + playerShip->getHeight() / 2;
			impactDistance *= impactDistance;
		}

		RenderMesh2D(meshes["ship"], modelMatrix, (*it0)->getColor());

		// verific coliziunea dintre nava si inamic
		// daca nava jucator are scutul activat, nu pierde viata
		// daca are loc impactul, elimin inamicul si scad o viata jucatorului
		// altfel, continui sa redesenez inamic in noua pozitie
		if (!gameOver)
		{
			dX = playerShip->getCenterX() - enemyCenterX;
			dY = playerShip->getCenterY() - enemyCenterY;
			enemyDistance = sqrt(dX * dX + dY * dY);

			if (((dX * dX + dY * dY) <= impactDistance) && !shield->isInUse())
			{
				playerShip->removeLife();
				if (playerShip->getLifes() == 0)
				{
					gameOver = true;
					timeOfGameOver = Engine::GetElapsedTime();
				}
				it0 = enemies.erase(it0);
			}
			else
			{
				// daca se foloseste scutul, inamicii nu pot trece de el
				if (shield->isInUse())
					if (enemyDistance <= (Shield::shieldRadius + playerShip->getHeight()))
						move = false;

				// daca navele sunt la o distanta mai mare decat raza scutului => pot inainta
				if (move)
				{
					dX /= enemyDistance;
					dY /= enemyDistance;

					enemyCenterX += dX * (*it0)->getSpeed();
					enemyCenterY += dY * (*it0)->getSpeed();

					(*it0)->setCenter(glm::vec2(enemyCenterX, enemyCenterY));
				}
				++it0;
			}
		}
		else
			++it0;
	}
}

// deseneaza pe ecran in dreapta sus vietile
void Vis2D::DrawLifes()
{
	double x = resolution.x - 2 * Bullet::bulletWidth;
	double y = resolution.y - 2 * Bullet::bulletLength;

	for (int i = 0; i < playerShip->getLifes(); i++)
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate(x - i * 1.75 * Bullet::bulletWidth, y);
		RenderMesh2D(meshes["life"], modelMatrix, color.yellow);
	}
}

// deseneaza pe ecran in dreapta sus (sub vieti) iconita starGun, cand e folosit
void Vis2D::DrawStarGunIcon()
{
	double x = resolution.x - 2 * Star::length;
	double y = resolution.y - 2 * Bullet::bulletLength - 4.3 * Star::length;

	// daca s-a terminat perioada de folosire
	if ((Engine::GetElapsedTime() - starGun->getTimeOfLastUse()) > Star::period)
		starGun->useStarGun(false);

	// daca e in folosire, il desenez violet (sau rosu daca e aproape consumat)
	if (starGun->isInUse())
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate(x, y);

		// daca jocul s-a incheiat si starGun e in folosire => ramane violet
		if(gameOver)
			RenderMesh2D(meshes["star"], modelMatrix, color.violet);
		else
		{
			if ((Star::period - (Engine::GetElapsedTime() - starGun->getTimeOfLastUse())) < (Star::period / 5))
				RenderMesh2D(meshes["star"], modelMatrix, color.red);
			else
				RenderMesh2D(meshes["star"], modelMatrix, color.violet);
		}
	}
}

void Vis2D::DrawCircle(std::vector<Point*> p, double centerX, double centerY, glm::vec3 col)
{
	double x, y;

	for (int i = 0; i < p.size(); i++)
	{
		x = p[i]->getCenterX() + centerX;
		y = p[i]->getCenterY() + centerY;
		modelMatrix = glm::mat3(1) * Transform2D::Translate(x, y);
		RenderMesh2D(meshes["point"], modelMatrix, col);
	}
}

void Vis2D::AddExtraLife()
{
	double impactDistance = 2 * Heart::length + playerShip->getHeight();
	impactDistance *= impactDistance;
	double dX, dY;
	bool c1, c2;

	if (extraLife->isVisible())
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate(extraLife->getCenterX(), extraLife->getCenterY());
		RenderMesh2D(meshes["heart"], modelMatrix, extraLife->getColor());

		// verific daca jucatorul a colectat viata suplimentara
		dX = (extraLife->getCenterX() - playerShip->getCenterX());
		dY = (extraLife->getCenterY() - playerShip->getCenterY());
		dX *= dX;	dY *= dY;

		// daca da, sterg viata suplimentara de pe ecran si cresc numarul de vieti ale navei
		// altfel incep sa "cobor" viata suplimentara pana dispare din scena (daca jocul nu s-a incheiat)
		if ((dX + dY) <= impactDistance)
		{
			playerShip->addLife();
			extraLife->setVisibility(false);
		}
		else if (!gameOver)
			extraLife->updateCenterY(-extraLife->getSpeed());

		// daca viata a aprasit spatiul logic o sterg
		c1 = (extraLife->getCenterX() > 1.5 * resolution.x) || (extraLife->getCenterX() < -resolution.x / 2);
		c2 = (extraLife->getCenterY() > 1.5 * resolution.y) || (extraLife->getCenterY() < -resolution.y / 2);

		if (c1 && c2)
			extraLife->setVisibility(false);
	}
}

void Vis2D::AddStarGun()
{
	double impactDistance = Star::length / 2 + Star::height + playerShip->getHeight();
	impactDistance *= impactDistance;
	double dX, dY;
	bool c1, c2;

	if (starGun->isVisible())
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate(starGun->getCenterX(), starGun->getCenterY());
		RenderMesh2D(meshes["star"], modelMatrix, starGun->getColor());

		// verific daca jucatorul a colectat starGun
		dX = starGun->getCenterX() - playerShip->getCenterX();
		dY = starGun->getCenterY() - playerShip->getCenterY();
		dX *= dX;	dY *= dY;

		// daca da, o sa poata trage in 4 directii pentru o anumita perioada
		if ((dX + dY) <= impactDistance)
		{
			playerShip->addStarGun();
			starGun->setVisibility(false);
		}
		else if (!gameOver)
			starGun->updateCenterY(-starGun->getSpeed());

		// daca a parasit spatiul ferestrei o sterg
		c1 = (starGun->getCenterX() > 1.5 * resolution.x) || (starGun->getCenterX() < -resolution.x / 2);
		c2 = (starGun->getCenterY() > 1.5 * resolution.y) || (starGun->getCenterY() < -resolution.y / 2);

		if (c1 && c2)
			starGun->setVisibility(false);
	}
}

void Vis2D::AddShield()
{
	double impactDistance = Shield::collectibleRadius + playerShip->getHeight();
	impactDistance *= impactDistance;
	double dX, dY;
	bool c1, c2;
	glm::vec3 col;
	std::vector<Point*> p;

	if (shield->isVisible())
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate(shield->getCenterX(), shield->getCenterY());
		RenderMesh2D(meshes["point"], modelMatrix, playerShip->getColor());

		// desenez iconita shield-ului
		p = shield->getCollectiblePoints();
		DrawCircle(p, shield->getCenterX(), shield->getCenterY(), color.orange);

		// verific daca jucatorul a colectat shieldul
		dX = shield->getCenterX() - playerShip->getCenterX();
		dY = shield->getCenterY() - playerShip->getCenterY();
		dX *= dX;	dY *= dY;

		// daca da, sterg iconita cu shield-ul de pe ecran si il adaug in jurul player-ului
		// altfel incep sa "cobor" iconita shield-ului (daca jocul nu s-a incheiat)
		if ((dX + dY) <= impactDistance)
		{
			shield->setVisibility(false);
			shield->useShield(true);
			shield->updateTimeOfLastUse(Engine::GetElapsedTime());
		}
		else if (!gameOver)
			shield->updateCenterY(-shield->getSpeed());

		// daca shield-ul a aprasit spatiul logic il sterg
		c1 = (shield->getCenterX() > 1.5 * resolution.x) || (shield->getCenterX() < -resolution.x / 2);
		c2 = (shield->getCenterY() > 1.5 * resolution.y) || (shield->getCenterY() < -resolution.y / 2);

		if (c1 && c2)
			shield->setVisibility(false);
	}

	// jucatorul a colectat shield-ul
	if (shield->isInUse())
	{
		// cand shield-ul e aproape consumat, il fac rosu
		if ((Shield::period - (Engine::GetElapsedTime() - shield->getTimeOfLastUse())) < (Shield::period / 5))
			col = color.red;
		else
			col = color.orange;

		// desenare shield
		p = shield->getShieldPoints();
		DrawCircle(p, playerShip->getCenterX(), playerShip->getCenterY(), col);

		// daca s-a terminat perioada de folosire
		if ((Engine::GetElapsedTime() - shield->getTimeOfLastUse()) > Shield::period)
			shield->useShield(false);
	}
}

void Vis2D::AddBullets()
{
	bool c1, c2;
	double angle, bulletCenterX, bulletCenterY;

	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();)
	{
		modelMatrix = glm::mat3(1) * Transform2D::Translate((*it)->getCenterX(), (*it)->getCenterY());
		modelMatrix *= Transform2D::Rotate((*it)->getAngle() + RADIANS(90));
		RenderMesh2D(meshes["bullet"], modelMatrix, (*it)->getColor());

		if (!gameOver)
		{
			bulletCenterX = (*it)->getCenterX();
			bulletCenterY = (*it)->getCenterY();
			angle = (*it)->getAngle();
			bulletCenterX += cos(angle) * Bullet::bulletSpeed;
			bulletCenterY += sin(angle) * Bullet::bulletSpeed;

			(*it)->setCenter(glm::vec2(bulletCenterX, bulletCenterY));

			// elimin gloantele ce au parasit fereastra
			c1 = (bulletCenterX > 1.5 * resolution.x) || (bulletCenterX < -resolution.x / 2);
			c2 = (bulletCenterY > 1.5 * resolution.y) || (bulletCenterY < -resolution.y / 2);
			if (c1 || c2)
				it = bullets.erase(it);
			else
				++it;
		}
		else
			++it;
	}
}

void Vis2D::Collisions()
{
	double bulletCenterX, bulletCenterY, enemyCenterX, enemyCenterY;
	bool c1, c2;
	double impactDistance = playerShip->getHeight();

	// verificare coliziune glont-inamic
	for (int i = 0; i < bullets.size(); i++)
		for (std::vector<Ship*>::iterator it2 = enemies.begin(); it2 != enemies.end();)
		{
			bulletCenterX = bullets.at(i)->getCenterX();
			bulletCenterY = bullets.at(i)->getCenterY();
			enemyCenterX = (*it2)->getCenterX();
			enemyCenterY = (*it2)->getCenterY();

			if ((*it2)->getName() == "redShip")
			{
				c1 = abs(enemyCenterX - bulletCenterX) < (impactDistance / 2);
				c2 = abs(enemyCenterY - bulletCenterY) < (impactDistance / 2);
			}
			else
			{
				c1 = abs(enemyCenterX - bulletCenterX) < impactDistance;
				c2 = abs(enemyCenterY - bulletCenterY) < impactDistance;
			}

			// retin indicele glontului ce si-a atins tinta
			// elimin sau scad o viata navei lovite
			if (c1 && c2)
			{
				// scad o viata navei galbene, ii dublez viteza si o ii schimb culoarea
				// altfel, am alt tip de inamic deci il elimin
				if ((*it2)->getName() == "yellowShip")
				{
					(*it2)->setTimeOfDestroy(Engine::GetElapsedTime());
					(*it2)->setName("redShip");
					(*it2)->setColor(color.red);
					(*it2)->doubleSpeed();
					it2 = enemies.end();
					bulletsToRemove.push_back(i);
				}
				else
				{
					// verific daca trebuie adaugata o abilitate
					if ((Engine::GetElapsedTime() - timeOfLastAbility) > abilitySpawnInterval)
					{
						timeOfLastAbility = Engine::GetElapsedTime();
						abilityType = std::rand() % 3;

						// 0 -> ExtraLife
						// 1 -> StarGun
						// 2 -> Shield
						if (abilityType == 0)
						{
							extraLife->setVisibility(true);
							extraLife->setCenter(glm::vec2((*it2)->getCenterX(), (*it2)->getCenterY()));
						}
						else if (abilityType == 1)
						{
							starGun->setVisibility(true);
							starGun->setCenter(glm::vec2((*it2)->getCenterX(), (*it2)->getCenterY()));
						}
						else
						{
							shield->setVisibility(true);
							shield->setCenter(glm::vec2((*it2)->getCenterX(), (*it2)->getCenterY()));
						}
					}

					enemies.erase(it2);
					it2 = enemies.end();
					bulletsToRemove.push_back(i);
				}
			}
			else
				++it2;
		}
}

void Vis2D::DrawScene()
{
	glm::vec2 cursor;
	double cursorX, cursorY;

	// calculez noul centru al navei in functie de tastele apasate
	if (!gameOver)
	{
		cursor = window->GetCursorPosition();
		cursorX = cursor.x;
		cursorY = cursor.y;
		cursorX -= playerShip->getCenterX();
		cursorY = resolution.y - cursor.y - playerShip->getCenterY();
		playerShip->setAngle(glm::atan(cursorY, cursorX));
		MoveShip();
	}

	// desenare nava jucator
	modelMatrix = glm::mat3(1) * Transform2D::Translate(playerShip->getCenterX(), playerShip->getCenterY());
	modelMatrix *= Transform2D::Rotate(playerShip->getAngle());
	RenderMesh2D(meshes["ship"], modelMatrix, playerShip->getColor());

	// generare de inamici
	if (!gameOver)
		SpawnEnemy();

	// desenare inamici
	DrawEnemies();

	// desenare vieti
	DrawLifes();

	// desenare iconita starGun
	DrawStarGunIcon();

	// adaug o viata suplimentara daca exista
	AddExtraLife();

	// adaug starGun daca exista
	AddStarGun();

	// adaug shield daca exista
	AddShield();

	// salvez in acest vector indecsii gloantelor ce ating tinta pt a le sterge
	bulletsToRemove.clear();

	// adaugare gloante in scena
	AddBullets();

	// verificare coliziuni (glont-inamic si inamic-nava)
	if (!gameOver)
	{
		Collisions();

		// elimin gloantele ce si-au atins tinta
		for (int i = bulletsToRemove.size() - 1; i >= 0; i--)
			bullets.erase(bullets.begin() + bulletsToRemove.at(i));
	}

	// reduc treptat intervalul de spawn
	if (!gameOver && (spawnInterval > 0.5))
		spawnInterval -= 0.0002;
}

void Vis2D::OnInputUpdate(float deltaTime, int mods)
{
}

void Vis2D::OnKeyPress(int key, int mods)
{
	if (!gameOver)
	{
		if (key == GLFW_KEY_W && !keyIsPressed.at(2))
			keyIsPressed[0] = true;
		else if (key == GLFW_KEY_S && !keyIsPressed.at(0))
			keyIsPressed[2] = true;
		else if (key == GLFW_KEY_A && !keyIsPressed.at(3))
			keyIsPressed[1] = true;
		else if (key == GLFW_KEY_D && !keyIsPressed.at(1))
			keyIsPressed[3] = true;
	}
}

void Vis2D::OnKeyRelease(int key, int mods)
{
	// add key release event
	if(key == GLFW_KEY_W)
		keyIsPressed[0] = false;
	else if (key == GLFW_KEY_S)
		keyIsPressed[2] = false;
	else if (key == GLFW_KEY_A)
		keyIsPressed[1] = false;
	else if (key == GLFW_KEY_D)
		keyIsPressed[3] = false;
}

void Vis2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Vis2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (!gameOver)
	{
		// click stanga
		if (button == 1)
		{
			double angle = playerShip->getAngle();
			double centerX = playerShip->getCenterX() + Bullet::bulletLength / 2 * cos(angle);
			double centerY = playerShip->getCenterY() + Bullet::bulletLength / 2 * sin(angle);

			Bullet *bullet = new Bullet("bullet", color.yellow);
			bullet->setAngle(angle);
			bullet->setCenter(glm::vec2(centerX, centerY));
			bullets.push_back(bullet);
		}

		// se foloseste starGun
		if (button == 2 && ((playerShip->nrOfStarGuns() > 0) || starGun->isInUse()))
		{
			// s-a terminat perioada de folosire
			if (!starGun->isInUse())
			{
				// daca am, folosesc alta
				if (playerShip->nrOfStarGuns() > 0)
				{
					playerShip->removeStarGun();
					starGun->updateTimeOfLastUse(Engine::GetElapsedTime());
					starGun->useStarGun(true);
				}		
			}
			else
			{
				// altfel, lansez 4 proiectile in 4 directii diferite (90 grade)
				for (int i = 0; i < 4; i++)
				{
					double angle = playerShip->getAngle() + i * RADIANS(90);
					double centerX = playerShip->getCenterX() + Bullet::bulletLength / 2 * cos(angle);
					double centerY = playerShip->getCenterY() + Bullet::bulletLength / 2 * sin(angle);

					Bullet *bullet = new Bullet("bullet", color.yellow);
					bullet->setAngle(angle);
					bullet->setCenter(glm::vec2(centerX, centerY));
					bullets.push_back(bullet);
				}
			}
		}
	}
}

void Vis2D::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Vis2D::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}