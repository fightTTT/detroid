#include "Input.h"

void Input::Update()
{
	for (auto trgType : _nowInputType)
	{
		// oldKey‚ÆNowKey‚Ì“ü—Íó‘Ô‚ªˆá‚Á‚Ä‚¢‚½‚Æ‚«‚É’†‚É“ü‚é
		if (_oldInputType[trgType.first] != _nowInputType[trgType.first])
		{
			// ‰Ÿ‚µ‚½uŠÔ,—£‚µ‚½uŠÔ‚Ìî•ñ‚ğ‰Ÿ‚µ‘±‚¯‚éA—£‚µ‘±‚¯‚é‚É•Ï‚¦‚é
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
				// ã‹L‚Ì‚Ç‚¿‚ç‚Å‚à‚È‚©‚Á‚½ê‡‚Í‰½‚à‚µ‚È‚¢
			}
		}

		if (_oldInputType.insert(std::make_pair(CHAR(trgType.first), _nowInputType[trgType.first])).second)
		{
			_oldInputType[trgType.first] = _nowInputType[trgType.first];
		}
	}
}
