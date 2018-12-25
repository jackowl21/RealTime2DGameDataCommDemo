#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include "MyPhoton.h"

using namespace std;

// The higher networkFPS, the higher bandwidth requirement of your game.
// ** about 30FPS is common data sync rate for real time games
// ** slower-paced action games could use as low as 10 FPS

const float networkFPS = 30.0f;
const float gNetworkFrameTime = 1.0f/networkFPS;

Application::Application ()
{
	curMouseX = -1;
	curMouseY = -1;
}

Application::~Application ()
{	
}

void Application::start ()
{
	srand(time(0));

	m_gameStarted = false;
	curMouseX = -1;
	curMouseY = -1;
	
	MyPhoton::getInstance().connect();

	m_sprite_body_p1        = new Sprite("../media/body_1.png");
	m_sprite_body_p2        = new Sprite("../media/body_2.png");
	m_sprite_bullet_p1      = new Sprite("../media/bullet_1.png");
	m_sprite_bullet_p2      = new Sprite("../media/bullet_2.png");
	m_sprite_bullet_s       = new Sprite("../media/bullet_s.png");
	m_sprite_missile_p1     = new Sprite("../media/missle_1.png");
	m_sprite_missile_p2     = new Sprite("../media/missle_2.png");
	m_sprite_obstacle_small = new Sprite("../media/obstacle_1.png");
	m_sprite_obstacle_big   = new Sprite("../media/obstacle_2.png");

	m_sprite_win            = new Sprite("../media/win.png");
	m_sprite_lose           = new Sprite("../media/lose.png");
	m_sprite_health_4_p1    = new Sprite("../media/hp_4_1.png");
	m_sprite_health_4_p2    = new Sprite("../media/hp_4_2.png");
	m_sprite_health_3_p1    = new Sprite("../media/hp_3_1.png");
	m_sprite_health_3_p2    = new Sprite("../media/hp_3_2.png");
	m_sprite_health_2_p1    = new Sprite("../media/hp_2_1.png");
	m_sprite_health_2_p2    = new Sprite("../media/hp_2_2.png");
	m_sprite_health_1       = new Sprite("../media/hp_1.png");
	m_sprite_health_0       = new Sprite("../media/hp_0.png");
	m_sprite_fireMode_1     = new Sprite("../media/single_mode.png");
	m_sprite_fireMode_2     = new Sprite("../media/rapid_mode.png");
	m_sprite_missile_on     = new Sprite("../media/missle_on.png");
	m_sprite_missile_off    = new Sprite("../media/missle_off.png");

	m_object1.setSprite(m_sprite_body_p1);
	m_object1.setPos(Vector(rand()%800,rand()%600,0));
	m_object1.setScale(Vector(0.15f, 0.15f, 0.15f));
	m_object1.setRotation(0);
	m_object1.setBlendMode(ALPHA);

	m_object2.setSprite(m_sprite_body_p2);
	m_object2.setPos(Vector(200, 200, 0));
	m_object2.setScale(Vector(0.15f, 0.15f, 0.15f));
	m_object2.setRotation(0);
	m_object2.setBlendMode(ALPHA);

	m_healthBar1.setSprite(m_sprite_health_4_p1);
	m_healthBar1.setPos(Vector(55.0f, 55.0f, 0.0f));
	m_healthBar1.setScale(Vector(0.15f, 0.15f, 0.0f));
	m_healthBar1.setRotation(0);
	m_healthBar1.setBlendMode(ALPHA);

	m_healthBar2.setSprite(m_sprite_health_4_p2);
	m_healthBar2.setPos(Vector(745.0f, 545.0f, 0.0f));
	m_healthBar2.setScale(Vector(0.15f, 0.15f, 0.0f));
	m_healthBar2.setRotation(0);
	m_healthBar2.setBlendMode(ALPHA);

	m_fireModeUI.setSprite(m_sprite_fireMode_1);
	m_fireModeUI.setPos(Vector(105.0f, 55.0f, 0.0f));
	m_fireModeUI.setScale(Vector(0.125f, 0.125f, 0.0f));
	m_fireModeUI.setRotation(0);
	m_fireModeUI.setBlendMode(ALPHA);

	m_missileUI.setSprite(m_sprite_missile_on);
	m_missileUI.setPos(Vector(150.0f, 55.0f, 0.0f));
	m_missileUI.setScale(Vector(0.125f, 0.125f, 0.0f));
	m_missileUI.setRotation(0);
	m_missileUI.setBlendMode(ALPHA);

	m_gameResult.setSprite(m_sprite_win);
	m_gameResult.setPos(Vector(400.0f, 300.0f, 0.0f));
	m_gameResult.setScale(Vector(0.5f, 0.5f, 0.0f));
	m_gameResult.setRotation(0);
	m_gameResult.setBlendMode(ALPHA);

	m_missile_1.setSprite(m_sprite_missile_p1);
	m_missile_1.setPos(Vector(0.0f, 0.0f, 0.0f));
	m_missile_1.setScale(Vector(0.10f, 0.10f, 0.0f));
	m_missile_1.setRotation(0);
	m_missile_1.setBlendMode(ALPHA);

	m_missile_2.setSprite(m_sprite_missile_p2);
	m_missile_2.setPos(Vector(0.0f, 0.0f, 0.0f));
	m_missile_2.setScale(Vector(0.10f, 0.10f, 0.0f));
	m_missile_2.setRotation(0);
	m_missile_2.setBlendMode(ALPHA);

	m_obstacle1.setSprite(m_sprite_obstacle_small);
	m_obstacle1.setPos(Vector(300.0f, 400.0f, 0.0f));
	m_obstacle1.setScale(Vector(0.2f, 0.2f, 0.0f));
	m_obstacle1.setRotation(0);
	m_obstacle1.setBlendMode(ALPHA);

	m_obstacle2.setSprite(m_sprite_obstacle_small);
	m_obstacle2.setPos(Vector(500.0f, 200.0f, 0.0f));
	m_obstacle2.setScale(Vector(0.2f, 0.2f, 0.0f));
	m_obstacle2.setRotation(0);
	m_obstacle2.setBlendMode(ALPHA);

	m_obstacle3.setSprite(m_sprite_obstacle_big);
	m_obstacle3.setPos(Vector(250.0f, 150.0f, 0.0f));
	m_obstacle3.setScale(Vector(0.4f, 0.4f, 0.0f));
	m_obstacle3.setRotation(0);
	m_obstacle3.setBlendMode(ALPHA);

	m_obstacle4.setSprite(m_sprite_obstacle_big);
	m_obstacle4.setPos(Vector(550.0f, 450.0f, 0.0f));
	m_obstacle4.setScale(Vector(0.4f, 0.4f, 0.0f));
	m_obstacle4.setRotation(0);
	m_obstacle4.setBlendMode(ALPHA);

	m_lastReceivedPos = m_object2.getPos();
}

