// Desirable Compiler options
{$B-} // Full boolean eval off (i.e. Short-cicuit boolean eval)

{ DbxOpenOdbc compiles under
 Delphi        V6.00, V6.01, V6.02, V7.00
 Kylix         V1(?), V2(?), V3(?)
 C++ Builder   V6(?)
}
{
CompilerVersion
(taken from http://www.blong.com/Tips/KylixTips.htm)
Delphi 5; Kylix 1; C++ Builder 5; or any earlier version: CompilerVersion NOT DEFINED
Delphi 6.00:   14.01
Delphi 6.01:   14.01
Delphi 6.02:   14.01
C++Builder 6:  14.01
Kylix 2:       14.10
Kylix 3:       14.50
Delphi 7:      15.00
}

{$IFDEF CONDITIONALEXPRESSIONS}
{$DEFINE _K1UP_}
{$IF Declared(CompilerVersion)}
{$IF CompilerVersion >= 14.01}
// Delphi 6.00 and up
{$DEFINE _D6UP_}
{$IFEND}
{$IF CompilerVersion >= 14.10}
// Kylix 2 and up
{$DEFINE _K2UP_}
{$IFEND}
{$IF CompilerVersion >= 14.50}
// Kylix 3 and up
// Kylix 3 supports something somewhere between D6 and D7
{$DEFINE _K3UP_}
{$IFEND}
{$IF CompilerVersion >= 15.00}
// Delphi 7.00 and up
{$DEFINE _D7UP_}
{$IFEND}
{$IFEND} // of: $IF Declared(CompilerVersion)
{$ELSE}  // of: $IFDEF CONDITIONALEXPRESSIONS
{$MESSAGE ERROR 'Compiler must be one of the following, or higher: Delphi 6; C++ Builder 6; Kylix 1'}
{$ENDIF}


{$UNDEF DynamicOdbcImport}
//{$DEFINE DynamicOdbcImport} // optional: It allows to use odbc libraries directly, passing odbc manager.

{$IFDEF DynamicOdbcImport}
  {$UNDEF UnloadApiCache}
  {$DEFINE UnloadApiCache} // optional: allow reload odbc api library
{$ENDIF}

{$DEFINE _iOdbcApi_}
{$DEFINE _FIX_PostgreSQL_ODBC_}// fixed: PostgreSQL ODBC driver charset conversion bug.
                               //   Driver supported only utf8 charsets for odbc api
                               //   function "SQLBindParameter".

