// Name:   KOL Addon - Visual XP Styles
// Rev.:   1.95
// Date:   9 aug 2007 /18:49/
// Author: MTsv DN
// Thanks: mdw

{$IFDEF _FPC}
const
  clGrey = TColor($808080);
  clLtGrey = TColor($C0C0C0);
  clDkGrey = TColor($808080);
{$ENDIF}

//********************* Creating font on Sender font base ********************//
function CreateNewFont(Sender : PControl): HFont;
const
 CLEARTYPE_QUALITY  = 5;
var
 fnWeight : Integer;
 fnItalic, fnUnderline, fnStrikeOut,
 fnQuality, fnPitch : DWORD;
begin
 // Font style
 if Sender.Font.FontStyle = [fsBold] then fnWeight := 700 else fnWeight := 0;
 if Sender.Font.FontStyle = [fsItalic] then fnItalic := DWORD(TRUE) else fnItalic := DWORD(FALSE);
 if Sender.Font.FontStyle = [fsUnderline] then fnUnderline := DWORD(TRUE) else fnUnderline := DWORD(FALSE);
 if Sender.Font.FontStyle = [fsStrikeOut] then fnStrikeOut := DWORD(TRUE) else fnStrikeOut := DWORD(FALSE);

 // Font quality
 case Sender.Font.FontQuality of
  fqAntialiased:    fnQuality := DWORD(ANTIALIASED_QUALITY);
  {$IFDEF AUTO_REPLACE_CLEARTYPE}
  fqClearType:      fnQuality := DWORD(CLEARTYPE_QUALITY);
  {$ELSE}
  fqClearType:      fnQuality := DWORD(ANTIALIASED_QUALITY);
  {$ENDIF}
  fqDraft:          fnQuality := DWORD(DRAFT_QUALITY);
  fqNonAntialiased: fnQuality := DWORD(NONANTIALIASED_QUALITY);
  fqProof:          fnQuality := DWORD(PROOF_QUALITY);
  {fqDefault:} else fnQuality := DWORD(DEFAULT_QUALITY);
 end;

 // Font pitch
 case Sender.Font.FontPitch of
  fpFixed:     fnPitch := DWORD(FIXED_PITCH);
  fpVariable:  fnPitch := DWORD(VARIABLE_PITCH);
  {fpDefault:} else fnPitch := DWORD(DEFAULT_PITCH);
 end;

 Result := CreateFont(Sender.Font.FontHeight,
                      Sender.Font.FontWidth,
                      0,
                      Sender.Font.FontOrientation,
                      fnWeight,
                      fnItalic,
                      fnUnderline,
                      fnStrikeOut,
                      Sender.Font.FontCharset,
                      OUT_DEFAULT_PRECIS,
                      CLIP_DEFAULT_PRECIS,
                      fnQuality,
                      fnPitch,
                      PKOLChar(Sender.Font.FontName));
end;
//***************************** Initializing themes **************************//
function InitThemes : boolean;
begin
 Result := false;
 ThemeLibrary := LoadLibrary(themelib);
 if ThemeLibrary > 0 then
  begin
   OpenThemeData := GetProcAddress(ThemeLibrary, 'OpenThemeData');
   DrawThemeBackground := GetProcAddress(ThemeLibrary, 'DrawThemeBackground');
   IsThemeBackgroundPartiallyTransparent := GetProcAddress(ThemeLibrary, 'IsThemeBackgroundPartiallyTransparent');
   DrawThemeParentBackground := GetProcAddress(ThemeLibrary, 'DrawThemeParentBackground');
   DrawThemeText := GetProcAddress(ThemeLibrary, 'DrawThemeText');
   CloseThemeData := GetProcAddress(ThemeLibrary, 'CloseThemeData');
   IsThemeActive := GetProcAddress(ThemeLibrary, 'IsThemeActive');
   IsAppThemed := GetProcAddress(ThemeLibrary, 'IsAppThemed');
   GetThemeColor := GetProcAddress(ThemeLibrary, 'GetThemeColor');
   Result := true;
  end;
end;
//***************************** Deinitializing themes ************************//
procedure DeinitThemes;
begin
 if ThemeLibrary > 0 then
  begin
   FreeLibrary(ThemeLibrary);
   ThemeLibrary := 0;
   OpenThemeData := nil;
   DrawThemeBackground := nil;
   IsThemeBackgroundPartiallyTransparent := nil;
   DrawThemeParentBackground := nil;
   CloseThemeData := nil;
   IsAppThemed := nil;
   IsThemeActive := nil;
   GetThemeColor := nil;
  end;
end;
//****************************** Checking themes *****************************//
procedure CheckThemes;
// Check Manifest file or resource
 function IsManifestFilePresent : boolean;
 begin
  Result := false;
  if FileExists(ExePath + '.manifest') then
   begin
    Result := true;
    exit;
   end;
  if FindResource(hInstance, MAKEINTRESOURCE(1), MakeIntResource(24)) <> 0 then
   Result := true;
 end;
// Check activity themes
 function UseThemes: Boolean;
 begin
  if (ThemeLibrary > 0) then Result := IsThemeActive
   else Result := False;
 end;
