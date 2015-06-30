//-----------------------------------------------------------------------------
#include "mathtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define RAND_MAX64 1125899906842623 ///< 64�줸�����üƳ̤j�� @ingroup mathtool
//-----------------------------------------------------------------------------
unsigned __int64 g_ui64rand64seed = 9;
//-----------------------------------------------------------------------------
// �ե�float�ഫ��int���A�ɷ|��1���~�t
int float2int(IN float f)
{
	int i = (int)f;
	float ferror = f - (float)i;

	if(fabs(ferror) > 0) // �X�{1�~�t, �ݭn�ե�
		((f < 0) ? i-- : i++);

	return i;
}
//-----------------------------------------------------------------------------
// ���o�������H���ƦC�C��
std::vector<int> uniquerandlist(IN int iMin, IN int iMax)
{
	std::vector<int> Result;

	if(iMin == iMax)
		return std::vector<int> { iMin };

	if(iMin > iMax)
		std::swap(iMin, iMax);

	std::generate_n(std::back_inserter(Result), iMax - iMin + 1, [&iMin] () { return iMin++; });
	std::random_shuffle(Result.begin(), Result.end());

	return Result;
}
//-----------------------------------------------------------------------------
// ���o���w�d�򤺪��ü�(�d��q 0 ~ RAND_MAX)
int rangerand(IN int iMin, IN int iMax)
{
	iMin = std::max(0, iMin);
	iMax = std::max(0, iMax);

	if(iMin == iMax)
		return iMin;

	if(iMin > iMax)
		std::swap(iMin, iMax);

	return (rand() % (iMax - iMin + 1)) + iMin;
}
//-----------------------------------------------------------------------------
// �]�w�üƺؤl64�줸����
void srand64(unsigned __int64 ui64Seed)
{
	g_ui64rand64seed = ui64Seed;
}
//-----------------------------------------------------------------------------
// ���o�ü�64�줸����
unsigned __int64 rand64()
{
	g_ui64rand64seed = g_ui64rand64seed * 2718281828459189 + 31415926535898011;

	return (unsigned __int64)(g_ui64rand64seed >> 14);
}
//-----------------------------------------------------------------------------
// ���o__int64���A�����
unsigned __int64 abs64(IN __int64 i)
{
	return (i >= 0) ? i : i * -1;
}
//-----------------------------------------------------------------------------
// ���o�H2�����ƪ�log���G
double log2(double f)
{
	return log(f) / log(2.0);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------