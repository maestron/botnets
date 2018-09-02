{
  KOL MCK (C) 2000 by Vladimir Kladov

  MCKfakeClasses.inc

  This file redefines mirror class types to PControl / PObj
  to use it by Delphi compiler - while compiling mirror KOL
  project. At design time these definitions are not visible
  for Delphi IDE because of conditional compiling directives.
}

{$I KOLDEF.INC}
{$IFNDEF FPC}
{$IFDEF _D7orHigher}
  {$WARN UNSAFE_TYPE OFF} // Too many such warnings in Delphi7
  {$WARN UNSAFE_CODE OFF}
  {$WARN UNSAFE_CAST OFF}
{$ENDIF}
{$ENDIF}

  TKOLProject = Pointer;
  TKOLApplet = Pointer;
  TKOLForm = Pointer;
  TKOLDataModule = Pointer;
  TKOLFrame = Pointer;
  TKOLMDIClient = PControl;
  TKOLMDIChild = Pointer;
  TKOLService = Pointer;

  TKOLButton = PControl;
  TKOLLabel = PControl;
  TKOLLabelEffect = PControl;
  TKOLPanel = PControl;
  TKOLSplitter = PControl;
  TKOLGradientPanel = PControl;
  TKOLBitBtn = PControl;
  TKOLGroupBox = PControl;
  TKOLCheckBox = PControl;
  TKOLRadioBox = PControl;
  TKOLEditBox = PControl;
  TKOLMemo = PControl;
  TKOLListBox = PControl;
  TKOLComboBox = PControl;
  TKOLPaintBox = PControl;
  TKOLImageShow = PControl;

  TKOLRichEdit = PControl;
  TKOLProgressBar = PControl;
  TKOLListView = PControl;
  TKOLTreeView = PControl;
  TKOLToolbar = PControl;
  TKOLTabControl = PControl;
  TTabPage = PControl;
  TKOLScrollBox = PControl;
  TKOLDateTimePicker = PControl;

  TKOLTimer = PTimer;
  TKOLThread = PThread;
  TKOLImageList = PImageList;
  TKOLMainMenu = PMenu;
  TKOLPopupMenu = PMenu;
  TKOLOpenSaveDialog = POpenSaveDialog;
  //TKOLOpenDirDialog = POpenDirDialog;
  TKOLTrayIcon = PTrayIcon;
  TKOLColorDialog = PColorDialog;
  //TKOLActionList = PActionList;
  //TKOLAction = PAction;
  TKOLScrollBar = PControl;

{$IFNDEF FPC}
{$IFDEF _D7orHigher}
  //{$WARN UNSAFE_TYPE ON} // Too many such warnings in Delphi7
  //{$WARN UNSAFE_CODE ON}
  //{$WARN UNSAFE_CAST ON}
{$ENDIF}
{$ENDIF}

