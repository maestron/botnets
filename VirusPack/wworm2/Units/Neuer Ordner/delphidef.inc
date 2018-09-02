//{$DEFINE _FPC}
{$DEFINE ASM_VERSION} // Comment this line to produce Pascal code.
                      // Or, just add PAS_VERSION to conditionals
                      // of your project (must be rebuilt).

{$IFDEF ASM_VERSION}
  {$IFDEF PAS_VERSION}
    {$UNDEF ASM_VERSION}
    // To compile a project with ASM_VERSION option turned off,
    // define a symbol PAS_VERSION in project options.
  {$ENDIF}
{$ENDIF}

{$I KOLDEF.INC}

//{$DEFINE USE_CONSTRUCTORS}
// Comment this line to produce smaller code if constructors are not used.
// When uncommented, this definition allows to create descendant controls
// and objects overriding constructors, which are actually members of objects.
// Otherwise, global functions (usually named New<ObjectName>) are used to
// create and initialize object instances. This gives smaller code, but
// prevents from using OOP inheritance.
// Note: creating descendant objects derived from TObj does not require using
// of this option. It is actually needed only for deriving new controls on
// base of TControl. See also option USE_CUSTOMEXTENSIONS below.

//{$DEFINE USE_CUSTOMEXTENSIONS}
// Uncomment this option or add it to your project conditional defines,
// if You wish to extend existing TControl object from
// the inner of those. When this option is turned on, include directive at the
// tail of TControl declaration is enabled, causing a compiler to include your
// portion of source directly into the TControl body. See comments near this
// directive there. (Search the word: USE_CUSTOMEXTENSIONS).
// Please note, that this option is not fully supported now.

{$IFNDEF NOT_UNLOAD_RICHEDITLIB}
  {$DEFINE UNLOAD_RICHEDITLIB}
{$ENDIF}
// You can freely comment this directive. 1st, if the application does not
// use richedit control. 2nd, even if it does, freeing the library handle
// actually is not needed.
// Another way to turn this option off is to define symbol NOT_UNLOAD_RICHEDITLIB
// in your project options.

//{$DEFINE TEST_VERSION}
{$DEFINE PARANOIA} //seems not needed under D6 !!! Inprise fixed this, finally... :)