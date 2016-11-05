//! \file ChainObserverB.h
//! \brief ����ְ�����۲����� ChainObserverB

#ifndef EXAMPLE_CHAINB_OBSERVER_H_
#define EXAMPLE_CHAINB_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! ��Ϊ���ӵ�ְ�����۲�����
/*! �����������ö�������඼�ܴ���ͬһ�����ã��ж���֪ͨ����
    \note ����������ӱ���˽�м̳�
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserverB : public Cx_ChangeObserver
{
    NOCOPY_CONSTRUCTOR(ChainObserverB);
public:
    //! ChainObserverB �۲��ߵ�֪ͨ������
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        //! ��һ��ְ����֪ͨ
        static bool DoWork1(int value)
        {
            Data data(1, &value, NULL);
            data.Notify();
            return data.ret;
        }

        //! �ڶ���ְ����֪ͨ
        static bool DoWork2(char c)
        {
            Data data(2, NULL, &c);
            data.Notify();
            return data.ret;
        }

        int     type;
        bool    ret;
        int*    value;
        char*   c;

    private:
        Data(int _type, int* _value, char* _c)
            : ChangeNotifyData("ChainObserverB")
            , type(_type), ret(false), value(_value), c(_c)
        {
        }
    };

protected:
    ChainObserverB() : Cx_ChangeObserver("ChainObserverB")
    {
    }

    //! ����������Ӧ��һ��ְ����֪ͨ
    virtual bool OnChainWork1(int value)
    {
        value; return false;
    }

    //! ����������Ӧ�ڶ���ְ����֪ͨ
    virtual bool OnChainWork2(char c)
    {
        c; return false;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);

        switch (mydata->type)
        {
        case 1:
            mydata->ret = OnChainWork1(*(mydata->value)) || mydata->ret;
            break;

        case 2:
            mydata->ret = OnChainWork2(*(mydata->c)) || mydata->ret;
            break;

        default:
            ASSERT(0);
        }
    }
};

#endif // EXAMPLE_CHAINB_OBSERVER_H_