begin
 AppTheming := false;
 if IsManifestFilePresent then
  if InitThemes then
   begin
    if UseThemes then
     AppTheming := true;
    DeinitThemes;
   end;
end;
//****************************** Drawing Splitter ****************************//
procedure WndSplitterXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
const
 Bit  : Word = $FF;
var
 B, Brush : HBRUSH;
 fDC : HDC;
 Bmp : HBITMAP;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndSplitterXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
  
 // Draw back layer
 Brush := CreateSolidBrush(Color2RGB(Sender.fParent.Color));
 fDC := SelectObject(DC, Brush);
 FillRect(DC, Sender.ClientRect, Brush);
 SelectObject(DC, fDC);
 DeleteObject(Brush);

 // Creating brush and pen
 if Sender.fPressed then
  begin
   Bmp := CreateBitmap(2, 2, 1, 1, @Bit);
   B := CreatePatternBrush(Bmp);
   fDC := SelectObject(DC, B);
   // Drawing splitter
   PatBlt   (DC, 0, 0, Sender.Width, Sender.Height, PATINVERT);
   // Destroying  brush and pen
   SelectObject(DC, fDC);
   DeleteObject(B);
   DeleteObject(Bmp);
  end;
end;
//*************************** Drawing TabControl Page ************************//
procedure WndTabXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 hThemes : THandle;
 Color : COLORREF;
 Brush : HBRUSH;
 fDC : HDC;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndTabXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
   hThemes := OpenThemeData(Sender.fHandle, 'TAB');
   if hThemes <> 0 then
    begin
     GetThemeColor(hThemes, 10, 0, 3805, Color);
     Sender.Color := Color2RGB(Color);
     Brush := CreateSolidBrush(Color2RGB(Color));
     fDC := SelectObject(DC, Brush);
     FillRect(DC, Sender.ClientRect, Brush);
     SelectObject(DC, fDC);
     DeleteObject(Brush);
     CloseThemeData(hThemes);
    end;
end;
//*************************** Drawing Panel control **************************//
procedure WndPanelXPResize( Dummy : Pointer; Sender: PObj );
var
 R : TRect;
begin
 R := PControl(Sender).ClientRect;
 InvalidateRect(PControl(Sender).fHandle, @R, False);
end;

procedure WndPanelXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 RClient, RText : TRect;
 LPos : DWORD;
 S : KOLString;
 F : HFONT;
 fDC1, fDC2 : HDC;
 hThemes : THandle;
 TxtColor, Color : COLORREF;
 Brush : HBRUSH;
 Pen : HPEN;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndPanelXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;

 // Getting rects
 RClient := Sender.ClientRect;
 // Getting text and text flags
 S := Sender.fCaption;
 LPos := 0;
 if S <> '' then
  begin
   case Sender.fVerticalAlign of
    vaTop:    LPos := DT_TOP;
    vaCenter: LPos := DT_VCENTER;
    vaBottom: LPos := DT_BOTTOM;
   end;
   case Sender.fTextAlign of
    taLeft:    LPos := LPos or DT_LEFT;
    taCenter:  LPos := LPos or DT_CENTER;
    taRight:   LPos := LPos or DT_RIGHT;
   end;
  end;

 // Draw back layer
 if Sender.fedgeStyle <> esTransparent then
  begin
   Brush := CreateSolidBrush(Color2RGB(Sender.fParent.Color));
   fDC1 := SelectObject(DC, Brush);
   FillRect(DC, RClient, Brush);

   case Sender.fedgeStyle of
   esRaised, esLowered:
    begin
     Sender.fStyle := Sender.fStyle and (not SS_SUNKEN) and (not WS_DLGFRAME);
     Sender.fExStyle := Sender.fExStyle and (not WS_EX_STATICEDGE) or WS_EX_WINDOWEDGE;

     Pen := CreatePen(PS_SOLID, 1, Color2RGB(clLtGrey));
     fDC2 := SelectObject(DC, Pen);
     RoundRect(DC, RClient.Left, RClient.Top,
                   RClient.Right, RClient.Bottom, 5, 5);
     SelectObject(DC, fDC2);
     DeleteObject(Pen);
    end;
   end;

   SelectObject(DC, fDC1);
   DeleteObject(Brush);
  end;

 if S <> '' then
  begin
   hThemes := OpenThemeData(Sender.fHandle, 'button');
   Color := Sender.Font.Color;
   if hThemes <> 0 then
    begin
     if not Sender.fEnabled then
      GetThemeColor(hThemes, 1, 4, 3803, Color);
     CloseThemeData(hThemes);
    end;
   RText := MakeRect(2, 2, Sender.Width-2, Sender.Height-2);

   // Create font
   F := CreateNewFont(Sender);
   fDC1 := SelectObject(DC, F);
   // Draw text
   SetBkMode(DC, TRANSPARENT);
   TxtColor := SetTextColor(DC, Color2RGB(Color));
   DrawText(DC, PKOLChar(S), Length(S), RText, LPos or DT_SINGLELINE);
   // Backup color
   SetTextColor(DC, Color2RGB(TxtColor));
   SetBkMode(DC, OPAQUE);
   // Destroying font
   SelectObject(DC, fDC1);
   DeleteObject(F);
  end;
