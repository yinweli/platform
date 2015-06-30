//-----------------------------------------------------------------------------
#include "mathtool.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
#define RAND_MAX64 1125899906842623 ///< 64位元版本亂數最大值 @ingroup mathtool
//-----------------------------------------------------------------------------
unsigned __int64 g_ui64rand64seed = 9;
//-----------------------------------------------------------------------------
// 校正float轉換為int型態時會有1的誤差
int float2int(IN float f)
{
	int i = (int)f;
	float ferror = f - (float)i;

	if(fabs(ferror) > 0) // 出現1誤差, 需要校正
		((f < 0) ? i-- : i++);

	return i;
}
//-----------------------------------------------------------------------------
// 取得不重複隨機排列列表
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
// 取得指定範圍內的亂數(範圍從 0 ~ RAND_MAX)
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
// 設定亂數種子64位元版本
void srand64(unsigned __int64 ui64Seed)
{
	g_ui64rand64seed = ui64Seed;
}
//-----------------------------------------------------------------------------
// 取得亂數64位元版本
unsigned __int64 rand64()
{
	g_ui64rand64seed = g_ui64rand64seed * 2718281828459189 + 31415926535898011;

	return (unsigned __int64)(g_ui64rand64seed >> 14);
}
//-----------------------------------------------------------------------------
// 取得__int64型態絕對值
unsigned __int64 abs64(IN __int64 i)
{
	return (i >= 0) ? i : i * -1;
}
//-----------------------------------------------------------------------------
// 取得以2為底數的log結果
double log2(double f)
{
	return log(f) / log(2.0);
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------