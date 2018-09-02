{$IFDEF VER90}
              {$DEFINE _D2}
              {$DEFINE _D2orD3}
              {$DEFINE _D2orD3orD4}
{$ENDIF}

{$IFDEF VER100}
              {$DEFINE _D3}
              {$DEFINE _D3orHigher}
              {$DEFINE _D2orD3}
              {$DEFINE _D2orD3orD4}
              {$DEFINE _D3orD4}
{$ENDIF}

{$IFDEF VER120}
              {$DEFINE _D3orHigher}
              {$DEFINE _D3orD4}
              {$DEFINE _D4}
              {$DEFINE _D4orHigher}
              {$DEFINE _D2orD3orD4}
{$ENDIF}

{$IFDEF VER130}
              {$DEFINE _D3orHigher}
              {$DEFINE _D4orHigher}
              {$DEFINE _D5}
              {$DEFINE _D5orHigher}
{$ENDIF}

{$IFDEF VER140}
              {$DEFINE _D3orHigher}
              {$DEFINE _D4orHigher}
              {$DEFINE _D5orHigher}
              {$DEFINE _D6}
              {$DEFINE _D6orHigher}
{$ENDIF}

{$IFDEF VER150}
              {$DEFINE _D3orHigher}
              {$DEFINE _D4orHigher}
              {$DEFINE _D5orHigher}
              {$DEFINE _D6orHigher}
              {$DEFINE _D7}
              {$DEFINE _D7orHigher}
{$WARN UNIT_DEPRECATED OFF}
{$WARN SYMBOL_PLATFORM OFF}
{$WARN UNSAFE_TYPE OFF}
{$WARN UNSAFE_CAST OFF}
{$WARN UNSAFE_CODE OFF}
{$ENDIF}

{$IFDEF VER160} // Delphi 8
Delphi version 8 not supported! (delphi 8 is .net only)
{$ENDIF}

{$IFDEF VER170} // Delphi 2005
             {$DEFINE _D3orHigher}
             {$DEFINE _D4orHigher}
             {$DEFINE _D5orHigher}
             {$DEFINE _D6orHigher}
             {$DEFINE _D7}
             {$DEFINE _D7orHigher}
             {$DEFINE _D2005orHigher}
{$WARN UNIT_DEPRECATED OFF}
{$WARN SYMBOL_PLATFORM OFF}
{$WARN UNSAFE_TYPE OFF}
{$WARN UNSAFE_CAST OFF}
{$WARN UNSAFE_CODE OFF}
{$ENDIF}

{$IFDEF VER180} // Delphi 2006
             {$DEFINE _D3orHigher}
             {$DEFINE _D4orHigher}
             {$DEFINE _D5orHigher}
             {$DEFINE _D6orHigher}
             {$DEFINE _D7}
             {$DEFINE _D7orHigher}
             {$DEFINE _D2005orHigher}
             {$DEFINE _D2006orHigher}
{$WARN UNIT_DEPRECATED OFF}
{$WARN SYMBOL_PLATFORM OFF}
{$WARN UNSAFE_TYPE OFF}
{$WARN UNSAFE_CAST OFF}
{$WARN UNSAFE_CODE OFF}
{$ENDIF}

{$IFDEF _D2005orHigher}

  // by Thaddy de Koning:
  {$IFDEF VER185} // Delphi 2007 ( and Highlander )
               {$DEFINE _D3orHigher}
               {$DEFINE _D4orHigher}
               {$DEFINE _D5orHigher}
               {$DEFINE _D6orHigher}
               {$DEFINE _D7}
               {$DEFINE _D7orHigher}
               {$DEFINE _D2005orHigher}
               {$DEFINE _D2006orHigher}
               {$DEFINE _D2007orHigher}
  {$WARN UNIT_DEPRECATED OFF}
  {$WARN SYMBOL_PLATFORM OFF}
  {$WARN UNSAFE_TYPE OFF}
  {$WARN UNSAFE_CAST OFF}
  {$WARN UNSAFE_CODE OFF}
  {$ENDIF}

{$INLINE OFF}
{$ENDIF}

{$IFDEF FPC}
{------------------------------------
by Thaddy de Koning:

FPC version 2.1.1 is very compatible with Delphi and kol now.
You can simply use the $(DELPHI)\source\rtl\win\*.pas files from Delphi 4/5 instead of the prepared files that were needed for 
FPC1.X
 
That is all to have full compatibility.
------------------------------------}
{$DEFINE PAS_VERSION}
{$IFDEF VER2}
 {$DEFINE _D3orHigher}
 {$DEFINE _D4orHigher}
 {$DEFINE _D5orHigher}
 {$DEFINE _D6orHigher}
 {$DEFINE _D7}
 {$DEFINE _D7orHigher}
{$ENDIF}
{$ENDIF}

{$IFNDEF _NOT_KOLCtrlWrapper_}
 {$DEFINE _KOLCtrlWrapper_}
{$ENDIF}

{$IFNDEF _NOT_KOLCtrlWrapper_}
  {$DEFINE _KOLCtrlWrapper_}
{$ENDIF}


