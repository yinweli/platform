//-----------------------------------------------------------------------------
#include "console.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define CONSOLE_MAXHISTORY 1024 // 最大命令歷史列表容量
#define CONSOLE_MAXCHAR 79 // 最大輸入字元數
//-----------------------------------------------------------------------------
C_ConsoleQueue::C_ConsoleQueue() {}
//-----------------------------------------------------------------------------
C_ConsoleQueue::~C_ConsoleQueue() {}
//-----------------------------------------------------------------------------
// 新增資料
void C_ConsoleQueue::Add(IN const nstring &szData)
{
	m_Data.push(szData);
}
//-----------------------------------------------------------------------------
// 取得資料
nstring C_ConsoleQueue::Data()
{
	nstring szData;

	if(m_Data.empty() == false)
	{
		szData = m_Data.front();
		m_Data.pop();
	}//if

	return szData;
}
//-----------------------------------------------------------------------------
C_ConsoleHistory::C_ConsoleHistory() : m_ulPos(0) {}
//-----------------------------------------------------------------------------
C_ConsoleHistory::~C_ConsoleHistory() {}
//-----------------------------------------------------------------------------
// 新增資料
void C_ConsoleHistory::Add(IN const nstring &szData)
{
	if(szData.empty())
		return;

	m_Data.push_back(szData);

	if(m_Data.size() > CONSOLE_MAXHISTORY)
		m_Data.erase(m_Data.begin());

	m_ulPos = m_Data.size();
}
//-----------------------------------------------------------------------------
// 游標向前一步
void C_ConsoleHistory::Prev()
{
	if(m_ulPos > 0)
		--m_ulPos;
}
//-----------------------------------------------------------------------------
// 游標向後一步
void C_ConsoleHistory::Next()
{
	if(m_ulPos < m_Data.size())
		++m_ulPos;
}
//-----------------------------------------------------------------------------
// 取得游標所指資料字串
nstring C_ConsoleHistory::Data() const
{
	return (m_ulPos >= 0 && m_ulPos < m_Data.size()) ? m_Data[m_ulPos] : __T("");
}
//-----------------------------------------------------------------------------
C_ConsoleKBStr::C_ConsoleKBStr() : m_wPos(0), m_bInsert(false) {}
//-----------------------------------------------------------------------------
C_ConsoleKBStr::~C_ConsoleKBStr() {}
//-----------------------------------------------------------------------------
// 設定標題字串
void C_ConsoleKBStr::SetTitle(IN const nstring &szTitle)
{
	m_szTitle = szTitle;
}
//-----------------------------------------------------------------------------
// 設定分隔字串
void C_ConsoleKBStr::SetToken(IN const nstring &szToken)
{
	m_szToken = szToken;
}
//-----------------------------------------------------------------------------
// 清除資料字串
void C_ConsoleKBStr::ClrData()
{
	m_szData = __T("");
	m_wPos = 0;
}
//-----------------------------------------------------------------------------
// 設定資料字串
void C_ConsoleKBStr::SetData(IN const nstring &szData)
{
	if(szData.empty())
		return;

	m_szData = szData;
	m_wPos = static_cast<short>(m_szData.size());
}
//-----------------------------------------------------------------------------
// 插入資料字元
void C_ConsoleKBStr::InsData(IN ENUM_AKCodes emKey, IN unsigned long ulMaxChar)
{
	if(emKey <= ENUM_AKCodes_NULL)
		return;

	if(emKey >= ENUM_AKCodes_BACKSPACE)
		return;

	nstring szKey = emKey == ENUM_AKCodes_SPACE ? __T(" ") : akcodestr(emKey);

	if(szKey.empty())
		return;

	if(m_bInsert)
	{
		if(m_wPos + m_szTitle.size() + m_szToken.size() >= ulMaxChar)
			return;

		m_szData.replace(m_wPos, szKey.size(), szKey);
	}
	else
	{
		if(m_szData.size() + m_szTitle.size() + m_szToken.size() >= ulMaxChar)
			return;

		m_szData.insert(m_wPos, szKey);
	}//if

	m_wPos += static_cast<short>(szKey.size());
}
//-----------------------------------------------------------------------------
// 向前刪除字元
void C_ConsoleKBStr::DelPrev()
{
	if(m_wPos <= 0 || m_szData.empty())
		return;

	m_szData.erase(m_wPos - 1, 1);
	--m_wPos;
}
//-----------------------------------------------------------------------------
// 向後刪除字元
void C_ConsoleKBStr::DelNext()
{
	if(m_szData.empty())
		return;

	m_szData.erase(m_wPos, 1);
}
//-----------------------------------------------------------------------------
// 游標移動到最前
void C_ConsoleKBStr::MoveFront()
{
	m_wPos = 0;
}
//-----------------------------------------------------------------------------
// 游標移動到最尾
void C_ConsoleKBStr::MoveBack()
{
	m_wPos = static_cast<short>(m_szData.size());
}
//-----------------------------------------------------------------------------
// 游標向前一步
void C_ConsoleKBStr::MovePrev()
{
	if(m_wPos > 0)
		--m_wPos;
}
//-----------------------------------------------------------------------------
// 游標向後一步
void C_ConsoleKBStr::MoveNext()
{
	if(m_wPos < static_cast<short>(m_szData.size()))
		++m_wPos;
}
//-----------------------------------------------------------------------------
// 開關替代旗標
void C_ConsoleKBStr::Insert()
{
	m_bInsert = !m_bInsert;
}
//-----------------------------------------------------------------------------
// 檢查是否為空
bool C_ConsoleKBStr::Empty() const
{
	return m_szData.empty();
}
//-----------------------------------------------------------------------------
// 取得標題字串
nstring C_ConsoleKBStr::Title() const
{
	return m_szTitle;
}
//-----------------------------------------------------------------------------
// 取得分隔字串
nstring C_ConsoleKBStr::Token() const
{
	return m_szToken;
}
//-----------------------------------------------------------------------------
// 取得資料字串
nstring C_ConsoleKBStr::Data() const
{
	return m_szData;
}
//-----------------------------------------------------------------------------
// 取得組合字串
nstring C_ConsoleKBStr::Combination() const
{
	return m_szTitle + m_szToken + m_szData;
}
//-----------------------------------------------------------------------------
// 取得資料字串長度
unsigned long C_ConsoleKBStr::Size() const
{
	return m_szData.size();
}
//-----------------------------------------------------------------------------
// 取得游標位置
short C_ConsoleKBStr::GetPos() const
{
	return m_wPos;
}
//-----------------------------------------------------------------------------
C_Console::C_Console() {}
//-----------------------------------------------------------------------------
C_Console::~C_Console() {}
//-----------------------------------------------------------------------------
// 定時處理
void C_Console::Process()
{
	if(_kbhit())
	{
		ENUM_AKCodes emKey = getakcode();

		switch(emKey)
		{
		case ENUM_AKCodes_BACKSPACE: // 當按下back鍵的處理
			m_ccKBStr.DelPrev();
			break;

		case ENUM_AKCodes_ESC: // 當按下esc鍵的處理
			m_ccKBStr.ClrData();
			break;

		case ENUM_AKCodes_HOME: // 當按下home鍵的處理
			m_ccKBStr.MoveFront();
			break;

		case ENUM_AKCodes_END: // 當按下end鍵的處理
			m_ccKBStr.MoveBack();
			break;

		case ENUM_AKCodes_INSERT: // 當按下insert鍵的處理
			m_ccKBStr.Insert();
			break;

		case ENUM_AKCodes_DELETE: // 當按下delete鍵的處理
			m_ccKBStr.DelNext();
			break;

		case ENUM_AKCodes_UP: // 當按下up鍵的處理
			m_ccHistory.Prev();
			m_ccKBStr.SetData(m_ccHistory.Data());
			break;

		case ENUM_AKCodes_DOWN: // 當按下down鍵的處理
			m_ccHistory.Next();
			m_ccKBStr.SetData(m_ccHistory.Data());
			break;

		case ENUM_AKCodes_LEFT: // 當按下left鍵的處理
			m_ccKBStr.MovePrev();
			break;

		case ENUM_AKCodes_RIGHT: // 當按下right鍵的處理
			m_ccKBStr.MoveNext();
			break;

		case ENUM_AKCodes_ENTER: // 當按下enter鍵的處理
			{
				nstring szData = m_ccKBStr.Data();

				if(szData.empty() == false)
				{
					m_Command.Add(szData);
					m_ccHistory.Add(szData);
					m_ccKBStr.ClrData();
				}//if
			}
			break;

		default:
			m_ccKBStr.InsData(emKey, CONSOLE_MAXCHAR);
			break;
		}//switch

		if(emKey == ENUM_AKCodes_ENTER)
			Show(__T("\n"), 0, false);
		else
			Show(m_ccKBStr.Combination(), m_ccKBStr.Title().size() + m_ccKBStr.Token().size() + m_ccKBStr.GetPos(), true);
	}//if
}
//-----------------------------------------------------------------------------
// 設定標題字串
void C_Console::SetTitle(IN const nstring &szTitle)
{
	m_ccKBStr.SetTitle(szTitle);
}
//-----------------------------------------------------------------------------
// 設定分隔字串
void C_Console::SetToken(IN const nstring &szToken)
{
	m_ccKBStr.SetToken(szToken);
}
//-----------------------------------------------------------------------------
// 取得標題字串
nstring C_Console::GetTitle() const
{
	return m_ccKBStr.Title();
}
//-----------------------------------------------------------------------------
// 取得分隔字串
nstring C_Console::GetToken() const
{
	return m_ccKBStr.Token();
}
//-----------------------------------------------------------------------------
// 取得指令字串
nstring C_Console::GetCommand()
{
	return m_Command.Data();
}
//-----------------------------------------------------------------------------
// 顯示指令
void C_Console::Show(IN const nstring &szString, IN unsigned long ulCursor, IN bool bReplace)
{
	if(bReplace)
		ReplaceConsoleLine(szString, static_cast<short>(ulCursor));
	else
		printfex(szString);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------