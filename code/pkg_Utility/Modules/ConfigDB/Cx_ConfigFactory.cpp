// x3c - C++ PluginFramework
//
// Changes:
// 2010-01-12, Zhang Yungui: Remove Ix_FileUtility.
//      Open access connection readonly if file is readonly.
//

#include <UtilFunc/PluginInc.h>
#include "Cx_ConfigFactory.h"
#include "Cx_CfgDatabase.h"
#include "ClsID_Internal.h"
#include "Ix_InitDatabase.h"
#include "Cx_SQLParser.h"

Cx_ConfigFactory::Cx_ConfigFactory()
{
}

Cx_ConfigFactory::~Cx_ConfigFactory()
{
}

Cx_Ptr Cx_ConfigFactory::OpenAccessDB(const std::wstring& filename, 
                                      const std::wstring& user, 
                                      const std::wstring& password)
{
    bool readonly = false;
    bool exist = x3CheckFileAttributes(filename.c_str(), &readonly, NULL);

    if (!exist)
    {
        X3LOG_ERROR2(L"@ConfigDB:IDS_NO_FILE", filename);
        return Cx_Ptr();
    }
    if (readonly)
    {
        X3LOG_INFO2(L"@ConfigDB:IDS_FILE_READONLY", filename);
    }

    std::wostringstream conn;

    if (_wcsicmp(wcsrchr(filename.c_str(), '.'), L".accdb") == 0)
    {
        conn << L"Provider=Microsoft.ACE.OLEDB.12.0;" ;
    }
    else
    {
        conn << L"Provider=Microsoft.Jet.OLEDB.4.0;" ;
    }
    conn << L"Data Source=" << filename << L";" ;

    if (!user.empty())
    {
        conn << L"User Id=" << user << L";" ;
    }
    if (password.empty())
    {
        conn << L"Password=" << password << L";" ;
    }
    else
    {
        conn << L"Jet OLEDB:Database Password=" << password << L";" ;
    }

    Cx_Interface<Ix_InitDatabase> pIFDB(x3::CLSID_CfgDatabase);
    ASSERT(pIFDB.IsNotNull());
    Ix_SQLParser* pSQLParser = new SQLParser_Access();

    return pIFDB->OpenConnection(conn.str(), pSQLParser, readonly)
        ? Cx_Ptr(pIFDB) : Cx_Ptr();
}

Cx_Ptr Cx_ConfigFactory::OpenSQLServerDB(const std::wstring& server, 
                                         const std::wstring& database, 
                                         const std::wstring& user, 
                                         const std::wstring& password)
{
    if (server.empty() || database.empty())
    {
        return Cx_Ptr();
    }

    std::wostringstream conn;

    conn << L"Provider=SQLOLEDB;"
        << L"Data Source=" << server << L";"
        << L"Initial Catalog=" << database << L";";

    if (!user.empty())
    {
        conn << L"User ID=" << user << L";" ;
        conn << L"Password=" << password << L";" ;
    }

    Cx_Interface<Ix_InitDatabase> pIFDB(x3::CLSID_CfgDatabase);
    ASSERT(pIFDB.IsNotNull());
    Ix_SQLParser* pSQLParser = new SQLParser_SQLServer();

    return pIFDB->OpenConnection(conn.str(), pSQLParser)
        ? Cx_Ptr(pIFDB) : Cx_Ptr();
}
