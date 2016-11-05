// x3c - C++ PluginFramework
#include "UnitTestInc.h"
#include "TestPluginManager.h"

#include "Log/Ix_LogManager.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestPluginManager );

TestPluginManager::TestPluginManager(void)
{
}

TestPluginManager::~TestPluginManager(void)
{
}

void TestPluginManager::setUp()
{
    VERIFY(LoadPlugins(L"", false) >= 0);
}

void TestPluginManager::tearDown()
{
    UnloadPlugins();
}

void TestPluginManager::testLoadUnloadPlugin()
{
    Ix_PluginLoader* pLoader = GetManagerLoader();
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../plugins/LogManager.plugin" PLNEXT));
    VERIFY(NULL!=GetModuleHandleW(L"../plugins/LogManager.plugin" PLNEXT));

    VERIFY(pLoader->UnloadPlugin(L"../plugins/LogManager.plugin" PLNEXT));
    VERIFY(NULL==GetModuleHandleW(L"../plugins/LogManager.plugin" PLNEXT));
}

void TestPluginManager::testLoadUnloadPlugins()
{
    Ix_PluginLoader* pLoader = GetManagerLoader();
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugins(L"../plugins") > 0);
    VERIFY(pLoader->UnloadPlugins() > 0);
}

void TestPluginManager::testLoadPluginFiles()
{
}

void TestPluginManager::testInitializePlugins()
{
}

void TestPluginManager::testRegisterPlugin()
{
}

void TestPluginManager::testCreateObject()
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    Cx_Interface<Ix_PluginLoader> pLoader(pFactory);

    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../plugins/LogManager.plugin" PLNEXT));

    //Ix_Object* ixObject=NULL;
    //VERIFY(0==pFactory->CreateObject(x3::CLSID_LogManager, &ixObject,NULL));
    //ixObject->InterfaceRelease(NULL);

    VERIFY(pLoader->UnloadPlugin(L"../plugins/LogManager.plugin" PLNEXT));
}

void TestPluginManager::testIsCreatorRegister()
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    VERIFY(pFactory);

    VERIFY(false == pFactory->IsCreatorRegister(x3::CLSID_LogManager));

    Cx_Interface<Ix_PluginLoader> pLoader(pFactory);
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../plugins/LogManager.plugin" PLNEXT));

    VERIFY(true == pFactory->IsCreatorRegister(x3::CLSID_LogManager));

    VERIFY(pLoader->UnloadPlugin(L"../plugins/LogManager.plugin" PLNEXT));
}

Ix_PluginLoader* TestPluginManager::GetManagerLoader(void)
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    Cx_Interface<Ix_PluginLoader> pLoader(pFactory);
    return pLoader.P();
}

Ix_ObjectFactory* TestPluginManager::GetManagerObjectFactory(void)
{
    typedef Ix_ObjectFactory* (*FUNC_GETREGISTERBANK)();
    FUNC_GETREGISTERBANK pfnBank = (FUNC_GETREGISTERBANK)GetProcAddress(GetModuleHandleW(L"PluginManagerX3" PLNEXT), "x3GetRegisterBank");
    ASSERT(pfnBank != NULL);

    return pfnBank ? (*pfnBank)() : NULL;
}
