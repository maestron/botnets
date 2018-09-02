#ifndef __INCLUDE_XML_NODE__
#define __INCLUDE_XML_NODE__

#include <stdlib.h>

#ifdef WIN32
#include <tchar.h>
#endif

// Some common types for char set portable code
#ifdef _UNICODE
    #ifndef LPCTSTR
        #define LPCTSTR const unsigned short *
    #endif /* LPCTSTR */
    #ifndef LPTSTR
        #define LPTSTR unsigned short*
    #endif /* LPTSTR */
    #ifndef TCHAR
        #define TCHAR unsigned short
    #endif /* TCHAR */
#else
    #ifndef LPCTSTR
        #define LPCTSTR const char *
    #endif /* LPCTSTR */
    #ifndef LPTSTR
        #define LPTSTR char *
    #endif /* LPTSTR */
    #ifndef TCHAR
        #define TCHAR char
    #endif /* TCHAR */
#endif
#ifndef FALSE
    #define FALSE 0
#endif /* FALSE */
#ifndef TRUE
    #define TRUE 1
#endif /* TRUE */

#ifndef WIN32
#define _T(c) c
#endif

// Enumeration for XML parse errors.
typedef enum XMLError
{
    eXMLErrorNone = 0,
    eXMLErrorMissingEndTag,
    eXMLErrorEmpty,
    eXMLErrorFirstNotStartTag,
    eXMLErrorMissingTagName,
    eXMLErrorMissingEndTagName,
    eXMLErrorNoMatchingQuote,
    eXMLErrorUnmatchedEndTag,
    eXMLErrorUnexpectedToken,
    eXMLErrorInvalidTag,
    eXMLErrorNoElements,
    eXMLErrorFileNotFound,
    eXMLErrorTagNotFound
} XMLError;

// Enumeration used to manage type of data. Use in conjonction with structure XMLNodeContents
typedef enum XMLElementType
{
    eNodeChild=0,
    eNodeAttribute=1,
    eNodeText=2,
    eNodeClear=3,
    eNodeNULL=4
} XMLElementType;

// Structure used to obtain error details if the parse fails.
typedef struct XMLResults
{
    enum XMLError error;
    int  nLine,nColumn;
} XMLResults;

// Structure for XML clear (unformatted) node (usually comments)
typedef struct {
    LPCTSTR lpszOpenTag; LPCTSTR lpszValue; LPCTSTR lpszCloseTag;
} XMLClear;

// Structure for XML attribute.
typedef struct {
    LPCTSTR lpszName; LPCTSTR lpszValue;
} XMLAttribute;

struct XMLNodeContents;

