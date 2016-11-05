/*! \file Ix_ClipboardUtil.h
 *  \brief Define clipboard operation interface: Ix_ClipboardUtil
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_ICLIPBOARDUTIL_H_
#define X3_UTIL_ICLIPBOARDUTIL_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_ClipboardUtil, "fc957aed-3c48-461e-b9b8-6ff255f2e71d");

//! Clipboard operation interface.
/*!
    \interface Ix_ClipboardUtil
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_ClipboardUtil
*/
class Ix_ClipboardUtil : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_ClipboardUtil)

    //! �������ı����Ƶ�������
    /*!
        \param wndOwner ��ǰ���ھ��������������������
        \param text Ҫ���Ƶ��ı����ǿ�
        \return �Ƿ������ı�
    */
    virtual bool CopyText(HWND wndOwner, const std::wstring& text) = 0;

    //! �Ӽ������ȡ�ı�����
    /*!
        \param[in] wndOwner ��ǰ���ھ��
        \param[out] text Ҫ�����ı�
        \param[in] clear ��ȡ�ı��Ƿ��������������
        \return �Ƿ������ı�
    */
    virtual bool PasteText(HWND wndOwner, std::wstring& text, bool clear = false) = 0;

    //! �����Ƿ����ճ���ı�
    virtual bool CanPasteText() = 0;
};

#endif // X3_UTIL_ICLIPBOARDUTIL_H_
