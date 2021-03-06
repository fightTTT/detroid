#include "Input.h"

void Input::Update()
{
	for (auto trgType : _nowInputType)
	{
		// oldKeyとNowKeyの入力状態が違っていたときに中に入る
		if (_oldInputType[trgType.first] != _nowInputType[trgType.first])
		{
			// 押した瞬間,離した瞬間の情報を押し続ける、離し続けるに変える
			if (_inputType[CHAR(trgType.first)] == INPUT_TRG::ON_MOMENT)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::ON;
			}
			else if (_inputType[CHAR(trgType.first)] == INPUT_TRG::OFF_MOMENT)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::OFF;
			}
			else
			{
				// 上記のどちらでもなかった場合は何もしない
			}
		}

		if (_oldInputType.insert(std::make_pair(CHAR(trgType.first), _nowInputType[trgType.first])).second)
		{
			_oldInputType[trgType.first] = _nowInputType[trgType.first];
		}
	}
}
