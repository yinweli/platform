/**
 * @file errorwin.h
 * @note Windows���~���O
 * @author yinweli
 */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ERRORWIN
#define _ERRORWIN
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
/**
 * @brief Windows���~���O
 * @ingroup nstderror
 */
class C_ErrorWin : public C_ErrorBase
{
private:
	//-------------------------------------
	int m_iWinError; ///< Windows���~�N�X
	//-------------------------------------

public:
	//-------------------------------------
	C_ErrorWin();
	C_ErrorWin(IN int error);
	virtual ~C_ErrorWin();
	//-------------------------------------
	operator bool () const;
	operator int () const;
	operator estring () const;
	//-------------------------------------
};
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------