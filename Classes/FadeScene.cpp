//#include "StageScene.h"
//#include "FadeScene.h"
//
//USING_NS_CC;
//
//Scene* Fade_::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer = Stage::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer);
//
//    // return the scene
//    return scene;
//}
//
//// on "init" you need to initialize your instance
//bool Fade_::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//	auto layer2 = LayerColor::create(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height);
//	layer2->ignoreAnchorPointForPosition(false);
//	layer2->setTouchEnabled(false);
//	layer2->setAnchorPoint(Vec2(0.5f, 0.5f));
//	layer2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
//	this->addChild(layer2);
//
//	schedule(schedule_selector(Fade_::Transition), 3.0f);
//
//
//
//    return true;
//}
//
//void Fade_::Transition(float frame)
//{
//	auto transition = TransitionFadeUp::create(2.0f, Stage::createScene());
//	Director::getInstance()->replaceScene(transition);
//}