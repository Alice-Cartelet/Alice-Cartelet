; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "记账小程序"
!define PRODUCT_VERSION "2.0"
!define PRODUCT_PUBLISHER "Alice-Cartelet"
!define PRODUCT_WEB_SITE "http://www.alicecartelet.cn/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\记账.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "ico.ico"
!define MUI_UNICON "ico2.ico"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "协议.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_RUN "$INSTDIR\记账.exe"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

ReserveFile "${NSISDIR}\Plugins\advsplash.dll"
ReserveFile "tu.bmp"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\remembermoney"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText "记账小程序2.0安装"

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "记账.exe"
  CreateDirectory "$SMPROGRAMS\记账小程序"
  CreateShortCut "$SMPROGRAMS\记账小程序\记账小程序.lnk" "$INSTDIR\记账.exe"
  CreateShortCut "$DESKTOP\记账小程序.lnk" "$INSTDIR\记账.exe"
  File "see.dll"
  File "first.dll"
  File "crative.dll"
  File "button3.dll"
  File "button2.dll"
  File "button1.dll"
  File "background.dll"
  File "back.dll"
  File "main.exe"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\记账小程序\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\记账小程序\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\记账.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\记账.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function .onInit
  InitPluginsDir
  File "/oname=$PLUGINSDIR\Splash_1.bmp" "tu.bmp"
  ; 使用闪屏插件显示闪屏
  advsplash::show 3000 500 500 -1 "$PLUGINSDIR\Splash_1"
  Pop $0 ; $0 返回 '1' 表示用户提前关闭闪屏, 返回 '0' 表示闪屏正常结束, 返回 '-1' 表示闪屏显示出错
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\background.dll"
  Delete "$INSTDIR\back.dll"
  Delete "$INSTDIR\button1.dll"
  Delete "$INSTDIR\button2.dll"
  Delete "$INSTDIR\button3.dll"
  Delete "$INSTDIR\crative.dll"
  Delete "$INSTDIR\first.dll"
  Delete "$INSTDIR\see.dll"
  Delete "$INSTDIR\main.exe"
  Delete "$INSTDIR\记账.exe"

  Delete "$SMPROGRAMS\记账小程序\Uninstall.lnk"
  Delete "$SMPROGRAMS\记账小程序\Website.lnk"
  Delete "$DESKTOP\记账小程序.lnk"
  Delete "$SMPROGRAMS\记账小程序\记账小程序.lnk"

  RMDir "$SMPROGRAMS\记账小程序"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
