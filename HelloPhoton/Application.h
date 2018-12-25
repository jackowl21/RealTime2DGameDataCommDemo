#pragma once
#include "Sprite.h"
#include "GameObject.h"

#include <list>
#include <math.h>

#define PI 3.14159265

enum FireMode
{
	F_SINGLE = 0,
	F_RAPID,
	F_TOTAL
};

class Application
{
protected:
	int m_method;

	Sprite*		m_sprite01;
	Sprite*     m_sprite02;

	Sprite*     m_sprite_body_p1;
	Sprite*     m_sprite_body_p2;

	Sprite*     m_sprite_bullet_p1;
	Sprite*     m_sprite_bullet_p2;
	Sprite*     m_sprite_bullet_s;

	Sprite*     m_sprite_missile_p1;
	Sprite*     m_sprite_missile_p2;

	Sprite*     m_sprite_obstacle_small;
	Sprite*     m_sprite_obstacle_big;

	//! UI Sprites
	Sprite*     m_sprite_win;
	Sprite*     m_sprite_lose;
	Sprite*     m_sprite_health_4_p1;
	Sprite*     m_sprite_health_3_p1;
	Sprite*     m_sprite_health_2_p1;
	Sprite*     m_sprite_health_4_p2;
	Sprite*     m_sprite_health_3_p2;
	Sprite*     m_sprite_health_2_p2;
	Sprite*     m_sprite_health_1;
	Sprite*     m_sprite_health_0;
	Sprite*     m_sprite_fireMode_1;
	Sprite*     m_sprite_fireMode_2;
	Sprite*     m_sprite_missile_on;
	Sprite*     m_sprite_missile_off;

	GameObject	m_object1;
	GameObject	m_object2;

	GameObject  m_healthBar1;
	GameObject  m_healthBar2;
	GameObject  m_fireModeUI;
	GameObject  m_missileUI;

	GameObject  m_gameResult;

	GameObject m_obstacle1;
	GameObject m_obstacle2;
	GameObject m_obstacle3;
	GameObject m_obstacle4;

	Bullet m_missile_1;
	Bullet m_missile_2;

	Vector m_lastReceivedPos;
	Vector m_lastReceivedMisslePos;

	float m_lastReceivedRotation;
	float m_lastReceivedMissleRotation;
	float m_lastReceivedBulletNumber;
	
	double m_prevReceivedTime;
	bool m_gameStarted;
	bool m_gameEnded = false;

	void networkUpdate();
	void limitVelAndPos(GameObject* go);
	void limitBulletVelAndPos(Bullet* go);

public:
	
	std::list <Bullet*> m_bList_1;
	std::list <Bullet*> m_bList_2;

	FireMode m_fireMode = F_SINGLE;

	float curMouseX, curMouseY;
	float curBulletX, curBulletY;
	float fireTime = 0;
	float enemyFireTime = 0;
	float fireRate = 0.5f;

	float bulletX = 0;
	float bulletY = 0;

	int health_p1 = 4;
	int health_p2 = 4;
	
	float isShot = -1;

	bool missleActivated_p1 = false;
	bool missleActivated_p2 = false;
	bool isPressed = false;

	Application();
	~Application();


	static Application& getInstance()
	{
		static Application app;
		return app;
	}

	void sendMyData(void);
	void sendBulletData(float mousePosX, float mousePosY);
	void OnReceivedOpponentData(float* data);
	void OnReceivedOpponentData2(float* data);

	virtual void start();	
	virtual void update(double elapsedTime);
	virtual void draw();
	virtual void onKeyPressed(int key);
	virtual void onKeyReleased(int key);
	virtual void onKeyHold(int key);
	virtual void onMousePressed(int button);
	virtual void onMouseReleased(int button);
	virtual void onMouseHold(int button);
	virtual void onMouseMoved(double mousePosX, double mousePosY);

	void drawBullets();
	void drawMissles();

	void updateBullets(float elapsedTime);
	void updateMissles(float elapsedTime);
	void updateMissleTargetPosition(GameObject* missle, GameObject* target);

	void bulletCollisionCheck(Bullet* bullet, GameObject* object, float limit);
	void missileCollisionCheck(Bullet* bullet, GameObject* object, float limit);
	void obstacleCollisionCheck(GameObject* obstacle, float limit);
	void boundaryCollisionCheck();

	void playerBulletDeathCheck();

	void shoot();
	void enemyShoot();
	void enemyShoot2(float x, float y);
	void shootMissle();
	void switchFireMode();

	void updateHealthBar1();
	void updateHealthBar2();

	void gameCondition();

	float lerp(float old, float latest, float value);
	float compareDistance(Vector object1, Vector object2);
	float axisDistance(float y1, float y2);

	bool distance(float one, float two);

};

