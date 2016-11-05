// x3c - C++ PluginFramework
#pragma once
#include "BaseTest.h"

#include "Ix_ObjectFactory.h"
#include "PluginManager/Ix_PluginLoader.h"

class TestPluginManager : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestPluginManager );
    CPPUNIT_TEST( testLoadUnloadPlugin );
    CPPUNIT_TEST( testLoadUnloadPlugins );
    CPPUNIT_TEST( testLoadPluginFiles );
    CPPUNIT_TEST( testInitializePlugins );
    CPPUNIT_TEST( testRegisterPlugin );

    CPPUNIT_TEST( testCreateObject );
    CPPUNIT_TEST( testIsCreatorRegister );
    CPPUNIT_TEST_SUITE_END();

public:
    TestPluginManager(void);
    ~TestPluginManager(void);

    virtual void setUp();
    virtual void tearDown();

public:
    void testLoadUnloadPlugin();
    void testLoadUnloadPlugins();
    void testLoadPluginFiles();
    void testInitializePlugins();
    void testRegisterPlugin();

    void testCreateObject();
    void testIsCreatorRegister();

private:
    Ix_PluginLoader* GetManagerLoader(void);
    Ix_ObjectFactory* GetManagerObjectFactory(void);
};
