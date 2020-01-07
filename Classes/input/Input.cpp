#include "Input.h"

void Input::Update()
{
	for (auto trgType : _nowInputType)
	{
		// oldKey��NowKey�̓��͏�Ԃ�����Ă����Ƃ��ɒ��ɓ���
		if (_oldInputType[trgType.first] != _nowInputType[trgType.first])
		{
			// �������u��,�������u�Ԃ̏�������������A����������ɕς���
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
				// ��L�̂ǂ���ł��Ȃ������ꍇ�͉������Ȃ�
			}
		}

		if (_oldInputType.insert(std::make_pair(CHAR(trgType.first), _nowInputType[trgType.first])).second)
		{
			_oldInputType[trgType.first] = _nowInputType[trgType.first];
		}
	}
}
