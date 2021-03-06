#pragma once
#ifdef _DEBUG
#include <memory>

#define TRACE(fmt,...) printf(fmt,__VA_ARGS__)		// 文字列を出力

class _DebugConOut
{
public:
	static _DebugConOut &GetInstance()
	{
		return *s_Instance;
	}
private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> s_Instance;
};
#else
#define TRACE(fmt,...) printf(fmt,_VA_ARGS_)
#endif	// _DEBUG