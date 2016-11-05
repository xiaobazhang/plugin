// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include "Cx_ClipboardUtil.h"
#ifdef _WIN32
#include <UtilFunc/ConvStr.h>
#include <UtilFunc/SysErrStr.h>

bool Cx_ClipboardUtil::CopyText(HWND wndOwner, const std::wstring& text)
{
    bool bRet = false;
    DWORD err = 0;

    if (!text.empty() && ::OpenClipboard(wndOwner))
    {
        HANDLE hMem = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(wchar_t) * (text.size() + 1));
        if (hMem != NULL)
        {
            wchar_t* str = (wchar_t*)::GlobalLock(hMem);
            if (NULL == str)
            {
                ::GlobalFree(hMem);
            }
            else
            {
                wcscpy_s(str, text.size() + 1, text.c_str());
                ::GlobalUnlock(hMem);

                ::EmptyClipboard();
                if (::SetClipboardData(CF_UNICODETEXT, hMem))
                {
                    bRet = true;
                }
                else
                {
                    err = GetLastError();
                    X3LOG_WARNING2(L"@TextUtility:IDS_SETCLIP_FAIL", x3::GetSystemErrorString(err));
                }
            }
        }
        else
        {
            err = GetLastError();
            X3LOG_WARNING2(L"@TextUtility:IDS_ALLOCMEM_FAIL", x3::GetSystemErrorString(err));
        }

        ::CloseClipboard();
    }
    else
    {
        err = GetLastError();
        X3LOG_WARNING2(L"@TextUtility:IDS_OPENCLIP_FAIL", x3::GetSystemErrorString(err));
    }

    return bRet;
}

bool Cx_ClipboardUtil::PasteText(HWND wndOwner, std::wstring& text, bool clear)
{
    text.resize(0);

    if (!::IsClipboardFormatAvailable(CF_UNICODETEXT)
        && !::IsClipboardFormatAvailable(CF_TEXT))
    {
        X3LOG_INFO(L"@TextUtility:IDS_CLIP_NOTEXT");
        return false;
    }

    if (!::OpenClipboard(wndOwner))
    {
        DWORD err = GetLastError();
        X3LOG_WARNING2(L"@TextUtility:IDS_OPENCLIP_FAIL", x3::GetSystemErrorString(err));
    }
    else
    {
        if (::IsClipboardFormatAvailable(CF_UNICODETEXT))
        {
            HANDLE hMem = ::GetClipboardData(CF_UNICODETEXT);
            if (hMem != NULL)
            {
                const wchar_t* lpStr = (const wchar_t*)::GlobalLock(hMem);
                if (lpStr != NULL)
                {
                    text = lpStr;
                    ::GlobalUnlock(hMem);
                }
            }
        }
        else if (::IsClipboardFormatAvailable(CF_TEXT))
        {
            HANDLE hMem = ::GetClipboardData(CF_UNICODETEXT);
            if (hMem != NULL)
            {
                const char* lpStr = (const char*)::GlobalLock(hMem);
                if (lpStr != NULL)
                {
                    text = x3::a2w(lpStr);
                    ::GlobalUnlock(hMem);
                }
            }
        }

        if (clear)
        {
            ::EmptyClipboard();
        }

        ::CloseClipboard();
    }

    return !text.empty();
}

bool Cx_ClipboardUtil::CanPasteText()
{
    return ::IsClipboardFormatAvailable(CF_UNICODETEXT)
        || ::IsClipboardFormatAvailable(CF_TEXT);
}

#endif // _WIN32
