Name "BunBunWar"

OutFile "Setup.exe"

InstallDir $PROGRAMFILES\BunBunWar

InstallDirRegKey HKLM "Software\BunBunWar" "Install_Dir"

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "BunBunWar (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r /x setup.exe /x .svn /x *.htm /x *.res /x *.idb /x bin-debug /x *.pch /x *.pdb /x *.exp /x *.lib /x *.ilk /x *.log /x *.obj bin media maps gametypes
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\BunBunWar "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BunBunWar" "DisplayName" "BunBunWar"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BunBunWar" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BunBunWar" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BunBunWar" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

Section "Microsoft VC++ Runtime Libraries"

  SetOutPath $SYSDIR
  
  File redist\msvcp71.dll redist\msvcr71.dll

SectionEnd

Section "Start Menu Shortcuts"

  SetOutPath $INSTDIR\bin

  CreateDirectory "$SMPROGRAMS\BunBunWar"
  CreateShortCut "$SMPROGRAMS\BunBunWar\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\BunBunWar\BunBunWar.lnk" "$INSTDIR\bin\BunBunWar.exe" "" "$INSTDIR\bin\BunBunWar.exe" 0
  
SectionEnd

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BunBunWar"
  DeleteRegKey HKLM SOFTWARE\BunBunWar

  ; Remove files and uninstaller
  RMDir /r $INSTDIR\bin
  RMDir /r $INSTDIR\media
  RMDir /r $INSTDIR\maps
  RMDir /r $INSTDIR\gametypes
  Delete $INSTDIR\*.*
  
  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\BunBunWar\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\BunBunWar"
  RMDir "$INSTDIR"

SectionEnd