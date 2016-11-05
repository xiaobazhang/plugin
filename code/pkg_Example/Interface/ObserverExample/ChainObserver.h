//! \file ChainObserver.h
//! \brief ����ְ�����۲����� ChainObserver

#ifndef EXAMPLE_CHAIN_OBSERVER_H_
#define EXAMPLE_CHAIN_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! ��Ϊ���ӵ�ְ�����۲�����
/*! �����������ö�������඼�ܴ���ͬһ������
    \note ����������ӱ���˽�м̳�
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserver : public Cx_ChangeObserver
{
public:
    //! ChainObserver �۲��ߵ�֪ͨ������
    class Data : public ChangeNotifyData
    {
    public:
        Data(int* _sum) : ChangeNotifyData("ChainObserver"), sum(_sum)
        {
        }

        int*    sum;
        NOCOPY_CONSTRUCTOR(Data);
    };

protected:
    ChainObserver() : Cx_ChangeObserver("ChainObserver")
    {
    }

    //! ����������Ӧְ����֪ͨ
    virtual void OnChain(int& sum)
    {
        sum;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);
        ASSERT(mydata && mydata->sum);
        OnChain(*(mydata->sum));
    }
    NOCOPY_CONSTRUCTOR(ChainObserver);
};

#endif // EXAMPLE_CHAIN_OBSERVER_H_