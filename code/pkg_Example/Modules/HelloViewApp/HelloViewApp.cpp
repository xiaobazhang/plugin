#include <UtilFunc/PluginInc.h>
#include <PluginManager/PluginManager.h>

// Include XComCreator.h in one and only one cpp file.
#include <PluginManager/XComCreator.h>

#include "Resource.h"
#include "MainFrm.h"

class CHelloApp : public CWinApp
{
public:
    CHelloApp()
    {
    }

protected:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

CHelloApp theApp;
CPluginManager s_loader;

BOOL CHelloApp::InitInstance()
{
	INITCOMMONCONTROLSEX initctls;
	initctls.dwSize = sizeof(initctls);
	initctls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initctls);

    VERIFY(AfxOleInit());
	CWinApp::InitInstance();

    VERIFY(s_loader.LoadPluginManager(L"../plugins"));
    s_loader.GetPluginLoader()->LoadPluginFiles(L"../plugins",
        L"HelloView.plugin" PLNEXT
        L",ChangeManager.plugin" PLNEXT);
    s_loader.GetPluginLoader()->InitializePlugins();

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	if (!pFrame || !pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    pFrame->SetIcon(LoadIcon(IDR_MAINFRAME), FALSE);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CHelloApp::ExitInstance()
{
    s_loader.Unload();

    return CWinApp::ExitInstance();
}


#if defined(_UNICODE) && _MSC_VER >= 1400
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
