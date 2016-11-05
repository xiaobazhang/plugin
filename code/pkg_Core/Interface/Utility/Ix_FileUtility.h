/*! \file Ix_FileUtility.h
 *  \brief Define file operation interface: Ix_FileUtility
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_IFILEUTILITY_H_
#define X3_UTIL_IFILEUTILITY_H_

#include <XComPtr.h>

X3CLSID_DEFINE(CLSID_FileUtility, "933b3bf9-69d0-4be7-8e49-92b73669d8db");

//! File operation interface(querying file information)
/*!
    \interface Ix_FileUtility1
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility1
{
public:
    virtual ~Ix_FileUtility1() {}

    //! ���һ��Ŀ¼���ļ��Ƿ����
    /*!
        \param filename Ŀ¼���ļ����ļ�ȫ���������Ŀ¼��ĩβҪ��б��
        \param checkWrite �Ƿ����д
        \return Ŀ¼���ļ��Ƿ���ڣ����checkWriteΪtrue��ͬʱҪ��ɶ�д
    */
    virtual bool IsPathFileExists(const wchar_t* filename, bool checkWrite = false) = 0;

    //! ����Ƿ�ΪĿ¼��
    /*!
        \param filename Ŀ¼���ļ����ļ�ȫ����
            ���checkExistsΪtrue��Ŀ¼ĩβ��б�ſ��п���
        \param checkExists �Ƿ����ʵ���ļ�������������Ƿ�ΪĿ¼��
        \return true:Ŀ¼, false:�ļ�
    */
    virtual bool IsPath(const wchar_t* filename, bool checkExists = false) = 0;

    //! �����ļ��޸�����ʱ��
    /*!
        \param filename �ļ�ȫ��
        \return ����ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS����ʧ��ʱΪ�մ�
    */
    virtual std::wstring GetModifyTime(const std::wstring& filename) = 0;

    //! �����ļ���С���ֽ�
    /*!
        \param filename �ļ�ȫ��
        \return �ļ���С���ֽڣ�ʧ��ʱΪ0������4GʱΪ0xFFFFFFFF
        \see FileSizeToString
    */
    virtual DWORD GetFileSize(const std::wstring& filename) = 0;
};

//! File operation interface(changing file)
/*!
    \interface Ix_FileUtility2
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility2
{
public:
    virtual ~Ix_FileUtility2() {}

    //! Ϊһ���ļ�ȫ�����������м�Ŀ¼
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־
        \param filename �ļ���Ŀ¼��ȫ��
        \param isPath ������filename��·���������ļ���
        \return �Ƿ񴴽��ɹ�
    */
    virtual bool CreateDirectory(const wchar_t* filename, bool isPath) = 0;

    //! ȷ��һ���ļ����ǿ�д��(�Զ�����Ŀ¼��ȥ��ֻ������)
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־
        \param filename �ļ�ȫ��
        \return �Ƿ�ɴ����ļ���ɸ�д
    */
    virtual bool VerifyFileCanWrite(const wchar_t* filename) = 0;

    //! ɾ��һ��Ŀ¼���ļ�
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־
        \param filename Ŀ¼���ļ����ļ�ȫ��
        \param recycle true��ʾ�Ž�����վ��false��ʾֱ��ɾ��
        \return true if successful. �ļ�ȫ��Ϊ�ջ��ļ��������򷵻�true
    */
    virtual bool DeletePathFile(const wchar_t* filename, bool recycle = false) = 0;

    //! �ƶ�һ��Ŀ¼���ļ�
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־���Զ�����Ŀ���ļ����ļ���
        \param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
        \param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
        \return true if successful. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
    */
    virtual bool MovePathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! ������һ��Ŀ¼���ļ�
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־
        \param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
        \param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
        \return true if successful. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
    */
    virtual bool RenamePathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! ����һ��Ŀ¼���ļ�
    /*! ʧ��ʱ���� X3LOG_ERROR2 ��¼��־���Զ�����Ŀ���ļ����ļ���
        \param oldFile ԭ����Ŀ¼���ļ����ļ�ȫ��
        \param newFile �µ�Ŀ¼���ļ����ļ�ȫ��
        \return true if successful. oldFileΪ�ջ�ԭ�ļ��������򷵻�true
    */
    virtual bool CopyPathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! ������Ϣ���ӵ���ߴ���
    virtual void SetMsgBoxOwnerWnd(HWND hwnd) = 0;

    //! ������Ϣ���ӵ���ߴ���
    virtual HWND GetMsgBoxOwnerWnd() = 0;
};