void Application::sendMyData(void)
{
	Vector pos =  m_object1.getPos();
	Vector vel = m_object1.getVelocity();
	Vector acc = m_object1.getAcceleration();
	float angle = m_object1.getRotation();

	Vector mPos = m_missile_1.getPos();
	Vector mVel = m_missile_1.getVelocity();
	Vector mAcc = m_missile_1.getAcceleration();
	float mAngle = m_missile_1.getRotation();

	//! method 1
	/*MyPhoton::getInstance().sendMyData(pos.mVal[0], pos.mVal[1],
										vel.mVal[0], vel.mVal[1],
										acc.mVal[0], acc.mVal[1],
										angle,
										bulletX, bulletY);*/

	//! method 2
	if (!m_bList_1.empty())
	{
		MyPhoton::getInstance().sendMyData2(
			pos.mVal[0], pos.mVal[1],
			vel.mVal[0], vel.mVal[1],
			acc.mVal[0], acc.mVal[1],
			angle, 
			mPos.mVal[0], mPos.mVal[1],
			mVel.mVal[0], mVel.mVal[1],
			mAcc.mVal[0], mAcc.mVal[1],
			mAngle,
			health_p2,
			(int)m_fireMode,
			m_bList_1.size(),m_bList_1);
	}
	else
	{
		MyPhoton::getInstance().sendMyData2(pos.mVal[0], pos.mVal[1],
			vel.mVal[0], vel.mVal[1],
			acc.mVal[0], acc.mVal[1],
			angle,
			mPos.mVal[0], mPos.mVal[1],
			mVel.mVal[0], mVel.mVal[1],
			mAcc.mVal[0], mAcc.mVal[1],
			mAngle,
			health_p2,
			-1,
			0, m_bList_1);
	}
	
	bulletX = 0;
	bulletY = 0;
}

