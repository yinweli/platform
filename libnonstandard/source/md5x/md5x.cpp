//-----------------------------------------------------------------------------
#include "md5x.h"
#include "md5.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
S_MD5Code::S_MD5Code()
{
	memset(MD5Code, 0, sizeof(MD5Code));
}
//-----------------------------------------------------------------------------
// ¨ú±oMD5½s½X
S_MD5Code GetMD5Code(IN const void *p, IN unsigned int uiSize)
{
	if(p == NULL || uiSize <= 0)
		return S_MD5Code();

	S_MD5Code sMD5Code;
	md5_state_t State;

	md5_init(&State);
	md5_append(&State, (const md5_byte_t *)p, uiSize);
	md5_finish(&State, sMD5Code.MD5Code);
	sMD5Code.szMD5Code = _T("");

	for(int i = 0; i < MD5CODE_SIZE; ++i)
		addprintf(sMD5Code.szMD5Code, __T("%02x"), sMD5Code.MD5Code[i]);

	return sMD5Code;
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------