end;
//************************** Drawing GroupBox control ************************//
procedure WndGroupBoxXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 hThemes : THandle;
 RClient, RText, RClipMain, RClipLeft, RClipRight : TRect;
 LPos, fState : DWORD;
 S : KOLString;
 F : HFONT;
 fDC : HDC;
 TxtColor, Color : COLORREF;
 TextWidth, TextHeight : Integer;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndGroupBoxXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
  
 // Getting text and text flags
 LPos := 0;
 case Sender.fVerticalAlign of
  vaTop:    LPos := DT_TOP;
  vaCenter: LPos := DT_VCENTER;
  vaBottom: LPos := DT_BOTTOM;
 end;
 case Sender.fTextAlign of
  taLeft:    LPos := LPos or DT_LEFT;
  taCenter:  LPos := LPos or DT_CENTER;
  taRight:   LPos := LPos or DT_RIGHT;
 end;
 S := Sender.fCaption;

 // Getting rects
 TextWidth := Sender.Canvas.WTextWidth(S);
 TextHeight := Sender.Canvas.WTextHeight(S);

 RClient := Sender.ClientRect;
 RClient.Left := RClient.Left - Sender.MarginLeft;
 RClient.Top := RClient.Top - Sender.MarginTop + (TextHeight div 2);
 RClient.Right := RClient.Right + Sender.MarginRight;
 RClient.Bottom := RClient.Bottom + Sender.MarginBottom;

 case Sender.fTextAlign of
  taCenter:
   begin
    RText := MakeRect(((RClient.Right div 2) - (TextWidth div 2)) - 2,
                      RClient.Top-6,
                      ((RClient.Right div 2) + (TextWidth div 2)) + 2,
                      TextHeight + (RClient.Top-6));
    RClipLeft := MakeRect(RClient.Left,
                          RClient.Top,
                          ((RClient.Right div 2) - (TextWidth div 2)) - 2,
                          TextHeight + (RClient.Top-6));
    RClipRight := MakeRect(((RClient.Right div 2) + (TextWidth div 2)) + 2,
                           RClient.Top-6,
                           RClient.Right,
                           TextHeight + (RClient.Top-6));
   end;
  taRight:
   begin
    RText := MakeRect((RClient.Right-4) - TextWidth,
                      RClient.Top-6,
                      RClient.Right-4,
                      TextHeight + (RClient.Top-6));
    RClipLeft := MakeRect(RClient.Left,
                          RClient.Top,
                          (RClient.Right-4) - TextWidth,
                          TextHeight + (RClient.Top-6));
    RClipRight := MakeRect(RClient.Right-4,
                           RClient.Top-6,
                           RClient.Right,
                           TextHeight + (RClient.Top-6));
   end;
 else
  RText := MakeRect(RClient.Left+4,
                    RClient.Top-6,
                    TextWidth + RClient.Left+4,
                    TextHeight + RClient.Top-6);
  RClipLeft := MakeRect(RClient.Left,
                        RClient.Top,
                        RClient.Left+4,
                        TextHeight + RClient.Top-6);
  RClipRight := MakeRect(TextWidth + RClient.Left+4,
                         RClient.Top-6,
                         RClient.Right,
                         TextHeight + RClient.Top-6);
 end;
 RClipMain := MakeRect(RClient.Left,
                       TextHeight + RClient.Top-6,
                       RClient.Right,
                       RClient.Bottom);
 // Open themes
 hThemes := OpenThemeData(Sender.fHandle, 'button');
 if hThemes <> 0 then
  begin
   Sender.Color := Sender.fParent.Color;
   if Sender.fEnabled then fState := 1 else fState := 2;
   // Drawing GroupBox rect "step by step"
   DrawThemeBackground(hThemes, DC, 4{BP_GROUPBOX}, fState{GBS_XXXXXX},  RClient, @RClipMain);
   DrawThemeBackground(hThemes, DC, 4{BP_GROUPBOX}, fState{GBS_XXXXXX},  RClient, @RClipLeft);
   DrawThemeBackground(hThemes, DC, 4{BP_GROUPBOX}, fState{GBS_XXXXXX},  RClient, @RClipRight);
   // Drawing GroupBox text
   if not Sender.fEnabled then GetThemeColor(hThemes, 1, 4, 3803, Color)
    else GetThemeColor(hThemes, 4, 2, 3803, Color);
   // Close themes
   CloseThemeData(hThemes);

   // Create font
   F := CreateNewFont(Sender);
   fDC := SelectObject(DC, F);
   // Draw text
   SetBkMode(DC, TRANSPARENT);
   TxtColor := SetTextColor(DC, Color2RGB(Color));
   DrawText(DC, PKOLChar(S), Length(S), RText, LPos or DT_SINGLELINE);
   // Backup color
   SetTextColor(DC, Color2RGB(TxtColor));
   SetBkMode(DC, OPAQUE);
   // Destroying font
   SelectObject(DC, fDC);
   DeleteObject(F);
  end;
