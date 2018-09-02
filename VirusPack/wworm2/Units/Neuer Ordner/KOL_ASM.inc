//------------------------------------------------------------------------------
// KOL_ASM.inc ()to be inlude in KOL.pas)
// v 2.80
function MsgBox( const S: KOLString; Flags: DWORD ): DWORD;
asm
        PUSH      EDX
        PUSH      EAX

        MOV       ECX, [Applet]
        XOR       EAX, EAX
        JECXZ     @@1
  {$IFDEF SNAPMOUSE2DFLTBTN}
        PUSHAD
        XCHG      EAX, ECX
        XOR       EDX, EDX
        PUSH      EDX
        PUSH      EDX
        PUSH      EDX
        PUSH      EAX
        MOV       EDX, offset[WndProcSnapMouse2DfltBtn]
        CALL      TControl.AttachProc
        CALL      TControl.Postmsg
        POPAD
  {$ENDIF}

        MOV       EAX, [ECX].TControl.fCaption
  {$IFDEF SNAPMOUSE2DFLTBTN}
        MOV       ECX, [ECX].TControl.fHandle
  {$ENDIF}
@@1:
        XCHG      EAX, [ESP]
        PUSH      EAX
        PUSH      0
        {$IFDEF UNICODE_CTRLS}
        CALL      MessageBoxW
        {$ELSE}
        CALL      MessageBox
        {$ENDIF}
  {$IFDEF SNAPMOUSE2DFLTBTN}
        MOV       ECX, [Applet]
        JECXZ     @@2
        PUSH      EAX
        XCHG      EAX, ECX
        MOV       EDX, offset[WndProcSnapMouse2DfltBtn]
        CALL      TControl.DetachProc
        POP       EAX
@@2:
  {$ENDIF}
end;

function MakeRect( Left, Top, Right, Bottom: Integer ): TRect; stdcall;
asm
        PUSH       ESI
        PUSH       EDI

        MOV        EDI, @Result
        LEA        ESI, [Left]

        MOVSD
        MOVSD
        MOVSD
        MOVSD

        POP        EDI
        POP        ESI
end;

function RectsEqual( const R1, R2: TRect ): Boolean;
asm
        //LEA       EAX, [R1]
        //LEA       EDX, [R2]
        MOV       ECX, size_TRect
        CALL      CompareMem
end;

function PointInRect( const P: TPoint; const R: TRect ): Boolean;
asm
        PUSH      ESI
        MOV       ECX, EAX
        MOV       ESI, EDX
        LODSD
        CMP       EAX, [ECX]
        JG        @@fail
        LODSD
        CMP       EAX, [ECX+4]
        JG        @@fail
        LODSD
        CMP       [ECX], EAX
        JG        @@fail
        LODSD
        CMP       [ECX+4], EAX
@@fail: SETLE     AL
        POP       ESI
end;

function MakePoint( X, Y: Integer ): TPoint;
asm
        MOV      ECX, @Result
        MOV      [ECX].TPoint.x, EAX
        MOV      [ECX].TPoint.y, EDX
end;

function MakeFlags( FlgSet: PDWORD; FlgArray: array of Integer): Integer;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, [EAX]
        MOV      ESI, EDX
        XOR      EDX, EDX
        INC      ECX
        JZ       @@exit
@@loo:
        LODSD
        TEST     EAX, EAX
        JGE      @@ge
        NOT      EAX
        TEST     BL, 1
        JZ       @@or
        DEC      EBX
@@ge:
        TEST     BL, 1
        JZ       @@nx
@@or:
        OR       EDX, EAX
@@nx:
        SHR      EBX, 1
        LOOP     @@loo

@@exit:
        XCHG     EAX, EDX
        POP      ESI
        POP      EBX
end;

constructor TObj.Create;
asm
        //CALL      System.@ObjSetup - Generated always by compiler
        //JZ        @@exit

        PUSH      EAX
        MOV       EDX, [EAX]
        CALL      dword ptr [EDX]
        POP       EAX

@@exit:
end;

{$IFDEF OLD_REFCOUNT}
procedure TObj.DoDestroy;
asm
        MOV       EDX, [EAX].fRefCount
        SAR       EDX, 1
        JZ        @@1
        JC        @@exit
        DEC       [EAX].fRefCount
        STC

@@1:    JC        @@exit
        MOV       EDX, [EAX]
        CALL      dword ptr [EDX + 4]
@@exit:
end;
{$ENDIF OLD_REFCOUNT}

function TObj.RefDec: Integer;
asm
  TEST  EAX, EAX
  JZ    @@exit
  {$IFDEF OLD_REFCOUNT}
        SUB      [EAX].fRefCount, 2
        JGE      @@exit
        TEST     [EAX].fRefCount, 1
        JZ       @@exit
        MOV      EDX, [EAX]
        PUSH     dword ptr [EDX+4]
  {$ELSE}
        SUB      [EAX].fRefCount, 2
        JGE      @@exit
        MOV      EDX, [EAX]
        PUSH     dword ptr [EDX+4]
  {$ENDIF}
@@exit:
end;

{$IFDEF OLD_FREE}
procedure TObj.Free;
asm
   //TEST    EAX,EAX
   JMP     RefDec
end;
{$ENDIF OLD_FREE}

{$IFNDEF CRASH_DEBUG}
destructor TObj.Destroy;
asm
        PUSH      EAX
        CALL      Final
        POP       EAX
        {$IFDEF USE_NAMES}
        PUSH      EAX
        XOR   EDX, EDX
        XOR   ECX, ECX
        CALL  SetName
        POP       EAX
        PUSH    EAX
        XOR             ECX, ECX
        XCHG    ECX, [EAX].fNamedObjList
        XCHG    EAX, ECX
        CALL    TObj.RefDec
        POP             EAX
        {$ENDIF}
        XOR       EDX, EDX
        CALL      System.@FreeMem
        //CALL      System.@Dispose
end;
{$ENDIF}

{procedure TObj.Final;
asm     //cmd    //opd
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fOnDestroy.TMethod.Code
        JECXZ    @@doAutoFree
        PUSH     EAX
        XCHG     EDX, EAX
        MOV      EAX, [EDX].fOnDestroy.TMethod.Data
        CALL     ECX
        POP      EAX
@@doAutoFree:
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fAutoFree
        JECXZ    @@exit
        PUSH     ESI
        PUSH     ECX
        MOV      ESI, [ECX].TList.fItems
        MOV      ECX, [ECX].TList.fCount
        SHR      ECX, 1
        //JZ @@eloop // should not occur! (when fAutoFree.Count = 0, it is freeing)
@@freeloop:
        MOV      EDX, [ESI+ECX*8-8]
        MOV      EAX, [ESI+ECX*8-4]
        PUSH     ECX
        CALL     EDX
        POP      ECX
        LOOP     @@freeloop
@@eloop:
        POP      EAX
        CALL     TObj.Free
        POP      ESI
@@exit:
end;}

procedure TObj.Add2AutoFree(Obj: PObj);
asm     //cmd    //opd
        PUSH     EBX
        PUSH     EDX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].fAutoFree
        TEST     EAX, EAX
        JNZ      @@1
        CALL     NewList
        MOV      [EBX].fAutoFree, EAX
@@1:    MOV      EBX, EAX
        XOR      EDX, EDX
        POP      ECX
        CALL     TList.Insert
        XCHG     EAX, EBX
        XOR      EDX, EDX
        MOV      ECX, offset TObj.RefDec
        //XOR      ECX, ECX
        CALL     TList.Insert
        POP      EBX
end;

procedure TObj.Add2AutoFreeEx( Proc: TObjectMethod );
asm     //cmd    //opd
        PUSH     EBX
        XCHG     EAX, EBX
        MOV      EAX, [EBX].fAutoFree
        TEST     EAX, EAX
        JNZ      @@1
        CALL     NewList
        MOV      [EBX].fAutoFree, EAX
@@1:    XOR      EDX, EDX
        MOV      ECX, [EBP+12] // Data
        MOV      EBX, EAX
        CALL     TList.Insert
        XCHG     EAX, EBX
        XOR      EDX, EDX
        MOV      ECX, [EBP+8] // Code
        CALL     TList.Insert
        POP      EBX
end;

procedure TObj.RemoveFromAutoFree(Obj: PObj);
asm
  PUSH  EBX
  XCHG  EBX, EAX
  MOV   ECX, [EBX].fAutoFree
  JECXZ @@exit
  XCHG  EAX, ECX
  PUSH  EAX
    CALL  TList.IndexOf
    TEST  EAX, EAX
  POP   EDX
  XCHG  EDX, EAX
  JL    @@exit
  PUSH  EAX
    AND   EDX, not 1
    XOR   ECX, ECX
    MOV   CL, 2
    CALL  TList.DeleteRange
  POP   EAX
  MOV   ECX, [EAX].TList.fCount
  INC   ECX
  LOOP  @@exit
  LEA   EAX, [EBX].fAutoFree
  CALL  Free_And_Nil
@@exit:
  POP   EBX
end;

destructor TList.Destroy;
asm
        PUSH      EAX
        CALL      TList.Clear
        POP       EAX
        CALL      TObj.Destroy
end;

{$IFDEF ASM_TLIST}
procedure TList.Release;
asm
       TEST      EAX, EAX
       JZ        @@e
       MOV       ECX, [EAX].fCount
       JECXZ     @@e
       MOV       EDX, [EAX].fItems
       PUSH      EAX
@@1:
       MOV       EAX, [EDX+ECX*4-4]
       TEST      EAX, EAX
       JZ        @@2
       PUSH      EDX
       PUSH      ECX
       CALL      System.@FreeMem
       POP       ECX
       POP       EDX
@@2:   LOOP      @@1
       POP       EAX
@@e:   CALL      TObj.RefDec
end;
{$ENDIF ASM_TLIST}

procedure TList.SetCapacity( Value: Integer );
asm
  {$IFDEF TLIST_FAST}
  CMP  [EAX].fUseBlocks, 0
  JZ   @@old
  CMP  [EAX].fBlockList, 0
  JNZ  @@just_set
  CMP  EDX, 256
  JLE  @@old
@@just_set:
  MOV  [EAX].fCapacity, EDX
  RET
@@old:
  {$ENDIF}
        CMP       EDX, [EAX].fCount
        {$IFDEF USE_CMOV}
        CMOVL     EDX, [EAX].fCount
        {$ELSE}
        JGE       @@1
        MOV       EDX, [EAX].fCount
@@1:    {$ENDIF}
        CMP       EDX, [EAX].fCapacity
        JE        @@exit

        MOV       [EAX].fCapacity, EDX
        SAL       EDX, 2
        LEA       EAX, [EAX].fItems
        CALL      System.@ReallocMem
@@exit:
end;

procedure TList.Clear;
asm
  {$IFDEF TLIST_FAST}
  PUSH EAX
  MOV  ECX, [EAX].fBlockList
  JECXZ @@1
  MOV  EDX, [ECX].fItems
  MOV  ECX, [ECX].fCount
  SHR  ECX, 1
  JZ   @@1
@@0:
  MOV  EAX, [EDX]
  ADD  EDX, 8
  PUSH EDX
  PUSH ECX
  CALL TObj.RefDec
  POP  ECX
  POP  EDX
  LOOP @@0
@@1:
  POP  EAX
  PUSH EAX
  XOR  EDX, EDX
  MOV  [EAX].fLastKnownBlockIdx, EDX
  LEA  EAX, [EAX].fBlockList
  CALL Free_And_Nil
  POP  EAX
  {$ENDIF}
        PUSH      [EAX].fItems
        XOR       EDX, EDX
        MOV       [EAX].fItems, EDX
        MOV       [EAX].fCount, EDX
        MOV       [EAX].fCapacity, EDX
        POP       EAX
        CALL      System.@FreeMem
end;

procedure TList.Add( Value: Pointer );
asm
        PUSH      EDX
        {$IFDEF TLIST_FAST}
        //if fUseBlocks and ((fCount >= 256) or Assigned( fBlockList )) then
        CMP       [EAX].fUseBlocks, 0
        JZ        @@old
        MOV       ECX, [EAX].fBlockList
        CMP       [EAX].fCount, 256
        JGE       @@1
        JECXZ     @@old
@@1:
        PUSH      EBX
        PUSH      ESI
        XCHG      EBX, EAX               // EBX == @Self
        MOV       ESI, ECX
        //if fBlockList = nil then
        INC       ECX
        LOOP      @@2
        CALL      NewList
        XCHG      ESI, EAX               // ESI == fBlockList
        MOV       [EBX].fBlockList, ESI  //fBlockList := NewList;
        MOV       [ESI].fUseBlocks, 0    //fBlockList.fUseBlocks := FALSE;
        XOR       EDX, EDX
        XCHG      EDX, [EBX].fItems      //fItems := nil;
        MOV       EAX, ESI
        CALL      TList.Add              //fBlockList.Add( fItems );
        MOV       EDX, [EBX].fCount
        MOV       EAX, ESI
        CALL      TList.Add              //fBlockList.Add( Pointer( fCount ) );
@@2:
        //if fBlockList.fCount = 0 then
        MOV       ECX, [ESI].fCount
        JECXZ     @@2A
        //LastBlockCount := Integer( fBlockList.fItems[ fBlockList.fCount-1 ] );
        MOV       EDX, [ESI].fItems
        MOV       EAX, [EDX+ECX*4-4]
        //if LastBlockCount >= 256 then
        CMP       EAX, 256
        JL        @@3
@@2A:
        MOV       EAX, ESI
        XOR       EDX, EDX
        CALL      TList.Add             //fBlockList.Add( nil );
        MOV       EAX, ESI
        XOR       EDX, EDX
        CALL      TList.Add             //fBlockList.Add( nil );
        XOR       EAX, EAX              //LastBlockCount := 0;
@@3:
        PUSH      EAX
        //LastBlockStart := fBlockList.Items[ fBlockList.fCount-2 ];
        MOV       ECX, [ESI].fCount
        MOV       EDX, [ESI].fItems
        LEA       EDX, [EDX+ECX*4-8]
        MOV       EAX, [EDX]
        //if LastBlockStart = nil then
        TEST      EAX, EAX
        JNZ       @@4
        //GetMem( LastBlockStart, 256 * Sizeof( Pointer ) );
        PUSH      EDX
          //MOV       EAX, 1024
          XOR       EAX, EAX
          MOV       AH,  4
          CALL      System.@GetMem
        POP       EDX
        //fBlockList.Items[ fBlockList.fCount-2 ] := LastBlockStart;
        MOV       [EDX], EAX
@@4:
        //fBlockList.Items[ fBlockList.fCount-1 ] := Pointer( LastBlockCount+1 );
        INC       [EDX+4]
        POP       ECX      // ECX == LastBlockCount

        //inc( fCount );
        INC       [EBX].fCount
        //PDWORD( Integer(LastBlockStart) + Sizeof(Pointer)*LastBlockCount )^ :=
        //        DWORD( Value );

        POP       ESI
        POP       EBX
        POP       EDX      // EDX == Value
        MOV       [EAX+ECX*4], EDX
        RET
@@old:
        {$ENDIF TLIST_FAST}
        LEA       ECX, [EAX].fCount
        MOV       EDX, [ECX]
        INC       dword ptr [ECX]
          PUSH      EDX
          CMP       EDX, [EAX].fCapacity
            PUSH      EAX
            JL        @@ok

            MOV       ECX, [EAX].fAddBy
            TEST      ECX, ECX
            JNZ       @@add
            MOV       ECX, EDX
            SHR       ECX, 2
            INC       ECX
          @@add:
            ADD       EDX, ECX
            CALL      TList.SetCapacity
@@ok:
            POP       ECX  // ECX = Self
          POP       EAX    // EAX = fCount -> Result (for TList.Insert)
        POP       EDX      // EDX = Value

        MOV       ECX, [ECX].fItems
        MOV       [ECX + EAX*4], EDX
end;

{$IFDEF ASM_TLIST}
procedure TList.DeleteRange(Idx, Len: Integer);
asm     //cmd    //opd
        TEST     ECX, ECX
        JLE      @@exit
        CMP      EDX, [EAX].fCount
        JGE      @@exit
        PUSH     EBX
        XCHG     EBX, EAX
        LEA      EAX, [EDX+ECX]
        CMP      EAX, [EBX].fCount
        JBE      @@1
        MOV      ECX, [EBX].fCount
        SUB      ECX, EDX
@@1:
        MOV      EAX, [EBX].fItems
        PUSH     [EBX].fCount
        SUB      [EBX].fCount, ECX
        MOV      EBX, EDX
        LEA      EDX, [EAX+EDX*4]
        LEA      EAX, [EDX+ECX*4]
        ADD      EBX, ECX
        POP      ECX
        SUB      ECX, EBX
        SHL      ECX, 2
        CALL     System.Move
        POP      EBX
@@exit:
end;

function TList.IndexOf( Value: Pointer ): Integer;
asm
        PUSH      EDI

        MOV       EDI, [EAX].fItems
        MOV       ECX, [EAX].fCount
          PUSH      EDI
          DEC       EAX            // make "NZ" - EAX always <> 1
          MOV       EAX, EDX
          REPNZ     SCASD
          POP       EDX
        {$IFDEF USE_CMOV}
        CMOVNZ    EDI, EDX
        {$ELSE}
        JZ        @@succ
        MOV       EDI, EDX
@@succ: {$ENDIF}

        MOV       EAX, EDI
        STC
        SBB       EAX, EDX
        SAR       EAX, 2

        POP       EDI
end;

procedure TList.Insert(Idx: Integer; Value: Pointer);
asm
        PUSH      ECX
        PUSH      EAX
        PUSH      [EAX].fCount
          PUSH      EDX
          CALL      TList.Add   // don't matter what to add
          POP       EDX         // EDX = Idx, Eax = Count-1
        POP       EAX
        SUB       EAX, EDX

        SAL       EAX, 2
        MOV       ECX, EAX      // ECX = (Count - Idx - 1) * 4
        POP       EAX
        MOV       EAX, [EAX].fItems
        LEA       EAX, [EAX + EDX*4]
        JL        @@1
          PUSH      EAX
          LEA       EDX, [EAX + 4]
          CALL      System.Move

          POP       EAX          // EAX = @fItems[ Idx ]
@@1:
        POP       ECX            // ECX = Value
        MOV       [EAX], ECX
end;
{$ENDIF ASM_TLIST}


procedure TList.MoveItem(OldIdx, NewIdx: Integer);
asm
        CMP       EDX, ECX
        JE        @@exit

        CMP       ECX, [EAX].fCount
        JGE       @@exit

        PUSH      EDI

        MOV       EDI, [EAX].fItems
        PUSH      dword ptr [EDI + EDX*4]
          PUSH      ECX
          PUSH      EAX
          CALL      TList.Delete
          POP       EAX
          POP       EDX
        POP       ECX

        POP       EDI
        CALL      TList.Insert
@@exit:
end;

function TList.Last: Pointer;
asm     //cmd    //opd
        MOV      ECX, [EAX].fCount
        JECXZ    @@0
        MOV      EAX, [EAX].fItems
        DEC      ECX
        MOV      ECX, [EAX + ECX*4]
@@0:    XCHG     EAX, ECX
end;

{$IFDEF ASM_TLIST}
procedure TList.Swap(Idx1, Idx2: Integer);
asm
        MOV       EAX, [EAX].fItems
          PUSH      dword ptr [EAX + EDX*4]
            PUSH      ECX
            MOV       ECX, [EAX + ECX*4]
            MOV       [EAX + EDX*4], ECX
            POP       ECX
          POP       EDX
        MOV       [EAX + ECX*4], EDX
end;
{$ENDIF}

procedure Run( var AppletWnd: PControl );
asm
        PUSH      EBX
        XCHG      EBX, EAX
        INC       [AppletRunning]
        MOV       EAX, [EBX]
        MOV       [Applet], EAX
        CALL      CallTControlCreateWindow
        JMP       @@2
@@1:
        CALL      WaitMessage
        MOV       EAX, [EBX]
        CALL      TControl.ProcessMessages
        {$IFDEF   USE_OnIdle}
        MOV       EAX, [EBX]
        CALL      [ProcessIdle]
        {$ENDIF}
@@2:
        MOVZX     ECX, [AppletTerminated]
        JECXZ     @@1

        MOV       ECX, [EBX]
        XCHG      EAX, EBX
        POP       EBX
        JECXZ     @@exit
        CALL      TerminateExecution
@@exit:
end;

function SimpleGetCtlBrushHandle( Sender: PControl ): HBrush;
asm     //        //
        {$IFDEF SMALLEST_CODE}
        PUSH      COLOR_BTNFACE
        CALL      GetSysColorBrush
        {$ELSE}
@@1:    MOV       ECX, [EAX].TControl.fParent
        JECXZ     @@2
        MOV       EDX, [EAX].TControl.fColor
        CMP       EDX, [ECX].TControl.fColor
        XCHG      EAX, ECX
        JE        @@1
        XCHG      EAX, ECX
@@2:    PUSH      EBX
        XCHG      EBX, EAX
        MOV       ECX, [EBX].TControl.fTmpBrush
        JECXZ     @@3
        MOV       EAX, [EBX].TControl.fColor
        CALL      Color2RGB
        CMP       EAX, [EBX].TControl.fTmpBrushColorRGB
        JE        @@3
        XOR       EAX, EAX
        XCHG      [EBX].TControl.fTmpBrush, EAX
        PUSH      EAX
        CALL      DeleteObject
@@3:    MOV       EAX, [EBX].TControl.fTmpBrush
        TEST      EAX, EAX
        JNE       @@4
        MOV       EAX, [EBX].TControl.fColor
        CALL      Color2RGB
        MOV       [EBX].TControl.fTmpBrushColorRGB, EAX
        PUSH      EAX
        CALL      CreateSolidBrush
        MOV       [EBX].TControl.fTmpBrush, EAX
@@4:    POP       EBX
        {$ENDIF SMALLEST_CODE}
end;

function NewBrush: PGraphicTool;
asm
        MOV      [Global_GetCtlBrushHandle], offset NormalGetCtlBrushHandle
        CALL     _NewGraphicTool
        MOV      [EAX].TGraphicTool.fNewProc, offset[NewBrush]
        MOV      [EAX].TGraphicTool.fType, gttBrush
        MOV      [EAX].TGraphicTool.fMakeHandleProc, offset[MakeBrushHandle]
        MOV      [EAX].TGraphicTool.fData.Color, clBtnFace
end;

function NewFont: PGraphicTool;
const FontDtSz = sizeof( TGDIFont );
asm
  MOV EAX, offset[DoApplyFont2Wnd]
  MOV [ApplyFont2Wnd_Proc], EAX
        CALL     _NewGraphicTool
        MOV      [EAX].TGraphicTool.fNewProc, offset[NewFont]
        MOV      [EAX].TGraphicTool.fType, gttFont
        MOV      [EAX].TGraphicTool.fMakeHandleProc, offset[MakeFontHandle]
        MOV      EDX, [DefFontColor]
        MOV      [EAX].TGraphicTool.fData.Color, EDX

        PUSH     EAX
        LEA      EDX, [EAX].TGraphicTool.fData.Font
        MOV      EAX, offset[ DefFont ]
        XOR      ECX, ECX
        MOV      CL, FontDtSz
        CALL     System.Move
        POP      EAX
end;

function NewPen: PGraphicTool;
asm
        CALL     _NewGraphicTool
        MOV      [EAX].TGraphicTool.fNewProc, offset[NewPen]
        MOV      [EAX].TGraphicTool.fType, gttPen
        MOV      [EAX].TGraphicTool.fMakeHandleProc, offset[MakePenHandle]
        MOV      [EAX].TGraphicTool.fData.Pen.Mode, pmCopy
end;

function Color2RGB( Color: TColor ): TColor;
asm
         BTR  EAX, 31
         JNC  @@exit
         PUSH      EAX
         CALL      GetSysColor
@@exit:
end;

function Color2RGBQuad( Color: TColor ): TRGBQuad;
asm
        CALL     Color2RGB
        // code by bart:
        xchg    ah,al                   // xxRRGGBB
        ror     eax,16                  // BBGGxxRR
        xchg    ah,al                   // BBGGRRxx
        shr     eax,8                   // 00BBGGRR
end;

function Color2Color16( Color: TColor ): WORD;
asm
  MOV  EDX, EAX
  SHR  EDX, 19
  AND  EDX, $1F
  MOV  ECX, EAX
  SHR  ECX, 5
  AND  ECX, $7E0;
  MOV  AH, AL
  AND  EAX, $F800
  OR   EAX, EDX
  OR   EAX, ECX
end;

function TGraphicTool.Assign(Value: PGraphicTool): PGraphicTool;
const SzfData = sizeof( fData );
asm     //        //
        TEST      EDX, EDX
        JNZ       @@1
        {$IFDEF OLD_REFCOUNT}
        TEST      EAX, EAX
        JZ        @@0
        CALL      TObj.DoDestroy
        {$ELSE}
        CALL      TObj.RefDec
        {$ENDIF}
        XOR       EAX, EAX
@@0:    RET
@@1:    PUSH      EDI
        MOV       EDI, EDX
        TEST      EAX, EAX
        JNZ       @@2
        XCHG      EAX, EDX
        CALL      dword ptr[EAX].TGraphicTool.fNewProc
@@2:    CMP       EAX, EDI
        JE        @@exit
        PUSH      EBX
        XCHG      EBX, EAX

        MOV       ECX, [EBX].TGraphicTool.fHandle
        JECXZ     @@3
        CMP       ECX, [EDI].TGraphicTool.fHandle
        JE        @@exit1
@@3:
        MOV       EAX, EBX
        CALL      TGraphicTool.Changed
        LEA       EDX, [EBX].TGraphicTool.fData
        LEA       EAX, [EDI].TGraphicTool.fData
        MOV       ECX, SzfData
        CALL      System.Move
        MOV       EAX, EBX
        CALL      TGraphicTool.Changed

@@exit1:
        XCHG      EAX, EBX
        POP       EBX
@@exit: POP       EDI
end;

procedure TGraphicTool.Changed;
asm
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fHandle
        JECXZ    @@exit
        PUSH     EAX
        PUSH     ECX

        CALL     @@CallOnChange

        CALL     DeleteObject
        POP      EAX
@@exit:

@@CallOnChange:
        MOV      ECX, [EAX].fOnChange.TMethod.Code
        JECXZ    @@no_onChange
        PUSH     EAX
        XCHG     EDX, EAX
        MOV      EAX, [EDX].fOnChange.TMethod.Data
        CALL     ECX
        POP      EAX
@@no_onChange:
end;

destructor TGraphicTool.Destroy;
asm
          PUSH      EAX
          CMP       [EAX].fType, gttFont
          JE        @@0
          MOV       ECX, [EAX].fData.Brush.Bitmap
          JECXZ     @@0
          PUSH      ECX
          CALL      DeleteObject
          POP       EAX
          PUSH      EAX
@@0:
        MOV       ECX, [EAX].fHandle
        JECXZ     @@1
        PUSH      ECX
        CALL      DeleteObject
@@1:
          POP       EAX
          CALL      TObj.Destroy
end;

function TGraphicTool.ReleaseHandle: Integer;
asm     //        //
        PUSH      EAX
        CALL      Changed
        POP       EDX
        XOR       EAX, EAX
        XCHG      [EDX].fHandle, EAX
end;

procedure TGraphicTool.SetInt( const Index: Integer; Value: Integer );
asm
        LEA    EDX, [EDX+EAX].fData
        CMP    [EDX], ECX
        JE     @@exit
        MOV    [EDX], ECX
        CALL   Changed
@@exit:
end;

function TGraphicTool.IsFontTrueType: Boolean;
asm
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit

        PUSH     EBX

        PUSH     EAX                  // fHandle

        PUSH     0
        CALL     GetDC

        PUSH     EAX                  // DC
        MOV      EBX, EAX
        CALL     SelectObject
        PUSH     EAX

        XOR      ECX, ECX
        PUSH     ECX
        PUSH     ECX
        PUSH     ECX
        PUSH     ECX
        PUSH     EBX
        CALL     GetFontData

        XCHG     EAX, [ESP]

        PUSH     EAX
        PUSH     EBX
        CALL     SelectObject

        PUSH     EBX
        PUSH     0
        CALL     ReleaseDC

        POP      EAX
        INC      EAX
        SETNZ    AL

        POP      EBX
@@exit:
end;

procedure TextAreaEx( Sender: PCanvas; var Sz : TSize; var Pt : TPoint );
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     EDX // [EBP-4] = @Sz
        PUSH     ECX // [EBP-8] = @Pt
        MOV      EBX, EAX
        CALL     TCanvas.GetFont
        MOV      ESI, [EAX].TGraphicTool.fData.Font.Orientation
        CALL     TGraphicTool.IsFontTrueType
        TEST     AL, AL
        JZ       @@exit

        MOV      EDI, [EBP-8]
        XOR      EAX, EAX
        STOSD
        STOSD
        TEST     ESI, ESI
        JZ       @@exit

        PUSH     EAX // Pts[1].x
        PUSH     EAX // Pts[1].y

        PUSH     ESI
        FILD     dword ptr [ESP]
        POP      EDX

        FILD     word ptr [@@1800]
        FDIV
        //FWAIT
        FLDPI
        FMUL
        //FWAIT

        FLD      ST(0)
        FSINCOS
        FWAIT

        MOV      ESI, [EBP-4]
        LODSD         // Sz.cx
        PUSH     EAX
        FILD     dword ptr [ESP]
        FMUL
        FISTP    dword ptr [ESP] // Pts[2].x
        FWAIT
        NEG      EAX
        PUSH     EAX
        FILD     dword ptr [ESP]
        FMUL
        FISTP    dword ptr [ESP] // Pts[2].y
        FWAIT

        FLDPI
        FLD1
        FLD1
        FADD
        FDIV
        FADD
        FSINCOS
        FWAIT

        LODSD
        NEG      EAX
        PUSH     EAX
        FILD     dword ptr [ESP]
        FMUL
        FISTP    dword ptr [ESP] // Pts[4].x
        FWAIT
        NEG      EAX
        PUSH     EAX
        FILD     dword ptr [ESP]
        FMUL
        FISTP    dword ptr [ESP] // Pts[4].y
        FWAIT

        POP      ECX
        POP      EDX
        PUSH     EDX
        PUSH     ECX
        ADD      EDX, [ESP+12]
        ADD      ECX, [ESP+8]
        PUSH     EDX
        PUSH     ECX

        MOV      ESI, ESP
        XOR      EDX, EDX // MinX
        XOR      EDI, EDI // MinY
        XOR      ECX, ECX
        MOV      CL, 3

@@loo1: LODSD
        CMP      EAX, EDI
        JGE      @@1
        XCHG     EDI, EAX
@@1:    LODSD
        CMP      EAX, EDX
        JGE      @@2
        XCHG     EDX, EAX
@@2:    LOOP     @@loo1

        MOV      ESI, [EBP-4]
        MOV      [ESI], ECX
        MOV      [ESI+4], ECX
        MOV      CL, 4
@@loo2:
        POP      EBX
        SUB      EBX, EDI
        CMP      EBX, [ESI+4]
        JLE      @@3
        MOV      [ESI+4], EBX
@@3:
        POP      EAX
        SUB      EAX, EDX
        CMP      EAX, [ESI]
        JLE      @@4
        MOV      [ESI], EAX
@@4:
        LOOP     @@loo2

        MOV      EDI, [EBP-8]
        STOSD
        XCHG     EAX, EBX
        STOSD
        JMP      @@exit

@@1800: DW  1800

@@exit:
        MOV      ESP, EBP
        POP      EBP
        POP      EDI
        POP      ESI
        POP      EBX
end;

procedure TGraphicTool.SetFontOrientation(Value: Integer);
asm
        MOV      byte ptr [GlobalGraphics_UseFontOrient], 1
        MOV      [GlobalCanvas_OnTextArea], offset[TextAreaEx]

        PUSH     EAX
        XCHG     EAX, EDX
        MOV      ECX, 3600
        CDQ
        IDIV     ECX     // EDX = Value mod 3600
        POP      EAX

        MOV      [EAX].fData.Font.Escapement, EDX
        MOV      ECX, EDX
        XOR      EDX, EDX
        MOV      DL, go_FontOrientation
        CALL     SetInt
end;

function TGraphicTool.GetFontStyle: TFontStyle;
asm
       MOV   EDX, dword ptr [EAX].fData.Font.Italic
       AND   EDX, $010101
       MOV   EAX, [EAX].fData.Font.Weight
       CMP   EAX, 700
       SETGE AL       //AL:1 = fsBold
       ADD   EDX, EDX
       OR    EAX, EDX //AL:2 = fsItalic
       SHR   EDX, 7
       OR    EAX, EDX //AL:3 = fsUnderline
       SHR   EDX, 7
       OR    EAX, EDX //AL:4 = fsStrikeOut
end;

procedure TGraphicTool.SetFontStyle(const Value: TFontStyle);
asm
        PUSH     EDI
        MOV      EDI, EAX
        PUSH     EDX
        CALL     GetFontStyle
        POP      EDX
        CMP      AL, DL
        JE       @@exit
        PUSH     EDI

        LEA      EDI, [EDI].fData.Font.Weight
        MOV      ECX, [EDI]
        SHR      EDX, 1
        JNC      @@1
        CMP      ECX, 700
        JGE      @@2
        MOV      ECX, 700
        JMP      @@2
@@1:    CMP      ECX, 700
        JL       @@2
        XOR      ECX, ECX
@@2:    XCHG     EAX, ECX
        STOSD    // change Weight
        SHR      EDX, 1
        SETC     AL
        STOSB    // change Italic
        SHR      EDX, 1
        SETC     AL
        STOSB    // change Underline
        SHR      EDX, 1
        SETC     AL
        STOSB    // change StrikeOut
        POP      EAX
        CALL     Changed
@@exit: POP      EDI
end;

function TGraphicTool.GetHandle: THandle;
const DataSz = sizeof( TGDIToolData );
asm
        PUSH      EBX
@@start:
        XCHG      EBX, EAX
        MOV       ECX, [EBX].fHandle
        JECXZ     @@1

        MOV       EAX, [EBX].fData.Color
        CALL      Color2RGB
        CMP       EAX, [EBX].fColorRGB
        JE        @@1

        MOV       EAX, EBX
        CALL      ReleaseHandle
        PUSH      EAX
        CALL      DeleteObject

@@1:    MOV       ECX, [EBX].fHandle
        INC       ECX
        LOOP      @@exit

        MOV       ECX, [EBX].fParentGDITool
        JECXZ     @@2
        LEA       EDX, [ECX].fData
        LEA       EAX, [EBX].fData
        MOV       ECX, DataSz
        CALL      CompareMem
        TEST      AL, AL
        MOV       EAX, [EBX].fParentGDITool
        JNZ       @@start

@@2:    MOV       EAX, [EBX].fData.Color
        CALL      Color2RGB
        MOV       [EBX].fColorRGB, EAX
        XCHG      EAX, EBX
        CALL      dword ptr [EAX].fMakeHandleProc
        XCHG      ECX, EAX

@@exit: XCHG      EAX, ECX
        POP       EBX
end;

function MakeBrushHandle( Self_: PGraphicTool ): THandle;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TGraphicTool.fHandle
        TEST     EAX, EAX
        JNZ      @@exit

        MOV      EAX, [EBX].TGraphicTool.fData.Color
        CALL     Color2RGB   // EAX = ColorRef

        XOR      EDX, EDX

        MOV      ECX, [EBX].TGraphicTool.fData.Brush.Bitmap
        PUSH     ECX
        JECXZ    @@1

        MOV      DL, BS_PATTERN
        JMP      @@2

@@1:
        MOV      CL, [EBX].TGraphicTool.fData.Brush.Style
        MOV      DL, CL
        SUB      CL, 2
        JL       @@2

        XCHG     ECX, [ESP]
        MOV      EAX, [EBX].TGraphicTool.fData.Brush.LineColor
        CALL     Color2RGB
        XOR      EDX, EDX
        MOV      DL, BS_HATCHED

@@2:    PUSH     EAX
        PUSH     EDX

        PUSH     ESP
        CALL     CreateBrushIndirect
        MOV      [EBX].TGraphicTool.fHandle, EAX

        ADD      ESP, 12

@@exit:
        POP      EBX
end;

{$IFDEF ASM_UNICODE}
{$IFNDEF AUTO_REPLACE_CLEARTYPE}
function MakeFontHandle( Self_: PGraphicTool ): THandle;
asm
         XCHG   EDX, EAX
         MOV    EAX, [EDX].TGraphicTool.fHandle
         TEST   EAX, EAX
         JNZ    @@exit
         PUSH   EDX
         LEA    ECX, [EDX].TGraphicTool.fData.Font
         PUSH   ECX
         CALL   CreateFontIndirect
         POP    EDX
         MOV    [EDX].TGraphicTool.fHandle, EAX
@@exit:
end;
{$ENDIF AUTO_REPLACE_CLEARTYPE}
{$ENDIF ASM_UNICODE}

function MakePenHandle( Self_: PGraphicTool ): THandle;
asm
        PUSH     EBX
        MOV      EBX, EAX

        MOV      EAX, [EBX].TGraphicTool.fHandle
        TEST     EAX, EAX
        JNZ      @@exit

        MOV      EAX, [EBX].TGraphicTool.fData.Color
        CALL     Color2RGB
        PUSH     EAX
        PUSH     EAX
        PUSH     [EBX].TGraphicTool.fData.Pen.Width
        MOVZX    EAX, [EBX].TGraphicTool.fData.Pen.Style
        PUSH     EAX
        PUSH     ESP
        CALL     CreatePenIndirect
        MOV      [EBX].TGraphicTool.fHandle, EAX
        ADD      ESP, 16
@@exit:
        POP      EBX
end;

function MakeGeometricPenHandle( Self_: PGraphicTool ): THandle;
asm
        MOV      ECX, [EAX].TGraphicTool.fHandle
        INC      ECX
        LOOP     @@exit

        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TGraphicTool.fData.Color
        CALL     Color2RGB // EAX = Color2RGB( fColor )
        CDQ                // EDX = lbHatch (0)
        MOV      ECX, [EBX].TGraphicTool.fData.Pen.BrushBitmap
        JECXZ    @@no_brush_bitmap

        XCHG     EDX, ECX // lbHatch = fPenBrushBitmap
        MOV      CL, BS_PATTERN // = 3
        JMP      @@create_pen

@@no_brush_bitmap:
        MOVZX    ECX, [EBX].TGraphicTool.fData.Pen.BrushStyle
        CMP      CL, 1
        JLE      @@create_pen
        MOV      EDX, ECX
        MOV      CL, 2
        SUB      EDX, ECX

@@create_pen:
        PUSH     EDX
        PUSH     EAX
        PUSH     ECX
        MOV      ECX, ESP

        CDQ
        PUSH     EDX
        PUSH     EDX
        PUSH     ECX
        PUSH     [EBX].TGraphicTool.fData.Pen.Width
        MOVZX    ECX, [EBX].TGraphicTool.fData.Pen.Join
        SHL      ECX, 12
        MOVZX    EDX, [EBX].TGraphicTool.fData.Pen.EndCap
        SHL      EDX, 8
        OR       EDX, ECX
        OR       DL, byte ptr [EBX].TGraphicTool.fData.Pen.Style
        OR       EDX, PS_GEOMETRIC
        PUSH     EDX
        CALL     ExtCreatePen

        POP      ECX
        POP      ECX
        POP      ECX

        MOV      [EBX].TGraphicTool.fHandle, EAX
        POP      EBX
        RET
@@exit:
        XCHG     EAX, ECX
end;

function TCanvas.Assign(SrcCanvas: PCanvas): Boolean;
asm
        PUSH     EBX
        PUSH     ESI
        XCHG     EBX, EAX
        MOV      ESI, EDX

        MOV      EAX, [EBX].fFont
        MOV      EDX, [ESI].fFont
        CALL     TGraphicTool.Assign
        MOV      [EBX].fFont, EAX

        MOV      EAX, [EBX].fBrush
        MOV      EDX, [ESI].fBrush
        CALL     TGraphicTool.Assign
        MOV      [EBX].fBrush, EAX

        MOV      EAX, [EBX].fPen
        MOV      EDX, [ESI].fPen
        CALL     TGraphicTool.Assign
        MOV      [EBX].fPen, EAX

        CALL     AssignChangeEvents

        MOV      ECX, [EBX].fFont
        OR       ECX, [EBX].fBrush
        OR       ECX, [EBX].fPen
        SETNZ    AL

        MOV      EDX, [ESI].fPenPos.x
        MOV      ECX, [ESI].fPenPos.y
        CMP      EDX, [EBX].fPenPos.x
        JNE      @@chg_penpos
        CMP      ECX, [EBX].fPenPos.y
        JE       @@1
@@chg_penpos:
        MOV      AL, 1
        MOV      [EBX].fPenPos.x, EDX
        MOV      [EBX].fPenPos.y, ECX
@@1:
        MOV       EDX, [ESI].fCopyMode
        CMP       EDX, [EBX].fCopyMode
        JE        @@2
        MOV       [EBX].fCopyMode, EDX
        MOV       AL, 1
@@2:
        POP       ESI
        POP       EBX
end;

procedure TCanvas.CreateBrush;
asm
        PUSH     EBX
        MOV      EBX, EAX

        MOV      ECX, [EAX].fBrush
        JECXZ    @@chk_owner

        MOV      EAX, ECX
        CALL     TGraphicTool.GetHandle
        PUSH     EAX

        MOV      EAX, EBX
        CALL     AssignChangeEvents

        MOV      EAX, EBX
        CALL     TCanvas.GetHandle
        PUSH     EAX

        CALL     SelectObject

        MOV      EDX, [EBX].TCanvas.fBrush
        CMP      [EDX].TGraphicTool.fData.Brush.Style, bsSolid

        MOV      EAX, [EDX].TGraphicTool.fData.Color
@@0:
        MOV      EBX, [EBX].TCanvas.fHandle
        MOV      ECX, offset[Color2RGB]
        JNZ      @@1

        PUSH     OPAQUE
        PUSH     EBX

        CALL     ECX //Color2RGB
        PUSH     EAX
        PUSH     EBX
        JMP      @@2
@@1:
        PUSH     TRANSPARENT
        PUSH     EBX

        CALL     ECX //Color2RGB
        NOT      EAX
        PUSH     EAX
        PUSH     EBX
@@2:
        CALL     SetBkColor
        CALL     SetBkMode
@@exit:
        POP      EBX
        RET

@@chk_owner:
        MOV      ECX, [EBX].fOwnerControl
        JECXZ    @@exit

        MOV      EAX, [ECX].TControl.fColor
        XOR      ECX, ECX
        JMP      @@0
end;

procedure TCanvas.CreateFont;
asm
        PUSH     EBX
        MOV      EBX, EAX

        MOV      ECX, [EAX].TCanvas.fFont
        JECXZ    @@chk_owner

        MOV      EAX, [ECX].TGraphicTool.fData.Color
        PUSH     ECX
        CALL     Color2RGB
        XCHG     EAX, [ESP]

        CALL     TGraphicTool.GetHandle
        PUSH     EAX

        MOV      EAX, EBX
        CALL     AssignChangeEvents;

        MOV      EAX, EBX
        CALL     TCanvas.GetHandle
        PUSH     EAX
        MOV      EBX, EAX

        CALL     SelectObject

@@set_txcolor:
        PUSH     EBX
        CALL     SetTextColor

@@exit:
        POP      EBX
        RET

@@chk_owner:
        MOV      ECX, [EBX].fOwnerControl
        JECXZ    @@exit

        MOV      EBX, [EBX].fHandle
        MOV      EAX, [ECX].TControl.fTextColor
        CALL     Color2RGB
        PUSH     EAX
        JMP      @@set_txcolor
end;

procedure TCanvas.CreatePen;
asm
        MOV      ECX, [EAX].TCanvas.fPen
        JECXZ    @@exit

        PUSH     EBX
        MOV      EBX, EAX

        MOV      DL, [ECX].TGraphicTool.fData.Pen.Mode
        MOVZX    EDX, DL
        INC      EDX
        PUSH     EDX

        MOV      EAX, ECX
        CALL     TGraphicTool.GetHandle
        PUSH     EAX

        MOV      EAX, EBX
        CALL     AssignChangeEvents

        MOV      EAX, EBX
        CALL     TCanvas.GetHandle
        PUSH     EAX
        MOV      EBX, EAX

        CALL     SelectObject
        PUSH     EBX
        CALL     SetROP2

        POP      EBX
@@exit:
end;

procedure TCanvas.DeselectHandles;
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        LEA      EBX, [EAX].TCanvas.fState
        //CALL     TCanvas.GetHandle
        MOV      EAX, [EAX].TCanvas.fHandle
        TEST     EAX, EAX
        JZ       @@exit

        MOVZX    EDX, byte ptr[EBX]
        AND      DL, PenValid or BrushValid or FontValid
        JZ       @@exit

        PUSH     EAX
        LEA      EDI, [Stock]

        MOV      ECX, [EDI]
        INC      ECX
        LOOP     @@1

        MOV      ESI, offset[ GetStockObject ]

        PUSH     BLACK_PEN
        CALL     ESI
        STOSD

        PUSH     HOLLOW_BRUSH
        CALL     ESI
        STOSD

        PUSH     SYSTEM_FONT
        CALL     ESI
        STOSD

@@1:
        LEA      ESI, [Stock]
        POP      EDX

        LODSD
        PUSH     EAX
        PUSH     EDX

        LODSD
        PUSH     EAX
        PUSH     EDX

        LODSD
        PUSH     EAX
        PUSH     EDX

        MOV      ESI, offset[ SelectObject ]
        CALL     ESI
        CALL     ESI
        CALL     ESI

        AND      byte ptr [EBX], not( PenValid or BrushValid or FontValid )
@@exit:
        POP      EDI
        POP      ESI
        POP      EBX
end;

function TCanvas.RequiredState(ReqState: DWORD): HDC; stdcall;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, ReqState
        MOV      ESI, [EBP+8] //Self
        MOV      EAX, ESI
        TEST     BL, ChangingCanvas
        JZ       @@1
        CALL     Changing
@@1:    AND      BL, 0Fh

        TEST     BL, HandleValid
        JZ       @@2
        CALL     TCanvas.GetHandle
        TEST     EAX, EAX
        JZ       @@ret_0
@@2:
        MOV      AL, [ESI].TCanvas.fState
        NOT      EAX
        AND      BL, AL
        JZ       @@ret_handle

        TEST     BL, FontValid
        JZ       @@3
        MOV      EAX, ESI
        CALL     CreateFont
@@3:    TEST     BL, PenValid
        JZ       @@5
        MOV      EAX, ESI
        CALL     CreatePen
        MOV      ECX, [ESI].TCanvas.fPen
        JCXZ     @@5
        MOV      AL, [ECX].TGraphicTool.fData.Pen.Style
        DEC      AL
        {$IFDEF PARANOIA} DB $2C, 3 {$ELSE} SUB AL, 3 {$ENDIF}
        JB       @@6
@@5:    TEST     BL, BrushValid
        JZ       @@7
@@6:    MOV      EAX, ESI
        CALL     CreateBrush
@@7:    OR       [ESI].TCanvas.fState, BL
@@ret_handle:
        MOV      EAX, [ESI].TCanvas.fHandle
@@ret_0:
        POP      ESI
        POP      EBX
end;

procedure TCanvas.SetHandle(Value: HDC);
asm
        PUSH     EBX
        MOV      EBX, EAX
        MOV      ECX, [EBX].fHandle
        CMP      ECX, EDX
        JZ       @@exit
        JECXZ    @@chk_val

        PUSH     EDX
        PUSH     ECX
          CALL     DeselectHandles
        POP      EDX

        MOV      ECX, [EBX].fOwnerControl
        JECXZ    @@chk_Release
        CMP      [ECX].TControl.fPaintDC, EDX
        JE       @@clr_Handle

@@chk_Release:
        PUSH     EDX
        CMP      [EBX].fOnGetHandle.TMethod.Code, offset[TControl.DC2Canvas]
        JNE      @@deldc
        PUSH     [ECX].TControl.fHandle
        CALL     ReleaseDC
        JMP      @@clr_Handle
@@deldc:
        CALL     DeleteDC

@@clr_Handle:
        XOR      ECX, ECX
        MOV      [EBX].TCanvas.fHandle, ECX
        MOV      [EBX].TCanvas.fIsPaintDC, CL
        AND      [EBX].TCanvas.fState, not HandleValid

        POP      EDX
@@chk_val:
        TEST     EDX, EDX
        JZ       @@exit

        OR       [EBX].TCanvas.fState, HandleValid
        MOV      [EBX].TCanvas.fHandle, EDX
        LEA      EDX, [EBX].TCanvas.fPenPos
        MOV      EAX, EBX
        CALL     SetPenPos

@@exit: POP      EBX
end;

procedure TCanvas.SetPenPos(const Value: TPoint);
asm
          MOV     ECX, [EDX].TPoint.y
          MOV     EDX, [EDX].TPoint.x
          MOV     [EAX].fPenPos.x, EDX
          MOV     [EAX].fPenPos.y, ECX
          CALL    MoveTo
end;

procedure TCanvas.Changing;
asm
        PUSHAD
        MOV      ECX, [EAX].fOnChange.TMethod.Code
        JECXZ    @@exit
        XCHG     EDX, EAX
        MOV      EAX, [EDX].fOnChange.TMethod.Data
        CALL     ECX
@@exit:
        POPAD
end;

procedure TCanvas.Arc(X1, Y1, X2, Y2, X3, Y3, X4, Y4: Integer); stdcall;
asm
        PUSH     ESI

        PUSH     HandleValid or PenValid or ChangingCanvas
        PUSH     dword ptr [EBP+8]
        CALL     RequiredState

        MOV      EDX, EAX

        LEA      ESI, [Y4]
        STD

        XOR      ECX, ECX
        MOV      CL, 8
@@1:
        LODSD
        PUSH     EAX

        LOOP     @@1

        CLD
        PUSH     EDX  //Canvas.fHandle
        CALL     Windows.Arc
        POP      ESI
end;

procedure TCanvas.Chord(X1, Y1, X2, Y2, X3, Y3, X4, Y4: Integer); stdcall;
asm
        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     dword ptr [EBP + 8]
        CALL     RequiredState

        MOV      EDX, EAX

        PUSH     ESI
        LEA      ESI, [Y4]
        STD

        XOR      ECX, ECX
        MOV      CL, 8
@@1:
        LODSD
        PUSH     EAX

        LOOP     @@1

        CLD
        PUSH     EDX  //Canvas.fHandle
        CALL     Windows.Chord
        POP      ESI
end;

procedure TCanvas.CopyRect(const DstRect: TRect; SrcCanvas: PCanvas;
  const SrcRect: TRect);
asm
        PUSH     ESI
        PUSH     EDI

        PUSH     [EAX].fCopyMode

        PUSH     EDX

          PUSH     HandleValid or BrushValid
          PUSH     ECX

          PUSH     HandleValid or FontValid or BrushValid or ChangingCanvas
          PUSH     EAX
          MOV      ESI, offset[ RequiredState ]
          CALL     ESI
          MOV      EDI, EAX     // EDI = @Self.fHandle

          CALL     ESI
          MOV      EDX, EAX     // EDX = SrcCanvas.fHandle

        POP      ECX          // ECX = @DstRect

        MOV      ESI, [SrcRect]

        MOV      EAX, [ESI].TRect.Bottom
        SUB      EAX, [ESI].TRect.Top
        PUSH     EAX

        MOV      EAX, [ESI].TRect.Right
        SUB      EAX, [ESI].TRect.Left
        PUSH     EAX

        PUSH     [ESI].TRect.Top

        LODSD
        PUSH     EAX

        PUSH     EDX

        MOV      EAX, [ECX].TRect.Bottom
        MOV      EDX, [ECX].TRect.Top
        SUB      EAX, EDX
        PUSH     EAX

        MOV      EAX, [ECX].TRect.Right
        MOV      ESI, [ECX].TRect.Left
        SUB      EAX, ESI
        PUSH     EAX

        PUSH     EDX

        PUSH     ESI

        PUSH     EDI

        CALL     StretchBlt

        POP      EDI
        POP      ESI
end;

procedure TCanvas.DrawFocusRect({$IFNDEF FPC}const{$ENDIF} Rect: TRect);
asm
        PUSH     EDX

        PUSH     HandleValid or BrushValid or FontValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.DrawFocusRect
end;

procedure TCanvas.Ellipse(X1, Y1, X2, Y2: Integer);
asm
        PUSH     [Y2]
        PUSH     [X2]
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.Ellipse
end;

procedure TCanvas.FillRect({$IFNDEF FPC}const{$ENDIF} Rect: TRect);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     EDX
        PUSH     HandleValid or BrushValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState
        MOV      ECX, [EBX].fBrush
        JECXZ    @@chk_ctl

@@fill_with_Brush:
        XCHG     EAX, ECX
        CALL     TGraphicTool.GetHandle
        POP      EDX
        PUSH     EAX
        JMP      @@fin
@@chk_ctl:
        MOV      ECX, [EBX].fOwnerControl
        JECXZ    @@dflt_fill
        XCHG     EAX, ECX
        MOV      ECX, [EAX].TControl.fBrush
        INC      ECX
        LOOP     @@fill_with_Brush
        MOV      EAX, [EAX].TControl.fColor
        CALL     Color2RGB
        PUSH     EAX
        CALL     CreateSolidBrush
        POP      EDX
        PUSH     EAX
        PUSH     EAX
        PUSH     EDX
        PUSH     [EBX].fHandle
        CALL     Windows.FillRect
        CALL     DeleteObject
        POP      EBX
        RET
@@dflt_fill:
        POP      EDX
        PUSH     COLOR_WINDOW + 1
@@fin:
        PUSH     EDX
        PUSH     [EBX].fHandle
        CALL     Windows.FillRect
        POP      EBX
end;

procedure TCanvas.FillRgn(const Rgn: HRgn);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     EDX

        PUSH     HandleValid or BrushValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState

        MOV      ECX, [EBX].TCanvas.fBrush
        JECXZ    @@1

@@fill_rgn_using_Brush:
        XCHG     EAX, ECX
        CALL     TGraphicTool.GetHandle
        POP      EDX
        PUSH     EAX
        PUSH     EDX
        PUSH     [EBX].fHandle
        CALL     Windows.FillRgn
        JMP      @@fin

@@1:    MOV      ECX, [EBX].TCanvas.fOwnerControl
        MOV      EAX, -1 // clWhite
        JECXZ    @@2

        XCHG     EAX, ECX
        MOV      ECX, [EAX].TControl.fBrush
        INC      ECX
        LOOP     @@fill_rgn_using_Brush

        MOV      EAX, [EAX].TControl.fColor
@@2:
        CALL     Color2RGB
        PUSH     EAX
        CALL     CreateSolidBrush // EAX = Br

        POP      EDX // Rgn

        PUSH     EAX //-------------------//
        PUSH     EAX           // Br
        PUSH     EDX           // Rgn
        PUSH     [EBX].FHandle // fHandle
        CALL     Windows.FillRgn

        CALL     DeleteObject

@@fin:
        POP      EBX
end;

procedure TCanvas.FloodFill(X, Y: Integer; Color: TColor;
  FillStyle: TFillStyle);
asm
        PUSH     EBX
        MOV      EBX, EAX

        MOVZX    EAX, [FillStyle]
        TEST     EAX, EAX
        MOV      EAX, FLOODFILLSURFACE   // = 1
        JZ       @@1
        //MOV      EAX, FLOODFILLBORDER  // = 0
        DEC      EAX
@@1:
        PUSH     EAX
        PUSH     [Color]
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or BrushValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState
        PUSH     EAX
        CALL     Windows.ExtFloodFill

        POP      EBX
end;

procedure TCanvas.FrameRect({$IFNDEF FPC}const{$ENDIF} Rect: TRect);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     EDX

        MOV      ECX, [EBX].TCanvas.fBrush
        JECXZ    @@1

        PUSH     [ECX].TGraphicTool.fData.Color
        JMP      @@cr_br

@@1:    MOV      ECX, [EBX].TCanvas.fOwnerControl
        JECXZ    @@2

        PUSH     [ECX].TControl.fColor
        JMP      @@cr_br

@@2:    PUSH     clWhite
@@cr_br:POP      EAX                  // @Rect
        CALL     Color2RGB
        PUSH     EAX
        CALL     CreateSolidBrush
        POP      EDX
          PUSH     EAX
        PUSH     EAX
        PUSH     EDX

        PUSH     HandleValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.FrameRect

        CALL     DeleteObject

        POP      EBX
end;

procedure TCanvas.LineTo(X, Y: Integer);
asm
        PUSH     ECX
        PUSH     EDX
        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState
        PUSH     EAX  //Canvas.fHandle
        CALL     Windows.LineTo
end;

procedure TCanvas.MoveTo(X, Y: Integer);
asm
        PUSH     0
        PUSH     ECX
        PUSH     EDX
        PUSH     HandleValid
        PUSH     EAX
        CALL     RequiredState
        PUSH     EAX  //Canvas.fHandle
        CALL     Windows.MoveToEx
end;

procedure TCanvas.Pie(X1, Y1, X2, Y2, X3, Y3, X4, Y4: Integer); stdcall;
asm
        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     dword ptr [EBP + 8]
        CALL     RequiredState

        MOV      EDX, EAX

        PUSH     ESI
        LEA      ESI, [Y4]
        STD

        XOR      ECX, ECX
        MOV      CL, 8
@@1:
        LODSD
        PUSH     EAX

        LOOP     @@1

        CLD
        PUSH     EDX  //Canvas.fHandle
        CALL     Windows.Pie
        POP      ESI
end;

procedure TCanvas.Polygon(const Points: array of TPoint);
asm
        INC      ECX
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.Polygon
end;

procedure TCanvas.Polyline(const Points: array of TPoint);
asm
        INC      ECX
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or PenValid or BrushValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.Polyline
end;

procedure TCanvas.Rectangle(X1, Y1, X2, Y2: Integer);
asm
        PUSH     [Y2]
        PUSH     [X2]
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or BrushValid or PenValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.Rectangle
end;

procedure TCanvas.RoundRect(X1, Y1, X2, Y2, X3, Y3: Integer);
asm
        PUSH     [Y3]
        PUSH     [X3]
        PUSH     [Y2]
        PUSH     [X2]
        PUSH     ECX
        PUSH     EDX

        PUSH     HandleValid or BrushValid or PenValid or ChangingCanvas
        PUSH     EAX
        CALL     RequiredState

        PUSH     EAX
        CALL     Windows.RoundRect
end;

procedure TCanvas.TextArea(const Text: String; var Sz: TSize;
  var P0: TPoint);
asm
        PUSH     EBX
        MOV      EBX, EAX

        PUSH     ECX
        CALL     TextExtent
        POP      EDX

        MOV      ECX, [P0]
        XOR      EAX, EAX
        MOV      [ECX].TPoint.x, EAX
        MOV      [ECX].TPoint.y, EAX

        CMP      [GlobalCanvas_OnTextArea], EAX
        JZ       @@exit
        MOV      EAX, EBX
        CALL     [GlobalCanvas_OnTextArea]

@@exit:
        POP      EBX
end;

function TCanvas.TextExtent(const Text: string): TSize;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX

        PUSH     ECX               // prepare @Result

        MOV      EAX, EDX
        CALL     System.@LStrLen
        PUSH     EAX               // prepare Length(Text)

        CALL     EDX2PChar
        PUSH     EDX               // prepare PChar(Text)

        PUSH     HandleValid or FontValid
        PUSH     EBX
        CALL     RequiredState

        XCHG     ESI, EAX
        TEST     ESI, ESI          // ESI = fHandle before
        JNZ      @@1

        PUSH     ESI
        CALL     CreateCompatibleDC

        MOV      EDX, EBX
        XCHG     EAX, EDX // EAX := @Self; EDX := DC
        CALL     SetHandle

//****************************************************** // Added By M.Gerasimov
        CMP      [EBX].TCanvas.fIsPaintDC, 1
        JZ       @@2
        XOR      ESI,ESI
@@2:
//******************************************************

@@1:
        PUSH     HandleValid or FontValid
        PUSH     EBX
        CALL     RequiredState
        PUSH     EAX               // prepare DC

        CALL     Windows.GetTextExtentPoint32

        TEST     ESI, ESI
        JNZ      @@exit

        XOR      EDX, EDX
        XCHG     EAX, EBX
        CALL     SetHandle

@@exit:
        POP      ESI
        POP      EBX
end;

procedure TCanvas.TextOut(X, Y: Integer; const Text: String); stdcall;
asm
        PUSH     EBX
        MOV      EBX, [EBP+8]

        MOV      EAX, [Text]
        PUSH     EAX
        CALL     System.@LStrLen
        XCHG     EAX, [ESP]             // prepare Length(Text)

        //CALL     System.@LStrToPChar  // string does not need to be null-terminated !
        PUSH     EAX                    // prepare PChar(Text)
        PUSH     [Y]                    // prepare Y
        PUSH     [X]                    // prepare X

        PUSH     HandleValid or FontValid or BrushValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState
        PUSH     EAX                    // prepare fHandle
        CALL     Windows.TextOut

        POP      EBX
end;

procedure TCanvas.TextRect(const Rect: TRect; X, Y: Integer; const Text: string);
asm
        PUSH     EBX
        XCHG     EBX, EAX

        PUSH     0              // prepare 0

        PUSH     EDX
        PUSH     ECX

        MOV      EAX, [Text]
        PUSH     EAX
        CALL     System.@LStrLen

        POP      ECX            // ECX = @Text[1]
        POP      EDX            // EDX = X
        XCHG     EAX, [ESP]     // prepare Length(Text), EAX = @Rect
        PUSH     ECX            // prepare PChar(Text)
        PUSH     EAX            // prepare @Rect

        XOR      EAX, EAX
        MOV      AL, ETO_CLIPPED // = 4
        MOV      ECX, [EBX].fBrush
        JECXZ    @@opaque

        CMP      [ECX].TGraphicTool.fData.Brush.Style, bsClear
        JZ       @@txtout

@@opaque:
        DB $0C, ETO_OPAQUE //OR       AL, ETO_OPAQUE
@@txtout:
        PUSH     EAX            // prepare Options
        PUSH     [Y]            // prepare Y
        PUSH     EDX            // prepare X

        PUSH     HandleValid or FontValid or BrushValid or ChangingCanvas
        PUSH     EBX
        CALL     RequiredState  // EAX = fHandle
        PUSH     EAX            // prepare fHandle

        CALL     Windows.ExtTextOut

        POP      EBX
end;

function TCanvas.GetBrush: PGraphicTool;
asm
        MOV      ECX, [EAX].fBrush
        INC      ECX
        LOOP     @@exit

        PUSH     EAX
        CALL     NewBrush
        POP      EDX
        PUSH     EAX

        MOV      [EDX].fBrush, EAX

        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Code, Offset[TCanvas.ObjectChanged]
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Data, EDX
        MOV      ECX, [EDX].fOwnerControl
        JECXZ    @@1

        PUSH     [ECX].TControl.fBrush
        MOV      ECX, [ECX].TControl.fColor
        MOV      [EAX].TGraphicTool.fData.Color, ECX
        POP      EDX
        TEST     EDX, EDX
        JZ       @@1

        CALL     TGraphicTool.Assign

@@1:    POP      ECX

@@exit: XCHG     EAX, ECX
end;

function TCanvas.GetFont: PGraphicTool;
asm
        MOV      ECX, [EAX].TCanvas.fFont
        INC      ECX
        LOOP     @@exit

        PUSH     EAX
        CALL     NewFont
        POP      EDX
        PUSH     EAX

        MOV      [EDX].TCanvas.fFont, EAX
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Code, Offset[TCanvas.ObjectChanged]
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Data, EDX

        MOV      ECX, [EDX].fOwnerControl
        JECXZ    @@1

        PUSH     [ECX].TControl.fFont
        MOV      ECX, [ECX].TControl.fTextColor
        MOV      [EAX].TGraphicTool.fData.Color, ECX
        POP      EDX
        TEST     EDX, EDX
        JZ       @@1

        CALL     TGraphicTool.Assign

@@1:    POP      ECX

@@exit: MOV      EAX, ECX
end;

function TCanvas.GetPen: PGraphicTool;
asm
        MOV      ECX, [EAX].TCanvas.fPen
        INC      ECX
        LOOP     @@exit

        PUSH     EAX
        CALL     NewPen
        POP      EDX
        MOV      [EDX].fPen, EAX
        PUSH     EAX
        MOV      EAX, EDX
        CALL     AssignChangeEvents
        POP      ECX

@@exit: MOV      EAX, ECX
end;

function TCanvas.GetHandle: HDC;
asm
        CMP      word ptr[EAX].fOnGetHandle.TMethod.Code+2, 0
        MOV      EDX, EAX
        MOV      EAX, [EDX].fHandle
        JZ       @@exit
        MOV      EAX, [EDX].fOnGetHandle.TMethod.Data
        PUSH     EDX
        CALL     [EDX].fOnGetHandle.TMethod.Code
        XCHG     EAX, [ESP]
        POP      EDX
        PUSH     EDX
        CALL     SetHandle
        POP      EAX
@@exit:
end;

procedure TCanvas.AssignChangeEvents;
asm
        PUSH     ESI
        LEA      ESI, [EAX].fBrush
        MOV      CL, 3
        MOV      EDX, EAX
@@1:    LODSD
        TEST     EAX, EAX
        JZ       @@nxt
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Data, EDX
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Code, offset[ ObjectChanged ]
@@nxt:  DEC      CL
        JNZ      @@1
        POP      ESI
end;

function Mul64i( const X: I64; Mul: Integer ): I64;
asm     //cmd    //opd
        TEST     EDX, EDX
        PUSHFD
        JGE      @@1
        NEG      EDX
@@1:    PUSH     ECX
        CALL     Mul64EDX
        POP      EAX
        POPFD
        JGE      @@2
        MOV      EDX, EAX
        CALL     Neg64
@@2:
end;

function Div64i( const X: I64; D: Integer ): I64;
asm     //cmd    //opd
        PUSH     EBX
        XOR      EBX, EBX
        PUSH     ESI
        XCHG     ESI, EAX
        LODSD
        MOV      [ECX], EAX
        LODSD
        MOV      [ECX+4], EAX
        MOV      ESI, ECX
        PUSH     EDX
        XCHG     EAX, ECX
        CALL     Sgn64
        TEST     EAX, EAX
        JGE      @@1
        INC      EBX
        MOV      EAX, ESI
        MOV      EDX, ESI
        CALL     Neg64
@@1:    POP      EDX
        TEST     EDX, EDX
        JGE      @@2
        XOR      EBX, 1
        NEG      EDX
@@2:    MOV      EAX, ESI
        MOV      ECX, ESI
        CALL     Div64EDX
        DEC      EBX
        JNZ      @@3
        MOV      EDX, ESI
        XCHG     EAX, ESI
        CALL     Neg64
@@3:    POP      ESI
        POP      EBX
end;

function Int2Hex( Value : DWord; Digits : Integer ) : String;
asm     // EAX = Value
        // EDX = Digits
        // ECX = @Result

        PUSH      0
        ADD       ESP, -0Ch

        PUSH      EDI
        PUSH      ECX

        LEA       EDI, [ESP+8+0Fh]  // EBX := @Buf[ 15 ]
        {$IFDEF SMALLEST_CODE}
        {$ELSE}
        AND       EDX, $F
        {$ENDIF}

@@loop: DEC       EDI
        DEC       EDX

        PUSH      EAX
        {$IFDEF PARANOIA} DB $24, $0F {$ELSE} AND AL, 0Fh {$ENDIF}

        {$IFDEF oldcode}

                {$IFDEF PARANOIA} DB $3C, 9 {$ELSE} CMP AL, 9 {$ENDIF}
                JA        @@10
                {$IFDEF PARANOIA} DB $04, 30h-41h+0Ah {$ELSE} ADD AL,30h-41h+0Ah {$ENDIF}
        @@10:
                {$IFDEF PARANOIA} DB $04, 41h-0Ah {$ELSE} ADD AL,41h-0Ah {$ENDIF}

        {$ELSE newcode}

                AAM
                DB $D5, $11 //AAD
                ADD      AL, $30

        {$ENDIF newcode}


        //MOV       byte ptr [EDI], AL
        STOSB
        DEC       EDI
        POP       EAX
        SHR       EAX, 4

        JNZ       @@loop

        TEST      EDX, EDX
        JG        @@loop

        POP       EAX      // EAX = @Result
        MOV       EDX, EDI // EDX = @resulting string
        CALL      System.@LStrFromPChar

        POP       EDI
        ADD       ESP, 10h

{== by KSer - to test it only.
function Int2Hex( Value : DWord; Digits : Integer ) : shortString;
asm
        MOV       [ECX], DL
        XADD      EDX, ECX
@@loop1:
        PUSH      EAX
        db   $24, $0F    // and  al,$0F
        AAM
        DB $D5, $11      // AAD
        db   $04, $30    // add  al,$30
        MOV       [EDX], AL
        POP       EAX
        SHR       EAX, 4
        DEC       EDX
        LOOP      @@loop1
}
end;

function Hex2Int( const Value : String) : Integer;
asm
        CALL     EAX2PChar
        PUSH     ESI
        XCHG     ESI, EAX
        XOR      EDX, EDX
        TEST     ESI, ESI
        JE       @@exit
        LODSB
        {$IFDEF PARANOIA} DB $3C, '$' {$ELSE} CMP AL, '$' {$ENDIF}
        JNE      @@1
@@0:    LODSB
@@1:    TEST     AL, AL
        JE       @@exit
        {$IFDEF PARANOIA} DB $2C, '0' {$ELSE} SUB AL, '0' {$ENDIF}
        {$IFDEF PARANOIA} DB $3C, 9 {$ELSE} CMP AL, '9' - '0' {$ENDIF}
        JBE      @@3

        {$IFDEF PARANOIA} DB $2C, $11 {$ELSE} SUB AL, 'A' - '0' {$ENDIF}
        {$IFDEF PARANOIA} DB $3C, 5 {$ELSE} CMP AL, 'F' - 'A' {$ENDIF}
        JBE      @@2

        {$IFDEF PARANOIA} DB $2C, 32 {$ELSE} SUB AL, 32 {$ENDIF}
        {$IFDEF PARANOIA} DB $3C, 5 {$ELSE} CMP AL, 'F' - 'A' {$ENDIF}
        JA       @@exit
@@2:
        {$IFDEF PARANOIA} DB $04, 0Ah {$ELSE} ADD AL, 0Ah {$ENDIF}
@@3:
        SHL      EDX, 4
        ADD      DL, AL
        JMP      @@0

@@exit: XCHG     EAX, EDX
        POP      ESI
end;

function cHex2Int( const Value : String) : Integer;
asm
     TEST  EAX, EAX
     JZ    @@exit
     CMP   word ptr [EAX], '0x'
     JZ    @@skip_2_chars
     CMP   word ptr [EAX], '0X'
     JNZ   @@2Hex2Int
@@skip_2_chars:
     INC   EAX
     INC   EAX
@@2Hex2Int:
     JMP   Hex2Int
@@exit:
end;

function Int2Str( Value : Integer ) : String;
asm
        XOR       ECX, ECX
        PUSH      ECX
        ADD       ESP, -0Ch

        PUSH      EBX
        LEA       EBX, [ESP + 15 + 4]
        PUSH      EDX
        CMP       EAX, ECX
        PUSHFD
        JGE       @@1
        NEG       EAX
@@1:
        MOV       CL, 10

@@2:
        DEC       EBX
        XOR       EDX, EDX
        DIV       ECX
        ADD       DL, 30h
        MOV       [EBX], DL
        TEST      EAX, EAX
        JNZ       @@2

        POPFD
        JGE       @@3

        DEC       EBX
        MOV       byte ptr [EBX], '-'
@@3:
        POP       EAX
        MOV       EDX, EBX
        CALL      System.@LStrFromPChar

        POP       EBX
        ADD       ESP, 10h
end;

function Int2Ths( I : Integer ) : String;
asm
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     EAX
        PUSH     EDX
        CALL     Int2Str
        POP      EDX
        POP      EAX
        TEST     EAX, EAX
        JGE      @@0
        NEG      EAX
@@0:
        CMP      EAX, 1000
        JL       @@Exit
        PUSH     EDX
        MOV      EAX, [EDX]
        PUSH     EAX
        CALL     System.@LStrLen         // EAX = Length(Result)
        POP      EDX
        PUSH     EDX                     // EDX = @Result[ 1 ]
        XOR      ECX, ECX

@@1:
        ROL      ECX, 8
        DEC      EAX
        MOV      CL, [EDX+EAX]
        JZ       @@fin
        CMP      ECX, 300000h
        JL       @@1

        PUSH     ECX
        XOR      ECX, ECX
        MOV      CL, [ThsSeparator]
        JMP      @@1

@@fin:  CMP      CL, '-'
        JNE      @@fin1
        CMP      CH, [ThsSeparator]
        JNE      @@fin1
        MOV      CH, 0                   // this corrects -,ddd,...
@@fin1: CMP      ECX, 01000000h
        JGE      @@fin2
        INC      EAX
        ROL      ECX, 8
        JMP      @@fin1
@@fin2: PUSH     ECX

        LEA      EDX, [ESP+EAX]
        MOV      EAX, [EBP-4]
        CALL     System.@LStrFromPChar
@@Exit:
        MOV      ESP, EBP
        POP      EBP
end;

function Int2Digs( Value, Digits : Integer ) : String;
asm
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     EDX             // [EBP-4] = Digits
        PUSH     ECX
        MOV      EDX, ECX
        CALL     Int2Str
        POP      ECX
        PUSH     ECX             // [EBP-8] = @Result
        MOV      EAX, [ECX]
        PUSH     EAX
        CALL     System.@LStrLen
        POP      EDX             // EDX = @Result[1]
        MOV      ECX, EAX        // ECX = Length( Result )
        ADD      EAX, EAX
        SUB      ESP, EAX
        MOV      EAX, ESP
        PUSHAD
        CALL     StrCopy
        POPAD
        MOV      EDX, EAX
        ADD      ESP, -100
        CMP      byte ptr [EDX], '-'
        PUSHFD
        JNE      @@1
        INC      EDX
@@1:
        MOV      EAX, [EBP-4]    // EAX = Digits
        CMP      ECX, EAX
        JGE      @@2
        DEC      EDX
        MOV      byte ptr [EDX], '0'
        INC      ECX
        JMP      @@1
@@2:
        POPFD
        JNE      @@3
        DEC      EDX
        MOV      byte ptr [EDX], '-'
@@3:
        MOV      EAX, [EBP-8]
        CALL     System.@LStrFromPChar
        MOV      ESP, EBP
        POP      EBP
end;

function Num2Bytes( Value : Double ) : String;
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        MOV      EBX, ESP
        MOV      ESI, EAX

        MOV      ECX, 4
        MOV      EDX, 'TGMk'
@@1:
        FLD      [Value]
@@10:
        FICOM    dword ptr [@@1024]
        FSTSW    AX
        SAHF
        JB       @@2

        FIDIV    dword ptr [@@1024]
        FST      [Value]
        WAIT

        TEST     DL, 20h
        JE       @@ror
        AND      DL, not 20h
        JMP      @@nxt
@@1024: DD       1024
@@100:  DD       100

@@ror:
        ROR      EDX, 8
@@nxt:
        LOOP     @@10
@@2:
        TEST     DL, 20h
        JZ       @@3
        MOV      DL, 0
@@3:    MOV      DH, 0
        PUSH     DX
        MOV      EDI, ESP

        FLD      ST(0)
        CALL     System.@TRUNC
        {$IFDEF _D2orD3}
        PUSH     0
        {$ELSE}
        PUSH     EDX
        {$ENDIF}
        PUSH     EAX
        FILD     qword ptr [ESP]
        POP      EDX
        POP      EDX

        MOV      EDX, ESI
        CALL     Int2Str

        FSUBP    ST(1), ST
        FIMUL    dword ptr [@@100]
        CALL     System.@TRUNC

        TEST     EAX, EAX
        JZ       @@4

        XOR      ECX, ECX
        MOV      CL, 0Ah
        CDQ
        IDIV     ECX
        TEST     EDX, EDX
        JZ       @@5

        MOV      AH, DL
        SHL      EAX, 16
        ADD      EAX, '00. '
        PUSH     EAX
        MOV      EDI, ESP
        INC      EDI
        JMP      @@4

@@5:    SHL      EAX, 8
        ADD      AX, '0.'
        PUSH     AX
        MOV      EDI, ESP

@@4:
        MOV      EAX, [ESI]
        CALL     System.@LStrLen
        ADD      ESP, -100

        SUB      EDI, EAX
        PUSH     ESI
        PUSH     EDI
        MOV      ESI, [ESI]
        MOV      ECX, EAX
        REP      MOVSB

        POP      EDX
        POP      EAX
        CALL     System.@LStrFromPChar

        MOV      ESP, EBX
        POP      EDI
        POP      ESI
        POP      EBX
end;

function S2Int( S: PChar ): Integer;
asm
        XCHG     EDX, EAX
        XOR      EAX, EAX
        TEST     EDX, EDX
        JZ       @@exit

        XOR      ECX, ECX
        MOV      CL, [EDX]
        INC      EDX
        CMP      CL, '-'
        PUSHFD
        JE       @@0
@@1:    CMP      CL, '+'
        JNE      @@2
@@0:    MOV      CL, [EDX]
        INC      EDX
@@2:    SUB      CL, '0'
        CMP      CL, '9'-'0'
        JA       @@fin
        LEA      EAX, [EAX+EAX*4] //
        LEA      EAX, [ECX+EAX*2] //
        JMP      @@0
@@fin:  POPFD
        JNE      @@exit
        NEG      EAX
@@exit:
end;

function Str2Int(const Value : String) : Integer;
asm
        CALL     EAX2PChar
        CALL     S2Int
end;

{$IFDEF ASM_UNICODE}
function TrimLeft(const S: string): string;
asm
        XCHG     EAX, EDX
        CALL     EDX2PChar
        DEC      EDX
@@1:    INC      EDX
        MOVZX    ECX, byte ptr [EDX]
        JECXZ    @@fin
        CMP      CL, ' '
        JBE      @@1
@@fin:
        CALL     System.@LStrFromPChar
end;

function TrimRight(const S: string): string;
asm
        PUSH     EDX
        PUSH     EAX

        PUSH     EAX
        CALL     System.@LStrLen
        XCHG     EAX, [ESP]
        CALL     EAX2PChar
        POP      ECX
        INC      ECX
@@1:    DEC      ECX
        MOV      DL, [EAX+ECX]
        JL       @@fin
        CMP      DL, ' '
        JBE      @@1
@@fin:
        INC      ECX
        POP      EAX
        XOR      EDX, EDX
        INC      EDX
        CALL     System.@LStrCopy
end;

function Trim( const S : string): string;
asm
        PUSH     EDX
        CALL     TrimRight
        POP      EDX
        MOV      EAX, [EDX]
        CALL     TrimLeft
end;
{$ENDIF ASM_UNICODE}

function LowerCase(const S: string): string;
asm
        PUSH     ESI
        XCHG     EAX, EDX
        PUSH     EAX
        CALL     System.@LStrAsg
        POP      EAX

        CALL     UniqueString

        PUSH     EAX
        CALL     System.@LStrLen
        POP      ESI

        XCHG     ECX, EAX

        JECXZ    @@exit

@@go:
        LODSB
        {$IFDEF PARANOIA} DB $2C, 'A' {$ELSE} SUB AL, 'A' {$ENDIF}
        {$IFDEF PARANOIA} DB $3C, 26 {$ELSE} CMP AL, 'Z'-'A'+1 {$ENDIF}
        JNB      @@1

        ADD      byte ptr [ESI - 1], 20h
@@1:
        LOOP     @@go
@@exit:
        POP      ESI
end;

function UpperCase(const S: string): string;
asm
        PUSH     ESI
        XCHG     EAX, EDX
        PUSH     EAX
        CALL     System.@LStrAsg
        POP      EAX

        CALL     UniqueString

        PUSH     EAX
        CALL     System.@LStrLen
        POP      ESI

        XCHG     ECX, EAX

        JECXZ    @@exit

@@go:
        LODSB
        {$IFDEF PARANOIA} DB $2C, 'a' {$ELSE} SUB AL, 'a' {$ENDIF}
        {$IFDEF PARANOIA} DB $3C, $1A {$ELSE} CMP AL, 'z'-'a'+1 {$ENDIF}
        JNB      @@1

        SUB      byte ptr [ESI - 1], 20h
@@1:
        LOOP     @@go
@@exit:
        POP      ESI
end;

{$IFDEF ASM_UNICODE}
function CopyEnd( const S : String; Idx : Integer ) : String;
asm
        PUSH     ECX
        PUSH     EAX
        PUSH     EDX

        CALL     System.@LStrLen

        POP      EDX
        TEST     EDX, EDX
        JG       @@1
        XOR      EDX, EDX
        INC      EDX
@@1:
        SUB      EAX, EDX
        MOV      ECX, EAX

        POP      EAX
        JGE      @@ret_end

        POP      EAX
        JL       System.@LStrClr

@@ret_end:
        INC      ECX
        CALL     System.@LStrCopy
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
function CopyTail( const S : String; Len : Integer ) : String;
asm
        PUSH     ECX
        PUSH     EAX
          PUSH     EDX
            CALL     System.@LStrLen
          POP      ECX
          CMP      ECX, EAX
          {$IFDEF USE_CMOV}
          CMOVG    ECX, EAX
          {$ELSE}
          JLE      @@1
          MOV      ECX, EAX
@@1:      {$ENDIF}

        MOV      EDX, EAX
        SUB      EDX, ECX
        INC      EDX
        POP      EAX
        CALL     System.@LStrCopy
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
procedure DeleteTail( var S : String; Len : Integer );
asm
        PUSH     EAX
        PUSH     EDX
        MOV      EAX, [EAX]
        CALL     System.@LStrLen
        POP      ECX
        CMP      ECX, EAX
        {$IFDEF USE_CMOV}
        CMOVG    ECX, EAX
        {$ELSE}
        JLE      @@1
        MOV      ECX, EAX
@@1:    {$ENDIF}

        MOV      EDX, EAX
        SUB      EDX, ECX
        INC      EDX
        POP      EAX
        CALL     System.@LStrDelete
end;
{$ENDIF}

function IndexOfChar( const S : String; Chr : Char ) : Integer;
asm
        CALL     EAX2PChar
        PUSH     EAX
        CALL     StrScan
        POP      EDX
        TEST     EAX, EAX
        JE       @@exit__1
        SUB      EAX, EDX
        INC      EAX
        RET
@@exit__1:
        DEC      EAX
end;

function IndexOfCharsMin( const S, Chars : String ) : Integer;
asm
        PUSH     ESI
        PUSH     EAX
        CALL     EDX2PChar
        MOV      ESI, EDX

        XOR      ECX, ECX
        DEC      ECX

@@1:    LODSB
        TEST     AL, AL
        JZ       @@exit

        XCHG     EDX, EAX
        POP      EAX
        PUSH     EAX

        PUSH     ECX
        CALL     IndexOfChar
        POP      ECX
        TEST     EAX, EAX
        JLE      @@1

        TEST     ECX, ECX
        JLE      @@2
        CMP      EAX, ECX
        JGE      @@1
@@2:
@@exit: XCHG     EAX, ECX
          JL     @@1
        POP      ECX
        POP      ESI
end;

function IndexOfStr( const S, Sub : String ) : Integer;
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI

        PUSH     EAX
        MOV      EAX, EDX
        PUSH     EDX
        CALL     System.@LStrLen
        MOV      EDI, EAX
        POP      EAX
        //CALL     System.@LStrToPChar
        CALL     EAX2PChar
        MOV      BL, [EAX]
        XCHG     EAX, [ESP]
        //CALL     System.@LStrToPChar
        CALL     EAX2PChar

        MOV      ESI, EAX

        DEC      EAX
@@1:    INC      EAX
        MOV      DL, BL
        CALL     StrScan
        TEST     EAX, EAX
        JE       @@exit__1

        POP      EDX
        PUSH     EDX

        MOV      ECX, EDI
        PUSH     EAX
        CALL     StrLComp
        POP      EAX
        JNE      @@1

        SUB      EAX, ESI
        INC      EAX
        JMP      @@exit

@@exit__1:
        DEC      EAX
@@exit:
        POP      EDX
        POP      EDI
        POP      ESI
        POP      EBX
end;

function AllocMem( Size : Integer ) : Pointer;
asm     //cmd    //opd
        TEST     EAX, EAX
        JZ       @@exit
        PUSH     EAX
        CALL     System.@GetMem
        POP      EDX
        PUSH     EAX
        MOV      CL, 0
        CALL     System.@FillChar
        POP      EAX
@@exit:
end;

function StrPCopy(Dest: PChar; const Source: string): PChar;
asm
        PUSH     EAX
        MOV      EAX, EDX
        CALL     System.@LStrLen
        MOV      ECX, EAX
        POP      EAX
        CALL     EDX2PChar
        CALL     StrLCopy
end;

function StrEq( const S1, S2 : String ) : Boolean;
asm
        TEST     EDX, EDX
        JNZ      @@1
@@0:    CMP      EAX, EDX
        JMP      @@exit
@@1:    TEST     EAX, EAX
        JZ       @@0
        MOV      ECX, [EAX-4]
        CMP      ECX, [EDX-4]
        JNE      @@exit
        PUSH     EAX
        PUSH     EDX
        PUSH     0
        MOV      EDX, ESP
        CALL     LowerCase
        PUSH     0
        MOV      EAX, [ESP + 8]
        MOV      EDX, ESP
        CALL     LowerCase
        POP      EAX
        POP      EDX
        PUSH     EDX
        PUSH     EAX
        CALL     System.@LStrCmp
        MOV      EAX, ESP
        PUSHFD
        XOR      EDX, EDX
        MOV      DL, 2
        CALL     System.@LStrArrayClr
        POPFD
        POP      EDX
        POP      EDX
        POP      EDX
        POP      EDX
@@exit:
        SETZ     AL
end;

function AnsiEq( const S1, S2 : String ) : Boolean;
asm
        CALL     AnsiCompareStrNoCase
        TEST     EAX, EAX
        SETZ     AL
end;

function StrIn(const S: String; const A: array of String): Boolean;
asm
@@1:
        TEST     ECX, ECX
        JL       @@ret_0

        PUSH     EDX
        MOV      EDX, [EDX+ECX*4]
        DEC      ECX

        PUSH     ECX
        PUSH     EAX
        CALL     StrEq
        DEC      AL
        POP      EAX
        POP      ECX

        POP      EDX
        JNZ      @@1

        MOV      AL, 1
        RET

@@ret_0:XOR      EAX, EAX
end;

{$IFDEF ASM_UNICODE}
function _StrSatisfy( S, Mask : PKOLChar ) : Boolean;
asm
    TEST EAX, EAX
    JZ   @@exit
        XCHG     ECX, EAX
        //       EDX <- Mask
        //       ECX <- S
        XOR      EAX, EAX
        MOV      AL, '*'
@@rest_satisfy:
        PUSH     ECX
        PUSH     EDX

@@nx_char:
        MOV      AH, [EDX]
        OR       AH, [ECX]
        JZ       @@fin //@@ret_true

        MOV      AH, 0

        CMP      word ptr [EDX], AX //'*'
        JE       @@fin //@@ret_true

        CMP      byte ptr [ECX], AH
        JNE      @@10

        DEC      EDX
@@1:
        INC      EDX
        CMP      byte ptr [EDX], AL //'*'
        JE       @@1

        CMP      byte ptr [EDX], AH
        SETZ     AL
        JMP      @@fin

@@10:   CMP      byte ptr [EDX], AH
        JE       @@ret_false

        CMP      byte ptr [EDX], '?'
        JNE      @@11

@@go_nx_char:
        INC      ECX
        INC      EDX
        JMP      @@nx_char

@@11:
        CMP      byte ptr [EDX], AL //'*'
        JNE      @@20

        INC      EDX
@@12:   CMP      byte ptr [ECX], AH
        JE       @@ret_false

        CALL     @@rest_satisfy
        TEST     AL, AL
        JNE      @@fin
        MOV      AL, '*'

        INC      ECX
        JMP      @@12

@@20:   MOV      AH, [EDX]
        XOR      AH, [ECX]

        JE       @@go_nx_char
@@ret_false:
        XOR      EAX, EAX

@@fin:
        POP      EDX
        POP      ECX
@@exit:
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
function StrSatisfy( const S, Mask: String ): Boolean;
asm
        PUSH     ESI
        XCHG     ESI, EAX
        PUSH     0
        XCHG     EAX, EDX
        CALL     EAX2PChar
        MOV      EDX, ESP

        CMP      byte ptr [EAX], 0
        JZ       @@0
        CALL     AnsiLowerCase
@@0:
        XCHG     EAX, ESI
        PUSH     0
        CALL     EAX2PChar
        MOV      EDX, ESP

        CMP      byte ptr [EAX], 0
        JZ       @@1
        CALL     AnsiLowerCase
@@1:
        POP      EAX
        POP      EDX
        PUSH     EDX
        PUSH     EAX
        CALL     _StrSatisfy

        XCHG     ESI, EAX

        CALL     RemoveStr
        CALL     RemoveStr
        XCHG     EAX, ESI

        POP      ESI
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
function _2StrSatisfy( S, Mask: PChar ): Boolean;
asm     //     //
        PUSH   EBX
        XCHG   EBX, EAX
        PUSH   0
        MOV    EAX, ESP
        CALL   System.@LStrFromPChar
        PUSH   0
        MOV    EAX, ESP
        MOV    EDX, EBX
        CALL   System.@LStrFromPChar
        POP    EAX
        POP    EDX
        PUSH   EDX
        PUSH   EAX
        CALL   StrSatisfy
        XCHG   EBX, EAX
        CALL   RemoveStr
        CALL   RemoveStr
        XCHG   EAX, EBX
        POP    EBX
end;
{$ENDIF}

procedure NormalizeUnixText( var S: String );
asm     //cmd    //opd
        CMP      dword ptr [EAX], 0
        JZ       @@exit
        PUSH     EBX
        PUSH     EDI
        MOV      EBX, EAX
        CALL     UniqueString
        MOV      EDI, [EBX]
@@1:    MOV      EAX, EDI
        CALL     System.@LStrLen
        XCHG     ECX, EAX
        MOV      AX, $0D0A

        CMP      byte ptr [EDI], AL
        JNE      @@loo
        MOV      byte ptr [EDI], AH
@@loo:
        TEST     ECX, ECX
        JZ       @@fin
@@loo1:
        REPNZ SCASB
        JNZ      @@fin
        CMP      byte ptr [EDI-2], AH
        JE       @@loo
        MOV      byte ptr [EDI-1], AH
        JNE      @@loo1
@@fin:  POP      EDI
        POP      EBX
@@exit:
end;

{$IFDEF ASM_UNICODE}
function __DelimiterLast( Str: PChar; Delimiters: PChar ): PChar;
asm
        PUSH     ESI

        CALL     EAX2PChar

        MOV      ESI, EDX
        MOV      EDX, EAX

@@tolast:
        CMP      byte ptr [EAX], 0
        JZ       @@next1
        INC      EAX
        JMP      @@tolast

@@next1:
        PUSH     EAX

@@next:
        LODSB
        TEST     AL, AL
        JZ       @@exit

        PUSH     EDX
        XCHG     EDX, EAX
        CALL     StrRScan
        POP      EDX

        TEST     EAX, EAX
        JZ       @@next

        POP      ECX
        CMP      byte ptr [ECX], 0
        JZ       @@next1

        CMP      EAX, ECX
        JG       @@next1

        PUSH     ECX
        JLE      @@next

@@exit: POP      EAX
        POP      ESI
end;

function DelimiterLast( const Str, Delimiters: String ): Integer;
asm
        CALL     EAX2PChar
        CALL     EDX2PChar
        PUSH     EAX
        CALL     __DelimiterLast
        POP      EDX
        SUB      EAX, EDX
        INC      EAX
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
function Format( const fmt: KOLString; params: array of const ): String;
asm
        PUSH    ESI
        PUSH    EDI
        PUSH    EBX
        MOV     EBX, ESP
        ADD     ESP, -2048
        MOV     ESI, ESP

        INC     ECX
        JZ      @@2
@@1:
        MOV     EDI, [EDX + ECX*8 - 8]
        PUSH    EDI
        LOOP    @@1
@@2:
        PUSH    ESP
        PUSH    EAX
        PUSH    ESI

        CALL    wvsprintf

        MOV     EDX, ESI
        MOV     EAX, @Result
        CALL    System.@LStrFromPChar

        MOV     ESP, EBX
        POP     EBX
        POP     EDI
        POP     ESI
end;
{$ENDIF ASM_UNICODE}

function FileCreate( const FileName: KOLString; OpenFlags: DWord): THandle;
asm
        XOR      ECX, ECX
        PUSH     ECX
        MOV      ECX, EDX
        SHR      ECX, 16
        AND      CX, $1FFF
        JNZ      @@1
        MOV      CL, FILE_ATTRIBUTE_NORMAL
@@1:    PUSH     ECX
        MOV      CL, DH
        PUSH     ECX                  // CreationMode
        PUSH     0
        MOV      CL, DL
        PUSH     ECX                  // ShareMode
        MOV      DX, 0
        PUSH     EDX                  // AccessMode
        //CALL     System.@LStrToPChar // FileName must not be ''
        PUSH     EAX
        CALL     CreateFile
end;

function FileClose( Handle: THandle): Boolean;
asm
        PUSH     EAX
        CALL     CloseHandle
        TEST     EAX, EAX
        SETNZ    AL
end;

{$IFNDEF FILE_EXISTS_EX}
{$IFDEF ASM_UNICODE}
function FileExists( const FileName : KOLString ) : Boolean;
const size_TWin32FindData = sizeof( {$IFDEF UNICODE_CTRLS} TWin32FindDataW {$ELSE} TWin32FindDataA {$ENDIF} );
asm
        CALL     EAX2PChar
        PUSH     EAX
        CALL     GetFileAttributes
        INC      EAX
        JZ       @@exit
        DEC      EAX
        {$IFDEF PARANOIA} DB $24, FILE_ATTRIBUTE_DIRECTORY {$ELSE} AND AL, FILE_ATTRIBUTE_DIRECTORY {$ENDIF}
        SETZ     AL
@@exit:
end;
{$ENDIF ASM_UNICODE}
{$ENDIF FILE_EXISTS_EX}

function FileSeek( Handle: THandle; MoveTo: integer; MoveMethod: TMoveMethod): DWord;
asm
        MOVZX    ECX, CL
        PUSH     ECX
        PUSH     0
        PUSH     EDX
        PUSH     EAX
        CALL     SetFilePointer
end;

function FileRead( Handle: THandle; var Buffer; Count: DWord): DWord;
asm
        PUSH     EBP
        PUSH     0
        MOV      EBP, ESP
        PUSH     0
        PUSH     EBP
        PUSH     ECX
        PUSH     EDX
        PUSH     EAX
        CALL     ReadFile
        TEST     EAX, EAX
        POP      EAX
        JNZ      @@exit
        XOR      EAX, EAX
@@exit:
        POP      EBP
end;

function File2Str( Handle: THandle): String;
asm
        PUSH     EDX
        TEST     EAX, EAX
        JZ       @@exit // return ''

        PUSH     EBX
        MOV      EBX, EAX // EBX = Handle
        XOR      EDX, EDX
        XOR      ECX, ECX
        INC      ECX
        CALL     FileSeek
        PUSH     EAX // Pos
        PUSH     0
        PUSH     EBX
        CALL     GetFileSize
        POP      EDX
        SUB      EAX, EDX // EAX = Size - Pos
        JZ       @@exitEBX

        PUSH     EAX
        CALL     System.@GetMem
        XCHG     EAX, EBX
        MOV      EDX, EBX
        POP      ECX
        PUSH     ECX
        CALL     FileRead
        POP      ECX
        MOV      EDX, EBX
        POP      EBX
        POP      EAX
        PUSH     EDX
        {$IFDEF _D2}
        CALL     _LStrFromPCharLen
        {$ELSE}
        CALL     System.@LStrFromPCharLen
        {$ENDIF}
        JMP      @@freebuf

@@exitEBX:
        POP      EBX
@@exit:
        XCHG     EDX, EAX
        POP      EAX // @Result
        PUSH     EDX
        CALL     System.@LStrFromPChar
@@freebuf:
        POP      EAX
        TEST     EAX, EAX
        JZ       @@fin
        CALL     System.@FreeMem
@@fin:
end;

function FileWrite( Handle: THandle; const Buffer; Count: DWord): DWord;
asm
        PUSH     EBP
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     0
        PUSH     EBP
        PUSH     ECX
        PUSH     EDX
        PUSH     EAX
        CALL     WriteFile
        TEST     EAX, EAX
        POP      EAX
        JNZ      @@exit
        XOR      EAX, EAX
@@exit:
        POP      EBP
end;

function FileEOF( Handle: THandle ) : Boolean;
asm
        PUSH     EAX

        PUSH     0
        PUSH     EAX
        CALL     GetFileSize

        XCHG     EAX, [ESP]

        MOV      CL, spCurrent
        XOR      EDX, EDX
        CALL     FileSeek

        POP      EDX
        CMP      EAX, EDX
        SETGE    AL
end;

function CompareSystemTime( const D1, D2 : TSystemTime) : Integer; assembler;
asm
        PUSH     ESI
        PUSH     EBX
        MOV      ESI, EAX
        XOR      EAX, EAX
        XOR      ECX, ECX
        MOV      CL, 8  // 8 words: wYear, wMonth,..., wMilliseconds
@@loo:
        LODSW
        MOV      BX, [EDX]
        INC      EDX
        INC      EDX

        CMP      CL, 6
        JE       @@cont  // skip compare DayOfWeek

        SUB      AX, BX
        JNE      @@calc

@@cont:
        LOOP     @@loo
        JMP      @@exit

@@calc:
        SBB      EAX, EAX
        {$IFDEF PARANOIA} DB $0C, 1 {$ELSE} OR AL, 1 {$ENDIF}

@@exit:
        POP      EBX
        POP      ESI
end;

function DirectoryExists( const Name: KOLString): Boolean;
asm
   PUSH EBX
        //CALL     System.@LStrToPChar // Name must not be ''
        PUSH     EAX
   PUSH SEM_NOOPENFILEERRORBOX or SEM_FAILCRITICALERRORS
   CALL SetErrorMode
   XCHG EBX, EAX
        CALL     GetFileAttributes
        INC      EAX
        JZ       @@exit
        DEC      EAX
        {$IFDEF PARANOIA} DB $24, FILE_ATTRIBUTE_DIRECTORY {$ELSE} AND AL, FILE_ATTRIBUTE_DIRECTORY {$ENDIF}
        SETNZ    AL
@@exit:
   XCHG EAX, EBX
   PUSH EAX
   CALL SetErrorMode
   XCHG EAX, EBX
   POP  EBX
end;

{$IFDEF ASM_UNICODE}
function ExtractFileName( const Path : String ) : String;
asm
        PUSH     EDX
        PUSH     EAX
        MOV      EDX, [DirDelimiters]
        CALL     __DelimiterLast
        POP      EDX
        CMP      byte ptr [EAX], 0
        JZ       @@1
        XCHG     EDX, EAX
        INC      EDX
@@1:    POP      EAX
        CALL     System.@LStrFromPChar
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
function GetStartDir : String;
asm
        PUSH     EBX
        MOV      EBX, EAX

        XOR      EAX, EAX
        MOV      AH, 2
        SUB      ESP, EAX
        MOV      EDX, ESP
        PUSH     EAX
        PUSH     EDX
        PUSH     0
        CALL     GetModuleFileName

        LEA      EDX, [ESP + EAX]
@@1:    DEC      EDX
        CMP      byte ptr [EDX], '\'
        JNZ      @@1

        INC      EDX
        MOV      byte ptr [EDX], 0

        MOV      EAX, EBX
        MOV      EDX, ESP
        CALL     System.@LStrFromPChar

        ADD      ESP, 200h
        POP      EBX
end;
{$ENDIF}

procedure TDirList.Clear;
asm
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fList
        JECXZ    @@exit
        XCHG     EAX, ECX
        CALL     TList.Release
@@exit:
end;

destructor TDirList.Destroy;
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     Clear
        LEA      EAX, [EBX].FPath
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        XCHG     EAX, EBX
        CALL     TObj.Destroy
        POP      EBX
end;

{$IFDEF ASM_UNICODE}
function FindFilter( const Filter: String): String;
asm
        XCHG     EAX, EDX
        PUSH     EAX
        CALL     System.@LStrAsg
        POP      EAX
        CMP      dword ptr [EAX], 0
        JNE      @@exit
        LEA      EDX, @@mask_all
        JE       System.@LStrFromPChar
@@mask_all:  DB  '*.*',0
@@exit:
end;
{$ENDIF ASM_UNICODE}

function TDirList.GetCount: Integer;
asm
        MOV      EAX, [EAX].fList
        TEST     EAX, EAX
        {$IFDEF USE_CMOV}
        CMOVNZ   EAX, [EAX].TList.fCount
        {$ELSE}
        JZ       @@exit
        MOV      EAX, [EAX].TList.fCount
@@exit: {$ENDIF}
end;

{$IFDEF ASM_UNICODE}
function TDirList.GetNames(Idx: Integer): string;
asm
        MOV      EAX, [EAX].fList
        MOV      EAX, [EAX].TList.fItems
        MOV      EDX, [EAX + EDX*4]
        ADD      EDX, offset TWin32FindData.cFileName //
        MOV      EAX, ECX
        CALL     System.@LStrFromPChar
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
procedure TDirList.ScanDirectoryEx(const DirPath, Filters: String;
  Attr: DWord);
asm
        PUSH     EBX
        MOV      EBX, EAX

        PUSHAD
        LEA      EAX, [EBX].fFilters
        CALL     Free_And_Nil

        CALL     NewStrList
        MOV      [EBX].fFilters, EAX
        POPAD

        PUSHAD
        PUSH     0
        MOV      EAX, ESP
        MOV      EDX, ECX
        CALL     System.@LStrLAsg
@@1:    MOV      ECX, [ESP]
        JECXZ    @@2
        MOV      EAX, ESP
        MOV      EDX, offset[@@semicolon]
        PUSH     0
        MOV      ECX, ESP
        CALL     Parse
        MOV      EAX, [ESP]
        MOV      EDX, ESP
        CALL     Trim
        POP      EDX
        PUSH     EDX
        TEST     EDX, EDX
        JZ       @@filt_added
        MOV      EAX, [EBX].fFilters
        CALL     TStrList.Add
@@filt_added:
        CALL     RemoveStr
        JMP      @@1

        //       ';' string literal
        DD       -1, 1
@@semicolon:
        DB       ';',0

@@2:    POP      ECX
        POPAD
        XOR      ECX, ECX
        PUSH     [Attr]
        CALL     ScanDirectory
        POP      EBX
@@exit:
end;
{$ENDIF ASM_UNICODE}

procedure SwapDirItems( const Data : PSortDirData; const e1, e2 : DWORD );
asm
        MOV      EAX, [EAX].TSortDirData.Dir
        MOV      EAX, [EAX].TDirList.fList
        MOV      EAX, [EAX].TList.fItems
        LEA      EDX, [EAX+EDX*4]
        LEA      ECX, [EAX+ECX*4]
        MOV      EAX, [EDX]
        XCHG     EAX, [ECX]
        MOV      [EDX], EAX
end;

procedure TDirList.Sort(Rules: array of TSortDirRules);
const   high_DefSortDirRules = High( DefSortDirRules );
asm
        PUSH     EBX
        PUSH     ESI
        XOR      EBX,EBX
        CMP      [EAX].fList, EBX
        JE       @@exit

        PUSH     EAX           // prepare Dir = @Self
        XOR      EAX, EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        MOV      ESI, ESP
        INC      ECX           // ECX = High(Rules)
        JZ       @@2
@@1:    MOV      AH, [EDX]     // AH = Rules[ I ]
        INC      EDX
        CALL     @@add_rule
        LOOP     @@1
@@2:    LEA      EDX, [DefSortDirRules]
        MOV      CL, high_DefSortDirRules + 1
@@21:   MOV      AH, [EDX]
        INC      EDX
        CALL     @@add_rule
        LOOP     @@21

        PUSH     BX           // prepare FoldersFirst(BL), CaseSensitive(BH)
        MOV      EBX, [ESP].TSortDirData.Dir
        MOV      EAX, ESP
        PUSH     offset[SwapDirItems]
        MOV      ECX, offset[CompareDirItems]
        MOV      EDX, [EBX].fList
        MOV      EDX, [EDX].TList.fCount
        CALL     SortData

        ADD      ESP, 18
        JMP      @@exit

@@add_rule:
        PUSH     ESI
        PUSH     ECX
        MOV      CL, 11
@@a1:   LODSB
        TEST     AL, AL
        JZ       @@a2
        CMP      AL, AH
        JE       @@a3
        LOOP     @@a1
@@a2:   DEC      ESI
        MOV      [ESI], AH
        CMP      AH, sdrFoldersFirst
        JNE      @@a4
        INC      BL
@@a4:   CMP      AH, sdrCaseSensitive
        JNE      @@a3
        INC      BH
@@a3:   POP      ECX
        POP      ESI
        RET

@@exit:
        POP      ESI
        POP      EBX
end;

destructor TThread.Destroy;
asm
        PUSH     EBX
        MOV      EBX, EAX
      CALL RefInc
        MOV      EAX, EBX
        CMP      [EBX].FTerminated, 0
        JNZ      @@1
        CALL     Terminate
        MOV      EAX, EBX
        CALL     WaitFor
@@1:    MOV      ECX, [EBX].FHandle
        JECXZ    @@2
        PUSH     ECX
        CALL     CloseHandle
@@2:    POP      EAX
        XCHG     EBX, EAX
        JMP      TObj.Destroy
end;

function TStream.GetSize: DWord;
asm
        CALL     [EAX].fMethods.fGetSiz
end;

procedure TStream.SetSize(NewSize: DWord);
asm
        CALL     [EAX].fMethods.fSetSiz
end;

function TStream.Read(var Buffer; Count: DWord): DWord;
asm
        CALL     [EAX].fMethods.fRead
end;

function TStream.Write(var Buffer; Count: DWord): DWord;
asm
        CALL     [EAX].fMethods.fWrite
end;

function TStream.Seek(MoveTo: integer; MoveMethod: TMoveMethod): DWord;
asm
        CALL     [EAX].fMethods.fSeek
end;

destructor TStream.Destroy;
asm
        PUSH     EAX
        PUSH     [EAX].fData.fThread
        CALL     [EAX].fMethods.fClose
        POP      EAX
        CALL     TObj.RefDec
        POP      EAX
        CALL     TObj.Destroy
end;

function WriteFileStreamEOF( Strm: PStream; var Buffer; Count: DWORD ): DWORD;
asm
        PUSH     EBX
        PUSH     [EAX].TStream.fData.fHandle
        CALL     WriteFileStream
        XCHG     EBX, EAX
        CALL     SetEndOfFile
        XCHG     EAX, EBX
        POP      EBX
end;

function SeekMemStream( Strm: PStream; MoveTo: Integer; MoveFrom: TMoveMethod ): DWORD;
asm
        PUSH     EBX
        MOV      EBX, EDX
        AND      ECX, $FF
        LOOP     @@not_from_cur
        ADD      EBX, [EAX].TStream.fData.fPosition
@@not_from_cur:
        LOOP     @@not_from_end
        ADD      EBX, [EAX].TStream.fData.fSize
@@not_from_end:
        CMP      EBX, [EAX].TStream.fData.fSize
        JLE      @@space_ok
        PUSH     EAX
        MOV      EDX, EBX
        CALL     TStream.SetSize
        POP      EAX
@@space_ok:
        XCHG     EAX, EBX
        MOV      [EBX].TStream.fData.fPosition, EAX
        POP      EBX
end;

procedure SetSizeMemStream( Strm: PStream; NewSize: DWORD );
asm
        push     ebx
        push     edx
        xchg     ebx, eax
        cmp      [ebx].TStream.fData.fCapacity, edx
        jae      @@mem_ok
        {$IFDEF OLD_MEMSTREAMS_SETSIZE}
        or       edx, [CapacityMask]
        inc      edx
        {$ENDIF}
        mov      [ebx].TStream.fData.fCapacity, edx
        mov      ecx, [ebx].TStream.fMemory
        jecxz    @@getmem
        lea      eax, [ebx].TStream.fMemory
        call     System.@ReallocMem
        jmp      @@setmem

@@getmem:
        or       ecx, edx
        jz       @@mem_ok
        xchg     eax, ecx
        call     System.@GetMem
@@setmem:
        mov      [ebx].TStream.fMemory, eax

@@mem_ok:
        pop      ecx // NewSize
        inc      ecx
        loop     @@set_new_sz

        xor      eax, eax
        mov      [ebx].TStream.fData.fCapacity, eax
        xchg     eax, [ebx].TStream.fMemory
        call     System.@FreeMem

        xor      ecx, ecx

@@set_new_sz:
        mov      [ebx].TStream.fData.fSize, ecx
        cmp      [ebx].TStream.fData.fPosition, ecx
        jb       @@exit
        mov      [ebx].TStream.fData.fPosition, ecx

@@exit:
        pop      ebx
end;

function ReadMemStream( Strm: PStream; var Buffer; Count: DWORD ): DWORD;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TStream.fData.fPosition
        ADD      EAX, ECX
        CMP      EAX, [EBX].TStream.fData.fSize
        JLE      @@count_ok
        MOV      ECX, [EBX].TStream.fData.fSize
        SUB      ECX, [EBX].TStream.fData.fPosition
@@count_ok:
        PUSH     ECX
        MOV      EAX, [EBX].TStream.fMemory
        ADD      EAX, [EBX].TStream.fData.fPosition
        CALL     System.Move
        POP      EAX
        ADD      [EBX].TStream.fData.fPosition, EAX
        POP      EBX
end;

function WriteMemStream( Strm: PStream; var Buffer; Count: DWORD ): DWORD;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TStream.fData.fPosition
        ADD      EAX, ECX
        CMP      EAX, [EBX].TStream.fData.fSize
        PUSH     EDX
        PUSH     ECX
        JLE      @@count_ok
        XCHG     EDX, EAX
        MOV      EAX, EBX
        CALL     TStream.SetSize
@@count_ok:
        POP      ECX
        POP      EAX
        MOV      EDX, [EBX].TStream.fMemory
        ADD      EDX, [EBX].TStream.fData.fPosition
        PUSH     ECX
        CALL     System.Move
        POP      EAX
        ADD      [EBX].TStream.fData.fPosition, EAX
        POP      EBX
end;

procedure CloseMemStream( Strm: PStream );
asm
        MOV      ECX, [EAX].TStream.fMemory
        JECXZ    @@exit
        XCHG     EAX, ECX
        CALL     System.@FreeMem
@@exit:
end;

function NewReadFileStream( const FileName: KOLString ): PStream;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, offset[BaseFileMethods]
        CALL     _NewStream
        MOV      EDX, [ReadFileStreamProc]
        MOV      [EAX].TStream.fMethods.fRead, EDX
        XCHG     EBX, EAX
        MOV      EDX, ofOpenRead or ofOpenExisting or ofShareDenyWrite
        CALL     FileCreate
        MOV      [EBX].TStream.fData.fHandle, EAX
        XCHG     EAX, EBX
        POP      EBX
end;

function NewWriteFileStream( const FileName: KOLString ): PStream;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, offset[BaseFileMethods]
        CALL     _NewStream
        MOV      [EAX].TStream.fMethods.fWrite, offset[WriteFileStreamEOF]
        MOV      [EAX].TStream.fMethods.fSetSiz, offset[SetSizeFileStream]
        XCHG     EBX, EAX
        MOV      EDX, ofOpenWrite or ofCreateAlways or ofShareDenyWrite
        CALL     FileCreate
        MOV      [EBX].TStream.fData.fHandle, EAX
        XCHG     EAX, EBX
        POP      EBX
end;

function WriteExMemoryStream( Strm: PStream; var Buffer; Count: DWORD ): DWORD;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TStream.fData.fSize
        SUB      EAX, [EBX].TStream.fData.fPosition
        CMP      EAX, ECX
        JGE      @@1
        XCHG     ECX, EAX
@@1:
        PUSH     EDX
        PUSH     ECX
        JLE      @@count_ok
        XCHG     EDX, EAX
        MOV      EAX, EBX
        CALL     TStream.SetSize
@@count_ok:
        POP      ECX
        POP      EAX
        MOV      EDX, [EBX].TStream.fMemory
        ADD      EDX, [EBX].TStream.fData.fPosition
        PUSH     ECX
        CALL     System.Move
        POP      EAX
        ADD      [EBX].TStream.fData.fPosition, EAX
        POP      EBX
end;

{$IFDEF ASM_UNICODE}
function Resource2Stream( DestStrm : PStream; Inst : HInst;
                          ResName : PChar; ResType : PChar ): Integer;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EDX // EBX = Inst
        PUSH     EAX      // DestStrm
        PUSH     ResType
        PUSH     ECX
        PUSH     EDX
        CALL     FindResource
        TEST     EAX, EAX
        JZ       @@exit0

        PUSH     EAX
        PUSH     EBX
        PUSH     EAX
        PUSH     EBX
        CALL     SizeofResource
        XCHG     EBX, EAX
        CALL     LoadResource
        TEST     EAX, EAX
        JZ       @@exit0
        XCHG     ESI, EAX

        PUSH     ESI
        CALL     GlobalLock
        TEST     EAX, EAX
        JNZ      @@P_ok

        CALL     GetLastError
        CMP      EAX, ERROR_INVALID_HANDLE
        JNZ      @@exit_00
        MOV      EAX, ESI

@@P_ok:
        XCHG     EDX, EAX
        POP      EAX // DestStrm
        PUSH     EDX
        MOV      ECX, EBX
        CALL     TStream.Write

        //EAX = Result (length of written data)
        XCHG     EBX, EAX
        POP      EAX
        CMP      ESI, EAX
        JE       @@not_unlock

        PUSH     ESI
        CALL     GlobalUnlock
@@not_unlock:
        XCHG     EAX, EBX
        JMP      @@exit

@@exit_00:
        XOR      EAX, EAX
@@exit0:
        POP      ECX
@@exit:
        POP      ESI
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

destructor TIniFile.Destroy;
asm     //cmd    //opd
        PUSH     EAX
        LEA      EDX, [EAX].fFileName
        PUSH     EDX
        LEA      EAX, [EAX].fSection
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        POP      EAX
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        POP      EAX
        CALL     TObj.Destroy
end;

procedure _FillStrList;    // Эта часть кода общая для двух следующих процедур
asm
///////////////////////////////
        OR      EAX,0
        JE      @@EXIT                  //ERROR
//        LEA     EAX,[EAX-IniBufferSize]
//        JE      @@EXIT
//      возможна нехватка Буфера... в принципе не ошибка :)
//      возвращаем что влезло...
//////////////////////////////
@@LOOP:
        LEA     EAX,[ESI+4]
        CALL    StrLen
        MOV     [ESI],EAX
        LEA     EDX,[ESI+4]
        INC     EAX
        ADD     ESI,EAX

        MOV     EAX,EDI

        CALL    TStrList.ADD

        CMP     byte ptr [ESI+4],0
        JNE     @@LOOP

@@EXIT:
        POP     EAX
        CALL    System.@FreeMem


        POP     ECX
        POP     EBX
        POP     EDI
        POP     ESI
end;

//[procedure TIniFile.GetSectionNames]
{$IFDEF ASM_UNICODE}
procedure TIniFile.GetSectionNames(Names: PStrList);
asm
        PUSH    ESI
        PUSH    EDI
        PUSH    EBX
        PUSH    ECX

        MOV     EBX,EAX
        MOV     EAX, IniBufferStrSize
        MOV     EDI,EDX

        CALL    System.@GetMem
        MOV     ESI,EAX
        PUSH    EAX

        PUSH    [EBX].fFileName
        MOV     EAX,IniBufferSize
        PUSH    EAX

        LEA     EAX,[ESI+4]
        PUSH    EAX

        CALL    GetPrivateProfileSectionNames
        JMP     _FillStrList
end;
{$ENDIF ASM_UNICODE}

//[procedure TIniFile.SectionData]
{$IFDEF ASM_UNICODE}
procedure TIniFile.SectionData(Names: PStrList);
asm
        PUSH    ESI
        PUSH    EDI
        PUSH    EBX
        PUSH    ECX

        MOV     EBX,EAX
        MOV     EAX, IniBufferStrSize
        MOV     EDI,EDX

        CALL    System.@GetMem
        MOV     ESI,EAX
        PUSH    EAX

        OR     [EBX].fMode,0
        JNE     @@DOWrite

        PUSH    [EBX].fFileName
        MOV     EAX,IniBufferSize
        PUSH    EAX

        LEA     EAX,[ESI+4]
        PUSH    EAX
        PUSH    [EBX].fSection

        CALL    GetPrivateProfileSection
        JMP     _FillStrList

@@DOWrite:

        PUSH    EBX
        PUSH    ESI
        PUSH    EDX
        PUSH    EBP

        MOV     EDX,0
        MOV     EBP,[EDI].TStrList.fCount
        MOV     EBX,IniBufferSize-2 // оставим место для #0#0

{ECM+++>} OR      EBP,EBP  // otherwise GetPChars when StrList.Count = 0 crashed

@@LOOP:
        JE      @@ENDLOOP

        OR      EBX,EBX
        JE      @@ENDLOOP

        PUSH    EDX
        MOV     EAX,EDI
        CALL    TStrList.GetPChars

        PUSH    EAX
        CALL    StrLen
        POP     EAX

        XOR     ECX,-1
        MOV     EDX,ESI

        SUB     EBX,ECX
        JA      @@L1
        ADD     ECX,EBX
        XOR     EBX,EBX
@@L1:

        ADD     ESI,ECX

        CALL    MOVE
@@L2:
        POP     EDX
        INC     EDX
        DEC     EBP
        JMP     @@LOOP
@@ENDLOOP:
        MOV     WORD PTR [ESI],0

        POP     EBP
        POP     EDX
        POP     ESI
        POP     EBX
///////////////////////////////////
        MOV     EAX,EBX                 // нодо очищать
        CALL    ClearSection
//////////////////////////////////

        PUSH    [EBX].fFileName
        PUSH    ESI
        PUSH    [EBX].fSection

        CALL    WritePrivateProfileSection

        POP     EAX
        CALL    System.@FreeMem

        POP     ECX
        POP     EBX
        POP     EDI
        POP     ESI

end;
{$ENDIF ASM_UNICODE}

function MakeAccelerator( fVirt: Byte; Key: Word ): TMenuAccelerator;
asm
        MOVZX    EAX, AL
        PUSH     EAX
        MOV      [ESP+1], DX
        POP      EAX
end;

function _NewTControl( AParent: PControl ): PControl;
begin
  New( Result, CreateParented( AParent ) );
end;
//[END _NewTControl]

//[function _NewWindowed]
function _NewWindowed( AParent: PControl; ControlClassName: PKOLChar; Ctl3D: Boolean ): PControl;
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI

        PUSH     ECX // Ctl3D
        PUSH     EDX // ControlClassName

        MOV      ESI, EAX // ESI = AParent
        CALL     _NewTControl
        XCHG     EBX, EAX // EBX = Result
        POP      [EBX].TControl.fControlClassName
        //INC      [EBX].TControl.fWindowed // incremented in TControl.Init

        POP      EDX // DL = parameter Ctl3D
        TEST     ESI, ESI
        JZ       @@no_parent

        LEA      ESI, [ESI].TControl.fWndProcResizeFlicks
        LEA      EDI, [EBX].TControl.fWndProcResizeFlicks
        MOVSD    // fWndProcResizeFlicks
        MOVSD    // fGotoControl
        LODSB    // fCtl3Dchild
        STOSB
        DEC      AL
        LODSB    // fCtl3D
        JZ       @@passed3D
        XOR      EDX, EDX
@@passed3D:
        XCHG     EAX, EDX
        STOSB    // fCtl3D

        MOVSD    // fTextColor
        MOVSD    // fColor

        {$IFDEF SMALLEST_CODE}
        {$IFDEF SMALLEST_CODE_PARENTFONT}
        LODSD
        XCHG     EDX, EAX
        XOR      EAX, EAX
        CALL     TGraphicTool.Assign
        STOSD    // fFont
        {$ELSE}
        LODSD
        XOR     EAX, EAX
        STOSD   // fFont = nil
        {$ENDIF}
        {$ELSE}
        LODSD
        XCHG     EDX, EAX
        XOR      EAX, EAX
        PUSH     EDX
        CALL     TGraphicTool.Assign
        STOSD    // fFont
        POP      EDX
        XCHG     ECX, EAX
        JECXZ    @@no_font
        MOV      [ECX].TGraphicTool.fParentGDITool, EDX
        MOV      [ECX].TGraphicTool.fOnChange.TMethod.Code, offset[TControl.FontChanged]
        MOV      [ECX].TGraphicTool.fOnChange.TMethod.Data, EBX
        MOV      EAX, EBX
        MOV      EDX, ECX
        CALL     TControl.FontChanged
        {$IFDEF USE_AUTOFREE4CONTROLS}
        MOV      EAX, EBX
        MOV      EDX, [EBX].TControl.fFont
        CALL     TControl.Add2AutoFree
        {$ENDIF}
@@no_font:
        {$ENDIF}

        {$IFDEF SMALLEST_CODE}
        LODSD
        XOR      EAX, EAX
        STOSD
        {$ELSE}
        LODSD
        XCHG     EDX, EAX
        XOR      EAX, EAX
        PUSH     EDX
        CALL     TGraphicTool.Assign
        STOSD    // fBrush
        POP      EDX
        XCHG     ECX, EAX
        JECXZ    @@no_brush
        MOV      [ECX].TGraphicTool.fParentGDITool, EDX
        MOV      [ECX].TGraphicTool.fOnChange.TMethod.Code, offset[TControl.BrushChanged]
        MOV      [ECX].TGraphicTool.fOnChange.TMethod.Data, EBX
        MOV      EAX, EBX
        MOV      EDX, ECX
        CALL     TControl.BrushChanged
        {$IFDEF USE_AUTOFREE4CONTROLS}
        MOV      EAX, EBX
        MOV      EDX, [EBX].TControl.fBrush
        CALL     TControl.Add2AutoFree
        {$ENDIF}
@@no_brush:
        {$ENDIF}

        //skip fCanvas
        LODSD
        ADD      EDI, 4

        LODSD
        STOSD    // fMargin
@@no_parent:
        XCHG     EAX, EBX
        POP      EDI
        POP      ESI
        POP      EBX
end;

function NewForm( AParent: PControl; const Caption: KOLString ): PControl;
const FormClass: array[ 0..4 ] of KOLChar = ( 'F', 'o', 'r', 'm', #0 );
asm
        PUSH     EBX
        PUSH     EDX
        MOV      EDX, offset[FormClass]
        MOV      CL, 1
        CALL     _NewWindowed
        MOV      EBX, EAX
        OR       byte ptr [EBX].TControl.fClsStyle, CS_DBLCLKS
        MOV      EDX, offset[WndProcForm]
        CALL     TControl.AttachProc
        MOV      EDX, offset[WndProcDoEraseBkgnd]
        MOV      EAX, EBX
        CALL     TControl.AttachProc
        POP      EDX
        INC      [EBX].TControl.fSizeGrip
        MOV      EAX, EBX
        CALL     TControl.SetCaption
        DEC      WORD PTR [EBX].TControl.fIsForm
        XCHG     EAX, EBX
        POP      EBX
end;

function NewApplet( const Caption: KOLString ): PControl;
const AppClass: array[ 0..3 ] of KOLChar = ( 'A', 'p', 'p', #0 );
asm
        XOR      ECX, ECX
        INC      ECX
        MOV      [AppButtonUsed], CL
        PUSH     EAX
        MOV      EDX, offset[AppClass]
        XOR      EAX, EAX
        CALL     _NewWindowed
        INC      [EAX].TControl.FIsApplet
        MOV      word ptr [EAX].TControl.fStyle + 2, $90CA //WS_VISIBLE or WS_SYSMENU or WS_POPUP or WS_MINIMIZEBOX or WS_CAPTION
        MOV      byte ptr [EAX].TControl.fExStyle + 2, WS_EX_APPWINDOW shr 16 // WS_EX_APPWINDOW = $40000
        CALL     @@newapp1

        PUSH     ESI // BODY of CreateAppButton here
        PUSH     0
        PUSH     [EAX].TControl.fHandle
        CALL     GetSystemMenu
        MOV      ESI, offset[DeleteMenu]

        XCHG     ECX, EAX
        MOV      EAX, SC_MAXIMIZE
        CDQ

        PUSH     EDX
        PUSH     EAX
        PUSH     ECX

        PUSH     EDX
        {$IFDEF PARANOIA} DB $2C, $20 {$ELSE} SUB AL, $20 {$ENDIF} // SC_MOVE
        PUSH     EAX
        PUSH     ECX

        PUSH     EDX
        {$IFDEF PARANOIA} DB $2C, $10 {$ELSE} SUB AL, $10 {$ENDIF} // SC_SIZE
        PUSH     EAX
        PUSH     ECX

        PUSH     1    // MF_GRAYED or MF_BYCOMMAND
        MOV      AX, SC_RESTORE
        PUSH     EAX
        PUSH     ECX

        CALL     EnableMenuItem
        CALL     ESI
        CALL     ESI
        CALL     ESI
        POP      ESI
@@ret_false:
        XOR      EAX, EAX
        RET

@@chk_CLOSE:
          CMP      word ptr [EDX].TMsg.message, WM_SYSCOMMAND
          JNZ      @@ret_false
          MOV      EDX, dword ptr [EDX].TMsg.wParam
          AND      DX, $FFF0
          CMP      DX, SC_CLOSE
          JNZ      @@ret_false
          PUSH     ECX
          MOV      ECX, [EAX].TControl.fChildren
          JECXZ    @@ret_false1
          XCHG     EAX, ECX
          MOV      ECX, [EAX].TList.fCount
          JECXZ    @@ret_false1
          MOV      EAX, [EAX].TList.fItems
          MOV      ECX, dword ptr [EAX]
          JECXZ    @@ret_false1
          XCHG     EAX, ECX
          PUSH     EAX
          CALL     TControl.IsMainWindow
          TEST     EAX, EAX
          POP      EAX
          JZ       @@ret_false1
          CALL     TControl.Close
          POP      ECX
          XOR      EAX, EAX
          MOV      dword ptr [ECX], EAX
          INC      EAX
          RET
  @@ret_false1:
          POP      ECX
          JMP      @@ret_false

@@newapp1:
        //MOV      [EAX].TControl.FCreateWndExt, offset[CreateAppButton]
        POP      [EAX].TControl.FCreateWndExt
        PUSH     EAX
        CALL     @@newapp2

        // BODY of WndProcApp here:
        CMP      word ptr [EDX].TMsg.message, WM_SETFOCUS
        JNZ      @@chk_CLOSE
        MOV      ECX, [EAX].TControl.FCurrentControl
        JECXZ    @@ret_false
        XCHG     EAX, ECX

        PUSH     EAX
        CALL     CallTControlCreateWindow
        POP      EAX
        PUSH     [EAX].TControl.fHandle

        CALL     SetFocus
        MOV      AL, 1
        RET

@@newapp2:
        POP      EDX
        CALL     TControl.AttachProc
        POP      EAX
        POP      EDX
        PUSH     EAX
        CALL     TControl.SetCaption
        POP      EAX
end;

{$IFDEF ASM_UNICODE}
function _NewControl( AParent: PControl; ControlClassName: PKOLChar;
                      Style: DWORD; Ctl3D: Boolean; Actions: PCommandActions ): PControl;
const szActions = sizeof(TCommandActions);
asm
        PUSH     EBX
        PUSH     EAX  // push AParent
        PUSH     ECX  // push Style
        MOVZX    ECX, Ctl3D
        CALL     _NewWindowed
        XCHG     EBX, EAX
        INC      [EBX].TControl.fIsControl
        INC      [EBX].TControl.fVerticalAlign
        MOV      EAX, Actions
        TEST     EAX, EAX
        JZ       @@noActions
        LEA      EDX, [EBX].TControl.fCommandActions
        XOR      ECX, ECX
        MOV      CL, szActions
        CALL     System.Move
@@noActions:
        POP      EDX  // pop Style
        OR       EDX, WS_CLIPSIBLINGS or WS_CLIPCHILDREN
        MOV      byte ptr [EBX].TControl.fLookTabKeys, $0F
        CMP      [EBX].TControl.fCtl3D, 0
        JZ       @@noCtl3D
        AND      EDX, not WS_BORDER
        OR       byte ptr [EBX].TControl.fExStyle + 1, WS_EX_CLIENTEDGE shr 8
@@noCtl3D:
        MOV      [EBX].TControl.fStyle, EDX
        TEST     EDX, WS_VISIBLE
        SETNZ    AL
        MOV      [EBX].TControl.fVisible, AL
        TEST     EDX, WS_TABSTOP
        POP      ECX // pop AParent
        PUSHFD
        JECXZ    @@noParent

        PUSH     ESI
        PUSH     EDI
        LEA      ESI, [ECX].TControl.fMargin
        LEA      EDI, [EBX].TControl.fBoundsRect
        LODSD
        {$IFNDEF SMALLEST_CODE}
        PUSH     EAX
        ADD      EAX, [ESI+24] // AParent.fClientLeft
        {$ENDIF}
        STOSD    // fBoundsRect.Left
        {$IFNDEF SMALLEST_CODE}
        POP      EAX
        PUSH     EAX
        ADD      EAX, [ESI+16] // AParent.fClientTop
        {$ENDIF}
        STOSD    // fBoundsRect.Top
        {$IFNDEF SMALLEST_CODE}
        XCHG     EDX, EAX
        POP      EAX
        {$ENDIF}
        ADD      EAX, 64
        STOSD    // fBoundsRect.Right
        {$IFNDEF SMALLEST_CODE}
        XCHG     EAX, EDX
        ADD      EAX, 64
        {$ENDIF}
        STOSD    // fBoundsRect.Bottom}
        POP      EDI
        POP      ESI

        MOV      EAX, [ECX].TControl.fCursor
        MOV      [EBX].TControl.fCursor, EAX
        XCHG     EAX, ECX
        CALL     TControl.ParentForm
        XCHG     ECX, EAX
        JECXZ    @@noParent
        INC      [ECX].TControl.fTabOrder
        MOV      EDX, [ECX].TControl.fTabOrder
        MOV      [EBX].TControl.fTabOrder, EDX
@@noParent:
        POPFD
        JZ       @@noTabStop
        INC      [EBX].TControl.fTabstop
        JECXZ    @@noTabstop
        XCHG     EAX, ECX
        MOV      ECX, [EAX].TControl.FCurrentControl
        INC      ECX
        LOOP     @@noTabStop
        MOV      [EAX].TControl.FCurrentControl, EBX
@@noTabStop:
        MOVZX    EDX, [CtlIdCount]
        INC      [CtlIdCount]
        MOV      [EBX].TControl.fMenu, EDX
        MOV      EDX, offset[WndProcCtrl]
        MOV      EAX, EBX
        CALL     TControl.AttachProc
        XCHG     EAX, EBX
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

function NewButton( AParent: PControl; const Caption: KOLString ): PControl;
const szActions = sizeof(TCommandActions);
asm
   PUSH EBX
        PUSH     EDX

        PUSH     0
        PUSH     offset[ButtonActions]

        MOV      EDX, offset[ButtonClass]
        MOV      ECX, WS_VISIBLE or WS_CHILD or BS_PUSHLIKE or WS_TABSTOP or BS_NOTIFY
        CALL     _NewControl
        XCHG     EBX, EAX
        INC      [EBX].TControl.fIgnoreDefault
        //MOV      [EBX].TControl.FCtl3D, 1
        MOV      EDX, [EBX].TControl.fBoundsRect.Top
        ADD      EDX, 22
        MOV      [EBX].TControl.fBoundsRect.Bottom, EDX
        MOV      [EBX].TControl.fTextAlign, taCenter
        INC      [EBX].TControl.fIsButton

        POP      EDX
        MOV      EAX, EBX
        CALL     TControl.SetCaption
        {$IFNDEF SMALLEST_CODE}
        {$IFNDEF BUTTON_DBLCLICK}
        MOV      EAX, EBX
        MOV      EDX, offset[WndProcBtnDblClkAsClk]
        CALL     TControl.AttachProc
        {$ENDIF}
        {$ENDIF SMALLEST_CODE}
        {$IFDEF ALL_BUTTONS_RESPOND_TO_ENTER}
        MOV      EAX, EBX
        MOV      EDX, offset[WndProcBtnReturnClick]
        CALL     TControl.AttachProc
        {$ENDIF}
   XCHG EAX, EBX
   POP  EBX
   
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_BitBtn
        POP      EAX
        POP      EDX
{$ENDIF}
end;

function WndProc_DrawItem( Sender: PControl; var Msg: TMsg; var Rslt: Integer )
                          : Boolean;
asm     //cmd    //opd
       CMP       word ptr [EDX].TMsg.message, WM_DRAWITEM
       JNZ       @@ret_false
       MOV       EAX, [EDX].TMsg.lParam
       MOV       ECX, [EAX].TDrawItemStruct.hwndItem
       JECXZ     @@ret_false
       PUSH      EDX
       {$IFDEF USE_PROP}
       PUSH      offset[ID_SELF]
       PUSH      ECX
       CALL      GetProp
       {$ELSE}
       PUSH      GWL_USERDATA
       PUSH      ECX
       CALL      GetWindowLong
       {$ENDIF}
       POP       EDX
       TEST      EAX, EAX
       JZ        @@ret_false
       PUSH      [EDX].TMsg.lParam
       PUSH      [EDX].TMsg.wParam
       PUSH      CN_DRAWITEM
       PUSH      EAX
       CALL      TControl.Perform
       MOV       AL, 1
       RET
@@ret_false:
       XOR       EAX, EAX
end;

function NewBitBtn( AParent: PControl; const Caption: KOLString;
         Options: TBitBtnOptions; Layout: TGlyphLayout; GlyphBitmap: HBitmap; GlyphCount: Integer ): PControl;
const szBitmapInfo = sizeof(TBitmapInfo);
asm
        PUSH     EBX
        PUSH     EDX
        PUSH     ECX

        PUSH     0
        PUSH     offset[ButtonActions]
        MOV      EDX, offset[ButtonClass]
        MOV      ECX, WS_VISIBLE or WS_CHILD or WS_TABSTOP or BS_OWNERDRAW or BS_NOTIFY
        CALL     _NewControl
        XCHG     EBX, EAX
        INC      [EBX].TControl.fIgnoreDefault
        INC      [EBX].TControl.fIsButton
        INC      [EBX].TControl.fIsBitBtn
        MOV      byte ptr [EBX].TControl.fCommandActions.aAutoSzX, 8
        MOV      byte ptr [EBX].TControl.fCommandActions.aAutoSzY, 8
        POP      EAX
        MOV      [EBX].TControl.fBitBtnOptions, AL
        MOVZX    EDX, Layout
        MOV      [EBX].TControl.fGlyphLayout, DL
        MOV      ECX, GlyphBitmap
        MOV      [EBX].TControl.fGlyphBitmap, ECX
        MOV      EDX, [EBX].TControl.fBoundsRect.Top
        ADD      EDX, 22
        MOV      [EBX].TControl.fBoundsRect.Bottom, EDX
        TEST     ECX, ECX
        JZ       @@noGlyphWH
        {$IFDEF PARANOIA} DB $A8, 01 {$ELSE} TEST AL, bboImageList {$ENDIF}
        JZ       @@getBmpWH
        PUSH     EAX
        MOV      EAX, ESP
        PUSH     EAX
        MOV      EDX, ESP
        PUSH     EAX
        PUSH     EDX
        PUSH     ECX
        CALL     ImageList_GetIconSize
        POP      EAX
        POP      EDX
        MOV      ECX, GlyphCount
        JMP      @@WHready
@@getBmpWH:
        ADD      ESP, -szBitmapInfo
        PUSH     ESP
        PUSH     szBitmapInfo
        PUSH     ECX
        CALL     GetObject
        XCHG     ECX, EAX
        POP      EAX
        POP      EAX
        POP      EDX
        ADD      ESP, szBitmapInfo-12
        TEST     ECX, ECX
        JZ       @@noGlyphWH
        MOV      ECX, GlyphCount
        INC      ECX
        LOOP     @@GlyphCountOK
        PUSH     EAX
        PUSH     EDX
        XCHG     EDX, ECX
        DIV      ECX
        XCHG     ECX, EAX
        POP      EDX
        POP      EAX
@@GlyphCountOK:
        CMP      ECX, 1
        JLE      @@WHReady
        PUSH     EDX
        CDQ
        IDIV     ECX
        POP      EDX
@@WHReady:
        MOV      [EBX].TControl.fGlyphWidth, EAX
        MOV      [EBX].TControl.fGlyphHeight, EDX
        MOV      [EBX].TControl.fGlyphCount, ECX
        POP      ECX     // ECX = @ Caption[ 1 ]
        PUSH     ECX
        PUSH     EDX
        PUSH     EAX
        TEST     EAX, EAX
        JLE      @@noWidthResize
        JECXZ    @@addWLeft
        CMP      [Layout], glyphOver
        JE       @@addWLeft
        MOVZX    ECX, byte ptr[ECX]
        JECXZ    @@addWLeft
        // else
        CMP      [Layout], glyphLeft
        JZ       @@addWRight
        CMP      [Layout], glyphRight
        JNZ      @@noWidthResize
@@addWRight:
        ADD      [EBX].TControl.fBoundsRect.Right, EAX
        ADD      [EBX].TControl.fCommandActions.aAutoSzX, AX
        JMP      @@noWidthResize
@@addWLeft:
        // then
        ADD      EAX, [EBX].TControl.fBoundsRect.Left
        MOV      [EBX].TControl.fBoundsRect.Right, EAX
        MOV      byte ptr [EBX].TControl.fCommandActions.aAutoSzX, 0
@@noWidthResize:
        TEST     EDX, EDX
        JLE      @@noHeightResize
        CMP      [Layout], glyphTop
        JE       @@addHBottom
        CMP      [Layout], glyphBottom
        JNE      @@addHTop
@@addHBottom:
        ADD      [EBX].TControl.fBoundsRect.Bottom, EDX
        ADD      [EBX].TControl.fCommandActions.aAutoSzY, DX
        JMP      @@noHeightResize
@@addHTop:
        ADD      EDX, [EBX].TControl.fBoundsRect.Top
        MOV      [EBX].TControl.fBoundsRect.Bottom, EDX
        MOV      [EBX].TControl.fCommandActions.aAutoSzY, 0
@@noHeightResize:
        POP      ECX
        POP      EAX
        CDQ
        MOV      DL, 4
        TEST     [EBX].TControl.fBitBtnOptions, 2 //1 shl bboNoBorder
        JNZ      @@noBorderResize
        JECXZ    @@noBorderWinc
        ADD      [EBX].TControl.fBoundsRect.Right, EDX
        CMP      [EBX].TControl.fCommandActions.aAutoSzX, 0
        JZ       @@noBorderWinc
        ADD      [EBX].TControl.fCommandActions.aAutoSzX, DX
@@noBorderWinc:
        TEST     EAX, EAX
        JLE      @@noBorderResize
        ADD      [EBX].TControl.fBoundsRect.Bottom, EDX
        CMP      [EBX].TControl.fCommandActions.aAutoSzY, 0
        JZ       @@noBorderResize
        ADD      [EBX].TControl.fCommandActions.aAutoSzY, DX
@@noBorderResize:
@@noGlyphWH:
        MOV      ECX, [EBX].TControl.fParent
        JECXZ    @@notAttach2Parent
        XCHG     EAX, ECX
        MOV      EDX, offset[WndProc_DrawItem]
        CALL     TControl.AttachProc
@@notAttach2Parent:
        MOV      EAX, EBX
        MOV      EDX, offset[WndProcBitBtn]
        CALL     TControl.AttachProc
        MOV      EAX, EBX
        POP      EDX
        CALL     TControl.SetCaption
        MOV      [EBX].TControl.fTextAlign, taCenter
        {$IFDEF ALL_BUTTONS_RESPOND_TO_ENTER}
        MOV      EAX, EBX
        MOV      EDX, offset[WndProcBtnReturnClick]
        CALL     TControl.AttachProc
        {$ENDIF}
        XCHG     EAX, EBX
        POP      EBX
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_BitBtn
        POP      EAX
        POP      EDX
 {$ENDIF}
end;

function NewCheckbox( AParent: PControl; const Caption: KOLString ): PControl;
asm
        CALL     NewButton
        MOV      EDX, [EAX].TControl.fBoundsRect.Left
        ADD      EDX, 72
        MOV      [EAX].TControl.fBoundsRect.Right, EDX
        MOV      [EAX].TControl.fStyle, WS_VISIBLE or WS_CHILD or BS_AUTOCHECKBOX or WS_TABSTOP or BS_NOTIFY
        MOV      [EAX].TControl.fCommandActions.aAutoSzX, 24
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_CheckBox
        POP      EAX
        POP      EDX
{$ENDIF}
end;

procedure ClickRadio( Sender:PObj );
asm
        MOV      ECX, [EAX].TControl.fParent
        JECXZ    @@exit
        PUSH     [EAX].TControl.fMenu
        PUSH     [ECX].TControl.fRadioLast
        PUSH     [ECX].TControl.fRadio1st
        PUSH     [ECX].TControl.fHandle
        CALL     CheckRadioButton
@@exit:
end;

function NewRadiobox( AParent: PControl; const Caption: KOLString ): PControl;
const
  RadioboxStyles = WS_VISIBLE or WS_CHILD or BS_RADIOBUTTON or
                   WS_TABSTOP or WS_GROUP or BS_NOTIFY;
asm
        PUSH     EBX
        PUSH     EAX
        CALL     NewCheckbox
        XCHG     EBX, EAX
        MOV      [EBX].TControl.fStyle, RadioboxStyles
        MOV      [EBX].TControl.fControlClick, offset[ClickRadio]
        POP      ECX
        JECXZ    @@exit
        MOV      EDX, [EBX].TControl.fMenu
        MOV      [ECX].TControl.fRadioLast, EDX
        MOV      EAX, [ECX].TControl.fRadio1st
        TEST     EAX, EAX
        JNZ      @@exit
        MOV      [ECX].TControl.fRadio1st, EDX
        MOV      EAX, EBX
        CALL     TControl.SetRadioChecked
@@exit: XCHG     EAX, EBX
        POP      EBX
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_RadioBox
        POP      EAX
        POP      EDX
{$ENDIF}
end;

{$IFDEF ASM_UNICODE}
function NewLabel( AParent: PControl; const Caption: KOLString ): PControl;
asm
        PUSH     EDX

        PUSH     0
        PUSH     offset[LabelActions]
        MOV      ECX, WS_VISIBLE or WS_CHILD or SS_LEFTNOWORDWRAP or SS_NOPREFIX or SS_NOTIFY
        MOV      EDX, offset[StaticClass]
        CALL     _NewControl
        INC      [EAX].TControl.fIsStaticControl
        INC      [EAX].TControl.fSizeRedraw
        MOV      EDX, [EAX].TControl.fBoundsRect.Top
        ADD      EDX, 22
        MOV      [EAX].TControl.fBoundsRect.Bottom, EDX
        POP      EDX
        PUSH     EAX
        CALL     TControl.SetCaption
        POP      EAX
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_Label
        POP      EAX
        POP      EDX
{$ENDIF}
end;
{$ENDIF ASM_UNICODE}

function NewWordWrapLabel( AParent: PControl; const Caption: KOLString ): PControl;
asm
        CALL     NewLabel
        MOV      EDX, [EAX].TControl.fBoundsRect.Top
        ADD      EDX, 44
        MOV      [EAX].TControl.fBoundsRect.Bottom, EDX
        INC      [EAX].TControl.fWordWrap
        AND      byte ptr [EAX].TControl.fStyle, not SS_LEFTNOWORDWRAP
end;

function NewLabelEffect( AParent: PControl; const Caption: KOLString; ShadowDeep: Integer ): PControl;
asm
        PUSH     EBX

        PUSH     ECX
        PUSH     EDX
        XOR      EDX, EDX
        CALL     NewLabel
        MOV      EBX, EAX
        DEC      [EBX].TControl.fIsStaticControl // снова 0 !
        MOV      EDX, offset[WndProcLabelEffect]
        CALL     TControl.AttachProc

        POP      EDX
        MOV      EAX, EBX
        CALL     TControl.SetCaption

        MOV      EDX, offset[WndProcDoEraseBkgnd]
        MOV      EAX,EBX
        CALL     TControl.AttachProc
        MOV      [EBX].TControl.fTextAlign, taCenter
        MOV      [EBX].TControl.fTextColor, clWindowText
        POP      [EBX].TControl.fShadowDeep
        INC      [EBX].TControl.fIgnoreWndCaption
        ADD      [EBX].TControl.fBoundsRect.Bottom, 40 - 22
        MOV      [EBX].TControl.fColor2, clNone

        XCHG     EAX, EBX
        POP      EBX
end;

function WndProcDoEraseBkgnd( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //        //
        CMP       word ptr [EDX].TMsg.message, WM_ERASEBKGND
        JNE       @@ret_false
        MOV       byte ptr [ECX], 1
        PUSH      EBX
        PUSH      EDI
        MOV       EBX, EAX
        MOV       EDI, [EDX].TMsg.wParam

        {$IFDEF SMALLEST_CODE}
        {$ELSE}
        CALL      TControl.CreateChildWindows
        CMP       [EBX].TControl.fTransparent, 0
        JNE       @@exit
        {$ENDIF}

        {$IFDEF SMALLEST_CODE}
        {$ELSE}
        PUSH      OPAQUE
        PUSH      EDI
        CALL      SetBkMode
        MOV       EAX, [EBX].TControl.fColor
        CALL      Color2RGB
        PUSH      EAX
        PUSH      EDI
        CALL      SetBkColor
        XOR       EAX, EAX
        PUSH      EAX
        PUSH      EAX
        PUSH      EAX
        PUSH      EDI
        CALL      SetBrushOrgEx
        {$ENDIF}
        SUB       ESP, 16
        PUSH      ESP
        PUSH      [EBX].TControl.fHandle
        CALL      GetClientRect
        MOV       EAX, EBX
        CALL      dword ptr[Global_GetCtlBrushHandle]
        MOV       EDX, ESP
        PUSH      EAX
        PUSH      EDX
        PUSH      EDI
        CALL      Windows.FillRect
        ADD       ESP, 16
@@exit: POP       EDI
        POP       EBX
@@ret_false:
        XOR       EAX, EAX
end;

{$IFDEF ASM_UNICODE}
function NewGroupbox( AParent: PControl; const Caption: KOLString ): PControl;
asm
        PUSH     EDX
        PUSH     0
        PUSH     offset[ButtonActions]
        MOV      EDX, offset[ButtonClass]
        MOV      ECX, WS_VISIBLE or WS_CHILD or BS_GROUPBOX or WS_CLIPCHILDREN or WS_CLIPSIBLINGS
        CALL     _NewControl
        OR       [EAX].TControl.fExStyle, WS_EX_CONTROLPARENT
        MOV      EDX, [EAX].TControl.fBoundsRect.Left
        ADD      EDX, 100
        MOV      [EAX].TControl.fBoundsRect.Right, EDX
        MOV      EDX, [EAX].TControl.fBoundsRect.Top
        ADD      EDX, 100
        MOV      [EAX].TControl.fBoundsRect.Bottom, EDX
        MOV      [EAX].TControl.fClientTop, 22
        XOR      EDX, EDX
        MOV      [EAX].TControl.fTabstop, DL
        MOV      DL, 2
        ADD      [EAX].TControl.fClientBottom, EDX
        ADD      [EAX].TControl.fClientLeft, EDX
        ADD      [EAX].TControl.fClientRight, EDX
        POP      EDX
        PUSH     EAX
        CALL     TControl.SetCaption
        POP      EAX
        PUSH     EAX
        INC      [EAX].TControl.fIsGroupBox
        MOV      EDX, offset[WndProcDoEraseBkgnd]
        CALL     TControl.AttachProc
        POP      EAX
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_GroupBox
        POP      EAX
        POP      EDX
{$ENDIF}
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
function NewPanel( AParent: PControl; EdgeStyle: TEdgeStyle ): PControl;
const CreateStyle = WS_VISIBLE or WS_CHILD or SS_LEFTNOWORDWRAP or
                    SS_NOPREFIX or SS_NOTIFY;
asm
{$IFDEF GRAPHCTL_XPSTYLES}
        MOVZX    EDX, EdgeStyle
        PUSH     EDX
{$ENDIF}

        PUSH     EDX
        MOV      EDX, offset[StaticClass]
        MOV      ECX, CreateStyle
        PUSH     0
        PUSH     offset[LabelActions]
        CALL     _NewControl
        ADD      [EAX].TControl.fBoundsRect.Right, 100-64
        ADD      [EAX].TControl.fBoundsRect.Bottom, 100-64
        OR       byte ptr [EAX].TControl.fExStyle+2, 1
        POP      ECX
        CMP      CL, 1
        JG       @@exit
        JE       @@sunken
        OR       byte ptr [EAX].TControl.fStyle+2, $40
{$IFDEF GRAPHCTL_XPSTYLES}
        JMP      @@visual
{$ELSE}
        RET
{$ENDIF}
@@sunken:
        OR       byte ptr [EAX].TControl.fStyle+1, $10
@@exit:

{$IFDEF GRAPHCTL_XPSTYLES}
@@visual:
        CMP      AppTheming, TRUE
        JNE      @@es_none_
        CMP      CL, 1
        JG       @@es_none_
        JE       @@not_sunken
        AND      byte ptr [EAX].TControl.fStyle+2, $00
        JNE      @@es_none_
@@not_sunken:
        AND      byte ptr [EAX].TControl.fStyle+1, $00
@@es_none_:

        PUSH     EBX
        MOV      BL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, BL
        POP      EBX
        
        POP      EDX
        PUSH     EAX
        PUSH     EDX
        CALL     TControl.SetEdgeStyle
        POP      EDX
        POP      EAX

        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_Panel
        POP      EAX
        POP      EDX
{$ENDIF}
end;
{$ENDIF ASM_UNICODE}

function WndProcSplitter( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, WM_NCHITTEST
        JNE      @@noWM_NCHITTEST
        PUSH     ECX
        PUSH     [EDX].TMsg.lParam
        PUSH     [EDX].TMsg.wParam
        PUSH     [EDX].TMsg.message
        PUSH     [EAX].TControl.fHandle
        CALL     DefWindowProc
        TEST     EAX, EAX
        JLE      @@htReady
        XOR      EAX, EAX
        INC      EAX
@@htReady:
        POP      ECX
        MOV      [ECX], EAX
        MOV      AL, 1
        RET

@@noWM_NCHITTEST:
        PUSH     EBX
        XCHG     EBX, EAX
        CMP      word ptr [EDX].TMsg.message, WM_MOUSEMOVE
        JNE      @@noWM_MOUSEMOVE

        PUSH     [EBX].TControl.fCursor
        CALL     Windows.SetCursor

        XOR      EDX, EDX

        {$IFDEF USE_ASM_DODRAG}
        CALL     @@DoDrag
        {$ELSE}
        MOV      EAX, EBX
        CALL     DoDrag
        {$ENDIF}

        POP      EBX
        RET

{$IFDEF USE_ASM_DODRAG}
@@DoDrag:
        PUSHAD
        MOVZX    EDI, DL // EDI = 1 if Cancel, 0 otherwise
        CMP      [EBX].TControl.fDragging, 0
        JZ       @@e_DoDrag
        MOV      EAX, [EBX].TControl.fParent
        MOV      EAX, [EAX].TControl.fChildren
        PUSH     EAX
        MOV      EDX, EBX
        CALL     TList.IndexOf
        POP      EDX // EDX = Self_.fParent.fChildren:PList
        MOV      EBP, EBX  // Prev := Self_;
        TEST     EAX, EAX
        JLE      @@noPrev
        MOV      EDX, [EDX].TList.fItems
        MOV      EBP, [EDX+EAX*4-4] // Prev = Self_.fParent.fChildren.fItems[I-1]
        PUSH     EBP  // push Prev
@@noPrev:
        PUSH     EDX
        PUSH     EDX
        PUSH     ESP
        CALL     GetCursorPos
        DEC      EDI
        JNZ      @@noCancel
        POP      EDX
        POP      EDX
        PUSH     [EBX].TControl.fSplitStartPos.y
        PUSH     [EBX].TControl.fSplitStartPos.x
@@noCancel:
        OR       EDI, -1
        MOV      CL, [EBX].TControl.fAlign
        MOV      AL, 1
        SHL      EAX, CL
        {$IFDEF PARANOIA} DB $A8, chkRight or chkBott {$ELSE} TEST AL, chkRight or chkBott {$ENDIF} //fAlign in [ caRight, caBottom ] ?
        JNZ      @@mReady
        INC      EDI
        INC      EDI
@@mReady:
        MOV      EDX, [EBX].TControl.fParent
        MOV      EBP, [EDX].TControl.fMargin
        NEG      EBP
        {$IFDEF PARANOIA} DB $A8, chkTop or chkBott {$ELSE} TEST AL, chkTop or chkBott {$ENDIF} // fAlign in [ caTop, caBottom ] ?
        XCHG     EAX, EDX
        JZ       @@noTopBottom

        CALL     TControl.GetClientHeight
        XCHG     EDX, EAX

        POP      EAX
        POP      ESI // MousePos.y
        MOV      EAX, ESI
        PUSH     EDX // Self_.fParent.ClientHeight
        SUB      EAX, [EBX].TControl.fSplitStartPos.y
        IMUL     EAX, EDI
        ADD      EAX, [EBX].TControl.fSplitStartSize // EAX = NewSize1

        POP      EDX
        SUB      EDX, EAX
        SUB      EDX, [EBX].TControl.fBoundsRect.Bottom
        ADD      EDX, [EBX].TControl.fBoundsRect.Top
        LEA      EDX, [EDX+EBP*4]

        MOV      ECX, [EBX].TControl.fSecondControl
        JECXZ    @@noSecondControl
        MOV      EDX, [ECX].TControl.fBoundsRect.Bottom
        SUB      EDX, [ECX].TControl.fBoundsRect.Top
        CMP      [ECX].TControl.fAlign, caClient
        JNZ      @@noSecondControl

        PUSH     EAX
        MOV      EAX, [EBX].TControl.fSplitStartPos.y
        SUB      EAX, ESI
        IMUL     EAX, EDI
        ADD      EAX, [EBX].TControl.fSplitStartPos2.y
        LEA      EDX, [EAX+EBP*4]
        POP      EAX

@@noSecondControl:
        JMP      @@newSizesReady

@@noTopBottom:
        CALL     TControl.GetClientWidth
        XCHG     EDX, EAX

        POP      ESI // MousePos.x
        POP      ECX
        MOV      EAX, ESI
        PUSH     EDX // Self_.fParent.ClientWidth
        SUB      EAX, [EBX].TControl.fSplitStartPos.x
        IMUL     EAX, EDI
        ADD      EAX, [EBX].TControl.fSplitStartSize // EAX = NewSize1

        POP      EDX
        SUB      EDX, EAX
        SUB      EDX, [EBX].TControl.fBoundsRect.Right
        ADD      EDX, [EBX].TControl.fBoundsRect.Left
        LEA      EDX, [EDX+EBP*4]

        MOV      ECX, [EBX].TControl.fSecondControl
        JECXZ    @@newSizesReady
        MOV      EDX, [ECX].TControl.fBoundsRect.Right
        SUB      EDX, [ECX].TControl.fBoundsRect.Left
        CMP      [ECX].TControl.fAlign, caClient
        JNZ      @@noSecondControl

        PUSH     EAX
        MOV      EAX, [EBX].TControl.fSplitStartPos.x
        SUB      EAX, ESI
        IMUL     EAX, EDI
        ADD      EAX, [EBX].TControl.fSplitStartPos2.x
        LEA      EDX, [EAX+EBP*4]
        POP      EAX

@@newSizesReady:
        MOV      ECX, [EBX].TControl.fSplitMinSize1
        SUB      ECX, EAX
        JLE      @@noCheckMinSize1
        SUB      EDX, ECX
        ADD      EAX, ECX

@@noCheckMinSize1:
        MOV      ECX, [EBX].TControl.fSplitMinSize2
        SUB      ECX, EDX
        JLE      @@noCheckMinSize2
        SUB      EAX, ECX
        ADD      EDX, ECX

@@noCheckMinSize2:
        MOV      ECX, [EBX].TControl.fOnSplit.TMethod.Code
        JECXZ    @@noOnSplit
        PUSHAD
        PUSH     EDX
        MOV      ESI, ECX
        XCHG     ECX, EAX
        MOV      EDX, EBX
        MOV      EAX, [EBX].TControl.fOnSplit.TMethod.Data
        CALL     ESI
        TEST     AL, AL
        POPAD
        JZ       @@e_DoDrag

@@noOnSplit:
        XCHG     ESI, EAX // NewSize1 -> ESI
        POP      EBP
        ADD      ESP, -16
        MOV      EAX, EBP
        MOV      EDX, ESP
        CALL     TControl.GetBoundsRect
        MOVZX    ECX, [EBX].TControl.fAlign
        LOOP     @@noPrev_caLeft
        ADD      ESI, [ESP].TRect.Left
        MOV      [ESP].TRect.Right, ESI
@@noPrev_caLeft:
        LOOP     @@noPrev_caTop
        ADD      ESI, [ESP].TRect.Top
        MOV      [ESP].TRect.Bottom, ESI
@@noPrev_caTop:
        LOOP     @@noPrev_caRight
        MOV      EAX, [ESP].TRect.Right
        SUB      EAX, ESI
        MOV      [ESP].TRect.Left, EAX
@@noPrev_caRight:
        LOOP     @@noPrev_caBottom
        MOV      EAX, [ESP].TRect.Bottom
        SUB      EAX, ESI
        MOV      [ESP].TRect.Top, EAX
@@noPrev_caBottom:
        MOV       EAX, EBP
        MOV       EDX, ESP
        CALL      TControl.SetBoundsRect
        ADD       ESP, 16
    {$IFDEF OLD_ALIGN}
        MOV       EAX, [EBX].TControl.fParent
    {$ELSE NEW_ALIGN}
        MOV       EAX, EBX
    {$ENDIF}
        CALL      dword ptr[Global_Align]

@@e_DoDrag:
        POPAD
        RET
{$ENDIF USE_ASM_DODRAG}

@@noWM_MOUSEMOVE:
        CMP      word ptr [EDX].TMsg.message, WM_LBUTTONDOWN
        JNE      @@noWM_LBUTTONDOWN
        MOV      ECX, [EBX].TControl.fParent
        TEST     ECX, ECX
        JZ       @@noWM_LBUTTONDOWN

        MOV      EAX, [ECX].TControl.fChildren
        PUSH     EAX
        MOV      EDX, EBX
        CALL     TList.IndexOf
        POP      ECX
        MOV      EDX, EBX
        TEST     EAX, EAX
        JLE      @@noParent1
        MOV      ECX, [ECX].TList.fItems
        MOV      EDX, [ECX+EAX*4-4]
@@noParent1:

        MOV      CL, [EBX].TControl.fAlign
        MOV      AL, 1
        SHL      EAX, CL
        {$IFDEF PARANOIA} DB $A8, chkTop or chkBott {$ELSE} TEST AL, chkTop or chkBott {$ENDIF} // fAlign in [caTop,caBottom] ?
        XCHG     EAX, EDX
        JZ       @@no_caTop_caBottom
        CALL     TControl.GetHeight
        JMP      @@caTop_caBottom
@@no_caTop_caBottom:
        CALL     TControl.GetWidth
@@caTop_caBottom:
        MOV      [EBX].TControl.fSplitStartSize, EAX
        MOV      ECX, [EBX].TControl.fSecondControl
        JECXZ    @@noSecondControl1
        XCHG     EAX, ECX
        PUSH     EAX
        CALL     TControl.GetWidth
        MOV      [EBX].TControl.fSplitStartPos2.x, EAX
        POP      EAX
        CALL     TControl.GetHeight
        MOV      [EBX].TControl.fSplitStartPos2.y, EAX
@@noSecondControl1:
        PUSH     [EBX].TControl.fHandle
        CALL     SetCapture
        OR       [EBX].TControl.fDragging, 1
        PUSH     0
        PUSH     100
        PUSH     $7B
        PUSH     [EBX].TControl.fHandle
        CALL     SetTimer
        LEA      EAX, [EBX].TControl.fSplitStartPos
        PUSH     EAX
        CALL     GetCursorPos
        JMP      @@exit

@@noWM_LBUTTONDOWN:
        CMP      word ptr [EDX].TMsg.message, WM_LBUTTONUP
        JNE      @@noWM_LBUTTONUP
        XOR      EDX, EDX

        {$IFDEF USE_ASM_DODRAG}
        CALL     @@DoDrag
        {$ELSE}
        MOV      EAX, EBX
        CALL     DoDrag
        {$ENDIF}

        JMP      @@killtimer

@@noWM_LBUTTONUP:
        CMP      word ptr[EDX].TMsg.message, WM_TIMER
        JNE      @@exit
        CMP      [EBX].TControl.fDragging, 0
        JE       @@exit
        PUSH     VK_ESCAPE
        CALL     GetAsyncKeyState
        TEST     EAX, EAX
        JGE      @@exit

        MOV      DL, 1
        {$IFDEF USE_ASM_DODRAG}
        CALL     @@DoDrag
        {$ELSE}
        MOV      EAX, EBX
        CALL     DoDrag
        {$ENDIF}

@@killtimer:
        MOV      [EBX].TControl.fDragging, 0
        PUSH     $7B
        PUSH     [EBX].TControl.fHandle
        CALL     KillTimer
        CALL     ReleaseCapture

@@exit:
        POP      EBX
        XOR      EAX, EAX
end;

function NewSplitterEx( AParent: PControl; MinSizePrev, MinSizeNext: Integer;
         EdgeStyle: TEdgeStyle ): PControl;
const int_IDC_SIZEWE = integer( IDC_SIZEWE );
asm
        PUSH     EBX
        PUSH     EAX  // AParent
        PUSH     ECX  // MinSizePrev
        PUSH     EDX  // MinSizeNext
        MOV      DL, EdgeStyle
        CALL     NewPanel
        XCHG     EBX, EAX
        POP      [EBX].TControl.fSplitMinSize1
        POP      [EBX].TControl.fSplitMinSize2
        INC      [EBX].TControl.fIsSplitter
        XOR      EDX, EDX
        MOV      DL, 4
        MOV      EAX, [EBX].TControl.fBoundsRect.Left
        ADD      EAX, EDX
        MOV      [EBX].TControl.fBoundsRect.Right, EAX
        ADD      EDX, [EBX].TControl.fBoundsRect.Top
        MOV      [EBX].TControl.fBoundsRect.Bottom, EDX

        POP      ECX  // ECX = AParent
        JECXZ    @@noParent2
        MOV      EAX, [ECX].TControl.fChildren
        MOV      ECX, [EAX].TList.fCount
        CMP      ECX, 1
        JLE      @@noParent2

        MOV      EAX, [EAX].TList.fItems
        MOV      EAX, [EAX+ECX*4-8]
        MOV      CL, [EAX].TControl.fAlign
        PUSH     ECX
        MOV      AL, 1
        SHL      EAX, CL
        {$IFDEF PARANOIA} DB $A8, chkTop or chkBott {$ELSE} TEST AL, chkTop or chkBott {$ENDIF}
        MOV      EAX, int_IDC_SIZEWE
        JZ       @@TopBottom
        INC      EAX
@@TopBottom:
        PUSH     EAX
        PUSH     0
        CALL     LoadCursor
        MOV      [EBX].TControl.fCursor, EAX
        POP      EDX
        MOV      EAX, EBX
        CALL     TControl.SetAlign

@@noParent2:
        MOV      EAX, EBX
        MOV      EDX, offset[WndProcSplitter]
        CALL     TControl.AttachProc
        XCHG     EAX, EBX
        POP      EBX
        
{$IFDEF GRAPHCTL_XPSTYLES}
        PUSH     EDX
        MOV      DL, [EAX].TControl.fTransparent
        MOV      [EAX].TControl.fClassicTransparent, DL
        POP      EDX
        
        PUSH     EDX
        PUSH     EAX
        CALL     Attach_WM_THEMECHANGED
        POP      EAX
        POP      EDX

        PUSH     EDX
        PUSH     EAX
        CALL     XP_Themes_For_Splitter
        POP      EAX
        POP      EDX
{$ENDIF}
end;

function NewGradientPanel( AParent: PControl; Color1, Color2: TColor ): PControl;
asm
        PUSH     ECX
        PUSH     EDX
        XOR      EDX, EDX
        CALL     NewLabel
        PUSH     EAX
        MOV      EDX, offset[WndProcGradient]
        CALL     TControl.AttachProc
        POP      EAX
        POP      [EAX].TControl.fColor1
        POP      [EAX].TControl.fColor2
        ADD      [EAX].TControl.fBoundsRect.Right, 40-64
        ADD      [EAX].TControl.fBoundsRect.Bottom, 40 - 22
end;

function NewGradientPanelEx( AParent: PControl; Color1, Color2: TColor;
                             Style: TGradientStyle; Layout: TGradientLayout ): PControl;
asm
        PUSH     ECX
        PUSH     EDX
        XOR      EDX, EDX
        CALL     NewLabel
        PUSH     EAX
        MOV      EDX, offset[WndProcGradientEx]
        CALL     TControl.AttachProc
        POP      EAX
        POP      [EAX].TControl.fColor1
        POP      [EAX].TControl.fColor2
        ADD      [EAX].TControl.fBoundsRect.Right, 40-100
        ADD      [EAX].TControl.fBoundsRect.Bottom, 40 - 22
        MOV      DL, Style
        MOV      [EAX].TControl.fGradientStyle, DL
        MOV      DL, Layout
        MOV      [EAX].TControl.fGradientLayout, DL
end;

const EditClass: array[0..4] of KOLChar = ( 'E','D','I','T',#0 );
function NewEditbox( AParent: PControl; Options: TEditOptions ) : PControl;
const int_IDC_IBEAM = integer( IDC_IBEAM );
const WS_flags = integer( WS_VISIBLE or WS_CHILD or WS_TABSTOP or WS_BORDER );
const WS_clear = integer( not(WS_VSCROLL or WS_HSCROLL) );
asm
        PUSH     EBX
        XCHG     EBX, EAX // EBX=AParent
        PUSH     EDX
        MOV      EAX, ESP
        XOR      ECX, ECX
        MOV      CL, 11
        MOV      EDX, offset [EditFlags]
        CALL     MakeFlags
        XCHG     ECX, EAX // ECX = Flags
        POP      EAX  // Options
        PUSH     EAX
        {$IFDEF PARANOIA} DB $A8, 8 {$ELSE} TEST AL, 8 {$ENDIF}
        JNZ      @@1
        AND      ECX, WS_clear
@@1:    OR       ECX, WS_flags
        PUSH     1
        PUSH     offset [EditActions]
        MOV      EDX, offset [EditClass]
        XCHG     EAX, EBX
        CALL     _NewControl
        XCHG     EBX, EAX
        LEA      ECX, [EBX].TControl.fBoundsRect
        MOV      EDX, [ECX].TRect.Left
        ADD      EDX, 100
        MOV      [ECX].TRect.Right, EDX
        MOV      EDX, [ECX].TRect.Top
        ADD      EDX, 22
        MOV      [ECX].TRect.Bottom, EDX
        POP      EAX // Options
        {$IFDEF PARANOIA} DB $A8, 8 {$ELSE} TEST AL, 8 {$ENDIF}
        MOV      DL, $0D
        JZ       @@2
        ADD      [ECX].TRect.Right, 100
        ADD      [ECX].TRect.Bottom, 200 - 22
        MOV      DL, 1
        INC      [EBX].TControl.fIgnoreDefault
@@2:
        TEST     AH, 4
        JZ       @@3
        AND      DL, $FE
@@3:    MOV      [EBX].TControl.fLookTabKeys, DL
        XCHG     EAX, EBX
        POP      EBX
end;

{$IFDEF ASM_UNICODE}
const ListBoxClass : array[ 0..7 ] of Char = ( 'L','I','S','T','B','O','X',#0 );
function NewListbox( AParent: PControl; Options: TListOptions ): PControl;
asm
        PUSH     EAX
        PUSH     EDX
        MOV      EAX, ESP
        MOV      EDX, offset[ListFlags]
        XOR      ECX, ECX
        MOV      CL, 11
        CALL     MakeFlags
        POP      EDX
        OR       EAX, WS_VISIBLE or WS_CHILD or WS_TABSTOP or WS_BORDER or WS_VSCROLL or LBS_NOTIFY
        XCHG     ECX, EAX
        POP      EAX
        PUSH     1
        PUSH     offset[ListActions]
        MOV      EDX, offset[ListBoxClass]
        CALL     _NewControl
        ADD      [EAX].TControl.fBoundsRect.Right, 100
        ADD      [EAX].TControl.fBoundsRect.Bottom, 200-64
        MOV      [EAX].TControl.fColor, clWindow
        MOV      [EAX].TControl.fLookTabKeys, 3
end;
{$ENDIF ASM_UNICODE}

{$IFNDEF USE_DROPDOWNCOUNT}
procedure ComboboxDropDown( Sender: PObj );
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX
        CALL     TControl.GetItemsCount
        CMP      EAX, 1
        JGE      @@1
        MOV      AL, 1
@@1:    CMP      EAX, 8
        JLE      @@2
        XOR      EAX, EAX
        MOV      AL, 8
@@2:    XOR      ESI, ESI
        PUSH     SWP_NOMOVE or SWP_NOSIZE or SWP_NOZORDER or SWP_NOACTIVATE or SWP_NOREDRAW or SWP_SHOWWINDOW
        PUSH     ESI
        PUSH     ESI
        PUSH     SWP_NOMOVE or SWP_NOZORDER or SWP_NOACTIVATE or SWP_NOREDRAW or SWP_HIDEWINDOW
        PUSH     EAX
        MOV      EAX, EBX
        CALL     TControl.GetHeight
        POP      ECX
        INC      ECX
        IMUL     ECX
        INC      EAX
        INC      EAX
        PUSH     EAX
        MOV      EAX, EBX
        CALL     TControl.GetWidth
        PUSH     EAX
        INC      ESI
@@3:    XOR      EDX, EDX
        PUSH     EDX
        PUSH     EDX
        PUSH     EDX
        PUSH     [EBX].TControl.fHandle
        CALL     SetWindowPos
        DEC      ESI
        JZ       @@3
        MOV      ECX, [EBX].TControl.fOnDropDown.TMethod.Code
        JECXZ    @@exit
        MOV      EAX, [EBX].TControl.fOnDropDown.TMethod.Data
        MOV      EDX, EBX
        CALL     ECX
@@exit: POP      ESI
        POP      EBX
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
procedure CreateComboboxWnd( Combo: PControl );
//const PrevProcStr: PChar = 'PREV_PROC'; //************ Remarked By M.Gerasimov
asm
        PUSH     EDI
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     GW_CHILD
        PUSH     [EBX].TControl.fHandle
@@getwindow:
        CALL     GetWindow
        TEST     EAX, EAX
        JZ       @@fin
        PUSH     offset[WndFuncCombo]
        PUSH     GWL_WNDPROC
        PUSH     EAX
        XCHG     EDI, EAX
        CALL     SetWindowLong
        PUSH     EAX
        PUSH     offset [ID_PREVPROC]                       //
        PUSH     EDI
        CALL     SetProp
@@2getnext:
        PUSH     GW_HWNDNEXT
        PUSH     EDI
        JMP      @@getwindow
@@fin:  POP      EBX
        POP      EDI
end;
{$ENDIF ASM_UNICODE}

const ComboboxClass: array[0..8] of KOLChar = ('C','O','M','B','O','B','O','X',#0 );
function NewCombobox( AParent: PControl; Options: TComboOptions ): PControl;
asm
        PUSH     EDX
        PUSH     EAX
        PUSH     EDX
        MOV      EAX, ESP
        MOV      EDX, offset[ComboFlags]
        XOR      ECX, ECX
        MOV      CL, 10
        CALL     MakeFlags
        POP      EDX
        XCHG     ECX, EAX
        POP      EAX
        PUSH     1
        PUSH     offset[ComboActions]
        MOV      EDX, offset[ComboboxClass]
        OR       ECX, WS_VISIBLE or WS_CHILD or WS_VSCROLL or CBS_HASSTRINGS or WS_TABSTOP
        TEST     ECX, CBS_SIMPLE
        JNZ      @@O
        OR       ECX, CBS_DROPDOWN
@@O:
        CALL     _NewControl
        MOV      [EAX].TControl.fCreateWndExt, offset[CreateComboboxWnd]
        MOV      [EAX].TControl.fDropDownProc, offset[ComboboxDropDown]
        OR       byte ptr [EAX].TControl.fClsStyle, CS_DBLCLKS
        ADD      [EAX].TControl.fBoundsRect.Right, 100-64
        ADD      [EAX].TControl.fBoundsRect.Bottom, 22-64
        MOV      CL, 1
        POP      EDX
        TEST     DL, 1
        JZ       @@exit
        MOV      CL, 3
@@exit:
        MOV      [EAX].TControl.fLookTabKeys, CL
        PUSH     EAX
        MOV      EDX, offset[ WndProcCombo ]
        CALL     TControl.AttachProc
        POP      EAX
end;

function WndProcResize(Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        PUSH     ESI
        CMP      word ptr [EDX].TMsg.message, WM_SIZE
        JNZ      @@exit

        MOV      ESI, [EAX].TControl.fChildren
        MOV      ECX, [ESI].TList.fCount
        JECXZ    @@exit
        MOV      ESI, [ESI].TList.fItems
@@loo:  PUSH     ECX
        LODSD
        PUSH     EAX
        PUSH     EAX
        PUSH     CM_SIZE
        PUSH     EAX
        CALL     TControl.Perform
        POP      ECX
        LOOP     @@loo

@@exit: XOR      EAX, EAX
        POP      ESI
end;

function WndProcParentResize( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, CM_SIZE
        JNZ      @@exit
        PUSH     0
        PUSH     0
        PUSH     WM_SIZE
        PUSH     EAX
        CALL     TControl.Perform
@@exit: XOR      EAX, EAX
end;

function NewProgressbar( AParent: PControl ): PControl;
asm
        PUSH     1
        PUSH     0
        MOV      EDX, offset[Progress_class]
        MOV      ECX, WS_CHILD or WS_VISIBLE
        CALL     _NewCommonControl
        LEA      EDX, [EAX].TControl.fBoundsRect
        MOV      ECX, [EDX].TRect.Left
        ADD      ECX, 300
        MOV      [EDX].TRect.Right, ECX
        MOV      ECX, [EDX].TRect.Top
        ADD      ECX, 20
        MOV      [EDX].TRect.Bottom, ECX
        XOR      EDX, EDX
        MOV      [EAX].TControl.fMenu, EDX
        MOV      [EAX].TControl.fTextColor, clHighlight
        MOV      [EAX].TControl.fCommandActions.aSetBkColor, PBM_SETBKCOLOR
end;

function NewProgressbarEx( AParent: PControl; Options: TProgressbarOptions ): PControl;
asm
        PUSH     EDX
        CALL     NewProgressbar
        POP      ECX
        XOR      EDX, EDX
        SHR      ECX, 1
        JNC      @@notVert
        MOV      DL, 4
@@notVert:
        SHR      ECX, 1
        JNC      @@notSmooth
        INC      EDX
@@notSmooth:
        OR       [EAX].TControl.fStyle, EDX
end;

function WndProcNotify( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNE      @@ret_false
        PUSH     ECX
        PUSH     EDX
        MOV      ECX, [EDX].TMsg.lParam
        {$IFDEF USE_PROP}
        PUSH     offset[ID_SELF]
        PUSH     [ECX].TNMHdr.hwndFrom
        CALL     GetProp
        {$ELSE}
        PUSH     GWL_USERDATA
        PUSH     [ECX].TNMHdr.hwndFrom
        CALL     GetWindowLong
        {$ENDIF}
        POP      EDX
        TEST     EAX, EAX
        JZ       @@ret_false_ECX
        MOV      ECX, [EAX].TControl.fHandle
        MOV      [EDX].TMsg.hwnd, ECX
        POP      ECX
        JMP      TControl.EnumDynHandlers
@@ret_false_ECX:
        POP      ECX
@@ret_false:
        XOR      EAX, EAX
end;

function WndProcCommonNotify( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNE      @@ret_false
        PUSH     EBX
        MOV      EBX, [EDX].TMsg.lParam
        MOV      EDX, [EBX].TNMHdr.code

@@chk_nm_click:
        XOR      ECX, ECX
        CMP      EDX, NM_CLICK
        JZ       @@click
        CMP      EDX, NM_RCLICK
        JNE      @@chk_killfocus
        INC      ECX
@@click:
        MOV      [EAX].TControl.fRightClick, CL

        MOV      ECX, [EAX].TControl.fOnClick.TMethod.Code
        JECXZ    @@fin_false
        MOV      EDX, [EAX].TControl.fOnClick.TMethod.Data
        JMP      @@fin_event

@@fin_false:
        POP      EBX
@@ret_false:
        XOR      EAX, EAX
        RET

@@chk_killfocus:
        CMP      EDX, NM_KILLFOCUS
        JNE      @@chk_setfocus
        MOV      ECX, [EAX].TControl.fOnLeave.TMethod.Code
        JECXZ    @@fin_false
        MOV      EDX, [EAX].TControl.fOnLeave.TMethod.Data
        JMP      @@fin_event
@@chk_setfocus:
        CMP      EDX, NM_RETURN
        JE       @@set_focus
        CMP      EDX, NM_SETFOCUS
        JNE      @@fin_false

@@set_focus:
        MOV      ECX, [EAX].TControl.fOnEnter.TMethod.Code
        JECXZ    @@fin_false
        MOV      EDX, [EAX].TControl.fOnEnter.TMethod.Data

@@fin_event:
        XCHG     EAX, EDX
        CALL     ECX
        POP      EBX
        MOV      AL, 1
end;

procedure ApplyImageLists2Control( Sender: PControl );
asm
        PUSHAD
        XCHG     ESI, EAX
        MOVZX    ECX, [ESI].TControl.fCommandActions.aSetImgList
        JECXZ    @@fin
        MOV      EBP, ECX
        XOR      EBX, EBX
        MOV      BL, 32
        XOR      EDI, EDI
@@loo:
        MOV      EAX, ESI
        MOV      EDX, EBX
        CALL     TControl.GetImgListIdx
        TEST     EAX, EAX
        JZ       @@nx
        CALL     TImageList.GetHandle
        PUSH     EAX
        PUSH     EDI
        PUSH     EBP
        PUSH     ESI
        CALL     TControl.Perform
@@nx:
        INC      EDI
        SHR      EBX, 1
        JZ       @@fin
        CMP      BL, 16
        JGE      @@loo
        XOR      EBX, EBX
        JMP      @@loo
@@fin:
        POPAD
end;

procedure ApplyImageLists2ListView( Sender: PControl );
asm
        PUSHAD

        XCHG     ESI, EAX
        PUSH     dword ptr [ESI].TControl.fLVOptions
        MOV      EAX, ESP
        MOV      EDX, offset[ListViewFlags]
        XOR      ECX, ECX
        MOV      CL, 25
        CALL     MakeFlags
        POP      ECX
        PUSH     ECX

        MOV      EDX, [ESI].TControl.fStyle
        //AND      DH, 3
        AND      DX, not $403F
        OR       EDX, EAX

        MOVZX    EAX, [ESI].TControl.fLVStyle
        OR       EDX, [EAX*4 + offset ListViewStyles]

        MOV      EAX, ESI
        CALL     TControl.SetStyle

        MOV      EAX, ESP
        MOV      EDX, offset[ListViewExFlags]
        XOR      ECX, ECX
        MOV      CL, 23
        CALL     MakeFlags
        POP      EDX
        PUSH     EAX
        PUSH     $3FFF
        PUSH     LVM_SETEXTENDEDLISTVIEWSTYLE
        PUSH     ESI
        CALL     TControl.Perform

        POPAD
        CALL     ApplyImageLists2Control
end;

function NewListView( AParent: PControl; Style: TListViewStyle; Options: TListViewOptions;
                      ImageListSmall, ImageListNormal, ImageListState: PImageList ): PControl;
asm
        PUSH     EDX
        PUSH     ECX
        MOVZX    EDX, DL
        MOV      ECX, [EDX*4 + offset ListViewStyles]
        OR       ECX, LVS_SHAREIMAGELISTS or WS_CHILD or WS_VISIBLE or WS_TABSTOP
        MOV      EDX, offset[WC_LISTVIEW]
        PUSH     1
        PUSH     offset[ListViewActions]
        CALL     _NewCommonControl

        MOV      EDX, ESP
        PUSH     EAX
        XCHG     EAX, EDX
        MOV      EDX, offset ListViewFlags
        XOR      ECX, ECX
        MOV      CL, 25
        CALL     MakeFlags
        XCHG     EDX, EAX
        POP      EAX
        MOV      ECX, [EAX].TControl.fStyle
        AND      ECX, not LVS_TYPESTYLEMASK
        OR       EDX, ECX
        MOV      [EAX].TControl.fStyle, EDX

        POP      [EAX].TControl.fLVOptions
        POP      EDX
        MOV      [EAX].TControl.fLVStyle, DL
        MOV      [EAX].TControl.fCreateWndExt, offset[ApplyImageLists2ListView]
        ADD      [EAX].TControl.fBoundsRect.Right, 200-64
        ADD      [EAX].TControl.fBoundsRect.Bottom, 150-64
        MOV      ECX, [ImageListState]
        XOR      EDX, EDX
        PUSHAD
        CALL     TControl.SetImgListIdx
        POPAD
        MOV      ECX, [ImageListSmall]
        MOV      DL, 16
        PUSHAD
        CALL     TControl.SetImgListIdx
        POPAD
        MOV      ECX, [ImageListNormal]
        ADD      EDX, EDX
        PUSH     EAX
        CALL     TControl.SetImgListIdx
        POP      EAX
        MOV      [EAX].TControl.fLVTextBkColor, clWindow
        XOR      EDX, EDX
        INC      EDX
        MOV      [EAX].TControl.fLookTabKeys, DL
end;

{$IFDEF ASM_UNICODE}
function WndProcTreeView( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //cmd    //opd
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNZ      @@ret_false
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EDX, [EDX].TMsg.lParam
        LEA      EAX, [EBX].TControl.fOnTVBeginDrag
        CMP      word ptr [EDX].TNMTreeView.hdr.code, NM_RCLICK
        JNE      @@chk_TVN_BEGINDRAG
        PUSH     ECX
        PUSH     ECX
        PUSH     ESP
        CALL     GetCursorPos
        MOV      EAX, EBX
        MOV      EDX, ESP
        MOV      ECX, EDX
        CALL     TControl.Screen2Client
        POP      EAX
        AND      EAX, $FFFF
        POP      EDX
        SHL      EDX, 16
        OR       EAX, EDX
        PUSH     EAX
        CALL     GetShiftState
        PUSH     EAX
        PUSH     WM_RBUTTONUP
        PUSH     [EBX].TControl.fHandle
        CALL     PostMessage
        JMP      @@2fin_false1

@@chk_TVN_BEGINDRAG:
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINDRAGW
        JZ       @@event_drag
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINRDRAGW
        JZ       @@event_drag
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINDRAG
        JZ       @@event_drag
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINRDRAG
        JNZ      @@chk_BEGINLABELEDIT
@@event_drag:
        MOV      EDX, [EDX].TNMTreeView.itemNew.hItem
@@event_call:
        MOV      ECX, [EAX].TMethod.Code
        JECXZ    @@2fin_false1
        MOV      EAX, [EAX].TMethod.Data
        XCHG     EBX, ECX
        XCHG     EDX, ECX
        CALL     EBX
@@2fin_false1:   JMP      @@fin_false
@@chk_BEGINLABELEDIT:
        LEA      EAX, [EBX].TControl.fOnTVBeginEdit
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINLABELEDITW
        JZ       @@beginlabeledit
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_BEGINLABELEDIT
        JNZ      @@chk_ITEMEXPANDED //@@chk_DELETEITEM
@@beginlabeledit:

        CMP      [EBX].TControl.fDragging, 0
        JZ       @@allow_LABELEDIT
        XOR      EAX, EAX
        INC      EAX
        MOV      [ECX], EAX
        JMP      @@ret_true

@@allow_LABELEDIT:
        PUSH     ECX // @Rslt

        MOV      ECX, [EAX].TMethod.Code
        JECXZ    @@2fin_false1
        PUSH     EBX
        XCHG     EBX, ECX
        MOV      EDX, [EDX].TTVDispInfo.item.hItem
        XCHG     EDX, ECX
        MOV      EAX, [EAX].TMethod.Data
        CALL     EBX
        TEST     AL, AL
        SETZ     AL        // Rslt := not event result;
        POP      EBX
        JZ       @@ret_EAX
        INC      [EBX].TControl.fEditing
        JMP      @@ret_EAX

@@call_EBX:
        CALL     EBX
@@2fin_false:
        JMP      @@fin_false
@@chk_ITEMEXPANDED:
        LEA      EAX, [EBX].TControl.fOnTVExpanded
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ITEMEXPANDEDW
        JZ       @@itemexpanded
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ITEMEXPANDED
        JNZ      @@chk_SELCHANGING
@@itemexpanded:
        MOV      ECX, [EAX].TMethod.Code
        JECXZ    @@2fin_false
        CMP      [EDX].TNMTreeView.action, TVE_EXPAND
        PUSH     ECX
        SETZ     CL
        XCHG     ECX, [ESP]
        JMP      @@event_drag
@@chk_SELCHANGING:
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_SELCHANGING
        JNE      @@chk_ITEMEXPANDING
        XCHG     EAX, ECX
        MOV      ECX, [EBX].TControl.fOnTVSelChanging.TMethod.Code
@@2fin_false2:
        JECXZ    @@2fin_false
        PUSH     EAX  //@Rslt
        PUSH     [EDX].TNMTreeView.itemNew.hItem
        XCHG     ECX, EBX //EBX=OnTVSelChanging.Code ECX=Sender
        XCHG     ECX, EDX //EDX=Sender ECX=Msg
        MOV      ECX, [ECX].TNMTreeView.itemOld.hItem
        MOV      EAX, [EDX].TControl.fOnTVSelChanging.TMethod.Data
        CALL     EBX
        XOR      AL, 1
        MOVZX    EAX, AL
        JMP      @@ret_EAX

@@chk_ITEMEXPANDING:
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ITEMEXPANDINGW
        JZ       @@itemexpanding
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ITEMEXPANDING
        JNE      @@chk_ENDLABELEDIT
@@itemexpanding:
        XCHG     EAX, ECX
        MOV      ECX, [EBX].TControl.fOnTVExpanding.TMethod.Code
        JECXZ    @@2fin_false2
        PUSH     EAX // @Rslt
        CMP      [EDX].TNMTreeView.action, TVE_EXPAND
        PUSH     ECX
        SETZ     CL
        XCHG     ECX, [ESP]
        XCHG     ECX, EBX  //EBX=OnTVExpanding.Code ECX=Seneder
        XCHG     EDX, ECX  //ECX=Msg EDX=Sender
        MOV      ECX, [ECX].TNMTreeView.itemNew.hItem //ECX=Item
        MOV      EAX, [EDX].TControl.fOnTVExpanding.TMethod.Data //EAX=object
@@111:
        CALL     EBX
@@ret_EAX:
        POP      EDX //EDX=@Rslt
        MOVZX    EAX, AL
        NEG      EAX
        MOV      [EDX], EAX
@@ret_true:
        MOV      AL, 1
        POP      EBX
        RET
@@chk_ENDLABELEDIT:
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ENDLABELEDITW
        JZ       @@endlabeledit
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_ENDLABELEDIT
        JNZ      @@chk_SELCHANGED
@@endlabeledit:
        MOV      [EBX].TControl.fEditing, 0
        XCHG     EAX, ECX
        MOV      ECX, [EBX].TControl.fOnTVEndEdit.TMethod.Code
        JECXZ    @@ret_1
        PUSH     EAX
        PUSH     EBX
        PUSH     0

        XCHG     EDX, EBX
        MOV      EAX, [EBX].TTVDispInfo.item.pszText
        PUSH     EDX
        PUSH     ECX
        XCHG     EAX, EDX
        {$IFDEF UNICODE_CTRLS}
        CMP      [EBX].TNMTreeView.hdr.code, TVN_ENDLABELEDITW
        JNZ      @@endlabeleditA
        CALL     TControl.TVGetItemTextW
        JMP      @@NewTxt_ready
@@endlabeleditA:
        {$ENDIF UNICODE_CTRLS}
        TEST     EDX, EDX
        JNZ      @@prepare_NewTxt
        // NewTxt := [EDX].TControl.TVItemText[ hItem ]
        LEA      ECX, [ESP + 8]
        MOV      EDX, [EBX].TTVDispInfo.item.hItem
        CALL     TControl.TVGetItemText
        JMP      @@NewTxt_ready
@@prepare_NewTxt:
        LEA      EAX, [ESP+8]
        CALL     System.@LStrFromPChar
@@NewTxt_ready:
        POP      ECX
        POP      EDX
        POP      EAX
        PUSH     EAX
        PUSH     EAX
        MOV      EAX, [EDX].TControl.fOnTVEndEdit.TMethod.Data
        MOV      EBX, [EBX].TTVDispInfo.item.hItem
        XCHG     ECX, EBX
        CALL     EBX
        XCHG     EBX, EAX
        CALL     RemoveStr
        XCHG     EAX, EBX
        POP      EBX
        JMP      @@ret_EAX
@@ret_1:
        INC      ECX
        MOV      [EAX], ECX
        JMP      @@ret_true

@@chk_SELCHANGED:
        {$IFDEF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_SELCHANGEDW
        JZ       @@selchanged
        {$ENDIF UNICODE_CTRLS}
        CMP      word ptr [EDX].TNMTreeView.hdr.code, TVN_SELCHANGED
        JNZ      @@fin_false
@@selchanged:
        XCHG     EAX, EBX
        CALL     TControl.DoSelChange

@@fin_false:
        POP      EBX
@@ret_false:
        XOR      EAX, EAX
end;
{$ENDIF ASM_UNICODE}

function NewTreeView( AParent: PControl; Options: TTreeViewOptions;
                      ImgListNormal, ImgListState: PImageList ): PControl;
asm     //cmd    //opd
        PUSH     EBX
        PUSH     ECX
        PUSH     EAX
        PUSH     EDX
        MOV      EAX, ESP
        MOV      EDX, offset[TreeViewFlags]
        XOR      ECX, ECX
        MOV      CL, 13
        CALL     MakeFlags
        POP      EDX
        OR       EAX, WS_VISIBLE or WS_CHILD or WS_TABSTOP
        XCHG     ECX, EAX
        POP      EAX
        MOV      EDX, offset[WC_TREEVIEW]
        PUSH     1
        PUSH     offset[TreeViewActions]
        CALL     _NewCommonControl
        MOV      EBX, EAX
        MOV      [EBX].TControl.fCreateWndExt, offset[ApplyImageLists2Control]
        MOV      [EBX].TControl.fColor, clWindow
        MOV      EDX, offset[WndProcTreeView]
        CALL     TControl.AttachProc
        ADD      [EBX].TControl.fBoundsRect.Right, 150-64
        ADD      [EBX].TControl.fBoundsRect.Bottom, 200-64
        MOV      EAX, EBX
        XOR      EDX, EDX
        MOV      DL, 32
        POP      ECX // ImageListNormal
        CALL     TControl.SetImgListIdx
        MOV      EAX, EBX
        XOR      EDX, EDX
        MOV      ECX, [ImgListState]
        CALL     TControl.SetImgListIdx
        MOV      byte ptr [EBX].TControl.fLookTabKeys, 1
        XCHG     EAX, EBX
        POP      EBX
end;

function WndProcTabControl( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //cmd    //opd
{$IFDEF OLD_ALIGN}
        PUSH     EBP
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        MOV      EBX, EAX
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNZ      @@chk_WM_SIZE
        MOV      EDX, [EDX].TMsg.lParam
//!!!
        CMP      word ptr [EDX].TNMHdr.code, TCN_SELCHANGING
        JNZ      @@chk_TCN_SELCHANGE
        CALL     TControl.GetCurIndex
        MOV      [EBX].TControl.fCurIndex, EAX
        JMP      @@ret_false
@@chk_TCN_SELCHANGE:
        CMP      word ptr [EDX].TNMHdr.code, TCN_SELCHANGE
        JNZ      @@ret_false

        CALL     TControl.GetCurIndex
        XCHG     EDI, EAX
        CMP      EDI, [EBX].TControl.fCurIndex
        PUSHFD   // WasActive = ZF

        MOV      [EBX].TControl.FCurIndex, EDI

        MOV      EAX, EBX
        CALL     TControl.GetItemsCount
        XCHG     ESI, EAX // ESI := Self_.Count

@@loo:  DEC      ESI
        JS       @@e_loo
        MOV      EDX, ESI
        MOV      EAX, EBX
        CALL     TControl.GetPages

        CMP      ESI, EDI
        PUSH     EAX
        SETZ     DL
        CALL     TControl.SetVisible
        POP      EAX
        CMP      ESI, EDI
        JNE      @@nx_loo
        CALL     TControl.BringToFront
@@nx_loo:
        JMP      @@loo
@@e_loo:
        POPFD
        JZ       @@ret_false

        MOV      ECX, [EBX].TControl.fOnSelChange.TMethod.Code
        JECXZ    @@ret_false
        MOV      EDX, EBX
        MOV      EAX, [EBX].TControl.fOnSelChange.TMethod.Data
        CALL     ECX
        JMP      @@ret_false
@@chk_WM_SIZE:
        CMP      word ptr [EDX].TMsg.message, WM_SIZE
        JNE      @@ret_false
        ADD      ESP, -16
        PUSH     ESP
        PUSH     [EBX].TControl.fHandle
        CALL     Windows.GetClientRect
        PUSH     ESP
        PUSH     0
        PUSH     TCM_ADJUSTRECT
        PUSH     EBX
        CALL     TControl.Perform
        MOV      EAX, EBX
        CALL     TControl.GetItemsCount
        XCHG     ESI, EAX
@@loo2:
        DEC      ESI
        JS       @@e_loo2
        MOV      EDX, ESI
        MOV      EAX, EBX
        CALL     TControl.GetPages
        MOV      EDX, ESP
        CALL     TControl.SetBoundsRect
        JMP      @@loo2
@@e_loo2:
        ADD      ESP, 16
@@ret_false:
        XOR      EAX, EAX
        POP      EDI
        POP      ESI
        POP      EBX
        POP      EBP
{$ELSE NEW_ALIGN}
        PUSH     EBX
        MOV      EBX, EAX
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNZ      @@chk_WM_SIZE
        MOV      EDX, [EDX].TMsg.lParam

        CMP      word ptr [EDX].TNMHdr.code, TCN_SELCHANGING
        JNZ      @@chk_TCN_SELCHANGE
        CALL     TControl.GetCurIndex
        MOV      [EBX].TControl.fCurIndex, EAX
        JMP      @@ret_false
@@chk_TCN_SELCHANGE:
        CMP      word ptr [EDX].TNMHdr.code, TCN_SELCHANGE
        JNZ      @@ret_false
        CALL     TControl.GetCurIndex
        MOV      EDX, [EBX].TControl.fCurIndex
        MOV      [EBX].TControl.fCurIndex, EAX
        CMP      EAX, EDX
        PUSHFD   // WasActive = ZF
        BT       EDX,31
        JBE      @@00
        MOV      EAX, EBX
        CALL     TControl.GetPages
        XOR      EDX,EDX
        CALL     TControl.SetVisible
@@00:
        MOV      EDX, [EBX].TControl.fCurIndex
        MOV      EAX, EBX
        CALL     TControl.GetPages
        MOV      DL,1
        PUSH     EAX
        CALL     TControl.SetVisible
        POP      EAX
        CALL     TControl.BringToFront
        POPFD
        JZ       @@ret_false
        MOV      ECX, [EBX].TControl.fOnSelChange.TMethod.Code
        JECXZ    @@ret_false
        MOV      EDX, EBX
        MOV      EAX, [EBX].TControl.fOnSelChange.TMethod.Data
        CALL     ECX
        JMP      @@ret_false
@@chk_WM_SIZE:
        CMP      word ptr [EDX].TMsg.message, WM_SIZE
        JNE      @@ret_false
        SUB      ESP, 10h
        PUSH     ESP
        PUSH     [EBX].TControl.fHandle
        CALL     Windows.GetClientRect
        MOV      EAX,[ESP].TRect.Right
        MOV      [EBX].TControl.fClientRight,EAX
        MOV      EAX,[ESP].TRect.Bottom
        MOV      [EBX].TControl.fClientBottom,EAX
        PUSH     ESP
        PUSH     0
        PUSH     TCM_ADJUSTRECT
        PUSH     EBX
        CALL     TControl.Perform
        POP      EAX
        MOV      [EBX].TControl.fClientLeft,EAX
        POP      EAX
        MOV      [EBX].TControl.fClientTop,EAX
        POP      EAX
        SUB      [EBX].TControl.fClientRight,EAX
        POP      EAX
        SUB      [EBX].TControl.fClientBottom,EAX
@@ret_false:
        XOR      EAX, EAX
        POP      EBX
{$ENDIF}
end;

{$IFDEF ASM_UNICODE}
function NewTabControl( AParent: PControl; const Tabs: array of PKOLChar; Options: TTabControlOptions;
         ImgList: PImageList; ImgList1stIdx: Integer ): PControl;
const lenf=high(TabControlFlags); //+++
asm     //cmd    //opd
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        XCHG     EBX, EAX
        PUSH     EDX
        PUSH     ECX
        LEA      EAX, [Options]
        MOV      EDX, offset[TabControlFlags]
        XOR      ECX, ECX
        MOV      CL, lenf
        CALL     MakeFlags
        TEST     byte ptr [Options], 4
        JZ       @@0
        OR       EAX, WS_TABSTOP or TCS_FOCUSONBUTTONDOWN
@@0:    OR       EAX, WS_CHILD or WS_CLIPSIBLINGS or WS_CLIPCHILDREN or WS_VISIBLE
        XCHG     ECX, EAX
        XCHG     EAX, EBX
        MOV      EDX, offset[WC_TABCONTROL]
        PUSH     1
        PUSH     offset[TabControlActions]
        CALL     _NewCommonControl
        MOV      EBX, EAX
        TEST     [Options], 2 shl (tcoBorder - 1)
        JNZ      @@borderfixed
        AND      [EBX].TControl.fExStyle, not WS_EX_CLIENTEDGE
@@borderfixed:
        MOV      EDX, offset[WndProcTabControl]
        CALL     TControl.AttachProc
        ADD      [EBX].TControl.fBoundsRect.Right, 100-64
        ADD      [EBX].TControl.fBoundsRect.Bottom, 100-64
        MOV      ECX, [ImgList]
        JECXZ    @@2
        XCHG     EAX, ECX
        CALL     TImageList.GetHandle
        PUSH     EAX
        PUSH     0
        PUSH     TCM_SETIMAGELIST
        PUSH     EBX
        CALL     TControl.Perform
@@2:
        POP      EDI // EDI = High(Tabs)
        POP      ESI // ESI = Tabs
        XOR      EDX, EDX // EDX := 0 (=I)
        MOV      EAX, [ImgList1stIdx] //(=II)
@@loop:
        CMP      EDX, EDI
        JG       @@e_loop
        PUSH     EAX
        PUSH     EDX
        PUSH     EAX
        LODSD
        XCHG     ECX, EAX
        MOV      EAX, EBX
        CALL     TControl.TC_Insert
        POP      EDX
        POP      EAX
        INC      EAX
        INC      EDX
        JMP      @@loop
@@e_loop:
        MOV      byte ptr [EBX].TControl.fLookTabKeys, 1
        XCHG     EAX, EBX
        POP      EDI
        POP      ESI
        POP      EBX
end;
{$ENDIF}

{$IFNDEF OLD_ALIGN}
function NewTabEmpty( AParent: PControl; Options: TTabControlOptions;
         ImgList: PImageList ): PControl;
const lenf=high(TabControlFlags); //+++
asm     //cmd    //opd
        PUSH     EBX
        MOV      EBX, EAX
        PUSH     ECX
        PUSH     EDX
        MOV      EAX, ESP
        MOV      EDX, offset[TabControlFlags]
        XOR      ECX, ECX
        MOV      CL, lenf
        CALL     MakeFlags
        TEST     byte ptr [ESP], 4
        JZ       @@0
        OR       EAX, WS_TABSTOP or TCS_FOCUSONBUTTONDOWN
@@0:    OR       EAX, WS_CHILD or WS_CLIPSIBLINGS or WS_CLIPCHILDREN or WS_VISIBLE
        XCHG     ECX, EAX
        XCHG     EAX, EBX
        MOV      EDX, offset[WC_TABCONTROL]
        PUSH     1
        PUSH     offset[TabControlActions]
        CALL     _NewCommonControl
        MOV      EBX, EAX
        POP      ECX //Options
        TEST     ECX, 2 shl (tcoBorder - 1)
        JNZ      @@borderfixed
        AND      [EBX].TControl.fExStyle, not WS_EX_CLIENTEDGE
@@borderfixed:
        MOV      EDX, offset[WndProcTabControl]
        CALL     TControl.AttachProc
        ADD      [EBX].TControl.fBoundsRect.Right, 100-64
        ADD      [EBX].TControl.fBoundsRect.Bottom, 100-64
        POP      ECX //ImgList
        JECXZ    @@2
        XCHG     EAX, ECX
        CALL     TImageList.GetHandle
        PUSH     EAX
        PUSH     0
        PUSH     TCM_SETIMAGELIST
        PUSH     EBX
        CALL     TControl.Perform
@@2:
        MOV      byte ptr [EBX].TControl.fLookTabKeys, 1
        XCHG     EAX, EBX
        POP      EBX
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
function NewToolbar( AParent: PControl; Align: TControlAlign; Options: TToolbarOptions;
                     Bitmap: HBitmap; const Buttons: array of PKOLChar;
                     const BtnImgIdxArray: array of Integer ) : PControl;
const szTBButton = Sizeof( TTBButton );
      Option3DBorder = 1 shl Ord( tbo3DBorder );
asm     //cmd    //opd
   PUSH EDI
        MOVZX    EDX, DL
        PUSH     EDX // Align
        PUSH     EAX // AParent

        XOR      EAX, EAX
        TEST     CL, Option3DBorder
        SETNZ    AL
        PUSH     EAX

        PUSH     ECX // Options

        MOV      AL, ICC_BAR_CLASSES
        CALL     DoInitCommonControls

        MOV      EAX, ESP
        MOV      EDX, offset[ToolbarOptions]
        XOR      ECX, ECX
        MOV      CL, 6
        CALL     MakeFlags
        POP      EDX

        PUSH     0
        XCHG     ECX, EAX // ECX = MakeFlags(...)
   MOV  EDI, ECX
        MOV      EAX, [ESP+8] // EAX = AParent
        MOV      EDX, [ESP+12] // EDX = Align
        OR       ECX, [EDX*4+offset ToolbarAligns]
        OR       ECX, WS_CHILD or WS_VISIBLE or TBSTYLE_TOOLTIPS
        MOV      EDX, offset[ TOOLBARCLASSNAME ]
        CALL     _NewCommonControl
        MOV      [EAX].TControl.fCommandActions.aClear, offset[ClearToolbar]
        MOV      [EAX].TControl.fCommandActions.aGetCount, TB_BUTTONCOUNT
        INC      [EAX].TControl.fIsButton
        POP      EDX // pop AParent
        POP      EDX // EDX = Align
        PUSH     EDX
        TEST     EDX, EDX
        JE       @@zero_bounds
        ADD      [EAX].TControl.fBoundsRect.Bottom, 26-64
        ADD      [EAX].TControl.fBoundsRect.Right, 1000-64
        JMP      @@bounds_ready
@@zero_bounds:
        MOV      [EAX].TControl.fBoundsRect.Left, EDX
        MOV      [EAX].TControl.fBoundsRect.Top, EDX
        MOV      [EAX].TControl.fBoundsRect.Right, EDX
        MOV      [EAX].TControl.fBoundsRect.Bottom, EDX
@@bounds_ready:
        PUSH     EBX
        PUSH     ESI
        XCHG     EBX, EAX
        MOV      ESI, offset[TControl.Perform]
        PUSH     0
        PUSH     0
        PUSH     TB_GETEXTENDEDSTYLE
        PUSH     EBX
        CALL     ESI
        OR       EAX, TBSTYLE_EX_DRAWDDARROWS
        PUSH     EAX
        PUSH     0
        PUSH     TB_SETEXTENDEDSTYLE
        PUSH     EBX
        CALL     ESI
        MOV      EDX, offset[WndProcToolbarCtrl]
        MOV      EAX, EBX
        CALL     TControl.AttachProc
        MOV      EDX, offset[WndProcDoEraseBkgnd]
        MOV      EAX, EBX
        CALL     TControl.AttachProc
        PUSH     0
        PUSH     szTBButton
        PUSH     TB_BUTTONSTRUCTSIZE
        PUSH     EBX
        CALL     ESI
        PUSH     0
        PUSH     [EBX].TControl.fMargin
        PUSH     TB_SETINDENT
        PUSH     EBX
        CALL     ESI
        MOV      EAX, [ESP+8] // Align
        {$IFDEF PARANOIA} DB $2C, 1 {$ELSE} SUB AL, 1 {$ENDIF}
        JL       @@bounds_correct
        JE       @@corr_right
        {$IFDEF PARANOIA} DB $2C, 2 {$ELSE} SUB AL, 2 {$ENDIF}
        JNE      @@corr_bottom
@@corr_right:
        MOV      EDX, [EBX].TControl.fBoundsRect.Left
        ADD      EDX, 24
        MOV      [EBX].TControl.fBoundsRect.Right, EDX
        JMP      @@bounds_correct
@@corr_bottom:
        MOV      EDX, [EBX].TControl.fBoundsRect.Top
        ADD      EDX, 22
        MOV      [EBX].TControl.fBoundsrect.Bottom, EDX
@@bounds_correct:
        MOV      EDX, [Bitmap]
        TEST     EDX, EDX
        JZ       @@bitmap_added
        MOV      EAX, EBX
        CALL     TControl.TBAddBitmap
@@bitmap_added:

        PUSH     dword ptr [BtnImgIdxArray]
        PUSH     dword ptr [BtnImgIdxArray-4]
        MOV      ECX, [Buttons-4]
        MOV      EDX, [Buttons]
        MOV      EAX, EBX
        CALL     TControl.TBAddButtons

        PUSH     0
        PUSH     0
        PUSH     WM_SIZE
        PUSH     EBX
        CALL     ESI
// ---
{+|ecm|}
// ---
        MOV      EDX,EDI
        OR       EDX,[EBX].TControl.FStyle
        MOV      EAX,EBX
        CALL     TControl.SetStyle
//  ---
{/+|ecm|}
//  ---
        XCHG     EAX, EBX
        POP      ESI
        POP      EBX
        POP      EDX
   POP  EDI
end;
{$ENDIF ASM_UNICODE}

{$IFNDEF NOT_USE_RICHEDIT}
function WndProc_RE_LinkNotify( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, WM_NOTIFY
        JNE      @@ret_false
        MOV      EDX, [EDX].TMsg.lParam
        CMP      [EDX].TNMHdr.code, EN_LINK
        JNE      @@ret_false
        PUSH     EBX
        PUSH     EDX
        XCHG     EBX, EAX
        XOR      EAX, EAX
        MOV      [ECX], EAX
        {$IFDEF UNICODE_CTRLS}
        ADD      ESP, -2040
        {$ELSE}
        ADD      ESP, -1020
        {$ENDIF}
        PUSH     EAX
        PUSH     ESP
        PUSH     [EDX].TENLink.chrg.cpMax
        PUSH     [EDX].TENLink.chrg.cpMin
        PUSH     ESP
        PUSH     0
        PUSH     EM_GETTEXTRANGE
        PUSH     EBX
        CALL     TControl.Perform
        LEA      EAX, [EBX].TControl.fREUrl

        POP      EDX
        POP      ECX
        DEC      EDX
        CMP      ECX, EDX
        POP      ECX
        MOV      EDX, ESP
        JLE      @@1
        CMP      byte ptr [EDX+1], 0
        JNZ      @@1
        // система вернула текст как unicode
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrFromPWChar
        {$ELSE not UNICODE_CTRLS}
        {$IFDEF  _D2}
        CALL     LStrFromPWChar
        {$ELSE}
        CALL     System.@LStrFromPWChar
        {$ENDIF}
        {$ENDIF UNICODE_CTRLS}
        JMP      @@2
@@1:
        // система вернула текст как обычную строку
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrFromPChar
        {$ELSE not UNICODE_CTRLS}
        CALL     System.@LStrFromPChar
        {$ENDIF UNICODE_CTRLS}
@@2:
        {$IFDEF UNICODE_CTRLS}
        ADD      ESP, 2044
        {$ELSE not UNICODE_CTRLS}
        ADD      ESP, 1024
        {$ENDIF UNICODE_CTRLS}
        POP      EDX
        MOV      ECX, [EDX].TENLink.msg
        LEA      EAX, [EBX].TControl.fOnREOverURL
        CMP      ECX, WM_MOUSEMOVE
        JE       @@Url_event
        LEA      EAX, [EBX].TControl.fOnREUrlClick
        CMP      ECX, WM_LBUTTONDOWN
        JE       @@Url_Event
        CMP      ECX, WM_RBUTTONDOWN
        JNE      @@after_Url_event
@@Url_event:
        MOV      ECX, [EAX].TMethod.Code
        JECXZ    @@after_Url_event
        MOV      EDX, EBX
        MOV      EAX, [EAX].TMethod.Data
        CALL     ECX
@@after_Url_event:
        POP      EBX
        MOV      AL, 1
        RET
@@ret_false:
        XOR      EAX, EAX
end;

{$IFDEF ASM_UNICODE}
function NewRichEdit1( AParent: PControl; Options: TEditOptions ): PControl;
const
  RichNamesCount = High( RichEditLibnames ) + 1;
asm
        PUSH     EDX

        MOV      ECX, [FRichEditModule]
        INC      ECX
        LOOP     @@loaded
        PUSHAD
        {$IFNDEF SMALLEST_CODE}
        {$IFNDEF SMALLER_CODE}
        PUSH     SEM_NOOPENFILEERRORBOX or SEM_FAILCRITICALERRORS
        CALL     SetErrorMode
        PUSH     EAX
        {$ENDIF}
        {$ENDIF}
@@search_richedit:
        MOV      BX, RichNamesCount + $400
        LEA      ESI, [RichEditLibNames]
        LEA      EDI, [RichEditClasses]
        CMP      [RichEditIdx], 0
        JZ       @@loo
        LEA      ESI, [ESI+(RichNamesCount-1)*4]
        LEA      EDI, [EDI+(RichNamesCount-1)*4]
        NEG      BH
@@loo:
        MOV      ECX, [EDI]
        MOV      [RichEditClass], ECX
        MOVSX    ECX, BH
        ADD      EDI, ECX
        MOV      EAX, [ESI]
        ADD      ESI, ECX
        PUSH     EAX
        CALL     LoadLibrary
        CMP      EAX, HINSTANCE_ERROR
        JG       @@break
        DEC      BL
        JNZ      @@loo
        JMP      @@fault
@@break:
        MOV      [FRichEditModule], EAX
@@fault:
        {$IFNDEF SMALLEST_CODE}
        {$IFNDEF SMALLER_CODE}
        CALL     SetErrorMode
        {$ENDIF}
        {$ENDIF}
        POPAD
@@loaded:
        PUSH     EAX
        PUSH     EDX
        MOV      EAX, ESP
        MOV      EDX, offset[RichEditFlags]
        XOR      ECX, ECX
        MOV      CL, 10
        CALL     MakeFlags
        XCHG     ECX, EAX
        POP      EDX
        POP      EAX
        PUSH     1
        PUSH     offset[RichEditActions]
        MOV      EDX, [RichEditClass]
        OR       ECX, WS_VISIBLE or WS_CHILD or WS_TABSTOP or WS_BORDER or ES_MULTILINE
        CALL     _NewCommonControl
        INC      [EAX].TControl.fIgnoreDefault
        POP      EDX
        TEST     DH, 4 // is eoWantTab in Options ?
        SETZ     DL
        MOV      [EAX].TControl.fLookTabKeys, DL
        PUSH     EBX
        MOV      EBX, EAX
        MOV      EDX, offset[WndProcRichEditNotify]
        CALL     TControl.AttachProc
        MOV      [EBX].TControl.fDoubleBuffered, 0
        INC      [EBX].TControl.fCannotDoubleBuf
        ADD      [EBX].TControl.fBoundsRect.Right, 100-64
        ADD      [EBX].TControl.fBoundsRect.Bottom, 200-64
        PUSH     ENM_CHANGE or ENM_SELCHANGE or ENM_REQUESTRESIZE or ENM_PROTECTED or $04000000
        PUSH     0
        PUSH     EM_SETEVENTMASK
        PUSH     EBX
        CALL     TControl.Perform
        MOV      EAX, clWindow
        MOV      [EBX].TControl.fColor, EAX
        CALL     Color2RGB
        PUSH     EAX
        PUSH     0
        PUSH     EM_SETBKGNDCOLOR
        PUSH     EBX
        CALL     TControl.Perform
        {$IFDEF RICHEDIT_XPBORDER}
        MOV      EDX, offset[WndProc_RichEditXPBorder]
        MOV      EAX, EBX
        CALL     TControl.AttachProc
        {$ENDIF RICHEDIT_XPBORDER}
        XCHG     EAX, EBX
        POP      EBX
end;
{$ENDIF ASM_UNICODE}
{$ENDIF NOT_USE_RICHEDIT}

function OleInit: Boolean;
asm
        MOV      ECX, [OleInitCount]
        INC      ECX
        LOOP     @@init1
        PUSH     ECX
        CALL     OleInitialize
        TEST     EAX, EAX
        MOV      AL, 0
        JNZ      @@exit
@@init1:
        INC      [OleInitCount]
        MOV      AL, 1
@@exit:
end;

procedure OleUnInit;
asm
        MOV      ECX, [OleInitCount]
        JECXZ    @@exit
        DEC      [OleInitCount]
        JNZ      @@exit
        CALL     OleUninitialize
@@exit:
end;

procedure TControl.Init;
const
  IniStyle = WS_VISIBLE or WS_CLIPCHILDREN or WS_CLIPSIBLINGS or
            WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX or WS_MAXIMIZEBOX or
            WS_BORDER or WS_THICKFRAME;
asm     //cmd    //opd
        PUSH     EBX
        PUSH     EDI
        MOV      EBX, EAX
        {$IFDEF _D2orD3}
        CALL     TObj.Init // for now, TObj.Init do nothing for Delphi 4 and higher
        {$ENDIF}
        {$IFDEF USE_GRAPHCTLS}
        MOV      [EBX].fDoInvalidate.TMethod.Code, offset[TControl.InvalidateWindowed]
        MOV      [EBX].fDoInvalidate.TMethod.Data, EBX
        {$ENDIF}
        MOV      EAX, offset WndProcDummy
        LEA      EDI, [EBX].fPass2DefProc
        STOSD    // fPass2DefProc := WndProcDummy
        STOSD    // fOnDynHandlers := WndProcDummy
        STOSD    // fWndProcKeybd := WndProcDummy
        STOSD    // fControlClick := WndProcDummy - similar to DefWindowProc
        STOSD    // fAutoSize := WndProcDummy - similar to DefWindowProc
        LEA      EDI, [EBX].fWndProcResizeFlicks
        STOSD

        MOV      [EBX].fWndFunc, offset WndFunc
        MOV      EDX, offset ClearText
        MOV      [EBX].fCommandActions.aClear, EDX
        INC      [EBX].fWindowed
        MOV      [EBX].fColor, clBtnFace
        MOV      [EBX].fTextColor, clWindowText and $FF
        MOV      byte ptr [EBX].fMargin, 2
        INC      dword ptr [EBX].fCtl3Dchild
        {$IFDEF SMALLEST_CODE}
        {$ELSE}
        INC      dword ptr [EBX].fCtl3D        // anyway assigned in _NewWindowed
        DEC      byte ptr [EBX].fAlphaBlend    // has no effect until AlphaBlend changed
        {$ENDIF}
        MOV      byte ptr[EBX].fClsStyle, CS_OWNDC
        MOV      [EBX].fStyle, IniStyle
        INC      dword ptr[EBX].fExStyle+2
        DEC      WORD PTR [EBX].fEnabled

        LEA      EDI, [EBX].fDynHandlers
        MOV      EBX, offset[NewList]
        CALL     EBX
        STOSD
        CALL     EBX
        STOSD

        POP      EDI
        POP      EBX
end;

procedure CallTControlInit( Ctl: PControl );
begin
  Ctl.Init;
end;
//[END CallTControlInit]

//[procedure TControl.InitParented]
procedure TControl.InitParented( AParent: PControl );
const IStyle = WS_VISIBLE or WS_CLIPCHILDREN or WS_CLIPSIBLINGS or
            WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX or WS_MAXIMIZEBOX or
            WS_BORDER or WS_THICKFRAME;
      IExStyle = WS_EX_CONTROLPARENT;
      IClsStyle = CS_OWNDC;
      int_IDC_ARROW = integer( IDC_ARROW );
asm
        PUSH      EAX
        PUSH      EDX
        //CALL      CallTControlInit
        mov EDX, [EAX]
        call dword ptr [EDX]

        POP       EDX
        POP       EAX
        TEST      EDX, EDX
        JZ        @@0
        MOV       ECX, [EDX].fColor
        MOV       [EAX].fColor, ECX
@@0:
        CALL      SetParent
end;

destructor TControl.Destroy;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX
        CALL     TControl.ParentForm
        XCHG     ECX, EAX
        JECXZ    @@cur_ctl_removed
        MOV      EDX, EBX
        XOR      EDX, [ECX].TControl.fCurrentControl
        JNE      @@cur_ctl_removed
        MOV      [ECX].TControl.fCurrentControl, EDX
@@cur_ctl_removed:

        MOV      ECX, [EBX].fHandle
        JECXZ    @@wndhidden
        PUSH     SW_HIDE
        PUSH     ECX
        CALL     ShowWindow
@@wndhidden:

        MOV      EAX, EBX
        CALL     Final
        {$IFDEF USE_AUTOFREE4CHILDREN}
        {$ELSE}
        MOV      EAX, EBX
        CALL     DestroyChildren
        {$ENDIF}

        XOR      ECX, ECX
        CMP      [EBX].fDestroying, CL
        JNZ      @@destroyed

        INC      [EBX].fDestroying

        {$IFDEF USE_AUTOFREE4CONTROLS}
        XOR      EAX, EAX
        XCHG     EAX, [EBX].fCanvas
        CALL     TObj.RefDec
        {$ELSE}
        PUSH     EBX
        LEA      ESI, [EBX].fFont
        MOV      BL, 3
@@free_font_brush_canvas:
        XOR      ECX, ECX
        XCHG     ECX, [ESI]
        LODSD
        XCHG     EAX, ECX
        CALL     TObj.RefDec
        DEC      BL
        JNZ      @@free_font_brush_canvas
        POP      EBX
        {$ENDIF}

        MOV      EAX, [EBX].fCustomObj
        CALL     TObj.RefDec

        MOV      EAX, [EBX].fHandle
        TEST     EAX, EAX
        JZ       @@free_fields

        {$IFNDEF USE_AUTOFREE4CONTROLS}
        {$IFNDEF NEW_MENU_ACCELL}
        XOR      ECX, ECX
        XCHG     ECX, [EBX].fAccelTable
        JECXZ    @@accelTable_destroyed
        PUSH     ECX
        CALL     DestroyAcceleratorTable
@@accelTable_destroyed:
        {$ENDIF}
        MOV      EAX, [EBX].fMenuObj
        CALL     TObj.RefDec
@@destroy_img_list:
        XOR      EAX, EAX
        XCHG     EAX, [EBX].fImageList
        TEST     EAX, EAX
        JZ       @@img_list_destroyed
        CALL     TObj.RefDec
        JMP      @@destroy_img_list
@@img_list_destroyed:
        {$ENDIF}

        MOV      ECX, [EBX].fIcon
        JECXZ    @@icoremoved
        INC      ECX
        JZ       @@icoremoved
        CMP      [EBX].fIconShared, 0
        JNZ      @@icoremoved
        DEC      ECX
        PUSH     ECX
        CALL     DestroyIcon
@@icoremoved:

        PUSH     [EBX].fHandle
        CALL     IsWindow
        TEST     EAX, EAX
        JZ       @@destroy2
        {$IFDEF USE_PROP}
        PUSH     offset[ID_SELF] //* Remarked By M.Gerasimov
        PUSH     [EBX].fHandle   //* unremarked to prevent problems with progress bar
        CALL     RemoveProp
        {$ELSE}
        PUSH     0
        PUSH     GWL_USERDATA
        PUSH     [EBX].fHandle
        CALL     SetWindowLong
        {$ENDIF}
        CMP      [EBX].fNCDestroyed, 0
        JNZ      @@destroy2
        //CMP      [EBX].fIsForm, 0
        //JZ       @@destroy2
        PUSH     [EBX].fHandle
        CALL     DestroyWindow
@@destroy2:
        XOR      EAX, EAX
        MOV      [EBX].fHandle, EAX

@@free_fields:
        PUSH     0
        MOVZX    ECX, [EBX].fCtlClsNameChg
        JECXZ    @@notFreeCtlClsName
        PUSH     [EBX].fControlClassName
@@notFreeCtlClsName:
        LEA      ESI, [EBX].fCustomData
        MOV      DL, 2
@@chkFreeLoop:
        LODSD
        XCHG     ECX, EAX
        JECXZ    @@notFree1
        PUSH     ECX
@@notFree1:
        DEC      DL
        JNZ      @@chkFreeLoop
@@FreeFieldsLoop:
        POP      ECX
        JECXZ    @@endFreeFieldsLoop
        XCHG     EAX, ECX
        CALL     System.@FreeMem
        JMP      @@FreeFieldsLoop
@@endFreeFieldsLoop:

        XOR      ECX, ECX
        XCHG     ECX, [EBX].fTmpBrush
        JECXZ    @@tmpBrush_deleted
        PUSH     ECX
        CALL     DeleteObject
@@tmpBrush_deleted:

        MOV      ECX, [EBX].fParent
        JECXZ    @@removed_from_parent
        CMP      [ECX].fCurrentControl, EBX
        JNE      @@removefromParent
        XOR      EAX, EAX
        MOV      [ECX].fCurrentControl, EAX
@@removefromParent:
        {$IFDEF USE_AUTOFREE4CHILDREN}
        PUSH     ECX
        {$ENDIF}
        MOV      EAX, [ECX].fChildren
        MOV      EDX, EBX
        CALL     TList.Remove
        {$IFDEF USE_AUTOFREE4CHILDREN}
        POP      EAX
        MOV      EDX, EBX
        CALL     TControl.RemoveFromAutoFree
        {$ENDIF}
@@removed_from_parent:

        {$IFDEF USE_AUTOFREE4CONTROLS}
        LEA      ESI, [EBX].fDynHandlers
        LODSD
        CALL     TObj.RefDec
        LODSD         // fChildren
        CALL     TObj.RefDec
        {$ELSE}
        PUSH     EBX
        LEA      ESI, [EBX].fDynHandlers
        MOV      BL, 5
@@freeloo:
        LODSD
        CALL     TObj.RefDec
        DEC      BL
        JNZ      @@freeloo
        POP      EBX
        {$ENDIF}

        LEA      EAX, [EBX].fCaption
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        XCHG     EAX, EBX
        CALL     TObj.Destroy
@@destroyed:
        POP      ESI
        POP      EBX
end;

procedure TControl.SetEnabled( Value: Boolean );
asm
        PUSH     EBX
        MOV      EBX, EAX
        MOVZX    EDX, DL
        PUSH     EDX
        CALL     GetEnabled
        POP      EDX
        CMP      AL, DL
        JZ       @@exit
        MOV      [EBX].fEnabled, DL
        TEST     EDX, EDX
        JNZ      @@andnot
        OR       byte ptr [EBX].fStyle + 3, 8
        JMP      @@1
@@andnot:
        AND      byte ptr [EBX].fStyle + 3, $F7
@@1:
        MOV      ECX, [EBX].fHandle
        JECXZ    @@2

        PUSH     EDX
        PUSH     ECX
        CALL     EnableWindow

@@2:
        XCHG     EAX, EBX
        CALL     Invalidate

@@exit:
        POP      EBX
end;

function TControl.GetParentWindow: HWnd;
asm
        MOV       EAX, [EAX].fParent
        TEST      EAX, EAX
        JNZ       TControl.GetWindowHandle
end;

{$IFDEF ASM_UNICODE}
function TControl.GetWindowHandle: HWnd;
asm
         MOV      ECX, [EAX].fHandle
         JECXZ    @@1
         XCHG     EAX, ECX
         RET
@@1:
         PUSH     EBX
         MOV      EBX, EAX
         CMP      [EBX].fCreateVisible, 0
         JNZ      @@2

         XOR      EDX, EDX
         CALL     TControl.Set_Visible

         MOV      EAX, EBX
         CALL     CallTControlCreateWindow
         { This is a call to Pascal piece of code, which
           calls virtual method TControl.CreateWindow }

         INC      [EBX].fCreateHidden
         JMP      @@0

@@2:     CALL     CallTControlCreateWindow
@@0:     MOV      EAX, [EBX].fHandle
         POP      EBX
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
function TControl.CreateWindow: Boolean;
const
  CS_OFF = CS_OWNDC or CS_CLASSDC or CS_PARENTDC or CS_GLOBALCLASS;
  CS_ON = 0; //CS_VREDRAW or CS_HREDRAW;
  szWndClass = sizeof( TWndClass );
  int_IDC_ARROW = integer( IDC_ARROW );
asm
        PUSH     EBX
        XCHG     EBX, EAX
        {$IFDEF DEBUG_CREATEWINDOW}
        MOV     EAX, EBX
        CALL    Debug_CreateWindow1
        {$ENDIF}
        MOV      ECX, [EBX].fParent
        JECXZ    @@chk_handle
        XCHG     EAX, ECX
        CALL     GetWindowHandle
        TEST     EAX, EAX
        JZ       @@ret_0
@@chk_handle:
        MOV      ECX, [EBX].fHandle
        JECXZ    @@prepare_Params
        MOV      DL, 0
        MOV      EAX, EBX
        CMP      [EBX].fCreateHidden, DL
        JZ       @@create_children
        CALL     CreateChildWindows
        MOV      EAX, EBX
        MOV      DL, 1
        CALL     Set_Visible
        MOV      [EBX].fCreateHidden, 0
        JMP      @@ret_true
@@create_children:
        CALL     CreateChildWindows
@@ret_true:
        MOV      AL, 1
@@ret_0:
        POP      EBX
        RET
@@prepare_params:
        {$IFDEF USE_GRAPHCTLS}
        MOV      AL, [EBX].fWindowed
        CMP      AL, 0
        JZ       @@ret_0
        {$ENDIF}
        PUSH     EBP
        MOV      EBP, ESP

        PUSH     ECX        // Params.WindowClass.lpszClassName := nil
        PUSH     ECX        // Params.WindowClass.lpszMenuName := nil
        PUSH     ECX        // Params.WindowClass.hbrBackground := 0
        PUSH     int_IDC_ARROW
        PUSH     ECX
        CALL     LoadCursor
        PUSH     EAX        // Params.WindowClass.hCursor := LoadCursor( 0, IDC_ARROW )
        XOR      ECX, ECX
        PUSH     ECX        // Params.WindowClass.hIcon := 0
        PUSH     [hInstance]// Params.WindowClass.hInstance := hInstance
        PUSH     ECX        // Params.WindowClass.cbWndExtra := 0
        PUSH     ECX        // Params.WindowClass.cbClsExtra := 0
        PUSH     [EBX].fDefWndProc     // Params.WindowClass.lpfnWndProc := fDefWndProc
        PUSH     [EBX].fClsStyle       // Params.WindowClass.style := fStyle
        ADD      ESP, -64
        PUSH     ECX
        MOV      EAX, EBX
        MOV      EDX, ESP
        CALL     get_ClassName
        POP      EDX
        MOV      EAX, ESP
        PUSH     EDX
        //CALL     StrPCopy    // StrPCopy( Params.WinClsNamBuf, ClassName )
        CALL     StrCopy
        CALL     RemoveStr
        PUSH     0           // Params.Param := nil
        PUSH     [hInstance] // Params.Inst := hInstance
        PUSH     [EBX].fMenu // Params.Menu := fMenu
        MOV      DL, 1
        MOV      EAX, EBX
        CALL     GetParentWnd
        PUSH     EAX         // Params.WndParent := GetParentWnd( True )

        MOV      ECX, CW_USEDEFAULT
        MOV      EAX, [EBX].fBoundsRect.Bottom
        MOV      EDX, [EBX].fBoundsRect.Top
        SUB      EAX, EDX
        JNZ      @@1
        MOV      EAX, ECX
@@1:    PUSH     EAX         // Params.Height := Height | CW_UseDefault
        MOV      EAX, [EBX].fBoundsRect.Right
        SUB      EAX, [EBX].fBoundsRect.Left
        {$IFDEF USE_CMOV}
        CMOVZ    EAX, ECX
        {$ELSE}
        JNZ      @@2
        MOV      EAX, ECX
@@2:    {$ENDIF}

        PUSH     EAX         // Params.Width := Width | CW_UseDefault
        MOV      EAX, [EBX].fBoundsRect.Left
        CMP      [EBX].fIsControl, CL
        JNZ      @@3
        TEST     byte ptr [EBX].fChangedPosSz, 3
        JNZ      @@3
        MOV      EDX, ECX
        XCHG     EAX, ECX
@@3:    PUSH     EDX         // Params.Y := Top | CW_UseDefault
        PUSH     EAX         // Params.X := Left | CW_UseDefault
        PUSH     [EBX].fStyle    // Params.Style := fStyle
        PUSH     [EBX].fCaption  // Params.Caption := fCaption
        LEA      EAX, [ESP+40]
        PUSH     EAX         // Params.WinClassName := @Params.WinClsNamBuf
        PUSH     [EBX].fExStyle  // Params.ExStyle := fExStyle

        MOV      ECX, [EBX].fControlClassName
        JECXZ    @@registerClass
        LEA      EAX, [ESP].TCreateWndParams.WindowClass
        PUSH     EAX           // @Params.WindowClass
        PUSH     ECX           // fControlClassName
        PUSH     [hInstance]   // hInstance
        CALL     GetClassInfo
        MOV      EAX, [ESP].TCreateWndParams.Inst
        MOV      [ESP].TCreateWndParams.WindowClass.hInstance, EAX
        AND      [ESP].TCreateWndParams.WindowClass.style, not CS_OFF
@@registerClass:
        CMP      [EBX].fDefWndProc, 0
        JNE      @@fDefWndProc_ready
        MOV      EAX, [ESP].TCreateWndParams.WindowClass.lpfnWndProc
        MOV      [EBX].fDefWndProc, EAX
@@fDefWndProc_ready:
        MOV      ECX, [ESP].TCreateWndParams.WndParent
        INC      ECX
        LOOP     @@registerClass1
        TEST     byte ptr [ESP].TCreateWndParams.Style+3, $40
        XCHG     EAX, ECX
        JNZ      @@fin
@@registerClass1:
        MOV      EAX, [ESP].TCreateWndParams.WinClassName
        MOV      EDX, [ESP].TCreateWndParams.WindowClass.hInstance
        ADD      ESP, -szWndClass
        PUSH     ESP
        PUSH     EAX
        PUSH     EDX
        CALL     GetClassInfo
        ADD      ESP, szWndClass
        TEST     EAX, EAX
        JNZ      @@registered
        MOV      EAX, [ESP].TCreateWndParams.WinClassName
        MOV      [ESP].TCreateWndParams.WindowClass.lpszClassName, EAX
        MOV      [ESP].TCreateWndParams.WindowClass.lpfnWndProc, offset WndFunc
        LEA      EAX, [ESP].TCreateWndParams.WindowClass
        PUSH     EAX
        CALL     RegisterClass
        TEST     EAX, EAX
        JZ       @@fin
@@registered:
        MOV      [CreatingWindow], EBX
        {$IFDEF DEBUG_CREATEWINDOW}
        MOV     EAX, EBX
        MOV     EDX, ESP
        CALL    Debug_CreateWindow2
        {$ENDIF}
        CALL     CreateWindowEx
        MOV      [EBX].fHandle, EAX
        TEST     EAX, EAX
        JZ       @@fin
        PUSH     EAX
        {$IFDEF USE_PROP}
        PUSH     offset ID_SELF
        {$ELSE}
        PUSH     GWL_USERDATA
        {$ENDIF}
        PUSH     EAX

        PUSH     0
        PUSH     $10002 //UIS_CLEAR or (UISF_HIDEFOCUS shl 16)
        PUSH     $0128  //WM_UPDATEUISTATE
        PUSH     EAX
        CALL     SendMessage

        {$IFDEF USE_PROP}
        CALL     GetProp
        {$ELSE}
        CALL     GetWindowLong
        {$ENDIF}
        XCHG     ECX, EAX
        POP      EAX
        INC      ECX
        LOOP     @@propSet
        MOV      [CreatingWindow], ECX
        PUSH     EBX
        {$IFDEF USE_PROP}
        PUSH     offset ID_SELF
        PUSH     EAX
        CALL     SetProp
        {$ELSE}
        PUSH     GWL_USERDATA
        PUSH     EAX
        CALL     SetWindowLong
        {$ENDIF}
@@propSet:
        {$IFDEF SMALLEST_CODE}
        {$ELSE}
        CMP      [EBX].fIsControl, 0
        JNZ      @@iconSet
        MOV      EAX, EBX
        CALL     GetIcon
        PUSH     EAX
        PUSH     1
        PUSH     WM_SETICON
        PUSH     EBX
        CALL     Perform
@@iconSet:
        {$ENDIF}
        MOV      ECX, [EBX].fCreateWndExt
        JECXZ    @@dblbufcreate
        MOV      EAX, EBX
        CALL     ECX
@@dblbufcreate:
@@applyfont:
        MOV      EAX, EBX
        CALL     ApplyFont2Wnd
        MOV      EAX, EBX
        CALL     ApplyFont2Wnd
        XCHG     EAX, EBX
        CALL     CreateChildWindows
        MOV      AL, 1
@@fin:
        MOV      ESP, EBP
        POP      EBP
@@ret_false:
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

function WndProcMouse(Self_: PControl; var Msg: TMsg; var Rslt: Integer): Boolean;
asm
         PUSH      EBX
         PUSH      ESI
         XCHG      EBX, EAX

         XOR       ECX, ECX // Rslt not used. ECX <= Result = 0
         MOV       EAX, [EDX].TMsg.message
         SUB       AH, WM_MOUSEFIRST shr 8
         CMP       EAX, $20A - WM_MOUSEFIRST //WM_MOUSELAST - WM_MOUSEFIRST
         JA        @@exit

         PUSH      dword ptr [EDX].TMsg.lParam // prepare X, Y

         PUSHAD
           PUSH      VK_MENU
           CALL      GetKeyState
           ADD       EAX, EAX
         POPAD

         XCHG        EAX, EDX
           MOV       EAX, [EAX].TMsg.wParam

           JNC       @@noset_MKALT
           {$IFDEF PARANOIA} DB $0C, MK_ALT {$ELSE} OR AL, MK_ALT {$ENDIF}
@@noset_MKALT:

         PUSH      EAX             // prepare Shift

         LEA       ESI, [EBX].TControl.fOnMouseDown
         CALL      dword ptr [EDX*4 + @@jump_table]

@@call_evnt:

         PUSH      ECX             // prepare Button, StopHandling
         MOV       ECX, ESP        // ECX = @MouseData

         CMP       word ptr [ESI].TMethod.Code+2, 0
         JZ        @@after_call

         MOV       EDX, EBX        // EDX = Self_
         MOV       EAX, [ESI].TMethod.Data      // EAX = Target_
         CALL      dword ptr [ESI].TMethod.Code

@@after_call:
         POP       ECX
         POP       EDX
         POP       EDX
         MOV       CL, CH           // Result := StopHandling

@@exit:
         XCHG      EAX, ECX
         POP       ESI
         POP       EBX
         RET

@@jump_table:
         DD Offset[@@MMove],Offset[@@LDown],Offset[@@LUp],Offset[@@LDblClk]
         DD Offset[@@RDown],Offset[@@RUp],Offset[@@RDblClk]
         DD Offset[@@MDown],Offset[@@MUp],Offset[@@MDblClk],Offset[@@MWheel]

@@MDown: INC       ECX
@@RDown: INC       ECX
@@LDown: INC       ECX
         RET

@@MUp:   INC       ECX
@@RUp:   INC       ECX
@@LUp:   INC       ECX
         LODSD
         LODSD
         RET

@@MMove: LEA       ESI, [EBX].TControl.fOnMouseMove
         RET

@@MDblClk: INC     ECX
@@RDblClk: INC     ECX
@@LDblClk: INC     ECX
         LEA       ESI, [EBX].TControl.fOnMouseDblClk
         RET

@@MWheel:LEA       ESI, [EBX].TControl.fOnMouseWheel
end;

{$IFDEF ASM_UNICODE}
function WndProcKeybd( Self_: PControl; var Msg: TMsg; var Rslt: Integer): Boolean;
asm
        PUSH     EBX
        MOV      ECX, [EDX].TMsg.message
        SUB      CX, $100
        CMP      ECX, 5
        JA       @@fin_false
        XCHG     EBX, EAX   // EBX = @Self
        XCHG     EAX, ECX   // EAX = message - WM_KEYFIRST
        LEA      ECX, [EBX].TControl.fOnKeyUp
        JZ       @@event
        {$IFDEF PARANOIA} DB $34, 1 {$ELSE} XOR AL, 1 {$ENDIF}
        JZ       @@event
        LEA      ECX, [EBX].TControl.fOnKeyDown
        {$IFDEF PARANOIA} DB $34, 1 {$ELSE} XOR AL, 1 {$ENDIF}
        JZ       @@event
        {$IFDEF PARANOIA} DB $34, 4 {$ELSE} XOR AL, 4 {$ENDIF}
        JZ       @@event
        LEA      ECX, [EBX].TControl.fOnChar
        {$IFDEF PARANOIA} DB $34, 6 {$ELSE} XOR AL, 2 xor 4 {$ENDIF}
        JZ       @@event
        {$IFDEF PARANOIA} DB $34, 4 {$ELSE} XOR AL, 6 xor 2 {$ENDIF}
        JNZ      @@fin_false
@@event:
        CMP      word ptr [ECX].TMethod.Code+2, 0
        JZ       @@fin_false
        PUSH     EDX
        PUSH     ECX
        LEA      ECX, [EDX].TMsg.wParam
        PUSH     ECX
        CALL     GetShiftState
        POP      ECX         // @wParam
        XCHG     EAX, [ESP]  // ShiftState; EAX=@event
        MOV      EDX, EBX    // @Self
        MOV      EBX, [EAX].TMethod.Code
        MOV      EAX, [EAX].TMethod.Data
        CALL     EBX

        POP      EDX
        MOV      ECX, [EDX].TMsg.wParam
        JECXZ    @@fin_true

@@fin_false:
        XOR      EAX, EAX
        POP      EBX
        RET

@@fin_true:
        MOV      AL, 1
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

{$IFNDEF USE_GRAPHCTLS}
{$IFNDEF NEW_MODAL}
function TControl.WndProc( var Msg: TMsg ): Integer;
asm     //cmd    //opd
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        XCHG     ESI, EAX
        MOV      EDI, EDX
        XOR      EAX, EAX
        CMP      EAX, [EDX].TMsg.hWnd
        JE       @@1
        CMP      EAX, [ESI].TControl.fHandle
        JNE      @@1
        {$IFDEF USE_GRAPHCTLS}
        CMP      [ESI].TControl.fWindowed, AL
        JNE      @@1
        {$ENDIF}
        MOV      EAX, [EDX].TMsg.hWnd
        MOV      [ESI].TControl.fHandle, EAX
@@1:
        XOR      eax, eax

        CMP      [AppletRunning], 0
        JZ       @@dyn2
        MOV      ECX, [Applet]
        JECXZ    @@dyn2
        CMP      ECX, ESI
        JE       @@dyn2

        CALL     @@onmess

@@dyn2: MOV      ECX, ESI
        CALL     @@onmess

        MOV      EBX, [ESI].TControl.fOnDynHandlers
        MOV      EAX, ESI
        CALL     @@callonmes

@@flicksproc:
        MOV      EAX, ESI
        MOV      EDX, EDI
        PUSH     0
        MOV      ECX, ESP
        CALL     dword ptr [ESI].TControl.fWndProcResizeFlicks
        TEST     AL, AL
        POP      EAX
        JNZ      @@pass2defproc

        MOVZX    EAX, word ptr [EDI].TMsg.message
        CMP      EAX, WM_CLOSE
        JNZ      @@chk_WM_DESTROY

        CMP      ESI, [Applet]
        JZ       @@postquit
        MOV      EAX, ESI
        CALL     IsMainWindow
        TEST     AL, AL
        JZ       @@calldef
@@postquit:
        PUSH     0
        CALL     PostQuitMessage
        JMP      @@calldef
//********************************************************** Added By M.Gerasimov
@@chk_WM_DESTROY:
        CMP      AX, WM_DESTROY
        JNE      @@chk_WM_NCDESTROY
        MOV      [ESI].TControl.fBeginDestroying, AL
        JMP      @@calldef
//**********************************************************
@@chk_WM_NCDESTROY:
        //CMP      word ptr [EDI].TMsg.message, WM_NCDESTROY
        CMP      AX, WM_NCDESTROY
        JNE      @@chk_WM_SIZE // @@chk_CM_RELEASE
//********************************************************** Added By M.Gerasimov
        {$IFDEF USE_PROP}
        PUSH     offset[ID_SELF]
        PUSH     [ESI].fHandle
        CALL     RemoveProp
        {$ENDIF}
//**********************************************************

@@return0:
        XOR      EAX, EAX
        JMP      @@exit // WM_NCDESTROY and CM_RELEASE
                        // is not a subject to pass it
                        // to fPass2DefProc
@@onmess:
        MOV      EAX, [ECX].TControl.fOnMessage.TMethod.Data
        MOV      EBX, [ECX].TControl.fOnMessage.TMethod.Code
@@callonmes:
        TEST     EBX, EBX
        JNZ      @@onmess1 // @@dynmes1
@@2onmessret:
        RET
@@onmess1:
        PUSH     0

        MOV      EDX, EDI
        MOV      ECX, ESP
        CALL     EBX
        TEST     AL, AL

        POP      EAX
        JZ       @@2onmessret
        POP      EDX // pop retaddr
        JMP      @@pass2defproc
@@chk_WM_SIZE:
        CMP      AX, WM_SIZE
        JNE      @@chk_WM_SYSCOMMAND //@@chk_WM_SHOWWINDOW

        MOV      EDX, EDI
        MOV      EAX, ESI
        CALL     TControl.CallDefWndProc
        PUSH     EAX

        MOV      ECX, [EDI].TMsg.wParam
        MOV      [ESI].TControl.fWindowState, CL

    {$IFDEF OLD_ALIGN}
        CMP      [ESI].TControl.fIsForm, 0
        JNZ      @@doGlobalAlignSelf
        MOV      EAX, [ESI].TControl.fParent
        CALL     dword ptr [Global_Align]
@@doGlobalAlignSelf:
    {$ENDIF}
        XCHG     EAX, ESI
        CALL     dword ptr [Global_Align]
        JMP      @@popeax_exit  // fPass2DefProc not needed, CallDefWndProc already called
@@chk_WM_SYSCOMMAND:
        CMP      AX, WM_SYSCOMMAND
        JNE      @@chk_WM_SETFOCUS

        MOV      EAX, [EDI].TMsg.wParam
        {$IFDEF PARANOIA} DB $24, $F0 {$ELSE} AND AL, $F0 {$ENDIF}
        CMP      AX, SC_MINIMIZE
        JNE      @@calldef

        MOV      EAX, ESI
        CALL     TControl.IsMainWindow
        TEST     AL, AL
        JZ       @@calldef

        CMP      ESI, [Applet]
        JE       @@calldef

        PUSH     0
        PUSH     SC_MINIMIZE
        PUSH     WM_SYSCOMMAND
        MOV      EAX, [Applet]
        PUSH     [EAX].TControl.fHandle
        CALL     PostMessage
@@ret_0:
        JMP      @@0pass2defproc

@@chk_WM_SETFOCUS:
        CMP      AX, WM_SETFOCUS
        JNE      @@chk_WM_CTLCOLOR //@@chk_WM_SETCURSOR

        MOV      EAX, ESI
        CALL     TControl.DoSetFocus
        TEST     AL, AL
        JZ       @@0pass2defproc

        INC      [ESI].TControl.fClickDisabled

        MOV      EAX, ESI
        MOV      EDX, EDI
        CALL     TControl.CallDefWndProc

        DEC      [ESI].TControl.fClickDisabled
        JMP      @@exit

@@chk_WM_CTLCOLOR:
        MOV      EDX, EAX
        SUB      DX, WM_CTLCOLORMSGBOX
        CMP      DX, WM_CTLCOLORSTATIC-WM_CTLCOLORMSGBOX
        JA       @@chk_WM_COMMAND

        PUSH     [EDI].TMsg.lParam
        PUSH     [EDI].TMsg.wParam
        ADD      AX, CN_BASE //+WM_CTLCOLORMSGBOX
        PUSH     EAX
        PUSH     [EDI].TMsg.lParam
        CALL     SendMessage
        JMP      @@pass2defproc

@@chk_WM_COMMAND:
        //CMP      word ptr [EDI].TMsg.message, WM_COMMAND
        CMP      AX, WM_COMMAND
        JNE      @@chk_WM_KEY

        {$IFDEF USE_PROP}
        PUSH     offset[ID_SELF]
        PUSH     [EDI].TMsg.lParam
        CALL     GetProp
        {$ELSE}
        PUSH     GWL_USERDATA
        PUSH     [EDI].TMsg.lParam
        CALL     GetWindowLong
        {$ENDIF}
        TEST     EAX, EAX
        JZ       @@calldef

        PUSH     [EDI].TMsg.lParam
        PUSH     [EDI].TMsg.wParam
        PUSH     CM_COMMAND
        PUSH     [EDI].TMsg.lParam
        CALL     SendMessage
        JMP      @@pass2defproc

@@chk_WM_KEY:
        MOV      EDX, EAX
        SUB      DX, WM_KEYFIRST
        CMP      DX, WM_KEYLAST-WM_KEYFIRST
        JA       @@calldef //@@chk_CM_EXECPROC
        {$IFDEF KEY_PREVIEW}
        CMP      [ESI].TControl.fKeyPreviewing, 0
        {JE       @@nokeypreview1
        CMP      AX, WM_KEYDOWN
        JE       @@in_focus
@@nokeypreview1:}
        JNE      @@in_focus
        {$ENDIF KEY_PREVIEW}

        CALL     GetFocus
        CMP      EAX, [ESI].TControl.fFocusHandle
        JE       @@in_focus
        CMP      EAX, [ESI].TControl.fHandle
        JE       @@in_focus
        {$IFDEF USE_GRAPHCTLS}
        CMP      [ESI].fWindowed, 0
        JE       @@0pass2defproc
        {$ENDIF}

@@in_focus:
        {$IFDEF KEY_PREVIEW}
        MOV      [ESI].TControl.fKeyPreviewing, 0
        {$ENDIF KEY_PREVIEW}
        PUSH     EAX

        MOV      ECX, ESP
        MOV      EDX, EDI
        MOV      EAX, ESI
        CALL     dword ptr [fGlobalProcKeybd]
        TEST     AL, AL
        JNZ      @@to_exit

        MOV      ECX, ESP
        MOV      EDX, EDI
        MOV      EAX, ESI
        CALL     [ESI].fWndProcKeybd
        TEST     AL, AL
@@to_exit:
        POP      EAX
        JNZ      @@pass2defproc

        PUSH     VK_CONTROL
        CALL     GetKeyState
        XCHG     EBX, EAX
        PUSH     VK_MENU
        CALL     GetKeyState
        OR       EAX, EBX
        JS       @@calldef

        CMP      word ptr [EDI].TMsg.message, WM_CHAR
        JNE      @@to_fGotoControl

        CMP      byte ptr [EDI].TMsg.wParam, 9
        JE       @@clear_wParam
        JMP      @@calldef

@@to_fGotoControl:
        MOV      EAX, ESI
        CALL     TControl.ParentForm
        TEST     EAX, EAX
        JZ       @@calldef

        MOV      ECX, [EAX].fGotoControl
        JECXZ    @@calldef

        MOV      EBX, ECX
        CMP      [EDI].TMsg.message, WM_KEYDOWN
        SETNE    CL
        CMP      [EDI].TMsg.message, WM_SYSKEYDOWN
        SETNE    CH
        AND      CL, CH
        MOV      EDX, [EDI].TMsg.wParam
        MOV      EAX, ESI
        CALL     EBX
        TEST     AL, AL
        JZ       @@calldef

@@clear_wParam:
        XOR      EAX, EAX
        MOV      [EDI].TMsg.wParam, EAX
        JMP      @@pass2defproc

@@calldef:
        XCHG     EAX, ESI
        MOV      EDX, EDI
        CALL     TControl.CallDefWndProc
        JMP      @@exit

@@0pass2defproc:
        XOR      EAX, EAX
@@pass2defproc:
        PUSH     EAX
@@1pass2defproc:
        CMP      [AppletTerminated], 0 //
        JNZ      @@popeax_exit         // uncommented 25-Oct-2003
        CMP      [ESI].fNCDestroyed, 0 //
        JNZ      @@popeax_exit         //

        MOV      ECX, ESP
        XCHG     EAX, ESI
        MOV      EDX, EDI
        CALL     dword ptr[EAX].fPass2DefProc
@@popeax_exit:
        POP      EAX

@@exit:
        POP      EDI
        POP      ESI
        POP      EBX
end;
{$ENDIF no NEW_MODAL}
{$ENDIF no USE_GRAPHCTLS}

procedure TControl.SetClsStyle( Value: DWord );
asm     //cmd    //opd
        CMP      EDX, [EAX].TControl.fClsStyle
        JE       @@exit
        MOV      [EAX].TControl.fClsStyle, EDX
        MOV      ECX, [EAX].TControl.fHandle
        JECXZ    @@exit
        PUSH     EDX
        PUSH     GCL_STYLE
        PUSH     ECX
        CALL     SetClassLong
@@exit:
end;

procedure TControl.SetStyle( Value: DWord );
const SWP_FLAGS = SWP_NOACTIVATE or SWP_NOMOVE or SWP_NOSIZE or
                 SWP_NOZORDER or SWP_FRAMECHANGED;
asm
        CMP      EDX, [EAX].fStyle
        JZ       @@exit
        MOV      [EAX].fStyle, EDX
        MOV      ECX, [EAX].fHandle
        JECXZ    @@exit

        PUSH     EAX

        PUSH     SWP_FLAGS
        XOR      EAX, EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     ECX

        PUSH     EDX
        PUSH     GWL_STYLE
        PUSH     ECX
        CALL     SetWindowLong

        CALL     SetWindowPos

        POP      EAX
        CALL     Invalidate
@@exit:
end;

procedure TControl.SetExStyle( Value: DWord );
const SWP_FLAGS = SWP_NOACTIVATE or SWP_NOMOVE or SWP_NOSIZE or
                 SWP_NOZORDER or SWP_FRAMECHANGED;
asm
        CMP      EDX, [EAX].fExStyle
        JZ       @@exit
        MOV      [EAX].fExStyle, EDX
        MOV      ECX, [EAX].fHandle
        JECXZ    @@exit

        PUSH     EAX

        PUSH     SWP_FLAGS
        XOR      EAX, EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     ECX

        PUSH     EDX
        PUSH     GWL_EXSTYLE
        PUSH     ECX
        CALL     SetWindowLong

        CALL     SetWindowPos

        POP      EAX
        CALL     Invalidate
@@exit:
end;

procedure TControl.SetCursor( Value: HCursor );
asm     //cmd    //opd
        PUSH     EBX
        MOV      EBX, EAX
        PUSH     EDX
        LEA      EDX, WndProcSetCursor
        CALL     TControl.AttachProc
        POP      EDX

        CMP      EDX, [EBX].TControl.fCursor
        JE       @@exit
        MOV      [EBX].TControl.fCursor, EDX
        MOV      ECX, [EBX].TControl.fHandle
        JECXZ    @@exit
        TEST     EDX, EDX                      //YS
        JE       @@exit                        //YS
        MOV      ECX, [ScreenCursor]
        INC      ECX
        LOOP     @@exit

        PUSH     EDX
        PUSH     EAX
        PUSH     EAX
        PUSH     ESP
        CALL     GetCursorPos
        MOV      EDX, ESP
        MOV      ECX, EDX
        MOV      EAX, EBX
        CALL     Screen2Client
        ADD      ESP, -16
        MOV      EDX, ESP
        MOV      EAX, EBX
        CALL     TControl.ClientRect
        MOV      EDX, ESP
        LEA      EAX, [ESP+16]
        CALL     PointInRect
        ADD      ESP, 24
        TEST     AL, AL
        JZ       @@fin
        CALL     Windows.SetCursor
        PUSH     EAX
@@fin:  POP      EAX
@@exit:
        POP      EBX
end;

procedure TControl.SetIcon( Value: HIcon );
asm     //cmd    //opd
        CMP      EDX, [EAX].TControl.fIcon
        JE       @@exit
        MOV      [EAX].TControl.fIcon, EDX
        INC      EDX
        JZ       @@1
        DEC      EDX
@@1:
        PUSH     EDX
        PUSH     1 //ICON_BIG
        PUSH     WM_SETICON
        PUSH     EAX
        CALL     Perform
        TEST     EAX, EAX
        JZ       @@exit
        PUSH     EAX
        CALL     DestroyIcon
@@exit:
end;

procedure TControl.SetMenu( Value: HMenu );
asm
        PUSH     EBX
        XCHG     EBX, EAX
        CMP      [EBX].fMenu, EDX
        JZ       @@exit
        PUSH     EDX
        MOV      ECX, [EBX].fMenuObj
        JECXZ    @@no_free_menuctl
        {$IFDEF USE_AUTOFREE4CONTROLS}
        PUSH     EDX
        MOV      EAX, EBX
        CALL     TControl.RemoveFromAutoFree
        POP      EAX
        {$ELSE}
        XCHG     EAX, EDX
        {$ENDIF}
        CALL     TObj.RefDec
@@no_free_menuctl:
        MOV      ECX, [EBX].fMenu
        JECXZ    @@no_destroy
        PUSH     ECX
        CALL     DestroyMenu
@@no_destroy:
        POP      EDX
        MOV      [EBX].fMenu, EDX
        MOV      ECX, [EBX].fHandle
        JECXZ    @@exit
        PUSH     EDX
        PUSH     ECX
        CALL     Windows.SetMenu
@@exit:
        POP      EBX
end;

procedure TControl.DoAutoSize;
asm
  MOV  ECX, [EAX].fAutoSize
  JECXZ     @@exit
  PUSH      ECX
@@exit:
end;

procedure TControl.SetCaption( const Value: KOLString );
asm
        PUSH    EBX
        XCHG    EBX, EAX
        LEA     EAX, [EBX].fCaption
        {$IFDEF UNICODE_CTRLS}
        CALL    System.@WStrAsg
        {$ELSE}
        CALL    System.@LStrAsg
        {$ENDIF}

        MOV     ECX, [EBX].fHandle
        JECXZ   @@0
        PUSH    [EBX].TControl.fCaption
        PUSH    0
        PUSH    WM_SETTEXT
        PUSH    ECX
        {$IFDEF UNICODE_CTRLS}
        CALL    SendMessageW
        {$ELSE}
        CALL    SendMessage
        {$ENDIF}
@@0:
        MOVZX   ECX, byte ptr [EBX].fIsStaticControl
        LOOP    @@1
        MOV     EAX, EBX
        CALL    Invalidate
@@1:
        XCHG    EAX, EBX
@@exit: POP     EBX
        PUSH    [EAX].fAutoSize
@@exit_2:
end;

function TControl.GetVisible: Boolean;
asm
        MOV     ECX, [EAX].fHandle
        JECXZ   @@check_fStyle
          PUSH  EAX
        PUSH    ECX
        CALL    IsWindowVisible
        TEST    EAX, EAX
          POP   EAX
        JMP     @@checked // Z if not visible

@@check_fStyle:
        TEST    byte ptr [EAX].fStyle+3, 10h // WS_VISIBLE shr 3
@@checked:
        SETNZ   DL
        MOV     [EAX].fVisible, DL
        XCHG    EAX, EDX
end;

function TControl.Get_Visible: Boolean;
asm     //     //
        MOV    ECX, [EAX].fHandle
        JECXZ  @@ret_fVisible
        CMP    [EAX].fIsControl, 0
        JNZ    @@ret_fVisible
        PUSH   EAX
        PUSH   ECX
        CALL   IsWindowVisible
        XCHG   EDX, EAX
        POP    EAX
        MOV    [EAX].fVisible, DL
@@ret_fVisible:
        MOVZX  EAX, [EAX].fVisible
end;

procedure TControl.Set_Visible( Value: Boolean );
const wsVisible = $10;
asm
    {$IFDEF OLD_ALIGN}
        PUSH     EBX
        PUSH     ESI
        //MOV      ESI, EAX
        XCHG     ESI, EAX
        MOVZX    EBX, DL
        {CALL     Get_Visible
        CMP      AL, BL
        JE       @@reset_fCreateHidden}

        MOV      AL, byte ptr [ESI].fStyle + 3
        TEST     EBX, EBX
        JZ       @@reset_WS_VISIBLE
        OR       AL, wsVisible
        PUSH     SW_SHOW
        JMP      @@store_Visible
@@reset_WS_VISIBLE:
        AND      AL, not wsVisible
        PUSH     SW_HIDE

@@store_Visible:
        MOV      byte ptr [ESI].fStyle + 3, AL
        MOV      [ESI].fVisible, BL
        MOV      ECX, [ESI].fHandle
        JECXZ    @@after_showwindow

        PUSH     ECX
        CALL     ShowWindow
        PUSH     ECX
@@after_showwindow:
        POP      ECX

        MOV      EAX, [ESI].fParent
        CALL     dword ptr [Global_Align]

@@chk_align_Self:
        TEST     EBX, EBX
        JZ       @@reset_fCreateHidden
        MOV      EAX, ESI
        CALL     dword ptr [Global_Align]


@@reset_fCreateHidden:
        MOV      ECX, [ESI].fHandle
        JECXZ    @@exit
        TEST     BL, BL
        JNZ      @@exit
        MOV      [ESI].fCreateHidden, BL { +++ }
@@exit:
        POP      ESI
        POP      EBX
    {$ELSE NEW_ALIGN}
        AND      byte ptr [EAX].fStyle + 3, not wsVisible
        TEST     DL,DL
        JZ       @@0
        OR       byte ptr [EAX].fStyle + 3, wsVisible
@@0:
        MOV      [EAX].fVisible, DL
        MOV      ECX, [EAX].fHandle
        JECXZ    @@exit
        PUSH     EAX
        JZ       @@1
        CALL     dword ptr [Global_Align]
        POP      EAX
        PUSH     SW_SHOW
        PUSH     [EAX].fHandle
        CALL     ShowWindow
@@exit:
        RET
@@1:
        MOV      [EAX].fCreateHidden, DL
        PUSH     SW_HIDE
        PUSH     ECX
        CALL     ShowWindow
        POP      EAX
        CALL     dword ptr [Global_Align]
    {$ENDIF}
end;

function TControl.GetBoundsRect: TRect;
asm
        PUSH      ESI
        PUSH      EDI
        LEA       ESI, [EAX].fBoundsRect
        MOV       EDI, EDX

        PUSH      EDX

        MOVSD
        MOVSD
        MOVSD
        MOVSD

        POP       EDI

        XCHG      ESI, EAX
        MOV       ECX, [ESI].fHandle
        JECXZ     @@exit

        PUSH      EDI
        PUSH      ECX
        CALL      GetWindowRect

        MOV       AL, [ESI].fIsMDIChild
        OR        AL, [ESI].fIsControl
        JZ        @@storeBounds

@@chk_Parent:
        MOV       EAX, [ESI].fParent

        TEST      EAX, EAX
        JZ        @@exit

        XOR       EDX, EDX
        PUSH      EDX
        PUSH      EDX
        MOV       ECX, ESP
        PUSH      EDX
        PUSH      EDX
        MOV       EDX, ESP
        CALL      TControl.Client2Screen
        POP       EAX
        POP       EAX

        POP       EAX
        NEG       EAX
        POP       ECX
        NEG       ECX
        PUSH      ECX
        PUSH      EAX
        PUSH      EDI
        CALL      OffsetRect

@@storeBounds:
        XCHG      ESI, EDI
        LEA       EDI, [EDI].fBoundsRect
        MOVSD
        MOVSD
        MOVSD
        MOVSD

@@exit:
        POP       EDI
        POP       ESI
end;

procedure HelpGetBoundsRect;
asm
        POP       ECX
        ADD       ESP, - size_TRect
        MOV       EDX, ESP
        PUSH      ECX
        PUSH      EAX
        CALL      TControl.GetBoundsRect
        POP       EAX
end;

procedure TControl.SetBoundsRect( const Value: TRect );
const swp_flags = SWP_NOZORDER or SWP_NOACTIVATE;
asm
        PUSH      EDI
        MOV       EDI, EAX

        PUSH      ESI
        MOV       ESI, EDX

        CALL      HelpGetBoundsRect

        MOV       EAX, ESI
        MOV       EDX, ESP
        CALL      RectsEqual
        TEST      AL, AL
        JNZ       @@exit

        POP       EDX   // left
        POP       ECX   // top
        POP       EAX   // right
        PUSH      EAX
        PUSH      ECX
        PUSH      EDX

        SUB       EAX, EDX  // EAX = width
        CMP       EDX, [ESI].TRect.Left
        MOV       DL, 0
        JE        @@1
        INC       EDX
@@1:    CMP       ECX, [ESI].TRect.Top
        JE        @@2
        OR        DL, 2
@@2:    OR        [EDI].fChangedPosSz, DL

        PUSH      EAX      // W saved

        MOV       EAX, [EDI].fBoundsRect.Bottom
        SUB       EAX, ECX
        PUSH      EAX      // H saved

        PUSH      EDI      // @Self saved
        {$IFDEF USE_GRAPHCTLS}
        CMP       [EDI].fWindowed, 0
        JNZ       @@invalid1
        MOV       EAX, EDI
        CALL      TControl.InvalidateNonWindowed
@@invalid1:
        {$ENDIF}

        LEA       EDI, [EDI].fBoundsRect
        MOVSD
        MOVSD
        MOVSD
        MOVSD

        MOV       ESI, EDI
        POP       EDI     // @ Self restored

        MOV       ECX, [EDI].fHandle
        JECXZ     @@fin

        STD
        PUSH      swp_flags

        LODSD
        LODSD
        XCHG      EDX, EAX // EDX = bottom
        LODSD
        XCHG      ECX, EAX // ECX = right
        LODSD
        SUB       EDX, EAX // EAX = bottom - top
        PUSH      EDX       // push HEIGHT
        XCHG      EDX, EAX  // EDX = top
        LODSD     // EAX = left
        CLD

        SUB       ECX, EAX
        PUSH      ECX       // push WIDTH

        PUSH      EDX       // push TOP
        PUSH      EAX       // push LEFT
        PUSH      0

        PUSH      [EDI].fHandle
        CALL      SetWindowPos

@@fin:
        POP       EDX       // H restored
        POP       EAX       // W restored

        CMP       [EDI].fSizeRedraw, 0
        JE        @@exit
@@invalid2:
        XCHG      EAX, EDI
        CALL      Invalidate

@@exit:
        ADD       ESP, size_TRect
        POP       ESI
        POP       EDI
end;

procedure TControl.SetWindowState( Value: TWindowState );
asm     //cmd    //opd
        CMP      [EAX].TControl.fWindowState, DL
        JE       @@exit
        MOV      [EAX].TControl.fWindowState, DL
        XCHG     EAX, EDX
        CBW
        CWDE
        MOV      AL, byte ptr [WindowStateShowCommands+EAX]
        PUSH     EAX
        XCHG     EAX, EDX
        CALL     TControl.GetWindowHandle
        PUSH     EAX
        CALL     ShowWindow
@@exit:
end;

procedure TControl.Show;
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     CreateWindow
        MOV      DL, 1
        MOV      EAX, EBX
        CALL     SetVisible
        PUSH     [EBX].fHandle
        CALL     SetForegroundWindow
        XCHG     EAX, EBX
        CALL     DoSetFocus
        POP      EBX
end;

function TControl.Client2Screen( const P: TPoint ): TPoint;
asm
        PUSH      ESI
        PUSH      EDI

        MOV       ESI, EDX
        MOV       EDI, ECX

        MOVSD
        MOVSD

        PUSH      ECX
        MOV       ECX, [EAX].fHandle
        JECXZ     @@exit

        PUSH      ECX
        CALL      ClientToScreen
        PUSH      ECX

@@exit: POP       ECX
        POP       EDI
        POP       ESI
end;

function TControl.Screen2Client( const P: TPoint ): TPoint;
asm
        PUSH      ESI
        PUSH      EDI

        MOV       ESI, EDX
        MOV       EDI, ECX

        MOVSD
        MOVSD

        PUSH      ECX
        MOV       ECX, [EAX].fHandle
        JECXZ     @@exit

        PUSH      ECX
        CALL      ScreenToClient
        PUSH      ECX

@@exit: POP       ECX
        POP       EDI
        POP       ESI
end;

function TControl.ClientRect: TRect;
asm
        PUSH      ESI
        XCHG      ESI, EAX
        PUSH      EDX
        PUSH      EDX      // prepare 'dest' for GetClientRect

        LEA       EAX, [ESI].fBoundsRect
        XOR       ECX, ECX
        MOV       CL, size_TRect

        CALL      System.Move

        MOV       EAX, ESI
        CALL      TControl.GetWindowHandle

        XCHG      ECX, EAX
        JECXZ     @@exit

        PUSH      ECX    // prepare 'handle' for GetClientRect
        CALL      GetClientRect

        PUSH      EDX

@@exit: POP       EDX
        POP       EDX  // EDX = @Result
        LEA       ESI, [ESI].fClientTop
        LODSD
        ADD       [EDX].TRect.Top, EAX
        LODSD
        SUB       [EDX].TRect.Bottom, EAX
        LODSD
        ADD       [EDX].TRect.Left, EAX
        LODSD
        SUB       [EDX].TRect.Right, EAX
        POP       ESI
end;

procedure TControl.Invalidate;
asm
  {$IFDEF USE_GRAPHCTLS}
  PUSH dword ptr [EAX].TControl.fDoInvalidate
  {$ELSE}
  MOV ECX, [EAX].fHandle
  JECXZ @@exit
  PUSH  $FF
  PUSH  0
  PUSH  ECX
  CALL  InvalidateRect
@@exit:
  {$ENDIF}
end;

{$IFDEF USE_GRAPHCTLS}
procedure TControl.InvalidateWindowed;
asm
  MOV ECX, [EAX].fHandle
  JECXZ @@exit
  PUSH  $FF
  PUSH  0
  PUSH  ECX
  CALL  InvalidateRect
@@exit:
end;
{$ENDIF USE_GRAPHCTLS}

//{$IFDEF ASM_UNICODE}
function TControl.GetIcon: HIcon;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        MOV       EAX, [EBX].fIcon
        INC       EAX
        JZ        @@exit
        DEC       EAX
        JNZ       @@exit

        MOV       ECX, [Applet]
        JECXZ     @@load
        CMP       ECX, EBX
        JZ        @@load

        XCHG      EAX, ECX
        CALL      TControl.GetIcon
        TEST      EAX, EAX
        JZ        @@exit

        XOR       EDX, EDX
        PUSH      EDX
        PUSH      EDX
        PUSH      EDX
        INC       EDX  // IMAGE_ICON = 1
        PUSH      EDX
        PUSH      EAX
        CALL      CopyImage
        JMP       @@store_fIcon

@@main_icon:
        {$IFDEF CUSTOM_APPICON}
        {$I CusomAppIconRsrcName_ASM.inc} // create such file with DB 'your icon rsrc name'
        {$ELSE}
        {$IFDEF UNICODE_CTRLS}
        DB 'M',0,'A',0,'I',0,'N',0,'I',0,'C',0,'O',0,'N',0,0
        {$ELSE}
        DB 'MAINICON'
        {$ENDIF}
        {$ENDIF}
        DB 0

@@load:
        PUSH      offset @@main_icon
        PUSH      [hInstance]
        CALL      LoadIcon
@@store_fIcon:
        MOV       [EBX].fIcon, EAX
@@exit:
        POP       EBX
end;
//{$ENDIF ASM_UNICODE}

function TControl.CallDefWndProc(var Msg: TMsg): Integer;
asm
        PUSH     [EDX].TMsg.lParam
        PUSH     [EDX].TMsg.wParam
        PUSH     [EDX].TMsg.message

        MOV      ECX, [EAX].fDefWndProc
        JECXZ    @@defwindowproc

        PUSH     [EAX].fHandle
        PUSH     ECX
        CALL     CallWindowProc
        RET

@@defwindowproc:
        PUSH     [EDX].TMsg.hwnd
        {$IFDEF UNICODE_CTRLS}
        CALL     DefWindowProcW
        {$ELSE}
        CALL     DefWindowProc
        {$ENDIF}
end;

function TControl.GetWindowState: TWindowState;
asm     //cmd    //opd
        PUSH     EBX
        PUSH     ESI
        XCHG     ESI, EAX
        MOVZX    EBX, [ESI].TControl.fWindowState
        MOV      ECX, [ESI].TControl.fHandle
        JECXZ    @@ret_EBX
        MOV      BL, 2
        MOV      ESI, ECX
        PUSH     ESI
        CALL     IsZoomed
        TEST     EAX, EAX
        JNZ      @@ret_EBX
        DEC      EBX
        PUSH     ESI
        CALL     IsIconic
        TEST     EAX, EAX
        JNZ      @@ret_EBX
        DEC      EBX
@@ret_EBX:
        XCHG     EAX, EBX
        POP      ESI
        POP      EBX
end;

function TControl.DoSetFocus: Boolean;
asm
        PUSH      ESI
        MOV       ESI, EAX

        CALL      GetEnabled
        {AND       AL, [ESI].fTabstop
        JNZ       @@1

        TEST      byte ptr [ESI+2].TControl.fStyle, 1 //(WS_TABSTOP shr 16)}
        MOV       DL, [ESI].TControl.fTabstop
        AND       DL, byte ptr [ESI+2].TControl.fStyle
        OR        EAX, EDX
        AND       EAX, 1
        JZ        @@exit

//@@1:
        INC       [ESI].TControl.fClickDisabled
        PUSH      [ESI].fHandle
        CALL      SetFocus
        DEC       [ESI].TControl.fClickDisabled
        MOV       AL, 1
@@exit:
        POP       ESI
end;

function TControl.GetEnabled: Boolean;
asm
        MOV       ECX, [EAX].fHandle
        JECXZ     @@get_field

        PUSH      ECX
        CALL      IsWindowEnabled
        RET

@@get_field:
        TEST      byte ptr [EAX].fStyle + 3, 8 //WS_DISABLED shr 3
        SETZ      AL
end;

function TControl.IsMainWindow: Boolean;
asm     XCHG ECX, EAX
        XOR  EDX, EDX
        MOV  EAX, [Applet]
        TEST EAX, EAX
        JNZ  @@0
        CMP  [ECX].fIsControl, AL
        JMP  @@3
@@0:    CMP  [appbuttonUsed], DL
        JZ   @@2
@@1:    PUSH ECX
        CALL TControl.GetMembers
        POP  ECX
@@2:    CMP  ECX, EAX
@@3:    SETZ AL
end;

{$IFDEF ASM_UNICODE}
function TControl.get_ClassName: String;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        XCHG      EAX, EDX
        MOV       EDX, [EBX].fControlClassName
        PUSH      EAX
        CALL      System.@LStrFromPChar
        POP       EAX
        CMP       [EBX].fCtlClsNameChg, 0
        JNZ       @@exit
        MOV       ECX, [EAX]
        MOV       EDX, offset[ @@obj ]
        CALL      System.@LStrCat3
        JMP       @@exit

        DD        -1, 4
@@obj:  DB        'obj_', 0

@@exit:
        POP       EBX
end;
{$ENDIF}

procedure TControl.SetParent( Value: PControl );
asm
        PUSH     EBX
        PUSH     EDI
        XCHG     EBX, EAX
        MOV      EDI, EDX
        MOV      ECX, [EBX].fParent
        CMP      EDI, ECX
        JE       @@exit

        JECXZ    @@1
        {$IFDEF USE_GRAPHCTLS}
        PUSH     ECX
        MOV      EAX, EBX
        CALL     TControl.Invalidate
        POP      ECX
        {$ENDIF}
        PUSH     ECX

        MOV      EAX, [ECX].fChildren
        MOV      EDX, EBX
        CALL     TList.Remove

        POP      EAX
        {$IFNDEF USE_AUTOFREE4CONTROL}
        PUSH     EAX
        MOV      EDX, EBX
        CALL     TObj.RemoveFromAutoFree
        POP      EAX
        {$ENDIF}

        {$IFNDEF SMALLEST_CODE}
        MOV      ECX, [EAX].fNotifyChild
        JECXZ    @@1
        XOR      EDX, EDX
        CALL     ECX
        {$ENDIF}
@@1:
        MOV      [EBX].fParent, EDI
        TEST     EDI, EDI
        JZ       @@exit

        MOV      EAX, [EDI].fChildren
        MOV      EDX, EBX
        CALL     TList.Add

        {$IFDEF USE_AUTOFREE4CHILDREN}
        MOV      EAX, EDI
        MOV      EDX, EBX
        CALL     TControl.Add2AutoFree
        {$ENDIF}

        {$IFNDEF INPACKAGE}
        MOV      ECX, [EBX].fHandle
        JECXZ    @@2
        MOV      EAX, EDI
        CALL     TControl.GetWindowHandle
        PUSH     EAX
        PUSH     [EBX].fHandle
        CALL     Windows.SetParent
@@2:
        {$ENDIF}

        {$IFNDEF SMALLEST_CODE}
        MOV      ECX, [EDI].fNotifyChild
        JECXZ    @@3
        MOV      EAX, EDI
        MOV      EDX, EBX
        CALL     ECX
@@3:
        MOV      ECX, [EBX].fNotifyChild
        JECXZ    @@4
        MOV      EAX, EDI
        MOV      EDX, EBX
        CALL     ECX
@@4:    {$ENDIF}

        {$IFNDEF USE_GRAPHCTLS}
        XCHG     EAX, EBX
        CALL     TControl.Invalidate
        {$ENDIF}
@@exit:
        POP      EDI
        POP      EBX
end;

constructor TControl.CreateParented(AParent: PControl);
asm     //cmd    //opd
        PUSH     EAX
        MOV      EDX, ECX
        MOV      ECX, [EAX]
        CALL     dword ptr [ECX+8]
        POP      EAX
end;

function TControl.GetLeft: Integer;
asm
        CALL      HelpGetBoundsRect
        POP       EAX

        POP       ECX
        POP       ECX
        POP       ECX
end;

procedure TControl.SetLeft( Value: Integer );
asm
        PUSH      EDI

        PUSH      EDX
        CALL      HelpGetBoundsRect
        POP       EDX           // EDX = Left
        POP       ECX           // ECX = Top
        POP       EDI           // EDI = Right

        SUB       EDI, EDX      // EDI = width
        MOV       EDX, [ESP+4]  // EDX = Left'
        ADD       EDI, EDX      // EDI = Right'

        PUSH      EDI
        PUSH      ECX
        PUSH      EDX
        MOV       EDX, ESP

        CALL      SetBoundsRect
        ADD       ESP, size_TRect + 4

        POP       EDI

end;

function TControl.GetTop: Integer;
asm
        CALL      HelpGetBoundsRect
        POP       EDX
          POP       EAX
        POP       EDX
        POP       EDX
end;

procedure TControl.SetTop( Value: Integer );
asm
        PUSH      ESI
        PUSH      EDI

          PUSH      EDX
        CALL      HelpGetBoundsRect
        POP       EDX           // EDX = Left
        POP       ECX           // ECX = Top
        POP       EDI           // EDI = Right
        POP       ESI           // ESI = Bottom

        SUB       ESI, ECX      // ESI = Height'
          POP       ECX         // ECX = Top'
        ADD       ESI, ECX      // ESI = Bottom'

        PUSH      ESI
        PUSH      EDI
        PUSH      ECX
        PUSH      EDX
        MOV       EDX, ESP

        CALL      SetBoundsRect
        ADD       ESP, size_TRect

        POP       EDI
        POP       ESI
end;

function TControl.GetWidth: Integer;
asm
        CALL      HelpGetBoundsRect
        POP       EDX
          POP       ECX
        POP       EAX
        SUB       EAX, EDX
          POP       ECX
end;

procedure TControl.SetWidth( Value: Integer );
asm
        PUSH      EDX

        CALL      HelpGetBoundsRect
        POP       EDX
        PUSH      EDX
        ADD       EDX, [ESP].size_TRect
        MOV       [ESP].TRect.Right, EDX

        MOV       EDX, ESP
        CALL      SetBoundsRect

        ADD       ESP, size_TRect + 4
end;

function TControl.GetHeight: Integer;
asm
        CALL      HelpGetBoundsRect
        POP       ECX
        POP       EDX          // EDX = top
        POP       ECX
        POP       EAX          // EAX = bottom
        SUB       EAX, EDX     // result = height
end;

procedure TControl.SetHeight( Value: Integer );
asm
        PUSH      EDX

        CALL      HelpGetBoundsRect
        MOV       EDX, [ESP].TRect.Top
        ADD       EDX, [ESP].size_TRect
        MOV       [ESP].TRect.Bottom, EDX

        MOV       EDX, ESP
        CALL      SetBoundsRect

        ADD       ESP, size_TRect + 4
end;

function TControl.GetPosition: TPoint;
asm
        PUSH      EDX
        CALL      HelpGetBoundsRect
        POP       EAX         // EAX = left
        POP       ECX         // ECX = top
        POP       EDX
        POP       EDX
        POP       EDX         // EDX = @Result
        MOV       [EDX], EAX
        MOV       [EDX+4], ECX
end;

procedure TControl.Set_Position( Value: TPoint );
asm
        PUSH      ESI
        PUSH      EDI

        PUSH      EAX
        PUSH      EDX
        CALL      HelpGetBoundsRect
        POP       EDX           // left
        POP       EAX           // top
        POP       ECX           // right
        SUB       ECX, EDX      // ECX = width
        POP       EDX           // bottom
        SUB       EDX, EAX      // EDX = height
        POP       EAX           // EAX = @Value
        POP       ESI           // ESI = @Self

        MOV       EDI, [EAX+4]  // top'
        ADD       EDX, EDI
        PUSH      EDX           // bottom'

        MOV       EAX, [EAX]    // left'
        ADD       ECX, EAX
        PUSH      ECX           // right'

        PUSH      EDI           // top'
        PUSH      EAX           // left'

        MOV       EAX, ESI
        MOV       EDX, ESP
        CALL      SetBoundsRect

        ADD       ESP, size_TRect

        POP       EDI
        POP       ESI
end;

procedure DefaultPaintBackground( Sender: PControl; DC: HDC; Rect: PRect );
asm
        PUSH      EDI

        PUSH      EDI
        MOV       EDI, ESP

        PUSH      ECX
        PUSH      EDX

        MOV       EAX, [EAX].TControl.fColor
        CALL      Color2RGB
        PUSH      EAX
        CALL      CreateSolidBrush
        STOSD
        MOV       EDI, EAX
        CALL      windows.FillRect
        PUSH      EDI
        CALL      DeleteObject
        POP       EDI
end;

procedure TControl.SetCtlColor( Value: TColor );
asm
        PUSH     EBX
        MOV      EBX, EAX

        {$IFNDEF INPACKAGE}
        PUSH     EDX

        CALL     GetWindowHandle
        XCHG     ECX, EAX

        POP      EDX
        {$ELSE}
        MOV      ECX, [EBX].fHandle
        {$ENDIF}

        JECXZ    @@1

        MOVZX    ECX, [EBX].fCommandActions.aSetBkColor
        JECXZ    @@1

        PUSH     EDX

        XCHG     EAX, EDX
        PUSH     ECX
        CALL     Color2RGB
        POP      ECX

        PUSH     EAX        // Color2RGB( Value )
        PUSH     0          // 0
        PUSH     ECX        // fCommandActions.aSetBkColor
        PUSH     EBX        // @ Self
        CALL     TControl.Perform

        POP      EDX

@@1:
        CMP      EDX, [EBX].fColor
        JZ       @@exit

        MOV      [EBX].fColor, EDX

        XOR      ECX, ECX
        XCHG     ECX, [EBX].fTmpBrush
        JECXZ    @@setbrushcolor

        PUSH     EDX
        PUSH     ECX
        CALL     DeleteObject
        POP      EDX

@@setbrushcolor:
        MOV      ECX, [EBX].fBrush
        JECXZ    @@invldte

        XCHG     EAX, ECX
        MOV      ECX, EDX
        //MOV      EDX, go_Color
        XOR      EDX, EDX
        CALL     TGraphicTool.SetInt

@@invldte:
        XCHG     EAX, EBX
        CALL     TControl.Invalidate
@@exit:
        POP      EBX
end;

function TControl.GetParentWnd( NeedHandle: Boolean ): HWnd;
asm
        MOV       ECX, [EAX].fParent
        JECXZ     @@exit

        PUSH      ECX
        TEST      DL, DL
        JZ        @@load_handle

        XCHG      EAX, ECX
        CALL      GetWindowHandle

@@load_handle:
        POP       ECX
        MOV       ECX, [ECX].fHandle

@@exit: XCHG      EAX, ECX

end;

procedure TControl.CreateChildWindows;
asm
        PUSH      ESI
        MOV       ESI, [EAX].TControl.fChildren
        MOV       ECX, [ESI].TList.fCount
        MOV       ESI, [ESI].TList.fItems
        JECXZ     @@exit

@@loop: PUSH      ECX
        LODSD
        CALL      CallTControlCreateWindow
        //CALL      TControl.GetWindowHandle
        POP       ECX
        LOOP      @@loop

@@exit: POP       ESI
end;

procedure TControl.DestroyChildren;
asm
        PUSH      ESI

        MOV       EAX, [EAX].fChildren
        PUSH      EAX
        MOV       ECX, [EAX].TList.fCount
        JECXZ     @@clear
        MOV       ESI, [EAX].TList.fItems
        LEA       ESI, [ESI + ECX*4 - 4]  // is order really important ?

@@loop: STD                               //
        LODSD
        CLD                               //

        PUSH      ECX
        CALL      TObj.RefDec
        POP       ECX

        LOOP      @@loop

@@clear:
        POP       EAX
        CALL      TList.Clear

        POP       ESI
end;

function TControl.ProcessMessage: Boolean;
const size_TMsg = sizeof( TMsg );
asm
        PUSH      EBX
        XCHG      EBX, EAX

        ADD       ESP, -size_TMsg-4

        MOV       EDX, ESP
        PUSH      1
        XOR       ECX, ECX
        PUSH      ECX
        PUSH      ECX
        PUSH      ECX
        PUSH      EDX
        CALL      PeekMessage

        TEST      EAX, EAX
        JZ        @@exit

        MOV       EDX, [ESP].TMsg.message
        CMP       DX, WM_QUIT
        JNZ       @@tran_disp
        MOV       [AppletTerminated], 1
        {$IFDEF   PROVIDE_EXITCODE}
        MOV       EDX, [ESP].TMsg.wParam
        MOV       [ExitCode], EDX
        {$ENDIF   PROVIDE_EXITCODE}
        JMP       @@fin

@@tran_disp:
        MOV       ECX, [EBX].fExMsgProc
        JECXZ     @@do_tran_disp
        MOV       EAX, EBX
        MOV       EDX, ESP
        CALL      ECX
        TEST      AL, AL
        JNZ       @@fin

@@do_tran_disp:
        MOV       EAX, ESP
        PUSH      EAX
        PUSH      EAX
        CALL      TranslateMessage
        CALL      DispatchMessage

@@fin:
        MOV       AX, word ptr [ESP].TMsg.message
        TEST      AX, AX
        SETNZ     AL

@@exit: ADD       ESP, size_TMsg+4
        POP       EBX
end;

procedure TControl.ProcessMessages;
asm
@@loo:  PUSH     EAX
        CALL     ProcessMessage
        DEC      AL
        POP      EAX
        JZ       @@loo
end;

function WndProcForm(Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
const szPaintStruct = sizeof(TPaintStruct);
asm     //cmd    //opd
        {$IFDEF ENDSESSION_HALT}
        CMP      word ptr [EDX].TMsg.message, WM_ENDSESSION
        JNE      @@chk_WM_SETFOCUS

        CMP      [EDX].TMsg.wParam, 0
        JZ       @@ret_false

        CALL     TObj.RefDec
        XOR      EAX, EAX
        MOV      [AppletRunning], AL
        XCHG     EAX, [Applet]
        INC      [AppletTerminated]

        CALL     TObj.RefDec
        CALL     System.@Halt0
        {$ENDIF ENDSESSION_HALT}

@@chk_WM_SETFOCUS:
        CMP      word ptr [EDX].TMsg.message, WM_SETFOCUS
        JNE      @@ret_false

        PUSH     EBX
        PUSH     ESI
        XOR      EBX, EBX
        XCHG     ESI, EAX
      {$IFDEF FIX_MODAL_SETFOCUS}
        MOV      ECX, [ESI].TControl.fModalForm
        JECXZ    @@no_fix_modal_setfocus
        PUSH     [ECX].TControl.fHandle
        CALL     SetFocus
@@no_fix_modal_setfocus:
      {$ENDIF}

        MOV      ECX, [ESI].TControl.FCurrentControl
        JECXZ    @@1
        INC      EBX
        XCHG     EAX, ECX

        // or CreateForm?
        PUSH     EAX
        CALL     CallTControlCreateWindow
        TEST     AL, AL
        POP      EAX
        JZ       @@1
        PUSH     [EAX].TControl.fHandle

        CALL     SetFocus
@@1:    MOV      ECX, [Applet]
        JECXZ    @@ret_EBX
        CMP      ECX, ESI
        JE       @@ret_EBX
        MOV      [ECX].TControl.FCurrentControl, ESI
@@ret_EBX:
        XCHG     EAX, EBX
        POP      ESI
        POP      EBX
        RET

@@ret_false:
        XOR      EAX, EAX
end;

function GetPrevCtrlBoundsRect( P: PControl; var R: TRect ): Boolean;
asm
        MOV       EDX, EBX
        MOV       EAX, [EBX].TControl.fParent
        TEST      EAX, EAX
        JZ        @@exit
          PUSH      EAX
        CALL      TControl.ChildIndex
        TEST      EAX, EAX
        XCHG      EDX, EAX
          POP       EAX
        JZ        @@exit
        DEC       EDX
        CALL      TControl.GetMembers

        POP       ECX  // retaddr
        ADD       ESP, -size_TRect
        MOV       EDX, ESP
        PUSH      ECX
        CALL      TControl.GetBoundsRect
        STC       // return CARRY
@@exit:
end;

function TControl.PlaceUnder: PControl;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        CALL      GetPrevCtrlBoundsRect
        JNC       @@exit
        POP       EDX  // EDX = Left
        MOV       EAX, EBX
        CALL      TControl.SetLeft

        POP       EDX
        POP       EDX
        POP       EDX  // EDX = Bottom

        MOV       EAX, [EBX].fParent
        ADD       EDX, [EAX].fMargin

        MOV       EAX, EBX
        CALL      TControl.SetTop
@@exit:
        XCHG      EAX, EBX
        POP       EBX
end;

function TControl.PlaceDown: PControl;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        CALL      GetPrevCtrlBoundsRect
        JNC       @@exit
        POP       EDX
        POP       EDX
        POP       EDX
        POP       EDX  // EDX = Bottom

        MOV       EAX, [EBX].fParent
        ADD       EDX, [EAX].fMargin

        MOV       EAX, EBX
        CALL      TControl.SetTop
@@exit:
        XCHG       EAX, EBX
        POP       EBX
end;

function TControl.PlaceRight: PControl;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        CALL      GetPrevCtrlBoundsRect
        JNC       @@exit
        POP       EDX
        POP       EDX  // EDX = Top
        MOV       EAX, EBX
        CALL      TControl.SetTop
        POP       EDX  // EDX = Right

        MOV       EAX, [EBX].fParent
        ADD       EDX, [EAX].fMargin

        POP       ECX
        MOV       EAX, EBX
        CALL      TControl.SetLeft
@@exit:
        XCHG      EAX, EBX
        POP       EBX
end;

function TControl.SetSize(W, H: Integer): PControl;
asm
        PUSH      EBX
        XCHG      EBX, EAX
        SUB  ESP, 16
        XCHG      EAX, EDX
        MOV  EDX, ESP
        PUSH      ECX // save H
        PUSH      EAX // save W
        MOV  EAX, EBX
        CALL GetBoundsRect
        POP       ECX // pop W
        JECXZ     @@nochg_W
        ADD       ECX, [ESP+4].TRect.Left
        MOV       [ESP+4].TRect.Right, ECX
@@nochg_W:
        POP       ECX // pop H
        JECXZ     @@nochg_H
        ADD       ECX, [ESP].TRect.Top
        MOV       [ESP].TRect.Bottom, ECX
@@nochg_H:
        MOV       EAX, EBX
        MOV       EDX, ESP
        CALL      TControl.SetBoundsRect
        ADD  ESP, 16
        XCHG      EAX, EBX
        POP       EBX
end;

function TControl.AlignLeft(P: PControl): PControl;
asm
        PUSH     EAX
        MOV      EAX, EDX
        CALL     TControl.GetLeft
        MOV      EDX, EAX
        POP      EAX
        PUSH     EAX
        CALL     TControl.SetLeft
        POP      EAX
end;

function TControl.AlignTop(P: PControl): PControl;
asm
        PUSH     EAX
        MOV      EAX, EDX
        CALL     TControl.GetTop
        MOV      EDX, EAX
        POP      EAX
        PUSH     EAX
        CALL     TControl.SetTop
        POP      EAX
end;

procedure TControl.DoClick;
asm
        PUSH     EAX
        CALL     [EAX].fControlClick
        POP      EDX

        MOV      ECX, [EDX].fOnClick.TMethod.Code
        JECXZ    @@exit
        MOV      EAX, [EDX].fOnClick.TMethod.Data
        CALL     ECX
@@exit:
end;

function TControl.ParentForm: PControl;
asm
@@1:    CMP      [EAX].fIsControl, 0
        JZ       @@exit
        MOV      EAX, [EAX].fParent
        TEST     EAX, EAX
        JNZ      @@1
@@exit:
end;

procedure TControl.SetProgressColor(const Value: TColor);
asm
        PUSH     EDX
        PUSH     EAX
        MOV      EAX, EDX
        CALL     Color2RGB
        POP      EDX
        PUSH     EDX
        PUSH     EAX
        PUSH     0
        PUSH     PBM_SETBARCOLOR
        PUSH     EDX
        CALL     Perform
        TEST     EAX, EAX
        POP      EAX
        POP      EDX
        JZ       @@exit
        MOV      [EAX].fTextColor, EDX
@@exit:
end;

function TControl.GetFont: PGraphicTool;
asm
        MOV      ECX, [EAX].FFont
        INC      ECX
        LOOP     @@exit
        PUSH     EAX
        CALL     NewFont
        {$IFDEF USE_AUTOFREE4CONTROLS}
        POP      EDX
        PUSH     EDX
        PUSH     EAX
        XCHG     eax, edx
        CALL     TObj.Add2AutoFree
        POP      EAX
        {$ENDIF}
        POP      EDX
        MOV      [EDX].FFont, EAX
        MOV      ECX, [EDX].fTextColor
        MOV      [EAX].TGraphicTool.fData.Color, ECX
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Code, offset[FontChanged]
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Data, EDX
        RET
@@exit: XCHG     EAX, ECX
end;

function TControl.GetBrush: PGraphicTool;
asm
        MOV      ECX, [EAX].FBrush
        INC      ECX
        LOOP     @@exit
        PUSH     EAX
        CALL     NewBrush
        POP      EDX   // @ Self
        MOV      [EDX].FBrush, EAX
        MOV      ECX, [EDX].fColor
        MOV      [EAX].TGraphicTool.fData.Color, ECX
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Code, offset[BrushChanged]
        MOV      [EAX].TGraphicTool.fOnChange.TMethod.Data, EDX
        {$IFDEF USE_AUTOFREE4CONTROLS}
        PUSH     EAX
        XCHG     EAX, EDX
        CALL     TControl.Add2AutoFree
        POP      ECX
        {$ENDIF}
@@exit: XCHG     EAX, ECX
end;

procedure TControl.FontChanged(Sender: PGraphicTool);
asm
        MOV      ECX, [EDX].TGraphicTool.fData.Color
        MOV      [EAX].fTextColor, ECX
        PUSH     EAX
        CALL     ApplyFont2Wnd
        POP      EAX
        CALL     Invalidate
end;

procedure TControl.BrushChanged(Sender: PGraphicTool);
asm
        MOV      ECX, [EDX].TGraphicTool.fData.Color
        MOV      [EAX].fColor, ECX
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fTmpBrush
        JECXZ    @@inv
        PUSH     EAX
        PUSH     ECX
        CALL     DeleteObject
        POP      EAX
@@inv:  CALL     Invalidate
end;

procedure DoApplyFont2Wnd( _Self: PControl );
asm
        PUSH       EBX
        XCHG       EBX, EAX

        MOV        ECX, [EBX].TControl.fFont
        JECXZ      @@exit
        XCHG       EAX, ECX

        MOV        ECX, [EBX].TControl.fHandle
        JECXZ      @@0

        MOV        EDX, [EAX].TGraphicTool.fData.Color
        MOV        [EBX].TControl.fTextColor, EDX

        PUSH       $FFFF
        CALL       TGraphicTool.GetHandle
        PUSH       EAX
        PUSH       WM_SETFONT
        PUSH       EBX
        CALL       TControl.Perform

@@0:
        XOR        ECX, ECX
        XCHG       ECX, [EBX].TControl.fCanvas
        JECXZ      @@1

        XCHG       EAX, ECX
        CALL       TObj.RefDec
@@1:
        XCHG       EAX, EBX
        CALL       TControl.DoAutoSize
@@exit:
        POP        EBX
end;

function TControl.ResizeParent: PControl;
asm
        LEA       EDX, [TControl.ResizeParentRight]
        PUSH      EDX
        CALL      EDX
        CALL      TControl.ResizeParentBottom
end;

function TControl.ResizeParentBottom: PControl;
asm
        PUSH      EAX
        PUSH      EBX
        MOV       EBX, [EAX].fParent
        TEST      EBX, EBX
        JZ        @@exit

        MOV       EDX, [EAX].fBoundsRect.Bottom
        ADD       EDX, [EBX].fMargin

        TEST      [EBX].fChangedPosSz, 20h
        JZ        @@1

        PUSH      EDX
        MOV       EAX, EBX
        CALL      GetClientHeight
        POP       EDX

        CMP       EDX, EAX
        JE        @@exit
@@1:
        MOV       EAX, EBX
        CALL      TControl.SetClientHeight
        OR        [EBX].fChangedPosSz, 20h
@@exit:
        POP       EBX
        POP       EAX
end;

function TControl.ResizeParentRight: PControl;
asm
        PUSH      EAX
        PUSH      EBX
        MOV       EBX, [EAX].fParent
        TEST      EBX, EBX
        JZ        @@exit

        MOV       EDX, [EAX].fBoundsRect.Right
        ADD       EDX, [EBX].fMargin

        TEST      [EBX].fChangedPosSz, 10h
        JZ        @@1

        PUSH      EDX
        MOV       EAX, EBX
        CALL      GetClientWidth
        POP       EDX

        CMP       EDX, EAX
        JLE       @@exit
@@1:
        MOV       EAX, EBX
        CALL      TControl.SetClientWidth
        OR        [EBX].fChangedPosSz, 10h
@@exit:
        POP       EBX
        POP       EAX
end;

function TControl.GetClientHeight: Integer;
asm
        ADD       ESP, -size_TRect
        MOV       EDX, ESP
        CALL      TControl.ClientRect
        POP       EDX
        POP       ECX            // Top
        POP       EDX
        POP       EAX            // Bottom
        SUB       EAX, ECX       // Result = Bottom - Top
end;

function TControl.GetClientWidth: Integer;
asm
        ADD       ESP, -size_TRect
        MOV       EDX, ESP
        CALL      TControl.ClientRect
        POP       ECX            // Left
        POP       EDX
        POP       EAX            // Right
        SUB       EAX, ECX       // Result = Right - Left
        POP       EDX
end;

procedure TControl.SetClientHeight(const Value: Integer);
asm
        PUSH      EBX
         PUSH      EDX

        MOV       EBX, EAX
        CALL      TControl.GetClientHeight
          PUSH      EAX
        MOV       EAX, EBX
        CALL      TControl.GetHeight // EAX = Height

          POP       EDX              // EDX = ClientHeight
        SUB       EAX, EDX           // EAX = Delta
         POP       EDX               // EDX = Value
        ADD       EDX, EAX           // EDX = Value + Delta
        XCHG      EAX, EBX           // EAX = @Self
        CALL      TControl.SetHeight
        POP       EBX
end;

procedure TControl.SetClientWidth(const Value: Integer);
asm
        PUSH      EBX
         PUSH      EDX

        MOV       EBX, EAX
        CALL      TControl.GetClientWidth
          PUSH      EAX
        MOV       EAX, EBX
        CALL      TControl.GetWidth  // EAX = Width

          POP       EDX              // EDX = ClientWidth
        SUB       EAX, EDX           // EAX = Width - ClientWidth
         POP       EDX               // EDX = Value
        ADD       EDX, EAX           // EDX = Value + Delta
        XCHG      EAX, EBX           // EAX = @Self
        CALL      TControl.SetWidth
        POP       EBX
end;

function TControl.CenterOnParent: PControl;
asm
        PUSHAD

        XCHG     ESI, EAX
        MOV      ECX, [ESI].fParent
        JECXZ    @@1
        CMP      [ESI].fIsControl, 0
        JNZ      @@2

@@1:
        PUSH     SM_CYSCREEN
        CALL     GetSystemMetrics
        PUSH     EAX

        PUSH     SM_CXSCREEN
        CALL     GetSystemMetrics
        PUSH     EAX

        PUSH     0
        PUSH     0               // ESP -> Rect( 0, 0, CX, CY )

        JMP      @@3

@@2:    ADD      ESP, -size_TRect
        MOV      EDX, ESP
        XCHG     EAX, ECX
        CALL     TControl.ClientRect
                                 // ESP -> ClientRect
@@3:    MOV      EAX, ESI
        CALL     GetWindowHandle

        MOV      EAX, ESI
        CALL     GetWidth

        POP      EDX       // left
        ADD      EAX, EDX          // + width

        POP      EDI       // top
        POP      EDX       // right

        SUB      EDX, EAX
        SAR      EDX, 1

        MOV      EAX, ESI
        CALL     SetLeft

        MOV      EAX, ESI
        CALL     GetHeight

        ADD      EAX, EDI  // height + top

        POP      EDX       // bottom
        SUB      EDX, EAX
        SAR      EDX, 1

        XCHG     EAX, ESI
        CALL     SetTop

        POPAD
end;

function TControl.GetHasBorder: Boolean;
const style_mask = WS_BORDER or WS_THICKFRAME or WS_DLGFRAME;
asm
        CALL     UpdateWndStyles
        MOV      EDX, [EAX].fStyle
        AND      EDX, style_mask
        SETNZ    DL
        MOV      EAX, [EAX].fExStyle
        AND      EAX, WS_EX_CLIENTEDGE
        SETNZ    AL
        OR       AL, DL
end;

function TControl.GetHasCaption: Boolean;
const style_mask1 = (WS_POPUP or WS_DLGFRAME) shr 16;
      style_mask2 = WS_CAPTION shr 16;
asm
        CALL     UpdateWndStyles
        MOV      ECX, [EAX].fStyle + 2
        MOV      EDX, ECX
        MOV      AL, 1
        AND      DX, style_mask1
        JZ       @@1
        AND      CX, style_mask2
        JNZ      @@1
        XOR      EAX, EAX
@@1:
end;

procedure TControl.SetHasCaption(const Value: Boolean);
const style_mask = not (WS_BORDER or WS_THICKFRAME or WS_DLGFRAME or WS_CAPTION
                             or WS_MINIMIZEBOX or WS_MAXIMIZEBOX or WS_SYSMENU);
      exstyle_mask = not (WS_EX_CONTROLPARENT or WS_EX_DLGMODALFRAME
                                or WS_EX_WINDOWEDGE or WS_EX_CLIENTEDGE);
asm
        PUSH     EAX
          PUSH     EDX

            CALL     GetHasCaption
          POP      ECX
          CMP      AL, CL

        POP      EAX
        JZ       @@exit   // Value = HasCaption

        MOV      EDX, [EAX].fStyle
        DEC      CL
        JNZ      @@1      // if not Value -> @@1

        AND      EDX, not WS_POPUP
        OR       EDX, WS_CAPTION
        JMP      @@set_style

@@1:
        CMP      [EAX].fIsControl, 0
        JNZ      @@2               // if fIsControl -> @@2

        AND      EDX, not (WS_CAPTION or WS_SYSMENU)
        OR       EDX, WS_POPUP
        JMP      @@3

@@2:
        AND      EDX, not WS_CAPTION
        OR       EDX, WS_DLGFRAME

@@3:
        PUSH     EDX

        MOV      EDX, [EAX].fExStyle
        OR       EDX, WS_EX_DLGMODALFRAME

        PUSH     EAX
        CALL     SetExStyle
        POP      EAX

        POP      EDX
@@set_style:
        CALL     SetStyle
@@exit:
end;

function TControl.GetCanResize: Boolean;
asm
        MOV      AL, [EAX].fPreventResize
        {$IFDEF PARANOIA} DB $34,$01 {$ELSE} XOR AL, 1 {$ENDIF}
end;

procedure TControl.SetCanResize( const Value: Boolean );
asm
        PUSH     EBX
        MOV      EBX, EAX

            CALL     GetCanResize
        CMP      AL, DL

        JZ       @@exit   // Value = CanResize
        MOV      [EBX].fPreventResize, AL
        {$IFDEF CANRESIZE_THICKFRAME}
        TEST     DL, DL

        MOV      EDX, [EBX].fStyle
        JZ       @@set_thick

        OR       EDX, WS_THICKFRAME
        JMP      @@set_style

@@set_thick:
        AND      EDX, not WS_THICKFRAME

@@set_style:
        MOV      EAX, EBX
        CALL     SetStyle
        {$ENDIF CANRESIZE_THICKFRAME}

        MOV      EAX, EBX
        CALL     GetWindowHandle

        MOV      EAX, EBX
        CALL     GetWidth
        MOV      [EBX].FFixWidth, EAX

        MOV      EAX, EBX
        CALL     GetHeight
        MOV      [EBX].FFixHeight, EAX

        XCHG     EAX, EBX
        MOV      EDX, offset[WndProcCanResize]
        CALL     TControl.AttachProc
@@exit:
        POP      EBX
end;

function TControl.GetStayOnTop: Boolean;
asm
        CALL     UpdateWndStyles
        TEST     byte ptr [EAX].fExStyle, WS_EX_TOPMOST
        SETNZ    AL
end;

procedure TControl.SetStayOnTop(const Value: Boolean);
asm
        PUSH     EAX
          PUSH     EDX

            CALL     GetStayOnTop
          POP      ECX
          MOVZX    ECX, CL
          CMP      AL, CL

        POP      EAX
        JZ       @@exit   // Value = StayOnTop

        MOV      EDX, [EAX].fHandle
        TEST     EDX, EDX
        JZ       @@1

        PUSH     SWP_NOMOVE or SWP_NOSIZE or SWP_NOACTIVATE
        XOR      EAX, EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     EAX
        DEC      ECX
        DEC      ECX
        PUSH     ECX

        PUSH     EDX
        CALL     SetWindowPos
        RET

@@1:
        JECXZ    @@1and

        OR       byte ptr [EAX].fExStyle, WS_EX_TOPMOST
        RET

@@1and: AND      byte ptr [EAX].fExStyle, not WS_EX_TOPMOST

@@exit:
end;

function TControl.UpdateWndStyles: PControl;
asm
        MOV      ECX, [EAX].fHandle
        JECXZ    @@exit

        PUSH     EBX

        XCHG     EBX, EAX
          PUSH     GCL_STYLE
          PUSH     ECX

          PUSH     GWL_EXSTYLE
          PUSH     ECX

          PUSH     GWL_STYLE
          PUSH     ECX

          CALL     GetWindowLong
          MOV      [EBX].fStyle, EAX

          CALL     GetWindowLong
          MOV      [EBX].fExStyle, EAX

          CALL     GetClassLong
          MOV      [EBX].fClsStyle, EAX
        XCHG     EAX, EBX
        POP      EBX
@@exit:
end;

function TControl.GetChecked: Boolean;
asm
        TEST     [EAX].fBitBtnOptions, 8 //1 shl Ord(bboFixed)
        JZ       @@1
        MOV      AL, [EAX].fChecked
        RET
@@1:
        PUSH     0
        PUSH     0
        PUSH     BM_GETCHECK
        PUSH     EAX
        CALL     Perform
@@exit:
end;

procedure TControl.Set_Checked(const Value: Boolean);
asm
        TEST     [EAX].fBitBtnOptions, 8 //1 shl Ord(bboFixed)
        JZ       @@1
        MOV      [EAX].fChecked, DL
        JMP      Invalidate
@@1:
        PUSH     0
        MOVZX    EDX, DL
        PUSH     EDX
        PUSH     BM_SETCHECK
        PUSH     EAX
        Call     Perform
end;

function TControl.SetRadioCheckedOld: PControl;
asm
        PUSH     EAX
        MOV      ECX, [EAX].fParent
        JECXZ    @@exit

        PUSH     [EAX].fMenu
        PUSH     [ECX].fRadioLast
        PUSH     [ECX].fRadio1st
        MOV      EAX, ECX
        CALL     GetWindowHandle
        PUSH     EAX
        CALL     CheckRadioButton
@@exit:
        POP      EAX
end;

function TControl.SetRadioChecked: PControl;
asm
  PUSH  EAX
  PUSH  DWORD PTR[EAX].fTabStop
  MOV   [EAX].fTabStop, 0
@@1:
  CALL  DoClick
  POP   EDX
  POP   EAX
  MOV   [EAX].fTabStop, DL
end;

function TControl.GetSelStart: Integer;
asm
         MOVZX    ECX, [EAX].fCommandActions.aGetSelRange
         JECXZ    @@exit
         XOR      EDX, EDX
         PUSH     EDX // space for Result
         PUSH     EDX // 0
         LEA      EDX, [ESP+4]
         PUSH     EDX // @ Result
         PUSH     ECX // EM_GETSEL
         PUSH     EAX
         CALL     Perform
         POP      ECX // Result
@@exit:
         XCHG     EAX, ECX
end;

function TControl.GetSelLength: Integer;
asm
        XOR       EDX, EDX
        MOVZX     ECX, word ptr[EAX].fCommandActions.aGetSelCount
        JECXZ     @@ret_ecx

        CMP       CX, EM_GETSEL
        JNZ       @@1
        PUSH      EDX
        PUSH      EDX
        MOV       EDX, ESP
        PUSH      EDX
        ADD       EDX, 4
        PUSH      EDX
        PUSH      ECX
        PUSH      EAX
        CALL      Perform
        POP       ECX
        POP       EDX
        SUB       ECX, EDX
@@ret_ecx:
        XCHG      EAX, ECX
        RET

@@1:    // LB_GETSELCOUNT, LVM_GETSELECTEDCOUNT
        PUSH      EDX // 0
        PUSH      EDX // 0
        PUSH      ECX // aGetSelCount
        PUSH      EAX // Handle
        CALL      Perform
@@fin_EAX:
end;

procedure TControl.SetSelLength(const Value: Integer);
asm
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     EAX
        PUSH     EDX
        CALL     GetSelStart
        POP      ECX
        POP      EDX
        ADD      ECX, EAX
        PUSH     ECX
        MOVZX    ECX, [EDX].fCommandActions.aSetSelRange
        JECXZ    @@check_ex
        PUSH     EAX
        JMP      @@perform

@@check_ex:
        MOVZX    ECX, [EDX].fCommandActions.aExSetSelRange
        JECXZ    @@exit
        PUSH     EAX
        PUSH     ESP
        PUSH     0
@@perform:
        PUSH     ECX
        PUSH     EDX
        CALL     Perform
@@exit: MOV      ESP, EBP
        POP      EBP
end;

{$IFDEF ASM_UNICODE}
function TControl.GetItems(Idx: Integer): String;
asm
        PUSH     ESI
        PUSH     EDI
        PUSH     EBX
        PUSH     EBP
        MOV      EBP, ESP

        MOV      EBX, EAX       // @Self
        MOV      ESI, EDX       // Idx
        MOV      EDI, ECX       // @Result

        CALL     Item2Pos
        PUSH     0              // push  0
        PUSH     EAX            // store Pos

        XCHG     EDX, EAX
        MOV      EAX, EBX
        CALL     Pos2Item       // EAX = Idx'
        XCHG     ESI, EAX       // ESI = Idx'

        XOR      EAX, EAX
        MOVZX    ECX, [EBX].fCommandActions.aGetItemLength
        JECXZ    @@ret_empty

        PUSH     ECX            // push aGetItemLength

        PUSH     EBX
        CALL     Perform

        TEST     EAX, EAX
        JZ       @@ret_empty

        PUSH     EAX              // save L
        ADD      EAX, 4

        CALL     System.@GetMem   // GetMem( L+4 )
        POP      EDX              // restore L
        LEA      ECX, [EDX+1]
        MOV      dword ptr [EAX], ECX
        MOVZX    ECX, [EBX].fCommandActions.aGetItemText
        JECXZ    @@ret_buf

        PUSH     EDX              // save L
        //MOV      word ptr [EAX], DX

        PUSH     EAX
          PUSH     EAX            // push Buf
          PUSH     ESI            // push Idx

          PUSH     ECX            // push aGetItemText
          PUSH     EBX
          CALL     Perform
        POP      EAX

        POP      EDX
@@ret_buf:
        MOV      byte ptr [EAX + EDX], 0   // Buf[ L ] := #0

@@ret_empty:     // EAX = 0
        XCHG     EDX, EAX
        MOV      EAX, EDI
        PUSH     EDX
        CALL     System.@LStrFromPChar
        POP      ECX
        JECXZ    @@exit
        XCHG     EAX, ECX
        CALL     System.@FreeMem

@@exit:
        MOV      ESP, EBP
        POP      EBP
        POP      EBX
        POP      EDI
        POP      ESI
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
procedure TControl.SetItems(Idx: Integer; const Value: String);
asm
        PUSH     EDI
        PUSH     EBX
        XCHG     EBX, EAX
        XCHG     EDI, EDX       // EDI = Idx
        CALL     ECX2PChar
        PUSH     ECX       // @Value[1]

        MOVZX    ECX, [EBX].fCommandActions.aSetItemText
        JECXZ    @@1

        PUSH     0
        PUSH     ECX

        MOV      EDX, EDI
        MOV      EAX, EBX
        CALL     Item2Pos
        PUSH     EAX            // store Strt

        MOV      EDX, EDI
        INC      EDX
        MOV      EAX, EBX
        CALL     Item2Pos
        POP      EDX            // EDX = Strt

        SUB      EAX, EDX
        PUSH     EAX            // store L

        MOV      EAX, EBX
        CALL     SetSelStart

        POP      EDX            // EDX = L
        PUSH     EBX            // prepare @Self for Perform
        XCHG     EAX, EBX
        CALL     SetSelLength

        // @Value[1] already in stack,
        // 0 already in stack
        // aSetItemText already in stack
        // @Self already in stack

        CALL     Perform
        JMP      @@exit

@@1:    // @Value[1] in stack already
        POP      EDX
        MOVZX    ECX, [EBX].fCommandActions.aDeleteItem
        JECXZ    @@exit

        {$IFNDEF  NOT_FIX_CURINDEX}
        PUSH     ESI
        PUSH     EBP

        PUSH     EDX

        MOV      EAX, EBX               // +AK
        CALL     GetCurIndex            // +AK
        XCHG     ESI, EAX    // ESI = TmpCurIdx

        MOV      EAX, EBX
        MOV      EDX, EDI
        CALL     GetItemData
        XCHG     EBP, EAX   // EBP = TmpData

        MOV      EDX, EDI
        MOV      EAX, EBX
        CALL     Delete

        MOV      EAX, EBX               // *AK
        MOV      EDX, EDI
        POP      ECX
        CALL     Insert

        MOV      ECX, EBP // ECX = TmpData
        MOV      EDX, EDI
        MOV      EAX, EBX
        CALL     SetItemData

        XCHG     EAX, EBX               // +AK
        MOV      EDX, ESI               // +AK
        CALL     SetCurIndex            // +AK

        POP      EBP
        POP      ESI
        {$ELSE NOT_FIX_CURINDEX}
        PUSH     EDX

        MOV      EDX, EDI
        MOV      EAX, EBX
        CALL     Delete

        XCHG     EAX, EBX
        XCHG     EDX, EDI

        POP      ECX
        CALL     Insert
        {$ENDIF NOT_FIX_CURINDEX}

@@exit:
        POP      EBX
        POP      EDI
end;
{$ENDIF ASM_UNICODE}

function TControl.GetItemsCount: Integer;
asm
        PUSH     0
        MOVZX    ECX, [EAX].fCommandActions.aGetCount
        JECXZ    @@ret_0
        PUSH     0
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        PUSH     EAX

@@ret_0:
        POP      EAX
end;

procedure HelpConvertItem2Pos;
asm
        JECXZ     @@exit
        PUSH      0
        PUSH      EDX
        PUSH      ECX
        PUSH      EAX
        CALL      TControl.Perform
        {XOR       EDX, EDX
        TEST      EAX, EAX
        JL        @@exit
        RET}
        XCHG      EDX, EAX
@@exit:
        XCHG      EAX, EDX
end;

function TControl.Item2Pos(ItemIdx: Integer): DWORD;
asm
        MOVZX     ECX, [EAX].fCommandActions.aItem2Pos
        JMP       HelpConvertItem2Pos
end;

function TControl.Pos2Item(Pos: Integer): DWORD;
asm
        MOVZX     ECX, [EAX].fCommandActions.aPos2Item
        JMP       HelpConvertItem2Pos
end;

{$IFDEF ASM_UNICODE}
function TControl.Add(const S: KOLString): Integer;
asm
        PUSH     EBX
        MOV      EBX, EAX               // EBX = @Self

        MOVZX    ECX, [EBX].fCommandActions.aAddItem   // ECX = aAddItem
        JECXZ    @@chk_addtext

        CALL     EDX2PChar
        PUSH     EDX
        PUSH     0
        PUSH     ECX
        PUSH     EBX
        CALL     Perform
        PUSH     EAX

        MOV      EAX, EBX
        CALL     TControl.GetItemsCount
        XCHG     EAX, ECX
        LOOP     @@ret_EAX

        XCHG     EAX, EBX
        INC      ECX
        XOR      EDX, EDX
        CALL     TControl.SetItemSelected
@@ret_EAX:
        POP      EAX
        JMP      @@exit

@@chk_addtext:
        MOV      ECX, [EBX].fCommandActions.aAddText
        JECXZ    @@add_text_simple

        CALL     ECX
        JMP      @@exit_0

@@add_text_simple:
        LEA      EAX, [EBX].fCaption
        CALL     System.@LStrCat
        MOV      EDX, [EBX].fCaption
        MOV      EAX, EBX
        CALL     SetCaption

@@exit_0:
        XOR      EAX, EAX
@@exit:
        POP      EBX
end;
{$ENDIF}

procedure TControl.Delete(Idx: Integer);
asm
        MOVZX    ECX, [EAX].fCommandActions.aDeleteItem
        JECXZ    @@exit

        PUSH     0
        PUSH     EDX
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
@@exit:
end;

{$IFDEF ASM_UNICODE}
function TControl.Insert(Idx: Integer; const S: String): Integer;
asm
         CALL    ECX2PChar
         PUSH    ECX
         MOVZX   ECX, [EAX].fCommandActions.aInsertItem
         JECXZ   @@exit_1

         PUSH    EDX
         PUSH    ECX
         PUSH    EAX
         CALL    Perform
         RET

@@exit_1:OR      EAX, -1
         POP     ECX
end;
{$ENDIF ASM_UNICODE}

function TControl.GetItemSelected(ItemIdx: Integer): Boolean;
asm
        MOVZX    ECX, [EAX].fCommandActions.aGetSelected
        JECXZ    @@check_range

        PUSH     1
        CMP      CL, CB_GETCURSEL and $FF
        JNZ      @@1
        MOV      [ESP], EDX
@@1:
        PUSH     LVIS_SELECTED // 2
        PUSH     EDX
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        POP      EDX
        CMP      EAX, EDX
        SETZ     AL
        RET

@@check_range:
        PUSH     EBX
        PUSH     ESI
        XCHG     ESI, EDX
        MOV      EBX, EAX

        CALL     GetSelStart
        XCHG     EBX, EAX
        CALL     GetSelLength

        SUB      ESI, EBX
        JL       @@ret_false

        CMP      EAX, ESI
@@ret_false:
        SETGE    AL
        POP      ESI
        POP      EBX
end;

procedure TControl.SetItemSelected(ItemIdx: Integer; const Value: Boolean);
asm
        PUSH     EDX
        PUSH     ECX
        MOVZX    ECX, [EAX].fCommandActions.aSetSelected
        JECXZ    @@chk_aSetCurrent

@@0:
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        RET

@@chk_aSetCurrent:
        POP      ECX
        MOVZX    ECX, [EAX].fCommandActions.aSetCurrent
        JECXZ    @@chk_aSetSelRange

        POP      EDX
        PUSH     0
        JMP      @@3

@@chk_aSetSelRange:
        MOVZX    ECX, [EAX].fCommandActions.aSetSelRange
        JECXZ    @@chk_aExSetSelRange
@@3:
        PUSH     EDX
        JMP      @@0

@@else: MOV      [EAX].FCurIndex, EDX
        CALL     Invalidate
        JMP      @@exit

@@chk_aExSetSelRange:
        MOVZX    ECX, [EAX].fCommandActions.aExSetSelRange
        JECXZ    @@else

        PUSH     EDX
        PUSH     ESP
        PUSH     0
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        POP      ECX

@@exit:
        POP      ECX
end;

procedure TControl.SetCtl3D(const Value: Boolean);
asm
        MOV      [EAX].fCtl3Dchild, DL
        //CMP      [EAX].fCtl3D, DL
        //JE       @@exit
        MOV      [EAX].fCtl3D, DL
        PUSHAD
        CALL     UpdateWndStyles
        POPAD
        MOV      ECX, [EAX].fExStyle
        DEC      DL
        MOV      EDX, [EAX].fStyle
        JNZ      @@1
        AND      EDX, not WS_BORDER
        OR       CH, WS_EX_CLIENTEDGE shr 8
        JMP      @@2
@@1:
        OR       EDX, WS_BORDER
        AND      CH, not(WS_EX_CLIENTEDGE shr 8)
@@2:
        PUSH     ECX
        PUSH     EAX
        CALL     SetStyle
        POP      EAX
        POP      EDX
        JMP      SetExStyle
@@exit:
end;

function TControl.Shift(dX, dY: Integer): PControl;
asm
        PUSHAD
        ADD      EDX, [EAX].fBoundsRect.TRect.Left
        CALL     SetLeft
        POPAD
        PUSH     EAX
        MOV      EDX, [EAX].fBoundsRect.TRect.Top
        ADD      EDX, ECX
        CALL     SetTop
        POP      EAX
end;

function CollectTabControls( Form: PControl ): PList;
asm
        PUSH     EDI
        PUSH     EAX
        CALL     NewList
        XCHG     EDI, EAX
        POP      EAX
        CALL     @@collecttab
        XCHG     EAX, EDI
        POP      EDI
        RET
@@collecttab:
        { <- EDI = Result:PList
             EAX = Form (or Control)
        }
        PUSH     EBP
        XOR      EBP, EBP // Result := FALSE;
        PUSH     ESI
        PUSH     EBX
        MOV      EDX, [EAX].TControl.fChildren
        MOV      ECX, [EDX].TList.fCount
        MOV      ESI, [EDX].TList.fItems
        JECXZ    @@e_loop
@@loo:  PUSH     ECX
        LODSD

          PUSH     EAX

        TEST     byte ptr [EAX].TControl.fStyle+2, WS_TABSTOP shr 16
        JZ       @@call_recur

        MOV      DL, [EAX].TControl.fTabStop
        AND      DL, [EAX].TControl.fEnabled
        JZ       @@call_recur

        CALL     TControl.GetToBeVisible
        TEST     AL, AL
        POP      EAX
        JZ       @@next
        PUSH     EAX

          XCHG     EDX, EAX
          PUSH     ESI
          MOV      ECX, [EDI].TList.fCount
          MOV      ESI, [EDI].TList.fItems
          XOR      EBX, EBX
          JECXZ    @@e_loo2
@@loo2:   LODSD
          MOV      EAX, [EAX].TControl.fTabOrder
          CMP      EAX, [EDX].TControl.fTabOrder
          JLE      @@next2
          POP      ESI
          MOV      ECX, EDX
          MOV      EDX, EBX
          MOV      EAX, EDI
          CALL     TList.Insert
          JMP      @@call_recur

@@next2:  INC      EBX
          LOOP     @@loo2
@@e_loo2:
          POP      ESI
          MOV      EAX, EDI
          CALL     TList.Add

@@call_recur:
          OR       EBP, 1 // Result := TRUE;
          POP      EAX
          MOVZX    ECX, [EAX].TControl.fEnabled
          JECXZ    @@next
          PUSH     EAX
          CALL     @@collecttab
          POP      EDX
          JZ       @@next

          MOV      EAX, EDI
          CALL     TList.Remove

@@next: POP      ECX
        LOOP     @@loo

@@e_loop:
        POP      EBX
        POP      ESI
        TEST     EBP, EBP
        POP      EBP
end;

procedure Tabulate2Next( Form: PControl; Dir: Integer );
asm
        PUSHAD
        PUSH     EAX      // save Form
        MOV      EBX, EAX
        MOV      EBP, EDX // EBP = Dir (direction <0 or >0)
        CALL     CollectTabControls
        XCHG     EDI, EAX // EDI = CL (list of controls)

        MOV      ECX, [EBX].TControl.fCurrentControl // C := Form.fCurrentControl
        XOR      EBX, EBX // I = 0
        JECXZ    @@1
        MOV      EBX, [ECX].TControl.fTabOrder // I = C.fTabOrder
@@1:
        MOV      ECX, [EDI].TList.fCount
        MOV      ESI, [EDI].TList.fItems
        XOR      EDX, EDX
        PUSH     EDX      // Ctrl1 = nil
        PUSH     EDX      // Ctrl2 = nil
        TEST     ECX, ECX
        JZ       @@e_loop

@@loop: PUSH     ECX
        LODSD
        CMP      [EAX].TControl.fTabOrder, EBX
        JZ       @@next

        MOV      ECX, [ESP+8] // ECX = Ctrl1
        JECXZ    @@c1nil
        MOV      ECX, [ECX].TControl.fTabOrder // ECX = Ctrl1.fTabOrder
        TEST     EBP, EBP
        JGE      @@c1ge

        CMP      [EAX].TControl.fTabOrder, EBX
        JGE      @@2
        CMP      [EAX].TControl.fTabOrder, ECX
        JLE      @@2

@@c1new:
        MOV      [ESP+8], EAX // Ctrl1 := C
        JMP      @@2

@@c1ge: CMP      [EAX].TControl.fTabOrder, EBX
        JLE      @@2
        CMP      [EAX].TControl.fTabOrder, ECX
        JL       @@c1new
        JMP      @@2

@@c1nil:
        TEST     EBP, EBP
        JL       @@c1nil_dirL
        CMP      [EAX].TControl.fTabOrder, EBX
        JG       @@c1new
        JMP      @@2

@@c1nil_dirL:
        CMP      [EAX].TControl.fTabOrder, EBX
        JL       @@c1new

@@2:
        MOV      ECX, [ESP+4] // ECX = Ctrl2
        JECXZ    @@c2new
        MOV      ECX, [ECX].TControl.fTabOrder

        TEST     EBP, EBP
        JL       @@c2dirL
        CMP      [EAX].TControl.fTabOrder, ECX
        JGE      @@next
        JMP      @@c2new

@@c2dirL:
        CMP      [EAX].TControl.fTabOrder, ECX
        JLE      @@next
@@c2new:
        MOV      [ESP+4], EAX

@@next: POP      ECX
        DEC      ECX
        JNZ      @@loop
        //LOOP     @@loop
@@e_loop:

        POP      EDX // Ctrl2
        POP      ECX // Ctrl1
        INC      ECX
        LOOP     @@3
        MOV      ECX, EDX
@@3:
        POP      EBX // EBX = Form
        JECXZ    @@exit

        XCHG     EAX, ECX
        {$IFDEF USE_GRAPHCTLS}
        CMP      [EAX].TControl.fWindowed, 0
        JZ       @@4
        {$ENDIF}
        MOV      ECX, [EAX].TControl.fHandle
        JECXZ    @@no_handle
@@4:
        INC      [EAX].TControl.fClickDisabled

        PUSH     EAX
        MOV      DL, 1
        CALL     TControl.SetFocused
        POP      EAX

        DEC      [EAX].TControl.fClickDisabled

@@no_handle:
        MOV      [EBX].TControl.fCurrentControl, EAX

@@exit:
        XCHG     EAX, EDI
        CALL     TObj.RefDec
        POPAD
end;

function Tabulate2Control( Self_: PControl; Key: DWORD; checkOnly: Boolean ): Boolean;
const tk_Tab = 1;
      tk_LR  = 2;
      tk_UD  = 4;
      tk_PuPd= 8;
asm
        PUSH     ESI
        MOV      ESI, offset[@@data]
        PUSH     EAX
        MOV      AH, 9
@@loop:
        LODSB
        CMP      DL, AL
        JE       @@1
        LODSB
        CMP      DL, AL
        JE       @@2
        ADD      AH, AH
        JNB      @@loop
        POP      EAX
@@exit0:
        XOR      EAX, EAX
        JMP      @@exit

@@data:
        DB       -1, VK_TAB, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_PRIOR, VK_NEXT

@@1:
        OR       EDX, -1
        JMP      @@3
@@2:
        XOR      EDX, EDX
        TEST     AH, 1
        JZ       @@3

          PUSH     ECX
        PUSH     EAX
        PUSH     VK_SHIFT
        CALL     GetKeyState
        CWDE
        XCHG EDX, EAX
        POP      EAX
          POP      ECX
@@3:
        POP      ESI
        MOV      AL, AH
        {$IFDEF PARANOIA} DB $24, 1 {$ELSE} AND AL, 1 {$ENDIF}
        TEST     byte ptr [ESI].TControl.fLookTabKeys, AL
        JZ       @@exit0

        TEST     CL, CL
        JNZ      @@exit

        PUSH     EDX
        MOV      EAX, ESI
        CALL     TControl.ParentForm
        POP      EDX
        CALL     Tabulate2Next
@@exit:
        POP      ESI
end;

function Tabulate2ControlEx( Self_: PControl; Key: DWORD; checkOnly: Boolean ): Boolean;
asm
        PUSH     EDI
        MOVZX    EDI, CL
        TEST     byte ptr [EAX].TControl.fLookTabKeys, 1
        JZ       @@1
@@0:
        MOV      ECX, EDX
        AND      CL, 7Fh
        CMP      CL, VK_TAB
        JNE      @@1

        PUSH     EDX
        CALL     TControl.ParentForm
        POP      EDX
        MOVSX    EDX, DL
        TEST     EDX, EDX
        JS       @@tab

        PUSH     EAX

        PUSH     VK_SHIFT
        CALL     GetAsyncKeyState
        SAR      EAX, 31
        {$IFDEF PARANOIA} DB $0C, $01 {$ELSE} OR AL, 1 {$ENDIF}
        MOV      EDX, EAX

        POP      EAX
@@tab:
        TEST     EDI, EDI
        POP      EDI
        JNZ      @@no_tab
        CALL     Tabulate2Next
@@no_tab:
        MOV      AL, 1
        RET

@@data: DB VK_LEFT, VK_LEFT
        DD offset[@@left]
        DB VK_UP, 2
        DB VK_RIGHT, VK_RIGHT
        DD offset[@@right]
        DB VK_DOWN, 2
        DB VK_UP, VK_PRIOR
        DD offset[@@up]
        DB VK_TAB or 80h, $C
        DB VK_DOWN, VK_NEXT
        DD offset[@@down]
        DB VK_TAB, $C

@@1:
        // EAX <- Self_:PControl
        //  DL <- Key
        PUSH     ESI
        MOV      ESI, offset[@@data]-6
        MOV      DH, 9
        PUSH     EAX
@@loop:
        ADD      DH, DH
        JNB      @@l1
        JMP      @@abort
@@fault1:
        POP      EDI
        POPAD
        PUSH     EAX
@@abort:
        POP      EAX
@@abort1:
        POP      ESI
        POP      EDI
        XOR      EAX, EAX
        RET

@@right:
        MOV      EAX, [ESP].TRect.Left
        SUB      EAX, [ESP+16].TRect.Left
@@left_right:
        JL       @@next1
        MOV      EDX, [ESP].TRect.Bottom
        SUB      EDX, [ESP+16].TRect.Top
        JL       @@next1
        MOV      EDX, [ESP].TRect.Top
        SUB      EDX, [ESP+16].TRect.Bottom
        JGE      @@next1
@@chk_dist:
        CMP      EAX, EDI
        JA       @@next1
        MOV      EDI, EAX
        MOV      EAX, [EBX+ECX*4-4]
        MOV      [ESP+36], EAX     // Found = Ctrl
        JMP      @@next1

@@l1:
        LODSD
        LODSW
        LODSW
        CMP      AL, DL
        JE       @@2
        CMP      AH, DL
        JNE      @@loop

@@2:
        PUSH     ESI
        LODSD
        LODSW
        POP      ESI
        XCHG     EDX, EAX
        POP      EAX
        TEST     [EAX].TControl.fLookTabKeys, DH
        JZ       @@abort1

        PUSHAD
        PUSH     EDI
        CALL     TControl.ParentForm
        MOV      ECX, [EAX].TControl.fCurrentControl
        JECXZ    @@fault1
        MOV      EBP, ECX           // EBP = CurCtrl

        PUSH     EAX                // save Form
        MOV      EBX, EAX
        CALL     CollectTabControls
        PUSH     0                  // save Found = nil
        PUSH     EAX                // save CollectedList
        MOV      EDI, EAX

        MOV      EBX, [EDI].TList.fItems
        ADD      ESP, -16
        PUSH     ESP
        PUSH     [EBP].TControl.fHandle
        CALL     GetWindowRect

        MOV      ECX, [EDI].TList.fCount
        OR       EDI, -1            // EDI = minDist
@@loop1:
        MOV      EAX, [EBX+ECX*4-4]
        CMP      EAX, EBP
        JE       @@next
        {}
        MOV      DL, [EAX].TControl.fEnabled
        AND      DL, [EAX].TControl.fTabstop
        JZ       @@next
        {}
        ADD      ESP, -16
        MOV      EDX, ESP
        PUSH     ECX
        PUSH     EDX
        PUSH     [EAX].TControl.fHandle
        CALL     GetWindowRect
        POP      ECX
        JMP      dword ptr [ESI]

@@left:
        MOV      EAX, [ESP+16].TRect.Left
        SUB      EAX, [ESP].TRect.Left
        JMP      @@left_right

@@not_found:
        POP      EDI
        POPAD
        MOV      DL, [ESI+4]
        POP      ESI
        JMP      @@0

@@up:
        MOV      EAX, [ESP+16].TRect.Top
        SUB      EAX, [ESP].TRect.Top
        JMP      @@up_down
@@down:
        MOV      EAX, [ESP].TRect.Top
        SUB      EAX, [ESP+16].TRect.Top
@@up_down:
        JL       @@next1
        MOV      EDX, [ESP].TRect.Right
        SUB      EDX, [ESP+16].TRect.Left
        JL       @@next1
        MOV      EDX, [ESP].TRect.Left
        SUB      EDX, [ESP+16].TRect.Right
        JL       @@chk_dist

@@next1:
        ADD      ESP, 16
@@next:
        LOOP     @@loop1
        ADD      ESP, 16
        POP      EAX       // pop CollectedList
        CALL     TObj.RefDec
        POP      ECX       // pop Found
        POP      EAX       // pop Form
        JECXZ    @@not_found

        POP      EDI
        TEST     EDI, EDI
        JNZ      @@no_go

        MOV      [EAX].TControl.fCurrentControl, ECX
        INC      [ECX].TControl.fClickDisabled
        PUSH     ECX
        MOV      ECX, [ECX].TControl.fHandle
        JECXZ    @@4
        PUSH     ECX
        CALL     Windows.SetFocus
@@4:    POP      ECX
        DEC      [ECX].TControl.fClickDisabled
@@no_go:
        POPAD
        POP      ESI
        POP      EDI
        MOV      AL, 1      // Result = True
end;

function TControl.Tabulate: PControl;
asm
        PUSH     EAX
        CALL     ParentForm
        TEST     EAX, EAX
        JZ       @@exit
        MOV      [EAX].fGotoControl, offset[Tabulate2Control]
@@exit: POP      EAX
end;

function TControl.TabulateEx: PControl;
asm
        PUSH     EAX
        CALL     ParentForm
        TEST     EAX, EAX
        JZ       @@exit
        MOV      [EAX].fGotoControl, offset[Tabulate2ControlEx]
@@exit: POP      EAX
end;

function TControl.GetCurIndex: Integer;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].fCurIndex
        MOVZX    ECX, [EBX].fCommandActions.aGetCurrent
        JECXZ    @@exit
        XOR      EAX, EAX
        CDQ
        CMP      CX, LVM_GETNEXTITEM
        JNE      @@0
        INC      EAX
        INC      EAX
        JMP      @@1
@@0:
        CMP      CL, EM_LINEINDEX and $FF
        JNZ      @@2
@@1:
        DEC      EDX
@@2:
        PUSH     EAX
        PUSH     EDX
        PUSH     ECX
        PUSH     EBX
        CALL     Perform

@@exit: POP      EBX
end;

procedure TControl.SetCurIndex(const Value: Integer);
asm
        MOVZX    ECX, [EAX].fCommandActions.aSetCurrent
        JECXZ    @@set_item_sel
        PUSHAD
        PUSH     0
        PUSH     EDX
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        POPAD
        CMP      CX, TCM_SETCURSEL
        JNE      @@exit
        PUSH     TCN_SELCHANGE
        PUSH     EAX // idfrom doesn't matter
        PUSH     [EAX].fHandle
        PUSH     ESP
        PUSH     0
        PUSH     WM_NOTIFY
        PUSH     EAX
        CALL     Perform
        POP      ECX
        POP      ECX
        POP      ECX
@@exit:
        RET
@@set_item_sel:
        INC      ECX
        CALL     SetItemSelected
end;

function TControl.GetTextAlign: TTextAlign;
asm
        PUSH     EAX
        CALL     UpdateWndStyles
        MOV      ECX, [EAX].fStyle
        MOV      EDX, dword ptr [EAX].fCommandActions.aTextAlignRight
        XOR      EAX, EAX
        AND      DX, CX
        JNZ      @@ret_1
        SHR      EDX, 16
        AND      ECX, EDX
        JNZ      @@ret_2
        POP      EAX
        MOVZX    EAX, [EAX].fTextAlign
        RET

@@ret_2:INC      EAX
@@ret_1:INC      EAX
@@ret_0:POP      ECX
end;

procedure TControl.SetTextAlign(const Value: TTextAlign);
asm
        MOV      [EAX].fTextAlign, DL
        XOR      ECX, ECX
        MOV      CX, [EAX].fCommandActions.aTextAlignLeft
        OR       CX, [EAX].fCommandActions.aTextAlignCenter
        OR       CX, [EAX].fCommandActions.aTextAlignRight
        NOT      ECX
        AND      ECX, [EAX].fStyle

        AND      EDX, 3
        OR       CX, [EAX + EDX * 2].fCommandActions.aTextAlignLeft

        MOV      DL, [EAX].fCommandActions.aTextAlignMask
        NOT      EDX
        AND      EDX, ECX
        CALL     SetStyle
end;

function TControl.GetVerticalAlign: TVerticalAlign;
asm
        PUSH     EAX
        CALL     UpdateWndStyles
        MOV      EDX, dword ptr [EAX].fCommandActions.aVertAlignCenter
        MOV      ECX, [EAX].fStyle
        XOR      EAX, EAX
        MOV      DH, DL
        AND      DL, CH
        JZ       @@1
        CMP      DL, DH
        JE       @@ret_0
@@1:    SHR      EDX, 16
        MOV      DH, DL
        AND      DL, CH
        JZ       @@2
        CMP      DL, DH
        JE       @@ret_2
@@2:    POP      EAX
        MOVZX    EAX, [EAX].fVerticalAlign
        RET
@@ret_2:INC      EAX
@@ret_1:INC      EAX
@@ret_0:POP      ECX
end;

procedure TControl.SetVerticalAlign(const Value: TVerticalAlign);
asm
        PUSH     EBX
        MOVZX    EBX, DL
        MOV      [EAX].fVerticalAlign, BL

        MOV      ECX, dword ptr [EAX].fCommandActions.aVertAlignCenter
        OR       CH, CL
        SHR      ECX, 8
        OR       CL, CH
        NOT      ECX
        MOV      EDX, [EAX].fStyle
        AND      DH, CL

        OR       DH, [EAX+EBX].fCommandActions.aVertAlignCenter
        POP      EBX
        CALL     SetStyle
end;

function TControl.Dc2Canvas( Sender: PCanvas ): HDC;
asm
        MOV      ECX, [EAX].fPaintDC
        JECXZ    @@chk_fHandle

        PUSH     ECX
        XCHG     EAX, EDX // EAX <= Sender
        MOV      EDX, ECX // EDX <= fPaintDC
        PUSH     EAX
        CALL     TCanvas.SetHandle
        POP      EAX
        MOV      [EAX].TCanvas.fIsPaintDC, 1
        POP      ECX
@@ret_ECX:
        XCHG     EAX, ECX
        RET

@@chk_fHandle:
        MOV      ECX, [EDX].TCanvas.fHandle
        INC      ECX
        LOOP     @@ret_ECX

        CALL     GetWindowHandle
        PUSH     EAX
        CALL     GetDC
end;

function TControl.GetCanvas: PCanvas;
asm
        PUSH     EBX
        PUSH     ESI
        XCHG     EBX, EAX

        MOV      ESI, [EBX].fCanvas
        TEST     ESI, ESI
        JNZ      @@exit

        XOR      EAX, EAX
        CALL     NewCanvas
        MOV      [EBX].fCanvas, EAX
        MOV      [EAX].TCanvas.fOwnerControl, EBX
        MOV      [EAX].TCanvas.fOnGetHandle.TMethod.Code, offset[ DC2Canvas ]
        MOV      [EAX].TCanvas.fOnGetHandle.TMethod.Data, EBX
        XCHG     ESI, EAX

        MOV      ECX, [EBX].fFont
        JECXZ    @@exit

        MOV      EAX, [ESI].TCanvas.fFont
        MOV      EDX, ECX
        CALL     TGraphicTool.Assign
        MOV      [ESI].TCanvas.fFont, EAX

        MOV      ECX, [EBX].fBrush
        JECXZ    @@exit

        MOV      EAX, [ESI].TCanvas.fBrush
        MOV      EDX, ECX
        CALL     TGraphicTool.Assign
        MOV      [ESI].TCanvas.fBrush, EAX

@@exit: XCHG     EAX, ESI
        POP      ESI
        POP      EBX
end;

procedure TControl.SetTransparent(const Value: Boolean);
asm
        MOV      [EAX].fTransparent, DL
        MOV      ECX, [EAX].fParent
        JECXZ    @@exit
        TEST     DL, DL
        JZ       @@exit

{$IFDEF GRAPHCTL_XPSTYLES}
        CMP      AppTheming, FALSE
        JNE      @@not_th
        PUSH     EBX
        MOV      BL, [EAX].fTransparent
        MOV      [EAX].fClassicTransparent, BL;
        POP      EBX
@@not_th:
{$ENDIF}

        PUSH     EAX
        XCHG     EAX, ECX
        CALL     SetDoubleBuffered
        POP      EAX
        MOV      EDX, offset[WndProcTransparent]
        CALL     AttachProc
@@exit:
end;

function _NewTrayIcon: PTrayIcon;
begin
  New(Result,Create);
end;
function NewTrayIcon( Wnd: PControl; Icon: HIcon ): PTrayIcon;
asm
        PUSH     EBX
        PUSH     EDX // push Icon
        PUSH     EAX // push Wnd
        CALL     _NewTrayIcon
        XCHG     EBX, EAX

        MOV      EAX, [FTrayItems]
        TEST     EAX, EAX
        JNZ      @@1
        CALL     NewList
        MOV      [FTrayItems], EAX
@@1:
        MOV      EDX, EBX
        CALL     TList.Add

        POP      EAX //Wnd
        MOV      [EBX].TTrayIcon.fControl, EAX
        POP      [EBX].TTrayIcon.fIcon //Icon

        MOV      EDX, offset[WndProcTray]
        TEST     EAX, EAX
        JZ       @@2
        CALL     TControl.AttachProc
@@2:
        MOV      DL, 1
        MOV      EAX, EBX
        CALL     TTrayIcon.SetActive
        XCHG     EAX, EBX
        POP      EBX
end;

function WndProcRecreateTrayIcons( Sender: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //cmd    //opd
        MOV      ECX, [fRecreateMsg]
        CMP      word ptr [EDX].TMsg.message, CX
        JNE      @@ret_false
        PUSH     ESI
        MOV      ESI, [FTrayItems]
        MOV      ECX, [ESI].TList.fCount
        MOV      ESI, [ESI].TList.fItems
@@loo:  PUSH     ECX
        LODSD
        MOV      DL, [EAX].TTrayIcon.fAutoRecreate
        AND      DL, [EAX].TTrayIcon.fActive
        JZ       @@nx
        DEC      [EAX].TTrayIcon.fActive
        CALL     TTrayIcon.SetActive
@@nx:   POP      ECX
        LOOP     @@loo
@@e_loo:POP      ESI
@@ret_false:
        XOR      EAX, EAX
end;

procedure TTrayIcon.SetAutoRecreate(const Value: Boolean);
asm     //cmd    //opd
        MOV      [EAX].fAutoRecreate, DL
        MOV      EAX, [EAX].FControl
        CALL     TControl.ParentForm
        MOV      EDX, offset[WndProcRecreateTrayIcons]
        CALL     TControl.AttachProc
        PUSH     offset[TaskbarCreatedMsg]
        CALL     RegisterWindowMessage
        MOV      [fRecreateMsg], EAX
end;

destructor TTrayIcon.Destroy;
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX
        XOR      EDX, EDX
        CALL     SetActive

        MOV      ECX, [EBX].fIcon
        JECXZ    @@icon_destroyed
        PUSH     ECX
        CALL     DestroyIcon
@@icon_destroyed:

        MOV      EDX, EBX
        MOV      ESI, [FTrayItems]
        MOV      EAX, ESI
        CALL     TList.IndexOf
        TEST     EAX, EAX
        JL       @@fin
          XCHG     EDX, EAX
          MOV      EAX, ESI
          CALL     TList.Delete
          MOV      EAX, [ESI].TList.fCount
          TEST     EAX, EAX
          JNZ      @@fin
          XCHG     EAX, [FTrayItems]
          CALL     TObj.RefDec
@@fin:  LEA      EAX, [EBX].FTooltip
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        XCHG     EAX, EBX
        CALL     TObj.Destroy
        POP      ESI
        POP      EBX
end;

procedure TTrayIcon.SetActive(const Value: Boolean);
asm
        CMP      [EAX].fActive, DL
        JE       @@exit
        MOV      ECX, [EAX].fIcon
        JECXZ    @@exit
        PUSH     EDX
        PUSH     EAX
          MOV      ECX, [EAX].FWnd
          INC      ECX
          LOOP     @@1
          MOV      ECX, [EAX].fControl
          XOR      EAX, EAX
          JECXZ    @@1
          XCHG     EAX, ECX
          CALL     TControl.GetWindowHandle
@@1:
        POP      ECX
        POP      EDX
        XCHG     EAX, ECX
        JECXZ    @@exit
        MOV      [EAX].fActive, DL
        MOVZX    EDX, DL
        XOR      DL, 1
        ADD      EDX, EDX
        CALL     SetTrayIcon
@@exit:
end;

procedure TTrayIcon.SetIcon(const Value: HIcon);
asm
        MOV      ECX, [EAX].fIcon
        CMP      ECX, EDX
        JE       @@exit
        MOV      [EAX].fIcon, EDX
        XOR      EDX, EDX
        JECXZ    @@nim_add
        INC      EDX      // NIM_MODIFY = 1
@@nim_add:
        MOVZX    ECX, [EAX].fActive
        JECXZ    @@exit
        CALL     SetTrayIcon
@@exit:
end;

{$IFDEF ASM_UNICODE}
procedure TTrayIcon.SetTooltip(const Value: String);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].fTooltip
        PUSH     EDX
        CALL     System.@LStrCmp
        POP      EDX
        JE       @@exit
        LEA      EAX, [EBX].fTooltip
        CALL     System.@LStrAsg
        CMP      [EBX].fActive, 0
        JE       @@exit
        XOR      EDX, EDX
        INC      EDX     // EDX = NIM_MODIFY
        XCHG     EAX, EBX
        CALL     SetTrayIcon
@@exit:
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

{$IFDEF ASM_UNICODE}
procedure TTrayIcon.SetTrayIcon(const Value: DWORD);
const sz_tid = sizeof( TNotifyIconData );
asm
        CMP      [AppletTerminated], 0
        JE       @@1
        MOV      DL, NIM_DELETE
@@1:
        PUSH     EBX
        PUSH     ESI
        MOV      ESI, EAX
        MOV      EBX, EDX

        XOR      ECX, ECX
        PUSH     ECX
        ADD      ESP, -60
        MOV      EDX, [ESI].fToolTip
        CALL     EDX2PChar
        MOV      EAX, ESP
        MOV      CL, 63
        CALL     StrLCopy

        PUSH     [ESI].fIcon
        PUSH     CM_TRAYICON
        XOR      EDX, EDX
        CMP      BL, NIM_DELETE
        JE       @@2
        MOV      DL, NIF_ICON or NIF_MESSAGE or NIF_TIP
@@2:    PUSH     EDX
        PUSH     ESI
        MOV      EAX, [ESI].FWnd
        TEST     EAX, EAX
        JNZ      @@3
        MOV      EAX, [ESI].fControl
        MOV      EAX, [EAX].TControl.fHandle
@@3:
        PUSH     EAX
        PUSH     sz_tid

        PUSH     ESP
        PUSH     EBX
        CALL     Shell_NotifyIcon

        ADD      ESP, sz_tid
        POP      ESI
        POP      EBX
@@exit:
end;
{$ENDIF ASM_UNICODE}

function WndProcJustOne( Control: PControl; var Msg: TMsg; var Rslt: Integer ) : Boolean;
asm
        MOV      ECX, [EDX].TMsg.message
        SUB      ECX, WM_CLOSE
        JE       @@1
        SUB      ECX, WM_NCDESTROY - WM_CLOSE
        JNE      @@exit
@@1:
        MOV      ECX, [EDX].TMsg.hwnd
        SUB      ECX, [EAX].TControl.fHandle
        JNE      @@exit

        XCHG     ECX, [JustOneMutex]
        JECXZ    @@exit

        PUSH     ECX
        CALL     CloseHandle

@@exit:
        XOR      EAX, EAX
end;

function WndProcJustOneNotify( Control: PControl; var Msg: TMsg; var Rslt: Integer ) : Boolean;
asm
        PUSH     EBP
        MOV      EBP, ESP
        PUSHAD
        CALL     WndProcJustOne
        POPAD
        XOR      EAX, EAX
        PUSH     ECX
          MOV      ECX, [EDX].TMsg.message
          SUB      ECX, [JustOneMsg]
        POP      ECX
        JNE      @@exit
        MOV      [ECX], EAX
        CMP      [OnAnotherInstance].TMethod.Code, EAX
        JE       @@exit_1

        //MOV      EAX, (MAX_PATH + 3) and 0FFFFCh
        MOV      AH, 2
        SUB      ESP, EAX

        MOV      ECX, ESP
        PUSH     EAX
        PUSH     ECX
        PUSH     [EDX].TMsg.lParam
        CALL     GetWindowText

        MOV      EDX, ESP
        PUSH     0
        MOV      EAX, ESP
        CALL     System.@LStrFromPChar

        MOV      EDX, [ESP]
        MOV      EAX, [OnAnotherInstance].TMethod.Data
        CALL     [OnAnotherInstance].TMethod.Code

        MOV      EAX, ESP
        CALL     System.@LStrClr
@@exit_1:
        MOV      AL, 1
@@exit:
        MOV      ESP, EBP
        POP      EBP
end;

{$IFDEF ASM_UNICODE}
function JustOneNotify( Wnd: PControl; const Identifier : String;
                        const aOnAnotherInstance: TOnAnotherInstance ) : Boolean;
asm
        PUSHAD
        MOV      EBP, ESP

        XCHG     EAX, EDX
        PUSH     EAX
        CALL     System.@LStrLen
        POP      EDX
        ADD      EAX, EAX
        SUB      ESP, EAX
        MOV      EAX, ESP
        CALL     StrPCopy
        PUSH     '.ega'
        PUSH     'sseM'
        PUSH     ESP
        CALL     RegisterWindowMessage
        MOV      [JustOneMsg], EAX
        TEST     EAX, EAX

        MOV      ESP, EBP
        POPAD
        JE       @@exit_f

        PUSHAD
        CALL     JustOne
        DEC      AL
        POPAD
        JZ       @@exit_t

        PUSH     EBX
        XCHG     EBX, EAX
        XOR      EDX, EDX
        XCHG     [EBX].TControl.fCaption, EDX
        PUSH     EDX

        CALL     GetCommandLine
        XCHG     EDX, EAX
        LEA      EAX, [EBX].TControl.fCaption
        CALL     System.@LStrFromPChar
        MOV      EAX, EBX
        MOV      EDX, [EBX].TControl.fCaption
        CALL     TControl.SetCaption
        MOV      EAX, EBX
        CALL     TControl.GetWindowHandle
        TEST     EAX, EAX
        JZ       @@rest_cap

        PUSH     BSM_APPLICATIONS
        MOV      EDX, ESP

        PUSH     EAX
        PUSH     0
        PUSH     [JustOneMsg]
        PUSH     EDX
        PUSH     BSF_QUERY or BSF_IGNORECURRENTTASK
        CALL     BroadcastSystemMessage

        POP      EDX
@@rest_cap:
        LEA      EAX, [EBX].TControl.fCaption
        CALL     System.@LStrClr
        POP      EDX
        MOV      [EBX].TControl.fCaption, EDX
        MOV      EAX, EBX
        CALL     TControl.SetCaption
        POP      EBX
@@exit_f:
        XOR      EAX, EAX
        JMP      @@exit

@@exit_t:
        PUSHAD
        LEA      ESI, [aOnAnotherInstance]
        LEA      EDI, [OnAnotherInstance]
        MOVSD
        MOVSD
        MOV      EDX, offset[WndProcJustOneNotify]
        CALL     TControl.AttachProc
        POPAD

        MOV      AL, 1
@@exit:
end;
{$ENDIF ASM_UNICODE}

destructor TStrList.Destroy;
asm
        PUSH     EAX
        CALL     Clear
        POP      EAX
        CALL     TObj.Destroy
end;

function TStrList.Add(const S: string): integer;
asm
        MOV      ECX, EDX
        MOV      EDX, [EAX].fCount
        PUSH     EDX
        CALL     Insert
        POP      EAX
end;

procedure TStrList.AddStrings(Strings: PStrList);
asm
        PUSH     EAX
        XCHG     EAX, EDX
        PUSH     0
        MOV      EDX, ESP
        CALL     GetTextStr
        POP      EDX
        POP      EAX
        MOV      CL, 1
        PUSH     EDX
        CALL     SetText
        CALL     RemoveStr
end;

procedure TStrList.Assign(Strings: PStrList);
asm
        PUSHAD
        CALL     Clear
        POPAD
        JMP      AddStrings
end;

procedure TStrList.Clear;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EDX, [EBX].fCount
@@loo:  DEC      EDX
        JL       @@eloo
        PUSH     EDX
        MOV      EAX, EBX
        CALL     Delete
        POP      EDX
        JMP      @@loo
@@eloo:
        XOR      EAX, EAX
        MOV      [EBX].fTextSiz, EAX
        XCHG     EAX, [EBX].fTextBuf
        TEST     EAX, EAX
        JZ       @@1
        CALL     System.@FreeMem
        {$IFNDEF _D2orD3} //???//
        XOR      EAX, EAX // not needed for Delphi4 and Higher: if OK, EAX = 0
        {$ENDIF}
@@1:    XCHG     EAX, [EBX].fList
        CALL     TObj.RefDec
        POP      EBX
end;

procedure TStrList.Delete(Idx: integer);
asm
        DEC      [EAX].fCount
        PUSH     EAX
        MOV      EAX, [EAX].fList
        MOV      ECX, [EAX].TList.fItems
        PUSH     dword ptr [ECX+EDX*4]
        CALL     TList.Delete
        POP      EAX
        POP      EDX
        MOV      ECX, [EDX].fTextSiz
        JECXZ    @@fremem
        CMP      EAX, [EDX].fTextBuf
        JB       @@fremem
        ADD      ECX, [EDX].fTextBuf
        CMP      EAX, ECX
        JB       @@exit
@@fremem:
        CALL     System.@FreeMem
@@exit:
end;

function TStrList.Get(Idx: integer): string;
asm
        PUSH     ECX
        MOV      EAX, [EAX].fList
        TEST     EAX, EAX
        JZ       @@1
        CALL     TList.Get
@@1:    XCHG     EDX, EAX
        POP      EAX
        JMP      System.@LStrFromPChar
end;

function TStrList.GetPChars(Idx: Integer): PChar;
asm
        MOV      EAX, [EAX].fList
        MOV      EAX, [EAX].TList.fItems
        MOV      EAX, [EAX+EDX*4]
end;

function TStrList.GetTextStr: string;
asm
        PUSH     ESI
        PUSH     EDI
        MOV      ECX, [EAX].fCount
        MOV      EAX, [EAX].fList
        PUSH     ECX
        JECXZ    @@1
        MOV      ESI, [EAX].TList.fItems
@@1:    PUSH     ESI
        XCHG     EAX, EDX
        XOR      EDX, EDX
        JECXZ    @@10
        PUSH     EAX
@@loo1:
        PUSH     ECX
        PUSH     EDX
        LODSD
        CALL     StrLen
        POP      EDX
        LEA      EDX, [EDX+EAX+2]
        POP      ECX
        LOOP     @@loo1

        POP      EAX
        POP      ESI
        XCHG     ECX, EDX
        PUSH     EAX
@@10:
        {$IFDEF _D2}
        CALL     _LStrFromPCharLen
        {$ELSE}
        CALL     System.@LStrFromPCharLen
        {$ENDIF}

        POP      EDI
        POP      ECX
        JECXZ    @@exit
        MOV      EDI, [EDI]

@@loo2: PUSH     ECX
        LODSD
        PUSH     EAX
        CALL     StrLen
        XCHG     ECX, EAX
        POP      EAX
        XCHG     EAX, ESI
        REP      MOVSB
        XCHG     ESI, EAX
        MOV      AX, $0A0D
        STOSW
        POP      ECX
        LOOP     @@loo2

        XCHG     EAX, ECX
        STOSB
@@exit:
        POP      EDI
        POP      ESI
end;

function TStrList.IndexOf(const S: string): integer;
asm
        PUSH     EBX
        PUSH     ESI
        OR       EBX, -1
        MOV      ECX, [EAX].fCount
        JECXZ    @@exit
        MOV      ESI, [EAX].fList
        MOV      ESI, [ESI].TList.fItems
        CALL     EDX2PChar
@@loo:  LODSD
        INC      EBX
        PUSH     EDX
        PUSH     ECX
        CALL     StrComp
        POP      ECX
        POP      EDX
        JE       @@exit
@@1:    LOOP     @@loo
        OR       EBX, -1
@@exit: XCHG     EAX, EBX
        POP      ESI
        POP      EBX
end;

procedure TStrList.Insert(Idx: integer; const S: string);
asm
        PUSH     EBX
        PUSH     EDX
        PUSH     ECX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].fList
        TEST     EAX, EAX
        JNZ      @@1
        CALL     NewList
        MOV      [EBX].fList, EAX
@@1:
        POP      EAX
        PUSH     EAX          // push S
        CALL     System.@LStrLen
        INC      EAX
        PUSH     EAX          // push L
        CALL     System.@GetMem
        MOV      byte ptr[EAX], 0
        XCHG     EDX, EAX
        POP      ECX
        POP      EAX
        PUSH     EDX          // push Mem
        TEST     EAX, EAX
        JE       @@2
        CALL     System.Move
@@2:    POP      ECX
        POP      EDX
        MOV      EAX, [EBX].fList
        CALL     TList.Insert
        INC      [EBX].fCount
        POP      EBX
end;

procedure TStrList.Put(Idx: integer; const Value: string);
asm
        PUSH     EAX
        PUSH     EDX
        CALL     Insert
        POP      EDX
        POP      EAX
        INC      EDX
        JMP      Delete
end;

procedure TStrList.SetText(const S: string; Append2List: boolean);
asm
        DEC      CL
        JZ       @@1
        PUSHAD
        CALL     Clear
        POPAD
@@1:    CALL     EDX2PChar
        JZ       @@exit

        PUSH     EBX
        PUSH     EDI
        MOV      EBX, EAX
        MOV      EDI, [EBX].fTextSiz

        MOV      EAX, [EDX-4] // EAX = Length(S)
        INC      EAX
        PUSH     EAX

        // add S to text buffer

        PUSH     EDX
        PUSH     [EBX].fTextBuf
        ADD      EAX, [EBX].fTextSiz
        CALL     System.@GetMem
        MOV      [EBX].fTextBuf, EAX

        MOV      ECX, EDI
        XCHG     EDX, EAX
        POP      EAX
        JECXZ    @@atb_fin
        PUSH     EAX
        CALL     System.Move

        POP      EDX
        PUSH     EDX

        PUSH     ESI
        MOV      ESI, [EBX].fList
        MOV      ESI, [ESI].TList.fItems
        MOV      ECX, [EBX].fCount

@@atb_loo:
        LODSD
        SUB      EAX, EDX
        CMP      EAX, [EBX].fTextSiz
        JAE      @@atb_nxt

        ADD      EAX, [EBX].fTextBuf
        MOV      [ESI-4], EAX

@@atb_nxt: LOOP  @@atb_loo

        POP      ESI
        POP      EAX
        CALL     System.@FreeMem
@@atb_fin:
        POP      EAX

        MOV      EDX, EDI
        ADD      EDX, [EBX].fTextBuf
        POP      ECX
        PUSH     ECX
        ADD      [EBX].fTextSiz, ECX

        CALL     System.Move

@@eatb:
        ADD      EDI, [EBX].fTextBuf // EDI ~ P

        MOV      ECX, [EBX].fList
        INC      ECX
        LOOP     @@2
        CALL     NewList
        MOV      [EBX].fList, EAX
@@2:
        POP      ECX
        MOV      EDX, [EBX].fCount

        PUSH     EDI
        PUSH     ECX
        MOV      AL, $0D

@@loo1: CMP      byte ptr [EDI], 0
        JZ       @@eloo1

        INC      EDX
        REPNZ    SCASB
        JNZ      @@eloo1

        CMP      byte ptr [EDI], $0A
        JNZ      @@loo1
        INC      EDI
        LOOP     @@loo1

@@eloo1:
        MOV      [EBX].fCount, EDX
        MOV      EAX, [EBX].fList
        PUSH     EDX
        PUSH     EAX
        CMP      EDX, [EAX].TList.fCapacity
        JLE      @@3
        CALL     TList.SetCapacity
@@3:    POP      EAX
        POP      ECX

        XCHG     ECX, [EAX].TList.fCount
        MOV      EDX, [EAX].TList.fItems
        LEA      EDX, [EDX+ECX*4]

        POP      ECX
        POP      EDI

        MOV      EAX, $0D
@@loo2: CMP      byte ptr [EDI], AH
        JZ       @@eloo2

        MOV      [EDX], EDI
        ADD      EDX, 4

        REPNZ    SCASB
        JNZ      @@eloo2

        MOV      [EDI-1], AH

        CMP      byte ptr [EDI], $0A
        JNZ      @@loo2
        INC      EDI
        LOOP     @@loo2
@@eloo2:

        POP      EDI
        POP      EBX
@@exit:
end;

procedure LowerCaseStrFromPCharEDX;
asm
          { <- EDX = PChar string
            -> [ESP] = LowerCase( PChar( EDX ) ),
               EAX, EDX, ECX - ?
          }
        POP      EAX
        PUSH     0
        PUSH     EAX
        LEA      EAX, [ESP+4]
        PUSH     EAX
        CALL     System.@LStrFromPChar
        POP      EDX
        MOV      EAX, [EDX]
        JMP      LowerCase
end;
function CompareStrListItems( const Sender : Pointer; const e1, e2 : DWORD ) : Integer;
asm
        CMP      [EAX].TStrList.fCaseSensitiveSort, 0
        MOV      EAX, [EAX].TStrList.fList
        MOV      EAX, [EAX].TList.fItems
        MOV      EDX, [EAX+EDX*4]
        MOV      EAX, [EAX+ECX*4]
        XCHG     EAX, EDX
        JNZ      StrComp
        PUSH     EBX

        XCHG     EBX, EAX
        CALL     LowerCaseStrFromPCharEDX

        MOV      EDX, EBX
        CALL     LowerCaseStrFromPCharEDX

        POP      EAX
        POP      EDX
        PUSH     EDX
        PUSH     EAX
        CALL     EAX2PChar
        CALL     EDX2PChar
        CALL     StrComp
        XCHG     EBX, EAX

        CALL     RemoveStr
        CALL     RemoveStr

        XCHG     EAX, EBX
        POP      EBX
end;

function CompareAnsiStrListItems( const Sender : Pointer; const e1, e2 : DWORD ) : Integer;
asm
        CMP      byte ptr [EAX].TStrList.fCaseSensitiveSort, 0
        MOV      EAX, [EAX].TStrList.fList
        MOV      EAX, [EAX].TList.fItems
        MOV      EDX, [EAX+EDX*4]
        MOV      EAX, [EAX+ECX*4]
        XCHG     EAX, EDX
        JZ       _AnsiCompareStrNoCase
        JMP      _AnsiCompareStr
end;

procedure TStrList.Sort(CaseSensitive: Boolean);
asm
        MOV      [EAX].fCaseSensitiveSort, DL
        PUSH     Offset[TStrList.Swap]
        MOV      ECX, Offset[CompareStrListItems]
        MOV      EDX, [EAX].fCount
        CALL     SortData
end;

procedure TStrList.AnsiSort(CaseSensitive: Boolean);
asm
        MOV      [EAX].fCaseSensitiveSort, DL
        PUSH     Offset[TStrList.Swap]
        MOV      ECX, Offset[CompareAnsiStrListItems]
        MOV      EDX, [EAX].fCount
        CALL     SortData
end;

{$IFDEF ASM_UNICODE}
function TStrList.AppendToFile(const FileName: string): Boolean;
asm
        PUSH     EBX
        MOV      EBX, EDX
        PUSH     0
        MOV      EDX, ESP
        CALL     GetTextStr
        XCHG     EAX, EBX
        MOV      EDX, ofOpenWrite or ofOpenAlways
        CALL     FileCreate
        MOV      EBX, EAX
        INC      EAX
        JZ       @@exit
        DEC      EAX
        XOR      EDX, EDX
        XOR      ECX, ECX
        MOV      CL, spEnd
        CALL     FileSeek
        POP      EAX
        PUSH     EAX
        CALL     System.@LStrLen
        XCHG     ECX, EAX
        MOV      EAX, EBX
        POP      EDX
        PUSH     EDX
        CALL     FileWrite
        XCHG     EAX, EBX
        CALL     FileClose
@@exit:
        CALL     RemoveStr
        POP      EBX
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
function TStrList.LoadFromFile(const FileName: string): Boolean;
asm
      PUSH     EAX
        XCHG     EAX, EDX
        MOV      EDX, ofOpenRead or ofShareDenyWrite or ofOpenExisting
        CALL     FileCreate
        INC      EAX
        JZ       @@exit
        DEC      EAX
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     0
        PUSH     EBX
        CALL     GetFileSize
        XOR      EDX, EDX
        PUSH     EDX
        XCHG     ECX, EAX
        MOV      EAX, ESP
        PUSH     ECX
        {$IFDEF _D2}
        CALL     _LStrFromPCharLen
        {$ELSE}
        CALL     System.@LStrFromPCharLen
        {$ENDIF}
        POP      ECX
        MOV      EAX, EBX
        POP      EDX
        PUSH     EDX
        CALL     FileRead
        XCHG     EAX, EBX
        CALL     FileClose
        POP      EDX
        POP      EBX
      POP      EAX
        PUSH     EDX
        XOR      ECX, ECX
        CALL     SetText
        CALL     RemoveStr
        PUSH     EDX
        MOV      AL, 1
@@exit: POP      EDX
end;
{$ENDIF}

procedure TStrList.LoadFromStream(Stream: PStream; Append2List: boolean);
asm
        PUSH     EAX
        PUSH     ECX
        PUSH     EBX
        XCHG     EAX, EDX
        MOV      EBX, EAX
        CALL     TStream.GetSize
        PUSH     EAX
        MOV      EAX, EBX
        CALL     TStream.GetPosition
        POP      ECX
        SUB      ECX, EAX
        XOR      EDX, EDX
        PUSH     EDX
        MOV      EAX, ESP
        PUSH     ECX
        {$IFDEF _D2}
        CALL     _LStrFromPCharLen
        {$ELSE}
        CALL     System.@LStrFromPCharLen
        {$ENDIF}
        POP      ECX
        POP      EDX
        XCHG     EAX, EBX
        PUSH     EDX
        CALL     TStream.Read
        POP      EDX
        POP      EBX
        POP      ECX
        POP      EAX
        PUSH     EDX
        CALL     SetText
        CALL     RemoveStr
end;

procedure TStrList.MergeFromFile(const FileName: KOLString);
asm
        PUSH     EAX
        XCHG     EAX, EDX
        CALL     NewReadFileStream
        XCHG     EDX, EAX
        POP      EAX
        MOV      CL, 1
        PUSH     EDX
        CALL     LoadFromStream
        POP      EAX
        JMP      TObj.RefDec
end;

{$IFDEF ASM_UNICODE}
function TStrList.SaveToFile(const FileName: string): Boolean;
asm
        PUSH     EBX
        PUSH     EAX
        XCHG     EAX, EDX
        MOV      EDX, ofOpenWrite or ofCreateAlways
        CALL     FileCreate
        INC      EAX
        JZ       @@exit
        DEC      EAX
        XCHG     EBX, EAX
        POP      EAX
        PUSH     0
        MOV      EDX, ESP
        CALL     GetTextStr
        POP      EAX
        PUSH     EAX
        CALL     System.@LStrLen
        XCHG     ECX, EAX
        POP      EDX
        PUSH     EDX
        MOV      EAX, EBX
        CALL     FileWrite
        PUSH     EBX
        CALL     SetEndOfFile
        XCHG     EAX, EBX
        CALL     FileClose
        CALL     RemoveStr
        PUSH     EDX
        INC      EAX
@@exit:
        POP      EDX
        POP      EBX
end;
{$ENDIF}

procedure TStrList.SaveToStream(Stream: PStream);
asm
        PUSH     EDX
        PUSH     0
        MOV      EDX, ESP
        CALL     GetTextStr
        POP      EAX
        PUSH     EAX
        CALL     System.@LStrLen
        XCHG     ECX, EAX
        POP      EDX
        POP      EAX
        PUSH     EDX
        JECXZ    @@1
        CALL     TStream.Write
@@1:
        CALL     RemoveStr
end;

function CompareIntegers( const Sender : Pointer; const e1, e2 : DWORD ) : Integer;
asm
        MOV      EDX, [EAX+EDX*4]
        SUB      EDX, [EAX+ECX*4]
        XCHG     EAX, EDX
end;

function CompareDwords( const Sender : Pointer; const e1, e2 : DWORD ) : Integer;
asm
        MOV      EDX, [EAX+EDX*4]
        SUB      EDX, [EAX+ECX*4]
        XCHG     EAX, EDX
        JNB      @@1
        SBB      EAX, EAX
@@1:
end;

procedure SwapIntegers( const Sender : Pointer; const e1, e2 : DWORD );
asm
        LEA      EDX, [EAX+EDX*4]
        LEA      ECX, [EAX+ECX*4]
        MOV      EAX, [EDX]
        XCHG     EAX, [ECX]
        MOV      [EDX], EAX
end;

function _NewStatusbar( AParent: PControl ): PControl;
const STAT_CLS_NAM: PKOLChar = STATUSCLASSNAME;
asm
        PUSH     0
        PUSH     0
        CMP      [EAX].TControl.fSizeGrip, 0
        MOV      ECX, WS_CHILD or WS_CLIPSIBLINGS or WS_CLIPCHILDREN or 3 or WS_VISIBLE
        JZ       @@1
        INC      CH
        AND      CL, not 3
@@1:
        MOV      EDX, [STAT_CLS_NAM]
        CALL     _NewCommonControl
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     EDI
        LEA      EDI, [EBX].TControl.fBoundsRect
        XOR      EAX, EAX
        STOSD
        STOSD
        STOSD
        STOSD
        MOV      [EBX].TControl.fAlign, caBottom
        INC      [EBX].TControl.fNotUseAlign
        POP      EDI
        MOV      EAX, EBX
        CALL     InitCommonControlSizeNotify
        XCHG     EAX, EBX
        POP      EBX
end;

procedure TControl.SetStatusText(Index: Integer; Value: PKOLChar);
asm
        PUSHAD
        MOV      EBX, EDX // EBX = Index
        MOV      ESI, EAX // ESI = @Self

        PUSH     Value // prepare value for call at the end of procedure
        PUSH     EBX   // prepare Index for call at the end of procedure

        MOV      ECX, [ESI].fStatusCtl
        INC      ECX
        LOOP     @@status_created

        CALL     GetClientHeight
        PUSH     EAX // ch = old client height

        MOV      EAX, ESI
        CALL     _NewStatusBar
        MOV      [ESI].fStatusCtl, EAX
        PUSH     EAX //-----------v

        CALL     TControl.GetWindowHandle
        MOV      [ESI].fStatusWnd, EAX
        XCHG     EDI, EAX
        POP      EAX //-----------^

        XOR      EDX, EDX
        PUSH     EDX
        INC      DH
        DEC      EDX
        CMP      EBX, EDX
        SETZ     DL
        NEG      EDX

@@1:    PUSH     EDX
        PUSH     SB_SIMPLE

        PUSH     EAX
        CALL     TControl.Perform

        ADD      ESP, -16
        PUSH     ESP
        PUSH     [ESI].fStatusWnd
        CALL     GetWindowRect
        POP      EAX
        POP      EDX
        POP      EAX
        POP      EAX
        SUB      EAX, EDX
        MOV      [ESI].fClientBottom, EAX

        POP      EDX // ch

        PUSH     0
        PUSH     0
        PUSH     WM_SIZE
        PUSH     EDI

        MOV      EAX, ESI
        CALL     TControl.SetClientHeight

        CALL     SendMessage

@@status_created:
        CMP      EBX, 255
        JGE      @@not_simple

        PUSH     0
        PUSH     0
        PUSH     SB_GETPARTS
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage

        CMP      EAX, EBX
        JG       @@reset_simple

        MOV      EAX, ESI
        CALL     GetWidth
        CDQ
        MOV      ECX, EBX
        INC      ECX
        IDIV     ECX
        MOV      EDX, EAX

        ADD      ESP, -1024
        MOV      ECX, EBX
        MOV      EDI, ESP
        JECXZ    @@2

@@store_loo:
        STOSD
        ADD      EAX, EDX
        LOOP     @@store_loo
@@2:
        OR       dword ptr [ESP+EBX*4], -1
        PUSH     ESP
        INC      EBX
        PUSH     EBX
        PUSH     SB_SETPARTS
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage
        ADD      ESP, 1024

@@reset_simple:
        PUSH     0
        PUSH     0
        PUSH     SB_SIMPLE
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage

@@not_simple:
        PUSH     SB_SETTEXT
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage
        POPAD
end;

function TControl.GetStatusText( Index: Integer ): PKOLChar;
asm
        MOV      ECX, [EAX].fStatusWnd
        JECXZ    @@exit

        PUSH     EBX
        PUSH     ESI
        XCHG     ESI, EAX // ESI = @Self
        MOV      EBX, EDX // EBX = Index

        XOR      EAX, EAX
        XCHG     EAX, [ESI].fStatusTxt
        TEST     EAX, EAX
        JZ       @@1
        CALL     System.@FreeMem
@@1:
        XOR      EAX, EAX
        CDQ
        MOV      DL, WM_GETTEXTLENGTH
          PUSH     WM_GETTEXT
        CMP      EBX, 255
        JZ       @@2
          POP      EAX
        MOV      EAX, EBX
        MOV      DX, SB_GETTEXTLENGTH
          PUSH     SB_GETTEXT
@@2:
        MOV      EBX, EAX

        PUSH     0
        PUSH     EAX
        PUSH     EDX
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage
        TEST     AX, AX
        JZ       @@get_rslt

        PUSH     EAX
        INC      EAX
        CALL     System.@GetMem
        POP      EDX
        MOV      [ESI].fStatusTxt, EAX
        MOV      byte ptr [EAX+EDX], 0

        POP      EDX // Msg
        PUSH     EAX
        PUSH     EBX
        PUSH     EDX
        PUSH     [ESI].fStatusWnd
        CALL     SendMessage
          PUSH     EDX
@@get_rslt:
          POP      EDX
        MOV      ECX, [ESI].fStatusTxt
        POP      ESI
        POP      EBX

@@exit: XCHG     EAX, ECX
end;

procedure TControl.RemoveStatus;
asm
        MOV      ECX, [EAX].fStatusCtl
        JECXZ    @@exit
        PUSH     EBX
        MOV      EBX, EAX
        CALL     GetClientHeight
        PUSH     EAX
        CDQ
        MOV      [EBX].fStatusWnd, EDX
        XCHG     EAX, EDX
        XCHG     [EBX].fStatusCtl, EAX
        CALL     TObj.RefDec
        POP      EAX
        CDQ
        MOV      [EBX].fClientBottom, EDX
        XCHG     EDX, EAX
        XCHG     EAX, EBX
        POP      EBX
        CALL     SetClientHeight
@@exit:
end;

function TControl.StatusPanelCount: Integer;
asm
        MOV      EAX, [EAX].fStatusWnd
        TEST     EAX, EAX
        JZ       @@exit
        PUSH     0
        PUSH     0
        PUSH     SB_GETPARTS
        PUSH     EAX
        CALL     SendMessage
@@exit:
end;

function TControl.GetStatusPanelX(Idx: Integer): Integer;
asm
        MOV      ECX, [EAX].fStatusWnd
        JECXZ    @@exit
        PUSH     EBX
        MOV      EBX, EDX
        ADD      ESP, -1024
        PUSH     ESP
        XOR      EDX, EDX
        DEC      DL
        PUSH     EDX
        MOV      DX, SB_GETPARTS
        PUSH     EDX
        PUSH     ECX
        CALL     SendMessage
        CMP      EAX, EBX
        MOV      ECX, [ESP+EBX*4]
        JG       @@1
        XOR      ECX, ECX
@@1:    ADD      ESP, 1024
        POP      EBX
@@exit:
        XCHG     EAX, ECX
end;

procedure TControl.SetStatusPanelX(Idx: Integer; const Value: Integer);
asm
        ADD      ESP, -1024
        MOV      EAX, [EAX].fStatusWnd
        TEST     EAX, EAX
        JZ       @@exit

        PUSH     ESP
        PUSH     EDX
        PUSH     SB_SETPARTS
        PUSH     EAX

        PUSH     EDX
        PUSH     ECX

        LEA      EDX, [ESP+24]
        PUSH     EDX
        PUSH     255
        PUSH     SB_GETPARTS
        PUSH     EAX
        CALL     SendMessage

        POP      ECX
        POP      EDX
        CMP      EAX, EDX
        JG       @@1
        ADD      ESP, 16
        JMP      @@exit

@@1:    MOV      [ESP+8], EAX
        MOV      [ESP+16+EDX*4], ECX
        CALL     SendMessage

@@exit: ADD      ESP, 1024
end;

destructor TImageList.Destroy;
asm
        PUSH     EAX
        XOR      EDX, EDX
        CALL     SetHandle
        POP      EAX
        MOV      EDX, [EAX].fNext
        MOV      ECX, [EAX].fPrev
        TEST     EDX, EDX
        JZ       @@nonext
        MOV      [EDX].fPrev, ECX
@@nonext:
        JECXZ    @@noprev
        MOV      [ECX].fNext, EDX
@@noprev:
        MOV      ECX, [EAX].fControl
        JECXZ    @@fin
        CMP      [ECX].TControl.fImageList, EAX
        JNZ      @@fin
        MOV      [ECX].TControl.fImageList, EDX
        {$IFDEF USE_AUTOFREE4CONTROLS}
        PUSH     EAX
        XCHG     EAX, ECX
        MOV      EDX, ECX
        CALL     TControl.RemoveFromAutoFree
        POP      EAX
        {$ENDIF}
@@fin:  CALL     TObj.Destroy
end;

function TImageList.GetHandle: THandle;
asm
        PUSH     EAX
        CALL     HandleNeeded
        POP      EAX
        MOV      EAX, [EAX].FHandle
end;

procedure TImageList.SetHandle(const Value: THandle);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      ECX, [EBX].FHandle
        CMP      ECX, EDX
        JZ       @@exit
        JECXZ    @@set_handle
        CMP      [EBX].fShareImages, 0
        JNZ      @@set_handle
        PUSH     EDX
        PUSH     ECX
        CALL     ImageList_Destroy
        POP      EDX

@@set_handle:
        MOV      [EBX].FHandle, EDX
        TEST     EDX, EDX
        JZ       @@set_sz0
        LEA      EAX, [EBX].FImgHeight
        PUSH     EAX
        LEA      EAX, [EBX].FImgWidth
        PUSH     EAX
        PUSH     EDX
        CALL     ImageList_GetIconSize
        JMP      @@exit

@@set_sz0:
        MOV      [EBX].fImgWidth, EDX
        MOV      [EBX].fImgHeight, EDX

@@exit:
        POP      EBX
end;

function TControl.Perform(msgcode: DWORD; wParam, lParam: Integer): Integer; stdcall;
asm
        PUSH     [lParam]
        PUSH     [wParam]
        PUSH     [msgcode]
        MOV      EAX, [EBP+8]
        CALL     TControl.GetWindowHandle
        PUSH     EAX
        {$IFDEF UNICODE_CTRLS}
        CALL     Windows.SendMessageW
        {$ELSE}
        CALL     Windows.SendMessage
        {$ENDIF}
end;

function TControl.Postmsg(msgcode: DWORD; wParam, lParam: Integer): Boolean; stdcall;
asm
        PUSH     [lParam]
        PUSH     [wParam]
        PUSH     [msgcode]
        MOV      EAX, [EBP+8]
        CALL     TControl.GetWindowHandle
        PUSH     EAX
        CALL     Windows.PostMessage
end;

function TControl.GetChildCount: Integer;
asm
        MOV      EAX, [EAX].fChildren
        MOV      EAX, [EAX].TList.fCount
end;

procedure TControl.SetItemVal(Item: Integer; const Index: Integer; const Value: Integer);
asm
        PUSH     EAX
        PUSH     [Value]
        PUSH     EDX
        MOV      EDX, ECX
        SHR      EDX, 16
        JNZ      @@1
        MOV      EDX, ECX
        INC      EDX
@@1:
        MOV      EBP, EDX
        AND      EDX, 7FFFh
        PUSH     EDX
        PUSH     EAX
        CALL     Perform
        MOV      EAX, EBP
        ADD      AX, AX
        POP      EAX
        JNB      @@2
        CALL     Invalidate
@@2:
end;

destructor TOpenSaveDialog.Destroy;
asm     //cmd    //opd
        PUSH     EAX
        PUSH     0
        LEA      EDX, [EAX].FFilter
        PUSH     EDX
        LEA      EDX, [EAX].FInitialDir
        PUSH     EDX
        LEA      EDX, [EAX].FDefExtension
        PUSH     EDX
        LEA      EDX, [EAX].FFileName
        PUSH     EDX
        LEA      EAX, [EAX].FTitle
@@loo:
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        POP      EAX
        TEST     EAX, EAX
        JNZ      @@loo
        POP      EAX
        CALL     TObj.Destroy
end;

{$IFDEF ASM_UNICODE}
function TOpenSaveDialog.Execute: Boolean;
asm
        PUSH     EBX
        XCHG     EBX, EAX

        XOR      ECX, ECX
        {$IFDEF OpenSaveDialog_Extended}
        MOVZX    EAX, [EBX].NoPlaceBar
        PUSH     EAX
        PUSH     ECX
        PUSH     ECX
        PUSH     [EBX].TemplateName
        PUSH     [EBX].HookProc
        {$ELSE}
        PUSH     ECX                      // prepare lpTemplateName = nil
        PUSH     ECX                      // prepare lpfnHook = nil
        {$ENDIF}
        PUSH     EBX                      // prepare lCustData = @Self
        MOV      EDX, [EBX].FDefExtension
        CALL     EDX2PChar
        PUSH     EDX                      // prepare lpstrDefExt = FDefExtension
        PUSH     ECX                      // prepare nFileExtension, nFileOffset: Word = 0, 0
        // prepare flags:
        LEA      EAX, [EBX].FOptions
        MOV      EDX, Offset[@@OpenSaveFlags]
        {$IFDEF OpenSaveDialog_Extended}
        MOV      CL, 14
        {$ELSE}
        MOV      CL, 12
        {$ENDIF}
        CALL     MakeFlags
        XOR      ECX, ECX
        OR       EAX, OFN_EXPLORER or OFN_LONGNAMES or OFN_ENABLESIZING
        PUSH     EAX                       // push Flags
        PUSH     [EBX].FTitle              // prepare lpstrTitle
        PUSH     [EBX].FInitialDir         // prepare lpstrInitialDir
        PUSH     ECX                       // prepare nMaxFileTitle = 0
        PUSH     ECX                       // prepare lpstrFileTitle = nil
        TEST     AH, 2      // MultiSelect?
        MOV      EAX, 65520
        JNZ      @@1
        MOV      AX, MAX_PATH+2
@@1:    PUSH     EAX                       // prepare nMaxFile
        CALL     System.@GetMem
        POP      ECX
        PUSH     ECX
        PUSH     EAX                       // prepare lpStrFile
        XOR      EDX, EDX

@@2:    MOV      EDX, [EBX].fFileName // no, fill it initilly by FileName
        CALL     EDX2PChar
        DEC      ECX // added 5 october 2003 to prevent possible error if FileName too big
        CALL     StrLCopy
        XOR      EDX, EDX

        PUSH     [EBX].FFilterIndex        // prepare nFilterIndex
        PUSH     EDX                       // prepare nMaxCustFilter
        PUSH     EDX                       // prepare lpstrCustomFilter
        PUSH     EDX                       // prepare lpstrFilter = nil
        MOV      EAX, ESP
        OR       EDX, [EBX].FFilter
        JZ       @@5

        MOV      ECX, offset[@@0]
        CALL     System.@LStrCat3          // prepare lpStrFilter = FFilter + #0
        POP      EAX
        PUSH     EAX
        XOR      EDX, EDX
@@3:    INC      EAX   // filter is not starting from ';' or '|'...
        CMP      [EAX], DL
        JZ       @@5
        CMP      byte ptr [EAX], '|'
        JNZ      @@3
@@4:    MOV      [EAX], DL
        JMP      @@3
@@OpenSaveFlags:
        DD OFN_CREATEPROMPT, OFN_EXTENSIONDIFFERENT, OFN_FILEMUSTEXIST
        DD OFN_HIDEREADONLY, OFN_NOCHANGEDIR, OFN_NODEREFERENCELINKS
        DD OFN_ALLOWMULTISELECT, OFN_NONETWORKBUTTON, OFN_NOREADONLYRETURN
        DD OFN_OVERWRITEPROMPT, OFN_PATHMUSTEXIST, OFN_READONLY, OFN_NOVALIDATE
        {$IFDEF OpenSaveDialog_Extended}
        DD OFN_ENABLETEMPLATE, OFN_ENABLEHOOK
        {$ENDIF}

        DD       -1, 1
@@0:    DB       0


@@5:
        PUSH     [hInstance]               // prepare hInstance

        MOV      ECX, [EBX].TControl.fWnd
        INC      ECX
        LOOP     @@6
        MOV      ECX, [Applet]
        JECXZ    @@6
        MOV      ECX, [ECX].TControl.fHandle
@@6:    PUSH     ECX                       // prepare hWndOwner
        {$IFDEF OpenSaveDialog_Extended}
        CALL     WinVer
        CMP      AL, wvNT
        MOV      DL, 76+12
        JA       @@6a
        CMP      AL, wvME
        JE       @@6a
        MOV      DL, 76
@@6a:   MOVZX    EAX, DL
        PUSH     EAX
        {$ELSE}
        PUSH     76                        // prepare lStructSize
        {$ENDIF}

        PUSH     ESP
        CMP      [EBX].TControl.FOpenDialog, 0
        JZ       @@7
        CALL     GetOpenFileName
        JMP      @@8
@@7:    CALL     GetSaveFileName
@@8:
        PUSH     EAX
        XOR      EDX, EDX
        TEST     EAX, EAX
        JZ       @@10

        MOV      EAX, [ESP+4].TOpenFileName.nFilterIndex
        MOV      [EBX].FFilterIndex, EAX

        TEST     BYTE PTR [ESP+4].TOpenFileName.Flags, OFN_READONLY
        SETNZ    AL
        MOV      [EBX].fOpenReadOnly, AL

        MOV      EAX, [ESP+4].TOpenFileName.lpstrFile
        MOV      EDX, EAX
        XOR      ECX, ECX

        TEST     [EBX].FOptions, 1 shl OSAllowMultiSelect
        JZ       @@10

        DEC      EAX
@@9:    INC      EAX
        CMP      byte ptr [EAX], CL
        JNZ      @@9
        CMP      byte ptr [EAX+1], CL
        JZ       @@10
        MOV      byte ptr [EAX], 13
        JMP      @@9

@@10:
        LEA      EAX, [EBX].FFileName
        CALL     System.@LStrFromPChar
        MOV      EAX, [ESP+4].TOpenFileName.lpstrFile
        CALL     System.@FreeMem // v1.86 +AK

        LEA      EAX, [ESP+4].TOpenFileName.lpstrFilter
        CALL     System.@LStrClr

        POP      EAX
        {$IFDEF OpenSaveDialog_Extended}
        ADD      ESP, 76+12
        {$ELSE}
        ADD      ESP, 76
        {$ENDIF}
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

destructor TOpenDirDialog.Destroy;
asm     //cmd    //opd
        PUSH     EAX
        PUSH     0
        LEA      EDX, [EAX].FTitle
        PUSH     EDX
        LEA      EDX, [EAX].FInitialPath
        PUSH     EDX
        LEA      EAX, [EAX].FStatusText
@@loo:
        {$IFDEF UNICODE_CTRLS}
        CALL     System.@WStrClr
        {$ELSE}
        CALL     System.@LStrClr
        {$ENDIF}
        POP      EAX
        TEST     EAX, EAX
        JNZ      @@loo
        POP      EAX
        CALL     TObj.Destroy
end;

{$IFDEF ASM_UNICODE}
function OpenDirSelChangeCallBack( Wnd: HWnd; Msg: DWORD; lParam, lpData: LParam ):
         Integer; stdcall;
asm
        MOV      EAX, [lpData]
        MOV      ECX, [EAX].TOpenDirDialog.FOnSelChanged.TMethod.Code
        JECXZ    @@exit

        LEA      EDX, [EAX].TOpenDirDialog.FBuf
        PUSH     EDX
        PUSH     [lParam]
        CALL     SHGetPathFromIDListA

        MOV      EDX, [lpData]
        LEA      ECX, [EDX].TOpenDirDialog.FBuf
        PUSH     0
        PUSH     ESP
        LEA      EAX, [EDX].TOpenDirDialog.FStatusText
        PUSH     EAX
        MOV      EAX, [EDX].TOpenDirDialog.FOnSelChanged.TMethod.Data
        CALL     dword ptr [EDX].TOpenDirDialog.FOnSelChanged.TMethod.Code
        PUSH     0
        PUSH     BFFM_ENABLEOK
        PUSH     [Wnd]
        CALL     SendMessage
@@1:
        MOV      EDX, [lpData]
        MOV      ECX, [EDX].TOpenDirDialog.FStatusText
        JECXZ    @@exit

        PUSH     ECX
        PUSH     0
        PUSH     BFFM_SETSTATUSTEXT
        PUSH     [Wnd]
        CALL     SendMessage

@@exit: XOR      EAX, EAX
end;
{$ENDIF}

{$IFNDEF NEW_OPEN_DIR_STYLE_EX}
function OpenDirCallBack( Wnd: HWnd; Msg: DWORD; lParam, lpData: LParam ): Integer;
         stdcall;
asm
        MOV      EAX, [Wnd]
        MOV      EDX, [lpData]

        MOV      [EDX].TOpenDirDialog.FDialogWnd, EAX

        MOV      ECX, [Msg]
        LOOP     @@chk_sel_chg
        // Msg = 1 -> BFFM_Initialized

        MOV      ECX, [EDX].TOpenDirDialog.FCenterProc
        JECXZ    @@1
        PUSH     EDX
        CALL     ECX
        POP      EDX
@@1:    MOV      ECX, [EDX].TOpenDirDialog.FInitialPath
        JECXZ    @@exit
        PUSH     ECX
        PUSH     1
        PUSH     BFFM_SETSELECTION
        PUSH     [Wnd]
        CALL     SendMessage
        JMP      @@exit

@@chk_sel_chg:
        LOOP     @@exit
        // Msg = 2 -> BFFM_SelChanged

        MOV      ECX, [EDX].TOpenDirDialog.FDoSelChanged
        JECXZ    @@exit
        POP      EBP
        JMP      ECX

@@exit: XOR      EAX, EAX
end;
{$ENDIF}

procedure OpenDirDlgCenter( Wnd: HWnd );
asm
        PUSH     EBX
        MOV      EBX, EAX

        ADD      ESP, -16
        PUSH     ESP
        PUSH     EAX
        CALL     GetWindowRect
        POP      EDX          // EDX = Left
        POP      ECX          // ECX = Top
        POP      EAX          // EAX = Right
        SUB      EAX, EDX     // EAX = W
        POP      EDX          // EDX = Bottom
        SUB      EDX, ECX     // EDX = H
        XOR      ECX, ECX
        INC      ECX
        PUSH     ECX  // prepare True
        PUSH     EDX  // prepare H
        PUSH     EAX  // prepare W

        INC      ECX
@@1:
        PUSH     ECX

        DEC      ECX
        PUSH     ECX
        CALL     GetSystemMetrics

        POP      ECX
        SUB      EAX, [ESP+4]
        SAR      EAX, 1
        PUSH     EAX

        LOOP     @@1

        PUSH     EBX
        CALL     MoveWindow
        POP      EBX
end;

procedure TOpenDirDialog.SetCenterOnScreen(const Value: Boolean);
asm
        MOV      [EAX].FCenterOnScreen, DL
        MOVZX    ECX, DL
        JECXZ    @@1
        MOV      ECX, Offset[OpenDirDlgCenter]
@@1:    MOV      [EAX].FCenterProc, ECX
end;

{$IFDEF ASM_UNICODE}
function TControl.TBAddInsButtons(Idx: Integer; const Buttons: array of PKOLChar;
  const BtnImgIdxArray: array of Integer): Integer; stdcall;
asm
        { [EBP+$8] = @Self
          [EBP+$C] = Idx
          [EBP+$10] = Buttons
          [EBP+$14] = High(Butons)
          [EBP+$18] = BtnImgIdxArray
          [EBP+$1C] = High(BtnImgIdxArray)
        }
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        OR       EBX, -1
        MOV      EAX, 20
        MOV      ECX, [EBP+$14]
        CMP      ECX, EBX
        JLE      @@fin
        INC      ECX
        MUL      ECX
        CALL     System.@GetMem
        PUSH     EAX           // save AB to FreeMem after
        MOV      EDX, EBX
        DEC      EDX           // nBmp := -2

        MOV      ECX, [EBP+$14]
        INC      ECX
        JZ       @@exit

        MOV      ECX, [EBP+$1C]
        INC      ECX
        JZ       @@1
        MOV      ECX, [BtnImgIdxArray]
        MOV      EDX, [ECX]
        DEC      EDX           // nBmp := BtnImgIdxArray[ 0 ] - 1
@@1:    MOV      ECX, [EBP+$14]
        INC      ECX
        MOV      ESI, [Buttons]
        MOV      EDI, EAX      // EDI = PAB
        PUSH     0             // N:=0 in [EBP-$14]
        // -- impossible?-- JZ       @@break
@@loop:
        LODSD
        TEST     EAX, EAX
        JZ       @@break
        PUSH     ECX

        CMP      word ptr [EAX], '-'
        JNE      @@2

        OR       EAX, -1
        STOSD
        MOV      EAX, [ToolbarsIDcmd]
        TEST     EBX, EBX
        {$IFDEF USE_CMOV}
        CMOVL    EBX, EAX
        {$ELSE}
        JGE      @@b0
        MOV      EBX, EAX
@@b0:   {$ENDIF}

        //INC      [ToolbarsIDcmd]
        STOSD
        XOR      EAX, EAX
        INC      AH  // TBSTYLE_SEP = 1
        STOSD
        DEC      AH
        STOSD
        DEC      EAX
        JMP      @@3

        DD       -1, 1
@@0:    DB       0

@@2:
        INC      EDX  // Inc( nBmp )
        PUSH     EAX

        MOV      EAX, [EBP+$1C]
        MOV      ECX, [EBP-$14]
        CMP      EAX, ECX
        MOV      EAX, EDX
        JL       @@21
        MOV      EAX, [BtnImgIdxArray]
        MOV      EAX, [EAX+ECX*4]
@@21:   STOSD

        TEST     EDX, EDX
        JGE      @@2a
        DEC      EDX
@@2a:

        MOV      EAX, [ToolbarsIDcmd]
        //INC      [ToolbarsIDcmd]
        STOSD
        TEST     EBX, EBX
        {$IFDEF USE_CMOV}
        CMOVL    EBX, EAX
        {$ELSE}
        JGE      @@210
        MOV      EBX, EAX
@@210:  {$ENDIF}

        POP      ECX
        MOV      AX, $1004 // AL=fsState=_ENABLED, AH=fsStyle=_AUTOSIZE
        CMP      byte ptr [ECX], '^'
        JNE      @@22
        MOV      AH, TBSTYLE_DROPDOWN or TBSTYLE_AUTOSIZE
        INC      ECX
@@22:   CMP      byte ptr [ECX], '-'
        JZ       @@23
        CMP      byte ptr [ECX], '+'
        JNZ      @@24
        MOV      AL, TBSTATE_ENABLED or TBSTATE_CHECKED
@@23:   INC      ECX
        OR       AH, TBSTYLE_CHECK
        CMP      byte ptr [ECX], '!'
        JNZ      @@24
        OR       AH, TBSTYLE_GROUP
        INC      ECX
@@24:   {$IFDEF TOOLBAR_DOT_NOAUTOSIZE_BUTTON}
        CMP      byte ptr [ECX], '.'
        JNZ      @@25
        AND      AH, not TBSTYLE_AUTOSIZE
        INC      ECX
@@25:
        {$ENDIF TOOLBAR_DOT_NOAUTOSIZE_BUTTON}
        STOSD
        MOV      EAX, [EBP+8]
        STOSD
        OR       EAX, -1
        CMP      word ptr [ECX], ' '
        JZ       @@3
        CMP      byte ptr [ECX], 0
        JZ       @@3

        PUSH     EDX
        PUSH     0
        MOV      EDX, ECX
        MOV      EAX, ESP
        CALL     System.@LStrFromPChar
        MOV      EAX, ESP
        MOV      EDX, offset[@@0]
        CALL     System.@LStrCat
        PUSH     dword ptr [ESP]
        PUSH     0
        PUSH     TB_ADDSTRING
        PUSH     dword ptr [EBP+8]
        CALL     Perform
        STOSD

        CALL     RemoveStr
        POP      EDX
        JMP      @@30

@@3:    STOSD
@@30:   INC      dword ptr [EBP-$14]
        INC      [ToolbarsIDcmd]
        POP      ECX
        DEC      ECX
        JNZ      @@loop
@@break:
        POP      ECX
        JECXZ    @@exit
        PUSH     dword ptr [ESP]
        MOV      EAX, [Idx]
        TEST     EAX, EAX
        JGE      @@31

        PUSH     ECX
        PUSH     TB_ADDBUTTONS
        JMP      @@32
@@31:
        PUSH     EAX
        PUSH     TB_INSERTBUTTON
@@32:
        PUSH     dword ptr [EBP+8]
        CALL     Perform
@@exit:
        POP      EAX
        CALL     System.@FreeMem
@@fin:
        POP      EDI
        POP      ESI
        XCHG     EAX, EBX
        POP      EBX
end;
{$ENDIF ASM_UNICODE}

function TControl.TBAddButtons(const Buttons: array of PKOLChar;
         const BtnImgIdxArray: array of Integer): Integer;
asm
        PUSH     dword ptr [EBP+8]
        PUSH     dword ptr [EBP+12]
        PUSH     ECX
        PUSH     EDX
        PUSH     -1
        PUSH     EAX
        CALL     TBAddInsButtons
end;

function TControl.TBGetBtnStt(BtnID: Integer; const Index: Integer): Boolean;
asm
        PUSH     0
        PUSH     ECX
        PUSH     EAX
        CALL     GetTBBtnGoodID
        POP      EDX
        POP      ECX
        PUSH     EAX
        ADD      ECX, 8
        PUSH     ECX
        PUSH     EDX
        CALL     Perform
        TEST     EAX, EAX
        SETNZ    AL
end;

function TControl.TBIndex2Item(Idx: Integer): Integer;
const                                                 //
  _sizeof_TTBButton = sizeof( TTBButton );            //
asm
        ADD      ESP, -_sizeof_TTBButton              //
        PUSH     ESP
        PUSH     EDX
        PUSH     TB_GETBUTTON
        PUSH     EAX
        CALL     Perform
        TEST     EAX, EAX
        MOV      EAX, [ESP].TTBButton.idCommand
        JNZ      @@1
        OR       EAX, -1
@@1:    ADD      ESP, _sizeof_TTBButton               //
end;

{$IFDEF ASM_UNICODE}
function TControl.TBGetButtonText( BtnID: Integer ): String;
asm
        PUSH     ECX
        ADD      ESP, -1024
        PUSH     ESP
        PUSH     EAX
        CALL     GetTBBtnGoodID
        POP      EDX
        PUSH     EAX
        PUSH     TB_GETBUTTONTEXT
        PUSH     EDX
        CALL     Perform
        TEST     EAX, EAX
        JLE      @@2
        MOV      EDX, ESP
        JMP      @@1
@@2:    XOR      EDX, EDX
@@1:    MOV      EAX, [ESP+1024]
        CALL     System.@LStrFromPChar
        ADD      ESP, 1028
end;
{$ENDIF}

{$IFDEF ASM_UNICODE}
procedure TControl.TBSetTooltips(BtnID1st: Integer;
  const Tooltips: array of PKOLChar);
asm
        PUSH     EBX
        PUSH     ESI
        MOV      ESI, ECX
        MOV      EBX, EAX
        PUSHAD
        MOV      ECX, [EBX].fTBttCmd
        INC      ECX
        LOOP     @@1
        CALL     NewList
        MOV      [EBX].fTBttCmd, EAX
        {$IFDEF USE_AUTOFREE4CONTROLS}
        XCHG     EDX, EAX
        MOV      EAX, EBX
        CALL     TControl.Add2AutoFree
        {$ENDIF}
        CALL     NewStrList
        MOV      [EBX].fTBttTxt, EAX
        {$IFDEF USE_AUTOFREE4CONTROLS}
        XCHG     EDX, EAX
        MOV      EAX, EBX
        CALL     TControl.Add2AutoFree
        {$ENDIF}
@@1:    POPAD
        MOV      ECX, [EBP+8]
        INC      ECX
        JZ       @@exit
@@loop:
        PUSH     ECX
        PUSH     EDX
        PUSH     0
        LODSD
        MOV      EDX, EAX
        MOV      EAX, ESP
        CALL     System.@LStrFromPChar

        MOV      EDX, [ESP+4]
        MOV      EAX, [EBX].fTBttCmd
        CALL     TList.IndexOf
        TEST     EAX, EAX
        JGE      @@2

        MOV      EDX, [ESP+4]
        MOV      EAX, [EBX].fTBttCmd
        CALL     TList.Add
        POP      EDX
        PUSH     EDX
        MOV      EAX, [EBX].fTBttTxt
        CALL     TStrList.Add
        JMP      @@3

@@2:
        MOV      EDX, EAX
        POP      ECX
        PUSH     ECX
        MOV      EAX, [EBX].fTBttTxt
        CALL     TStrList.Put
@@3:
        CALL     RemoveStr

        POP      EDX
        POP      ECX
        INC      EDX
        LOOP     @@loop
@@exit:
        POP      ESI
        POP      EBX
end;
{$ENDIF}

function TControl.TBButtonAtPos(X, Y: Integer): Integer;
asm
        PUSH     EAX
        CALL     TBBtnIdxAtPos
        TEST     EAX, EAX
        MOV      EDX, EAX
        POP      EAX
        JGE      TBIndex2Item
        MOV      EAX, EDX
end;

function TControl.TBBtnIdxAtPos(X, Y: Integer): Integer;
asm
        PUSH     EBX
        PUSH     ECX
        PUSH     EDX
        MOV      EBX, EAX
        CALL     GetItemsCount
        MOV      ECX, EAX
        JECXZ    @@fin
@@1:    PUSH     ECX
        ADD      ESP, -16
        PUSH     ESP
        DEC      ECX
        PUSH     ECX
        PUSH     TB_GETITEMRECT
        PUSH     EBX
        CALL     Perform
        MOV      EDX, ESP
        LEA      EAX, [ESP+20]
        CALL     PointInRect
        ADD      ESP, 16
        POP      ECX
        TEST     AL, AL
        {$IFDEF USE_CMOV}
        CMOVNZ   EAX, ECX
        {$ELSE}
        JZ       @@2
        MOV      EAX, ECX
        JMP      @@fin
@@2:    {$ENDIF}
        JNZ      @@fin

        LOOP     @@1
@@fin:  DEC      EAX
        POP      EDX
        POP      EDX
        POP      EBX
end;

procedure TControl.TBSetButtonText(BtnID: Integer; const Value: KOLString);
asm
        PUSH     0
        PUSH     ECX
        PUSH     EAX
        CALL     GetTBBtnGoodID
        POP      EDX

        ADD      ESP, -16
        PUSH     TBIF_TEXT
        PUSH     32 //Sizeof( TTBButtonInfo )
        PUSH     ESP
        PUSH     EAX
        PUSH     TB_SETBUTTONINFO
        PUSH     EDX
        CALL     Perform
        ADD      ESP, 32 //sizeof( TTBButtonInfo )
end;

function TControl.TBGetBtnWidth(BtnID: Integer): Integer;
asm
        ADD      ESP, -16
        MOV      ECX, ESP
        CALL     TBGetButtonRect
        POP      EDX
        POP      ECX
        POP      EAX
        SUB      EAX, EDX
        POP      EDX
end;

procedure TControl.TBSetBtnWidth(BtnID: Integer; const Value: Integer);
asm
        PUSH     EBX
        MOV      EBX, ECX

        PUSH     EAX
        CALL     GetTBBtnGoodID
        POP      EDX

        ADD      ESP, -24
        PUSH     TBIF_SIZE or TBIF_STYLE
        PUSH     32
        MOV      ECX, ESP

        PUSH     ECX
        PUSH     EAX
        PUSH     TB_SETBUTTONINFO
        PUSH     EDX

        PUSH     ECX
        PUSH     EAX
        PUSH     TB_GETBUTTONINFO
        PUSH     EDX
        CALL     Perform

        MOV      [ESP+16+18], BX
        AND      byte ptr [ESP+16].TTBButtonInfo.fsStyle, not TBSTYLE_AUTOSIZE
        CALL     Perform
        ADD      ESP, 32
        POP      EBX
end;

procedure TControl.AddDirList(const Filemask: KOLString; Attrs: DWORD);
asm
        CALL     EDX2PChar
        PUSH     EDX
        PUSH     ECX
        MOVZX    ECX, [EAX].fCommandActions.aDir
        JECXZ    @@exit
        PUSH     ECX
        PUSH     EAX
        CALL     Perform
        RET
@@exit:
        POP      ECX
        POP      ECX
end;

{$IFDEF noASM_VERSION}
function WndProcShowModal( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm
        CMP      word ptr [EDX].TMsg.message, WM_CLOSE
        JNZ      @@ret_false

        XCHG     EDX, EAX
        XOR      EAX, EAX
        CMP      [EDX].TControl.fModalResult, EAX
        JNZ      @@1
        OR       [EDX].TControl.fModalResult, -1
@@1:
        MOV      [ECX], EAX
        INC      EAX
        RET
@@ret_false:
        XOR      EAX, EAX

end;
{$ENDIF}

function TimerProc( Wnd : HWnd; Msg : Integer; T : PTimer; CurrentTime : DWord ): Integer;
          stdcall;
asm     //cmd    //opd
        {$IFDEF STOPTIMER_AFTER_APPLETTERMINATED}
        CMP      [AppletTerminated], 0
        JNZ      @@exit
        {$ENDIF}
        MOV      EDX, T
        MOV      ECX, [EDX].TTimer.fOnTimer.TMethod.Code
        JECXZ    @@exit
        MOV      EAX, [EDX].TTimer.fOnTimer.TMethod.Data
        CALL     ECX
@@exit: XOR      EAX, EAX
end;

destructor TTimer.Destroy;
asm
        PUSH     EAX
        XOR      EDX, EDX
        CALL     TTimer.SetEnabled
        POP      EAX
        CALL     TObj.Destroy
        DEC      [TimerCount]
        JNZ      @@exit
        XOR      EAX, EAX
        XCHG     EAX, [TimerOwnerWnd]
        CALL     TObj.RefDec
@@exit:
end;

procedure TTimer.SetEnabled(const Value: Boolean);
asm
        PUSH     EBX
        XCHG     EBX, EAX

        CMP      [EBX].fEnabled, DL
        JZ       @@exit

        {$IFDEF TIMER_APPLETWND}

        MOV      ECX, [Applet]
        JECXZ    @@exit

        MOV      [EBX].fEnabled, DL
        TEST     DL, DL
        JZ       @@disable

        {$ELSE}

        MOV      [EBX].fEnabled, DL
        TEST     DL, DL
        JZ       @@disable

        MOV      ECX, [TimerOwnerWnd]
        INC      ECX
        LOOP     @@owner_ready

        INC      ECX
        MOV      EDX, offset[EmptyString]
        XOR      EAX, EAX
        CALL     _NewWindowed
        MOV      [TimerOwnerWnd], EAX
        MOV      [EAX].TControl.fStyle, 0
        INC      [EAX].TControl.fIsControl
        XCHG     ECX, EAX

        {$ENDIF}

@@owner_ready:

        PUSH     offset[TimerProc]
        PUSH     [EBX].fInterval
        PUSH     EBX
        XCHG     EAX, ECX
        CALL     TControl.GetWindowHandle
        PUSH     EAX
        CALL     SetTimer
        MOV      [EBX].fHandle, EAX

        JMP      @@exit

@@disable:
        XOR      ECX, ECX
        XCHG     ECX, [EBX].TTimer.fHandle
        JECXZ    @@exit

        PUSH     ECX
        {$IFDEF TIMER_APPLETWND}
        MOV      EAX, [Applet]
        {$ELSE}
        MOV      EAX, [TimerOwnerWnd]
        {$ENDIF}
        PUSH     [EAX].TControl.fHandle
        CALL     KillTimer

@@exit:
        POP      EBX
end;

function PrepareBitmapHeader( W, H, BitsPerPixel: Integer ): PBitmapInfo;
const szIH = sizeof(TBitmapInfoHeader);
      szHd = szIH + 256 * Sizeof(TRGBQuad);
asm
        PUSH     EDI

          PUSH     ECX  // BitsPerPixel
        PUSH     EDX    // H
        PUSH     EAX    // W

        MOV      EAX, szHd
        CALL     AllocMem

        MOV      EDI, EAX
        XCHG     ECX, EAX

        XOR      EAX, EAX
        MOV      AL, szIH
        STOSD           // biSize = Sizeof( TBitmapInfoHeader )
        POP      EAX    // ^ W
        STOSD           // -> biWidth
        POP      EAX    // ^ H
        STOSD           // -> biHeight
        XOR      EAX, EAX
        INC      EAX
        STOSW           // 1 -> biPlanes
          POP      EAX  // ^ BitsPerPixel
        STOSW           // -> biBitCount

        XCHG     EAX, ECX // EAX = Result
        POP      EDI
end;

function Bits2PixelFormat( BitsPerPixel: Integer ): TPixelFormat;
asm
        PUSH     ESI
        MOV      ESI, offset[ BitsPerPixel_By_PixelFormat + 1 ]
        XOR      ECX, ECX
        XCHG     EDX, EAX
@@loo:  INC      ECX
        LODSB
        CMP      AL, DL
        JZ       @@exit
        TEST     AL, AL
        JNZ      @@loo
@@exit: XCHG     EAX, ECX
        POP      ESI
end;

function _NewBitmap( W, H: Integer ): PBitmap;
begin
  New( Result, Create );
  Result.fDetachCanvas := DummyDetachCanvas;
  Result.fWidth := W;
  Result.fHeight := H;
end;
function NewBitmap( W, H: Integer ): PBitmap;
asm
        PUSH     EAX
        PUSH     EDX
        CALL     _NewBitmap
        POP      EDX
        POP      ECX
        PUSH     EAX
        INC      [EAX].TBitmap.fHandleType
        JECXZ    @@exit
        TEST     EDX, EDX
        JZ       @@exit
        PUSH     EBX
        PUSH     EAX
        PUSH     EDX
        PUSH     ECX
        PUSH     0
        CALL     GetDC
        PUSH     EAX
        XCHG     EBX, EAX
        CALL     CreateCompatibleBitmap
        POP      EDX
        MOV      [EDX].TBitmap.fHandle, EAX
        PUSH     EBX
        PUSH     0
        CALL     ReleaseDC
        POP      EBX
@@exit: POP      EAX
end;

procedure PreparePF16bit( DIBHeader: PBitmapInfo );
const szBIH = sizeof(TBitmapInfoHeader);
asm
        MOV      byte ptr [EAX].TBitmapInfoHeader.biCompression, BI_BITFIELDS
        ADD      EAX, szBIH
        XCHG     EDX, EAX
        MOV      EAX, offset[InitColors]
        XOR      ECX, ECX
        MOV      CL, 19*4
        CALL     System.Move
end;

function NewDIBBitmap( W, H: Integer; PixelFormat: TPixelFormat ): PBitmap;
asm
        PUSH     EBX

        PUSH     ECX
        PUSH     EDX
        PUSH     EAX
        CALL     _NewBitmap
        XCHG     EBX, EAX
        POP      EAX //W
        POP      EDX //H
        POP      ECX //PixelFormat

        TEST     EAX, EAX
        JZ       @@exit
        TEST     EDX, EDX
        JZ       @@exit

        PUSH     EAX
        MOVZX    EAX, CL
        JMP      @@loadBitsPixel
@@loadDefault:
        MOVZX    EAX, [DefaultPixelFormat]
@@loadBitsPixel:
        MOVZX    ECX, byte ptr [ BitsPerPixel_By_PixelFormat + EAX ]
        JECXZ    @@loadDefault
        MOV      [EBX].TBitmap.fNewPixelFormat, AL
        {$IFDEF PARANOIA} DB $3C, pf16bit {$ELSE} CMP AL, pf16bit {$ENDIF}
        POP      EAX

        PUSHFD
        CALL     PrepareBitmapHeader
        MOV      [EBX].TBitmap.fDIBHeader, EAX
        POPFD
        JNZ      @@2

        CALL     PreparePF16bit

@@2:
        MOV      EAX, EBX
        CALL     TBitmap.GetScanLineSize
        MOV      EDX, [EBX].TBitmap.fHeight
        MUL      EDX
        MOV      [EBX].TBitmap.fDIBSize, EAX
        ADD      EAX, 16
        PUSH     EAX
        PUSH     GMEM_FIXED or GMEM_ZEROINIT
        CALL     GlobalAlloc
        MOV      [EBX].TBitmap.fDIBBits, EAX
@@exit:
        XCHG     EAX, EBX
        POP      EBX
end;

procedure TBitmap.ClearData;
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     [EBX].fDetachCanvas
        XOR      ECX, ECX
        XCHG     ECX, [EBX].fHandle
        JECXZ    @@1
        PUSH     ECX
        CALL     DeleteObject
        XOR      ECX, ECX
        MOV      [EBX].fDIBBits, ECX
@@1:    XCHG     ECX, [EBX].fDIBBits
        JECXZ    @@2
        PUSH     ECX
        CALL     GlobalFree
@@2:    XOR      ECX, ECX
        XCHG     ECX, [EBX].fDIBHeader
        JECXZ    @@3
        XCHG     EAX, ECX
        CALL     System.@FreeMem
@@3:    XOR      EAX, EAX
        MOV      [EBX].fScanLineSize, EAX
        MOV      [EBX].fGetDIBPixels, EAX
        MOV      [EBX].fSetDIBPixels, EAX
        XCHG     EAX, EBX
        POP      EBX
        CALL     ClearTransImage
end;

procedure TBitmap.Clear;
asm
        PUSH     EAX
        CALL     RemoveCanvas
        POP      EAX
        PUSH     EAX
        CALL     ClearData
        POP      EAX
        XOR      EDX, EDX
        MOV      [EAX].fWidth, EDX
        MOV      [EAX].fHeight, EDX
        MOV      [EAX].fDIBAutoFree, DL
end;

destructor TBitmap.Destroy;
asm
        PUSH     EAX
        CALL     Clear
        POP      EAX
        CALL     TObj.Destroy
end;

procedure TBitmap.Draw(DC: HDC; X, Y: Integer);
const szBitmap = sizeof( tagBitmap );
asm                       // [EBP+8] = Y
        PUSH     EDX      // [EBP-4] = DC
        PUSH     ECX      // [EBP-8] = X
        PUSH     EBX
        PUSH     ESI
@@try_again:
        MOV      EBX, EAX
        CALL     GetEmpty // GetEmpty must be assembler version !
        JZ       @@exit

        MOV      ECX, [EBX].fHandle
        JECXZ    @@2
        //MOV      EAX, EBX
        //CALL     [EBX].fDetachCanvas // detached in StartDC
        ADD      ESP, -szBitmap
        PUSH     ESP
        PUSH     szBitmap
        PUSH     [EBX].fHandle
        CALL     GetObject
        TEST     EAX, EAX
        MOV      ESI, [ESP].tagBitmap.bmHeight
        {$IFDEF USE_CMOV}
        CMOVZ    ESI, [EBX].fHeight
        {$ELSE}
        JNZ      @@1
        MOV      ESI, [EBX].fHeight
@@1:    {$ENDIF}

        ADD      ESP, szBitmap
        CALL     StartDC

        PUSH     SRCCOPY
        PUSH     0
        PUSH     0
        PUSH     EAX
        CALL     @@prepare
        CALL     BitBlt
        CALL     FinishDC
        JMP      @@exit

@@prepare:
        XCHG     ESI, [ESP]
        PUSH     [EBX].fWidth
        PUSH     Y
        PUSH     dword ptr [EBP-8]
        PUSH     dword ptr [EBP-4]
        JMP      ESI

@@2:
        MOV      ECX, [EBX].fDIBHeader
        JECXZ    @@exit

        MOV      ESI, [ECX].TBitmapInfoHeader.biHeight
        TEST     ESI, ESI
        JGE      @@20
        NEG      ESI
@@20:
        PUSH     SRCCOPY
        PUSH     DIB_RGB_COLORS
        PUSH     ECX
        PUSH     [EBX].fDIBBits
        PUSH     ESI
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        CALL     @@prepare
        CALL     StretchDIBits
        TEST     EAX, EAX
        JNZ      @@exit
        MOV      EAX, EBX
        CALL     GetHandle
        TEST     EAX, EAX
        XCHG     EAX, EBX
        JNZ      @@try_again
@@exit:
        POP      ESI
        POP      EBX
        MOV      ESP, EBP
end;

procedure TBitmap.StretchDraw(DC: HDC; const Rect: TRect);
asm
        PUSH     EBX
        PUSH     EDI
        PUSH     EBP
        MOV      EBP, ESP
        PUSH     EDX
        PUSH     ECX
        MOV      EBX, EAX
        CALL     GetEmpty
        JZ       @@exit

        MOV      ECX, [EBX].fHandle
        JECXZ    @@2

@@0:
        CALL     StartDC
        PUSH     SRCCOPY
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        PUSH     EAX

        CALL     @@prepare
        CALL     StretchBlt
        CALL     FinishDC
        JMP      @@exit

@@prepare:
        POP      EDI
        MOV      EAX, [EBP-8]
        MOV      EDX, [EAX].TRect.Bottom
        MOV      ECX, [EAX].TRect.Top
        SUB      EDX, ECX
        PUSH     EDX
        MOV      EDX, [EAX].TRect.Right
        MOV      EAX, [EAX].TRect.Left
        SUB      EDX, EAX
        PUSH     EDX
        PUSH     ECX
        PUSH     EAX
        PUSH     dword ptr [EBP-4]
        JMP      EDI


@@2:    MOV      ECX, [EBX].fDIBHeader
        JECXZ    @@exit

        PUSH     SRCCOPY
        PUSH     DIB_RGB_COLORS
        PUSH     ECX
        PUSH     [EBX].fDIBBits
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        CALL     @@prepare
        CALL     StretchDIBits
        TEST     EAX, EAX
        JG       @@exit

        MOV      EAX, EBX
        CALL     GetHandle
        MOV      ECX, [EBX].fHandle
        JECXZ    @@exit
        JMP      @@0

@@exit: MOV      ESP, EBP
        POP      EBP
        POP      EDI
        POP      EBX
end;

procedure TBitmap.DrawTransparent(DC: HDC; X, Y: Integer; TranspColor: TColor);
asm
        PUSH     ECX
        MOV      ECX, TranspColor
        INC      ECX
        MOV      ECX, [Y]
        JNZ      @@2
        XCHG     ECX, [ESP]
        CALL     Draw
        JMP      @@exit
@@2:
        ADD      ECX, [EAX].fHeight
        PUSH     ECX
        MOV      ECX, [EBP-4]
        ADD      ECX, [EAX].fWidth
        PUSH     ECX
        PUSH     [Y]
        PUSH     dword ptr [EBP-4]
        MOV      ECX, ESP
        PUSH     [TranspColor]
        CALL     StretchDrawTransparent
@@exit:
        MOV      ESP, EBP
end;

procedure TBitmap.StretchDrawTransparent(DC: HDC; const Rect: TRect; TranspColor: TColor);
asm
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [TranspColor]
        INC      EAX
        MOV      EAX, EBX
        JNZ      @@2
        CALL     StretchDraw
        JMP      @@exit
@@2:
        PUSH     EDX
        PUSH     ECX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit2

        MOV      EAX, [TranspColor]
        CALL     Color2RGB
        MOV      ECX, [EBX].fTransMaskBmp
        JECXZ    @@makemask0
        CMP      EAX, [EBX].fTransColor
        JE       @@3
@@makemask0:
        MOV      [EBX].fTransColor, EAX
        INC      ECX
        LOOP     @@20
        XOR      EAX, EAX // pass height = 0
        // absolutely no matter what to pass as width
        CALL     NewBitmap
        MOV      [EBX].fTransMaskBmp, EAX
@@20:
        MOV      EAX, [EBX].fTransMaskBmp
        PUSH     EAX
        MOV      EDX, EBX
        CALL     Assign
        POP      EAX
        MOV      EDX, [EBX].fTransColor
        CALL     Convert2Mask
@@3:
        MOV      EAX, [EBX].fTransMaskBmp
        CALL     GetHandle
        POP      ECX
        POP      EDX
        PUSH     EAX
        XCHG     EAX, EBX
        CALL     StretchDrawMasked
        JMP      @@exit
@@exit2:
        POP      ECX
        POP      EDX
@@exit:
        POP      EBX
end;

procedure TBitmap.StretchDrawMasked(DC: HDC; const Rect: TRect; Mask: HBitmap);
asm
        PUSH     EDX                    // [EBP-4] = DC
        PUSH     ECX                    // [EBP-8] = Rect
        PUSH     EBX                    // save EBX
        MOV      EBX, EAX               // EBX = @ Self
        PUSH     ESI                    // save ESI
  {$IFDEF FIX_TRANSPBMPPALETTE}
  CALL GetPixelFormat
  CMP  AL, pf4bit
  JZ   @@draw_fixed
  CMP  AL, pf8bit
  JNZ  @@draw_normal
  @@draw_fixed:
    XOR  EAX, EAX
    XOR  EDX, EDX
    CALL NewBitmap
    MOV  ESI, EAX
    MOV  EDX, EBX
    CALL Assign
    MOV  EAX, ESI
    XOR  EDX, EDX
    MOV  DL, pf32bit
    CALL SetPixelFormat
    MOV  EAX, ESI
    MOV  EDX, [EBP-4]
    MOV  ECX, [EBP-8]
    PUSH [Mask]
    CALL StretchDrawMasked
    XCHG EAX, ESI
    CALL TObj.RefDec
    JMP  @@exit
  @@draw_normal:
        MOV      EAX, EBX
  {$ENDIF FIX_TRANSPBMPPALETTE}
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@to_exit

        PUSH     0
        CALL     CreateCompatibleDC
        PUSH     EAX                    // [EBP-20] = MaskDC

        PUSH     [Mask]
        PUSH     EAX
        CALL     SelectObject
        PUSH     EAX                    // [EBP-24] = Save4Mask

        CALL     StartDC                // [EBP-28] = DCfrom; [EBP-32] = Save4From

        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     EAX
        CALL     CreateCompatibleBitmap
        PUSH     EAX                    // [EBP-36] = MemBmp

        PUSH     0
        CALL     CreateCompatibleDC
        PUSH     EAX                    // [EBP-40] = MemDC

        PUSH     dword ptr [EBP-36] //MemBmp
        PUSH     EAX
        CALL     SelectObject
        PUSH     EAX                    // [EBP-44] = Save4Mem

        PUSH     SRCCOPY
        MOV      EAX, [EBP-20] //MaskDC
        CALL     @@stretch1

        PUSH     SRCERASE
        MOV      EAX, [EBP-28] //DCfrom
        CALL     @@stretch1

        PUSH     0
        PUSH     dword ptr [EBP-4] //DC
        CALL     SetTextColor
        PUSH     EAX                    // [EBP-48] = crText

        PUSH     $FFFFFF
        PUSH     dword ptr [EBP-4] //DC
        CALL     Windows.SetBkColor
        PUSH     EAX                    // [EBP-52] = crBack

        PUSH     SRCAND
        MOV      EAX, [EBP-20] //MaskDC
        CALL     @@stretch2

        PUSH     SRCINVERT
        MOV      EAX, [EBP-40] //MemDC
        CALL     @@stretch2

        PUSH     dword ptr [EBP-4] //DC
        CALL     Windows.SetBkColor

        PUSH     dword ptr [EBP-4] //DC
        CALL     SetTextColor

        MOV      ESI, offset[FinishDC]
        CALL     ESI
        CALL     DeleteObject   // DeleteObject( MemBmp )
        CALL     ESI
        CALL     ESI
@@to_exit:
        STC
        JC       @@exit

@@stretch1:
        POP      ESI
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        XOR      EDX, EDX
        PUSH     EDX
        PUSH     EDX
        PUSH     EAX
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     EDX
        PUSH     EDX
        PUSH     dword ptr [EBP-40] //MemDC
        JMP      @@stretch3

@@stretch2:
        POP      ESI
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        PUSH     EAX
        MOV      EAX, [EBP-8] //Rect
        MOV      EDX, [EAX].TRect.Bottom
        MOV      ECX, [EAX].TRect.Top
        SUB      EDX, ECX
        PUSH     EDX
        MOV      EDX, [EAX].TRect.Right
        MOV      EAX, [EAX].TRect.Left
        SUB      EDX, EAX
        PUSH     EDX
        PUSH     ECX
        PUSH     EAX
        PUSH     dword ptr [EBP-4] //DC
@@stretch3:
        CALL     StretchBlt
        JMP      ESI

@@exit:
        POP      ESI
        POP      EBX
        MOV      ESP, EBP
end;

procedure DetachBitmapFromCanvas( Sender: PBitmap );
asm
        XOR      ECX, ECX
        XCHG     ECX, [EAX].TBitmap.fCanvasAttached
        JECXZ    @@exit
        PUSH     ECX
        MOV      EAX, [EAX].TBitmap.fCanvas
        PUSH     [EAX].TCanvas.fHandle
        CALL     SelectObject
@@exit:
end;

function TBitmap.GetCanvas: PCanvas;
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     GetEmpty
        JZ       @@exit
        MOV      EAX, EBX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit
        MOV      ECX, [EBX].fCanvas
        INC      ECX
        LOOP     @@ret_Canvas

        MOV      [EBX].fApplyBkColor2Canvas, offset[ApplyBitmapBkColor2Canvas]
        PUSH     0
        CALL     CreateCompatibleDC
        CALL     NewCanvas
        MOV      [EBX].fCanvas, EAX
        MOV      [EAX].TCanvas.fOnChange.TMethod.Code, offset[CanvasChanged]
        MOV      [EAX].TCanvas.fOnChange.TMethod.Data, EBX
        CALL     TCanvas.GetBrush
        XOR      EDX, EDX
        MOV      ECX, [EBX].fBkColor
        JECXZ    @@ret_Canvas
        CALL     TGraphicTool.SetInt

@@ret_Canvas:
        MOV      EAX, [EBX].fCanvas
        MOV      ECX, [EAX].TCanvas.fHandle
        INC      ECX
        LOOP     @@attach_Canvas
        PUSH     EAX
        MOV      [EBX].fCanvasAttached, ECX
        PUSH     ECX
        CALL     CreateCompatibleDC
        XCHG     EDX, EAX
        POP      EAX
        CALL     TCanvas.SetHandle

@@attach_Canvas:
        MOV      ECX, [EBX].fCanvasAttached
        INC      ECX
        LOOP     @@2
        PUSH     [EBX].fHandle
        MOV      EAX, [EBX].fCanvas
        CALL     TCanvas.GetHandle
        PUSH     EAX
        CALL     SelectObject
        MOV      [EBX].fCanvasAttached, EAX

@@2:    MOV      [EBX].fDetachCanvas, offset[DetachBitmapFromCanvas]
        MOV      EAX, [EBX].fCanvas
@@exit: POP      EBX
end;

function TBitmap.GetEmpty: Boolean;
asm
        PUSH     ECX
        MOV      ECX, [EAX].fWidth
        JECXZ    @@1
        MOV      ECX, [EAX].fHeight
@@1:    TEST     ECX, ECX
        POP      ECX
        SETZ     AL
end;

procedure TBitmap.LoadFromFile(const Filename: KOLString);
asm
        PUSH     EAX
        XCHG     EAX, EDX
        CALL     NewReadFileStream
        XCHG     EDX, EAX
        POP      EAX
        PUSH     EDX
        CALL     LoadFromStream
        POP      EAX
        CALL     TObj.RefDec
end;

{$IFDEF ASM_UNICODE}
procedure TBitmap.LoadFromResourceName(Inst: DWORD; ResName: PChar);
asm
        PUSH     EBX
        MOV      EBX, EAX
        PUSHAD
        CALL     Clear
        POPAD
        XOR      EAX, EAX
        PUSH     ECX
        MOVZX    ECX, [EBX].fHandleType
        INC      ECX
        LOOP     @@1
        MOV      AH, LR_CREATEDIBSECTION shr 8 // = $2000
@@1:    MOV      AL, LR_DEFAULTSIZE // = $40
        POP      ECX
        PUSH     EAX
        PUSH     0
        PUSH     0
        PUSH     IMAGE_BITMAP
        PUSH     ECX
        PUSH     EDX
        CALL     LoadImage
        TEST     EAX, EAX
        JZ       @@exit
        XCHG     EDX, EAX
        XCHG     EAX, EBX
        CALL     SetHandle
@@exit: POP      EBX
end;
{$ENDIF ASM_UNICODE}

function TBitmap.ReleaseHandle: HBitmap;
asm
        PUSH     EBX
        MOV      EBX, EAX
        XOR      EDX, EDX
        CALL     SetHandleType
        MOV      EAX, EBX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit

        CMP      [EBX].fDIBAutoFree, 0
        JZ       @@1
        MOV      EAX, [EBX].fDIBSize
        PUSH     EAX
        PUSH     EAX
        PUSH     GMEM_FIXED {or GMEM_ZEROINIT}
        CALL     GlobalAlloc
        MOV      EDX, EAX
        XCHG     EAX, [EBX].fDIBBits
        POP      ECX
        CALL     System.Move
@@1:
        XOR      EAX, EAX
        MOV      [EBX].fDIBAutoFree, AL
        XCHG     EAX, [EBX].fHandle

@@exit: POP      EBX
end;

procedure TBitmap.SaveToFile(const Filename: KOLString);
asm
        PUSH     EAX
        PUSH     EDX
        CALL     GetEmpty
        POP      EAX
        JZ       @@exit
        CALL     NewWriteFileStream
        XCHG     EDX, EAX
        POP      EAX
        PUSH     EDX
        CALL     SaveToStream
        POP      EAX
        CALL     TObj.RefDec
        PUSH     EAX
@@exit: POP      EAX
end;

procedure TBitmap.SaveToStream(Strm: PStream);
type  tBFH = TBitmapFileHeader;
      tBIH = TBitmapInfoHeader;
const szBIH = Sizeof( tBIH );
      szBFH = Sizeof( tBFH );
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX
        MOV      ESI, EDX
        CALL     GetEmpty
        JZ       @@exit
        MOV      EAX, ESI
        CALL     TStream.GetPosition
        PUSH     EAX

        MOV      EAX, EBX
        XOR      EDX, EDX // EDX = bmDIB
        CALL     SetHandleType
        XOR      EAX, EAX
        MOV      EDX, [EBX].fDIBHeader
        MOVZX    ECX, [EDX].TBitmapInfoHeader.biBitCount
        CMP      CL, 8
        JG       @@1
        MOV      AL, 4
        SHL      EAX, CL
@@1:
          PUSH     EAX                        // ColorsSize
        LEA      ECX, [EAX + szBFH + szBIH]
        CMP      [EDX].TBitmapInfoHeader.biCompression, 0
        JZ       @@10
        ADD      ECX, 74
@@10:
        PUSH     ECX                        // BFH.bfOffBits
        PUSH     0
        ADD      ECX, [EBX].fDIBSize
        PUSH     ECX
        MOV      CX, $4D42
        PUSH     CX
        XOR      ECX, ECX
        MOV      EDX, ESP
        MOV      CL, szBFH
          PUSH     ECX
        MOV      EAX, ESI
        CALL     TStream.Write
          POP      ECX
        ADD      ESP, szBFH
        XOR      EAX, ECX
          POP      ECX  // ColorsSize
        JNZ      @@ewrite

        MOV      EDX, [EBX].fDIBHeader
        CMP      [EDX].TBitmapInfoHeader.biCompression, 0
        JZ       @@11
        ADD      ECX, 74
@@11:

        ADD      ECX, szBIH
        PUSH     ECX
        MOV      EAX, ESI
        CALL     TStream.Write
        POP      ECX
        XOR      EAX, ECX
        JNZ      @@ewrite

        MOV      ECX, [EBX].fDIBSize
        MOV      EDX, [EBX].fDIBBits
        MOV      EAX, ESI
        PUSH     ECX
        CALL     TStream.Write
        POP      ECX
        XOR      EAX, ECX

@@ewrite:
        POP      EDX
        JZ       @@exit
        XCHG     EAX, ESI
        XOR      ECX, ECX
        CALL     TStream.Seek
@@exit:
        POP      ESI
        POP      EBX
end;

procedure TBitmap.SetHandle(const Value: HBitmap);
const szB = sizeof( tagBitmap );
      szDIB = sizeof( TDIBSection );
      szBIH = sizeof( TBitmapInfoHeader ); // = 40
asm
        PUSH     EBX
        MOV      EBX, EAX
        PUSH     EDX
        CALL     Clear
        POP      ECX
        TEST     ECX, ECX
        JZ       @@exit
        PUSH     ECX
        ADD      ESP, -szDIB

        CALL     WinVer
        CMP      AL, wvNT
        JB       @@ddb

        PUSH     ESP
        PUSH     szDIB
        PUSH     ECX
        CALL     GetObject
        CMP      EAX, szDIB
        JNZ      @@ddb

        MOV      [EBX].fHandleType, 0
        MOV      EAX, [ESP].TDIBSection.dsBm.bmWidth
        MOV      [EBX].fWidth, EAX
        MOV      EDX, [ESP].TDIBSection.dsBm.bmHeight
        MOV      [EBX].fHeight, EDX
        MOVZX    ECX, [ESP].TDIBSection.dsBm.bmBitsPixel
        CALL     PrepareBitmapHeader
        MOV      [EBX].fDIBHeader, EAX
        LEA      EDX, [EAX].TBitmapInfo.bmiColors
        LEA      EAX, [ESP].TDIBSection.dsBitfields
        XOR      ECX, ECX
        MOV      CL, 12
        CALL     System.Move

        MOV      EDX, [ESP].TDIBSection.dsBm.bmBits
        MOV      [EBX].fDIBBits, EDX
        MOV      EDX, [ESP].TDIBSection.dsBmih.biSizeImage
        MOV      [EBX].fDIBSize, EDX
        MOV      [EBX].fDIBAutoFree, 1
        ADD      ESP, szDIB
        POP      [EBX].fHandle
        JMP      @@exit

@@ddb:
        MOV      ECX, [ESP+szDIB]
        PUSH     ESP
        PUSH     szB
        PUSH     ECX
        CALL     GetObject
        POP      EDX
        POP      EDX         // bmWidth
        POP      ECX         // bmHeight
        ADD      ESP, szDIB-12
        TEST     EAX, EAX
        JZ       @@exit
        MOV      [EBX].fWidth, EDX
        MOV      [EBX].fHeight, ECX
        POP      dword ptr [EBX].fHandle
        MOV      [EBX].fHandleType, 1
@@exit: POP      EBX
end;

procedure TBitmap.SetHeight(const Value: Integer);
asm
        CMP      EDX, [EAX].fHeight
        JE       @@exit
        PUSHAD
        XOR      EDX, EDX
        INC      EDX
        CALL     SetHandleType
        POPAD
        MOV      [EAX].fHeight, EDX
        CALL     FormatChanged
@@exit:
end;

procedure TBitmap.SetPixelFormat(Value: TPixelFormat);
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     GetEmpty   //   if Empty then Exit;
        JZ       @@exit     //
        MOV      EAX, EBX   //
        PUSH     EDX
        CALL     GetPixelFormat
        POP      EDX
        CMP      EAX, EDX
        JE       @@exit
        TEST     EDX, EDX
        MOV      EAX, EBX
        JNE      @@2
        POP      EBX
        INC      EDX // EDX = bmDDB
        JMP      SetHandleType
@@2:
        MOV      [EBX].fNewPixelFormat, DL
@@3:
        XOR      EDX, EDX
        CALL     SetHandleType
        XCHG     EAX, EBX
        CMP      EAX, 0
@@exit:
        POP      EBX
        JNE      FormatChanged
end;

function CalcScanLineSize( Header: PBitmapInfoHeader ): Integer;
asm
        MOVZX    EDX, [EAX].TBitmapInfoHeader.biBitCount
        MOV      EAX, [EAX].TBitmapInfoHeader.biWidth
        MUL      EDX
        ADD      EAX, 31
        SHR      EAX, 3
        AND      EAX, -4
end;

procedure FillBmpWithBkColor( Bmp: PBitmap; DC2: HDC; oldWidth, oldHeight: Integer );
asm
        PUSH     EBX
        PUSH     ESI
        XCHG     EAX, EBX
        PUSH     EDX // [EBP-12] = DC2
        PUSH     ECX // [EBP-16] = oldWidth
        MOV      EAX, [EBX].TBitmap.fBkColor
        CALL     Color2RGB
        TEST     EAX, EAX
        JZ       @@exit
        XCHG     ESI, EAX // ESI = Color2RGB( Bmp.fBkColor )
        MOV      EAX, EBX
        CALL     TBitmap.GetHandle
        TEST     EAX, EAX
        JZ       @@exit
        PUSH     EAX //fHandle
        PUSH     dword ptr [EBP-12] //DC2
        CALL     SelectObject
        PUSH     EAX // [EBP-20] = oldBmp
        PUSH     ESI
        CALL     CreateSolidBrush
        XCHG     ESI, EAX // ESI = Br
        PUSH     [EBX].TBitmap.fHeight
        PUSH     [EBX].TBitmap.fWidth
        MOV      EAX, [oldHeight]
        MOV      EDX, [EBP-16] //oldWidth
        CMP      EAX, [EBX].TBitmap.fHeight
        JL       @@fill
        CMP      EDX, [EBX].TBitmap.fWidth
        JGE      @@nofill
@@fill: CMP      EAX, [EBX].TBitmap.fHeight
        JNE      @@1
        XOR      EAX, EAX
@@1:
        CMP      EDX, [EBX].TBitmap.fWidth
        JNZ      @@2
        CDQ
@@2:    PUSH     EAX
        PUSH     EDX

        MOV      EDX, ESP
        PUSH     ESI
        PUSH     EDX
        PUSH     dword ptr [EBP-12] //DC2
        CALL     Windows.FillRect
        POP      ECX
        POP      ECX
@@nofill:
        POP      ECX
        POP      ECX
        PUSH     ESI //Br
        CALL     DeleteObject
        PUSH     dword ptr [EBP-12] //DC2
        CALL     SelectObject
@@exit:
        POP      ECX
        POP      EDX
        POP      ESI
        POP      EBX
end;

procedure TBitmap.FormatChanged;
type  tBIH = TBitmapInfoHeader;
      tBmp = tagBitmap;
const szBIH = Sizeof( tBIH );
      szBmp = Sizeof( tBmp );
asm
        PUSH     EAX
        CALL     GetEmpty
        POP      EAX
        JZ       @@exit
        PUSHAD
        MOV      EBX, EAX
        CALL     [EBX].fDetachCanvas
        XOR      EAX, EAX
        MOV      [EBX].fScanLineSize, EAX
        MOV      [EBX].fGetDIBPixels, EAX
        MOV      [EBX].fSetDIBPixels, EAX
        MOV      ESI, [EBX].fWidth    // ESI := oldWidth
        MOV      EDI, [EBX].fHeight   // EDI := oldHeight
        MOV      ECX, [EBX].fDIBBits
        JECXZ    @@noDIBBits
        MOV      EAX, [EBX].fDIBHeader
        MOV      ESI, [EAX].TBitmapInfo.bmiHeader.biWidth
        MOV      EDI, [EAX].TBitmapInfo.bmiHeader.biHeight
        TEST     EDI, EDI
        JGE      @@1
        NEG      EDI
@@1:    JMP      @@createDC2
@@noDIBBits:
        MOV      ECX, [EBX].fHandle
        JECXZ    @@createDC2
        ADD      ESP, -24 // -szBmp
        PUSH     ESP
        PUSH     24 //szBmp
        PUSH     ECX
        CALL     GetObject
        XCHG     ECX, EAX
        JECXZ    @@2
        MOV      ESI, [ESP].tBmp.bmWidth
        MOV      EDI, [ESP].tBmp.bmHeight
@@2:    ADD      ESP, 24 //szBmp
@@createDC2:
        PUSH     0
        CALL     CreateCompatibleDC
        PUSH     EAX                         // > DC2
        CMP      [EBX].fHandleType, bmDDB
        JNE      @@DIB_handle_type
        PUSH     0
        CALL     GetDC
        PUSH     EAX                         // > DC0
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     EAX
        CALL     CreateCompatibleBitmap
        XCHG     EBP, EAX        // EBP := NewHandle
        PUSH     0
        CALL     ReleaseDC                   // <
        POP      EDX
        PUSH     EDX             // EDX := DC2
        PUSH     EBP
        PUSH     EDX
        CALL     SelectObject
        PUSH     EAX                         // > OldBmp
        PUSH     [EBX].fHeight   // prepare Rect(0,0,fWidth,fHeight)
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        MOV      EAX, [EBX].fBkColor
        CALL     Color2RGB
        PUSH     EAX
        CALL     CreateSolidBrush
        MOV      EDX, ESP
        PUSH     EAX                         // > Br
        PUSH     EAX
        PUSH     EDX
        PUSH     dword ptr [ESP+32] // (DC2)
        CALL     Windows.FillRect
        CALL     DeleteObject                // <
        ADD      ESP, 16            // remove Rect
        MOV      ECX, [EBX].fDIBBits
        JECXZ    @@draw
        PUSH     dword ptr [ESP+4] // (DC2)
        CALL     SelectObject                // < (OldBmp)
        PUSH     DIB_RGB_COLORS    // : DIB_RGB_COLORS
        PUSH     [EBX].fDIBHeader  // : fDIBHeader
        PUSH     [EBX].fDIBBits    // : fDIBBits
        PUSH     [EBX].fHeight     // : fHeight
        PUSH     0                 // : 0
        PUSH     EBP               // : NewHandle
        PUSH     dword ptr [ESP+24] // (DC2)
        CALL     SetDIBits
        JMP      @@clearData
@@draw:
        MOV      EDX, [ESP+4]
        PUSH     EDX           // prepare DC2 for SelectObject
        MOV      EAX, EBX
        XOR      ECX, ECX
        PUSH     ECX
        CALL     Draw
        CALL     SelectObject
@@clearData:
        MOV      EAX, EBX
        CALL     ClearData
        MOV      [EBX].fHandle, EBP

        JMP      @@fillBkColor

@@DIB_handle_type:    // [ESP] = DC2
        MOVZX    EAX, [EBX].fNewPixelFormat
@@getBitsPixel:
        XCHG     ECX, EAX
        MOV      CL, [ECX] + offset BitCounts
        MOVZX    EAX, [DefaultPixelFormat]
        JECXZ    @@getBitsPixel
        XOR      EBP, EBP            // NewHandle := 0
        MOV      EAX, [EBX].fWidth   // EAX := fWidth
        MOV      EDX, [EBX].fHeight  // EDX := fHeight
        CALL     PrepareBitmapHeader
        PUSH     EAX                            // > NewHeader
        CMP      [EBX].fNewPixelFormat, pf16bit
        JNE      @@newHeaderReady
        CALL     PreparePF16bit
@@newHeaderReady:
        POP      EAX
        PUSH     EAX
        CALL     CalcScanLineSize
        MOV      EDX, [EBX].fHeight
        MUL      EDX
        PUSH     EAX                           // > sizeBits

        PUSH     EAX
        PUSH     GMEM_FIXED
        CALL     GlobalAlloc

        PUSH     EAX                           // > NewBits
        PUSH     DIB_RGB_COLORS
        PUSH     dword ptr [ESP+12] // (NewHeader)
        PUSH     EAX
        MOV      EAX, [EBX].fHeight
        CMP      EAX, EDI
        {$IFDEF USE_CMOV}
        CMOVG    EAX, EDI
        {$ELSE}
        JLE      @@3
        MOV      EAX, EDI
@@3:    {$ENDIF}

        PUSH     EAX
        PUSH     0
        MOV      EAX, EBX
        CALL     GetHandle
        PUSH     EAX
        PUSH     dword ptr [ESP+36] // (DC2)
        CALL     GetDIBits

        MOV      EDX, [EBX].fHeight
        CMP      EDX, EDI
        {$IFDEF USE_CMOV}
        CMOVG    EDX, EDI
        {$ELSE}
        JLE      @@30
        MOV      EDX, EDI
@@30:   {$ENDIF}

        CMP      EAX, EDX
        JE       @@2clearData

        CALL     GlobalFree

        XOR      EAX, EAX
        PUSH     EAX

        MOV      EDX, ESP        // EDX = @NewBits
        MOV      ECX, [ESP+8]    // ECX = @NewHeader
        PUSH     EAX             // -> 0
        PUSH     EAX             // -> 0
        PUSH     EDX             // -> @NewBits
        PUSH     DIB_RGB_COLORS  // -> DIB_RGB_COLORS
        PUSH     ECX             // -> @NewHeader
        PUSH     dword ptr [ESP+32] // -> DC2
        CALL     CreateDIBSection

        XOR      ESI, -1 // use OldWidth to store NewDIBAutoFree flag

        XCHG     EBP, EAX        // EBP := NewHandle
        PUSH     EBP
        PUSH     dword ptr [ESP+16] // -> DC2
        CALL     SelectObject
        PUSH     EAX           // save oldBmp
        MOV      EDX, [ESP+16] // DC2 -> EDX (DC)
        XOR      ECX, ECX      // 0   -> ECX (X)
        PUSH     ECX           // 0   -> stack (Y)
        MOV      EAX, EBX
        CALL     TBitmap.Draw
        PUSH     dword ptr [ESP+16] // -> DC2
        CALL     SelectObject

@@2clearData:
        MOV      EAX, EBX
        CALL     ClearData

        POP      [EBX].fDIBBits
        POP      [EBX].fDIBSize
        POP      [EBX].fDIBHeader
        MOV      [EBX].fHandle, EBP

        TEST     ESI, ESI
        MOV      [EBX].fDIBAutoFree, 0
        JGE      @@noDIBautoFree
        INC      [EBX].fDIBAutoFree
@@noDIBautoFree:

@@fillBkColor:
        MOV      ECX, [EBX].fFillWithBkColor
        JECXZ    @@deleteDC2
        POP      EDX // (DC2)
        PUSH     EDX
        PUSH     EDI
        XCHG     ECX, ESI
        XCHG     EAX, EBX
        CALL     ESI
@@deleteDC2:
        CALL     DeleteDC
        POPAD
@@exit:
end;

function TBitmap.GetScanLine(Y: Integer): Pointer;
asm
        MOV      ECX, [EAX].fDIBHeader
        JECXZ    @@exit
        MOV      ECX, [ECX].TBitmapInfoHeader.biHeight
        TEST     ECX, ECX
        JL       @@1

        SUB      ECX, EDX
        DEC      ECX
        MOV      EDX, ECX

@@1:    MOV      ECX, [EAX].fScanLineSize
        INC      ECX
        PUSH     [EAX].fDIBBits
        LOOP     @@2

        PUSH     EDX
        CALL     GetScanLineSize
        POP      EDX
        XCHG     ECX, EAX

@@2:    XCHG     EAX, ECX
        MUL      EDX
        POP      ECX
        ADD      ECX, EAX

@@exit: XCHG     EAX, ECX
end;

function TBitmap.GetScanLineSize: Integer;
asm
        MOV      ECX, [EAX].fDIBHeader
        JECXZ    @@exit

        PUSH     EAX
        XCHG     EAX, ECX
        CALL     CalcScanLineSize
        XCHG     ECX, EAX
        POP      EAX
        MOV      [EAX].fScanLineSize, ECX

@@exit: XCHG     EAX, ECX
end;

procedure TBitmap.CanvasChanged( Sender : PObj );
asm
        PUSH     EAX

          XCHG     EAX, EDX
          CALL     TCanvas.GetBrush
          MOV      EDX, [EAX].TGraphicTool.fData.Color

        POP      EAX
        MOV      [EAX].fBkColor, EAX
        CALL     ClearTransImage
end;

procedure TBitmap.Dormant;
asm
        PUSH     EAX
        CALL     RemoveCanvas
        POP      EAX
        MOV      ECX, [EAX].fHandle
        JECXZ    @@exit
        CALL     ReleaseHandle
        PUSH     EAX
        CALL     DeleteObject
@@exit:
end;

procedure TBitmap.SetBkColor(const Value: TColor);
asm
        CMP      [EAX].fBkColor, EDX
        JE       @@exit
        MOV      [EAX].fBkColor, EDX
        MOV      [EAX].fFillWithBkColor, offset[FillBmpWithBkColor]
        MOV      ECX, [EAX].fApplyBkColor2Canvas
        JECXZ    @@exit
        CALL     ECX
@@exit:
end;

function TBitmap.Assign(SrcBmp: PBitmap): Boolean;
const szBIH = sizeof(TBitmapInfoHeader);
asm
        PUSHAD
        XCHG     EBX, EAX
@@clear:
        MOV      ESI, EDX
        MOV      EAX, EBX
        CALL     Clear
        MOV      EAX, ESI
        OR       EAX, EAX
        JZ       @@exit
        CALL     GetEmpty
        JZ       @@exit
        MOV      EAX, [ESI].fWidth
        MOV      [EBX].fWidth, EAX
        MOV      EAX, [ESI].fHeight
        MOV      [EBX].fHeight, EAX
        MOVZX    ECX, [ESI].fHandleType
        MOV      [EBX].fHandleType, CL
          JECXZ    @@fmtDIB

        DEC      ECX  // ECX = 0
        PUSH     ECX
        PUSH     ECX
        PUSH     ECX
        PUSH     ECX //IMAGE_BITMAP=0
        PUSH     [ESI].fHandle
        CALL     CopyImage
        MOV      [EBX].fHandle, EAX
        TEST     EAX, EAX
        XCHG     EDX, EAX
        JZ       @@clear
        JMP      @@exit

@@fmtDIB:
        XCHG     EAX, ECX
        MOV      AX, szBIH+1024
        PUSH     EAX
        CALL     System.@GetMem
        MOV      [EBX].fDIBHeader, EAX
        XCHG     EDX, EAX
        POP      ECX
        MOV      EAX, [ESI].fDIBHeader
        CALL     System.Move
        MOV      EAX, [ESI].fDIBSize
        MOV      [EBX].fDIBSize, EAX
        PUSH     EAX
        PUSH     EAX
        PUSH     GMEM_FIXED
        CALL     GlobalAlloc
        MOV      [EBX].fDIBBits, EAX
        XCHG     EDX, EAX
        POP      ECX
        MOV      EAX, [ESI].fDIBBits
        CALL     System.Move

        INC      EBX // reset "ZF"

@@exit:
        POPAD
        SETNZ    AL
end;

procedure TBitmap.RemoveCanvas;
asm
        PUSH     EAX
        CALL     [EAX].fDetachCanvas
        POP      EDX
        XOR      EAX, EAX
        XCHG     EAX, [EDX].fCanvas
        CALL     TObj.RefDec
end;

function TBitmap.DIBPalNearestEntry(Color: TColor): Integer;
const szBIH = sizeof(TBitmapInfoHeader);
asm
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        XCHG     ESI, EAX
        XCHG     EAX, EDX
        CALL     Color2RGBQuad
        XCHG     EDI, EAX
        MOV      EAX, ESI
        CALL     GetDIBPalEntryCount
        XCHG     ECX, EAX
        XOR      EAX, EAX
        JECXZ    @@exit

        MOV      ESI, [ESI].fDIBHeader
        ADD      ESI, szBIH
        XOR      EDX, EDX
        PUSH     EDX
        DEC      DX

@@loo:  LODSD
        XOR      EAX, EDI
        MOV      EBX, EAX
        SHR      EBX, 16
        MOV      BH, 0
        ADD      AL, AH
        MOV      AH, 0
        ADC      AX, BX
        CMP      AX, DX
        JAE      @@1
        MOV      DX, AX
        POP      EBX
        PUSH     EDX // save better index (in high order word)
@@1:    ADD      EDX, $10000 // increment index
        LOOP     @@loo

        XCHG     EAX, ECX
        POP      AX
        POP      AX
@@exit:
        POP      EDI
        POP      ESI
        POP      EBX
end;

function TBitmap.GetDIBPalEntries(Idx: Integer): TColor;
const szBIH = sizeof(TBitmapInfoHeader);
asm
        MOV      ECX, [EAX].fDIBHeader
        JECXZ    @@exit

        MOV      ECX, [ECX+szBIH+EDX*4]
        INC      ECX

@@exit: DEC      ECX
        XCHG     EAX, ECX
end;

function TBitmap.GetDIBPalEntryCount: Integer;
asm
        PUSH     EAX
        CALL     GetEmpty
        POP      EAX
        JZ       @@ret0
        CALL     GetPixelFormat
        MOVZX    ECX, AL
        MOV      EAX, ECX
        LOOP     @@1
        // pf1bit:
        INC      EAX
        RET
@@1:
        LOOP     @@2
        // pf4bit:
        MOV      AL, 16
        RET
@@2:
        LOOP     @@ret0
        // pf8bit:
        XOR      EAX, EAX
        INC      AH
        RET
@@ret0:
        XOR      EAX, EAX
end;

procedure TBitmap.ClearTransImage;
asm
        OR       [EAX].fTransColor, -1
        XOR      EDX, EDX
        XCHG     [EAX].fTransMaskBmp, EDX
        XCHG     EAX, EDX
        CALL     TObj.RefDec
end;

{$IFDEF USE_OLDCONVERT2MASK}
procedure TBitmap.Convert2Mask(TranspColor: TColor);
asm
        PUSH     EBX
        PUSH     ESI
        MOV      EBX, EAX
        MOV      ESI, EDX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit

        PUSH     0
        PUSH     1
        PUSH     1
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        CALL     CreateBitmap
        PUSH     EAX                // MonoHandle
        PUSH     0
        CALL     CreateCompatibleDC
        POP      EDX
        PUSH     EDX
        PUSH     EAX                // MonoDC

        PUSH     EDX
        PUSH     EAX
        CALL     SelectObject
        PUSH     EAX                // SaveMono

        CALL     StartDC            // DCfrom, SaveFrom
        XCHG     EAX, ESI
        CALL     Color2RGB
        PUSH     EAX // Color2RGB(TranspColor)
        PUSH     dword ptr [ESP+8] //DCfrom
        CALL     Windows.SetBkColor
        PUSH     EAX                // SaveBkColor

        PUSH     SRCCOPY
        PUSH     0
        PUSH     0
        PUSH     dword ptr [ESP+12+4+4] //DCfrom
        PUSH     [EBX].fHeight
        PUSH     [EBX].fWidth
        PUSH     0
        PUSH     0
        PUSH     dword ptr [ESP+32+16] //MonoDC
        CALL     BitBlt

        PUSH     dword ptr [ESP+8] //DCfrom
        CALL     Windows.SetBkColor // ESP-> SaveFrom
        CALL     FinishDC           // ESP-> SaveMono
        CALL     FinishDC           // ESP-> MonoHandle

        MOV      EAX, EBX
        CALL     ClearData
        POP      [EBX].fHandle
        MOV      [EBX].fHandleType, bmDDB
@@exit:
        POP      ESI
        POP      EBX
end;
{$ELSE USE_OLDCONVERT2MASK} //Pascal
procedure TBitmap.Convert2Mask(TranspColor: TColor);
asm
        PUSH EBX
        PUSH ESI
        PUSH EBP
        PUSH EDI
        XCHG EBP, EAX          // EBP = @ Self
        XCHG EAX, EDX          // EAX = TranspColor
        CALL Color2RGB
        XCHG EBX, EAX          // EBX := Color2RGB( TranspColor );
        MOV  EAX, EBP          // EAX := @ Self;
        CALL GetPixelFormat
        CMP  AL, pf15bit
        JB   @@SwapRB
        CMP  AL, pf24bit
        JB   @@noSwapRB
@@SwapRB:
        BSWAP EBX
        SHR   EBX, 8
@@noSwapRB:
        MOV  DL, pf4bit
        CMP  AL, DL
        JB   @@setpixelformat
@@1:    MOV  DL, pf32bit
        CMP  AL, DL
        JBE  @@translate
@@setpixelformat:
        MOV  EAX, EBP
        CALL SetPixelFormat
@@translate:
        MOV  EAX, [EBP].fWidth
        MOV  EDX, [EBP].fHeight
        MOV  CL, pf1bit
        CALL NewDibBitmap
        PUSH EAX
        XOR  EDX, EDX
        INC  EDX
        MOV  ECX, $FFFFFF
        CALL SetDIBPalEntries
        XOR  EDX, EDX
@@Yloop:CMP  EDX, [EBP].fHeight
        JGE  @@exit
        PUSH EDX
        MOV  EAX, EBP
        CALL GetScanLine
        XCHG ESI, EAX
        MOV  EAX, [ESP+4]
        POP  EDX
        PUSH EDX
        CALL GetScanLine
        XCHG EDI, EAX
        MOV  EAX, EBP
        CALL GetPixelFormat
        MOVZX ECX, AL
        SUB  ECX, pf4bit
        MOV  DL, 8
        JNE  @@chk_pf8bit
        //-------- pf4bit:
        CMP  dword ptr [ESP], 0
        JNZ  @@4_0
        XOR  EDX, EDX
@@4_searchentry:
        PUSH EDX
        MOV  EAX, EBP //[ESP+8]
        CALL GetDIBPalEntries
        CMP  EAX, EBX
        POP  EDX
        JZ   @@4_foundentry
        INC  EDX
        CMP  EDX, 16
        JB   @@4_searchentry
@@4_foundentry:
        XCHG EBX, EDX
        MOV  DL, 8
@@4_0:  MOV  ECX, [EBP].fWidth
        INC  ECX
        SHR  ECX, 1
@@Xloop_pf4bit:
        MOV  AH, [ESI]
        SHR  AH, 4
        CMP  AH, BL
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        MOV  AH, [ESI]
        AND  AH, $0F
        CMP  AH, BL
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        DEC  DL
        JNZ  @@4_1
        STOSB
        MOV  DL, 8
@@4_1: INC  ESI
        LOOP @@Xloop_pf4bit
        JMP  @@nextline
@@chk_pf8bit:
        LOOP @@chk_pf15bit
        //-------- pf4bit:
        CMP  dword ptr [ESP], 0
        JNZ  @@8_0
        XOR  EDX, EDX
@@8_searchentry:
        PUSH EDX
        MOV  EAX, EBP //[ESP+8]
        CALL GetDIBPalEntries
        CMP  EAX, EBX
        POP  EDX
        JZ   @@8_foundentry
        INC  DL
        JNZ  @@8_searchentry
@@8_foundentry:
        XCHG EBX, EDX
        MOV  DL, 8
@@8_0:  MOV  ECX, [EBP].fWidth
        INC  ECX
@@Xloop_pf8bit:
        CMP  BL, [ESI]
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        JNZ  @@8_1
        STOSB
        MOV  DL, 8
@@8_1:  INC  ESI
        LOOP @@Xloop_pf8bit
        JMP  @@nextline
@@chk_pf15bit:
        LOOP @@chk_pf16bit
        //-------- pf15bit:
        CMP  dword ptr [ESP], 0
        JNZ  @@15_0
        XCHG EAX, EBX
        PUSH EDX
        CALL Color2Color15
        POP  EDX
        XCHG EBX, EAX
@@15_0: MOV  ECX, [EBP].fWidth
@@Xloop_pf15bit:
        CMP  word ptr [ESI], BX
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        JNZ  @@15_1
        STOSB
        MOV  DL, 8
@@15_1: ADD  ESI, 2
        LOOP @@Xloop_pf15bit
        JMP  @@nextline
@@chk_pf16bit:
        LOOP @@chk_pf24bit
        //-------- pf16bit:
        CMP  dword ptr [ESP], 0
        JNZ  @@16_0
        XCHG EAX, EBX
        PUSH EDX
        CALL Color2Color16
        POP  EDX
        XCHG EBX, EAX
@@16_0: MOV  ECX, [EBP].fWidth
@@Xloop_pf16bit:
        CMP  word ptr [ESI], BX
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        JNZ  @@16_1
        STOSB
        MOV  DL, 8
@@16_1: ADD  ESI, 2
        LOOP @@Xloop_pf16bit
        JMP  @@nextline
@@chk_pf24bit:
        LOOP @@chk_pf32bit
        //-------- pf24bit:
        MOV  ECX, [EBP].fWidth
        PUSH EBP
        //AND  EBX, $FFFFFF
@@Xloop_pf24bit:
        MOV  EBP, dword ptr [ESI]
        AND  EBP, $FFFFFF
        CMP  EBP, EBX
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        JNZ  @@24_1
        STOSB
        MOV  DL, 8
@@24_1: ADD  ESI, 3
        LOOP @@Xloop_pf24bit
        POP  EBP
        JMP  @@nextline
@@chk_pf32bit:
        //-------- pf32bit:
        MOV  ECX, [EBP].fWidth
@@Xloop_pf32bit:
        and  dword ptr [ESI], $FFFFFF
        CMP  EBX, dword ptr [ESI]
        SETZ AH
        SHL  AL, 1
        OR   AL, AH
        DEC  DL
        JNZ  @@32_1
        STOSB
        MOV  DL, 8
@@32_1: ADD  ESI, 4
        LOOP @@Xloop_pf32bit
@@nextline:
        TEST DL, DL
        JZ   @@nx1
        CMP  DL, 8
        JE   @@nx1
@@finloop1:
        SHL  AL, 1
        DEC  DL
        JNZ  @@finloop1
        STOSB
@@nx1:
        POP  EDX
        INC  EDX
        JMP  @@Yloop
@@exit:
        POP  EDX
        PUSH EDX
        XCHG EAX, EBP
        CALL Assign
        POP  EAX
        CALL TObj.RefDec
        POP  EDI
        POP  EBP
        POP  ESI
        POP  EBX
end;
{$ENDIF USE_OLDCONVERT2MASK} //Pascal

procedure _PrepareBmp2Rotate;
const szBIH = sizeof(TBitmapInfoHeader);
asm
        { <- BL = increment to height }
        XCHG     EDI, EAX
        MOV      ESI, EDX // ESI = SrcBmp

        XCHG     EAX, EDX
        CALL     TBitmap.GetPixelFormat
        MOVZX    ECX, AL
        PUSH     ECX

        MOV      EDX, [ESI].TBitmap.fWidth
        MOVZX    EBX, BL
        ADD      EDX, EBX

        MOV      EAX, [ESI].TBitmap.fHeight
        CALL     NewDIBBitmap
        STOSD
        XCHG     EDI, EAX

        MOV      EAX, [ESI].TBitmap.fDIBHeader
        ADD      EAX, szBIH
        MOV      EDX, [EDI].TBitmap.fDIBHeader
        ADD      EDX, szBIH
        XOR      ECX, ECX
        MOV      CH, 4
        CALL     System.Move

        MOV      EAX, EDI
        XOR      EDX, EDX
        CALL     TBitmap.GetScanLine
        MOV      EBX, [EDI].TBitmap.fWidth
        DEC      EBX // EBX = DstBmp.fWidth - 1
        XCHG     EDI, EAX // EDI = DstBmp.ScanLine[ 0 ]

        XOR      EDX, EDX
        INC      EDX
        CALL     TBitmap.GetScanLine
        XCHG     EDX, EAX
        SUB      EDX, EDI // EDX = BytesPerDstLine

        MOV      EBP, [ESI].TBitmap.fWidth
        DEC      EBP // EBP = SrcBmp.fWidth - 1

        POP      ECX // ECX = PixelFormat
end;
procedure _RotateBitmapMono( var DstBmp: PBitmap; SrcBmp: PBitmap );
const szBIH = sizeof(TBitmapInfoHeader);
asm
        PUSHAD
        MOV      BL, 7
        CALL     _PrepareBmp2Rotate

        SHR      EBP, 3
        SHL      EBP, 8 // EBP = (WBytes-1) * 256

        MOV      ECX, EBX // ECX and 7 = Shf
        SHR      EBX, 3
        ADD      EDI, EBX // EDI = Dst

        XOR      EBX, EBX // EBX = temp mask
        XOR      EAX, EAX // Y = 0
@@looY:
        PUSH     EAX
        PUSH     EDI // Dst1 = Dst (Dst1 in EDI, Dst saved)
        PUSH     ESI // SrcBmp

        PUSH     EDX //BytesPerDstLine
        PUSH     ECX //Shf

        XCHG     EDX, EAX
        XCHG     EAX, ESI
        CALL     TBitmap.GetScanLine
        XCHG     ESI, EAX // ESI = Src

        POP      ECX // CL = Shf
        AND      ECX, 7 // ECX = Shf
        OR       ECX, EBP // ECX = (Wbytes-1)*8 + Shf
        POP      EDX // EDX = BytesPerDstLine

        MOV      BH, $80
        SHR      EBX, CL // BH = mask, BL = mask & Tmp
@@looX:
        XOR      EAX, EAX

        LODSB

        MOV      AH, AL
        SHR      EAX, CL
        OR       EAX,$01000000

@@looBits:
        MOV      BL, AH
        AND      BL, BH
        OR       [EDI], BL
        ADD      EDI, EDX
        ADD      EAX, EAX
        JNC      @@looBits

        SUB      ECX, 256
        JGE      @@looX

        POP      ESI // ESI = SrcBmp
        POP      EDI // EDI = Dst
        POP      EAX // EAX = Y

        ADD      ECX, 256-1
        JGE      @@1
        DEC      EDI
@@1:
        INC      EAX
        CMP      EAX, [ESI].TBitmap.fHeight
        JL       @@looY

        POPAD
end;

procedure _RotateBitmap4bit( var DstBmp: PBitmap; SrcBmp: PBitmap );
const szBIH = sizeof(TBitmapInfoHeader);
asm
        PUSHAD
        MOV      BL, 1
        CALL     _PrepareBmp2Rotate

        SHR      EBP, 1 // EBP = WBytes - 1
        SHL      EBP, 8 // EBP = (WBytes - 1) * 256

        // EBX = DstBmp.fWidth - 1
        MOV      ECX, EBX
        SHL      ECX, 2 // ECX and 7 = Shf (0 or 4)
        SHR      EBX, 1
        ADD      EDI, EBX // EDI = Dst

        XOR      EAX, EAX // Y = 0
        XOR      EBX, EBX

@@looY:
        PUSH     EAX // save Y
        PUSH     EDI // Dst1 = Dst (Dst1 in EDI, Dst saved)
        PUSH     ESI // SrcBmp

        PUSH     EDX // BytesPerDstLine
        PUSH     ECX // Shf

        XCHG     EDX, EAX
        XCHG     EAX, ESI
        CALL     TBitmap.GetScanLine
        XCHG     ESI, EAX // ESI = Src

        POP      ECX
        AND      ECX, 7 // CL = Shf
        OR       ECX, EBP // ECX = (WBytes-1)*256 + Shf
        POP      EDX // EDX = BytesPerDstLine

        MOV      BH, $F0
        SHR      EBX, CL // shift mask right 4 or 0

@@looX:
        XOR      EAX, EAX
        LODSB
        MOV      AH, AL
        SHR      EAX, CL

        MOV      BL, AH
        AND      BL, BH
        OR       [EDI], BL
        ADD      EDI, EDX

        SHL      EAX, 4
        AND      AH, BH
        OR       [EDI], AH
        ADD      EDI, EDX

        SUB      ECX, 256
        JGE      @@looX

        POP      ESI // ESI = SrcBmp
        POP      EDI // EDI = Dst
        POP      EAX // EAX = Y

        ADD      ECX, 256 - 4
        JGE      @@1

        DEC      EDI
@@1:
        INC      EAX
        CMP      EAX, [ESI].TBitmap.fHeight
        JL       @@looY

        POPAD
end;

procedure _RotateBitmap8bit( var DstBmp: PBitmap; SrcBmp: PBitmap );
const szBIH = sizeof(TBitmapInfoHeader);
asm
        PUSHAD
        XOR      EBX, EBX
        CALL     _PrepareBmp2Rotate

        ADD      EDI, EBX // EDI = Dst

        MOV      EBX, EDX // EBX = BytesPerDstLine
        DEC      EBX
        MOV      EBP, ESI // EBP = SrcBmp

        XOR      EDX, EDX // Y = 0

@@looY:
        PUSH     EDX
        PUSH     EDI

        MOV      EAX, EBP
        CALL     TBitmap.GetScanLine
        XCHG     ESI, EAX
        MOV      ECX, [EBP].TBitmap.fWidth

@@looX:
        MOVSB
        ADD      EDI, EBX
        LOOP     @@looX

        POP      EDI
        POP      EDX

        DEC      EDI
        INC      EDX
        CMP      EDX, [EBP].TBitmap.fHeight
        JL       @@looY

        POPAD
end;

procedure _RotateBitmap16bit( var DstBmp: PBitmap; SrcBmp: PBitmap );
asm
        PUSHAD
        XOR      EBX, EBX
        CALL     _PrepareBmp2Rotate

        ADD      EBX, EBX
        ADD      EDI, EBX // EDI = Dst
        MOV      EBX, EDX // EBX = BytesPerDstLine
        DEC      EBX
        DEC      EBX
        MOV      EBP, ESI // EBP = SrcBmp

        XOR      EDX, EDX // Y = 0

@@looY:
        PUSH     EDX
        PUSH     EDI

        MOV      EAX, EBP
        CALL     TBitmap.GetScanLine
        XCHG     ESI, EAX
        MOV      ECX, [EBP].TBitmap.fWidth

@@looX:
        MOVSW
        ADD      EDI, EBX
        LOOP     @@looX

        POP      EDI
        POP      EDX

        DEC      EDI
        DEC      EDI
        INC      EDX
        CMP      EDX, [EBP].TBitmap.fHeight
        JL       @@looY

        POPAD
end;

procedure _RotateBitmap2432bit( var DstBmp: PBitmap; SrcBmp: PBitmap );
asm
        PUSHAD
        XOR      EBX, EBX
        CALL     _PrepareBmp2Rotate

        SUB      ECX, pf24bit
        JNZ      @@10
        LEA      EBX, [EBX+EBX*2]
        JMP      @@11
@@10:
        LEA      EBX, [EBX*4]
@@11:   ADD      EDI, EBX // EDI = Dst

        MOV      EBX, EDX // EBX = BytesPerDstLine
        DEC      EBX
        DEC      EBX
        DEC      EBX

        MOV      EBP, ESI // EBP = SrcBmp

        XOR      EDX, EDX // Y = 0

@@looY:
        PUSH     EDX
        PUSH     EDI
        PUSH     ECX // ECX = 0 if pf24bit (1 if pf32bit)

        MOV      EAX, EBP
        CALL     TBitmap.GetScanLine
        XCHG     ESI, EAX
        MOV      ECX, [EBP].TBitmap.fWidth
        POP      EAX
        PUSH     EAX

@@looX:
        MOVSW
        MOVSB
        ADD      ESI, EAX
        ADD      EDI, EBX
        LOOP     @@looX

        POP      ECX
        POP      EDI
        POP      EDX

        DEC      EDI
        DEC      EDI
        DEC      EDI
        SUB      EDI, ECX
        INC      EDX
        CMP      EDX, [EBP].TBitmap.fHeight
        JL       @@looY

        POPAD
end;

procedure _RotateBitmapRight( SrcBmp: PBitmap );
asm
        PUSH     EBX
        PUSH     EDI
        MOV      EBX, EAX
        CMP      [EBX].TBitmap.fHandleType, bmDIB
        JNZ      @@exit

        CALL     TBitmap.GetPixelFormat
        MOVZX    ECX, AL
        LOOP     @@not1bit
        MOV      EAX, [RotateProcs.proc_RotateBitmapMono]
@@not1bit:
        LOOP     @@not4bit
        MOV      EAX, [RotateProcs.proc_RotateBitmap4bit]
@@not4bit:
        LOOP     @@not8bit
        MOV      EAX, [RotateProcs.proc_RotateBitmap8bit]
@@not8bit:
        LOOP     @@not15bit
        INC      ECX
@@not15bit:
        LOOP     @@not16bit
        MOV      EAX, [RotateProcs.proc_RotateBitmap16bit]
@@not16bit:
        LOOP     @@not24bit
        INC      ECX
@@not24bit:
        LOOP     @@not32bit
        MOV      EAX, [RotateProcs.proc_RotateBitmap2432bit]
@@not32bit:
        TEST     EAX, EAX
        JZ       @@exit

        PUSH     ECX
        XCHG     ECX, EAX
        MOV      EAX, ESP
        MOV      EDX, EBX
        CALL     ECX

        POP      EDI
        MOV      EAX, [EBX].TBitmap.fWidth
        CMP      EAX, [EDI].TBitmap.fHeight
        JGE      @@noCutHeight

        MOV      EDX, [EDI].TBitmap.fScanLineSize
        MUL      EDX
        MOV      [EDI].TBitmap.fDIBSize, EAX

        MOV      EDX, [EDI].TBitmap.fDIBHeader
        MOV      EDX, [EDX].TBitmapInfoHeader.biHeight
        TEST     EDX, EDX
        JL       @@noCorrectImg

        PUSH     EAX

        MOV      EDX, [EDI].TBitmap.fHeight
        DEC      EDX
        MOV      EAX, EDI
        CALL     TBitmap.GetScanLine
        PUSH     EAX

        MOV      EDX, [EBX].TBitmap.fWidth
        DEC      EDX
        MOV      EAX, EDI
        CALL     TBitmap.GetScanLine
        POP      EDX

        POP      ECX
        CALL     System.Move

@@noCorrectImg:
        MOV      EAX, [EBX].TBitmap.fWidth
        MOV      [EDI].TBitmap.fHeight, EAX
        MOV      EDX, [EDI].TBitmap.fDIBHeader
        MOV      [EDX].TBitmapInfoHeader.biHeight, EAX

@@noCutHeight:
        MOV      EAX, EBX
        CALL     TBitmap.ClearData

        XOR      EAX, EAX
        XCHG     EAX, [EDI].TBitmap.fDIBHeader
        XCHG     [EBX].TBitmap.fDIBHeader, EAX

        XCHG     EAX, [EDI].TBitmap.fDIBBits
        XCHG     [EBX].TBitmap.fDIBBits, EAX

        MOV      AL, [EDI].TBitmap.fDIBAutoFree
        MOV      [EBX].TBitmap.fDIBAutoFree, AL

        MOV      EAX, [EDI].TBitmap.fDIBSize
        MOV      [EBX].TBitmap.fDIBSize, EAX

        MOV      EAX, [EDI].TBitmap.fWidth
        MOV      [EBX].TBitmap.fWidth, EAX

        MOV      EAX, [EDI].TBitmap.fHeight
        MOV      [EBX].TBitmap.fHeight, EAX

        XCHG     EAX, EDI
        CALL     TObj.RefDec
@@exit:
        POP      EDI
        POP      EBX
end;

function TBitmap.GetPixels(X, Y: Integer): TColor;
asm
        PUSH     EBX
        MOV      EBX, EAX
        PUSH     ECX
        PUSH     EDX
        CALL     GetEmpty
        PUSHFD
        OR       EAX, -1
        POPFD
        JZ       @@exit

        CALL     StartDC
        PUSH     dword ptr [ESP+12]
        PUSH     dword ptr [ESP+12]
        PUSH     EAX
        CALL     Windows.GetPixel
        XCHG     EBX, EAX
        CALL     FinishDC
        XCHG     EAX, EBX
@@exit:
        POP      EDX
        POP      EDX
        POP      EBX
end;

procedure TBitmap.SetPixels(X, Y: Integer; const Value: TColor);
asm
        PUSH     EBX
        MOV      EBX, EAX
        PUSH     ECX
        PUSH     EDX
        CALL     GetEmpty
        JZ       @@exit

        CALL     StartDC
        MOV      EAX, Value
        CALL     Color2RGB
        PUSH     EAX
        PUSH     dword ptr [ESP+16]
        PUSH     dword ptr [ESP+16]
        PUSH     dword ptr [ESP+16]
        CALL     Windows.SetPixel
        CALL     FinishDC
@@exit:
        POP      EDX
        POP      ECX
        POP      EBX
end;

function _GetDIBPixelsPalIdx( Bmp: PBitmap; X, Y: Integer ): TColor;
const szBIH = Sizeof(TBitmapInfoHeader);
asm
        PUSH     EBX
        PUSH     EDI
        PUSH     EDX
        XCHG     EBX, EAX

        XCHG     EAX, EDX
        MOV      EDI, [EBX].TBitmap.fPixelsPerByteMask
        INC      EDI
        CDQ
        DIV      EDI
        DEC      EDI
        XCHG     ECX, EAX // EAX = Y, ECX = X div (Bmp.fPixeldPerByteMask+1)

        MOV      EDX, [EBX].TBitmap.fScanLineDelta
        IMUL     EDX

        ADD      EAX, [EBX].TBitmap.fScanLine0
        MOVZX    EAX, byte ptr[EAX+ECX]

        POP      EDX
        MOV      ECX, [EBX].TBitmap.fPixelsPerByteMask
        AND      EDX, ECX
        SUB      ECX, EDX

        PUSH     EAX
        MOV      EDI, [EBX].TBitmap.fDIBHeader
        MOVZX    EAX, [EDI].TBitmapInfoHeader.biBitCount
        MUL      ECX
        XCHG     ECX, EAX
        POP      EAX
        SHR      EAX, CL
        AND      EAX, [EBX].TBitmap.fPixelMask

        MOV      EAX, [EDI+szBIH+EAX*4]
        CALL     Color2RGBQuad

        POP      EDI
        POP      EBX
end;

function _GetDIBPixels16bit( Bmp: PBitmap; X, Y: Integer ): TColor;
asm
        PUSH     [EAX].TBitmap.fPixelMask
        PUSH     EDX // X
        PUSH     EAX
        MOV      EAX, [EAX].TBitmap.fScanLineDelta
        IMUL     ECX
        POP      EDX
        ADD      EAX, [EDX].TBitmap.fScanLine0
        POP      ECX
        MOVZX    EAX, word ptr [EAX+ECX*2]
        POP      EDX
        CMP      DL, 15
        JNE      @@16bit

        MOV      EDX, EAX
        SHR      EDX, 7
        SHL      EAX, 6
        MOV      DH, AH
        AND      DH, $F8
        SHL      EAX, 13
        JMP      @@1516bit

@@16bit:
        MOV      DL, AH
        SHL      EAX, 5
        MOV      DH, AH
        SHL      EAX, 14
@@1516bit:
        AND      EAX, $F80000
        OR       EAX, EDX
        AND      AX, $FCF8
end;

function _GetDIBPixelsTrueColor( Bmp: PBitmap; X, Y: Integer ): TColor;
asm
        PUSH     EBX
        XCHG     EBX, EAX
        PUSH     EDX
        MOV      EAX, [EBX].TBitmap.fScanLineDelta
        IMUL     ECX
        XCHG     ECX, EAX
        POP      EDX
        MOV      EAX, [EBX].TBitmap.fBytesPerPixel
        MUL      EDX
        ADD      EAX, [EBX].TBitmap.fScanLine0
        MOV      EAX, [EAX+ECX]
        AND      EAX, $FFFFFF
        CALL     Color2RGBQuad
        POP      EBX
end;

function TBitmap.GetDIBPixels(X, Y: Integer): TColor;
asm
        CMP      word ptr [EAX].fGetDIBPixels+2, 0
        JNZ      @@assigned

        // if not assigned, this preparing will be performed for first call:
        CMP      [EAX].fHandleType, bmDDB
        JZ       @@GetPixels

        PUSHAD
        MOV      EBX, EAX
        XOR      EDX, EDX
        CALL     GetScanLine
        MOV      [EBX].fScanLine0, EAX
        XOR      EDX, EDX
        INC      EDX
        MOV      EAX, EBX
        CALL     GetScanLine
        SUB      EAX, [EBX].fScanLine0
        MOV      [EBX].fScanLineDelta, EAX
        MOV      EAX, EBX
        CALL     GetPixelFormat
        MOVZX    ECX, AL
        MOV      DX, $0F00
        MOV      byte ptr [EBX].fBytesPerPixel, 4
        XOR      EAX, EAX
        LOOP     @@if4bit
        MOV      DX, $0107
        JMP      @@1bit4bit8bit
@@if4bit:
        LOOP     @@if8bit
        INC      EDX // MOV      DX, $0F01
        JMP      @@1bit4bit8bit
@@if8bit:
        LOOP     @@if15bit
        MOV      DH, $FF //MOV      DX, $FF00
@@1bit4bit8bit:
        MOV      EAX, offset[_GetDIBPixelsPalIdx]
@@if15bit:
        LOOP     @@if16bit
        //MOV      DH, $0F
        DEC      DH
        INC      ECX
@@if16bit:
        LOOP     @@if24bit
        INC      DH
        MOV      EAX, offset[_GetDIBPixels16bit]
@@if24bit:
        LOOP     @@if32bit
        DEC      [EBX].fBytesPerPixel
        INC      ECX
        DEC      EDX
@@if32bit:
        LOOP     @@iffin
        INC      EDX
        MOV      EAX, offset[_GetDIBPixelsTrueColor]
@@iffin:
        MOV      byte ptr [EBX].fPixelMask, DH
        MOV      byte ptr [EBX].fPixelsPerByteMask, DL
        MOV      [EBX].fGetDIBPixels, EAX
        TEST     EAX, EAX
        POPAD
@@GetPixels:
        JZ       GetPixels

@@assigned:
        JMP      [EAX].fGetDIBPixels
end;

procedure _SetDIBPixels1bit( Bmp: PBitmap; X, Y: Integer; Value: TColor );
asm
        PUSH     EDX
        PUSH     [EAX].TBitmap.fScanLine0
        PUSH     ECX
        PUSH     [EAX].TBitmap.fScanLineDelta
        MOV      EAX, Value
        CALL     Color2RGB
        MOV      EDX, EAX
        SHR      EAX, 16
        ADD      AL, DL
        ADC      AL, DH
        CMP      EAX, 170
        SETGE    CL
        AND      ECX, 1
        SHL      ECX, 7
        POP      EAX
        POP      EDX
        IMUL     EDX
        POP      EDX
        ADD      EAX, EDX
        POP      EDX
        PUSH     ECX
        MOV      ECX, EDX
        SHR      EDX, 3
        ADD      EAX, EDX
        AND      ECX, 7
        MOV      DX, $FF7F
        SHR      EDX, CL
        AND      byte ptr [EAX], DL
        POP      EDX
        SHR      EDX, CL
        OR       byte ptr [EAX], DL
end;

procedure _SetDIBPixelsPalIdx( Bmp: PBitmap; X, Y: Integer; Value: TColor );
asm
        XCHG     EAX, EBP
        PUSH     EDX // -> X
        PUSH     ECX // -> Y
        MOV      ECX, [EBP].TBitmap.fPixelsPerByteMask
        INC      ECX
        XCHG     EAX, EDX
        CDQ
        DIV      ECX
        XCHG     ECX, EAX // ECX = X div (fPixelsPerByteMask+1)
        POP      EAX // <- Y
        MOV      EDX, [EBP].TBitmap.fScanLineDelta
        IMUL     EDX
        ADD      ECX, EAX
        ADD      ECX, [EBP].TBitmap.fScanLine0 // ECX = Pos
        PUSH     ECX // -> Pos

        MOV      EDX, [ESP+16] // Value
        MOV      EAX, EBP
        CALL     TBitmap.DIBPalNearestEntry // EAX = Pixel

        POP      ECX // <- Pos
        POP      EDX // <- X

        PUSH     EAX // -> Pixel

        MOV      EAX, [EBP].TBitmap.fPixelsPerByteMask
        AND      EDX, EAX
        SUB      EAX, EDX
        MOV      EDX, [EBP].TBitmap.fDIBHeader
        MOVZX    EDX, [EDX].TBitmapInfoHeader.biBitCount
        MUL      EDX // EAX = Shf

        XCHG     ECX, EAX // ECX = Shf, EAX = Pos
        MOV      EDX, [EBP].TBitmap.fPixelMask
        SHL      EDX, CL
        NOT      EDX
        AND      byte ptr [EAX], DL

        POP      EDX // <- Pixel
        SHL      EDX, CL
        OR       byte ptr [EAX], DL
end;

procedure _SetDIBPixels16bit( Bmp: PBitmap; X, Y: Integer; Value: TColor );
asm
        ADD      EDX, EDX
        ADD      EDX, [EAX].TBitmap.fScanLine0
        PUSH     EDX // -> X*2 + Bmp.fScanLine0
        PUSH     [EAX].TBitmap.fPixelMask
        MOV      EAX, [EAX].TBitmap.fScanLineDelta
        IMUL     ECX
        PUSH     EAX  // -> Y* Bmp.fScanLineDelta
        MOV      EAX, Value
        CALL     Color2RGB
        POP      EBP  // <- Y* Bmp.fScanLineDelta
        POP      EDX
        XOR      ECX, ECX
        SUB      DL, 16
        JZ       @@16bit

        MOV      CH, AL
        SHR      CH, 1
        SHR      EAX, 6
        MOV      EDX, EAX
        AND      DX, $3E0
        SHR      EAX, 13
        JMP      @@1516

@@16bit:
        {$IFDEF PARANOIA} DB $24, $F8 {$ELSE} AND AL, $F8 {$ENDIF}
        MOV      CH, AL
        SHR      EAX, 5
        MOV      EDX, EAX
        AND      DX, $7E0
        SHR      EAX, 14

@@1516:
        MOV      AH, CH
        AND      AX, $FC1F
        OR       AX, DX

        POP      EDX
        MOV      [EBP+EDX], AX
end;

procedure _SetDIBPixelsTrueColor( Bmp: PBitmap; X, Y: Integer; Value: TColor );
asm
        PUSH     [EAX].TBitmap.fScanLineDelta
        PUSH     [EAX].TBitmap.fScanLine0
        MOV      EAX, [EAX].TBitmap.fBytesPerPixel
        MUL      EDX
        POP      EDX
        ADD      EDX, EAX
        POP      EAX
        PUSH     EDX
        IMUL     ECX
        POP      EDX
        ADD      EDX, EAX
        PUSH     EDX
        MOV      EAX, Value
        CALL     Color2RGBQuad
        POP      EDX
        AND      dword ptr [EDX], $FF000000
        OR       [EDX], EAX
end;

procedure TBitmap.SetDIBPixels(X, Y: Integer; const Value: TColor);
asm
        CMP      word ptr [EAX].fSetDIBPixels+2, 0
        JNZ      @@assigned
        PUSHAD
        MOV      EBX, EAX
        XOR      EDX, EDX
        CMP      [EBX].fHandleType, DL // bmDIB = 0
        JNE      @@ddb
        CALL     GetScanLine
        MOV      [EBX].fScanLine0, EAX
        XOR      EDX, EDX
        INC      EDX
        MOV      EAX, EBX
        CALL     GetScanLine
        SUB      EAX, [EBX].fScanLine0
        MOV      [EBX].fScanLineDelta, EAX
        MOV      EAX, EBX
        CALL     GetPixelFormat
        MOVZX    ECX, AL
        MOV      DX, $0F01
        MOV      EAX, offset[_SetDIBPixelsPalIdx]
        MOV      byte ptr [EBX].fBytesPerPixel, 4
        LOOP     @@if4bit
        MOV      EAX, offset[_SetDIBPixels1bit]
@@if4bit:
        LOOP     @@if8bit
@@if8bit:
        LOOP     @@if15bit
        DEC      DL
        MOV      DH, $FF
@@if15bit:
        LOOP     @@if16bit
        DEC      DH
        INC      ECX
@@if16bit:
        LOOP     @@if24bit
        INC      DH
        MOV      EAX, offset[_SetDIBPixels16bit]
@@if24bit:
        LOOP     @@if32bit
        DEC      EDX
        DEC      [EBX].fBytesPerPixel
        INC      ECX
@@if32bit:
        LOOP     @@ifend
        INC      EDX
        MOV      EAX, offset[_SetDIBPixelsTrueColor]
@@ifend:
        MOV      byte ptr [EBX].fPixelMask, DH
        MOV      byte ptr [EBX].fPixelsPerByteMask, DL
        MOV      [EBX].fSetDIBPixels, EAX
        TEST     EAX, EAX
@@ddb:
        POPAD
        JNZ      @@assigned
        PUSH     Value
        CALL     SetPixels
        JMP      @@exit
@@assigned:
        PUSH     Value
        CALL     [EAX].fSetDIBPixels
@@exit:
end;

procedure TBitmap.FlipVertical;
asm
        PUSH     EBX
        MOV      EBX, EAX
        MOV      ECX, [EBX].fHandle
        JECXZ    @@noHandle

        CALL     StartDC
        PUSH     SrcCopy
        MOV      EDX, [EBX].fHeight
        PUSH     EDX
        MOV      ECX, [EBX].fWidth
        PUSH     ECX
        PUSH     0
        PUSH     0
        PUSH     EAX
        NEG      EDX
        PUSH     EDX
        PUSH     ECX
        NEG      EDX
        DEC      EDX
        PUSH     EDX
        PUSH     0
        PUSH     EAX
        CALL     StretchBlt
        CALL     FinishDC
        POP      EBX
        RET

@@noHandle:
        MOV      ECX, [EBX].fDIBBits
        JECXZ    @@exit

        PUSHAD   //----------------------------------------\
        XOR      EBP, EBP // Y = 0
        //+++++++++++++++++++++++++++ provide fScanLineSize
        MOV      EAX, EBX
        MOV      EDX, EBP
        CALL     GetScanLine //
        SUB      ESP, [EBX].fScanLineSize

@@loo:  LEA      EAX, [EBP*2]
        CMP      EAX, [EBX].fHeight
        JG       @@finloo

        MOV      EAX, EBX
        MOV      EDX, EBP
        CALL     GetScanLine
        MOV      ESI, EAX // ESI = ScanLine[ Y ]
        MOV      EDX, ESP
        MOV      ECX, [EBX].fScanLineSize
        PUSH     ECX
        CALL     System.Move

        MOV      EAX, EBX
        MOV      EDX, [EBX].fHeight
        SUB      EDX, EBP
        DEC      EDX
        CALL     GetScanLine
        MOV      EDI, EAX
        MOV      EDX, ESI
        POP      ECX
        PUSH     ECX
        CALL     System.Move

        POP      ECX
        MOV      EAX, ESP
        MOV      EDX, EDI
        CALL     System.Move

        INC      EBP
        JMP      @@loo

@@finloo:
        ADD      ESP, [EBX].fScanLineSize
        POPAD
@@exit:
        POP      EBX
end;

procedure TBitmap.FlipHorizontal;
asm
        PUSH     EBX
        MOV      EBX, EAX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit

        CALL     StartDC
        PUSH     SrcCopy
        MOV      EDX, [EBX].fHeight
        PUSH     EDX
        MOV      ECX, [EBX].fWidth
        PUSH     ECX
        PUSH     0
        PUSH     0
        PUSH     EAX
        PUSH     EDX
        NEG      ECX
        PUSH     ECX
        PUSH     0
        NEG      ECX
        DEC      ECX
        PUSH     ECX
        PUSH     EAX
        CALL     StretchBlt
        CALL     FinishDC
@@exit:
        POP      EBX
end;

(*
procedure TBitmap.CopyRect(const DstRect: TRect; SrcBmp: PBitmap;
  const SrcRect: TRect);
asm
        PUSHAD
        MOV      EBX, EAX
        MOV      ESI, ECX
        MOV      EDI, EDX
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit
        MOV      EAX, ESI
        CALL     GetHandle
        TEST     EAX, EAX
        JZ       @@exit
        CALL     StartDC
        XCHG     EBX, ESI
        CMP      EBX, ESI
        JNZ      @@diff1
        PUSH     EAX
        PUSH     0
        JMP      @@nodiff1
@@diff1:
        CALL     StartDC
@@nodiff1:
        PUSH     SrcCopy                  // ->
        MOV      EBP, [SrcRect]
        MOV      EAX, [EBP].TRect.Bottom
        MOV      EDX, [EBP].TRect.Top
        SUB      EAX, EDX
        PUSH     EAX                      // ->
        MOV      EAX, [EBP].TRect.Right
        MOV      ECX, [EBP].TRect.Left
        SUB      EAX, ECX
        PUSH     EAX                      // ->
        PUSH     EDX                      // ->
        PUSH     ECX                      // ->
        PUSH     dword ptr [ESP+24]       // -> DCsrc
        MOV      EAX, [EDI].TRect.Bottom
        MOV      EDX, [EDI].TRect.Top
        SUB      EAX, EDX
        PUSH     EAX                      // ->
        MOV      EAX, [EDI].TRect.Right
        MOV      ECX, [EDI].TRect.Left
        SUB      EAX, ECX
        PUSH     EAX                      // ->
        PUSH     EDX                      // ->
        PUSH     ECX                      // ->
        PUSH     dword ptr [ESP+13*4]     // -> DCdst
        CALL     StretchBlt
        CMP      EBX, ESI
        JNE      @@diff2
        POP      ECX
        POP      ECX
        JMP      @@nodiff2
@@diff2:
        CALL     FinishDC
@@nodiff2:
        CALL     FinishDC
@@exit:
        POPAD
end;
*)

procedure asmIconEmpty( Icon: PIcon );
asm
        CMP      [EAX].TIcon.fHandle, 0
end;

procedure TIcon.Clear;
asm     //cmd    //opd
        XOR      ECX, ECX
        XCHG     ECX, [EAX].fHandle
        JECXZ    @@1
        CMP      [EAX].fShareIcon, 0
        JNZ      @@1
        PUSH     EAX
        PUSH     ECX
        CALL     DestroyIcon
        POP      EAX
@@1:    MOV      [EAX].fShareIcon, 0
end;

{$IFNDEF ICON_DIFF_WH}
function TIcon.Convert2Bitmap(TranColor: TColor): HBitmap;
asm     //cmd    //opd
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        PUSH     EBP
        MOV      EBX, EAX
        MOV      EBP, EDX
        XOR      EDX, EDX
        CALL     asmIconEmpty
        JZ       @@ret_0
        PUSH     0
        CALL     GetDC
        PUSH     EAX //> DC0
        PUSH     EAX
        CALL     CreateCompatibleDC
        XCHG     EDI, EAX
        MOV      EDX, [EBX].fSize

        POP      EAX
        PUSH     EAX
        PUSH     EDX //>Bottom
        PUSH     EDX //>Right
        PUSH     0   //>Top
        PUSH     0   //>Left

        PUSH     EDX
        PUSH     EDX
        PUSH     EAX
        CALL     CreateCompatibleBitmap
        XCHG     EBP, EAX

        CALL     Color2RGB
        PUSH     EAX

        PUSH     EBP
        PUSH     EDI
        CALL     SelectObject
        XCHG     ESI, EAX

        CALL     CreateSolidBrush

        MOV      EDX, ESP
        PUSH     EAX
        PUSH     EAX
        PUSH     EDX
        PUSH     EDI
        CALL     Windows.FillRect
        CALL     DeleteObject

        XCHG     EAX, EBX
        MOV      EDX, EDI
        XOR      ECX, ECX
        PUSH     ECX
        CALL     Draw

        PUSH     EDI
        PUSH     ESI
        CALL     FinishDC

        ADD      ESP, 16
        PUSH     0
        CALL     ReleaseDC
        MOV      EDX, EBP

@@ret_0:
        XCHG     EAX, EDX
        POP      EBP
        POP      EDI
        POP      ESI
        POP      EBX
end;
{$ENDIF}

destructor TIcon.Destroy;
asm     //cmd    //opd
        PUSH     EAX
        CALL     Clear
        POP      EAX
        CALL     TObj.Destroy
end;

procedure TIcon.Draw(DC: HDC; X, Y: Integer);
asm     //cmd    //opd
        CALL     asmIconEmpty
        JZ       @@exit
        PUSH     DI_NORMAL
        PUSH     0
        PUSH     0
        {$IFDEF ICON_DIFF_WH}
        PUSH     [EAX].fHeight
        PUSH     [EAX].fWidth
        {$ELSE}
        PUSH     [EAX].fSize
        PUSH     [EAX].fSize
        {$ENDIF}
        PUSH     [EAX].fHandle
        PUSH     Y
        PUSH     ECX
        PUSH     EDX
        CALL     DrawIconEx
@@exit:
end;

procedure TIcon.StretchDraw(DC: HDC; Dest: TRect);
asm     //cmd    //opd
        CALL     asmIconEmpty
        JZ       @@exit
        PUSH     DI_NORMAL
        PUSH     0
        PUSH     0
        PUSH     ECX
        PUSH     ECX
        PUSH     [EAX].fHandle
        PUSH     [ECX].TRect.Top
        PUSH     [ECX].TRect.Left
        PUSH     EDX
        MOV      EAX, [ECX].TRect.Bottom
        SUB      EAX, [ECX].TRect.Top
        MOV      [ESP+20], EAX
        MOV      EAX, [ECX].TRect.Right
        SUB      EAX, [ECX].TRect.Left
        MOV      [ESP+16], EAX
        CALL     DrawIconEx
@@exit:
end;

procedure TIcon.SaveToFile(const FileName: KOLString);
asm     //cmd    //opd
        PUSH     EAX
        MOV      EAX, ESP
        MOV      ECX, EDX
        XOR      EDX, EDX
        CALL     SaveIcons2File
        POP      EAX
end;

procedure TIcon.SaveToStream(Strm: PStream);
asm     //cmd    //opd
        PUSH     EAX
        MOV      EAX, ESP
        MOV      ECX, EDX
        XOR      EDX, EDX
        CALL     SaveIcons2Stream
        POP      EAX
end;

function ColorBits( ColorsCount : Integer ) : Integer;
asm     //cmd    //opd
        PUSH     EBX
        MOV      EDX, offset[PossibleColorBits]
@@loop: MOVZX    ECX, byte ptr [EDX]
        JECXZ    @@e_loop
        INC      EDX
        XOR      EBX, EBX
        INC      EBX
        SHL      EBX, CL
        CMP      EBX, EAX
        JL       @@loop
@@e_loop:
        XCHG     EAX, ECX
        POP      EBX
end;

{$IFNDEF OLD_ALIGN}
{$IFDEF ASM_VERSION}
procedure AlignChildrenProc(Sender: PObj);
const AlignModes = (1 shl byte(caBottom))+(1 shl byte(caTop))+
                 (((1 shl byte(caRight)) +(1 shl byte(caLeft)))shl 8)+
                 (((1 shl byte(caClient))+(1 shl byte(caNone)))shl 16);
asm     //cmd    //opd
        TEST     EAX,EAX
        JZ       @@21
        CMP      [EAX].TControl.fParent,0
        SETZ     DL
        OR       DL,[EAX].TControl.fisForm
        BTR      dword ptr[EAX].TControl.fAligning,oaFromSelf
        JA       @@20
        OR       byte ptr[EAX].TControl.fAligning,(1 shl oaWaitAlign)
        MOV      EAX,[EAX].TControl.fParent
@@20:   CALL     @@ToBeAlign
        JNZ      @@DoAlign
@@21:   RETN

@@ToBeAlign:
        MOV      DL,[EAX].TControl.fVisible
        OR       DL,[EAX].TControl.fCreateHidden
        JE       @@10
        AND      DL,[EAX].TControl.fisForm
        JNE      @@12
        CMP      dword ptr[EAX].TControl.fParent,0
        JE       @@11
        PUSH     EAX
        MOV      EAX,[EAX].TControl.fParent
        CALL     @@ToBeAlign
        POP      EAX
@@10:   XOR      DL,1
//!!! Important: oaWaitAlign=0
        OR       [EAX].TControl.fAligning,DL
@@11:   XOR      DL,1
@@12:   RETN

@@DoAlign:
        //CALL     AlignChildrenProc_
        //RET
        PUSH     EBP
        PUSH     EBX
        PUSH     ESI
        PUSH     EDI
        PUSH     AlignModes //00210A14h
        SUB      ESP,030h
        MOV      EBX,EAX
        AND      byte ptr[EBX].TControl.fAligning,not(1 shl oaWaitAlign)
        OR       byte ptr[EBX].TControl.fAligning,(1 shl oaAligning)
        LEA      EDX,[ESP+20h] //@CR
        CALL     TControl.ClientRect
@@Main:
        MOV      EAX,[EBX].TControl.fChildren
        MOV      EDI,[EAX].TList.fCount
        MOV      EBP,[EAX].TList.fItems
        JMP      @@entry
@@loop:
        MOV      ESI,[EBP]
        MOV      AL,[ESI].TControl.fVisible
        OR       AL,[ESI].TControl.fCreateHidden
        JZ       @@continue
        MOVZX    EAX,[ESI].TControl.fAlign
        BT       [ESP+30h],EAX //Allowed
        JNC      @@continue
        CMP      byte ptr[ESI].TControl.fNotUseAlign,0
        JNE      @@align
        MOV      EDX,ESP       //@R
        MOV      EAX,ESI       //C
        CALL     TControl.GetBoundsRect
        MOV      EAX,[ESP+0Ch] //R.Bottom
        MOV      [ESP+1Ch],EAX //H
        MOV      EAX,[ESP+08h] //R.Right
        MOV      [ESP+18h],EAX //W
        MOV      EAX,[ESP+04h] //R.Top
        MOV      [ESP+14h],EAX //R1.Top
        SUB      [ESP+1Ch],EAX //H
        MOV      EAX,[ESP]     //R.Left
        MOV      [ESP+10h],EAX //R1.Left
        SUB      [ESP+18h],EAX //W
        MOV      EDX,[EBX].TControl.fMargin
        MOVZX    ECX,byte ptr[ESI].TControl.fAlign
//!!! Order of caXXX-constants is important
        LOOP     @@caTop
        MOV      EAX,[ESP+20h] //CR.Left
        SUB      EAX,[ESP]     //R.Left
        ADD      EAX,EDX       //+Margin
        MOV      ECX,[ESP+18h] //W
        ADD      ECX,EDX       //+Margin
        ADD      [ESP+20h],ECX //CR.Left
        JMP      @@00
@@caTop:
        LOOP     @@caRight
        MOV      EAX,[ESP+24h] //CR.Top
        SUB      EAX,[ESP+04h] //R.Top
        ADD      EAX,EDX       //+Margin
        MOV      ECX,[ESP+1Ch] //H
        ADD      ECX,EDX       //+Margin
        ADD      [ESP+24h],ECX //CR.Top
        JMP      @@01
@@caRight:
        LOOP     @@caBottom
        MOV      EAX,[ESP+28h] //CR.Right
        SUB      EAX,[ESP+08h] //R.Right
        SUB      EAX,EDX       //-Margin
        MOV      ECX,[ESP+18h] //W
        ADD      ECX,EDX       //+Margin
        SUB      [ESP+28h],ECX //CR.Right
@@00:   ADD      [ESP],EAX     //R.Left
        ADD      [ESP+08h],EAX //R.Right
        MOV      EAX,[ESP+2Ch] //CR.Bottom
        SUB      EAX,EDX       //+Margin
        MOV      [ESP+0Ch],EAX //R.Bottom
        ADD      EDX,[esp+24h] //Margin+CR.Top
        MOV      [ESP+04h],edx //R.Top
        JMP      @@caNone
@@caBottom:
        LOOP     @@caClient
        MOV      EAX,[ESP+2Ch] //CR.Bottom
        SUB      EAX,[ESP+0Ch] //R.Bottom
        SUB      EAX,EDX       //-Margin
        MOV      ECX,[ESP+1Ch] //H
        ADD      ECX,EDX       //+Margin
        SUB      [ESP+2Ch],ECX //CR.Bottom
@@01:   ADD      [ESP+04h],EAX //R.Top
        ADD      [ESP+0Ch],EAX //R.Bottom
        MOV      EAX,[ESP+28h] //CR.Right
        SUB      EAX,EDX       //-Margin
        MOV      [esp+08h],EAX //R.Right
        ADD      EDX,[ESP+20h] //Margin+CR.Left
        MOV      [ESP],EDX     //R.Left
        JMP      @@caNone
@@caClient:
        LOOP     @@caNone
        MOV      EAX,[ESP+2Ch] //CR.Bottom
        SUB      EAX,EDX       //-Margin
        MOV      [ESP+0Ch],EAX //R.Bottom
        MOV      EAX,[ESP+28h] //CR.Right
        SUB      EAX,EDX       //-Margin
        MOV      [ESP+08h],EAX //R.Right
        MOV      EAX,[ESP+24h] //CR.Top
        ADD      EAX,EDX       //+Margin
        MOV      [ESP+04h],EAX //R.Top
        ADD      EDX,[ESP+20h] //Margin+CR.Left
        MOV      [ESP],EDX     //R.Left
@@caNone:
        MOV      EAX,[ESP]     //R.Left
        CMP      EAX,[ESP+08h] //R.Right
        JLE      @@02  //CMOVG ???
        MOV      [ESP+08h],EAX //R.Right
@@02:   MOV      EAX,[ESP+04h] //R.Top
        CMP      EAX,[ESP+0Ch] //R.Bottom
        JLE      @@03  //CMOVG ???
        MOV      [ESP+0Ch],EAX //R.Bottom
@@03:   MOV      EDX,[ESP]     //R.Left
        SUB      EDX,[ESP+10h] //R1.Left
        MOV      EAX,[ESP+04h] //R.Top
        SUB      EAX,[ESP+14h] //R1.Top
        OR       EDX,EAX       //ChgPos
        MOV      ECX,[ESP+08h] //R.Right
        SUB      ECX,[ESP]     //R.Left
        SUB      ECX,[ESP+18h] //W
        MOV      EAX,[ESP+0Ch] //R.Bottom
        SUB      EAX,[ESP+04h] //R.Top
        SUB      EAX,[ESP+1Ch] //H
        OR       EAX,ECX
        JZ       @@04
        AND      byte ptr[ESI].TControl.fAligning,not(1 shl oaWaitAlign)
        OR       byte ptr[ESI].TControl.fAligning,(1 shl oaFromSelf)
@@04:   OR       EAX,EDX
        JZ       @@align
        MOV      EDX,ESP       //@R
        MOV      EAX,ESI       //C
        CALL     TControl.SetBoundsRect
@@align:
        TEST     byte ptr[ESI].TControl.fAligning,(1 shl oaWaitAlign)
        JZ       @@continue
        MOV      EAX,ESI       //C
        CALL     @@DoAlign
@@continue:
        TEST     byte ptr[EBX].TControl.fAligning,(1 shl oaAligning)
        JZ       @@exit
        ADD      EBP,4
@@entry:
        DEC      EDI
        JGE      @@loop
        SHR      dword ptr[ESP+30h],8 //Allowed
        JNZ      @@Main
        AND      byte ptr[EBX].TControl.fAligning,not(1 shl oaAligning)
@@exit:
        ADD      ESP,34h
        POP      EDI
        POP      ESI
        POP      EBX
        POP      EBP
end;
{$ENDIF ASM_VERSION}
{$ENDIF OLD_ALIGN}

function WndProcUpdate( Sender: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //cmd    //opd
        PUSH     EBX
        XCHG     EBX, EAX
        MOV      EAX, [EBX].TControl.fUpdateCount
        TEST     EAX, EAX
        JZ       @@exit

        XOR      EAX, EAX
        MOV      EDX, [EDX].TMsg.message
        CMP      DX, WM_PAINT
        JNE      @@chk_erasebkgnd

        MOV      [ECX], EAX
        PUSH     EAX
        PUSH     [EBX].TControl.fHandle
        CALL     ValidateRect
        JMP      @@rslt_1
@@chk_erasebkgnd:
        CMP      DX, WM_ERASEBKGND
        JNE      @@exit
        INC      EAX
        MOV      [ECX], EAX
@@rslt_1:
        MOV      AL, 1
@@exit:
        POP      EBX
end;

function EnumDynHandlers( Self_: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
asm     //cmd    //opd
        CMP      [EAX].TControl.fRefCount, 0
        JL       @@fin_false
        PUSHAD
        MOV      EBX, EAX
        MOV      EBP, ECX
        MOV      ECX, [EBX].TControl.fDynHandlers
        JECXZ    @@ret_false
        MOV      ESI, ECX
        MOV      ECX, [ESI].TList.fCount
        JECXZ    @@ret_false
        MOV      EDI, ECX
        SHR      EDI, 1
        CALL     TControl.RefInc
@@loo:  DEC      EDI
        JS       @@e_loo
        PUSH     EDX
        PUSH     EBX
{$IFNDEF SMALLEST_CODE}
{$IFNDEF ENUM_DYN_HANDLERS_AFTER_RUN}
        XOR      EAX, EAX
        CMP      [AppletTerminated], AL
        JZ       @@do_call
        MOV      ECX, [ESI].TList.fItems
        MOV      ECX, [ECX+EDI*8+4]
        JECXZ    @@skip_call
{$ENDIF}
{$ENDIF}
@@do_call:
        MOV      EAX, [ESI].TList.fItems
        MOV      EAX, [EAX+EDI*8]
        XCHG     EAX, EBX
        MOV      ECX, EBP
        CALL     EBX
@@skip_call:
        POP      EBX
        POP      EDX
        TEST     AL, AL
        JZ       @@loo
@@ret_true:
        MOV      EAX, EBX
        CALL     TControl.RefDec
        POPAD
        MOV      AL, 1
        RET
@@e_loo:
        XOR      EAX, EAX
        INC      EAX
        CMP      [EBX].TControl.fRefCount, EAX
        JE       @@ret_true
        MOV      EAX, EBX
        CALL     TControl.RefDec
@@ret_false:
        POPAD
@@fin_false:
        XOR      EAX, EAX
end;

procedure TControl.AttachProcEx( Proc: TWindowFunc; ExecuteAfterAppletTerminated: Boolean );
asm     PUSH     EBX
        PUSH     EDI
        PUSH     ECX
        XCHG     EBX, EAX
        MOV      EDI, EDX
        MOV      [EBX].fOnDynHandlers, offset[EnumDynHandlers]
        MOV      EAX, [EBX].fDynHandlers
        MOV      EDX, EDI
        CALL     TList.IndexOf
        TEST     EAX, EAX
        JGE      @@exit

        MOV      EAX, [EBX].fDynHandlers
        PUSH     EAX
        MOV      EDX, EDI
        CALL     TList.Add
        POP      EAX
        POP      EDX
        PUSH     EDX
        CALL     TList.Add
@@exit: {$IFNDEF SMALLEST_CODE}
        MOV      EAX, [EBX].fDynHandlers
        CALL     [Global_AttachProcExtension]
        {$ENDIF}
        POP      ECX
        POP      EDI
        POP      EBX
end;

function TControl.IsProcAttached(Proc: TWindowFunc): Boolean;
asm     //cmd    //opd
        //MOV      ECX, [EAX].TControl.fDynHandlers
        MOV      EAX, [EAX].TControl.fDynHandlers
        //JECXZ    @@exit
        //XCHG     EAX, ECX
        CALL     TList.IndexOf
        TEST     EAX, EAX
        //SETGE    CL
        SETGE    AL
//@@exit: XCHG     EAX, ECX
end;

function WinVer : TWindowsVersion;
asm
  MOVSX EAX, byte ptr [SaveWinVer]
  INC   AH     // если <> 0 после инкремента, то AL содержит вычисленную версию
  JNZ   @@exit
  CALL  GetVersion // EAX < 0 для платформы 9х, иначе NT; AL=MajorVersion; AH=MinorVersion
  XCHG  EDX, EAX
  XOR   EAX, EAX
  TEST  EDX, EDX
  XCHG  DL, DH    // DH=MajorVersion; DL=MinorVersion
  JL    @@platform_9x
  MOV   AL, wvNT
  CMP   DH, 5
  JB    @@save_exit
  INC   AL // wvY2K
  CMP   DX, $0501
  JB    @@save_exit
  INC   AL // wvXP
  DEC   DL
  JZ    @@save_exit
  INC   AL // wvServer2003
  CMP   DH, 6
  JB    @@save_exit
  INC   AL // wvVista
  JMP   @@save_exit
@@platform_9x:
  CMP   DH, 4
  JB    @@save_exit // wv31
  INC   AL // wv95
  CMP   DX, $040A
  JB    @@save_exit
  INC   AL // wv98
  CMP   DX, $045A
  JB    @@save_exit
  INC   AL // wvME
@@save_exit:
  MOV   byte ptr [SaveWinVer], AL
@@exit:
end;

//======================================== THE END OF FILE KOL_ASM.inc

