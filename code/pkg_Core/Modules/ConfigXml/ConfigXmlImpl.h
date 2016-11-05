// x3c - C++ PluginFramework
// Changes:
// 2011-01-18, Zhang Yungui: Delay call CoUninitialize until plugin is unloading.

#ifndef _X3_CONFIGXML_CONFIGXMLIMPL_H
#define _X3_CONFIGXML_CONFIGXMLIMPL_H

class IFileCryptHandler;
class Ix_ConfigData;

struct ConfigXmlImpl
{
    long                m_nTransaction;
    ULONG               m_nModifiedCount;
    std::wstring        m_strFileName;
    std::wstring        m_strRootName;
    std::wstring        m_strEncoding;
    std::wstring        m_strNameSpace;
    std::wstring        m_strSchemaLocation;
    bool                m_bModified;
    bool                m_bNeedLoad;
    XMLDOMDocumentPtr   m_xmlDoc;
    XMLDOMElementPtr    m_xmlRoot;
    IFileCryptHandler*  m_pCryptHandler;
    Ix_ConfigData*      m_pThis;

    ConfigXmlImpl(Ix_ConfigData* pThis) : m_pThis(pThis)
    {
        m_nTransaction = 0;
        m_nModifiedCount = 0;
        m_bModified = false;
        m_bNeedLoad = true;
        m_strEncoding = L"UTF-8";
        m_pCryptHandler = NULL;
    }

    ~ConfigXmlImpl()
    {
    }

    XMLDOMElementPtr GetRoot()
    {
        if (NULL == m_xmlRoot)
            Reload();
        return m_xmlRoot;
    }

    void SetModified(bool bModified = true)
    {
        m_bModified = bModified;
        if (bModified)
            m_nModifiedCount++;
    }

    bool Reload();
    void NewDoc();
    XMLDOMElementPtr GetParentNode(Ix_ConfigSection* pParent, std::wstring& strSection);
    XMLDOMElementPtr GetParentNode(XMLDOMElementPtr xmlParent, std::wstring& strSection);
};

#endif // _X3_CONFIGXML_CONFIGXMLIMPL_H
