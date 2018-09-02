{*******************************************************************************
  delpjicommctrl.inc
  -- included in KOL.pas --
*******************************************************************************}

////////////////////////////////////////////////////////////////////////////
// this part of unit contains definitions moved here from CommCtrl.pas
// (using of CommCtrl.pas in Delphi3 leads to increase size of executable
// onto 30K)

type
  PTCItemA = ^TTCItemA;
  PTCItemW = ^TTCItemW;
  PTCItem = {$IFDEF UNICODE_CTRLS} PTCItemW {$ELSE} PTCItemA {$ENDIF};
  tagTCITEMA = packed record
    mask: UINT;
    dwState: UINT;
    dwStateMask: UINT;
    pszText: PAnsiChar;
    cchTextMax: Integer;
    iImage: Integer;
    lParam: LPARAM;
  end;
  tagTCITEMW = packed record
    mask: UINT;
    dwState: UINT;
    dwStateMask: UINT;
    pszText: PWideChar;
    cchTextMax: Integer;
    iImage: Integer;
    lParam: LPARAM;
  end;

  PTCKeyDown = ^TTCKeyDown;
  TTCKEYDOWN = packed record
    hdr: TNMHDR;
    wVKey: Word;
    flags: UINT;
  end;

  tagTCITEM = {$IFDEF UNICODE_CTRLS} tagTCITEMW {$ELSE} tagTCITEMA {$ENDIF};
  _TC_ITEMA = tagTCITEMA;
  _TC_ITEMW = tagTCITEMW;
  _TC_ITEM = {$IFDEF UNICODE_CTRLS} _TC_ITEMW {$ELSE} _TC_ITEMA {$ENDIF};
  TTCItemA = tagTCITEMA;
  TTCItemW = tagTCITEMW;
  TTCItem = {$IFDEF UNICODE_CTRLS} TTCItemW {$ELSE} TTCItemA {$ENDIF};
  TC_ITEMA = tagTCITEMA;
  TC_ITEMW = tagTCITEMW;
  TC_ITEM = {$IFDEF UNICODE_CTRLS} TC_ITEMW {$ELSE} TC_ITEMA {$ENDIF};


