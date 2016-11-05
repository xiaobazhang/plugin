/*! \file Ix_FileVersion.h
 *  \brief Define interface for getting file version: Ix_FileVersion
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_IFILEVERSION_H_
#define X3_UTIL_IFILEVERSION_H_

#include "Ix_Object.h"

//! interface for getting file version.
/*!
    \interface Ix_FileVersion
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileVersion : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_FileVersion)

    //! ��ȡģ����ļ��汾��
    /*!
        \param[out] version ���汾�ţ����硰1.0.12.0��
        \param[in] filename DLL��EXE���ļ�ȫ��
        \return �Ƿ��ȡ�ɹ�
    */
    virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename) = 0;

    //! ��ȡģ����ļ��汾��
    /*!
        \param[out] ver1 ���汾�ŵ����汾�����硰1.2.3.0����1
        \param[out] ver2 ���汾�ŵĴΰ汾�����硰1.2.3.0����2
        \param[out] ver3 ���汾�ŵĵ���λ�����硰1.2.3.0����3
        \param[out] ver4 ���汾�ŵĵ���λ�����硰1.2.3.0����0
        \param[in] filename DLL��EXE���ļ�ȫ��
        \return �Ƿ��ȡ�ɹ�
    */
    virtual bool GetFileVersion(WORD& ver1, WORD& ver2, 
        WORD& ver3, WORD& ver4, const std::wstring& filename) = 0;

    //! ��ȡģ����ļ�˵��
    /*!
        \param[out] description ����ļ�˵��
        \param[in] filename DLL��EXE���ļ�ȫ��
        \return �Ƿ��ȡ�ɹ�
    */
    virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename) = 0;
};

#endif // X3_UTIL_IFILEVERSION_H_
