#include "EffectMng.h"


EffectMng::EffectMng()
{
}

EffectMng::~EffectMng()
{
	manager->release();
}

bool EffectMng::init()
{
	manager = nullptr;
	
	return false;
}



void EffectMng::AddEffect(std::string efkState)
{
	manager = efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize());
	auto effect = efk::Effect::create(efkState,13.0f);
	emitter = efk::EffectEmitter::create(manager);

	emitter->setPlayOnEnter(true);

	emitter->setPosition(cocos2d::Vec2(300, 300));
	emitter->setScale(20);
	emitter->setEffect(effect);

}

void EffectMng::update()
{
	// Effect1
	//if (count % 300 == 0)
	//{
	//	auto effect = efk::Effect::create("Laser01.efk", 13.0f);
	//	if (effect != nullptr)
	//	{
	//

	//		emitter = efk::EffectEmitter::create(manager);
	//		emitter->setEffect(effect);
	//		emitter->setPlayOnEnter(true);

	//		emitter->setRotation3D(cocos2d::Vec3(0, 90, 0));
	//		emitter->setPosition(cocos2d::Vec2(320, 150));

	//		// emitter->setScale(13);
	//		//this->addChild(emitter, 0);

	//		// No need (because it uses autorelease after 1.41)
	//		//effect->release();
	//	}
	//}

	//// Effect2
	//if (count % 300 == 120)
	//{

	//	auto effect = efk::Effect::create("Homing_Laser01.efk");
	//	if (effect != nullptr)
	//	{


	//		emitter = efk::EffectEmitter::create(manager);
	//		emitter->setEffect(effect);
	//		emitter->setPlayOnEnter(true);

	//		emitter->setPosition(cocos2d::Vec2(320, 150));
	//		emitter->setScale(4);

	//		/**
	//		Some parameters are required to set after addChild

	//		一部のパラメーターはAddChildした後に設定する必要があります。
	//		*/
	//		emitter->setTargetPosition(cocos2d::Vec3(320, 480, 0));

	//		// No need (because it uses autorelease after 1.41)
	//		//effect->release();
	//	}
	//}

	manager->update();
}

efk::EffectManager & EffectMng::GetEffectMng()
{
	// TODO: return ステートメントをここに挿入します
	return *manager;
}

efk::EffectEmitter * EffectMng::GetEfkEmitter()
{
	// TODO: return ステートメントをここに挿入します
	return emitter;
}

void EffectMng::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	manager->begin(renderer, _globalZOrder);
	this->getScene()->visit(renderer, parentTransform, parentFlags);
	manager->end(renderer, _globalZOrder);
}