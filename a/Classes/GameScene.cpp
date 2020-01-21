/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include<memory>
//#include <ck/ck.h>
//#include <ck/config.h>
#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "effect/EffectMng.h"
#include "obj/Enemy.h"

USING_NS_CC;

#if CK_PLATFORM_ANDROID
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL
		Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv *env, jclass activity, jobject context)
	{
		CkConfig config(env, context);
		CkInit(&config);
		CkBank *g_bank = CkBank::newBank("mymySound.ckb");
		CkSound *g_sound = CkSound::newBankSound(g_bank, "mymy");
		g_sound->setLoopCount(-1);
		g_sound->play();
	}
}
#ifdef  __cpluspus
#endif
#endif

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
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
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }



    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 30);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    //this->addChild(label, 1);
    //}

	auto bgLayer = Layer::create();
	auto mdlLayer = Layer::create();
	auto playerLayer = Layer::create();
	auto enemyLayer = Layer::create();
	auto mapLayer = Layer::create();
	auto effectLayer = Layer::create();

	bgLayer->setName("BGLayer");
	mdlLayer->setName("MDLLayer");
	playerLayer->setName("PlayerLayer");
	enemyLayer->setName("EnemyLayer");
	mapLayer->setName("MapLayer");
	effectLayer->setName("EffectLayer");

	bg_ground = Sprite::create("image/Environment/background.png");
	bg_ground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgLayer->addChild(bg_ground);
	/*auto bg_ground2 = Sprite::create("image/Environment/background.png");
	bg_ground2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg_ground2->addChild(bg_ground);*/
	/*this->addChild(bgLayer);*/

	auto mdl_ground = Sprite::create("image/Environment/middleground-no-fungus.png");
	mdl_ground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	mdlLayer->addChild(mdl_ground);
	/*this->addChild(mdlLayer,1);*/

	auto map = TMXTiledMap::create("untitled.tmx");
	map->setPosition(0,0);
	map->setName("MapData");
	auto groundLayer = map->getLayer("ground");
	groundLayer->setGlobalZOrder(0);
	//auto trapLayer = map->getLayer("trap");
	//trapLayer->setGlobalZOrder(1);



	/*auto subGroundLayer = map->getLayer("subGround");
	subGroundLayer->setGlobalZOrder(2);*/
	mapLayer->addChild(map);
	/*this->addChild(mapLayer, 3);*/

	_player = Player::createSprite();
	_player->setName("player");
	playerLayer->addChild(_player);
	/*this->addChild(playerLayer, 5);

	this->addChild(effectLayer, 6);*/

	_enemy = Enemy::createSprite();
	enemyLayer->addChild(_enemy);


	auto followLayer = Layer::create();
	followLayer->setName("FollowerLayer");
	followLayer->addChild(bgLayer, 0);
	followLayer->addChild(mdlLayer, 1);
	followLayer->addChild(mapLayer, 2);
	followLayer->addChild(effectLayer, 3);
	followLayer->addChild(playerLayer, 4);
	followLayer->addChild(enemyLayer, 4);

	followLayer->runAction(Follow::create(_player, Rect(0.0f, 0.0f, map->getContentSize().width, map->getContentSize().height)));
	this->addChild(followLayer, 0);

	this->scheduleUpdate();

#if CK_PLATFORM_ANDROID
	//CkConfig config(env, activity);
#else
	//bank = CkBank::newBank("Resources/mymySound.ckb");
	//sound = CkSound::newBankSound(bank,"mymy");
	/*sound->setLoopCount(-1);
	sound->play();*/
#endif

	return true;
}

void GameScene::update(float delta)
{
	if (_enemy != nullptr)
	{
		auto enemycol = cocos2d::Size(36, 48);

		for (auto &shotData : ((Player&)_player).GetShotArray())
		{
			cocos2d::Size shotSize = {9,6};
			for (auto &shot : shotData.shot)
			{
				if (shot->getPositionX() + shotSize.width >= _enemy->getPositionX() - enemycol.width
				&& shot->getPositionX() - shotSize.width <= _enemy->getPositionX() + enemycol.width
				&& shot->getPositionY() + shotSize.height >= _enemy->getPositionY() - enemycol.height
				&& shot->getPositionY() - shotSize.height <= _enemy->getPositionY() + enemycol.height)
				{
					shot->setName("dethShot");

					auto action = RemoveSelf::create();
					_enemy->runAction(action);

					//NextStartScene();
				}
			}
			
		}

	}



	/*auto 	bg_ground2 = Sprite::create("image/Environment/background.png");
	bg_ground2.get*/
	
	/*CkUpdate();*/

	//auto playerLayer = this->getChildByName("FollowerLayer")->getChildByName("PlayerLayer");

	//playerLayer->getPosition()
}

void GameScene::menuCloseCallback(Ref* pSender)
{
//#if CK_PLATFORM_ANDROID
//#else
//	CkConfig config;
//	sound->destroy();
//	bank->destroy();
//#endif
//	
//	CkShutdown();
    /*Close the cocos2d-x game scene and quit the application*/
    Director::getInstance()->end();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
}

void GameScene::NextStartScene()
{
	cocos2d::Scene* scene = StartScene::createScene();
	scene->setName("gameScene");
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5, scene));
}
