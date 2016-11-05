/*! \file Ix_FileTransaction.h
 *  \brief Define interface of file operation with transaction: Ix_FileTransaction
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_IFILETRANSACTION_H_
#define X3_UTIL_IFILETRANSACTION_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_FileTransaction, "66087749-6a2d-40b7-86d9-687664f91e1b");

//! interface of file operation with transaction.
/*!
    \interface Ix_FileTransaction
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileTransaction
*/
class Ix_FileTransaction : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_FileTransaction)

    //! �ӹ���״̬�ع�����
    virtual void Rollback() = 0;

    //! �õ��������������
    virtual long GetLevel() const = 0;

    //! �����Ƿ����ڻع�����
    virtual bool IsRollbacking() const = 0;

    //! ɾ��һ��Ŀ¼���ļ�
    /*!
        \param filename Ŀ¼���ļ����ļ�ȫ��
        \param recycle true��ʾ�Ž�����վ��false��ʾֱ��ɾ��
        \return �Ƿ���ɾ����Ŀ¼���ļ�. �ļ�ȫ��Ϊ�ջ��ļ��������򷵻�true
    */
    virtual bool DeletePathFile(const wchar_t* filename, bool recycle = false) = 0;
};

#endif // X3_UTIL_IFILETRANSACTION_H_
