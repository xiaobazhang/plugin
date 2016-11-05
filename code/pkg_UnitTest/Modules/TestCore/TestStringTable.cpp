// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestStringTable.h"
#include <Xml/Ix_StringTable.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestStringTable );

TestStringTable::TestStringTable()
{
}

void TestStringTable::setUp()
{
    VERIFY(LoadPlugins(L"StringTable.plugin" PLNEXT
        L",ConfigXml.plugin" PLNEXT
        L",LogManager.plugin" PLNEXT, false) >= 2);
}

void TestStringTable::tearDown()
{
    UnloadPlugins();
}

void TestStringTable::testSimple()
{
    Cx_Interface<Ix_StringTable> pIFTable(x3::CLSID_StringTable);
    ASSERT(pIFTable);

    pIFTable->LoadFiles(L"");

    std::wstring value, module, id;

    ASSERT(pIFTable->GetValue(value, L"StringTable", L"IDS_LOAD_STRFILE"));
    ASSERT(pIFTable->GetValue(value, L"@StringTable:IDS_LOAD_STRFILE", module, id)
        && module == L"StringTable" && id == L"IDS_LOAD_STRFILE");

    ASSERT(!pIFTable->GetValue(value, L"StringTable", L"XXX"));
    ASSERT(!pIFTable->GetValue(value, L"XXX", L"XXX"));
}
