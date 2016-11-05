//! \file XmlUtil.h
//! \brief Define XML DOM wrapper class using TinyXml: CXmlUtil.

#ifndef __XMLUTIL_TINYXML_INCLUDED_
#define __XMLUTIL_TINYXML_INCLUDED_

// ticpp: http://ticpp.googlecode.com/svn/trunk
#define TIXML_USE_STL
#include "tinyxml.h"

template <class T>
class XMLDOMPtr
{
public:
    XMLDOMPtr(void* /*null*/ = 0) : m_data(NULL)
    {
    }

    XMLDOMPtr(const XMLDOMPtr& src) : m_data(src.m_data)
    {
        if (m_data)
        {
            InterlockedIncrement(&(m_data->second));
        }
    }

    ~XMLDOMPtr()
    {
        Free();
    }

    XMLDOMPtr& operator=(const XMLDOMPtr& src)
    {
        if (this != &src)
        {
            Free();
            m_data = src.m_data;
            if (m_data)
            {
                InterlockedIncrement(&(m_data->second));
            }
        }
        return *this;
    }

    XMLDOMPtr& operator=(void* /*null*/)
    {
        Free();
        return *this;
    }

    void Free()
    {
        if (m_data)
        {
            if (0 == InterlockedDecrement(&(m_data->second)))
            {
                delete m_data->first;
            }
            m_data = NULL;
        }
    }

    operator T*() { return m_data ? m_data->first : NULL; }
    operator const T*() const { return m_data ? m_data->first : NULL; }

private:
    std::pair<T*, long>*    m_data;
};

typedef XMLDOMPtr<TiXmlDocument> XMLDOMDocumentPtr;
typedef XMLDOMPtr<TiXmlElement> XMLDOMElementPtr;

//! Interface of xml file encryption and decryption.
class IXmlFileCrypt
{
public:
    virtual ~IXmlFileCrypt() {}

    //! Load a xml file encrypted.
    /*!
        \param[out] doc new xml document object.
        \param[in] filename absolute file name, or Web Service URL.
        \return true if successful. CXmlUtil will load directly if returns false.
    */
    virtual bool Decrypt(XMLDOMDocumentPtr& doc, const wchar_t* filename) = 0;

    //! Encrypt a xml file after saved.
    /*!
        \param[in] filename absolute file name.
        \return true if successful.
    */
    virtual bool CryptFile(const wchar_t* filename) = 0;
};

//! XML DOM wrapper class using TinyXml.
class CXmlUtil
{
public:

//--------------------------------------
// �ļ�����
//--------------------------------------

    //! ����һ��XML�ĵ�����
    /*! �´�����XML�ĵ�����δ���浽�ļ���
        \param[out] doc new xml document object.
        \param[in] rootName ���ڵ����ƣ������Զ��������ڵ�
        \param[in] encoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
        \param[in] nameSpace XML�����ռ�
        \param[in] comment ���ڵ��˵������
        \return �Ƿ񴴽��ɹ�
    */
    static bool NewXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* rootName,
        const wchar_t* encoding = L"UTF-8",
        const wchar_t* nameSpace = L"",
        const wchar_t* comment = L"");

    //! ����һ��XML�ĵ����󣬲��õ����ڵ�
    /*! �´�����XML�ĵ�����δ���浽�ļ���
        \param[out] doc new xml document object.
        \param[in] root ������ڵ����
        \param[in] rootName ���ڵ����ƣ������Զ��������ڵ�
        \param[in] encoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
        \param[in] nameSpace XML�����ռ�
        \return �Ƿ񴴽��ɹ�
    */
    static bool NewXMLFile2(
        XMLDOMDocumentPtr& doc,
        XMLDOMElementPtr& root,
        const wchar_t* rootName,
        const wchar_t* encoding = L"UTF-8",
        const wchar_t* nameSpace = L"");

    //! װ��һ��XML�ļ�
    /*!
        \param[out] doc new xml document object.
        \param[in] filename absolute file name, or Web Service URL.
        \param[in] handler �ӽ��ܵĲ�������
        \return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ��ܶ�ȡ�ļ����ܴ���XML�ĵ�����
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* handler = NULL);

    //! װ��һ��XML�ļ����������ڵ�
    /*!
        \param[out] doc new xml document object.
        \param[in] filename absolute file name, or Web Service URL.
        \param[in] root ������ڵ����
        \param[in] rootName ���ڵ�����
        \param[in] handler �ӽ��ܵĲ�������
        \return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ�����ָ���ĸ��ڵ�ȴ���
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        XMLDOMElementPtr& root,
        const wchar_t* rootName,
        IXmlFileCrypt* handler = NULL);

    //! ���浽һ��XML�ļ�
    /*!
        \param[in] doc Ҫ�����XML�ĵ�����
        \param[in] filename �ļ�ȫ��
        \param[in] handler �ӽ��ܵĲ�������
        \return �Ƿ񱣴�ɹ�
    */
    static bool SaveXMLFile(
        const XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* handler = NULL);

    //! ���ַ�����װ��XML�ļ�
    /*!
        \param[out] doc ����´�����XML�ĵ�����
        \param[in] xmlstr XML��ʽ���ַ���
        \return �Ƿ�װ�سɹ�
    */
    static bool LoadXMLFromString(
        XMLDOMDocumentPtr& doc,
        const wchar_t* xmlstr);

    //! ��ȡXML�ַ���
    /*!
        \param[in] doc xml document object.
        \return XML��ʽ���ַ���
        \see GetNodeXMLString
    */
    static std::wstring GetXMLString(
        const XMLDOMDocumentPtr& doc);

    //! ��ȡ���ڵ�����
    /*!
        \param[in] doc xml document object.
        \return ���ڵ�����
        \see GetTagName
    */
    static std::wstring GetRootName(
        const XMLDOMDocumentPtr& doc);

