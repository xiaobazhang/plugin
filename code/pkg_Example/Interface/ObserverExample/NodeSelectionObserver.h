//! \file NodeSelectionObserver.h
//! \brief ����ڵ�ѡ��ı�۲����� NodeSelectionObserver

#ifndef EXAMPLE_NODESELECTION_OBSERVER_H_
#define EXAMPLE_NODESELECTION_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! ��Ϊ���ӵĽڵ�ѡ��ı�۲�����
/*! �����������������඼��Ӧ�ڵ�仯�����ɱ�������ѭ���仯
    \note ����������ӱ���˽�м̳�
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class NodeSelectionObserver : public Cx_ChangeObserver
{
    NOCOPY_CONSTRUCTOR(NodeSelectionObserver);
public:
    //! NodeSelectionObserver �۲��ߵ�֪ͨ������
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        Data(long _objid, NodeSelectionObserver* _sender)
            : ChangeNotifyData("NodeSelectionObserver")
            , objid(_objid), sender(_sender)
        {
        }

        long    objid;
        NodeSelectionObserver*   sender;
    };

protected:
    NodeSelectionObserver() : Cx_ChangeObserver("NodeSelectionObserver")
    {
    }

    //! ����������Ӧ�ڵ�ѡ��ı�֪ͨ
    virtual void OnNodeSelection(long objid, NodeSelectionObserver* sender)
    {
        objid; sender;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);
        OnNodeSelection(mydata->objid, mydata->sender);
    }
};

#endif // EXAMPLE_NODESELECTION_OBSERVER_H_