const
  CCM_FIRST               = $2000;      { Common control shared messages }
  CCM_SETBKCOLOR          = CCM_FIRST + 1; // lParam is bkColor
  CCM_SETCOLORSCHEME      = CCM_FIRST + 2; // lParam is color scheme
  CCM_GETCOLORSCHEME      = CCM_FIRST + 3; // fills in COLORSCHEME pointed to by lParam
  CCM_GETDROPTARGET       = CCM_FIRST + 4;
  CCM_SETUNICODEFORMAT    = CCM_FIRST + 5;
  CCM_GETUNICODEFORMAT    = CCM_FIRST + 6;

  TCS_SCROLLOPPOSITE    = $0001;  // assumes multiline tab
  TCS_BOTTOM            = $0002;
  TCS_RIGHT             = $0002;
  TCS_MULTISELECT       = $0004;  // allow multi-select in button mode
  TCS_FLATBUTTONS       = $0008;
  TCS_FORCEICONLEFT     = $0010;
  TCS_FORCELABELLEFT    = $0020;
  TCS_HOTTRACK          = $0040;
  TCS_VERTICAL          = $0080;
  TCS_TABS              = $0000;
  TCS_BUTTONS           = $0100;
  TCS_SINGLELINE        = $0000;
  TCS_MULTILINE         = $0200;
  TCS_RIGHTJUSTIFY      = $0000;
  TCS_FIXEDWIDTH        = $0400;
  TCS_RAGGEDRIGHT       = $0800;
  TCS_FOCUSONBUTTONDOWN = $1000;
  TCS_OWNERDRAWFIXED    = $2000;
  TCS_TOOLTIPS          = $4000;
  TCS_FOCUSNEVER        = $8000;

  TCS_EX_FLATSEPARATORS = $00000001;
  TCS_EX_REGISTERDROP   = $00000002;

  TCM_FIRST               = $1300;      { Tab control messages }
  TCM_GETIMAGELIST       = TCM_FIRST + 2;
  TCM_SETIMAGELIST       = TCM_FIRST + 3;
  TCM_GETITEMCOUNT       = TCM_FIRST + 4;
  TCM_GETITEMA           = TCM_FIRST + 5;
  TCM_SETITEMA           = TCM_FIRST + 6;
  TCM_INSERTITEMA        = TCM_FIRST + 7;
  TCM_DELETEITEM         = TCM_FIRST + 8;
  TCM_DELETEALLITEMS     = TCM_FIRST + 9;
  TCM_GETITEMRECT        = TCM_FIRST + 10;
  TCM_GETCURSEL          = TCM_FIRST + 11;
  TCM_SETCURSEL          = TCM_FIRST + 12;
  TCM_HITTEST            = TCM_FIRST + 13;
  TCM_SETITEMEXTRA       = TCM_FIRST + 14;
  TCM_ADJUSTRECT         = TCM_FIRST + 40;
  TCM_SETITEMSIZE        = TCM_FIRST + 41;
  TCM_REMOVEIMAGE        = TCM_FIRST + 42;
  TCM_SETPADDING         = TCM_FIRST + 43;
  TCM_GETROWCOUNT        = TCM_FIRST + 44;
  TCM_GETTOOLTIPS        = TCM_FIRST + 45;
  TCM_SETTOOLTIPS        = TCM_FIRST + 46;
  TCM_GETCURFOCUS        = TCM_FIRST + 47;
  TCM_SETCURFOCUS        = TCM_FIRST + 48;
  TCM_SETMINTABWIDTH     = TCM_FIRST + 49;
  TCM_DESELECTALL        = TCM_FIRST + 50;
  TCM_HIGHLIGHTITEM      = TCM_FIRST + 51;
  TCM_SETEXTENDEDSTYLE   = TCM_FIRST + 52;  // optional wParam == mask
  TCM_GETEXTENDEDSTYLE   = TCM_FIRST + 53;
  TCM_GETITEMW           = TCM_FIRST + 60;
  TCM_SETITEMW           = TCM_FIRST + 61;
  TCM_INSERTITEMW        = TCM_FIRST + 62;
  TCM_SETUNICODEFORMAT   = CCM_SETUNICODEFORMAT;
  TCM_GETUNICODEFORMAT   = CCM_GETUNICODEFORMAT;
  TCM_GETITEM             = {$IFDEF UNICODE_CTRLS} TCM_GETITEMW
                            {$ELSE} TCM_GETITEMA {$ENDIF};
  TCM_SETITEM             = {$IFDEF UNICODE_CTRLS} TCM_SETITEMW
                            {$ELSE} TCM_SETITEMA {$ENDIF};
  TCM_INSERTITEM          = {$IFDEF UNICODE_CTRLS} TCM_INSERTITEMW
                            {$ELSE} TCM_INSERTITEMA {$ENDIF};

  TCN_FIRST                = 0-550;       { tab control }
  TCN_LAST                 = 0-580;
  TCN_KEYDOWN             = TCN_FIRST - 0;
  TCN_SELCHANGE           = TCN_FIRST - 1;
  TCN_SELCHANGING         = TCN_FIRST - 2;
  TCN_GETOBJECT           = TCN_FIRST - 3;

  TCIF_TEXT       = $0001;
  TCIF_IMAGE      = $0002;
  TCIF_RTLREADING = $0004;
  TCIF_PARAM      = $0008;
  TCIF_STATE      = $0010;

  PBS_SMOOTH              = 01;
  PBS_VERTICAL            = 04;

  PBM_SETRANGE            = WM_USER+1;
  PBM_SETPOS              = WM_USER+2;
  PBM_DELTAPOS            = WM_USER+3;
  PBM_SETSTEP             = WM_USER+4;
  PBM_STEPIT              = WM_USER+5;
  PBM_SETRANGE32          = WM_USER+6;   // lParam = high, wParam = low
  PBM_GETRANGE            = WM_USER+7;   // lParam = PPBRange or Nil
					 // wParam = False: Result = high
					 // wParam = True: Result = low
  PBM_GETPOS              = WM_USER+8;
  PBM_SETBARCOLOR         = WM_USER+9;		// lParam = bar color
  PBM_SETBKCOLOR          = CCM_SETBKCOLOR;  // lParam = bkColor

  SB_SETTEXTA             = WM_USER+1;
  SB_GETTEXTA             = WM_USER+2;
  SB_GETTEXTLENGTHA       = WM_USER+3;
  SB_SETTIPTEXTA          = WM_USER+16;
  SB_GETTIPTEXTA          = WM_USER+18;

  SB_SETTEXTW             = WM_USER+11;
  SB_GETTEXTW             = WM_USER+13;
  SB_GETTEXTLENGTHW       = WM_USER+12;
  SB_SETTIPTEXTW          = WM_USER+17;
  SB_GETTIPTEXTW          = WM_USER+19;

  SB_SETTEXT             = {$IFDEF UNICODE_CTRLS} SB_SETTEXTW {$ELSE} SB_SETTEXTA {$ENDIF};
  SB_GETTEXT             = {$IFDEF UNICODE_CTRLS} SB_GETTEXTW {$ELSE} SB_GETTEXTA {$ENDIF};
  SB_GETTEXTLENGTH       = {$IFDEF UNICODE_CTRLS} SB_GETTEXTLENGTHW {$ELSE} SB_GETTEXTLENGTHA {$ENDIF};
  SB_SETTIPTEXT          = {$IFDEF UNICODE_CTRLS} SB_SETTIPTEXTW {$ELSE} SB_SETTIPTEXTA {$ENDIF};
  SB_GETTIPTEXT          = {$IFDEF UNICODE_CTRLS} SB_GETTIPTEXTW {$ELSE} SB_GETTIPTEXTA {$ENDIF};

  SB_SETPARTS             = WM_USER+4;
  SB_GETPARTS             = WM_USER+6;
  SB_GETBORDERS           = WM_USER+7;
  SB_SETMINHEIGHT         = WM_USER+8;
  SB_SIMPLE               = WM_USER+9;
  SB_GETRECT              = WM_USER + 10;
  SB_ISSIMPLE             = WM_USER+14;
  SB_SETICON              = WM_USER+15;
  SB_GETICON              = WM_USER+20;
  SB_SETUNICODEFORMAT     = CCM_SETUNICODEFORMAT;
  SB_GETUNICODEFORMAT     = CCM_GETUNICODEFORMAT;

  SBT_OWNERDRAW            = $1000;
  SBT_NOBORDERS            = $0100;
  SBT_POPOUT               = $0200;
  SBT_RTLREADING           = $0400;
  SBT_TOOLTIPS             = $0800;

  SB_SETBKCOLOR            = CCM_SETBKCOLOR;      // lParam = bkColor

  SBARS_SIZEGRIP          = $0100;

  { List View Styles }
  LVS_ICON                = $0000;
  LVS_REPORT              = $0001;
  LVS_SMALLICON           = $0002;
  LVS_LIST                = $0003;

  LVS_TYPEMASK            = $0003;
  LVS_SINGLESEL           = $0004;
  LVS_SHOWSELALWAYS       = $0008;
  LVS_SORTASCENDING       = $0010;
  LVS_SORTDESCENDING      = $0020;
  LVS_SHAREIMAGELISTS     = $0040;
  LVS_NOLABELWRAP         = $0080;
  LVS_AUTOARRANGE         = $0100;
  LVS_EDITLABELS          = $0200;
  LVS_OWNERDATA           = $1000;
  LVS_NOSCROLL            = $2000;

  LVS_TYPESTYLEMASK       = $FC00;

  LVS_ALIGNTOP            = $0000;
  LVS_ALIGNLEFT           = $0800;
  LVS_ALIGNMASK           = $0c00;

  LVS_OWNERDRAWFIXED      = $0400;
  LVS_NOCOLUMNHEADER      = $4000;
  LVS_NOSORTHEADER        = $8000;

  { List View Extended Styles }
  LVS_EX_GRIDLINES        = $00000001;
  LVS_EX_SUBITEMIMAGES    = $00000002;
  LVS_EX_CHECKBOXES       = $00000004;
  LVS_EX_TRACKSELECT      = $00000008;
  LVS_EX_HEADERDRAGDROP   = $00000010;
  LVS_EX_FULLROWSELECT    = $00000020; // applies to report mode only
  LVS_EX_ONECLICKACTIVATE = $00000040;
  LVS_EX_TWOCLICKACTIVATE = $00000080;
  LVS_EX_FLATSB           = $00000100;
  LVS_EX_REGIONAL         = $00000200;
  LVS_EX_INFOTIP          = $00000400; // listview does InfoTips for you
  LVS_EX_LABELTIP         = $00004000; 
  LVS_EX_UNDERLINEHOT     = $00000800;
  LVS_EX_UNDERLINECOLD    = $00001000;
  LVS_EX_MULTIWORKAREAS   = $00002000;

  I_IMAGECALLBACK         = -1;
  I_SKIP                  = -2;
  LVSIL_NORMAL            = 0;
  LVSIL_SMALL             = 1;
  LVSIL_STATE             = 2;

  { List View column styles }
  LVCF_FMT                = $0001;
  LVCF_WIDTH              = $0002;
  LVCF_TEXT               = $0004;
  LVCF_SUBITEM            = $0008;
  LVCF_IMAGE              = $0010;
  LVCF_ORDER              = $0020;
  LVSCW_AUTOSIZE              = -1;
  LVSCW_AUTOSIZE_USEHEADER    = -2;

  LVCFMT_LEFT             = $0000;
  LVCFMT_RIGHT            = $0001;
  LVCFMT_CENTER           = $0002;
  LVCFMT_JUSTIFYMASK      = $0003;

  LVCFMT_IMAGE            = $0800;
  LVCFMT_BITMAP_ON_RIGHT  = $1000;
  LVCFMT_COL_HAS_IMAGES   = $8000;

  LVIF_TEXT               = $0001;
  LVIF_IMAGE              = $0002;
  LVIF_PARAM              = $0004;
  LVIF_STATE              = $0008;
  LVIF_INDENT             = $0010;
  //LVIF_NORECOMPUTE        = $0800;
  LVIF_DI_SETITEM         = $1000;

  LVIS_FOCUSED            = $0001;
  LVIS_SELECTED           = $0002;
  LVIS_CUT                = $0004;
  LVIS_DROPHILITED        = $0008;
  //LVIS_ACTIVATING         = $0020;

  LVIS_OVERLAYMASK        = $0F00;
  LVIS_STATEIMAGEMASK     = $F000;

  { List View messages }
  LVM_FIRST               = $1000;      { ListView messages }
  LVM_SETUNICODEFORMAT    = CCM_SETUNICODEFORMAT;
  LVM_GETUNICODEFORMAT    = CCM_GETUNICODEFORMAT;
  LVM_GETBKCOLOR          = LVM_FIRST + 0;
  LVM_SETBKCOLOR          = LVM_FIRST + 1;
  LVM_GETIMAGELIST        = LVM_FIRST + 2;
  LVM_SETIMAGELIST        = LVM_FIRST + 3;
  LVM_GETITEMCOUNT        = LVM_FIRST + 4;
  LVM_GETITEMA            = LVM_FIRST + 5;
  LVM_SETITEMA            = LVM_FIRST + 6;
  LVM_INSERTITEMA         = LVM_FIRST + 7;
  LVM_DELETEITEM          = LVM_FIRST + 8;
  LVM_DELETEALLITEMS      = LVM_FIRST + 9;
  LVM_GETCALLBACKMASK     = LVM_FIRST + 10;
  LVM_SETCALLBACKMASK     = LVM_FIRST + 11;
  LVM_GETNEXTITEM         = LVM_FIRST + 12;
  LVM_FINDITEMA           = LVM_FIRST + 13;
  LVM_GETITEMRECT         = LVM_FIRST + 14;
  LVM_SETITEMPOSITION     = LVM_FIRST + 15;
  LVM_GETITEMPOSITION     = LVM_FIRST + 16;
  LVM_GETSTRINGWIDTHA     = LVM_FIRST + 17;
  LVM_HITTEST             = LVM_FIRST + 18;
  LVM_ENSUREVISIBLE       = LVM_FIRST + 19;
  LVM_SCROLL              = LVM_FIRST + 20;
  LVM_REDRAWITEMS         = LVM_FIRST + 21;
  LVM_ARRANGE             = LVM_FIRST + 22;
  LVM_EDITLABELA          = LVM_FIRST + 23;
  LVM_GETCOLUMNA          = LVM_FIRST + 25;
  LVM_SETCOLUMNA          = LVM_FIRST + 26;
  LVM_INSERTCOLUMNA       = LVM_FIRST + 27;
  LVM_DELETECOLUMN        = LVM_FIRST + 28;
  LVM_GETCOLUMNWIDTH      = LVM_FIRST + 29;
  LVM_SETCOLUMNWIDTH      = LVM_FIRST + 30;
  LVM_GETHEADER           = LVM_FIRST + 31;

  LVM_CREATEDRAGIMAGE     = LVM_FIRST + 33;
  LVM_GETVIEWRECT         = LVM_FIRST + 34;
  LVM_GETTEXTCOLOR        = LVM_FIRST + 35;
  LVM_SETTEXTCOLOR        = LVM_FIRST + 36;
  LVM_GETTEXTBKCOLOR      = LVM_FIRST + 37;
  LVM_SETTEXTBKCOLOR      = LVM_FIRST + 38;
  LVM_GETTOPINDEX         = LVM_FIRST + 39;
  LVM_GETCOUNTPERPAGE     = LVM_FIRST + 40;
  LVM_GETORIGIN           = LVM_FIRST + 41;
  LVM_UPDATE              = LVM_FIRST + 42;
  LVM_SETITEMSTATE        = LVM_FIRST + 43;
  LVM_GETITEMSTATE        = LVM_FIRST + 44;
  LVM_GETITEMTEXTA        = LVM_FIRST + 45;
  LVM_SETITEMTEXTA        = LVM_FIRST + 46;
  LVM_SETITEMCOUNT        = LVM_FIRST + 47;
  LVM_SORTITEMS           = LVM_FIRST + 48;
  LVM_SETITEMPOSITION32   = LVM_FIRST + 49;
  LVM_GETSELECTEDCOUNT    = LVM_FIRST + 50;
  LVM_GETITEMSPACING      = LVM_FIRST + 51;
  LVM_GETISEARCHSTRINGA   = LVM_FIRST + 52;
  LVM_SETICONSPACING      = LVM_FIRST + 53;
  LVM_SETEXTENDEDLISTVIEWSTYLE = LVM_FIRST + 54;
  LVM_GETEXTENDEDLISTVIEWSTYLE = LVM_FIRST + 55;
  LVM_GETSUBITEMRECT      = LVM_FIRST + 56;
  LVM_SUBITEMHITTEST      = LVM_FIRST + 57;
  LVM_SETCOLUMNORDERARRAY = LVM_FIRST + 58;
  LVM_GETCOLUMNORDERARRAY = LVM_FIRST + 59;
  LVM_SETHOTITEM  = LVM_FIRST + 60;
  LVM_GETHOTITEM  = LVM_FIRST + 61;
  LVM_SETHOTCURSOR  = LVM_FIRST + 62;
  LVM_GETHOTCURSOR  = LVM_FIRST + 63;
  LVM_APPROXIMATEVIEWRECT = LVM_FIRST + 64;
  LVM_SETWORKAREA         = LVM_FIRST + 65;
  LVM_GETSELECTIONMARK    = LVM_FIRST + 66;
  LVM_SETSELECTIONMARK    = LVM_FIRST + 67;
  LVM_SETBKIMAGEA         = LVM_FIRST + 68;
  LVM_GETBKIMAGEA         = LVM_FIRST + 69;
  LVM_GETWORKAREAS        = LVM_FIRST + 70;
  LVM_SETHOVERTIME        = LVM_FIRST + 71;
  LVM_GETHOVERTIME        = LVM_FIRST + 72;
  LVM_GETNUMBEROFWORKAREAS  = LVM_FIRST + 73;
  LVM_SETTOOLTIPS       = LVM_FIRST + 74;
  LVM_GETITEMW            = LVM_FIRST + 75;
  LVM_SETITEMW            = LVM_FIRST + 76;
  LVM_INSERTITEMW         = LVM_FIRST + 77;
  LVM_GETTOOLTIPS       = LVM_FIRST + 78;

  LVM_SORTITEMSEX       = LVM_FIRST + 81;

  LVM_FINDITEMW            = LVM_FIRST + 83;
  LVM_GETSTRINGWIDTHW      = LVM_FIRST + 87;

  LVM_GETCOLUMNW          = LVM_FIRST + 95;
  LVM_SETCOLUMNW           = LVM_FIRST + 96;
  LVM_INSERTCOLUMNW        = LVM_FIRST + 97;

  LVM_GETITEMTEXTW         = LVM_FIRST + 115;
  LVM_SETITEMTEXTW         = LVM_FIRST + 116;
  LVM_GETISEARCHSTRINGW    = LVM_FIRST + 117;
  LVM_EDITLABELW           = LVM_FIRST + 118;

  LVM_SETBKIMAGEW         = LVM_FIRST + 138;
  LVM_GETBKIMAGEW         = LVM_FIRST + 139;

  LVM_GETITEM            = {$IFDEF UNICODE_CTRLS} LVM_GETITEMW {$ELSE} LVM_GETITEMA {$ENDIF};
  LVM_SETITEM            = {$IFDEF UNICODE_CTRLS} LVM_SETITEMW {$ELSE} LVM_SETITEMA {$ENDIF};
  LVM_INSERTITEM         = {$IFDEF UNICODE_CTRLS} LVM_INSERTITEMW {$ELSE} LVM_INSERTITEMA {$ENDIF};
  LVM_GETCOLUMN          = {$IFDEF UNICODE_CTRLS} LVM_GETCOLUMNW {$ELSE} LVM_GETCOLUMNA {$ENDIF};
  LVM_SETCOLUMN          = {$IFDEF UNICODE_CTRLS} LVM_SETCOLUMNW {$ELSE} LVM_SETCOLUMNA {$ENDIF};
  LVM_INSERTCOLUMN       = {$IFDEF UNICODE_CTRLS} LVM_INSERTCOLUMNW {$ELSE} LVM_INSERTCOLUMNA {$ENDIF};
  LVM_GETITEMTEXT        = {$IFDEF UNICODE_CTRLS} LVM_GETITEMTEXTW {$ELSE} LVM_GETITEMTEXTA {$ENDIF};
  LVM_SETITEMTEXT        = {$IFDEF UNICODE_CTRLS} LVM_SETITEMTEXTW {$ELSE} LVM_SETITEMTEXTA {$ENDIF};
  LVM_EDITLABEL          = {$IFDEF UNICODE_CTRLS} LVM_EDITLABELW {$ELSE} LVM_EDITLABELA {$ENDIF};
  LVM_FINDITEM           = {$IFDEF UNICODE_CTRLS} LVM_FINDITEMW {$ELSE} LVM_FINDITEMA {$ENDIF};
  LVM_GETISEARCHSTRING   = {$IFDEF UNICODE_CTRLS} LVM_GETISEARCHSTRINGW {$ELSE} LVM_GETISEARCHSTRINGA {$ENDIF};
  LVM_GETSTRINGWIDTH     = {$IFDEF UNICODE_CTRLS} LVM_GETSTRINGWIDTHW {$ELSE} LVM_GETSTRINGWIDTHA {$ENDIF};

  LVM_SETBKIMAGE = {$IFDEF UNICODE_CTRLS} LVM_SETBKIMAGEW {$ELSE} LVM_SETBKIMAGEA {$ENDIF};
  LVM_GETBKIMAGE = {$IFDEF UNICODE_CTRLS} LVM_GETBKIMAGEW {$ELSE} LVM_GETBKIMAGEA {$ENDIF};

  LV_MAX_WORKAREAS        = 16;

  LVIR_BOUNDS             = 0;
  LVIR_ICON               = 1;
  LVIR_LABEL              = 2;
  LVIR_SELECTBOUNDS       = 3;

  LVHT_NOWHERE            = $0001;
  LVHT_ONITEMICON         = $0002;
  LVHT_ONITEMLABEL        = $0004;
  LVHT_ONITEMSTATEICON    = $0008;
  LVHT_ONITEM             = LVHT_ONITEMICON or LVHT_ONITEMLABEL or
			    LVHT_ONITEMSTATEICON;
  LVHT_ABOVE              = $0008;
  LVHT_BELOW              = $0010;
  LVHT_TORIGHT            = $0020;
  LVHT_TOLEFT             = $0040;

  LVNI_ALL                = $0000;
  LVNI_FOCUSED            = $0001;
  LVNI_SELECTED           = $0002;
  LVNI_CUT                = $0004;
  LVNI_DROPHILITED        = $0008;

  LVNI_ABOVE              = $0100;
  LVNI_BELOW              = $0200;
  LVNI_TOLEFT             = $0400;
  LVNI_TORIGHT            = $0800;

  { WM_NOTIFY codes }
  NM_FIRST                 = 0-  0;       { generic to all controls }
  NM_LAST                  = 0- 99;
  NM_OUTOFMEMORY           = NM_FIRST-1;
  NM_CLICK                 = NM_FIRST-2;
  NM_DBLCLK                = NM_FIRST-3;
  NM_RETURN                = NM_FIRST-4;
  NM_RCLICK                = NM_FIRST-5;
  NM_RDBLCLK               = NM_FIRST-6;
  NM_SETFOCUS              = NM_FIRST-7;
  NM_KILLFOCUS             = NM_FIRST-8;
  NM_CUSTOMDRAW            = NM_FIRST-12;
  NM_HOVER                 = NM_FIRST-13;
  NM_NCHITTEST             = NM_FIRST-14;   // uses NMMOUSE struct
  NM_KEYDOWN               = NM_FIRST-15;   // uses NMKEY struct
  NM_RELEASEDCAPTURE       = NM_FIRST-16;
  NM_SETCURSOR             = NM_FIRST-17;   // uses NMMOUSE struct
  NM_CHAR                  = NM_FIRST-18;   // uses NMCHAR struct

  LVN_FIRST                = 0-100;       { listview }
  LVN_LAST                 = 0-199;
  LVN_ITEMCHANGING        = LVN_FIRST-0;
  LVN_ITEMCHANGED         = LVN_FIRST-1;
  LVN_INSERTITEM          = LVN_FIRST-2;
  LVN_DELETEITEM          = LVN_FIRST-3;
  LVN_DELETEALLITEMS      = LVN_FIRST-4;
  LVN_COLUMNCLICK         = LVN_FIRST-8;
  LVN_BEGINDRAG           = LVN_FIRST-9;
  LVN_BEGINRDRAG          = LVN_FIRST-11;
  LVN_ODCACHEHINT         = LVN_FIRST-13;
  LVN_ODFINDITEMA         = LVN_FIRST-52;
  LVN_ODFINDITEMW         = LVN_FIRST-79;
  LVN_ITEMACTIVATE        = LVN_FIRST-14;
  LVN_ODSTATECHANGED      = LVN_FIRST-15;
  LVN_ODFINDITEM          = {$IFDEF UNICODE_CTRLS} LVN_ODFINDITEMW {$ELSE} LVN_ODFINDITEMA {$ENDIF};
  LVN_BEGINLABELEDITA      = LVN_FIRST-5;
  LVN_ENDLABELEDITA        = LVN_FIRST-6;
  LVN_BEGINLABELEDITW      = LVN_FIRST-75;
  LVN_ENDLABELEDITW        = LVN_FIRST-76;
  LVN_BEGINLABELEDIT      = {$IFDEF UNICODE_CTRLS} LVN_BEGINLABELEDITW {$ELSE} LVN_BEGINLABELEDITA {$ENDIF};
  LVN_ENDLABELEDIT        = {$IFDEF UNICODE_CTRLS} LVN_ENDLABELEDITW {$ELSE} LVN_ENDLABELEDITA {$ENDIF};
  LVN_HOTTRACK            = LVN_FIRST-21;
  LVN_GETDISPINFOA        = LVN_FIRST-50;
  LVN_SETDISPINFOA        = LVN_FIRST-51;
  LVN_GETDISPINFOW        = LVN_FIRST-77;
  LVN_SETDISPINFOW        = LVN_FIRST-78;
  LVN_GETDISPINFO        = {$IFDEF UNICODE_CTRLS} LVN_GETDISPINFOW {$ELSE} LVN_GETDISPINFOA {$ENDIF};
  LVN_SETDISPINFO        = {$IFDEF UNICODE_CTRLS} LVN_SETDISPINFOW {$ELSE} LVN_SETDISPINFOA {$ENDIF};

