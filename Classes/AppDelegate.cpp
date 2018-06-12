#include "AppDelegate.h"
//#include "exam1/MapScene.h"
//#include "exam2/HelloWorldScene.h"
//#include "exam3/AnimationEditor/AnimationEditorScene.h"
//#include "exam3/AnimationScene/AnimationScene.h"
//#include "exam3/AnimationScene/MenuScene.h"
//#include "exam4/ParticleScene.h"
//#include "exam5/AudioScene.h"
#include "exam4/PhysicsScene.h"
#include "exam4/MenuScene.h"
//#include "exam7/MazeScene.h"
//#include "exam8/GameClient.h"



USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	//SimpleAudioEngine::end();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("exam4");
        director->setOpenGLView(glview);
    }
	//把宽高当成320、480
	//glview->setDesignResolutionSize(320, 480, kResolutionShowAll);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();    // 创建相应章节的场景进行测试
	//Director::getInstance()->pushScene(scene);
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
