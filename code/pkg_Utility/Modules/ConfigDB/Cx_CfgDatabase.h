/*! \file Cx_CfgDatabase.h
 *  \brief Define database I/O operator implement class: Cx_CfgDatabase
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.9.25
 */
// Changes:
// 2010-01-12, Zhang Yungui: Add readonly param in OpenConnection()

#ifndef _X3_CONFIGDB_CFGDATABASE_H
#define _X3_CONFIGDB_CFGDATABASE_H

#include <Xml/Ix_ConfigData.h>
#include <Xml/Ix_ConfigTransaction.h>
#include "Ix_InitDatabase.h"
#include "Ix_SQLParser.h"
#include "msado15.tlh"

class Cx_CfgRecordset;

//! Database I/O operator implement class.
class Cx_CfgDatabase
    : public Ix_ConfigData
    , public Ix_ConfigTransaction
    , public Ix_InitDatabase
{
    X3BEGIN_CLASS_DECLARE(Cx_CfgDatabase)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigData)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigTransaction)
        X3DEFINE_INTERFACE_ENTRY(Ix_InitDatabase)
    X3END_CLASS_DECLARE()
protected:
    //! ���캯��
    Cx_CfgDatabase();

    //! �����������Զ��ر����ݿ�
    virtual ~Cx_CfgDatabase();

public:
    //! ִ��SQL��䣬���ؼ�¼��
    _RecordsetPtr ExecuteSQL(LPCTSTR sql, const char* file, long line);

    //! ��������һ���Ӱ�������
    long GetRecordsAffected();

    //! �õ�һ����������ֶ�(����)���¼�¼ID
    bool GetRecordNewID(ULONG& newid, const std::wstring& table, 
        const std::wstring& field);

    //! ����һ��SELECT��䣬��ѯ��¼����
    bool GetRecordCount(long& count, const std::wstring& sqlSelect);

    //! ִ��SQL��䣬���ؼ�¼��
    Cx_Ptr OpenRecordset(const std::wstring& sqlSelect);

    //! ����SQLָ������
    Ix_SQLParser* GetSQLParser();

protected:
    //! �ر����ݿ�����
    void CloseConnection();

    //! �����սڵ����
    void CreateNullSection(Cx_Interface<Ix_ConfigSection>& pIFSec);

protected:
    _ConnectionPtr      m_pCon;             //!< ���ݿ����Ӷ���
    Ix_SQLParser*       m_pSQLParser;       //!< SQLָ������
    long                m_nRecordsAffected; //!< ����һ���Ӱ�������
    long                m_nModifiedCount;   //!< ���ݿ��¼�Ķ�����

protected:
    // Ix_InitDatabase
    virtual bool OpenConnection(const std::wstring& connection, 
        Ix_SQLParser* pSQLParser, bool readonly = false);

    // From Ix_ConfigTransaction
    virtual void BeginTransaction();
    virtual bool EndTransaction();
    virtual ULONG GetModifiedCount();