void Application::sendBulletData(float mousePosX, float mousePosY)
{
	//MyPhoton::getInstance().sendMyData2(mousePosX, mousePosY);
}

void Application::networkUpdate()
{
	static double prevTime = glfwGetTime();
	
	double time = glfwGetTime();
	//sendMyData();
	if(time - prevTime >= gNetworkFrameTime) 
	{
		//cout << "sent" << endl;
		sendMyData();
		playerBulletDeathCheck();
		prevTime = time;
	}
}

void Application::limitVelAndPos(GameObject* go)
{
	if(go->getVelocity().length() > 400.0f)
	{
		Vector vec = go->getVelocity();
		vec.normalize();
		vec *= 400.0f;
		go->setVelocity(vec);
	}
}

void Application::limitBulletVelAndPos(Bullet * go)
{
	if (go->getVelocity().length() > 500.0f)
	{
		Vector vec = go->getVelocity();
		vec.normalize();
		vec *= 500.0f;
		go->setVelocity(vec);
	}
}

void Application::update (double elapsedTime)
{
	MyPhoton::getInstance().run();

	if(!m_gameStarted)
		return;

	
	m_object1.update(elapsedTime);
	m_object1.setAcceleration(Vector(0.0f, 0.0f, 0.0f));
	limitVelAndPos(&m_object1);

	networkUpdate();

	m_object2.update(elapsedTime);
	m_object2.setPos(Vector::lerp(m_object2.getPos(), m_lastReceivedPos, 0.001f));

	limitVelAndPos(&m_object2);

	updateBullets(elapsedTime);
	updateMissles(elapsedTime);

	obstacleCollisionCheck(&m_obstacle1, 55);
	obstacleCollisionCheck(&m_obstacle2, 55);
	obstacleCollisionCheck(&m_obstacle3, 90);
	obstacleCollisionCheck(&m_obstacle4, 90);

	boundaryCollisionCheck();
	gameCondition();
	
}

void Application::draw()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!m_gameStarted)
		return;

	m_healthBar1.draw();
	m_healthBar2.draw();
	m_fireModeUI.draw();
	m_missileUI.draw();

	m_object1.draw();
	m_object2.draw();

	m_obstacle1.draw();
	m_obstacle2.draw();
	m_obstacle3.draw();
	m_obstacle4.draw();

	drawBullets();
	drawMissles();

	if(m_gameEnded)
		m_gameResult.draw();
}


