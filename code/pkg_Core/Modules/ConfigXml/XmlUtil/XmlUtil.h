// x3c - C++ PluginFramework
//! \file XmlUtil.h
//! \brief Define MSXML DOM wrapper class: CXmlUtil.

#ifndef __XMLUTIL_NONMFC_INCLUDED_
#define __XMLUTIL_NONMFC_INCLUDED_
#pragma once

#include "XMLhelpers.h"

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

//! MSXML DOM wrapper class, not need MFC.
class CXmlUtil
{
public:

//--------------------------------------
// �ļ�����
//--------------------------------------

    //! ����һ��XML�ĵ�����
    /*! �´�����XML�ĵ�����δ���浽�ļ���
        \param[out] doc new xml document object.
        \param[in] pszRootName ���ڵ����ƣ������Զ��������ڵ�
        \param[in] pszEncoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
        \param[in] pszNameSpace XML�����ռ�
        \param[in] comment ���ڵ��˵������
        \return �Ƿ񴴽��ɹ�
    */
    static bool NewXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* pszRootName,
        const wchar_t* pszEncoding = L"UTF-8",
        const wchar_t* pszNameSpace = L"",
        const wchar_t* comment = L"");

    //! ����һ��XML�ĵ����󣬲��õ����ڵ�
    /*! �´�����XML�ĵ�����δ���浽�ļ���
        \param[out] doc new xml document object.
        \param[in] root ������ڵ����
        \param[in] pszRootName ���ڵ����ƣ������Զ��������ڵ�
        \param[in] pszEncoding XML���Ա��룬Ĭ��ΪUnicode��ʽ�ġ�UTF-8��
        \param[in] pszNameSpace XML�����ռ�
        \return �Ƿ񴴽��ɹ�
    */
    static bool NewXMLFile2(
        XMLDOMDocumentPtr& doc,
        XMLDOMElementPtr& root,
        const wchar_t* pszRootName,
        const wchar_t* pszEncoding = L"UTF-8",
        const wchar_t* pszNameSpace = L"");

    //! װ��һ��XML�ļ�
    /*!
        \param[out] doc new xml document object.
        \param[in] filename absolute file name, or Web Service URL.
        \param[in] pCryptHandler �ӽ��ܵĲ�������
        \return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ��ܶ�ȡ�ļ����ܴ���XML�ĵ�����
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* pCryptHandler = NULL);

    //! װ��һ��XML�ļ����������ڵ�
    /*!
        \param[out] doc new xml document object.
        \param[in] filename absolute file name, or Web Service URL.
        \param[in] root ������ڵ����
        \param[in] pszRootName ���ڵ�����
        \param[in] pCryptHandler �ӽ��ܵĲ�������
        \return �Ƿ�װ�سɹ���ʧ��ԭ���ǲ�����ָ���ĸ��ڵ�ȴ���
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        XMLDOMElementPtr& root,
        const wchar_t* pszRootName,
        IXmlFileCrypt* pCryptHandler = NULL);

    //! ���浽һ��XML�ļ�
    /*!
        \param[in] doc Ҫ�����XML�ĵ�����
        \param[in] filename �ļ�ȫ��
        \param[in] pCryptHandler �ӽ��ܵĲ�������
        \return �Ƿ񱣴�ɹ�
    */
    static bool SaveXMLFile(
        const XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* pCryptHandler = NULL);

    //! ���ַ�����װ��XML�ļ�
    /*!
        \param[out] doc ����´�����XML�ĵ�����
        \param[in] pszXML XML��ʽ���ַ���
        \return �Ƿ�װ�سɹ�
    */
    static bool LoadXMLFromString(
        XMLDOMDocumentPtr& doc,
        LPCSTR pszXML);

    //! ���ַ�����װ��XML�ļ����Զ�����Unicodeǰ׺��־
    /*!
        \param[out] doc ����´�����XML�ĵ�����
        \param[in] pszXML XML��ʽ���ַ���
        \return �Ƿ�װ�سɹ�
    */
    static bool LoadXMLFromString(
        XMLDOMDocumentPtr& doc,
        const wchar_t* pszXML);

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
        \param[in] pszRootName ���ڵ�����
        \return �Ƿ���ڸ������Ƶĸ��ڵ�
        \see GetRootName
    */
    static bool GetRoot(
        XMLDOMElementPtr& root,
        const XMLDOMDocumentPtr& doc,
        const wchar_t* pszRootName);

    //! �õ��ӽڵ����
    /*!
        \param[in] ele xml element object.
        \param[in] pszChildName ��Ԫ������
        \return ����Ԫ��ele�µ�����ΪpszChildName���ӽڵ����
    */
    static long GetChildCount(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszChildName);

    //! �õ�һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] parent xml element object.
        \param[in] pszChildName ��Ԫ������
        \param[in] nIndex �ڼ�����Ԫ�أ���0��ʼ
        \return �Ƿ��ж�Ӧ����Ԫ�ض���
    */
    static bool GetChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* pszChildName,
        long nIndex = 0);

    //! �õ��򴴽�һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] doc xml document object.
        \param[in] parent xml element object.
        \param[in] pszChildName ��Ԫ������
        \return true if successful.
    */
    static bool GetChildOrAdd(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& parent,
        const wchar_t* pszChildName);

    //! ���һ���ӽڵ�
    /*!
        \param[out] outEle �����Ԫ�ض���
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] pszChildName ��Ԫ������
        \return true if successful.
    */
    static bool AddChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* pszChildName);

    //! ɾ��һ���ӽڵ�
    /*!
        \param[in] ele xml element object.
        \param[in] pszChildName ��Ԫ������
        \param[in] nIndex Ҫɾ���ڼ�����Ԫ�أ���0��ʼ
        \return �Ƿ��ж�Ӧ����Ԫ�ض���ɾ��
    */
    static bool DelChild(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszChildName,
        long nIndex);

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
    /*! ɾ������Ԫ���µ���������ΪpszChildName���ӽڵ�
        \param[in] ele xml element object.
        \param[in] pszChildName ��Ԫ������
        \param[in] pszAttrName ��Ԫ�صı�ʶ����������ѡֵ
        \param[in] pszAttrValue ��ʶ��������Ӧ��ֵ��pszAttrName��Ϊ��ʱ��Ч
        \return ɾ������Ԫ�ظ���
    */
    static long DelChildren(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszChildName,
        const wchar_t* pszAttrName = L"", const wchar_t* pszAttrValue = L"");

    //! ���ҽڵ������е��ӽڵ����
    /*!
        \param[out] outEle ������ҵ�����Ԫ�ض���
        \param[in] parent xml element object.���ڸýڵ��²���
        \param[in] pszElement ��Ԫ������
        \param[in] pszField ��Ԫ�ص���һ��Ԫ������
        \param[in] value ��Ԫ�ص���һ��Ԫ�ص�����
        \return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
    */
    static long FindElement(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* pszElement,
        const wchar_t* pszField,
        const wchar_t* value);

    //! ���ҽڵ������е��ӽڵ����
    /*! ����Ԫ��parent����Ԫ�ؽڵ㣬�����Ǹ���Ԫ����������ΪpszAttr1��
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
        \param[in] pszElement ��Ԫ������
        \param[in] pszAttr1 ��Ԫ�ص���������
        \param[in] value1 ��Ԫ�ص�����ֵ
        \param[in] pszAttr2 ��Ԫ�ص���һ���������ƣ�Ϊ�������
        \param[in] value2 ��Ԫ�ص���һ�����Զ�Ӧ��ֵ��pszAttr2��Ϊ��ʱ��Ч
        \return �ҵ����ǵڼ�����Ԫ�أ�-1��ʾ�Ҳ���
    */
    static long FindElementByAttr(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* pszElement,
        const wchar_t* pszAttr1,
        const wchar_t* value1,
        const wchar_t* pszAttr2,
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
        \param[in] node xml element object.
        \param[in] defaultText �ڵ����ݵ�Ĭ��ֵ
        \return �����ڵ������
    */
    static std::wstring GetText(
        const XMLDOMNodePtr& node,
        const wchar_t* defaultText = L"");

    //! �õ�һ���ڵ��CDATAֵ
    /*!
        \param[in] ele xml element object.
        \param[in] defaultText �ڵ��CDATA���ݵ�Ĭ��ֵ
        \return �ýڵ��CDATA����
    */
    static std::wstring GetTextCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* defaultText = L"");

    //! ���ýڵ�����
    /*!
        \param[in] node xml element object.
        \param[in] text �����ڵ������
        \return true if successful.
    */
    static bool SetText(
        const XMLDOMNodePtr& node,
        const wchar_t* text);

    //! ���ýڵ�����
    /*!
        ���������ڲ����Ƿ�����_UNICODE��������꣬����ֱ�����ÿ��ֽ��ַ������ݣ�
        ������ANSI����ģʽ�½�LPCWSTRת��ΪBSTRʱ�Զ����б���ת�����������롣

        ʹ������������ӷ�UNICODE�ı��ļ��ж�ȡ���ֽ��ַ�������MultiByteToWideChar
        ����ת��Ϊ���ֽ��ַ��������ñ��������ýڵ����ݣ��������ܽ��ض����Ա����
        ����ת��ΪUNICODE��XML���ݡ�

        \param[in] node xml element object.
        \param[in] text �����ڵ��UNICODE���ݣ�ĩβ���������
        \return true if successful.
    */
    static bool SetTextW(
        const XMLDOMNodePtr& node,
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
        \param[in] defaultText �������ݵ�Ĭ��ֵ
        \return ��Ԫ�ص���������
    */
    static std::wstring GetAttribute(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        const wchar_t* defaultText = L"");

    //! �õ�һ�����Խڵ���������
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] defValue �������ݵ�Ĭ������ֵ
        \return ��Ԫ�ص�������������ֵ
    */
    static UINT GetAttributeInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        INT defValue = 0);

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
        BOOL defValue = FALSE);

    //! �õ�һ�����Խڵ㸡��������
    /*!
        \param[in] ele xml element object.
        \param[in] name ��Ԫ�ص����Խڵ�����
        \param[in] value �������ݵ�Ĭ�ϸ�����ֵ
        \param[out] unitName ������������ַ��������������β���ĵĵ�λ����
        \return ��Ԫ�ص��������ݸ�����ֵ
    */
    static double GetAttributeFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* name,
        double value = 0,
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
        INT value);

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
        BOOL value);

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
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defaultText �ӽڵ����ݵ�Ĭ��ֵ
        \return ���ӽڵ������
    */
    static std::wstring GetField(
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        const wchar_t* defaultText = L"");

    //! ����һ���ڵ������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�����
        \return true if successful.
    */
    static bool SetField(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        const wchar_t* value);

    //! �õ�һ���ڵ����������ֵ��ʶ��ʮ��������
    /*!
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ������ֵ
        \return ���ӽڵ���������ֵ
    */
    static UINT GetFieldInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        INT defValue = 0);

    //! �õ�һ���ڵ�Ĳ���ֵ����ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defValue �ӽڵ����ݵ�Ĭ�ϲ���ֵ
        \return ���ӽڵ����ݲ���ֵ
    */
    static bool GetFieldBool(
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        BOOL defValue = FALSE);

    //! �õ�һ���ڵ�ĸ���������ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] value �ӽڵ����ݵ�Ĭ�ϸ�����ֵ
        \param[out] unitName ������������ַ�������ӽڵ�����β���ĵĵ�λ����
        \return ���ӽڵ����ݸ�����ֵ
    */
    static double GetFieldFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        double value = 0,
        std::wstring* unitName = NULL);

    //! ����һ���ڵ����������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ����������
        \return true if successful.
    */
    static bool SetFieldInt(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        INT value);

    //! ����һ���ڵ�Ĳ���ֵ����ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�Ĳ������ݣ��Զ�ת���ɡ�true����false��
        \return true if successful.
    */
    static bool SetFieldBool(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        BOOL value);

    //! ����һ���ڵ�ĸ���������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ�ĸ���������
        \param[in] unitName ���ӽڵ�����β�����ӵĵ�λ���ƣ�Ϊ�������
        \param[in] decimal ����С�����ڼ�λ��������������������
        \return true if successful.
    */
    static bool SetFieldFloat(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        double value,
        const wchar_t* unitName = L"",
        int decimal = 4);

    //! ����һ���ڵ��ʮ����������ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ����������
        \param[in] digits ��Ϊ1��6ʱ�������ַ���������ָ�������֣���������ǰ���㣬����"0x00012A"
        \return true if successful.
    */
    static bool SetFieldHex(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        INT value,
        INT digits = 0);

    //! �õ�һ���ڵ��CDATA����ֵ
    /*!
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ�����
        \param[in] defaultText �ӽڵ��CDATA���ݵ�Ĭ��ֵ
        \return ���ӽڵ��CDATA����
    */
    static std::wstring GetFieldCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
        const wchar_t* defaultText = L"");

    //! ����һ���ڵ��CDATA����ֵ
    /*!
        \param[in] doc xml document object.
        \param[in] ele xml element object.
        \param[in] filename ��Ԫ�ص���Ԫ�ؽڵ����ƣ�û�����Զ������ڵ�
        \param[in] value �ӽڵ��CDATA����
        \return true if successful.
    */
    static bool SetFieldCDATA(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* filename,
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

#endif // __XMLUTIL_NONMFC_INCLUDED_