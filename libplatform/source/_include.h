/**
 * @file _include.h
 * @note 平台引入檔
 * @author yinweli
 */
//-----------------------------------------------------------------------------
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef __INCLUDE_LIBPLATFORM
#define __INCLUDE_LIBPLATFORM
//-----------------------------------------------------------------------------
#include <vcclr.h>
#using <libcsnstandard.dll>
#using <libsetup.dll>
//-----------------------------------------------------------------------------
#define _WINSOCK2_ ///< 定義使用 winsock2.h 而不使用 windows.h
#include "..\..\libnonstandard\source\_nstd\_nstd.h"
#include "..\..\libnonstandard\source\_nstderr\_nstderr.h"
#include "..\..\libnonstandard\source\_nstring\_nstring.h"
#include "..\..\libnonstandard\source\_nstroutf\_nstroutf.h"
#include "..\..\libnonstandard\source\_ntime\_ntime.h"
#include "..\..\libnonstandard\source\algorithm\algorithm.h"
#include "..\..\libnonstandard\source\argument\argument.h"
#include "..\..\libnonstandard\source\callfunclog\callfunclog.h"
#include "..\..\libnonstandard\source\console\console.h"
#include "..\..\libnonstandard\source\consoleargv\consoleargv.h"
#include "..\..\libnonstandard\source\consoletool\consoletool.h"
#include "..\..\libnonstandard\source\crashrpt\crashrpt.h"
#include "..\..\libnonstandard\source\dbase\dbase.h"
#include "..\..\libnonstandard\source\dbmssql\dbmssql.h"
#include "..\..\libnonstandard\source\dbmysql\dbmysql.h"
#include "..\..\libnonstandard\source\dbsqlite\dbsqlite.h"
#include "..\..\libnonstandard\source\filetool\filetool.h"
#include "..\..\libnonstandard\source\formtable\formtable.h"
#include "..\..\libnonstandard\source\inifile\inifile.h"
#include "..\..\libnonstandard\source\memoryleak\memoryleak.h"
#include "..\..\libnonstandard\source\threadlock\threadlock.h"
#include "..\..\libnonstandard\source\threadobj\threadobj.h"
#include "..\..\libnonstandard\source\xsocket\xsocket.h"
//-----------------------------------------------------------------------------
#include "define.h"
/* misc */
#include "cstring.h"
#include "safe.h"
/* kernal */
#include "bmdata.h"
#include "command.h"
#include "component.h"
#include "control.h"
#include "database.h"
#include "dbf.h"
#include "event.h"
#include "handle.h"
#include "network.h"
#include "output.h"
#include "packet.h"
#include "record.h"
#include "server.h"
/* platform */
#include "platform.h"
/* object */
#include "obj.h"
#include "objbenchmark.h"
#include "objcommand.h"
#include "objcomponent.h"
#include "objdatabase.h"
#include "objdbf.h"
#include "objevent.h"
#include "objhandle.h"
#include "objnetwork.h"
#include "objoutput.h"
#include "objpacket.h"
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------