//--------------------------------------
// �ڵ����
//--------------------------------------

    //! �õ����ڵ�
    /*!
        \param[out] root ���XML���ڵ����
        \param[in] doc xml document object.
        \param[in] rootName ���ڵ�����
        \return �Ƿ���ڸ������Ƶĸ��ڵ�
        \see GetRootName
    */
    static bool GetRoot(
        XMLDOMElementPtr& root,
        const XMLDOMDocumentPtr& doc,
        const wchar_t* rootName);

    //! �õ��ӽڵ����
    /*!
        \param[in] ele xml element object.
        \param[in] childName ��Ԫ������
        \return ����Ԫ��ele�µ�����ΪchildName���ӽڵ����
    */
    static long GetChildCount(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName);

    //! �õ�һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] parent xml element object.
        \param[in] childName ��Ԫ������
        \param[in] index �ڼ�����Ԫ�أ���0��ʼ
        \return �Ƿ��ж�Ӧ����Ԫ�ض���
    */
    static bool GetChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        long index = 0);

    //! �õ��򴴽�һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] doc xml document object.
        \param[in] parent xml element object.
        \param[in] childName ��Ԫ������
        \return true if successful.
    */
    static bool GetChildOrAdd(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName);

    //! ���һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] childName ��Ԫ������
        \return true if successful.
    */
    static bool AddChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* childName);

    //! ɾ��һ���ӽڵ�
    /*!
        \param[in] ele xml element object.
        \param[in] childName ��Ԫ������
        \param[in] index Ҫɾ���ڼ�����Ԫ�أ���0��ʼ
        \return �Ƿ��ж�Ӧ����Ԫ�ض���ɾ��
    */
    static bool DelChild(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName,
        long index);

    //! ɾ��һ���ӽڵ�
    /*!
        \param[in] parent XML��Ԫ�ض���
        \param[in,out] eleDel Ҫɾ����XML��Ԫ�ض���
        \return �Ƿ��ж�Ӧ����Ԫ�ض���ɾ��
    */
    static bool DelChild(
        const XMLDOMElementPtr& parent,
        XMLDOMElementPtr& eleDel);

    //! ɾ�������ӽڵ�
    /*! ɾ������Ԫ���µ���������ΪchildName���ӽڵ�
        \param[in] ele xml element object.
        \param[in] childName ��Ԫ������
        \param[in] attrName ��Ԫ�صı�ʶ����������ѡֵ
        \param[in] attrValue ��ʶ��������Ӧ��ֵ��attrName��Ϊ��ʱ��Ч
        \return ɾ������Ԫ�ظ���
    */
    static long DelChildren(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName,
        const wchar_t* attrName = L"", const wchar_t* attrValue = L"");

    //! ���ҽڵ������е��ӽڵ����
    /*!
        \param[out] outEle ������ҵ�����Ԫ�ض���
        \param[in] parent xml element object.���ڸýڵ��²���
        \param[in] childName ��Ԫ������
        \param[in] fieldName ��Ԫ�ص���һ��Ԫ������
        \param[in] value ��Ԫ�ص���һ��Ԫ�ص�����
        \return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
    */
    static long FindElement(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        const wchar_t* fieldName,
        const wchar_t* value);

    //! ���ҽڵ������е��ӽڵ����
    /*! ����Ԫ��parent����Ԫ�ؽڵ㣬�����Ǹ���Ԫ����������Ϊattr1��
        ����Ϊvalue1�����Խڵ㣬��������������������\n
        ��������������ʾ����\n
        ��\<parent_item\>\n
        ������\<item id="12" type="font" other=""\>\<otherinfo/\>\</item\>\n
        ������\<item id="34" type="char" other=".."\>\<otherinfo/\>\</item\>\n
        ������\<item id="34" type="para" other="info"\>\<otherinfo/\>\</item\>\n
        ��\</parent_item\>\n
        ����FindElement(outEle, parent, "item", "id", "34", "type", "char")����1

        \param[out] outEle ������ҵ�����Ԫ�ض���
        \param[in] parent xml element object.���ڸýڵ��²���
        \param[in] childName ��Ԫ������
        \param[in] attr1 ��Ԫ�ص���������
        \param[in] value1 ��Ԫ�ص�����ֵ
        \param[in] attr2 ��Ԫ�ص���һ���������ƣ�Ϊ�������
        \param[in] value2 ��Ԫ�ص���һ�����Զ�Ӧ��ֵ��attr2��Ϊ��ʱ��Ч
        \return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
    */
    static long FindElementByAttr(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        const wchar_t* attr1,
        const wchar_t* value1,
        const wchar_t* attr2,
        const wchar_t* value2);