end;
//************************* Drawing CheckBox control *************************//
procedure WndCheckBoxXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 hThemes : THandle;
 RClient, RCheck, RText : TRect;
 fState : DWORD;
 W, H : Integer;
 S : KOLString;
 F : HFONT;
 fDC : HDC;
 Color : COLORREF;
 TxtColor : COLORREF;
 Brush : HBRUSH;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndCheckBoxXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
  
 // Getting metrics
 W := GetSystemMetrics( SM_CXMENUCHECK );
 H := GetSystemMetrics( SM_CYMENUCHECK );
 // Getting caption
 S := Sender.fCaption;
 // Getting rects
 RClient := Sender.ClientRect;
 RCheck := RClient;
 RCheck.Right := RCheck.Left + W;
 if Sender.fWordWrap then
  RCheck.Top := RCheck.Top + Sender.Border
 else
  RCheck.Top := RCheck.Top + (RCheck.Bottom - RCheck.Top - H) div 2;
 RCheck.Bottom := RCheck.Top + H;
 RText := MakeRect(RCheck.Right + Sender.Border, RCheck.Top,
                   RClient.Right, RCheck.Bottom);
 // Getting state
 fState := 1; {CBS_UNCHECKEDNORMAL}
 if not Sender.fEnabled then
  fState := 4 {CBS_UNCHECKEDDISABLED}
 else
 if Sender.fHot then
  fState := 2; {CBS_UNCHECKEDHOT}
 if Sender.fPressed then
  fState := 3{CBS_UNCHECKEDPRESSED};
 case Sender.Check3 of
  tsChecked : Inc( fState, 4 );
  tsIndeterminate : Inc( fState, 8 );
 end;

 // Draw back layer
 if not Sender.fTransparent then
  begin
   Brush := CreateSolidBrush(Color2RGB(Sender.fParent.Color));
   fDC := SelectObject(DC, Brush);
   FillRect(DC, RClient, Brush);
   SelectObject(DC, fDC);
   DeleteObject(Brush);
  end;

 // Draw theme
 Color := Sender.Font.Color;
 hThemes := OpenThemeData(Sender.fHandle, 'button');
 if hThemes <> 0 then
  begin
   if not Sender.fEnabled then
    GetThemeColor(hThemes, 1, 4, 3803, Color);
   DrawThemeBackground(hThemes, DC, 3 {BP_CHECKBOX}, fState, RCheck, @RCheck);
   CloseThemeData(hThemes);
  end;
  
 // Create font
 F := CreateNewFont(Sender);
 fDC := SelectObject(DC, F);
 // Draw text
 SetBkMode(DC, TRANSPARENT);
 TxtColor := SetTextColor(DC, Color2RGB(Color));
 DrawText(DC, PKOLChar(S), Length(S), RText, DT_LEFT or DT_VCENTER or DT_SINGLELINE);
 // Destroying font
 SetTextColor(DC, Color2RGB(TxtColor));
 SetBkMode(DC, OPAQUE);
 // Destroying object
 SelectObject(DC, fDC);
 DeleteObject(F);

 // Draw focusrect
 if GetFocus = Sender.fHandle then DrawFocusRect(DC, RClient);
end;
//************************* Drawing RadioBox control *************************//
procedure WndRadioBoxXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 hThemes : THandle;
 RClient, RDot, RText : TRect;
 fState : DWORD;
 W, H : Integer;
 S : KOLString;
 F : HFONT;
 fDC : HDC;
 Color, TxtColor : COLORREF;
 Brush : HBRUSH;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndRadioBoxXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
  
 // Getting metrics
 W := GetSystemMetrics( SM_CXMENUCHECK );
 H := GetSystemMetrics( SM_CYMENUCHECK );
 // Getting caption
 S := Sender.fCaption;
 // Getting rects
 RClient := Sender.ClientRect;
 RDot := RClient;
 RDot.Right := RDot.Left + W;
 if Sender.fWordWrap then
  RDot.Top := RDot.Top + Sender.Border
 else
  RDot.Top := RDot.Top + (RDot.Bottom - RDot.Top - H) div 2;
 RDot.Bottom := RDot.Top + H;
 RText := MakeRect(RDot.Right + Sender.Border, RDot.Top,
                   RClient.Right, RDot.Bottom);
 // Getting state
 fState := 1; {CBS_UNCHECKEDNORMAL}
 if not Sender.fEnabled then
  fState := 4 {CBS_UNCHECKEDDISABLED}
 else
 if Sender.fHot then
  fState := 2; {CBS_UNCHECKEDHOT}
 if Sender.fPressed then
  fState := 3{CBS_UNCHECKEDPRESSED};
 if Sender.Checked then
  Inc( fState, 4 );

 // Draw back layer
 if not Sender.fTransparent then
  begin
   Brush := CreateSolidBrush(Color2RGB(Sender.fParent.Color));
   fDC := SelectObject(DC, Brush);
   FillRect(DC, RClient, Brush);
   SelectObject(DC, fDC);
   DeleteObject(Brush);
  end;

 // Draw theme
 Color := Sender.Font.Color;
 hThemes := OpenThemeData(Sender.fHandle, 'button');
 if hThemes <> 0 then
  begin
   if not Sender.fEnabled then
    GetThemeColor(hThemes, 1, 4, 3803, Color);
   DrawThemeBackground(hThemes, DC, 2 {BP_RADIOBOX}, fState, RDot, @RDot);
   CloseThemeData(hThemes);
  end;
  
 // Create font
 F := CreateNewFont(Sender);
 fDC := SelectObject(DC, F);
 // Draw text
 SetBkMode(DC, TRANSPARENT);
 TxtColor := SetTextColor(DC, Color2RGB(Color));
 DrawText(DC, PKOLChar(S), Length(S), RText, DT_LEFT or DT_VCENTER or DT_SINGLELINE);
 // Destroying font
 SetTextColor(DC, Color2RGB(TxtColor));
 SetBkMode(DC, OPAQUE);
 // Destroying object
 SelectObject(DC, fDC);
 DeleteObject(F);
 
 // Draw focusrect
 if GetFocus = Sender.fHandle then DrawFocusRect(DC, RClient);