void Application::OnReceivedOpponentData(float* data)
{
	//Vector prevPos = m_object2.getPos();

	if(m_gameStarted == false)
	{
		m_gameStarted = true;
		m_object2.setPos(Vector(data[0], data[1], 0));

		m_lastReceivedPos = m_object2.getPos();
		m_object2.setVelocity(Vector(data[2], data[3], 0));
		m_prevReceivedTime = glfwGetTime();
		return;
	}
	
	m_lastReceivedPos = Vector(data[0], data[1], 0);
	m_lastReceivedRotation = data[6];

	m_object2.setVelocity(Vector(data[2], data[3], 0));
	m_object2.setPos(Vector::lerp(m_object2.getPos(), m_lastReceivedPos, 0.01f));
	m_object2.setRotation(lerp(m_object2.getRotation(), m_lastReceivedRotation, 1.0f));

	if (data[7] != 0 && data[8] != 0)
	{
		enemyShoot2(data[7], data[8]);
	}

	/*if (data[7] > 0)
	{
		enemyFireTime += 0.001f;

		if (enemyFireTime > fireRate)
		{
			enemyShoot();
			enemyFireTime = 0.0f;
		}
	}
	else
	{
		enemyFireTime = 0;
	}*/

	//m_object2.setPos(m_lastReceivedPos);

	/*if (data[7] > 0 && data[8] > 0)
	{
		float vX = data[7] - m_object2.getPos().mVal[0];
		float vY = data[8] - m_object2.getPos().mVal[1];

		GameObject* bullet = new GameObject(m_sprite_bullet_p2, m_object2.getPos().mVal[0], m_object2.getPos().mVal[1]);
		bullet->setVelocity(Vector(vX, vY * -1, 0));
		bullet->setScale(Vector(0.05, 0.05, 0));
		bullet->setBlendMode(ALPHA);

		m_enemyBulletList.push_back(bullet);
	}*/
	
}

void Application::OnReceivedOpponentData2(float * data)
{
	if (m_gameStarted == false)
	{
		m_gameStarted = true;
		m_object2.setPos(Vector(data[0], data[1], 0));

		m_lastReceivedPos = m_object2.getPos();
		m_object2.setVelocity(Vector(data[2], data[3], 0));
		m_prevReceivedTime = glfwGetTime();
		return;
	}

	m_lastReceivedPos = Vector(data[0], data[1], 0);
	m_lastReceivedRotation = data[6];

	m_object2.setVelocity(Vector(data[2], data[3], 0));
	m_object2.setPos(Vector::lerp(m_object2.getPos(), m_lastReceivedPos, 0.01f));
	m_object2.setRotation(lerp(m_object2.getRotation(), m_lastReceivedRotation, 1.0f));

	
	if (data[9] != 0 && data[10] != 0)
	{
		if (compareDistance(m_lastReceivedPos, Vector(data[7], data[8], 0)) < 10.0f)
		{
			m_lastReceivedMisslePos = Vector(data[7], data[8], 0);
			m_lastReceivedMissleRotation = data[13];

			m_missile_2.setVelocity(Vector(data[9], data[10], 0));
			m_missile_2.setPos(m_lastReceivedMisslePos);
			m_missile_2.setRotation(m_lastReceivedMissleRotation);
		}
		else
		{
			m_lastReceivedMisslePos = Vector(data[7], data[8], 0);
			m_lastReceivedMissleRotation = data[13];

			m_missile_2.setVelocity(Vector(data[9], data[10], 0));
			m_missile_2.setPos(Vector::lerp(m_missile_2.getPos(), m_lastReceivedMisslePos, 0.01f));
			m_missile_2.setRotation(lerp(m_missile_2.getRotation(), m_lastReceivedMissleRotation, 1.0f));
		}

		missleActivated_p2 = true;
	}
	else
	{
		missleActivated_p2 = false;
	}
	
	health_p1 = data[14];
	updateHealthBar1();

	if (data[16] > 0.0f)
	{
		Bullet* bullet = new Bullet();
		
		bullet->setSprite(m_sprite_bullet_p2);
		bullet->setBlendMode(ALPHA);
		bullet->setScale(Vector(0.05, 0.05, 0));
		bullet->setPos(m_object2.getPos());
		bullet->setRotation(m_object2.getRotation());

		m_bList_2.push_back(bullet);
	}
	
	
	int startPos = 18;

	for (std::list<Bullet*>::iterator i = m_bList_2.begin(); i != m_bList_2.end(); i++)
	{
		(*i)->m_lastReceivedPos = Vector(data[startPos], data[startPos + 1], 0);
		startPos += 2;
	}

	for (std::list<Bullet*>::iterator i = m_bList_2.begin(); i != m_bList_2.end(); i++)
	{
		(*i)->setVelocity(Vector(data[startPos], data[startPos + 1], 0));
		(*i)->setPos(Vector::lerp((*i)->getPos(), (*i)->m_lastReceivedPos, 0.5f));
		startPos += 2;
	}

	for (std::list<Bullet*>::iterator i = m_bList_2.begin(); i != m_bList_2.end(); /**/)
	{
		if (data[startPos] > 0.0f)
		{
			(*i)->life = data[startPos];
			++i;
		}
		else
		{
			delete (*i);
			m_bList_2.erase(i++);
		}

		//(*i)->life = data[startPos];
		//++i;
		startPos++;
	}

}