type
  tagNMLVODSTATECHANGE = packed record
    hdr: TNMHdr;
    iFrom: Integer;
    iTo: Integer;
    uNewState: UINT;
    uOldState: UINT;
  end;
  PNMLVODStateChange = ^TNMLVODStateChange;
  TNMLVODStateChange = tagNMLVODSTATECHANGE;

type
  PLVColumn = ^TLVColumn;
  TLVColumn = packed record
    mask: DWORD;
    fmt: DWORD;
    cx: Integer;
    pszText: PKOL_Char;
    cchTextMax: Integer;
    iSubItem: Integer;
    // only IE4+ :
    iImage: Integer;
    iOrder: Integer;
  end;

  PLVItem = ^TLVItem;
  TLVItem = packed record
    mask: DWORD;
    iItem: Integer;
    iSubItem: Integer;
    state: Integer;
    stateMask: DWORD;
    pszText: PKOL_Char;
    cchTextMax: Integer;
    iImage: Integer;
    lParam: LParam;
    iIndent: Integer; // only for IE3.0 and higher
  end;

  PLVDispInfo = ^TLVDispInfo;
  TLVDispInfo = packed record
    hdr: TNMHDR;
    item: TLVItem;
  end;

  PLVFindInfoA = ^TLVFindInfo;
  TLVFindInfo = packed record
    flags: UINT;
    psz: PKOLChar;
    lParam: LPARAM;
    pt: TPoint;
    vkDirection: UINT;
  end;
  PLVFindInfoW = ^TLVFindInfoW;
  TLVFindInfoW = packed record
    flags: UINT;
    psz: PWideChar;
    lParam: LPARAM;
    pt: TPoint;
    vkDirection: UINT;
  end;

  TLVHitTestInfo = packed record
     pt: TPoint;
     flags: DWORD;
     iItem: Integer;
     iSubItem: Integer;
   end;

const
  LVFI_PARAM              = $0001;
  LVFI_STRING             = $0002;
  LVFI_PARTIAL            = $0008;
  LVFI_WRAP               = $0020;
  LVFI_NEARESTXY          = $0040;

