#include "StageScene.h"
//#include "FadeScene.h"

USING_NS_CC;

// �X�e�[�W�ԍ�
int stageNum = 0;

// ���i�摜1�̃T�C�Y
int sushiImgLength = 200;

// �t���[���̃T�C�Y
int frameImgLength = 1321;

// �l�ԉ摜�T�C�Y
int humanImgLength = 584;

// �{�[�h����
int bottomDistance = 40;
// �{�[�h���E��
int sideDistance = 60;

// �l�Ԃ�Y���W
int humanPosY = 262;

// �l�Ԃ̔{��
float humanRatio = 0.7;

// �X�e�[�W�t�@�C����
std::string stageFileName[] =
{
	"honban.txt"
};

// �l�摜�t�@�C����
std::string humanImgFileName = "balloon2.png";

// �w�i�t�@�C����
std::string backgroundFileName = "background2.png";

// �t���[���t�@�C����
std::string frame0FileName = "frame0.png";
std::string frame1FileName = "frame1.png";

Scene* Stage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Stage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Stage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	centerPos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	Director::getInstance()->setDisplayStats(false);

	// ��ԕϐ��̏�����
	oneSlected = false;	// �Z���̑I���Ȃ�
	clearFlag = false;	// ���N���A

	// �Q�[���G���W��
	gameEngine.init(stageFileName[stageNum]);

	SetBackground();
	SetHuman();
	SetBoard();
	SetButton();
	SetTouchEvent();

    return true;
}

void Stage::SetBackground()
{
	//auto backLayer1 = LayerColor::create(Color4B(51, 75, 112, 255), centerPos.x * 2 * 0.95, centerPos.y * 2 * 0.95);
	//backLayer1->ignoreAnchorPointForPosition(false);
	//backLayer1->setTouchEnabled(false);
	//backLayer1->setAnchorPoint(Vec2(0.5f, 0.5f));
	//backLayer1->setPosition(centerPos);
	auto back = Sprite::create(backgroundFileName);
	back->setPosition(Vec2(0, centerPos.y * 2));
	back->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->addChild(back, 0);
}

void Stage::SetHuman()
{
	// ���N�G�X�g�𓾂�
	requests = gameEngine.getRequest();

	// �q�̃X�v���C�g
	auto human = Sprite::create(humanImgFileName);
	human->setPosition(Vec2(centerPos.x, centerPos.y + humanPosY));
	this->addChild(human, 1);

	auto scale = cocos2d::ScaleBy::create(0, (centerPos.x * 2) / humanImgLength * humanRatio);
	human->runAction(scale);

	//// �e�[�u��
	//auto table = Sprite::create(humanImgFileName);
	//human->setPosition(Vec2(centerPos.x, centerPos.y));
	//this->addChild(table);
	//auto scale = cocos2d::ScaleBy::create(0, humanImgWidth / (centerPos.x * 2));
	//human->runAction(scale);

	//for (int i = 0; i < requests.size(); i++)
	//{
	//	for (int j = 0; j < requests[i].request.size(); j++)
	//	{
	//		// �X�v���C�g�쐬
	//		if ()
	//		{
	//			
	//		}
	//	}
	//}
}

void Stage::SetBoard()
{
	// �{�[�h�����󂯎��
	std::vector<std::vector<int>> board = gameEngine.getBoard();
	int sizeX = board[0].size(), sizeY = board.size();
	int fitWidth = centerPos.x * 2 - sideDistance * 2 ;
	float afterImgWidth = (float)fitWidth / sizeX;
	float imageRatio = afterImgWidth / sushiImgLength;

	float boardSizeHalfX = (sizeX / 2.0f - 0.5f) * sushiImgLength;
	float boardSizeHalfY = (sizeY / 2.0f - 0.5f) * sushiImgLength;
	//Vec2 board00(int(centerPos.x - boardSizeHalfX), 
	//	int(centerPos.y - boardSizeHalfY));
	Vec2 board00(sideDistance + afterImgWidth / 2, bottomDistance + afterImgWidth * sizeY - afterImgWidth / 2);

	// �Ԙg�X�v���C�g�쐬
	redFrame = Sprite::create(frame1FileName);
	redFrame->setAnchorPoint(Vec2(0.5f, 0.5f));
	redFrame->setVisible(false);
	this->addChild(redFrame, 2);

	auto scale = cocos2d::ScaleBy::create(0, afterImgWidth / frameImgLength);
	redFrame->runAction(scale);

	// �{�[�h�̃X�v���C�g�쐬
	boardSprite.resize(board.size());
	for (int i = 0; i < board.size(); i++)
	{
		boardSprite[i].resize(board[i].size());
		for (int j = 0; j < board[i].size(); j++)
		{
			// �g�X�v���C�g
			auto frame = Sprite::create(frame0FileName);
			frame->setAnchorPoint(Vec2(0.5f, 0.5f));
			frame->setPosition(Vec2(board00.x + afterImgWidth * j, board00.y - afterImgWidth * i));
			this->addChild(frame, 1);

			auto scale = cocos2d::ScaleBy::create(0, afterImgWidth / frameImgLength);
			frame->runAction(scale);

			// �l�^�X�v���C�g
			std::string netaName = "neta";
			netaName += std::to_string(board[i][j]);
			netaName.append(".png");

			boardSprite[i][j] = Sprite::create(netaName);
			boardSprite[i][j]->setAnchorPoint(Vec2(0.5f, 0.5f));
			boardSprite[i][j]->setPosition(Vec2(board00.x + afterImgWidth * j, board00.y - afterImgWidth * i));
			this->addChild(boardSprite[i][j], 3);

			// �T�C�Y����
			scale = cocos2d::ScaleBy::create(0, imageRatio * 0.8);
			boardSprite[i][j]->runAction(scale);
		}
	}
}