void Application::onKeyPressed (int key)
{
	if (!m_gameStarted)
		return;

	if (m_gameEnded)
		return;

	if (key == GLFW_KEY_Q)
	{
		switchFireMode();
	}
}

void Application::onKeyReleased (int key)
{
	if (!m_gameStarted)
		return;

}

void Application::onKeyHold (int key)
{
	if(!m_gameStarted)
		return;

	if (m_gameEnded)
		return;
	
	if (key == GLFW_KEY_W)
	{
		m_object1.setAcceleration(m_object1.getAcceleration() + Vector(0.0f, 500.0f, 0.0f));		
	}
	if(key == GLFW_KEY_A)
	{
		m_object1.setAcceleration(m_object1.getAcceleration()+Vector(-500.0f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_S)
	{
		m_object1.setAcceleration(m_object1.getAcceleration()+Vector(0.0f, -500.0f, 0.0f));
	}
	if(key == GLFW_KEY_D)
	{
		m_object1.setAcceleration(m_object1.getAcceleration()+Vector(500.0f, 0.0f, 0.0f));
	}
	
}

void Application::onMousePressed (int button)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		shoot();
	}
	if (button == GLFW_MOUSE_BUTTON_2)
	{
		shootMissle();
	}
}

void Application::onMouseReleased (int button)
{
	isShot = -1;
	fireTime = 0;
}

void Application::onMouseHold (int button)
{
	if (m_fireMode == F_RAPID)
	{
		fireTime += 0.01f;

		if (fireTime > fireRate)
		{
			shoot();
			fireTime = 0.0f;
		}
	}
}

void Application::onMouseMoved (double mousePosX, double mousePosY)
{
	float invertedY = abs(600 - m_object1.getPos().mVal[1]);

	float dirX = m_object1.getPos().mVal[0] - mousePosX;
	float dirY = invertedY - mousePosY;

	float direction = atan2(dirX, dirY);

	m_object1.setRotation(direction);

	curMouseX = (float)mousePosX;
	curMouseY = (float)mousePosY;
}

void Application::drawBullets()
{
	if (m_bList_1.empty() == false)
	{
		for (std::list<Bullet*>::iterator i = m_bList_1.begin(); i != m_bList_1.end(); i++)
		{
			(*i)->draw();
		}
	}

	if (m_bList_2.empty() == false)
	{
		for (std::list<Bullet*>::iterator i = m_bList_2.begin(); i != m_bList_2.end(); i++)
		{
			(*i)->draw();
		}
	}
}

void Application::drawMissles()
{
	if (missleActivated_p1)
	{
		m_missile_1.draw();
	}
	if (missleActivated_p2)
	{
		m_missile_2.draw();
	}
}