typedef struct XMLNode
{
//  friend class XMLNode;
  protected:
    typedef struct // to allow shallow copy and "intelligent/smart" pointers (automatic delete):
    {
        LPCTSTR       lpszName;        // Element name (=NULL if root)
        int           nChild,          // Num of child nodes
                      nText,           // Num of text fields
                      nClear,          // Num of Clear fields (comments)
                      nAttribute,      // Num of attributes
                      isDeclaration;   // Whether node is an XML declaration - '<?xml ?>'
        XMLNode       *pParent;        // Pointer to parent element (=NULL if root)
        XMLNode       *pChild;         // Array of child nodes
        LPCTSTR       *pText;          // Array of text fields
        XMLClear      *pClear;         // Array of clear fields
        XMLAttribute  *pAttribute;     // Array of attributes
        int           *pOrder;         // order in which the child_nodes,text_fields,clear_fields and
        int  ref_count;
    } XMLNodeData;
    XMLNodeData *d;

    // protected constructor: use one of these four methods to get your first instance of XMLNode:
    //  - parseString
    //  - parseFile
    //  - openFileHelper
    //  - createXMLTopNode
    XMLNode(XMLNode *pParent, LPCTSTR lpszName, int isDeclaration);

  public:

    // You must create your first instance of XMLNode with these 3 parse functions:
    // (see complete explanation of parameters below)

    static XMLNode parseString   (LPCTSTR     lpszXML, LPCTSTR tag=NULL, XMLResults *pResults=NULL);
    static XMLNode parseFile     (const char *lpszXML, LPCTSTR tag=NULL, XMLResults *pResults=NULL);
    static XMLNode openFileHelper(const char *lpszXML, LPCTSTR tag);

    // The tag parameter should be the name of the first tag inside the XML file.
    // If the tag parameter is omitted, the 3 functions return a node that represents
    // the head of the xml document including the declaration term (<? ... ?>).

    // If the XML document is corrupted:
    //   - The "openFileHelper" method will stop execution and display an error message.
    //   - The 2 other methods will initialize the "pResults" variable with some information that
    //     can be used to trace the error.
    // you can have a detailed explanation of the parsing error with this function:

    static LPCTSTR getError(XMLError error);

    LPCTSTR getName();                                     // name of the node
    LPCTSTR getText(int i=0);                              // return ith text field
    int nText();                                           // nbr of text field
    XMLNode getChildNode(int i);                           // return ith child node
    XMLNode getChildNode(LPCTSTR name, int i);             // return ith child node with specific name
                                                           //     (return an empty node if failing)
    XMLNode getChildNode(LPCTSTR name, int *i=NULL);       // return next child node with specific name
                                                           //     (return an empty node if failing)
    int nChildNode(LPCTSTR name);                          // return the number of child node with specific name
    int nChildNode();                                      // nbr of child node
    XMLAttribute getAttribute(int i);                      // return ith attribute
    char isAttributeSet(LPCTSTR name);                     // test if an attribute with a specific name is given
    LPCTSTR getAttribute(LPCTSTR name, int i);             // return ith attribute content with specific name
                                                           //     (return a NULL if failing)
    LPCTSTR getAttribute(LPCTSTR name, int *i=NULL);       // return next attribute content with specific name
                                                           //     (return a NULL if failing)
    int nAttribute();                                      // nbr of attribute
    XMLClear getClear(int i);                              // return ith clear field (comment)
    int nClear();                                          // nbr of clear field
    LPTSTR createXMLString(int nFormat, int *pnSize=NULL); // create XML string starting from current XMLNode
    XMLNodeContents enumContents(int i);                   // enumerate all the different contents (child,text,
                                                           //     clear,attribute) of the current XMLNode. The order
                                                           //     is reflecting the order of the original file/string
    int nElement();                                        // nbr of different contents for current node
    char isEmpty();                                        // is this node Empty?
    char isDeclaration();

// to allow shallow copy:
    ~XMLNode();
    XMLNode(const XMLNode &A);
    XMLNode& operator=( const XMLNode& A );
    static void destroyCurrentBuffer(XMLNodeData *d);

    XMLNode(): d(NULL){};
    static XMLNode emptyXMLNode;
    static XMLClear emptyXMLClear;
    static XMLAttribute emptyXMLAttribute;

    // The following functions allows you to create from scratch a XMLNode structure
    // The strings given as parameters for these methods will be free'd by the XMLNode class:
    static XMLNode createXMLTopNode();
    XMLNode addChild(LPCTSTR lpszName, int isDeclaration=FALSE);
    XMLAttribute *addAttribute(LPCTSTR lpszName, LPCTSTR lpszValuev);
    LPCTSTR addText(LPCTSTR lpszValue);
    XMLClear *addClear(LPCTSTR lpszValue, LPCTSTR lpszOpen, LPCTSTR lpszClose);

private:

    // these are functions used internally (don't bother about them):
    int ParseClearTag(void *pXML, void *pClear);
    int ParseXMLElement(void *pXML);
    void addToOrder(int index, int type);
    static int CreateXMLStringR(XMLNodeData *pEntry, LPTSTR lpszMarker, int nFormat);
    static void *enumContent(XMLNodeData *pEntry,int i, XMLElementType *nodeType);
    static int nElement(XMLNodeData *pEntry);
    static void removeOrderElement(XMLNodeData *d, XMLElementType t, int index);
    static void exactMemory(XMLNodeData *d);
} XMLNode;


// This structure is given by the function "enumContents".
typedef struct XMLNodeContents
{
    // This dictates what's the content of the XMLNodeContent
    enum XMLElementType type;
    // should be an union to access the appropriate data.
    // compiler does not allow union of object with constructor... too bad.
    XMLNode child;
    XMLAttribute attrib;
    LPCTSTR text;
    XMLClear clear;

} XMLNodeContents;

// The 2 following functions are processing strings so that all the characters
// &,",',<,> are replaced by their XML equivalent: &amp;, &quot;, &apos;, &lt;, &gt;.
// The second function ("toXMLStringFast") allows you to re-use the same output
// buffer for all the conversions so that only a few memory allocations are performed.
// If the output buffer is too small to contain the resulting string, it will
// be enlarged. These 2 functions are useful when creating from scratch an
// XML file using printf.
LPTSTR toXMLString(LPCTSTR source);
LPTSTR toXMLStringFast(LPTSTR *destBuffer,int *destSz, LPCTSTR source);
// you should not use this one:
LPTSTR toXMLString(LPTSTR dest,LPCTSTR source);

// duplicate (copy in a new allocated buffer) the source string
LPTSTR stringDup(LPCTSTR source, int cbData=0);

#endif