end;
//******************** Drawing Button and BitButton control ******************//
procedure WndButtonXPDraw( Dummy : Pointer; Sender: PControl; DC: HDC );
var
 hThemes : THandle;
 F : HFONT;
 fDC1, fDC2 : HDC;
 RClient : TRect;
 RText : TRect;
 RIcon : TRect;
 S : WideString;
 fState, bStyle : DWORD;
 Bmp : HBITMAP;
 W, H : Integer;
 HPos, VPos : DWORD;
 Brush : HBRUSH;
 Pen : HPEN;
 SenderWidth, SenderHeight : integer;
begin
 // Checking user owner-draw
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint <> @WndButtonXPDraw) then
  begin
   Sender.fOnPaint(Sender, DC);
   exit;
  end;
 if Assigned(Sender.fOnBitBtnDraw) then
  begin
   fState := 0{PBS_NORMAL};
   if not Sender.fEnabled then
    fState := 2{PBS_DISABLED}
     else
   if GetFocus = Sender.fHandle then
    fState := 3{PBS_PRESSED}
     else
   if Sender.fHot then
    fState := 4{PBS_HOT};
   if Sender.fPressed then
    fState := 1{PBS_PRESSED};
   Sender.fOnBitBtnDraw(Sender, fState);
   exit;
  end;

 // Getting rects
 RClient := Sender.ClientRect;
 RText := RClient;
 // Calc bitmap rect
 Bmp := Sender.fGlyphBitmap;
 HPos := 0; VPos := 0;
 if Bmp <> 0 then
  begin
   SenderWidth := Sender.Width;
   SenderHeight := Sender.Height;
   W := Sender.fGlyphWidth;
   H := Sender.fGlyphHeight;
   if Sender.fglyphLayout in [ glyphLeft ] then
    begin
     RIcon := MakeRect((SenderWidth div 2) - (W + (W div 4)),
                       (SenderHeight div 2) - (H div 2),
                        W, SenderHeight);
     RText.Left := (SenderWidth div 2) + (W div 4);
     HPos := DT_LEFT;
     VPos := DT_VCENTER;
    end;
   if Sender.fglyphLayout in [ glyphRight ] then
    begin
     RIcon := MakeRect((SenderWidth div 2) + (W div 4),
                       (SenderHeight div 2) - (H div 2),
                        W, SenderHeight);
     RText.Right := (SenderWidth div 2) - (W div 4);
     HPos := DT_RIGHT;
     VPos := DT_VCENTER;
    end;
   if Sender.fglyphLayout in [ glyphOver ] then
    begin
     RIcon := MakeRect((SenderWidth div 2) - (W div 2),
                       (SenderHeight div 2) - (H div 2),
                        W, SenderHeight);
     HPos := DT_CENTER;
     VPos := DT_VCENTER;
    end;
   if Sender.fglyphLayout in [ glyphTop ] then
    begin
     RIcon := MakeRect((SenderWidth div 2) - (W div 2),
                       (SenderHeight div 2) - (H + (H div 4)),
                       W, SenderHeight);
     RText.Top := (SenderHeight div 2) + (H div 4);
     HPos := DT_CENTER;
     VPos := DT_TOP;
    end;
   if Sender.fglyphLayout in [ glyphBottom ] then
    begin
     RIcon := MakeRect((SenderWidth div 2) - (W div 2),
                       (SenderHeight div 2) + (H div 4),
                        W, SenderHeight);
     RText.Bottom := (SenderHeight div 2) - (H div 4);
     HPos := DT_CENTER;
     VPos := DT_BOTTOM;
    end;
  end
   else
    begin
     HPos := DT_CENTER;
     VPos := DT_VCENTER;
     RIcon := MakeRect(0, 0, 0, 0);
    end;

 // Getting caption
 S := Sender.fCaption;
 // Getting state
 fState := 1{PBS_NORMAL};
 if not Sender.fEnabled then
  fState := 4{PBS_DISABLED}
  else
 if Sender.fHot then
  fState := 2{PBS_HOT};
 if Sender.fPressed then
  fState := 3{PBS_PRESSED};
 // Opening themes
 hThemes := OpenThemeData(Sender.fHandle, 'button');
 if hThemes <> 0 then
  begin
   Brush := CreateSolidBrush(Color2RGB(Sender.fParent.Color));
   fDC1 := SelectObject(DC, Brush);
   FillRect(DC, RClient, Brush);
   if (Sender.Flat) and (fState = 1{PBS_NORMAL}) then
    begin
     Pen := CreatePen(PS_SOLID, 1, clLtGrey);
     fDC2 := SelectObject(DC, Pen);
     RoundRect(DC, RClient.Left+2, RClient.Top+2, RClient.Right-2, RClient.Bottom-2, 3, 3);
     SelectObject(DC, fDC2);
     DeleteObject(Pen);
    end
     else
      DrawThemeBackground(hThemes, DC, 1{BP_PUSHBUTTON}, fState, RClient, @RClient);
   SelectObject(DC, fDC1);
   DeleteObject(Brush);
   
   if Bmp <> 0 then
    begin
     if Sender.fEnabled then bStyle := ILD_TRANSPARENT else bStyle := ILD_BLEND50;
     ImageList_Draw(Bmp, Sender.BitBtnImgIdx, DC, RIcon.Left, RIcon.Top, bStyle);
    end;
   // Create font
   F := CreateNewFont(Sender);
   fDC1 := SelectObject(DC, F);
   // Draw text
   DrawThemeText(hThemes, DC, 1{BP_PUSHBUTTON}, fState, PWideChar(S), Length(S),
                 HPos or VPos or DT_SINGLELINE, 0, RText);
   // Destroying font
   SelectObject(DC, fDC1);
   DeleteObject(F);

   CloseThemeData(hThemes);
  end;      

 if GetFocus = Sender.fHandle then
  DrawFocusRect(DC, MakeRect(RClient.Left+4, RClient.Top+4, RClient.Right-4, RClient.Bottom-4));