const
  HDM_FIRST               = $1200;      { Header messages }
  HDM_GETITEMW             = HDM_FIRST + 11;
  HDM_GETITEMA             = HDM_FIRST + 3;
  HDM_GETITEM              = {$IFDEF UNICODE_CTRLS} HDM_GETITEMW {$ELSE} HDM_GETITEMA {$ENDIF}; 

  HDI_WIDTH               = $0001;

type
  PHDItemA = ^THDItemA;
  PHDItemW = ^THDItemW;
  PHDItem = {$IFDEF UNICODE_CTRLS} PHDItemW {$ELSE} PHDItemA {$ENDIF};
  _HD_ITEMA = packed record
    Mask: Cardinal;
    cxy: Integer;
    pszText: PAnsiChar;
    hbm: HBITMAP;
    cchTextMax: Integer;
    fmt: Integer;
    lParam: LPARAM;
    iImage: Integer;        // index of bitmap in ImageList
    iOrder: Integer;        // where to draw this item
  end;
  _HD_ITEMW = packed record
    Mask: Cardinal;
    cxy: Integer;
    pszText: PWideChar;
    hbm: HBITMAP;
    cchTextMax: Integer;
    fmt: Integer;
    lParam: LPARAM;
    iImage: Integer;        // index of bitmap in ImageList
    iOrder: Integer;        // where to draw this item
  end;
  THDItemA = _HD_ITEMA;
  THDItemW = _HD_ITEMW;
  THDItem = {$IFDEF UNICODE_CTRLS} _HD_ITEMW {$ELSE} _HD_ITEMA {$ENDIF};

const
  TVS_HASBUTTONS          = $0001;
  TVS_HASLINES            = $0002;
  TVS_LINESATROOT         = $0004;
  TVS_EDITLABELS          = $0008;
  TVS_DISABLEDRAGDROP     = $0010;
  TVS_SHOWSELALWAYS       = $0020;
  TVS_RTLREADING          = $0040;
  TVS_NOTOOLTIPS          = $0080;
  TVS_CHECKBOXES          = $0100;
  TVS_TRACKSELECT         = $0200;
  TVS_SINGLEEXPAND        = $0400;
  TVS_INFOTIP             = $0800;
  TVS_FULLROWSELECT       = $1000;
  TVS_NOSCROLL            = $2000;
  TVS_NONEVENHEIGHT       = $4000;

  TVIF_TEXT               = $0001;
  TVIF_IMAGE              = $0002;
  TVIF_PARAM              = $0004;
  TVIF_STATE              = $0008;
  TVIF_HANDLE             = $0010;
  TVIF_SELECTEDIMAGE      = $0020;
  TVIF_CHILDREN           = $0040;
  TVIF_INTEGRAL           = $0080;
  TVIF_DI_SETITEM         = $1000;

  TVIS_FOCUSED            = $0001;
  TVIS_SELECTED           = $0002;
  TVIS_CUT                = $0004;
  TVIS_DROPHILITED        = $0008;
  TVIS_BOLD               = $0010;
  TVIS_EXPANDED           = $0020;
  TVIS_EXPANDEDONCE       = $0040;
  TVIS_EXPANDPARTIAL      = $0080;

  TVIS_OVERLAYMASK        = $0F00;
  TVIS_STATEIMAGEMASK     = $F000;
  TVIS_USERMASK           = $F000;

  TV_FIRST                = $1100;      { TreeView messages }
  TVM_INSERTITEMA         = TV_FIRST + 0;
  TVM_INSERTITEMW          = TV_FIRST + 50;
  TVM_INSERTITEM          = {$IFDEF UNICODE_CTRLS} TVM_INSERTITEMW
                            {$ELSE} TVM_INSERTITEMA {$ENDIF};
  TVM_DELETEITEM          = TV_FIRST + 1;
  TVM_EXPAND              = TV_FIRST + 2;

  TVE_COLLAPSE            = $0001;
  TVE_EXPAND              = $0002;
  TVE_TOGGLE              = $0003;
  TVE_EXPANDPARTIAL       = $4000;
  TVE_COLLAPSERESET       = $8000;

  TVM_GETITEMRECT         = TV_FIRST + 4;
  TVM_GETCOUNT            = TV_FIRST + 5;
  TVM_GETINDENT           = TV_FIRST + 6;
  TVM_SETINDENT           = TV_FIRST + 7;
  TVM_GETIMAGELIST        = TV_FIRST + 8;

  TVSIL_NORMAL            = 0;
  TVSIL_STATE             = 2;

  TVM_SETIMAGELIST        = TV_FIRST + 9;
  TVM_GETNEXTITEM         = TV_FIRST + 10;

  TVGN_ROOT               = $0000;
  TVGN_NEXT               = $0001;
  TVGN_PREVIOUS           = $0002;
  TVGN_PARENT             = $0003;
  TVGN_CHILD              = $0004;
  TVGN_FIRSTVISIBLE       = $0005;
  TVGN_NEXTVISIBLE        = $0006;
  TVGN_PREVIOUSVISIBLE    = $0007;
  TVGN_DROPHILITE         = $0008;
  TVGN_CARET              = $0009;
  TVGN_LASTVISIBLE        = $000A;

  TVM_SELECTITEM          = TV_FIRST + 11;
  TVM_GETITEMA            = TV_FIRST + 12;
  TVM_GETITEMW            = TV_FIRST + 62;
  TVM_GETITEM             = {$IFDEF UNICODE_CTRLS} TVM_GETITEMW {$ELSE} TVM_GETITEMA {$ENDIF};
  TVM_SETITEMA            = TV_FIRST + 13;
  TVM_SETITEMW            = TV_FIRST + 63;
  TVM_SETITEM             = {$IFDEF UNICODE_CTRLS} TVM_SETITEMW {$ELSE} TVM_SETITEMA {$ENDIF};
  TVM_EDITLABELA          = TV_FIRST + 14;
  TVM_EDITLABELW          = TV_FIRST + 65;
  TVM_EDITLABEL           = {$IFDEF UNICODE_CTRLS} TVM_EDITLABELW {$ELSE} TVM_EDITLABELA {$ENDIF};
  TVM_GETEDITCONTROL      = TV_FIRST + 15;
  TVM_GETVISIBLECOUNT     = TV_FIRST + 16;
  TVM_HITTEST             = TV_FIRST + 17;

  TVHT_NOWHERE            = $0001;
  TVHT_ONITEMICON         = $0002;
  TVHT_ONITEMLABEL        = $0004;
  TVHT_ONITEMINDENT       = $0008;
  TVHT_ONITEMBUTTON       = $0010;
  TVHT_ONITEMRIGHT        = $0020;
  TVHT_ONITEMSTATEICON    = $0040;
  TVHT_ONITEM             = TVHT_ONITEMICON or TVHT_ONITEMLABEL or
		            TVHT_ONITEMSTATEICON;

  TVHT_ABOVE              = $0100;
  TVHT_BELOW              = $0200;
  TVHT_TORIGHT            = $0400;
  TVHT_TOLEFT             = $0800;

  TVM_CREATEDRAGIMAGE     = TV_FIRST + 18;
  TVM_SORTCHILDREN        = TV_FIRST + 19;
  TVM_ENSUREVISIBLE       = TV_FIRST + 20;
  TVM_SORTCHILDRENCB      = TV_FIRST + 21;
  TVM_ENDEDITLABELNOW     = TV_FIRST + 22;
  TVM_GETISEARCHSTRINGA   = TV_FIRST + 23;
  TVM_GETISEARCHSTRINGW   = TV_FIRST + 64;
  TVM_GETISEARCHSTRING    = {$IFDEF UNICODE_CTRLS} TVM_GETISEARCHSTRINGW {$ELSE} TVM_GETISEARCHSTRINGA {$ENDIF};
  TVM_SETTOOLTIPS         = TV_FIRST + 24;
  TVM_GETTOOLTIPS         = TV_FIRST + 25;
  TVM_SETINSERTMARK       = TV_FIRST + 26;
  TVM_SETITEMHEIGHT       = TV_FIRST + 27;
  TVM_GETITEMHEIGHT       = TV_FIRST + 28;
  TVM_SETBKCOLOR          = TV_FIRST + 29;
  TVM_SETTEXTCOLOR        = TV_FIRST + 30;
  TVM_GETBKCOLOR          = TV_FIRST + 31;
  TVM_GETTEXTCOLOR        = TV_FIRST + 32;
  TVM_SETSCROLLTIME       = TV_FIRST + 33;
  TVM_GETSCROLLTIME       = TV_FIRST + 34;
  TVM_SETINSERTMARKCOLOR  = TV_FIRST + 37;
  TVM_GETINSERTMARKCOLOR  = TV_FIRST + 38;
  TVM_SETLINECOLOR        = TV_FIRST + 40;

  TVM_SETUNICODEFORMAT     = CCM_SETUNICODEFORMAT;
  TVM_GETUNICODEFORMAT     = CCM_GETUNICODEFORMAT;

  TVN_FIRST                = 0-400;       { treeview }
  TVN_LAST                 = 0-499;
  TVN_SELCHANGINGA         = TVN_FIRST-1;
  TVN_SELCHANGEDA          = TVN_FIRST-2;
  TVN_SELCHANGINGW         = TVN_FIRST-50;
  TVN_SELCHANGEDW          = TVN_FIRST-51;
  TVN_SELCHANGING          = {$IFDEF UNICODE_CTRLS} TVN_SELCHANGINGW {$ELSE} TVN_SELCHANGINGA {$ENDIF};
  TVN_SELCHANGED           = {$IFDEF UNICODE_CTRLS} TVN_SELCHANGEDW {$ELSE} TVN_SELCHANGEDA {$ENDIF};

  TVC_UNKNOWN             = $0000;
  TVC_BYMOUSE             = $0001;
  TVC_BYKEYBOARD          = $0002;

  TVN_GETDISPINFOA        = TVN_FIRST-3;
  TVN_SETDISPINFOA        = TVN_FIRST-4;
  TVN_GETDISPINFOW        = TVN_FIRST-52;
  TVN_SETDISPINFOW        = TVN_FIRST-53;
  TVN_GETDISPINFO         = {$IFDEF UNICODE_CTRLS} TVN_GETDISPINFOW {$ELSE} TVN_GETDISPINFOA {$ENDIF};
  TVN_SETDISPINFO         = {$IFDEF UNICODE_CTRLS} TVN_SETDISPINFOW {$ELSE} TVN_SETDISPINFOA {$ENDIF};

  TVN_ITEMEXPANDINGA       = TVN_FIRST-5;
  TVN_ITEMEXPANDEDA        = TVN_FIRST-6;
  TVN_BEGINDRAGA           = TVN_FIRST-7;
  TVN_BEGINRDRAGA          = TVN_FIRST-8;
  TVN_DELETEITEMA          = TVN_FIRST-9;
  TVN_BEGINLABELEDITA      = TVN_FIRST-10;
  TVN_ENDLABELEDITA        = TVN_FIRST-11;
  TVN_GETINFOTIPA          = TVN_FIRST-13;
  TVN_ITEMEXPANDINGW       = TVN_FIRST-54;
  TVN_ITEMEXPANDEDW        = TVN_FIRST-55;
  TVN_BEGINDRAGW           = TVN_FIRST-56;
  TVN_BEGINRDRAGW          = TVN_FIRST-57;
  TVN_DELETEITEMW          = TVN_FIRST-58;
  TVN_BEGINLABELEDITW      = TVN_FIRST-59;
  TVN_ENDLABELEDITW        = TVN_FIRST-60;
  TVN_GETINFOTIPW          = TVN_FIRST-14;
  TVN_ITEMEXPANDING       = {$IFDEF UNICODE_CTRLS} TVN_ITEMEXPANDINGW {$ELSE} TVN_ITEMEXPANDINGA {$ENDIF};
  TVN_ITEMEXPANDED        = {$IFDEF UNICODE_CTRLS} TVN_ITEMEXPANDEDW {$ELSE} TVN_ITEMEXPANDEDA {$ENDIF};
  TVN_BEGINDRAG           = {$IFDEF UNICODE_CTRLS} TVN_BEGINDRAGW {$ELSE} TVN_BEGINDRAGA {$ENDIF};
  TVN_BEGINRDRAG          = {$IFDEF UNICODE_CTRLS} TVN_BEGINRDRAGW {$ELSE} TVN_BEGINRDRAGA {$ENDIF};
  TVN_DELETEITEM          = {$IFDEF UNICODE_CTRLS} TVN_DELETEITEMW {$ELSE} TVN_DELETEITEMA {$ENDIF};
  TVN_BEGINLABELEDIT      = {$IFDEF UNICODE_CTRLS} TVN_BEGINLABELEDITW {$ELSE} TVN_BEGINLABELEDITA {$ENDIF};
  TVN_ENDLABELEDIT        = {$IFDEF UNICODE_CTRLS} TVN_ENDLABELEDITW {$ELSE} TVN_ENDLABELEDITA {$ENDIF};
  TVN_GETINFOTIP          = {$IFDEF UNICODE_CTRLS} TVN_GETINFOTIPW {$ELSE} TVN_GETINFOTIPA {$ENDIF};
  TVN_KEYDOWN             = TVN_FIRST-12;
  TVN_SINGLEEXPAND        = TVN_FIRST-15;

  TVI_ROOT                = $FFFF0000;
  TVI_FIRST               = $FFFF0001;
  TVI_LAST                = $FFFF0002;
  TVI_SORT                = $FFFF0003;

