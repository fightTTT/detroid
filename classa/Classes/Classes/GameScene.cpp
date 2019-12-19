#include "GameScene.h"
#include "SoundManager.h"
#include "EffekseerManager.h"
#include "Key.h"
#include "Touch.h"

CkBank* bank;
CkSound* sound;
//CkSound* tester;

GameScene::~GameScene()
{
	delete _oprtState;
}

Scene * GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
	// シーンの初期化
	if (!Scene::init())
	{
		return false;
	}
	this->setName("GameScene");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SoundManager::Instance().AddBank("hellocricket.ckb");
	FXManager::Instace().CreateGroupManager(visibleSize);

	// 閉じるボタン
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// レイヤーの生成と自身のチャイルド登録
	auto bgLayer = Layer::create();
	bgLayer->setName("BackgroundLayer");
	auto background = Sprite::create("background.png");
	background->setPosition(
		visibleSize.width / 2,
		visibleSize.height / 2);
	bgLayer->addChild(background, 0);

	auto blockLayer = Layer::create();
	blockLayer->setName("BlocksLayer");
	_map = TMXTiledMap::create("First Level.tmx");
	_map->setName("MapData");
	_map->setPosition(Vec2(0.0f, 0.0f));
	blockLayer->addChild(_map, 0);

	auto bl = _map->getLayer("Blocks");	
	auto playerLayer = Layer::create();
	auto player = Player::createPlayer();
	playerLayer->addChild(player);

	auto infoLayer = Layer::create();
	infoLayer->setName("InfoLayer");
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	infoLayer->addChild(menu, 1);

	auto effectLayer = Layer::create();
	effectLayer->setName("EffectLayer");

	// プレイヤーをついて行くレイヤー
	auto followerLayer = Layer::create();
	followerLayer->setName("FollowerLayer");
	followerLayer->addChild(bgLayer, 0);
	followerLayer->addChild(blockLayer, 1);
	followerLayer->addChild(effectLayer, 2);
	followerLayer->addChild(playerLayer, 3);

	followerLayer->runAction(Follow::create(player,Rect(0.0f,0.0f,_map->getContentSize().width,_map->getContentSize().height)));

	// レイヤーの登録
	this->addChild(followerLayer, 0);
	this->addChild(infoLayer, 10);
	this->scheduleUpdate();

	auto laser = FXManager::Instace().AddEffect("Laser01.efk");
	laser->setRotation3D(Vec3(0.0f, 90.0f, 0.0f));
	this->addChild(laser, 0);
	auto distortion = FXManager::Instace().AddEffect("Simple_Distortion.efk");
	distortion->setRotation3D(Vec3(20.0f, 0.0f, 0.0f));
	this->addChild(distortion, 0);

	SoundManager::Instance().PlayAudio("321.ogg");
	SoundManager::Instance().PlayAudio("hellocricket.ckb", "hello");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_oprtState = new OprtInputKey;
#else
	_oprtState = new OprtInputTouch;
#endif

	_oprtState->Init();
	infoLayer->addChild(_oprtState);

	auto nameLabel = Label::create("1816221_TAN_SOON_SEANG", "fonts/HGRGE.TTC", 50);
	nameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - nameLabel->getContentSize().height));
	this->addChild(nameLabel,100);

	return true;
}

void GameScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	// 閉じるボタンを押したときエンドする
	Director::getInstance()->end();
}

OprtState * GameScene::GetOprtState(void) const
{
	return _oprtState;
}

bool GameScene::CreateLayer(Layer * layer, int zOrder)
{
	return false;
}

void GameScene::update(float delta)
{
	FXManager::Instace().Update();
	SoundManager::Instance().Update();
}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	auto manager = FXManager::Instace().GetManager();
	manager->begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	manager->end(renderer, _globalZOrder);
	manager->setIsDistortionEnabled(true);
}