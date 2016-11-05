/*! \file Cx_ChangeObserver.h
 *  \brief Define the base classes of change observer data: ChangeNotifyData, Cx_ChangeObserver.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \version
 *      2010.10.22: First release.
 *      2011.02.08: Add parameter 'fromdll' in RegisterObserver.
 */
#ifndef X3_OBSERVER_CHANGENOTIFYDATA_H_
#define X3_OBSERVER_CHANGENOTIFYDATA_H_

#include "XComPtr.h"
#include "Ix_ChangeManager.h"

#ifndef NOCOPY_CONSTRUCTOR
#define NOCOPY_CONSTRUCTOR(cls) \
private:                \
    cls(const cls&);    \
    void operator=(const cls&)
#endif

//! The base class of change observer event data.
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see Cx_ChangeObserver
*/
class ChangeNotifyData
{
protected:
    //! Constructor. type is unique observer name passed from derived class.
    ChangeNotifyData(const char* type) : m_type(type)
    {
    }

public:
    //! Broadcast change event.
    void Notify()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(x3::CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->ChangeNotify(m_type, this);
        }
    }

    //! Return the unique observer name passed from derived class.
    const char* GetChangeType() const
    {
        return m_type;
    }

    //! Destructor for dynamic cast.
    virtual ~ChangeNotifyData()
    {
    }

private:
    ChangeNotifyData();
    NOCOPY_CONSTRUCTOR(ChangeNotifyData);

    const char*     m_type;
};

//! The base class of change observer.
/*! Derived class need implement DoUpdate().
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see ChangeNotifyData
*/
class Cx_ChangeObserver : public Ix_ChangeObserver
{
private:
    //! Process the change event.
    /*!
        \param data the event data which can be dynamic casted to specified class.
    */
    virtual void DoUpdate(ChangeNotifyData* data) = 0;

protected:
    //! Constructor. type is unique observer name passed from derived class.
    Cx_ChangeObserver(const char* type, bool register_now = true)
        : m_type(type), m_times(0)
    {
        if (register_now)
        {
            RegisterObserver();
        }
    }

    //! Return the unique observer name passed from derived class.
    const char* GetChangeType() const
    {
        return m_type;
    }

    //! Return if the change event is broadcasting.
    bool IsUpdating() const
    {
        return m_times != 0;
    }

    //! Delay register observer (passing false to constructor).
    void RegisterObserver()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(x3::CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->RegisterObserver(GetChangeType(), this, x3GetModuleHandle());
        }
    }

public:
    //! Destructor for unregister observer.
    virtual ~Cx_ChangeObserver()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(x3::CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->UnRegisterObserver(GetChangeType(), this);
        }
    }

private:
    void Update(ChangeNotifyData* data)
    {
        //ASSERT(data && 0 == strcmp(data->GetChangeType(), GetChangeType()));
        ++m_times;
        DoUpdate(data);
        --m_times;      // assume no exception
    }

private:
    Cx_ChangeObserver();
    NOCOPY_CONSTRUCTOR(Cx_ChangeObserver);

    const char*     m_type;
    long            m_times;
};

#endif // X3_OBSERVER_CHANGENOTIFYDATA_H_