//--------------------------------------
// �ڵ�����
//--------------------------------------

    //! �õ��ڵ������
    /*!
        \param[in] ele xml element object.
        \return �����ڵ��XML�������
        \see GetRootName
    */
    static std::wstring GetTagName(
        const XMLDOMElementPtr& ele);

    //! �õ��ڵ����ݣ�ʶ��CDATA
    /*! �ڵ�����ݼȿ����Ǽ򵥵��������ݣ�Ҳ������CDATA�ڵ�
        \param[in] ele xml element object.
        \param[in] defValue �ڵ����ݵ�Ĭ��ֵ
        \return �����ڵ������
    */
    static std::wstring GetText(
        const XMLDOMElementPtr& ele,
        const wchar_t* defValue = L"");

    //! �õ�һ���ڵ��CDATAֵ
    /*!
        \param[in] ele xml element object.
        \param[in] defValue �ڵ��CDATA���ݵ�Ĭ��ֵ
        \return �ýڵ��CDATA����
    */
    static std::wstring GetTextCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* defValue = L"");

    //! ���ýڵ�����
    /*!
        \param[in] ele xml element object.
        \param[in] text �����ڵ������
        \return true if successful.
    */
    static bool SetText(
        const XMLDOMElementPtr& ele,
        const wchar_t* text);

    //! ���ýڵ�����
    /*!
        ���������ڲ����Ƿ�����_UNICODE��������꣬����ֱ�����ÿ��ֽ��ַ������ݣ�
        ������ANSI����ģʽ�½�LPCWSTRת��ΪBSTRʱ�Զ����б���ת�����������롣

        ʹ������������ӷ�UNICODE�ı��ļ��ж�ȡ���ֽ��ַ�������MultiByteToWideChar
        ����ת��Ϊ���ֽ��ַ��������ñ��������ýڵ����ݣ��������ܽ��ض����Ա����
        ����ת��ΪUNICODE��XML���ݡ�

        \param[in] ele xml element object.
        \param[in] text �����ڵ��UNICODE���ݣ�ĩβ���������
        \return true if successful.
    */
    static bool SetTextW(
        const XMLDOMElementPtr& ele,
        const wchar_t* text);

    //! ����һ���ڵ��CDATAֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] value �ڵ��CDATA����
        \return true if successful.
    */
    static bool SetTextCDATA(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* value);

    //! ��ȡһ���ڵ��XML�ַ���
    /*!
        \param[in] ele xml element object.
        \return XML�ַ���
        \see GetXMLString
    */
    static std::wstring GetNodeXMLString(
        const XMLDOMElementPtr& ele);