type
  PTVItemA = ^TTVItemA;
  PTVItemW = ^TTVItemW;
  PTVItem = {$IFDEF UNICODE_CTRLS} PTVItemW {$ELSE} PTVItemA {$ENDIF};
  tagTVITEMA = packed record
    mask: UINT;
    hItem: THandle;
    state: UINT;
    stateMask: UINT;
    pszText: PAnsiChar;
    cchTextMax: Integer;
    iImage: Integer;
    iSelectedImage: Integer;
    cChildren: Integer;
    lParam: LPARAM;
  end;
  tagTVITEMW = packed record
    mask: UINT;
    hItem: THandle;
    state: UINT;
    stateMask: UINT;
    pszText: PWideChar;
    cchTextMax: Integer;
    iImage: Integer;
    iSelectedImage: Integer;
    cChildren: Integer;
    lParam: LPARAM;
  end;
  tagTVITEM = {$IFDEF UNICODE_CTRLS} tagTVITEMW {$ELSE} tagTVITEMA {$ENDIF};
  _TV_ITEMA = tagTVITEMA;
  _TV_ITEMW = tagTVITEMW;
  _TV_ITEM  = {$IFDEF UNICODE_CTRLS} _TV_ITEMW {$ELSE} _TV_ITEMA {$ENDIF};
  TTVItemA  = tagTVITEMA;
  TTVItemW  = tagTVITEMW;
  TTVItem   = {$IFDEF UNICODE_CTRLS} TTVItemW {$ELSE} TTVItemA {$ENDIF};
  TV_ITEMA  = tagTVITEMA;
  TV_ITEMW  = tagTVITEMW;
  TV_ITEM   = {$IFDEF UNICODE_CTRLS} TV_ITEMW {$ELSE} TV_ITEMA {$ENDIF};

  // only used for Get and Set messages.  no notifies
  tagTVITEMEXA = packed record
    mask: UINT;
    hItem: THandle;
    state: UINT;
    stateMask: UINT;
    pszText: PAnsiChar;
    cchTextMax: Integer;
    iImage: Integer;
    iSelectedImage: Integer;
    cChildren: Integer;
    lParam: LPARAM;
    iIntegral: Integer;
  end;
  tagTVITEMEXW = packed record
    mask: UINT;
    hItem: THandle;
    state: UINT;
    stateMask: UINT;
    pszText: PWideChar;
    cchTextMax: Integer;
    iImage: Integer;
    iSelectedImage: Integer;
    cChildren: Integer;
    lParam: LPARAM;
    iIntegral: Integer;
  end;
  tagTVITEMEX = {$IFDEF UNICODE_CTRLS} tagTVITEMEXW {$ELSE} tagTVITEMEXA {$ENDIF};
  PTVItemExA = ^TTVItemExA;
  PTVItemExW = ^TTVItemExW;
  PTVItemEx = {$IFDEF UNICODE_CTRLS} PTVItemExW {$ELSE} PTVItemExA {$ENDIF};
  TTVItemExA = tagTVITEMEXA;
  TTVItemExW = tagTVITEMEXW;
  TTVItemEx = {$IFDEF UNICODE_CTRLS} TTVItemExW {$ELSE} TTVItemExA {$ENDIF};

  PNMTreeViewA = ^TNMTreeViewA;
  PNMTreeViewW = ^TNMTreeViewW;
  PNMTreeView = {$IFDEF UNICODE_CTRLS} PNMTreeViewW {$ELSE} PNMTreeViewA {$ENDIF};
  tagNMTREEVIEWA = packed record
    hdr: TNMHDR;
    action: Integer;
    itemOld: TTVItemA;
    itemNew: TTVItemA;
    ptDrag: TPoint;
  end;
  tagNMTREEVIEWW = packed record
    hdr: TNMHDR;
    action: Integer;
    itemOld: TTVItemW;
    itemNew: TTVItemW;
    ptDrag: TPoint;
  end;
  tagNMTREEVIEW = {$IFDEF UNICODE_CTRLS} tagNMTREEVIEWW {$ELSE} tagNMTREEVIEWA {$ENDIF};
  _NM_TREEVIEWA = tagNMTREEVIEWA;
  _NM_TREEVIEWW = tagNMTREEVIEWW;
  _NM_TREEVIEW = {$IFDEF UNICODE_CTRLS} _NM_TREEVIEWW {$ELSE} _NM_TREEVIEWA {$ENDIF};
  TNMTreeViewA  = tagNMTREEVIEWA;
  TNMTreeViewW  = tagNMTREEVIEWW;
  TNMTreeView = {$IFDEF UNICODE_CTRLS} TNMTreeViewW {$ELSE} TNMTreeViewA {$ENDIF};
  NM_TREEVIEWA  = tagNMTREEVIEWA;
  NM_TREEVIEWW  = tagNMTREEVIEWW;
  NM_TREEVIEW = {$IFDEF UNICODE_CTRLS} NM_TREEVIEWW {$ELSE} NM_TREEVIEWA {$ENDIF};

  tagNMCUSTOMDRAWINFO = packed record
    hdr: TNMHdr;
    dwDrawStage: DWORD;
    hdc: HDC;
    rc: TRect;
    dwItemSpec: DWORD;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    uItemState: UINT;
    lItemlParam: LPARAM;
  end;
  PNMCustomDraw = ^TNMCustomDraw;
  TNMCustomDraw = tagNMCUSTOMDRAWINFO;

const
  // custom draw return flags
  // values under 0x00010000 are reserved for global custom draw values.
  // above that are for specific controls
  CDRF_DODEFAULT          = $00000000;
  CDRF_NEWFONT            = $00000002;
  CDRF_SKIPDEFAULT        = $00000004;
  CDRF_NOTIFYPOSTPAINT    = $00000010;
  CDRF_NOTIFYITEMDRAW     = $00000020;
  CDRF_NOTIFYSUBITEMDRAW  = $00000020;  // flags are the same, we can distinguish by context
  CDRF_NOTIFYPOSTERASE    = $00000040;

  // drawstage flags
  // values under = $00010000 are reserved for global custom draw values.
  // above that are for specific controls
  CDDS_PREPAINT           = $00000001;
  CDDS_POSTPAINT          = $00000002;
  CDDS_PREERASE           = $00000003;
  CDDS_POSTERASE          = $00000004;
  // the = $000010000 bit means it's individual item specific
  CDDS_ITEM               = $00010000;
  CDDS_ITEMPREPAINT       = CDDS_ITEM or CDDS_PREPAINT;
  CDDS_ITEMPOSTPAINT      = CDDS_ITEM or CDDS_POSTPAINT;
  CDDS_ITEMPREERASE       = CDDS_ITEM or CDDS_PREERASE;
  CDDS_ITEMPOSTERASE      = CDDS_ITEM or CDDS_POSTERASE;
  CDDS_SUBITEM            = $00020000;

  // itemState flags
  CDIS_SELECTED       = $0001;
  CDIS_GRAYED         = $0002;
  CDIS_DISABLED       = $0004;
  CDIS_CHECKED        = $0008;
  CDIS_FOCUS          = $0010;
  CDIS_DEFAULT        = $0020;
  CDIS_HOT            = $0040;
  CDIS_MARKED         = $0080;
  CDIS_INDETERMINATE  = $0100;