//! File operation interface(changing file name)
/*!
    \interface Ix_FileUtility3
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility3
{
public:
    virtual ~Ix_FileUtility3() {}

    //! ���·��ת��Ϊ����·��
    /*! ��һ������ڸ����ο�·�������·��ת��Ϊ����·��������Ѿ��Ǿ���·���򲻱�
        \param relFile Ҫת�������·�������硰./abc������/Root������../1/2.dat��
        \param relIsFile ���·�����ļ�������·����
        \param baseFile �ο�·����������ĸ�·����ת����Ϊ����ȡEXE·��
        \param baseIsFile �ο�·�����ļ�������·����
        \return ת����ľ���·�������relIsFileΪfalse�����·��ĩβ��б��
    */
    virtual std::wstring RelToAbs(const wchar_t* relFile, bool relIsFile,
        const wchar_t* baseFile = NULL, bool baseIsFile = true) = 0;

    //! ����·��ת��Ϊ���·��
    /*! ��һ������·��ת��Ϊ����ڸ����ο�·�������·��
        \param absFile Ҫת���ľ���·��
        \param absIsFile ����·�����ļ�������·����
        \param baseFile �ο�·����������ĸ�·����ת����Ϊ����ȡEXE·��
        \param baseIsFile �ο�·�����ļ�������·����
        \return ת��������·�������relIsFileΪfalse�����·��ĩβ��б�ţ�
            ���ʧ�����ԭ��·����ͬ
    */
    virtual std::wstring AbsToRel(const wchar_t* absFile, bool absIsFile,
        const wchar_t* baseFile = NULL, bool baseIsFile = true) = 0;

    //! �ı��ļ�ȫ���ĺ�׺��
    /*!
        \param[in] filename �������ļ�ȫ�������ļ��Ƿ�����޹�
        \param[in] suffix �µĺ�׺�������뺬�е��
        \return �µ��ļ�ȫ��
    */
    virtual std::wstring ChangeFileNameSuffix(
        const wchar_t* filename, const wchar_t* suffix) = 0;

    //! ����·�����ļ�������׺���γ�һ���ļ�ȫ��
    /*!
        \param path Ŀ¼ȫ�����ǿգ�ĩβ��б�ſ��п���
        \param title �ļ������⣬�ǿգ�����·�������ext��Ϊ������Ժ�׺��
        \param ext �ļ���չ��������·�����ļ������⣬����û�е��
        \return �µ��ļ�ȫ��
    */
    virtual std::wstring MakeFileName(const std::wstring& path,
        const std::wstring& title, const std::wstring& ext) = 0;

    //! �����µ�����ļ���
    /*!
        \param path Ŀ¼ȫ�������ļ��ڸ�Ŀ¼��Ψһ��ĩβ��б�ſ��п���
        \param prefix �ļ���ǰ׺�����硰t������Ϊ��
        \param ext �ļ���չ������ſ��Բ��ǵ�һ���ַ���û�е������Զ����ϣ�
            ���硰xml������_s.jpg��
        \param returnRel �Ƿ񷵻�����ļ�����false��ʾ�����µľ����ļ�ȫ��
        \return �µ�����ļ��������硰t12.xml��
    */
    virtual std::wstring CreateFileName(const std::wstring& path,
        const std::wstring& prefix, const std::wstring& ext,
        bool returnRel = true) = 0;
};

//! File operation interface(getting parts of file name)
/*!
    \interface Ix_FileUtility4
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility4
{
public:
    virtual ~Ix_FileUtility4() {}

    //! �õ��ļ������⣬��·���ͺ�׺��
    virtual std::wstring GetFileTitle(const wchar_t* filename) = 0;

    //! �õ��ļ���Ŀ¼���ļ�������·��
    virtual std::wstring GetFileName(const wchar_t* filename) = 0;

    //! �õ��ļ���չ�������е��
    virtual std::wstring GetExtension(const wchar_t* filename) = 0;

    //! �õ��ļ���Ŀ¼���ڵ�Ŀ¼��ĩβ��б��
    /*!
        \param filename �ļ���Ŀ¼���ļ�ȫ����Ŀ¼ĩβ��б�ſ��п���
        \return ���ڵ�Ŀ¼��ĩβ��б��
    */
    virtual std::wstring GetPathOfFile(const wchar_t* filename) = 0;

    //! �ж������ļ����Ƿ���ͬ
    /*! �������Ƚ������ļ�ȫ������������ļ������Զ�����Ŀ¼�ָ���
        \param[in] filename1 ��һ���ļ��л��ļ����ļ���
        \param[in] filename2 �ڶ����ļ��л��ļ����ļ���
        \param[out] samePartCount �����ΪNULL������ļ������м���������ͬ�ģ�
            �����ļ�ȫ���ĸ�������ָ�м��ļ��������ļ�������
        \return 0��ʾ�ļ�����ͬ��1��-1��ʾ�ļ�����ͬ
    */
    virtual int CompareFileName(const wchar_t* filename1, const wchar_t* filename2,
        long* samePartCount = NULL) = 0;
};

//! File operation interface
/*!
    \interface Ix_FileUtility
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility
    \see x3::FileUtility(), RelToAbs.h
*/
class Ix_FileUtility : public Ix_Object
    , public Ix_FileUtility1
    , public Ix_FileUtility2
    , public Ix_FileUtility3
    , public Ix_FileUtility4
{
public:
    X3DEFINE_IID(Ix_FileUtility)
};

namespace x3 {

//! Get file operator object.
/*!
    \ingroup _GROUP_UTILITY_
    \see RelToAbs.h
*/
inline Cx_Interface<Ix_FileUtility> FileUtility()
{
    Cx_Interface<Ix_FileUtility> pIFUtility(x3::CLSID_FileUtility);
#ifdef ASSERT
    ASSERT(pIFUtility.IsNotNull());
#endif
    return pIFUtility;
}

} // x3

#endif // X3_UTIL_IFILEUTILITY_H_
