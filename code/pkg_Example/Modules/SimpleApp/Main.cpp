#include <UtilFunc/PluginInc.h>
#include <PluginManager/PluginManager.h>

// Include XComCreator.h in one and only one cpp file.
#include <PluginManager/XComCreator.h>

static void Test();

#if defined(_MSC_VER) && defined(UNICODE)
#define main wmain
#endif

int main()
{
    CPluginManager loader;

    if (loader.LoadPluginManager(L"../plugins"))
    {
        loader.GetPluginLoader()->LoadPlugins(L"../plugins");
        loader.GetPluginLoader()->InitializePlugins();

        Test();

        loader.Unload();
    }

    return 0;
}


#include <Ix_Example.h>

void MyFunc2(const Cx_Ptr& obj)
{
    long value = 0;

    // Cx_Interface��Cx_Ptr��ת��תΪ�ض��ӿ�
    Cx_Interface<Ix_Example> pIFExample(obj);
    if (pIFExample)
    {
        pIFExample->Foo(value);
        printf("value: %ld\n", value);
    }
}

static void Test()
{
    long value = 0;

    // ʹ����ID�ͽӿڴ�������
    Cx_Interface<Ix_Example> pIFExample(CLSID_Example);
    if (pIFExample)
    {
        pIFExample->Foo(value);    // ���ýӿں���
        printf("value: %ld\n", value);
    }

    // ת��Ϊ�����ӿ�
    Cx_Interface<Ix_Example2> pIFExample2(pIFExample);
    if (pIFExample2.IsNotNull())
    {
        pIFExample2->Foo2(value);
    }

    // תΪ�޽ӿ����͵�Cx_Ptr���ɱ��⺯������ʱ������������ӿ��ļ�
    MyFunc2(Cx_Ptr(pIFExample2));
}