end;
//************************* Control MouseEnter event *************************//
procedure WndXPMouseEnter( Dummy : Pointer; Sender: PObj );
begin
 PControl(Sender).fHot := true;
 if Assigned(PControl(Sender).fOnMouseEnter) and
   (@PControl(Sender).fOnMouseEnter <> @WndXPMouseEnter) then
   PControl(Sender).fOnMouseEnter(Sender);
end;
//************************* Control MouseLeave event *************************//
procedure WndXPMouseLeave( Dummy : Pointer; Sender: PObj );
begin
 PControl(Sender).fHot := false;
 if Assigned(PControl(Sender).fOnMouseLeave) and
   (@PControl(Sender).fOnMouseLeave <> @WndXPMouseLeave) then
   PControl(Sender).fOnMouseLeave(Sender);
end;
//*************************** Control Message event **************************//
function WndXPMessage( Sender: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
var
 pt : TPoint;
 Mouse: TMouseEventData;
begin
 Result := false;

 case Msg.message of
 WM_LBUTTONDBLCLK:
  begin
   if Assigned(Sender.fOnMouseDblClk) then
    begin
     Mouse.Button := mbLeft;
     Mouse.StopHandling := false;
     Mouse.R1 := 0;
     Mouse.R2 := 0;
     Mouse.Shift := 120;
     Mouse.X := 0;
     Mouse.Y := 0;
     GetCursorPos(pt);
     if ScreenToClient(Sender.fHandle, pt) then
      begin
       Mouse.X := pt.X;
       Mouse.Y := pt.Y;
      end;
     Sender.fOnMouseDblClk(Sender, Mouse);
    end;
    if not Sender.fIsSplitter then
     SendMessage( Sender.fHandle, WM_LBUTTONDOWN, Msg.wParam, Msg.lParam );
  end;
  
 WM_LBUTTONDOWN:
  begin
   if Assigned(Sender.fOnMouseDown) then
    begin
     Mouse.Button := mbLeft;
     Mouse.StopHandling := false;
     Mouse.R1 := 0;
     Mouse.R2 := 0;
     Mouse.Shift := 120;
     Mouse.X := 0;
     Mouse.Y := 0;
     GetCursorPos(pt);
     if ScreenToClient(Sender.fHandle, pt) then
      begin
       Mouse.X := pt.X;
       Mouse.Y := pt.Y;
      end;
     Sender.fOnMouseDown(Sender, Mouse);
    end;
   Sender.fPressed := true;
   Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
  end;

 WM_LBUTTONUP:
  begin
   if Assigned(Sender.fOnMouseUp) then
    begin
     Mouse.Button := mbLeft;
     Mouse.StopHandling := false;
     Mouse.R1 := 0;
     Mouse.R2 := 0;
     Mouse.Shift := 120;
     Mouse.X := 0;
     Mouse.Y := 0;
     GetCursorPos(pt);
     if ScreenToClient(Sender.fHandle, pt) then
      begin
       Mouse.X := pt.X;
       Mouse.Y := pt.Y;
      end;
     Sender.fOnMouseUp(Sender, Mouse);
    end;
   Sender.fPressed := false;
   Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
  end;

 WM_KEYDOWN:
  begin
   if Msg.wParam = VK_SPACE then
    begin
     if Assigned(Sender.fOnKeyDown) then
      Sender.fOnKeyDown(Sender, Msg.wParam, GetShiftState);
     Sender.fPressed := true;
     Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
    end;
  end;

 WM_KEYUP:
  begin
   if Msg.wParam = VK_SPACE then
    begin
     if Assigned(Sender.fOnKeyUp) then
      Sender.fOnKeyUp(Sender, Msg.wParam, GetShiftState);
     Sender.fPressed := false;
     Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
    end;
  end;

  WM_KILLFOCUS:
   begin
    Sender.fHot := false;
    Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
   end;

  WM_SETFOCUS:
   begin
    Sender.fHot := true;
    Sender.OnPaint(Sender, GetWindowDC(Msg.hWnd));
    Result := true;
   end;
  end;
end;
//*************************** Events for CheckBox ****************************//
procedure XP_Themes_For_CheckBox(Sender : PControl);
begin
 if AppTheming then
  Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndCheckBoxXPDraw ) );
end;
//*************************** Events for RadioBox ****************************//
procedure XP_Themes_For_RadioBox(Sender : PControl);
begin
 if AppTheming then
  Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndRadioBoxXPDraw ) );
end;
//**************************** Events for Panel ******************************//
procedure XP_Themes_For_Panel(Sender : PControl);
begin
 if AppTheming then
  begin
   if Sender.fedgeStyle = esTransparent then Sender.SetTransparent(True) else
    begin
     Sender.OnResize := TOnEvent( MakeMethod( nil, @WndPanelXPResize ) );
     Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndPanelXPDraw ) );
    end;
  end;
end;
//*************************** Events for Splitter ****************************//
procedure XP_Themes_For_Splitter(Sender : PControl);
begin
 if AppTheming then
  begin
   Sender.AttachProc(WndXPMessage);
   Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndSplitterXPDraw ) );
  end;
end;
//**************************** Events for Label ******************************//
procedure XP_Themes_For_Label(Sender : PControl);
begin
 if AppTheming then Sender.SetTransparent(True);
end;
//************************** Events for GroupBox *****************************//
procedure XP_Themes_For_GroupBox(Sender : PControl);
begin
 if AppTheming then
  Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndGroupBoxXPDraw ) );
end;
//************************** Events for TabPanel *****************************//
procedure XP_Themes_For_TabPanel(Sender : PControl);
begin
 if AppTheming then
  Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndTabXPDraw ) );
end;
//********************* Events for Button and BitButton **********************//
procedure XP_Themes_For_BitBtn(Sender : PControl);
begin
 if AppTheming then
  begin
   Sender.AttachProc(WndXPMessage);
   Sender.OnMouseEnter := TOnEvent( MakeMethod( nil, @WndXPMouseEnter ) );
   Sender.OnMouseLeave := TOnEvent( MakeMethod( nil, @WndXPMouseLeave ) );
   Sender.OnPaint := TOnPaint( MakeMethod( nil, @WndButtonXPDraw ) );
  end;
end;
//*********************** Deattach ownerdraw function ************************//
procedure Deattach(Sender : PControl; PaintProc : Pointer);
begin
 if Sender.IsProcAttached(WndXPMessage) then
  Sender.DetachProc(WndXPMessage);
 if Assigned(Sender.fOnMouseEnter) and (@Sender.fOnMouseEnter = @WndXPMouseEnter) and (not Sender.fFlat) then
  Sender.fOnMouseEnter := nil;
 if Assigned(Sender.fOnMouseLeave) and (@Sender.fOnMouseLeave = @WndXPMouseLeave) and (not Sender.fFlat) then
  Sender.fOnMouseLeave := nil;
 if Assigned(Sender.fOnPaint) and (@Sender.fOnPaint = PaintProc) then
  Sender.fOnPaint := nil;
