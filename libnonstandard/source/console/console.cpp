//-----------------------------------------------------------------------------
#include "console.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define CONSOLE_MAXHISTORY 1024 // �̤j�R�O���v�C��e�q
#define CONSOLE_MAXCHAR 79 // �̤j��J�r����
//-----------------------------------------------------------------------------
C_ConsoleQueue::C_ConsoleQueue() {}
//-----------------------------------------------------------------------------
C_ConsoleQueue::~C_ConsoleQueue() {}
//-----------------------------------------------------------------------------
// �s�W���
void C_ConsoleQueue::Add(IN const nstring &szData)
{
	m_Data.push(szData);
}
//-----------------------------------------------------------------------------
// ���o���
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
// �s�W���
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
// ��ЦV�e�@�B
void C_ConsoleHistory::Prev()
{
	if(m_ulPos > 0)
		--m_ulPos;
}
//-----------------------------------------------------------------------------
// ��ЦV��@�B
void C_ConsoleHistory::Next()
{
	if(m_ulPos < m_Data.size())
		++m_ulPos;
}
//-----------------------------------------------------------------------------
// ���o��Щҫ���Ʀr��
nstring C_ConsoleHistory::Data() const
{
	return (m_ulPos >= 0 && m_ulPos < m_Data.size()) ? m_Data[m_ulPos] : __T("");
}
//-----------------------------------------------------------------------------
C_ConsoleKBStr::C_ConsoleKBStr() : m_wPos(0), m_bInsert(false) {}
//-----------------------------------------------------------------------------
C_ConsoleKBStr::~C_ConsoleKBStr() {}
//-----------------------------------------------------------------------------
// �]�w���D�r��
void C_ConsoleKBStr::SetTitle(IN const nstring &szTitle)
{
	m_szTitle = szTitle;
}
//-----------------------------------------------------------------------------
// �]�w���j�r��
void C_ConsoleKBStr::SetToken(IN const nstring &szToken)
{
	m_szToken = szToken;
}
//-----------------------------------------------------------------------------
// �M����Ʀr��
void C_ConsoleKBStr::ClrData()
{
	m_szData = __T("");
	m_wPos = 0;
}
//-----------------------------------------------------------------------------
// �]�w��Ʀr��
void C_ConsoleKBStr::SetData(IN const nstring &szData)
{
	if(szData.empty())
		return;

	m_szData = szData;
	m_wPos = static_cast<short>(m_szData.size());
}
//-----------------------------------------------------------------------------
// ���J��Ʀr��
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
// �V�e�R���r��
void C_ConsoleKBStr::DelPrev()
{
	if(m_wPos <= 0 || m_szData.empty())
		return;

	m_szData.erase(m_wPos - 1, 1);
	--m_wPos;
}
//-----------------------------------------------------------------------------
// �V��R���r��
void C_ConsoleKBStr::DelNext()
{
	if(m_szData.empty())
		return;

	m_szData.erase(m_wPos, 1);
}
//-----------------------------------------------------------------------------
// ��в��ʨ�̫e
void C_ConsoleKBStr::MoveFront()
{
	m_wPos = 0;
}
//-----------------------------------------------------------------------------
// ��в��ʨ�̧�
void C_ConsoleKBStr::MoveBack()
{
	m_wPos = static_cast<short>(m_szData.size());
}
//-----------------------------------------------------------------------------
// ��ЦV�e�@�B
void C_ConsoleKBStr::MovePrev()
{
	if(m_wPos > 0)
		--m_wPos;
}
//-----------------------------------------------------------------------------
// ��ЦV��@�B
void C_ConsoleKBStr::MoveNext()
{
	if(m_wPos < static_cast<short>(m_szData.size()))
		++m_wPos;
}
//-----------------------------------------------------------------------------
// �}�����N�X��
void C_ConsoleKBStr::Insert()
{
	m_bInsert = !m_bInsert;
}
//-----------------------------------------------------------------------------
// �ˬd�O�_����
bool C_ConsoleKBStr::Empty() const
{
	return m_szData.empty();
}
//-----------------------------------------------------------------------------
// ���o���D�r��
nstring C_ConsoleKBStr::Title() const
{
	return m_szTitle;
}
//-----------------------------------------------------------------------------
// ���o���j�r��
nstring C_ConsoleKBStr::Token() const
{
	return m_szToken;
}
//-----------------------------------------------------------------------------
// ���o��Ʀr��
nstring C_ConsoleKBStr::Data() const
{
	return m_szData;
}
//-----------------------------------------------------------------------------
// ���o�զX�r��
nstring C_ConsoleKBStr::Combination() const
{
	return m_szTitle + m_szToken + m_szData;
}
//-----------------------------------------------------------------------------
// ���o��Ʀr�����
unsigned long C_ConsoleKBStr::Size() const
{
	return m_szData.size();
}
//-----------------------------------------------------------------------------
// ���o��Ц�m
short C_ConsoleKBStr::GetPos() const
{
	return m_wPos;
}
//-----------------------------------------------------------------------------
C_Console::C_Console() {}
//-----------------------------------------------------------------------------
C_Console::~C_Console() {}
//-----------------------------------------------------------------------------
// �w�ɳB�z
void C_Console::Process()
{
	if(_kbhit())
	{
		ENUM_AKCodes emKey = getakcode();

		switch(emKey)
		{
		case ENUM_AKCodes_BACKSPACE: // ����Uback�䪺�B�z
			m_ccKBStr.DelPrev();
			break;

		case ENUM_AKCodes_ESC: // ����Uesc�䪺�B�z
			m_ccKBStr.ClrData();
			break;

		case ENUM_AKCodes_HOME: // ����Uhome�䪺�B�z
			m_ccKBStr.MoveFront();
			break;

		case ENUM_AKCodes_END: // ����Uend�䪺�B�z
			m_ccKBStr.MoveBack();
			break;

		case ENUM_AKCodes_INSERT: // ����Uinsert�䪺�B�z
			m_ccKBStr.Insert();
			break;

		case ENUM_AKCodes_DELETE: // ����Udelete�䪺�B�z
			m_ccKBStr.DelNext();
			break;

		case ENUM_AKCodes_UP: // ����Uup�䪺�B�z
			m_ccHistory.Prev();
			m_ccKBStr.SetData(m_ccHistory.Data());
			break;

		case ENUM_AKCodes_DOWN: // ����Udown�䪺�B�z
			m_ccHistory.Next();
			m_ccKBStr.SetData(m_ccHistory.Data());
			break;

		case ENUM_AKCodes_LEFT: // ����Uleft�䪺�B�z
			m_ccKBStr.MovePrev();
			break;

		case ENUM_AKCodes_RIGHT: // ����Uright�䪺�B�z
			m_ccKBStr.MoveNext();
			break;

		case ENUM_AKCodes_ENTER: // ����Uenter�䪺�B�z
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
// �]�w���D�r��
void C_Console::SetTitle(IN const nstring &szTitle)
{
	m_ccKBStr.SetTitle(szTitle);
}
//-----------------------------------------------------------------------------
// �]�w���j�r��
void C_Console::SetToken(IN const nstring &szToken)
{
	m_ccKBStr.SetToken(szToken);
}
//-----------------------------------------------------------------------------
// ���o���D�r��
nstring C_Console::GetTitle() const
{
	return m_ccKBStr.Title();
}
//-----------------------------------------------------------------------------
// ���o���j�r��
nstring C_Console::GetToken() const
{
	return m_ccKBStr.Token();
}
//-----------------------------------------------------------------------------
// ���o���O�r��
nstring C_Console::GetCommand()
{
	return m_Command.Data();
}
//-----------------------------------------------------------------------------
// ��ܫ��O
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