void Application::updateBullets(float elapsedTime)
{
	if (!m_bList_1.empty())
	{
		for (std::list<Bullet*>::iterator i = m_bList_1.begin(); i != m_bList_1.end(); /**/)
		{
			(*i)->update(elapsedTime);
			(*i)->updateHealth(elapsedTime);

			bulletCollisionCheck((*i), &m_obstacle1, 45);
			bulletCollisionCheck((*i), &m_obstacle2, 45);
			bulletCollisionCheck((*i), &m_obstacle3, 100);
			bulletCollisionCheck((*i), &m_obstacle4, 100);

			if ((*i)->collisionCheck(&m_object2) && (*i)->life > 0.0f)
			{
				if (health_p2 > 0)
				{
					if ((*i)->bulletMode == (int)F_SINGLE)
						health_p2--;
					else
						health_p2 -= 2;
				}
					
				updateHealthBar2();
				(*i)->life = -1;
			}

			++i;
		}
	}

	if (!m_bList_2.empty())
	{
		for (std::list<Bullet*>::iterator i = m_bList_2.begin(); i != m_bList_2.end(); /**/)
		{
			/*if ((*i)->isDead())
			{
				delete (*i);
				m_bList_1.erase(i++);
			}
			else*/
			{
				(*i)->update(elapsedTime);
				(*i)->setPos(Vector::lerp((*i)->getPos(), (*i)->m_lastReceivedPos, 0.5f));
				limitBulletVelAndPos(*i);
				++i;
			}
			
		}
	}
}

void Application::updateMissles(float elapsedTime)
{
	if (missleActivated_p1)
	{
		updateMissleTargetPosition(&m_missile_1, &m_object2);
		m_missile_1.update(elapsedTime);
		missileCollisionCheck(&m_missile_1, &m_obstacle1, 45);
		missileCollisionCheck(&m_missile_1, &m_obstacle2, 45);
		missileCollisionCheck(&m_missile_1, &m_obstacle3, 90);
		missileCollisionCheck(&m_missile_1, &m_obstacle4, 90);

		if (m_missile_1.collisionCheck(&m_object2))
		{
			health_p2 -= 3;
			updateHealthBar2();
			missleActivated_p1 = false;
			m_missile_1.setVelocity(Vector(0,0,0));
			m_missileUI.setSprite(m_sprite_missile_on);
		}
	}
	if (missleActivated_p2)
	{
		m_missile_2.update(elapsedTime);
		m_missile_2.setPos(Vector::lerp(m_missile_2.getPos(), m_lastReceivedMisslePos, 0.01f));

		missileCollisionCheck(&m_missile_2, &m_obstacle1, 45);
		missileCollisionCheck(&m_missile_2, &m_obstacle2, 45);
		missileCollisionCheck(&m_missile_2, &m_obstacle3, 90);
		missileCollisionCheck(&m_missile_2, &m_obstacle4, 90);
		
		if (m_missile_2.collisionCheck(&m_object1))
		{
			missleActivated_p2 = false;
			m_missile_2.setVelocity(Vector(0, 0, 0));
		}
	}
}

void Application::updateMissleTargetPosition(GameObject * missle, GameObject * target)
{
	Vector newVelocity = target->getPos() - missle->getPos();
	newVelocity.normalize();
	//newVelocity.mVal[1] *= -1;
	missle->setVelocity(newVelocity * 100);

	Vector newDirection = target->getPos() - missle->getPos();
	float newRadian = atan2(newDirection.mVal[0] * -1, newDirection.mVal[1]);
	missle->setRotation(newRadian);
}

void Application::bulletCollisionCheck(Bullet * bullet, GameObject * object, float limit)
{
	Vector distance = object->getPos() - bullet->getPos();

	if (distance.length() < limit)
	{
		bullet->life = -1;
	}
}

void Application::missileCollisionCheck(Bullet * bullet, GameObject * object, float limit)
{
	Vector distance = object->getPos() - bullet->getPos();

	if (distance.length() < limit)
	{
		missleActivated_p1 = false;
		m_missile_1.setVelocity(Vector(0, 0, 0));
		m_missileUI.setSprite(m_sprite_missile_on);
	}
}

