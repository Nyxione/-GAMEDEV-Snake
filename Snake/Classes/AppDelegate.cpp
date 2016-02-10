#include "AppDelegate.h"
#include "SnakeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Snake");
		glview->setFrameSize(500, 500);
		director->setOpenGLView(glview);
	}
	
	auto scene = Snake::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}