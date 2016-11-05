//! \file DocEventObserver.h
//! \brief �����ĵ��¼��۲����� DocEventObserver

#ifndef EXAMPLE_DOCEVENT_OBSERVER_H_
#define EXAMPLE_DOCEVENT_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! �ĵ��¼�����
enum kDocEventType
{
    kDocEvent_BeforeOpen,       //!< �ĵ���֮ǰ
    kDocEvent_AfterOpen,        //!< �ĵ���֮��
    kDocEvent_OpenFail,         //!< �ĵ���ʧ��
};

//! ��Ϊ���ӵ��ĵ��¼��۲�����
/*! �����������������඼����Ӧ����¼�֪ͨ
    \note ����������ӱ���˽�м̳�
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class DocEventObserver : public Cx_ChangeObserver
{
    NOCOPY_CONSTRUCTOR(DocEventObserver);
public:
    //! DocEventObserver �۲��ߵ�֪ͨ������
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        Data(kDocEventType _event)
            : ChangeNotifyData("DocEventObserver")
            , event(_event), count(0)
        {
        }

        kDocEventType   event;
        long            count;
    };

protected:
    DocEventObserver() : Cx_ChangeObserver("DocEventObserver")
    {
    }

    //! ��Ӧ�ĵ���֮ǰ��֪ͨ
    virtual bool OnDocEventBeforeOpen() { return false; }

    //! ��Ӧ�ĵ���֮���֪ͨ
    virtual bool OnDocEventAfterOpen() { return false; }

    //! ��Ӧ�ĵ���ʧ�ܵ�֪ͨ
    virtual bool OnDocEventOpenFail() { return false; }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);

        switch (mydata->event)
        {
        case kDocEvent_BeforeOpen:
            if (OnDocEventBeforeOpen())
                mydata->count++;
            break;

        case kDocEvent_AfterOpen:
            if (OnDocEventAfterOpen())
                mydata->count++;
            break;

        case kDocEvent_OpenFail:
            if (OnDocEventOpenFail())
                mydata->count++;
            break;

        default:
            ASSERT(0);
        }
    }
};

#endif // EXAMPLE_DOCEVENT_OBSERVER_H_
