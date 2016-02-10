#pragma once

#include "cocos2d.h"

class Snake : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Snake);

	void update(float) override;
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

private:
	cocos2d::Sprite* spr_josh;
	cocos2d::Sprite* spr_sticks;
	cocos2d::Sprite* spr_note;
	char direction;
	char prevDirection;
	int distance = 20;
	int length = 0;

	cocos2d::PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) {
		sceneWorld = world;
	};

	bool onContactBegin(cocos2d::PhysicsContact &contact);
};