void Application::obstacleCollisionCheck(GameObject* obstacle, float limit)
{
	Vector difference = obstacle->getPos() - m_object1.getPos();

	if (difference.length() < limit)
	{
		m_object1.setAcceleration(Vector(0, 0, 0));
		//m_object1.setVelocity(Vector(0, 0, 0));
		if(m_object1.getPos().mVal[1] > obstacle->getPos().mVal[1])
			m_object1.setVelocity(Vector(m_object1.getVelocity().mVal[0], 10, 0));
		else if (m_object1.getPos().mVal[1] < obstacle->getPos().mVal[1])
			m_object1.setVelocity(Vector(m_object1.getVelocity().mVal[0], -10, 0));

		if (m_object1.getPos().mVal[0] > obstacle->getPos().mVal[0])
			m_object1.setVelocity(Vector(10, m_object1.getVelocity().mVal[1], 0));
		else if (m_object1.getPos().mVal[0] < obstacle->getPos().mVal[0])
			m_object1.setVelocity(Vector(-10, m_object1.getVelocity().mVal[1], 0));
	}

}

void Application::boundaryCollisionCheck()
{
	if (m_object1.getPos().mVal[0] < 10.0f)
	{
		m_object1.setAcceleration(Vector(0, 0, 0));
		m_object1.setVelocity(Vector(5.0f, m_object1.getVelocity().mVal[1], 0));
	}
	else if (m_object1.getPos().mVal[0] > 790.0f)
	{
		m_object1.setAcceleration(Vector(0, 0, 0));
		m_object1.setVelocity(Vector(-5.0f, m_object1.getVelocity().mVal[1], 0));
	}

	if (m_object1.getPos().mVal[1] < 5.0f)
	{
		m_object1.setAcceleration(Vector(0, 0, 0));
		m_object1.setVelocity(Vector(m_object1.getVelocity().mVal[0], 5.0f, 0));
	}
	else if (m_object1.getPos().mVal[1] > 595.0f)
	{
		m_object1.setAcceleration(Vector(0, 0, 0));
		m_object1.setVelocity(Vector(m_object1.getVelocity().mVal[0], -5.0f, 0));
	}
}

void Application::playerBulletDeathCheck()
{
	for (std::list<Bullet*>::iterator i = m_bList_1.begin(); i != m_bList_1.end(); /**/)
	{
		if ((*i)->isDead())
		{
			delete (*i);
			m_bList_1.erase(i++);
		}
		else
		{
			++i;
		}
	}
}



void Application::shoot()
{
	//float vX = curMouseX - m_object1.getPos().mVal[0];
	//float vY = curMouseY - m_object1.getPos().mVal[1];

	float speed = 300.0f;

	float vX_2 = speed * sinf(m_object1.getRotation());
	float vY_2 = speed * cosf(m_object1.getRotation());

	bulletX = vX_2;
	bulletY = vY_2;

	Bullet* bullet = new Bullet();
	
	bullet->setSprite(m_sprite_bullet_p1);
	bullet->bulletMode = 0;
		
	bullet->setBlendMode(ALPHA);
	bullet->setScale(Vector(0.05, 0.05, 0));
	bullet->setRotation(m_object1.getRotation());
	bullet->setPos(Vector(m_object1.getPos().mVal[0], m_object1.getPos().mVal[1], 0));
	bullet->setVelocity(Vector(vX_2 * -1, vY_2 * 1, 0));

	m_bList_1.push_back(bullet);

	isShot = 1;
}

