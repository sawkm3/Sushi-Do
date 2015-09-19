#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__

#include "cocos2d.h"
#include "Board.h"
#include <vector>
#include <utility>
#include <string>

class Stage : public cocos2d::Layer
{
private:
	Board gameEngine;
	std::vector<std::vector<cocos2d::Sprite*>> boardSprite;
	bool oneSlected;
	std::pair<int, int> selectedPos;
	cocos2d::Vec2 centerPos;
	bool clearFlag;
	std::vector<Request> requests;
	cocos2d::Sprite* redFrame;

	void SetBackground();
	void SetHuman();
	void SetBoard();
	void SetButton();
	void SetTouchEvent();
	void MyTimer(float);
    
	void menuSubmitCallback(Ref*);

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Stage);
};

#endif // __HELLOWORLD_SCENE_H__
