/*! \file FrameAppImpl.h
 *  \brief Implement the base application class: CFrameApp
 *  \note Include this file in one and only one CPP file of your MFC application project.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.10.27
 */
#include <UtilFunc/PluginInc.h>
#include "FrameApp.h"
#include "Ix_FrameWndFactory.h"
#include <PluginManager/PluginManager.h>

BEGIN_MESSAGE_MAP(CFrameApp, CWinApp)
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CFrameApp::CFrameApp()
{
    m_loader = new CPluginManager;
}

CFrameApp::~CFrameApp()
{
    delete m_loader;
}

BOOL CFrameApp::InitInstance()
{
    // Enable visual styles on Windows XP or later
    INITCOMMONCONTROLSEX initCtrls;
    initCtrls.dwSize = sizeof(initCtrls);
    initCtrls.dwICC = ICC_WIN95_CLASSES | ICC_DATE_CLASSES;
    InitCommonControlsEx(&initCtrls);

    CWinApp::InitInstance();
    VERIFY(AfxOleInit());

    return LoadPlugins()
        && CheckAppInstance()
        && CreateFrameWnd();
}

BOOL CFrameApp::LoadPlugins()
{
    return m_loader->LoadCorePlugins(L"plugins")
        && m_loader->GetPluginLoader()->LoadPlugins(L"plugins") > 0
        && m_loader->GetPluginLoader()->InitializePlugins() > 0;
}

int CFrameApp::ExitInstance()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(m_factory);
    SafeCall(pIFFactory, OnQuit());
    pIFFactory.Release();
    m_factory.Release();

    m_loader->Unload();

    return CWinApp::ExitInstance();
}

BOOL CFrameApp::CheckAppInstance()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFrameWndFactory(x3::CLSID_FrameWndFactory);
    ASSERT(pIFFrameWndFactory.IsNotNull());

    m_factory = pIFFrameWndFactory;

    return 0 == *GetSingletonAppUID()
        || pIFFrameWndFactory && pIFFrameWndFactory->CheckAppInstance(GetSingletonAppUID());
}

BOOL CFrameApp::CreateFrameWnd()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(m_factory);
    return pIFFactory->CreateFrameWnd(GetFactoryFile());
}

BOOL CFrameApp::OnIdle(LONG lCount)
{
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(m_factory);
    BOOL more = CWinApp::OnIdle(lCount);

    return pIFFactory->OnIdle(lCount) || more;
}

// <exepath>\translations\<exename>Chs.dll
HINSTANCE CFrameApp::LoadAppLangResourceDLL()
{
    HINSTANCE hResDll = NULL;

#if _MSC_VER > 1400
    TCHAR szPath[MAX_PATH], szTitle[60];

    GetModuleFileName(m_hInstance, szPath, MAX_PATH);
    StrCpyN(szTitle, PathFindFileName(szPath), _countof(szTitle));
    PathRemoveExtension(szTitle);
    PathRemoveFileSpec(szPath);
    PathAppendW(szPath, L"translations");
    PathAppendW(szPath, szTitle);

    hResDll = AfxLoadLangResourceDLL(_T("%s%s.dll"), szPath);
    TRACE2("Load resource file: %s (%s)\n", szPath, hResDll ? L"ok" : L"fail");

#elif _MSC_VER > 1200
    hResDll = AfxLoadLangResourceDLL(_T("%s%s.dll"));
#endif

    return hResDll;
}


#if _MSC_VER > 1200     // not VC6
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