void Application::enemyShoot()
{
	float speed = 1000.0f;

	float vX_2 = speed * sinf(m_object2.getRotation());
	float vY_2 = speed * cosf(m_object2.getRotation());

	Bullet* bullet = new Bullet();
	bullet->setSprite(m_sprite_bullet_p2);
	bullet->setBlendMode(ALPHA);
	bullet->setScale(Vector(0.05, 0.05, 0));
	bullet->setPos(Vector(m_object2.getPos().mVal[0], m_object2.getPos().mVal[1], 0));
	bullet->setVelocity(Vector(vX_2 * -1, vY_2 * 1, 0));

	m_bList_2.push_back(bullet);
}

void Application::enemyShoot2(float x, float y)
{
	float speed = 1000.0f;

	Bullet* bullet = new Bullet();
	bullet->setSprite(m_sprite_bullet_p2);
	bullet->setBlendMode(ALPHA);
	bullet->setScale(Vector(0.05, 0.05, 0));
	bullet->setPos(Vector(m_object2.getPos().mVal[0], m_object2.getPos().mVal[1], 0));
	bullet->setVelocity(Vector(x * -1, y * 1, 0));

	m_bList_2.push_back(bullet);
}

void Application::shootMissle()
{
	float speed = 50.0f;

	float vX = speed * sinf(m_object2.getRotation());
	float vY = speed * cosf(m_object2.getRotation());

	if (!missleActivated_p1)
	{
		m_missile_1.setPos(m_object1.getPos());
		m_missile_1.setRotation(m_object1.getRotation());
		m_missile_1.setVelocity(Vector(vX * -1, vY * 1, 0));
		missleActivated_p1 = true;
		m_missileUI.setSprite(m_sprite_missile_off);
	}
		
}

void Application::switchFireMode()
{
	if (m_fireMode == F_SINGLE)
	{
		m_fireMode = F_RAPID;
		m_fireModeUI.setSprite(m_sprite_fireMode_2);
	}
	else if (m_fireMode == F_RAPID)
	{
		m_fireMode = F_SINGLE;
		m_fireModeUI.setSprite(m_sprite_fireMode_1);
	}
}

void Application::updateHealthBar1()
{
	if (health_p1 == 4)
	{
		m_healthBar1.setSprite(m_sprite_health_4_p1);
	}
	else if (health_p1 == 3)
	{
		m_healthBar1.setSprite(m_sprite_health_3_p1);
	}
	else if (health_p1 == 2)
	{
		m_healthBar1.setSprite(m_sprite_health_2_p1);
	}
	else if (health_p1 == 1)
	{
		m_healthBar1.setSprite(m_sprite_health_1);
	}
	else
	{
		m_healthBar1.setSprite(m_sprite_health_0);
	}
}

void Application::updateHealthBar2()
{
	if (health_p2 == 4)
	{
		m_healthBar2.setSprite(m_sprite_health_4_p2);
	}
	else if (health_p2 == 3)
	{
		m_healthBar2.setSprite(m_sprite_health_3_p2);
	}
	else if (health_p2 == 2)
	{
		m_healthBar2.setSprite(m_sprite_health_2_p2);
	}
	else if (health_p2 == 1)
	{
		m_healthBar2.setSprite(m_sprite_health_1);
	}
	else
	{
		m_healthBar2.setSprite(m_sprite_health_0);
	}
}

void Application::gameCondition()
{
	if (!m_gameEnded)
	{
		if (health_p1 <= 0 && health_p2 > 0)
		{
			m_gameResult.setSprite(m_sprite_lose);
			m_gameEnded = true;
		}

		if (health_p2 <= 0 && health_p1 > 0)
		{
			m_gameEnded = true;
		}
	}
}

float Application::lerp(float old, float latest, float value)
{
	return ((old * (1 - value)) + (latest * value));
}

float Application::compareDistance(Vector object1, Vector object2)
{
	Vector difference = object2 - object1;
	return difference.length();
}

float Application::axisDistance(float y1, float y2)
{
	float distance = abs(y2 - y1);
	return distance;
}

bool Application::distance(float one, float two)
{
	return (one > two);
}
