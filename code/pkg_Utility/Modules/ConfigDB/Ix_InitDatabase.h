// x3c - C++ PluginFramework
//
// Changes:
// 2010-01-12, Zhang Yungui: Add readonly param in OpenConnection()
// 2011.06.30: Remove RTTI.

#ifndef _X3_CONFIGDB_INITDATABASE_INTERFACE_H
#define _X3_CONFIGDB_INITDATABASE_INTERFACE_H

class Ix_SQLParser;

//! ��ʼ�����ݿ���ʶ���Ľӿ�
class Ix_InitDatabase : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_InitDatabase)

    //! ָ��SQL���Ӵ������ݿ�
    virtual bool OpenConnection(const std::wstring& wstrConnection, 
        Ix_SQLParser* pSQLParser, bool readonly = false) = 0;
};

#endif // _X3_CONFIGDB_INITDATABASE_INTERFACE_H
