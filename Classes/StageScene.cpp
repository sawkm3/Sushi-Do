#include "StageScene.h"
//#include "FadeScene.h"

USING_NS_CC;

// ステージ番号
int stageNum = 0;

// 寿司画像1つのサイズ
int sushiImgLength = 200;

// フレームのサイズ
int frameImgLength = 1321;

// 人間画像サイズ
int humanImgLength = 584;

// ボード下幅
int bottomDistance = 40;
// ボード左右幅
int sideDistance = 60;

// 人間のY座標
int humanPosY = 262;

// 人間の倍率
float humanRatio = 0.7;

// ステージファイル名
std::string stageFileName[] =
{
	"honban.txt"
};

// 人画像ファイル名
std::string humanImgFileName = "balloon2.png";

// 背景ファイル名
std::string backgroundFileName = "background2.png";

// フレームファイル名
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

	// 状態変数の初期化
	oneSlected = false;	// セルの選択なし
	clearFlag = false;	// 未クリア

	// ゲームエンジン
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
	// リクエストを得る
	requests = gameEngine.getRequest();

	// 客のスプライト
	auto human = Sprite::create(humanImgFileName);
	human->setPosition(Vec2(centerPos.x, centerPos.y + humanPosY));
	this->addChild(human, 1);

	auto scale = cocos2d::ScaleBy::create(0, (centerPos.x * 2) / humanImgLength * humanRatio);
	human->runAction(scale);

	//// テーブル
	//auto table = Sprite::create(humanImgFileName);
	//human->setPosition(Vec2(centerPos.x, centerPos.y));
	//this->addChild(table);
	//auto scale = cocos2d::ScaleBy::create(0, humanImgWidth / (centerPos.x * 2));
	//human->runAction(scale);

	//for (int i = 0; i < requests.size(); i++)
	//{
	//	for (int j = 0; j < requests[i].request.size(); j++)
	//	{
	//		// スプライト作成
	//		if ()
	//		{
	//			
	//		}
	//	}
	//}
}

void Stage::SetBoard()
{
	// ボード情報を受け取る
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

	// 赤枠スプライト作成
	redFrame = Sprite::create(frame1FileName);
	redFrame->setAnchorPoint(Vec2(0.5f, 0.5f));
	redFrame->setVisible(false);
	this->addChild(redFrame, 2);

	auto scale = cocos2d::ScaleBy::create(0, afterImgWidth / frameImgLength);
	redFrame->runAction(scale);

	// ボードのスプライト作成
	boardSprite.resize(board.size());
	for (int i = 0; i < board.size(); i++)
	{
		boardSprite[i].resize(board[i].size());
		for (int j = 0; j < board[i].size(); j++)
		{
			// 枠スプライト
			auto frame = Sprite::create(frame0FileName);
			frame->setAnchorPoint(Vec2(0.5f, 0.5f));
			frame->setPosition(Vec2(board00.x + afterImgWidth * j, board00.y - afterImgWidth * i));
			this->addChild(frame, 1);

			auto scale = cocos2d::ScaleBy::create(0, afterImgWidth / frameImgLength);
			frame->runAction(scale);

			// ネタスプライト
			std::string netaName = "neta";
			netaName += std::to_string(board[i][j]);
			netaName.append(".png");

			boardSprite[i][j] = Sprite::create(netaName);
			boardSprite[i][j]->setAnchorPoint(Vec2(0.5f, 0.5f));
			boardSprite[i][j]->setPosition(Vec2(board00.x + afterImgWidth * j, board00.y - afterImgWidth * i));
			this->addChild(boardSprite[i][j], 3);

			// サイズ調整
			scale = cocos2d::ScaleBy::create(0, imageRatio * 0.8);
			boardSprite[i][j]->runAction(scale);
		}
	}
}

void Stage::SetButton()
{
	// 提出ボタン作成
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
		// 寿司画像タッチ判定
		Point p = touch->getLocation();
		
		for (int i = 0; i < boardSprite.size(); i++)
		{
			for (int j = 0; j < boardSprite[i].size(); j++)
			{
				// 寿司のタッチ検出
				Rect r = boardSprite[i][j]->boundingBox();
				if (r.containsPoint(p))
				{
					// 1個目タッチ
					if (!oneSlected)
					{
						selectedPos = std::pair<int, int>(i, j);
						oneSlected = true;

						// 選択したセルを赤枠で囲むアニメーション							//////
						redFrame->setPosition(boardSprite[i][j]->getPosition());
						redFrame->setVisible(true);
					}
					// 2個目タッチ
					else
					{
						// 赤枠を消す
						redFrame->setVisible(false);

						// 同じ場所のとき、取り消し
						if (selectedPos.first == i && selectedPos.second == j)
						{
							oneSlected = false;
						}

						// 入れ替え
						bool changed = gameEngine.change(selectedPos, std::pair<int, int>(i, j));
						
						// 入れ替えない
						if (!changed) return false;


						// 盤面更新
						Sprite* tmp = boardSprite[selectedPos.first][selectedPos.second];
						boardSprite[selectedPos.first][selectedPos.second] = boardSprite[i][j];
						boardSprite[i][j] = tmp;

						// 更新アニメーション								///////
						// (仮)
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

	// リスナー追加
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Stage::menuSubmitCallback(Ref* pSender)
{
	// 提出
	bool cleared = gameEngine.submit();

	// ゲームクリア
	if (cleared)
	{
		// 寿司完成アニメーション
		

		// クリア画面
	    //スプライトの作成
		auto pImg = Sprite::create("clear.png");
		pImg->setPosition(Vec2(centerPos.x, centerPos.y));
		this->addChild(pImg, 5);

		////拡大のアクション
		//auto scaleAction = FadeIn::create(.2);
  //  
		////3秒のお休み
		//auto delay = DelayTime::create(3);
  //  
		////フェードアウトのアクション
		//auto fadeOutAction = FadeOut::create(.5);
  //  
		////拡大->3秒お休み->フェードアウトの順番にアクションを並べる
		//auto sequence = Sequence::create(scaleAction, delay, fadeOutAction, NULL);
  //  
		////開始！
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