type
  tagNMLVCUSTOMDRAW = packed record
    nmcd: TNMCustomDraw;
    clrText: COLORREF;
    clrTextBk: COLORREF;
    iSubItem: Integer; // IE 4.0 and higher
  end;
  PNMLVCustomDraw = ^TNMLVCustomDraw;
  TNMLVCustomDraw = tagNMLVCUSTOMDRAW;




  PTVDispInfoA = ^TTVDispInfoA;
  PTVDispInfoW = ^TTVDispInfoW;
  PTVDispInfo = {$IFDEF UNICODE_CTRLS} PTVDispInfoW {$ELSE} PTVDispInfoA {$ENDIF};
  tagTVDISPINFOA = packed record
    hdr: TNMHDR;
    item: TTVItemA;
  end;
  tagTVDISPINFOW = packed record
    hdr: TNMHDR;
    item: TTVItemW;
  end;
  tagTVDISPINFO = {$IFDEF UNICODE_CTRLS} tagTVDISPINFOW {$ELSE} tagTVDISPINFOA {$ENDIF};
  _TV_DISPINFOA = tagTVDISPINFOA;
  _TV_DISPINFOW = tagTVDISPINFOW;
  _TV_DISPINFO = {$IFDEF UNICODE_CTRLS} _TV_DISPINFOW {$ELSE} _TV_DISPINFOA {$ENDIF};
  TTVDispInfoA = tagTVDISPINFOA;
  TTVDispInfoW = tagTVDISPINFOW;
  TTVDispInfo = {$IFDEF UNICODE_CTRLS} TTVDispInfoW {$ELSE} TTVDispInfoA {$ENDIF};
  TV_DISPINFOA = tagTVDISPINFOA;
  TV_DISPINFOW = tagTVDISPINFOW;
  TV_DISPINFO = {$IFDEF UNICODE_CTRLS} TV_DISPINFOW {$ELSE} TV_DISPINFOA {$ENDIF};

  tagNMMOUSE = packed record
    hdr: TNMHdr;
    dwItemSpec: DWORD;
    dwItemData: DWORD;
    pt: TPoint;
    dwHitInfo: DWORD; // any specifics about where on the item or control the mouse is
  end;
  PNMMouse = ^TNMMouse;
  TNMMouse = tagNMMOUSE;

type
  PTVHitTestInfo = ^TTVHitTestInfo;
  TTVHitTestInfo = packed Record
    pt: TPoint;
    fl: DWORD;
    hItem: THandle;
  end;