//--------------------------------------
// ���Բ���
//--------------------------------------

    //! ɾ��һ������
    /*!
        \param[in] ele xml element object.
        \param[in] name Ҫɾ������������
        \return �Ƿ�ɾ��������
    */
    static bool DelAttribute(
        const XMLDOMElementPtr& ele,
        const wchar_t* name);

    //! �õ�һ�����Խڵ�����
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] defValue �������ݵ�Ĭ��ֵ
        \return ��Ԫ�ص���������
    */
    static std::wstring GetAttribute(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        const wchar_t* defValue = L"");

    //! �õ�һ�����Խڵ���������
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] defValue �������ݵ�Ĭ������ֵ
        \return ��Ԫ�ص�������������ֵ
    */
    static int GetAttributeInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        int defValue = 0);

    //! �õ�һ�����Խڵ㲼��ֵ����
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] defValue �������ݵ�Ĭ�ϲ���ֵ
        \return ��Ԫ�ص��������ݲ���ֵ
    */
    static bool GetAttributeBool(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        int defValue = 0);

    //! �õ�һ�����Խڵ㸡��������
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] defValue �������ݵ�Ĭ�ϸ�����ֵ
        \param[out] unitName ������������ַ��������������β���ĵĵ�λ����
        \return ��Ԫ�ص��������ݸ�����ֵ
    */
    static double GetAttributeFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        double defValue = 0,
        std::wstring* unitName = NULL);

    //! ����һ�����Խڵ�����
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
        \param[in] value ��������
        \return true if successful.
    */
    static bool SetAttribute(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        const wchar_t* value);

    //! ����һ�����Խڵ���������
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
        \param[in] value ���Ե���������
        \return true if successful.
    */
    static bool SetAttributeInt(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        int value);

    //! ����һ�����Խڵ㲼��ֵ����ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
        \param[in] value ���ԵĲ������ݣ��Զ�ת���ɡ�true����false��
        \return true if successful.
    */
    static bool SetAttributeBool(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        int value);

    //! ����һ�����Խڵ㸡��������
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ����ƣ�û�����Զ��������Խڵ�
        \param[in] value ���Եĸ���������
        \param[in] unitName ����������β�����ӵĵ�λ���ƣ�Ϊ�������
        \param[in] decimal ����С�����ڼ�λ��������������������
        \return true if successful.
    */
    static bool SetAttributeFloat(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        double value,
        const wchar_t* unitName = L"",
        int decimal = 4);

    //! �õ�һ���ڵ������ֵ��ʶ��CDATA
    /*! �ӽڵ�����ݼȿ����Ǽ򵥵��������ݣ�Ҳ������CDATA�ڵ�
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ��ֵ
        \return ���ӽڵ������
    */
    static std::wstring GetField(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* defValue = L"");

    //! ����һ���ڵ������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�����
        \return true if successful.
    */
    static bool SetField(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* value);

    //! �õ�һ���ڵ����������ֵ��ʶ��ʮ��������
    /*!
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ������ֵ
        \return ���ӽڵ���������ֵ
    */
    static int GetFieldInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int defValue = 0);

    //! �õ�һ���ڵ�Ĳ���ֵ����ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ�ϲ���ֵ
        \return ���ӽڵ����ݲ���ֵ
    */
    static bool GetFieldBool(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int defValue = 0);

    //! �õ�һ���ڵ�ĸ���������ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ�ϸ�����ֵ
        \param[out] unitName ������������ַ�������ӽڵ�����β���ĵĵ�λ����
        \return ���ӽڵ����ݸ�����ֵ
    */
    static double GetFieldFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        double defValue = 0,
        std::wstring* unitName = NULL);

    //! ����һ���ڵ����������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ����������
        \return true if successful.
    */
    static bool SetFieldInt(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value);

    //! ����һ���ڵ�Ĳ���ֵ����ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�Ĳ������ݣ��Զ�ת���ɡ�true����false��
        \return true if successful.
    */
    static bool SetFieldBool(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value);

    //! ����һ���ڵ�ĸ���������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�ĸ���������
        \param[in] unitName ���ӽڵ�����β�����ӵĵ�λ���ƣ�Ϊ�������
        \param[in] decimal ����С�����ڼ�λ��������������������
        \return true if successful.
    */
    static bool SetFieldFloat(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        double value,
        const wchar_t* unitName = L"",
        int decimal = 4);

    //! ����һ���ڵ��ʮ����������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ����������
        \param[in] digits ��Ϊ1��6ʱ�������ַ���������ָ�������֣���������ǰ���㣬����"0x00012A"
        \return true if successful.
    */
    static bool SetFieldHex(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value,
        int digits = 0);

    //! �õ�һ���ڵ��CDATA����ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ��CDATA���ݵ�Ĭ��ֵ
        \return ���ӽڵ��CDATA����
    */
    static std::wstring GetFieldCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* defValue = L"");

    //! ����һ���ڵ��CDATA����ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] fieldName ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ��CDATA����
        \return true if successful.
    */
    static bool SetFieldCDATA(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* value);

//--------------------------------------
// ��������
//--------------------------------------

    //! �����ϴε��õĴ�����������
    static std::wstring GetLastErrorResult();

    //! �ڸ��ڵ�ǰ����ע�ͽڵ�
    /*!
        \param[in] doc xml document object.
        \param[in] comment content of the comment node.
        \return true if successful.
    */
    static bool CreateDocComment(
        const XMLDOMDocumentPtr& doc,
        const wchar_t* comment);

    //! ��ָ���ڵ�ǰ����ע�ͽڵ�
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] comment content of the comment node.
        \return true if successful.
    */
    static bool CreateNodeComment(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* comment);

    //! Returns the parent element node.
    static bool GetParentNode(
        XMLDOMElementPtr& parent,
        XMLDOMElementPtr& node);
};

#endif // __XMLUTIL_TINYXML_INCLUDED_
