/**
 * @file algorithm.h
 * @note �t��k�t�C�禡
 * @author yinweli
 */
/**
 * @page �p��ϥ�algorithm
 * algorithm���t�@�Ǻt��k�����X\n\n
 * --------------------------------------------------\n
 * Header           : algorithm.h\n
 * Library(debug)   : \n
 * Library(release) : \n
 * --------------------------------------------------\n
 * �Բӻ����аѷ� @ref algorithm
 */
/** @defgroup algorithm */
#pragma once
#pragma warning(disable:4100; disable:4786)
//-----------------------------------------------------------------------------
#ifndef _ALGORITHM
#define _ALGORITHM
//-----------------------------------------------------------------------------
#include "..\_nstd\_nstd.h"
#include "..\_nstderr\_nstderr.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN; ///< namespace start
//-----------------------------------------------------------------------------
// map�t��k
/**
 * @brief �s�W��ƨ�std::map��, �p�G�w�����, �N�^�� end
 * @param r �n�ާ@��std::map����
 * @param k ���ޭ�
 * @param v ��ƭ�
 * @return �s�W�����N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator insertmap(OUT std::map<K, V> &r, IN const K k, IN const V v)
{
	std::map<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		return r.end();
	else
		return r.insert(Itor, std::map<K, V>::value_type(k, v));
}
/**
 * @brief �s�W�Χ�s��ƨ�std::map��
 * @param r �n�ާ@��std::map����
 * @param k ���ޭ�
 * @param v ��ƭ�
 * @return �s�W�Χ�s�����N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator updatemap(OUT std::map<K, V> &r, IN const K k, IN const V v)
{
	std::map<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		Itor->second = v;
	else
		Itor = r.insert(Itor, std::map<K, V>::value_type(k, v));

	return Itor;
}
/**
 * @brief �qstd::map���R������, �öǦ^���V�U�@�Ӥ��������N��
 * @note �зǪ���STL��, ���p�e����erase�禡���|�Ǧ^���V�U�@�Ӥ��������N��, ���OVC6.0�������|. �Өƹ�W�o�˼g��ı�o���²��, �ҥH�o�Ө禡�N�O�Ψӵ��¥Ϊk��
 * @param r �n�ާ@��std::map����
 * @param k ���ޭ�
 * @return �U�@�Ӥ��������N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::map<K, V>::iterator erasemap(OUT std::map<K, V> &r, IN const K k)
{
	std::map<K, V>::iterator Itor = r.find(k);

	r.erase(Itor++);

	return Itor;
}
/**
 * @brief �qstd::map���̷ӱ���P�_�R������
 * @param r �n�ާ@��std::map����
 * @param p ����P�_����
 * @ingroup algorithm
 */
template<typename K, typename V, typename P> void removeifmap(std::map<K, V> &r, P p)
{
	std::map<K, V>::iterator Itor = r.begin();

	while((Itor = std::find_if(Itor, r.end(), p)) != r.end())
		r.erase(Itor++);
}
//-----------------------------------------------------------------------------
// multimap�t��k
/**
 * @brief �s�W��ƨ�std::multimap��, �p�G�w�����, �N�^�� end
 * @param r �n�ާ@��std::multimap����
 * @param k ���ޭ�
 * @param v ��ƭ�
 * @return �s�W�����N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator insertmultimap(OUT std::multimap<K, V> &r, IN const K k, IN const V v)
{
	std::multimap<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		return r.end();
	else
		return r.insert(Itor, std::multimap<K, V>::value_type(k, v));
}
/**
 * @brief �s�W�Χ�s��ƨ�std::multimap��
 * @param r �n�ާ@��std::multimap����
 * @param k ���ޭ�
 * @param v ��ƭ�
 * @return �s�W�Χ�s�����N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator updatemultimap(OUT std::multimap<K, V> &r, IN const K k, IN const V v)
{
	std::multimap<K, V>::iterator Itor = r.lower_bound(k);

	if(Itor != r.end() && r.key_comp()(k, Itor->first) == false)
		Itor->second = v;
	else
		Itor = r.insert(Itor, std::multimap<K, V>::value_type(k, v));

	return Itor;
}
/**
 * @brief �qstd::multimap���R������, �öǦ^���V�U�@�Ӥ��������N��
 * @note �зǪ���STL��, ���p�e����erase�禡���|�Ǧ^���V�U�@�Ӥ��������N��, ���OVC6.0�������|. �Өƹ�W�o�˼g��ı�o���²��, �ҥH�o�Ө禡�N�O�Ψӵ��¥Ϊk��
 * @param r �n�ާ@��std::multimap����
 * @param k ���ޭ�
 * @return �U�@�Ӥ��������N��
 * @ingroup algorithm
 */
template<typename K, typename V> typename std::multimap<K, V>::iterator erasemultimap(OUT std::multimap<K, V> &r, IN const K k)
{
	std::multimap<K, V>::iterator Itor = r.find(k);

	r.erase(Itor++);

	return Itor;
}
/**
 * @brief �qstd::multimap���̷ӱ���P�_�R������
 * @param r �n�ާ@��std::multimap����
 * @param p ����P�_����
 * @ingroup algorithm
 */
template<typename K, typename V, typename P> void removeifmultimap(std::multimap<K, V> &r, P p)
{
	std::multimap<K, V>::iterator Itor = r.begin();

	while((Itor = std::find_if(Itor, r.end(), p)) != r.end())
		r.erase(Itor++);
}
//-----------------------------------------------------------------------------
_NSTD_END; ///< namespace end
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------