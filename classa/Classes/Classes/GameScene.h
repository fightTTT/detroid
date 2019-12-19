#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Input.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	~GameScene();
	static Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	OprtState* GetOprtState(void) const;
private:
	bool CreateLayer(Layer* layer, int zOrder);
	TMXTiledMap* _map;
	void update(float delta);
	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags);
	OprtState* _oprtState = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
