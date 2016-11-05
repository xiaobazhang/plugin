/*! \file Ix_TempFolder.h
 *  \brief Define temporary directory operation interface: Ix_TempFolder
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_ITEMPFOLDER_H_
#define X3_UTIL_ITEMPFOLDER_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_TempFolder, "6d215195-061e-4c03-827d-8c692c293617");

//! Temporary directory operation interface.
/*!
    \interface Ix_TempFolder
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_TempFolder
*/
class Ix_TempFolder : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_TempFolder)

    //! ���ø�Ŀ¼��Ӱ����������´����Ķ���
    /*!
        \param path ��Ŀ¼��ȫ��
    */
    virtual void SetRootPath(const std::wstring& path) = 0;

    //! ɾ����������ʱĿ¼
    /*! ��������ñ�����������ʱ��Ŀ¼���ڱ���������ʱ������˳�ʱҲ���Զ�ɾ��
        \return true if successful.
    */
    virtual bool DeleteFolder() = 0;

    //! ������ʱĿ¼����ʼ��
    /*! ����ʱ��Ŀ¼���ڱ���������ʱ������˳�ʱ�Զ�ɾ��
        \param prefix ��Ŀ¼����ǰ׺�����硰pdf��
        \return ��ʱĿ¼��ȫ�������ش�����С��2ʱ��ʾʧ��
    */
    virtual std::wstring CreateFolder(const std::wstring& prefix) = 0;

    //! ������ʱĿ¼��ȫ��
    virtual std::wstring GetPath() const = 0;

    //! �����µ���ʱ�ļ���
    /*!
        \param prefix �ļ���ǰ׺����Ϊ��
        \param ext �ļ���չ�������硰xml������_s.jpg��
        \return �µ��ļ�ȫ��
    */
    virtual std::wstring CreateFileName(const std::wstring& prefix, 
        const std::wstring& ext) = 0;
};

#endif // X3_UTIL_ITEMPFOLDER_H_