const

  cctrl = 'comctl32.dll';

  HINST_COMMCTRL = THandle(-1);

  CCS_TOP                 = $00000001;
  CCS_NOMOVEY             = $00000002;
  CCS_BOTTOM              = $00000003;
  CCS_NORESIZE            = $00000004;
  CCS_NOPARENTALIGN       = $00000008;
  CCS_ADJUSTABLE          = $00000020;
  CCS_NODIVIDER           = $00000040;
  CCS_VERT                = $00000080;
  CCS_LEFT                = (CCS_VERT or CCS_TOP);
  CCS_RIGHT               = (CCS_VERT or CCS_BOTTOM);
  CCS_NOMOVEX             = (CCS_VERT or CCS_NOMOVEY);

  PROGRESS_CLASS: array[ 0..17 ] of KOLChar = ('m','s','c','t','l','s','_',
                                 'p','r','o','g','r','e','s','s','3','2',#0);
  STATUSCLASSNAME: array[ 0..18 ] of KOLChar = ('m','s','c','t','l','s','_',
                                  's','t','a','t','u','s','b','a','r','3','2',#0);
  WC_LISTVIEW: array[0..13] of KOLChar = ('S','y','s','L','i','s','t',
                                 'V','i','e','w','3','2',#0);
  TOOLBARCLASSNAME: array[0..15] of KOLChar = ('T','o','o','l','b','a','r',
                                 'W','i','n','d','o','w','3','2',#0 );
  TOOLTIPS_CLASS: array[0..16] of KOLChar = ('t','o','o','l','t','i','p','s','_',
                                 'c','l','a','s','s','3','2',#0);
  WC_TREEVIEW: array[0..13] of KOLChar = ('S','y','s','T','r','e','e',
                                 'V','i','e','w','3','2',#0);
  WC_TABCONTROL: array[0..15] of KOLChar = ('S','y','s','T','a','b','C','o','n','t',
                                 'r','o','l','3','2',#0);
  DATETIMEPICK_CLASS: array[ 0..17 ] of KOLChar = (
    'S','y','s','D','a','t','e','T','i','m','e','P','i','c','k','3','2',#0 );

  TBN_FIRST                = 0-700;       { toolbar }
  TBN_LAST                 = 0-720;

  TBCDRF_NOEDGES              = $00010000;  // Don't draw button edges
  TBCDRF_HILITEHOTTRACK       = $00020000;  // Use color of the button bk when hottracked
  TBCDRF_NOOFFSET             = $00040000;  // Don't offset button if pressed
  TBCDRF_NOMARK               = $00080000;  // Don't draw default highlight of image/text for TBSTATE_MARKED
  TBCDRF_NOETCHEDEFFECT       = $00100000;  // Don't draw etched effect for disabled items

  TB_ENABLEBUTTON         = WM_USER + 1;
  TB_CHECKBUTTON          = WM_USER + 2;
  TB_PRESSBUTTON          = WM_USER + 3;
  TB_HIDEBUTTON           = WM_USER + 4;
  TB_INDETERMINATE        = WM_USER + 5;
  TB_MARKBUTTON           = WM_USER + 6;
  TB_ISBUTTONENABLED      = WM_USER + 9;
  TB_ISBUTTONCHECKED      = WM_USER + 10;
  TB_ISBUTTONPRESSED      = WM_USER + 11;
  TB_ISBUTTONHIDDEN       = WM_USER + 12;
  TB_ISBUTTONINDETERMINATE = WM_USER + 13;
  TB_ISBUTTONHIGHLIGHTED   = WM_USER + 14;
  TB_SETSTATE             = WM_USER + 17;
  TB_GETSTATE             = WM_USER + 18;
  TB_ADDBITMAP            = WM_USER + 19;
  TB_ADDBUTTONSA          = WM_USER + 20;
  TB_ADDBUTTONSW          = WM_USER + 68;
  TB_INSERTBUTTONA        = WM_USER + 21;
  TB_INSERTBUTTONW        = WM_USER + 67;
  TB_DELETEBUTTON         = WM_USER + 22;
  TB_GETBUTTON            = WM_USER + 23;
  TB_BUTTONCOUNT          = WM_USER + 24;
  TB_COMMANDTOINDEX       = WM_USER + 25;

  TB_SAVERESTOREA          = WM_USER + 26;
  TB_ADDSTRINGA            = WM_USER + 28;
  TB_GETBUTTONTEXTA        = WM_USER + 45;
  TBN_GETBUTTONINFOA       = TBN_FIRST-0;

  TB_GETBUTTONINFOW        = WM_USER + 63;
  TB_SETBUTTONINFOW        = WM_USER + 64;
  TB_GETBUTTONINFOA        = WM_USER + 65;
  TB_SETBUTTONINFOA        = WM_USER + 66;
  TB_GETBUTTONINFO         = {$IFDEF UNICODE_CTRLS} TB_GETBUTTONINFOW {$ELSE} TB_GETBUTTONINFOA {$ENDIF};
  TB_SETBUTTONINFO         = {$IFDEF UNICODE_CTRLS} TB_SETBUTTONINFOW {$ELSE} TB_SETBUTTONINFOA {$ENDIF};

  TB_SAVERESTOREW          = WM_USER + 76;
  TB_ADDSTRINGW            = WM_USER + 77;
  TB_GETBUTTONTEXTW        = WM_USER + 75;
  TBN_GETBUTTONINFOW       = TBN_FIRST-20;
  TB_SAVERESTORE          = {$IFDEF UNICODE_CTRLS} TB_SAVERESTOREW {$ELSE} TB_SAVERESTOREA {$ENDIF};
  TB_ADDSTRING            = {$IFDEF UNICODE_CTRLS} TB_ADDSTRINGW {$ELSE} TB_ADDSTRINGA {$ENDIF};
  TB_GETBUTTONTEXT        = {$IFDEF UNICODE_CTRLS} TB_GETBUTTONTEXTW {$ELSE} TB_GETBUTTONTEXTA {$ENDIF};
  TBN_GETBUTTONINFO       = {$IFDEF UNICODE_CTRLS} TBN_GETBUTTONINFOW {$ELSE} TBN_GETBUTTONINFOA {$ENDIF};

  TBN_DROPDOWN            = TBN_FIRST-10;
  TBN_CLOSEUP             = TBN_FIRST-11;

  TB_CUSTOMIZE            = WM_USER + 27;
  TB_GETITEMRECT          = WM_USER + 29;
  TB_BUTTONSTRUCTSIZE     = WM_USER + 30;
  TB_SETBUTTONSIZE        = WM_USER + 31;
  TB_SETBITMAPSIZE        = WM_USER + 32;
  TB_AUTOSIZE             = WM_USER + 33;
  TB_GETTOOLTIPS          = WM_USER + 35;
  TB_SETTOOLTIPS          = WM_USER + 36;
  TB_SETPARENT            = WM_USER + 37;
  TB_SETROWS              = WM_USER + 39;
  TB_GETROWS              = WM_USER + 40;
  TB_SETCMDID             = WM_USER + 42;
  TB_CHANGEBITMAP         = WM_USER + 43;
  TB_GETBITMAP            = WM_USER + 44;
  TB_REPLACEBITMAP        = WM_USER + 46;
  TB_SETINDENT            = WM_USER + 47;
  TB_SETIMAGELIST         = WM_USER + 48;
  TB_GETIMAGELIST         = WM_USER + 49;
  TB_LOADIMAGES           = WM_USER + 50;
  TB_GETRECT              = WM_USER + 51; { wParam is the Cmd instead of index }
  TB_SETHOTIMAGELIST      = WM_USER + 52;
  TB_GETHOTIMAGELIST      = WM_USER + 53;
  TB_SETDISABLEDIMAGELIST = WM_USER + 54;
  TB_GETDISABLEDIMAGELIST = WM_USER + 55;
  TB_SETSTYLE             = WM_USER + 56;
  TB_GETSTYLE             = WM_USER + 57;
  TB_GETBUTTONSIZE        = WM_USER + 58;
  TB_SETBUTTONWIDTH       = WM_USER + 59;
  TB_SETMAXTEXTROWS       = WM_USER + 60;
  TB_GETTEXTROWS          = WM_USER + 61;

  TB_GETOBJECT            = WM_USER + 62;  // wParam == IID, lParam void **ppv
  TB_GETHOTITEM           = WM_USER + 71;
  TB_SETHOTITEM           = WM_USER + 72;  // wParam == iHotItem
  TB_SETANCHORHIGHLIGHT   = WM_USER + 73;  // wParam == TRUE/FALSE
  TB_GETANCHORHIGHLIGHT   = WM_USER + 74;
  TB_MAPACCELERATORA      = WM_USER + 78;  // wParam == ch, lParam int * pidBtn

  TB_SETEXTENDEDSTYLE     = WM_USER + 84;  // For TBSTYLE_EX_*
  TB_GETEXTENDEDSTYLE     = WM_USER + 85;  // For TBSTYLE_EX_*
  TB_INSERTBUTTON         = {$IFDEF UNICODE_CTRLS} TB_INSERTBUTTONW {$ELSE} TB_INSERTBUTTONA {$ENDIF};
  TB_ADDBUTTONS           = {$IFDEF UNICODE_CTRLS} TB_ADDBUTTONSW {$ELSE} TB_ADDBUTTONSA {$ENDIF};

  IDB_STD_SMALL_COLOR     = 0;
  IDB_STD_LARGE_COLOR     = 1;
  IDB_VIEW_SMALL_COLOR    = 4;
  IDB_VIEW_LARGE_COLOR    = 5;
  IDB_HIST_SMALL_COLOR    = 8;
  IDB_HIST_LARGE_COLOR    = 9;

  STD_CUT                 = 0;
  STD_COPY                = 1;
  STD_PASTE               = 2;
  STD_UNDO                = 3;
  STD_REDO                = 4;
  STD_DELETE              = 5;
  STD_FILENEW             = 6;
  STD_FILEOPEN            = 7;
  STD_FILESAVE            = 8;
  STD_PRINTPRE            = 9;
  STD_PROPERTIES          = 10;
  STD_HELP                = 11;
  STD_FIND                = 12;
  STD_REPLACE             = 13;
  STD_PRINT               = 14;

{ icon indexes for standard view bitmap }

  VIEW_LARGEICONS         = 0;
  VIEW_SMALLICONS         = 1;
  VIEW_LIST               = 2;
  VIEW_DETAILS            = 3;
  VIEW_SORTNAME           = 4;
  VIEW_SORTSIZE           = 5;
  VIEW_SORTDATE           = 6;
  VIEW_SORTTYPE           = 7;
  VIEW_PARENTFOLDER       = 8;
  VIEW_NETCONNECT         = 9;
  VIEW_NETDISCONNECT      = 10;
  VIEW_NEWFOLDER          = 11;
  VIEW_VIEWMENU           = 12;

{ icon indexes for standard history bitmap }

  HIST_BACK               = 0;
  HIST_FORWARD            = 1;
  HIST_FAVORITES          = 2;
  HIST_ADDTOFAVORITES     = 3;
  HIST_VIEWTREE           = 4;

  TBSTATE_CHECKED         = $01;
  TBSTATE_PRESSED         = $02;
  TBSTATE_ENABLED         = $04;
  TBSTATE_HIDDEN          = $08;
  TBSTATE_INDETERMINATE   = $10;
  TBSTATE_WRAP            = $20;
  TBSTATE_ELLIPSES        = $40;
  TBSTATE_MARKED          = $80;

  TBSTYLE_BUTTON          = $00;
  TBSTYLE_SEP             = $01;
  TBSTYLE_CHECK           = $02;
  TBSTYLE_GROUP           = $04;
  TBSTYLE_CHECKGROUP      = TBSTYLE_GROUP or TBSTYLE_CHECK;
  TBSTYLE_DROPDOWN        = $08;
  TBSTYLE_AUTOSIZE        = $0010; // automatically calculate the cx of the button
  TBSTYLE_NOPREFIX        = $0020; // if this button should not have accel prefix

  TBSTYLE_TOOLTIPS        = $0100;
  TBSTYLE_WRAPABLE        = $0200;
  TBSTYLE_ALTDRAG         = $0400;
  TBSTYLE_FLAT            = $0800;
  TBSTYLE_LIST            = $1000;
  TBSTYLE_CUSTOMERASE     = $2000;
  TBSTYLE_REGISTERDROP    = $4000;
  TBSTYLE_TRANSPARENT     = $8000;
  TBSTYLE_EX_DRAWDDARROWS = $00000001;

  TBIF_IMAGE              = $00000001;
  TBIF_TEXT               = $00000002;
  TBIF_STATE              = $00000004;
  TBIF_STYLE              = $00000008;
  TBIF_LPARAM             = $00000010;
  TBIF_COMMAND            = $00000020;
  TBIF_SIZE               = $00000040;

  TTN_FIRST                = 0-520;       { tooltips }
  TTN_LAST                 = 0-549;
  TTN_NEEDTEXTA            = TTN_FIRST - 0;
  TTN_NEEDTEXT             = TTN_FIRST - 0;
  TTN_NEEDTEXTW            = TTN_FIRST - 10;

  TTS_ALWAYSTIP           = $01;
  TTS_NOPREFIX            = $02;

  TTM_ACTIVATE            = WM_USER + 1;
  TTM_SETDELAYTIME        = WM_USER + 3;

  TTM_ADDTOOLA             = WM_USER + 4;
  TTM_DELTOOLA             = WM_USER + 5;
  TTM_NEWTOOLRECTA         = WM_USER + 6;
  TTM_GETTOOLINFOA         = WM_USER + 8;
  TTM_SETTOOLINFOA         = WM_USER + 9;
  TTM_HITTESTA             = WM_USER + 10;
  TTM_GETTEXTA             = WM_USER + 11;
  TTM_UPDATETIPTEXTA       = WM_USER + 12;
  TTM_ENUMTOOLSA           = WM_USER + 14;
  TTM_GETCURRENTTOOLA      = WM_USER + 15;

  TTM_ADDTOOLW             = WM_USER + 50;
  TTM_DELTOOLW             = WM_USER + 51;
  TTM_NEWTOOLRECTW         = WM_USER + 52;
  TTM_GETTOOLINFOW         = WM_USER + 53;
  TTM_SETTOOLINFOW         = WM_USER + 54;
  TTM_HITTESTW             = WM_USER + 55;
  TTM_GETTEXTW             = WM_USER + 56;
  TTM_UPDATETIPTEXTW       = WM_USER + 57;
  TTM_ENUMTOOLSW           = WM_USER + 58;
  TTM_GETCURRENTTOOLW      = WM_USER + 59;
  TTM_WINDOWFROMPOINT      = WM_USER + 16;
  TTM_TRACKACTIVATE        = WM_USER + 17;  // wParam = TRUE/FALSE start end  lparam = LPTOOLINFO
  TTM_TRACKPOSITION        = WM_USER + 18;  // lParam = dwPos
  TTM_SETTIPBKCOLOR        = WM_USER + 19;
  TTM_SETTIPTEXTCOLOR      = WM_USER + 20;
  TTM_GETDELAYTIME         = WM_USER + 21;
  TTM_GETTIPBKCOLOR        = WM_USER + 22;
  TTM_GETTIPTEXTCOLOR      = WM_USER + 23;
  TTM_SETMAXTIPWIDTH       = WM_USER + 24;
  TTM_GETMAXTIPWIDTH       = WM_USER + 25;
  TTM_SETMARGIN            = WM_USER + 26;  // lParam = lprc
  TTM_GETMARGIN            = WM_USER + 27;  // lParam = lprc
  TTM_POP                  = WM_USER + 28;
  TTM_POPUP                = WM_USER + 34;
  TTM_UPDATE               = WM_USER + 29;

  TTM_ADDTOOL             = {$IFDEF UNICODE_CTRLS} TTM_ADDTOOLW {$ELSE} TTM_ADDTOOLA {$ENDIF};
  TTM_DELTOOL             = {$IFDEF UNICODE_CTRLS} TTM_DELTOOLW {$ELSE} TTM_DELTOOLA {$ENDIF};
  TTM_NEWTOOLRECT         = {$IFDEF UNICODE_CTRLS} TTM_NEWTOOLRECTW {$ELSE} TTM_NEWTOOLRECTA {$ENDIF};
  TTM_GETTOOLINFO         = {$IFDEF UNICODE_CTRLS} TTM_GETTOOLINFOW {$ELSE} TTM_GETTOOLINFOA {$ENDIF};
  TTM_SETTOOLINFO         = {$IFDEF UNICODE_CTRLS} TTM_SETTOOLINFOW {$ELSE} TTM_SETTOOLINFOA {$ENDIF};
  TTM_HITTEST             = {$IFDEF UNICODE_CTRLS} TTM_HITTESTW {$ELSE} TTM_HITTESTA {$ENDIF};
  TTM_GETTEXT             = {$IFDEF UNICODE_CTRLS} TTM_GETTEXTW {$ELSE} TTM_GETTEXTA {$ENDIF};
  TTM_UPDATETIPTEXT       = {$IFDEF UNICODE_CTRLS} TTM_UPDATETIPTEXTW {$ELSE} TTM_UPDATETIPTEXTA {$ENDIF};
  TTM_ENUMTOOLS           = {$IFDEF UNICODE_CTRLS} TTM_ENUMTOOLSW {$ELSE} TTM_ENUMTOOLSA {$ENDIF};
  TTM_GETCURRENTTOOL      = {$IFDEF UNICODE_CTRLS} TTM_GETCURRENTTOOLW {$ELSE} TTM_GETCURRENTTOOLA {$ENDIF};

  TTM_RELAYEVENT          = WM_USER + 7;
  TTM_GETTOOLCOUNT        = WM_USER +13;

  TTF_IDISHWND            = $0001;
  TTF_CENTERTIP           = $0002;
  TTF_RTLREADING          = $0004;
  TTF_SUBCLASS            = $0010;
  TTF_TRACK               = $0020;
  TTF_ABSOLUTE            = $0080;
  TTF_TRANSPARENT         = $0100;
  TTF_DI_SETITEM          = $8000;       // valid only on the TTN_NEEDTEXT callback

  LPSTR_TEXTCALLBACKA = LPSTR(-1);
  LPSTR_TEXTCALLBACKW = LPWSTR(-1);
  LPSTR_TEXTCALLBACK = {$IFDEF UNICODE_CTRLS} LPSTR_TEXTCALLBACKW {$ELSE} LPSTR_TEXTCALLBACKA {$ENDIF};

  CW_USEDEFAULT = Integer($80000000);

type
  PTBAddBitmap = ^TTBAddBitmap;
  TTBAddBitmap = packed record
    hInst: THandle;
    nID: UINT;
  end;

  PTBButton = ^TTBButton;
  TTBButton = packed record
    iBitmap: Integer;
    idCommand: Integer;
    fsState: Byte;
    fsStyle: Byte;
    bReserved: array[1..2] of Byte;
    dwData: Longint;
    iString: Integer;
  end;

  PTBButtonInfo = ^TTBButtonInfo;
  TTBButtonInfo = packed record
    cbSize: UINT;
    dwMask: DWORD;
    idCommand: Integer;
    iImage: Integer;
    fsState: Byte;
    fsStyle: Byte;
    cx: Word;
    lParam: DWORD;
    pszText: PKOLChar;
    cchText: Integer;
  end;

  PColorMap = ^TColorMap;
  TColorMap = packed record
    cFrom: TColorRef;
    cTo: TColorRef;
  end;

  PTBNotify = ^TTBnotify;
  TTBNotify = packed record
    hdr: TNMHdr;
    iItem: Integer;
    tbButton: TTBButton;
    cchText: Integer;
    pszText: PChar;
  end;

  PNMTBCustomDraw = ^TNMTBCustomDraw;
  TNMTBCustomDraw = packed record
    nmcd: TNMCUSTOMDRAW;
    hbrMonoDither: HBrush;
    hbrLines     : HBrush;
    hpenLines    : HPen;
    clrText      : COLORREF;
    clrMark      : COLORREF;
    clrTextHighlight: COLORREF;
    clrBtnFace      : COLORREF;
    clrBtnHighlight : COLORREF;
    clrHighlightHotTrack: COLORREF;
    rcText          : TRect;
    nStringBkMode   : Integer;
    nHLStringBkMode : Integer;
    iListGap        : Integer;
  end;

  PTooltipText = ^TTooltipText;
  TTooltipText = packed record
    hdr: TNMHdr;
    lpszText: PKOLChar;
    szText: array[0..79] of KOLChar;
    hinst: HINST;
    uFlags: UINT;
    lParam: LPARAM;
  end;

  PToolInfo = ^TToolInfo;
  TToolInfo = packed record
    cbSize: UINT;
    uFlags: UINT;
    hwnd: HWND;
    uId: UINT;
    Rect: TRect;
    hInst: THandle;
    lpszText: PKOLChar;
    lParam: LPARAM;
  end;

const
  WM_MOUSEHOVER                       = $02A1;
  WM_MOUSELEAVE                       = $02A3;

  TME_HOVER           = $00000001;
  TME_LEAVE           = $00000002;
  TME_QUERY           = $40000000;
  TME_CANCEL          = $80000000;

  HOVER_DEFAULT       = $FFFFFFFF;

  ODT_HEADER              = 100;
  ODT_TAB                 = 101;
  ODT_LISTVIEW            = 102;

type
  tagTRACKMOUSEEVENT = packed record
    cbSize: DWORD;
    dwFlags: DWORD;
    hwndTrack: HWND;
    dwHoverTime: DWORD;
  end;
  PTrackMouseEvent = ^TTrackMouseEvent;
  TTrackMouseEvent = tagTRACKMOUSEEVENT;

//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
// Some stuff from new Delphi versions (not available in old ones):
  {$IFNDEF UNICODE_CTRLS}
const
  //IDC_HAND = MakeIntResource(32649);
  IDC_HAND = PChar(32649);
  {$ENDIF}

/////////////////////////////////////////////////////////
const
  VK_PAGE_DOWN = VK_NEXT;
  VK_PAGE_UP   = VK_PRIOR;
  VK_ALT       = VK_MENU;

PBT_APMQUERYSUSPEND        =  00     ;
PBT_APMQUERYSTANDBY        =  01     ;
PBT_APMQUERYSUSPENDFAILED  =  02     ;
PBT_APMQUERYSTANDBYFAILED  =  03     ;
PBT_APMSUSPEND             =  04     ;
PBT_APMSTANDBY             =  05     ;
PBT_APMRESUMECRITICAL      =  06     ;
PBT_APMRESUMESUSPEND       =  07     ;
PBT_APMRESUMESTANDBY       =  08     ;
PBTF_APMRESUMEFROMFAILURE  =  000001 ;
PBT_APMBATTERYLOW          =  09     ;
PBT_APMPOWERSTATUSCHANGE   =  10     ;
PBT_APMOEMEVENT            =  11     ;
PBT_APMRESUMEAUTOMATIC     = $12     ; // hexadecimal $12 = 18 !

{ DATETIMEPICKER}

const
  // messages
  DTM_FIRST         = $1000;
  DTM_GETSYSTEMTIME = DTM_FIRST + 1;
  DTM_SETSYSTEMTIME = DTM_FIRST + 2;
  DTM_GETRANGE      = DTM_FIRST + 3;
  DTM_SETRANGE      = DTM_FIRST + 4;
  DTM_SETFORMATA    = DTM_FIRST + 5;
  DTM_SETMCCOLOR    = DTM_FIRST + 6;
  DTM_GETMCCOLOR    = DTM_FIRST + 7;
  DTM_GETMONTHCAL   = DTM_FIRST + 8;
  DTM_SETMCFONT     = DTM_FIRST + 9;
  DTM_GETMCFONT     = DTM_FIRST + 10;
  DTM_SETFORMATW    = DTM_FIRST + 50;
  DTM_SETFORMAT     = {$IFDEF UNICODE_CTRLS} DTM_SETFORMATW {$ELSE} DTM_SETFORMATA {$ENDIF};

  // Ranges
  GDTR_MIN = $0001;
  GDTR_MAX = $0002;

  // Return Values
  GDT_ERROR = -1;
  GDT_VALID = 0;
  GDT_NONE  = 1;

  // notifications
  DTN_FIRST                = 0-760;       { datetimepick }
  DTN_LAST                 = 0-799;

  DTN_DATETIMECHANGE = DTN_FIRST + 1;  // the systemtime has changed
  DTN_USERSTRINGA    = DTN_FIRST + 2;  // the user has entered a string
  DTN_USERSTRINGW    = DTN_FIRST + 15;
  DTN_WMKEYDOWNA     = DTN_FIRST + 3;  // modify keydown on app format field (X)
  DTN_WMKEYDOWNW     = DTN_FIRST + 16;
  DTN_FORMATA        = DTN_FIRST + 4;  // query display for app format field (X)
  DTN_FORMATW        = DTN_FIRST + 17;
  DTN_FORMATQUERYA   = DTN_FIRST + 5;  // query formatting info for app format field (X)
  DTN_FORMATQUERYW   = DTN_FIRST + 18;
  DTN_DROPDOWN       = DTN_FIRST + 6;  // MonthCal has dropped down
  DTN_CLOSEUP        = DTN_FIRST + 7;  // MonthCal is popping up
  DTN_USERSTRING     = {$IFDEF UNICODE_CTRLS} DTN_USERSTRINGW {$ELSE} DTN_USERSTRINGA {$ENDIF};
  DTN_WMKEYDOWN      = {$IFDEF UNICODE_CTRLS} DTN_WMKEYDOWNW {$ELSE} DTN_WMKEYDOWNA {$ENDIF};
  DTN_FORMAT         = {$IFDEF UNICODE_CTRLS} DTN_FORMATW {$ELSE} DTN_FORMATA {$ENDIF};
  DTN_FORMATQUERY    = {$IFDEF UNICODE_CTRLS} DTN_FORMATQUERYW {$ELSE} DTN_FORMATQUERYA {$ENDIF};

  // styles
  DTS_UPDOWN          = $0001;  // use UPDOWN instead of MONTHCAL
  DTS_SHOWNONE        = $0002;  // allow a NONE selection
  DTS_SHORTDATEFORMAT = $0000;  // use the short date format
                                // (app must forward WM_WININICHANGE messages)
  DTS_LONGDATEFORMAT  = $0004;  // use the long date format
                                // (app must forward WM_WININICHANGE messages)
  DTS_TIMEFORMAT      = $0008;  // use the time format
                                // (app must forward WM_WININICHANGE messages)
  DTS_APPCANPARSE     = $0010;  // allow user entered strings
                                // (app MUST respond to DTN_USERSTRING)
  DTS_RIGHTALIGN      = $0020;  // right-align popup instead of left-align it

  // color index constants
  MCSC_BACKGROUND       = 0;   // the background color (between months)
  MCSC_TEXT             = 1;   // the dates
  MCSC_TITLEBK          = 2;   // background of the title
  MCSC_TITLETEXT        = 3;
  MCSC_MONTHBK          = 4;   // background within the month cal
  MCSC_TRAILINGTEXT     = 5;   // the text color of header & trailing days

  // structures
type
  tagNMDATETIMESTRINGA = packed record
    nmhdr: TNmHdr;
    pszUserString: PAnsiChar;     // string user entered
    st: TSystemTime;           // app fills this in
    dwFlags: DWORD;            // GDT_VALID or GDT_NONE
  end;
  tagNMDATETIMESTRINGW = packed record
    nmhdr: TNmHdr;
    pszUserString: PWideChar;     // string user entered
    st: TSystemTime;           // app fills this in
    dwFlags: DWORD;            // GDT_VALID or GDT_NONE
  end;
  tagNMDATETIMESTRING = {$IFDEF UNICODE_CTRLS} tagNMDATETIMESTRINGW {$ELSE} tagNMDATETIMESTRINGA {$ENDIF};
  PNMDateTimeStringA = ^TNMDateTimeStringA;
  PNMDateTimeStringW = ^TNMDateTimeStringW;
  PNMDateTimeString = {$IFDEF UNICODE_CTRLS} PNMDateTimeStringW {$ELSE} PNMDateTimeStringA {$ENDIF};
  TNMDateTimeStringA = tagNMDATETIMESTRINGA;
  TNMDateTimeStringW = tagNMDATETIMESTRINGW;
  TNMDateTimeString = {$IFDEF UNICODE_CTRLS} TNMDateTimeStringW {$ELSE} TNMDateTimeStringA {$ENDIF};

{******************************************************************************}
