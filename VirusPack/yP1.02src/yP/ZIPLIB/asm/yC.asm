.386
.model flat, stdcall
option casemap:none

include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\comdlg32.inc
include \masm32\include\shell32.inc
include \masm32\include\imagehlp.inc

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\comdlg32.lib
includelib \masm32\lib\shell32.lib
includelib \masm32\lib\imagehlp.lib

include \masm32\include\windows.inc
include resource.inc

DlgProc PROTO :HWND, :UINT, :WPARAM, :LPARAM

;------------ CONST ---------
.const
CHECK_SI_FLAG           equ 1
ERASE_HEADER_FLAG       equ 2
DESTROY_IMPORT_FLAG     equ 4
CHECK_HEADER_CRC        equ 8
ANTI_DUMP_FLAG          equ 16
API_REDIRECT_FLAG       equ 32

szFilter                db "ExE files",0,"*.exe",0,"All files",0,"*.*",0,0
szCurDir                db ".",0
szNoFile                db "No file selected up to now !",0
szErr                   db "ERROR",0

;------------ DATA ----------
.data
hInst                   dd 0
hDLG                    dd 0
ofn                     OPENFILENAME <>
cFname           		db MAX_PATH dup (0)

;------------ CODE ----------
.code

include CryptStuff.ASM
include PER.ASM

main:
	invoke GetModuleHandle,0
	mov hInst,eax
	invoke DialogBoxParam,eax,IDD_MAINDLG,0,offset DlgProc,0
THEEND:
	invoke ExitProcess,0

DlgProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	LOCAL  hDrop : HANDLE

	pushad
	.IF uMsg == WM_INITDIALOG
	   invoke LoadIcon,hInst,IDI_ICON
	   invoke SendMessage,hDlg,WM_SETICON,TRUE,eax
	   push hDlg
	   pop hDLG
	   ; check the checkboxes :)
	   invoke CheckDlgButton,hDlg,IDC_CHECKHEADERCRC,TRUE
	   invoke CheckDlgButton,hDlg,IDC_DESTROYIMPORT,TRUE
	   invoke CheckDlgButton,hDlg,IDC_ANTIDUMP,TRUE
	   INVOKE CheckDlgButton,hDlg,IDC_APIREDIRECT,TRUE
	   invoke DragAcceptFiles,hDlg,TRUE
	   
	.ELSEIF uMsg == WM_DROPFILES
	   push wParam
	   pop hDrop
	   invoke DragQueryFile,hDrop,0,offset cFname,sizeof cFname
	   invoke DragFinish,hDrop
	   invoke SetDlgItemText,hDlg,IDC_TARGETFILE,offset cFname
	   
	.ELSEIF uMsg == WM_COMMAND
           mov eax,wParam
           
           .IF ax == IDC_CLOSE
              invoke SendMessage,hDlg,WM_CLOSE,NULL,NULL
              
	   .ELSEIF ax == IDC_CHOOSEFILE
	      ; get a file path
	      mov ofn.lStructSize,SIZEOF ofn 
	      mov ofn.lpstrFilter,offset szFilter
	      push hDlg
	      pop ofn.hwndOwner
	      mov ofn.lpstrFile, offset cFname 
	      mov ofn.nMaxFile,SIZEOF cFname
	      mov ofn.lpstrInitialDir,offset szCurDir
	      mov ofn.Flags, OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST or OFN_LONGNAMES or OFN_HIDEREADONLY
	      push offset ofn
	      call GetOpenFileName
	      test eax,eax
	      jz @@ExitDlgProc
	      invoke SetDlgItemText,hDlg,IDC_TARGETFILE,offset cFname  
	                  
	   .ELSEIF ax == IDC_CRYPT
	      ; ----- was a file selected ? -----
	      mov eax,offset cFname
	      .IF byte ptr [eax] == 0
	         invoke MessageBox,hDlg,offset szNoFile,offset szErr,MB_ICONERROR
	         jmp @@ExitDlgProc
	      .ENDIF
	      
	      ; ---- build the protection flag -----
	      xor edi,edi
	      invoke IsDlgButtonChecked,hDlg,IDC_SICHECK
	      .IF eax == BST_CHECKED
	         or edi,CHECK_SI_FLAG
	      .ENDIF
	      invoke IsDlgButtonChecked,hDlg,IDC_ERASEPEHEADER
	      .IF eax == BST_CHECKED
	         or edi,ERASE_HEADER_FLAG
	      .ENDIF
	      invoke IsDlgButtonChecked,hDlg,IDC_DESTROYIMPORT
	      .IF eax == BST_CHECKED
	         or edi,DESTROY_IMPORT_FLAG
	      .ENDIF
	      invoke IsDlgButtonChecked,hDlg,IDC_CHECKHEADERCRC
	      .IF eax == BST_CHECKED
	         or edi,CHECK_HEADER_CRC
	      .ENDIF
	      invoke IsDlgButtonChecked,hDlg,IDC_ANTIDUMP
	      .IF eax == BST_CHECKED
	         or edi,ANTI_DUMP_FLAG
	      .ENDIF
	      INVOKE IsDlgButtonChecked,hDlg,IDC_APIREDIRECT
	      .IF EAX == BST_CHECKED
	         OR  EDI, API_REDIRECT_FLAG
	      .ENDIF
	      push edi
	      push hDlg
	      push offset cFname
	      call CryptFile
	   .ENDIF
	   
	.ELSEIF uMsg == WM_CLOSE
	   invoke EndDialog,hDlg,0
	.ENDIF
	popad
	
  @@ExitDlgProc:
	xor eax,eax
	ret
DlgProc endp
end main