void Stage::SetButton()
{
	// ��o�{�^���쐬
    auto submitButton = MenuItemImage::create(
                                        "Button0.png",
                                        "Button1.png",
										CC_CALLBACK_1(Stage::menuSubmitCallback, this));
	submitButton->setAnchorPoint(Vec2(0.5f, 0.5f));													/////
	submitButton->setPosition(Vec2(centerPos.x, 20));													/////

	auto menu = Menu::create(submitButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 4);
}


void Stage::SetTouchEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		// ���i�摜�^�b�`����
		Point p = touch->getLocation();
		
		for (int i = 0; i < boardSprite.size(); i++)
		{
			for (int j = 0; j < boardSprite[i].size(); j++)
			{
				// ���i�̃^�b�`���o
				Rect r = boardSprite[i][j]->boundingBox();
				if (r.containsPoint(p))
				{
					// 1�ڃ^�b�`
					if (!oneSlected)
					{
						selectedPos = std::pair<int, int>(i, j);
						oneSlected = true;

						// �I�������Z����Ԙg�ň͂ރA�j���[�V����							//////
						redFrame->setPosition(boardSprite[i][j]->getPosition());
						redFrame->setVisible(true);
					}
					// 2�ڃ^�b�`
					else
					{
						// �Ԙg������
						redFrame->setVisible(false);

						// �����ꏊ�̂Ƃ��A������
						if (selectedPos.first == i && selectedPos.second == j)
						{
							oneSlected = false;
						}

						// ����ւ�
						bool changed = gameEngine.change(selectedPos, std::pair<int, int>(i, j));
						
						// ����ւ��Ȃ�
						if (!changed) return false;


						// �ՖʍX�V
						Sprite* tmp = boardSprite[selectedPos.first][selectedPos.second];
						boardSprite[selectedPos.first][selectedPos.second] = boardSprite[i][j];
						boardSprite[i][j] = tmp;

						// �X�V�A�j���[�V����								///////
						// (��)
						Vec2 tmpPos = boardSprite[i][j]->getPosition();
						boardSprite[i][j]->setPosition(boardSprite[selectedPos.first][selectedPos.second]->getPosition());
						boardSprite[selectedPos.first][selectedPos.second]->setPosition(tmpPos);

						oneSlected = false;
					}
				}
			}
		}

		return true;
	};

	// ���X�i�[�ǉ�
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Stage::menuSubmitCallback(Ref* pSender)
{
	// ��o
	bool cleared = gameEngine.submit();

	// �Q�[���N���A
	if (cleared)
	{
		// ���i�����A�j���[�V����
		

		// �N���A���
	    //�X�v���C�g�̍쐬
		auto pImg = Sprite::create("clear.png");
		pImg->setPosition(Vec2(centerPos.x, centerPos.y));
		this->addChild(pImg, 5);

		////�g��̃A�N�V����
		//auto scaleAction = FadeIn::create(.2);
  //  
		////3�b�̂��x��
		//auto delay = DelayTime::create(3);
  //  
		////�t�F�[�h�A�E�g�̃A�N�V����
		//auto fadeOutAction = FadeOut::create(.5);
  //  
		////�g��->3�b���x��->�t�F�[�h�A�E�g�̏��ԂɃA�N�V��������ׂ�
		//auto sequence = Sequence::create(scaleAction, delay, fadeOutAction, NULL);
  //  
		////�J�n�I
		//pImg->runAction(sequence);

		//Director::getInstance()->pushScene(Pause::createScene());

		this->schedule(schedule_selector(Stage::MyTimer), 2.0f);
	}
}

void Stage::MyTimer(float delta)
{
	auto transition = TransitionFadeUp::create(2.0f, Stage::createScene());
	Director::getInstance()->replaceScene(transition);
}