end;
//********************* Handling of message WM_THEMECHANGED ******************//
function WndXP_WM_THEMECHANGED( Sender: PControl; var Msg: TMsg; var Rslt: Integer ): Boolean;
begin
 Result := false;

 if Msg.message = $31A {WM_THEMECHANGED} then
  begin
   if AppTheming then DeinitThemes;
   CheckThemes;
   if AppTheming then
    begin
     InitThemes;
     if ((Sender.fStyle and BS_AUTOCHECKBOX) = BS_AUTOCHECKBOX) and
        (Sender.SubClassName = 'obj_BUTTON') and
        (Sender.fIsGroupBox = false) and
        (Sender.fIsSplitter = false) and
        (Sender.fIsBitBtn = false) then
      begin
       XP_Themes_For_CheckBox(Sender);
       exit;
      end;
     if ((Sender.fStyle and BS_AUTO3STATE) = BS_AUTO3STATE) and
        (Sender.SubClassName = 'obj_BUTTON') and
        (Sender.fIsGroupBox = false) and
        (Sender.fIsSplitter = false) and
        (Sender.fIsBitBtn = false) then
      begin
       XP_Themes_For_CheckBox(Sender);
       exit;
      end;
     if ((Sender.fStyle and BS_RADIOBUTTON) = BS_RADIOBUTTON) and
        (Sender.SubClassName = 'obj_BUTTON') and
        (Sender.fIsGroupBox = false) and
        (Sender.fIsSplitter = false) and
        (Sender.fIsBitBtn = false) then
      begin
       XP_Themes_For_RadioBox(Sender);
       exit;
      end;
     if ((Sender.fStyle and BS_GROUPBOX) = BS_GROUPBOX) and
        (Sender.SubClassName = 'obj_BUTTON') and
        (Sender.fIsGroupBox = true) and
        (Sender.fIsSplitter = false) and
        (Sender.fIsBitBtn = false) then
      begin
       XP_Themes_For_GroupBox(Sender);
       exit;
      end;
     if (Sender.SubClassName = 'obj_BUTTON') and
        (Sender.fIsGroupBox = false) and
        (Sender.fIsSplitter = false) then
      begin
       XP_Themes_For_BitBtn(Sender);
       exit;
      end;
     if (Sender.SubClassName = 'obj_STATIC') then
      begin
       if Sender.fIsStaticControl > 0 then XP_Themes_For_Label(Sender)
        else
         begin
          if Sender.fIsSplitter then XP_Themes_For_Splitter(Sender)
           else
            begin
             if Sender.fParent.SubClassName = 'obj_SysTabControl32' then
              XP_Themes_For_TabPanel(Sender)
               else
                XP_Themes_For_Panel(Sender);
            end;
         end;
       exit;
      end;
    end
     else
      begin
       if ((Sender.fStyle and BS_AUTOCHECKBOX) = BS_AUTOCHECKBOX) and
          (Sender.SubClassName = 'obj_BUTTON') and
          (Sender.fIsGroupBox = false) and
          (Sender.fIsSplitter = false) and
          (Sender.fIsBitBtn = false) then
        begin
         Deattach(Sender, @WndCheckBoxXPDraw);
         exit;
        end;
       if ((Sender.fStyle and BS_AUTO3STATE) = BS_AUTO3STATE) and
          (Sender.SubClassName = 'obj_BUTTON') and
          (Sender.fIsGroupBox = false) and
          (Sender.fIsSplitter = false) and
          (Sender.fIsBitBtn = false) then
        begin
         Deattach(Sender, @WndCheckBoxXPDraw);
         exit;
        end;
       if ((Sender.fStyle and BS_RADIOBUTTON) = BS_RADIOBUTTON) and
          (Sender.SubClassName = 'obj_BUTTON') and
          (Sender.fIsGroupBox = false) and
          (Sender.fIsSplitter = false) and
          (Sender.fIsBitBtn = false) then
        begin
         Deattach(Sender, @WndRadioBoxXPDraw);
         exit;
        end;
       if ((Sender.fStyle and BS_GROUPBOX) = BS_GROUPBOX) and
          (Sender.SubClassName = 'obj_BUTTON') and
          (Sender.fIsGroupBox = true) and
          (Sender.fIsSplitter = false) and
          (Sender.fIsBitBtn = false) then
        begin
         Deattach(Sender, @WndGroupBoxXPDraw);
         exit;
        end;
       if (Sender.SubClassName = 'obj_BUTTON') and
          (Sender.fIsGroupBox = false) and
          (Sender.fIsSplitter = false) then
        begin
         Deattach(Sender, @WndButtonXPDraw);
         exit;
        end;
       if (Sender.SubClassName = 'obj_STATIC') then
        begin
         if Sender.fIsStaticControl > 0 then
          else
           begin
            if Sender.fIsSplitter then Deattach(Sender, @WndSplitterXPDraw)
             else
              if Sender.fParent.SubClassName = 'obj_SysTabControl32' then
               Deattach(Sender, @WndTabXPDraw)
                else
                 begin
                  Deattach(Sender, @WndPanelXPDraw);
                  case Sender.fedgeStyle of
                   esRaised:
                    begin
                     Sender.fStyle := Sender.fStyle and (not SS_SUNKEN);
                     Sender.fExStyle := Sender.fExStyle and (not WS_EX_STATICEDGE);
                     Sender.fExStyle := Sender.fExStyle or WS_EX_WINDOWEDGE;
                     Sender.fStyle := Sender.fStyle or WS_DLGFRAME;
                    end;
                   esLowered:
                    begin
                     Sender.fStyle := Sender.fStyle and (not WS_DLGFRAME);
                     Sender.fExStyle := Sender.fExStyle or WS_EX_WINDOWEDGE;
                     Sender.fExStyle := Sender.fExStyle or WS_EX_STATICEDGE;
                     Sender.fStyle := Sender.fStyle or SS_SUNKEN;
                    end;
                  else
                   Sender.fStyle := Sender.fStyle and (not SS_SUNKEN) and (not WS_DLGFRAME);
                   Sender.fExStyle := Sender.fExStyle and (not WS_EX_STATICEDGE) or WS_EX_WINDOWEDGE;
                  end;
                 end;
           end;
         Sender.SetTransparent(Sender.fClassicTransparent);
         exit;
        end;
      end;
  end;
end;
//********************* Attaching to message WM_THEMECHANGED *****************//
procedure Attach_WM_THEMECHANGED(Sender : PControl);
begin
 Sender.AttachProc(WndXP_WM_THEMECHANGED);
end;
//********************************* End File *********************************//
