#pragma once

#define AfxDeferRegisterClass(fClass) AfxEndDeferRegisterClass(fClass)

CLASS_DECL_VMSWIN BOOL AfxEndDeferRegisterClass(LONG fToRegister, const char ** ppszClass);


// Temporary ::collection::map management (locks temp ::collection::map on current thread)
//CLASS_DECL_VMSWIN void AfxLockTempMaps(::radix::application * papp);
//CLASS_DECL_VMSWIN BOOL AfxUnlockTempMaps(::radix::application * papp, BOOL bDeleteTemps = TRUE);



// from wincore.cpp
extern CLASS_DECL_VMSWIN const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_VMSWIN const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_VMSWIN const char _afxWndMDIFrame[];
extern CLASS_DECL_VMSWIN const char _afxWndFrameOrView[];
extern CLASS_DECL_VMSWIN const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_VMSWIN void AfxCancelModes(HWND hWndRcvr);
CLASS_DECL_VMSWIN BOOL AfxHelpEnabled();  // determine if ID_HELP handler exists
CLASS_DECL_VMSWIN BOOL AfxCustomLogFont(UINT nIDS, LOGFONT* pLogFont);
CLASS_DECL_VMSWIN BOOL AfxGetPropSheetFont(string & strFace, WORD& wSize, BOOL bWizard);

CLASS_DECL_VMSWIN BOOL _AfxIsComboBoxControl(HWND hWnd, UINT nStyle);
CLASS_DECL_VMSWIN BOOL _AfxCheckCenterDialog(const char * lpszResource);
CLASS_DECL_VMSWIN BOOL _AfxCompareClassName(HWND hWnd, const char * lpszClassName);
CLASS_DECL_VMSWIN HWND _AfxChildWindowFromPoint(HWND, POINT);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();
