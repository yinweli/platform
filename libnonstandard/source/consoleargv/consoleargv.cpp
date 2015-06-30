//-----------------------------------------------------------------------------
#include "consoleargv.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_ConsoleArgv::C_ConsoleArgv(IN unsigned long argc, IN char *argv[])
{
	if(argc <= 0)
		return;

	if(argv == nullptr)
		return;

	for(unsigned long ulPos = 0; ulPos < argc; ++ulPos)
		set(ulPos, argv[ulPos]);
}
//-----------------------------------------------------------------------------
C_ConsoleArgv::C_ConsoleArgv(IN unsigned long argc, IN wchar_t *argv[])
{
	if(argc <= 0)
		return;

	if(argv == nullptr)
		return;

	for(unsigned long ulPos = 0; ulPos < argc; ++ulPos)
		set(ulPos, argv[ulPos]);
}
//-----------------------------------------------------------------------------
C_ConsoleArgv::~C_ConsoleArgv() {}
//-----------------------------------------------------------------------------
// 取得執行檔路徑
nstring C_ConsoleArgv::ExePath() const
{
	return get(0);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------