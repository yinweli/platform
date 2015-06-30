//-----------------------------------------------------------------------------
#include "base64.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN
//-----------------------------------------------------------------------------
const char C_Base64::m_Padding = '@';
const char C_Base64::m_Encode[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
								   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
								   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
const char C_Base64::m_Decode[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 
								   52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, 
								   -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 
								   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, 
								   -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
								   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
								   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
const int C_Base64::m_Mod[] = {0, 2, 1};
//-----------------------------------------------------------------------------
// base64½s½X
nstring C_Base64::Encode(IN const nstring &szData) const
{
	if(szData.empty())
		return __T("");

	std::string szInput = C_NString(szData);
	int iInput = szInput.size();
	int iOutput = 4 * ((iInput + 2) / 3);
	char *pOutput = nstdnew char[iOutput + 1];

	if(pOutput == nullptr)
		return __T("");

	memset(pOutput, 0, iOutput + 1);

	for(int i = 0, j = 0; i < iInput; )
	{
		unsigned int octet_a = i < iInput ? (unsigned char)szInput[i++] : 0;
		unsigned int octet_b = i < iInput ? (unsigned char)szInput[i++] : 0;
		unsigned int octet_c = i < iInput ? (unsigned char)szInput[i++] : 0;
		unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		pOutput[j++] = m_Encode[(triple >> 3 * 6) & 0x3F];
		pOutput[j++] = m_Encode[(triple >> 2 * 6) & 0x3F];
		pOutput[j++] = m_Encode[(triple >> 1 * 6) & 0x3F];
		pOutput[j++] = m_Encode[(triple >> 0 * 6) & 0x3F];
	}//for

	for (int i = 0; i < m_Mod[iInput % 3]; i++)
		pOutput[iOutput - 1 - i] = 0;

	return C_NString(pOutput);
}
//-----------------------------------------------------------------------------
// base64¸Ñ½X
nstring C_Base64::Decode(IN const nstring &szData) const
{
	if(szData.empty())
		return __T("");

	std::string szInput = C_NString(szData);

	szInput.append(szData.size() % 4, m_Padding);

	int iInput = szInput.size();
	int iOutput = iInput / 4 * 3;

	if(szInput[iInput - 1] == m_Padding)
		--iOutput;

	if(szInput[iInput - 2] == m_Padding)
		--iOutput;

	unsigned char *pOutput = nstdnew unsigned char[iOutput + 1];

	if(pOutput == nullptr)
		return __T("");

	memset(pOutput, 0, iOutput + 1);

	for(int i = 0, j = 0; i < iInput; )
	{
		unsigned int sextet_a = szInput[i] == m_Padding ? 0 & i++ : m_Decode[szInput[i++]];
		unsigned int sextet_b = szInput[i] == m_Padding ? 0 & i++ : m_Decode[szInput[i++]];
		unsigned int sextet_c = szInput[i] == m_Padding ? 0 & i++ : m_Decode[szInput[i++]];
		unsigned int sextet_d = szInput[i] == m_Padding ? 0 & i++ : m_Decode[szInput[i++]];
		unsigned int triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

		if(j < iOutput)
			pOutput[j++] = (triple >> 2 * 8) & 0xFF;

		if(j < iOutput)
			pOutput[j++] = (triple >> 1 * 8) & 0xFF;

		if(j < iOutput)
			pOutput[j++] = (triple >> 0 * 8) & 0xFF;
	}//for

	return C_NString(reinterpret_cast<char *>(pOutput));
}
//-----------------------------------------------------------------------------
_NSTD_END
//-----------------------------------------------------------------------------