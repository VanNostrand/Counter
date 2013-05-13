!include "MUI2.nsh"
!include "FileFunc.nsh"

!define /date TIMESTAMP "%Y%m%d" 

Name "MtG Counter for Manabase.de"
OutFile "mtg_counter_win32_${TIMESTAMP}.exe"
SetCompressor /SOLID lzma
InstallDir "$PROGRAMFILES\Counter"

!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_WELCOMEPAGE_TEXT "This wizard will guide you through the installation.$\r$\n$\r$\nClick Next to continue."

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\COPYING"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "Application" SecApplication
	SetOutPath "$INSTDIR"
	File ..\release\Counter.exe
	File ..\COPYING
	File C:\MinGW\bin\libstdc++-6.dll
	File C:\MinGW\bin\libgcc_s_dw2-1.dll
	File C:\MinGW\bin\mingwm10.dll
	File C:\Qt\4.8.4\bin\QtCore4.dll
	File C:\Qt\4.8.4\bin\QtGui4.dll
	
	WriteUninstaller "$INSTDIR\uninstall.exe"
		${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
        IntFmt $0 "0x%08X" $0
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "DisplayName" "Counter"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "InstallLocation" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "DisplayIcon" "$INSTDIR\Counter.exe"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter" "EstimatedSize" "$0"
SectionEnd

Section "Start menu item" SecStartMenu
	createDirectory "$SMPROGRAMS\Counter"
	createShortCut "$SMPROGRAMS\Counter\Counter.lnk" "$INSTDIR\Counter.exe"
	createShortCut "$SMPROGRAMS\Counter\uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
	Delete "$INSTDIR\Counter.exe"
	Delete "$INSTDIR\COPYING"
	Delete "$INSTDIR\uninstall.exe"
	Delete "$INSTDIR\libstdc++-6.dll"
	Delete "$INSTDIR\libgcc_s_dw2-1.dll"
    Delete "$INSTDIR\mingwm10.dll"
    Delete "$INSTDIR\QtCore4.dll"
    Delete "$INSTDIR\QtGui4.dll"
    RMDir "$INSTDIR"

	RMDir /r "$SMPROGRAMS\Counter"
	
	DeleteRegKey HKCU "Software\Counter"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Counter"
SectionEnd

LangString DESC_SecApplication ${LANG_ENGLISH} "Counter program files"
LangString DESC_SecUpdateConfig ${LANG_ENGLISH} "Update the paths in the application settings according to the installation paths."
LangString DESC_SecStartMenu ${LANG_ENGLISH} "Create start menu items for Counter."
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
        !insertmacro MUI_DESCRIPTION_TEXT ${SecApplication} $(DESC_SecApplication)
        !insertmacro MUI_DESCRIPTION_TEXT ${SecStartMenu} $(DESC_SecStartMenu)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

