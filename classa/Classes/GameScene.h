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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <memory>
#include <ck/bank.h>
#include <ck/Sound.h>
#include <jni.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "input/TouchInput.h"
#include "input/KeyInput.h"
#include "Player.h"
#include "effect/EffectMng.h"

#ifndef __ANDROID_JNI__
#define __ANDROID_JNI__
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL	Java_org_cocos2dx_cpp_AppActivity_initCricket(
		JNIEnv *env,
		jclass activity,
		jobject context
	);
#ifdef __cplusplus
}
#endif
#endif

class GameScene : public cocos2d::Scene
{
	cocos2d::Sprite* face = nullptr;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void update(float delta)override;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
	Player* player;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	CkBank* bank;
	CkSound* sound;
	//char*   MultiByteToUTF8(const char* src);
};

#endif // __HELLOWORLD_SCENE_H__
