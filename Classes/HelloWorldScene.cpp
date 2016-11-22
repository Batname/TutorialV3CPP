#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mySprite = Sprite::create("CloseNormal.png");
    mySprite->setPosition(Point((visibleSize.width/2)+origin.x, (visibleSize.height/2)+origin.y));
    
    addChild(mySprite);
    
    
    const char backgroundAudio[] = "audio/background.mp3";
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(backgroundAudio);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(backgroundAudio, true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
//    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
    float x = touch->getLocation().x;
    float y = touch->getLocation().y;
    CCLOG("On touch beging x = %f, y = %f", x, y);
    return true;
}


void HelloWorld::stopEffect(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
