#include "SnakeScene.h"

USING_NS_CC;

Scene* Snake::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	auto layer = Snake::create();

	scene->addChild(layer);

	return scene;
}

bool Snake::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto spr_wall1 = Sprite::create("walls_horr.png");
	spr_wall1->setAnchorPoint(Vec2(0,0));
	spr_wall1->setPosition(0, 0);
	this->addChild(spr_wall1, 1);

	auto spr_wall2 = Sprite::create("walls_horr.png");
	spr_wall2->setAnchorPoint(Vec2(0, 0));
	spr_wall2->setPosition(0, 475);
	this->addChild(spr_wall2, 1);

	auto spr_wall3 = Sprite::create("walls_ver.png");
	spr_wall3->setAnchorPoint(Vec2(0, 0));
	spr_wall3->setPosition(0, 0);
	this->addChild(spr_wall3, 1);

	auto spr_wall4 = Sprite::create("walls_ver.png");
	spr_wall4->setAnchorPoint(Vec2(0, 0));
	spr_wall4->setPosition(475, 0);
	this->addChild(spr_wall4, 1);

	spr_josh = Sprite::create("Josh-resize.png");
	spr_josh->setPosition(250, 250);
	this->addChild(spr_josh, 1);
	direction = 'r';
	prevDirection = ' '; 

	spr_sticks = Sprite::create("drumstick.png");
	int tempx = cocos2d::RandomHelper::random_int(30, 450);
	int tempy = cocos2d::RandomHelper::random_int(30, 450);
	spr_sticks->setPosition(tempx, tempy);
	this->addChild(spr_sticks, 0);

	auto pbody_sticks = PhysicsBody::createBox(Size(25.0f, 25.0f)); 
	pbody_sticks->setCollisionBitmask(2);
	pbody_sticks->setContactTestBitmask(true);
	pbody_sticks->setGravityEnable(false);
	spr_sticks->setPhysicsBody(pbody_sticks);

	auto pbody_josh = PhysicsBody::createBox(Size(22.0f, 40.0f));
	pbody_josh->setCollisionBitmask(1);
	pbody_josh->setContactTestBitmask(true);
	pbody_josh->setGravityEnable(false);
	spr_josh->setPhysicsBody(pbody_josh);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Snake::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Snake::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	
	return true;
}

void Snake::update(float delta) {
	auto position = spr_josh->getPosition();

	switch (direction) {
		case 'd': position.y -= 80 * delta; break;		//down
		case 'u': position.y += 80 * delta; break;		//up
		case 'r': position.x += 80 * delta; break;		//right
		case 'l': position.x -= 80 * delta; break;		//left
	}

	//wall collision 
	if ((spr_josh->getPositionX() <= 25 || spr_josh->getPositionX() >= 475) ||
		spr_josh->getPositionY() <= 25 || spr_josh->getPositionY() >= 475) {
		CCLOG("WALL");
	}

	spr_josh->setPosition(position);

}

void Snake::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	auto position = spr_josh->getPosition();
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		if (direction != 'r') {
			direction = 'l';
		} break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		if (direction != 'l') {
			direction = 'r';
		} break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		if (direction != 'u') {
			direction = 'd';
		} break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		if (direction != 'd') {
			direction = 'u';
		} break;
	}
}

bool Snake::onContactBegin(cocos2d::PhysicsContact &contact) {
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//collision with food
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) ||
		(2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
		CCLOG("COLLISION");
		length++;
		int tempx = cocos2d::RandomHelper::random_int(30, 450);
		int tempy = cocos2d::RandomHelper::random_int(30, 450);
		spr_sticks->setPosition(tempx, tempy);
	}

	return true;
}