// From Ix_ConfigData
protected:
    //! ִ��SQL��䣬���ؼ�¼��
    /*! �����������ڶ�ȡ������¼������ʹ�ü�¼���� GetSectionByIndex() ���б�����ȡ���� GetSectionByIndex() �Ĵ���ʾ����
        \return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
        \param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ����������������
        \param ignore ���Ա�����
    */
    Cx_Ptr GetSection(const wchar_t* sqlSelect, bool ignore = true);

    //! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
    /*! �����������ڸ��ݱ���������Ҳ��޸ļ�¼�����磺 \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    Cx_ConfigSection secRec(secRecordset.GetSectionByIndex(L"", 0));
    secRec->SetString(L"title", L"test3");
    secRec->SetString(L"create_time", L"@CURDATE()");
    secRec->SetDate(L"update_date", 2010, 3, 10);
    VERIFY(Cx_ConfigTransaction(Cx_Ptr(secRec.P())).Submit());
        \endcode
        \return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
        \param nullP ����ΪNULL
        \param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \param ignore ���Ա�����
    */
    Cx_Ptr GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, ULONG condValue, 
        bool ignore = true);

    //! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
    /*! �����������ڶ�ȡ������¼������ʹ�ü�¼���� GetSectionByIndex() ���б�����ȡ���� GetSectionByIndex() �Ĵ���ʾ����
        \return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
        \param nullP ����ΪNULL
        \param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \param ignore ���Ա�����
    */
    Cx_Ptr GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, const wchar_t* condValue, 
        bool ignore = true);

    //! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
    /*!
        \return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
        \param nullP ����ΪNULL
        \param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \param fieldName2 ��ѯ�����еĵڶ����Ƚ��ֶΣ�Ϊ������Ը�����
        \param condValue2 fieldName2��Ӧ��ֵ�������ڲ�ѯ�бȽ���ȣ�fieldName2�ǿ�ʱ��Ч
        \param ignore ���Ա�����
    */
    Cx_Ptr GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, const wchar_t* condValue, 
        const wchar_t* fieldName2, const wchar_t* condValue2, 
        bool ignore = true);

    //! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
    /*!
        \return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
        \param nullP ����ΪNULL
        \param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \param fieldName2 ��ѯ�����еĵڶ����Ƚ��ֶΣ�Ϊ������Ը�����
        \param condValue2 fieldName2��Ӧ��ֵ�������ڲ�ѯ�бȽ���ȣ�fieldName2�ǿ�ʱ��Ч
        \param ignore ���Ա�����
    */
    Cx_Ptr GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, ULONG condValue, 
        const wchar_t* fieldName2, ULONG condValue2, 
        bool ignore = true);

    //! ���ؼ�¼���ļ�¼����
    /*! ����ʾ���� \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    if (1 == secRecordset.GetSectionCount(L"")) { }
        \endcode
        \param pRecordset ��¼������ͨ�� GetSection() �õ���
        \param ignore ���Ա�����
        \return ��¼����
    */
    long GetSectionCount(Ix_ConfigSection* pRecordset, const wchar_t* ignore);

    //! ����һ����¼����ָ����ŵļ�¼����
    /*! ���������ڶԼ�¼�����б�����ȡ������ʾ���� \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(
        L"SELECT id,title FROM article WHERE id=4"));
    for (long iRec = 0; iRec < 99; iRec++)
    {
        Cx_ConfigSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
        if (!secRec->IsValid())
            break;
        ULONG nID = secRec->GetUInt32(L"id");
        std::wstring wstrName = secRec->GetString(L"title");
    }
        \endcode
        \return ��¼���� Cx_CfgRecord ,��Ϊ��
        \param pRecordset ��¼������ͨ�� GetSection() �õ���
        \param ignore ���Ա�����
        \param index ��¼����ţ�ȡֵ����Ϊ0����¼���ĵ�ǰ��š���ǰ���+1
    */
    Cx_Ptr GetSectionByIndex(
        Ix_ConfigSection* pRecordset, const wchar_t* ignore, long index);

    //! ����һ���¼�¼�������ø����ֶε�ֵ
    /*! ��ʱ��δ�����ݿ������Ӽ�¼��
        ����ʹ�� \@NEWID ���ĳ���ֶ�ȡֵΪ(���ID+1)�����磺 \code
    Cx_ConfigSection secRec(pIFDb->AddSection(NULL, L"table"));
    secNewRec->SetString(L"id", L"@NEWID");
    secNewRec->SetString(L"title", L"test12");
    VERIFY(Cx_ConfigTransaction(Cx_Ptr(secNewRec.P())).Submit());
    ULONG nID = secNewRec->GetUInt32(L"id");
        \endcode
        \return �¼�¼���� Cx_CfgRecord
        \param nullP ����ΪNULL
        \param table ���ݿ���������硰book��
    */
    Cx_Ptr AddSection(Ix_ConfigSection* nullP, const wchar_t* table);

    //! ��֧�ֱ�����
    bool RemoveSection(Ix_ConfigSection*);

    //! ɾ��ָ�������ļ�¼
    /*! ����ʾ���� \code
    pIFDb->RemoveChildren(NULL, L"book", L"type", L"sometype");
        \endcode
        \param nullP ����ΪNULL
        \param table ���ݿ����
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶΣ�ͨ���������ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \return ɾ���ļ�¼��
    */
    long RemoveChildren(Ix_ConfigSection* nullP, const wchar_t* table, 
        const wchar_t* field = L"", const wchar_t* condValue = L"");

    //! ɾ��ָ�������ļ�¼
    /*! ����ʾ���� \code
    pIFDb->RemoveChildren(NULL, L"book", L"id", 1);
        \endcode
        \param nullP ����ΪNULL
        \param table ���ݿ����
        \param field ��ѯ�����еĵ�һ���Ƚ��ֶΣ�ͨ���������ֶ�
        \param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
        \return ɾ���ļ�¼��
    */
    long RemoveChildren(Ix_ConfigSection* nullP, const wchar_t* table, 
        const wchar_t* field, ULONG condValue);

    //! Returns the parent node of the specified node.(This function is not supported.)
    Cx_Ptr GetParentSection(Ix_ConfigSection*);
};

#endif // _X3_CONFIGDB_CFGDATABASE_H
