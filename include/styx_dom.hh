/*!
 * @header	styx_dom.hh
 * @abstract	DOM parser object definition.
 * @discussion	Contains all types and objects definitions for using a DOM type
 *		parser and XPath access for XML file reading.
 * @author	Amaury Bouchard <amaury@amaury.net>
 * @version	1.0.0 Dec 23 2000
 * @see		styx.hh
 * @see		styx_sax.hh
 */
#ifndef	__STYX_DOM_H__
#define	__STYX_DOM_H__

#include <vector>
#include "styx.hh"
#include "styx_sax.hh"

/*!
 * @typedef	DomNodeType
 * @discussion	Defined type for constant used as DOM nodes type.
 * @constant	VOID_NODE No node type set yet.
 * @constant	ELEMENT_NODE Traditionnal XML tag.
 * @constant	ATTRIBUTE_NODE Attribute node of an existing tag.
 * @constant	TEXT_NODE Explicit or implicit node of text inside an XML tag.
 * @constant	CDATA_SECTION_NODE CDATA tag.
 * @constant	ENTITY_REFERENCE_NODE Node of entity reference. Not used.
 * @constant	ENTITY_NODE Node of entity. Not used.
 * @constant	PROCESSING_INSTRUCTION_NODE Node of processing instruction.
 * @constant	COMMENT_NODE XML comment node.
 * @constant	DOCUMENT_NODE Root XML document.
 * @constant	DOCUMENT_TYPE_NODE Node of document type. Not used.
 * @constant	DOCUMENT_FRAGMENT_NODE Node of document fragment. Not used.
 * @constant	NOTATION_NODE Node for notations. Not used.
 */
typedef enum	DomNodeType_e
{
  VOID_NODE = 0,
  ELEMENT_NODE,
  ATTRIBUTE_NODE,
  TEXT_NODE,
  CDATA_SECTION_NODE,
  ENTITY_REFERENCE_NODE,
  ENTITY_NODE,
  PROCESSING_INSTRUCTION_NODE,
  COMMENT_NODE,
  DOCUMENT_NODE,
  DOCUMENT_TYPE_NODE,
  DOCUMENT_FRAGMENT_NODE,
  NOTATION_NODE
}		DomNodeType;

/* default node name definitions */
/*! @defined TEXT_NODE_NAME Default name of all text nodes. */
#define	TEXT_NODE_NAME			"#text"
/*! @defined CDATA_SECTION_NODE_NAME Default name of CDATA nodes. */
#define	CDATA_SECTION_NODE_NAME		"#cdata-section"
/*! @defined COMMENT_NODE_NAME Default name of comment nodes. */
#define	COMMENT_NODE_NAME		"#comment"
/*! @defined DOCUMENT_NODE_NAME Default name of root document node. */
#define	DOCUMENT_NODE_NAME		"#document"
/*! @defined DOCUMENT_FRAGMENT_NODE_NAME Default name of document fragment. */
#define	DOCUMENT_FRAGMENT_NODE_NAME	"#document-fragment"

class	StyxSax;
class	StyxSaxAttr;
class	StyxDom;
class	StyxDomNode;
class	StyxDomNamespace;

/*!
 * @class	StyxDom
 * @abstract	Document Object Model XML parser object.
 * @discussion	Inherits of StyxSax object. Buid a DOM-tree which contains a
 *		representation of the parsed XML file. Datas could be added, or
 *		retreive by using XPath functionnality.
 */
class		StyxDom : StyxSax
{
public:
  /*!
   * @function	readFile
   *		Do parsing of the given file.
   * @param	filename Name of the XML file to parse.
   * @result	A boolean set to true if the parsing was done without error.
   */
  bool			readFile(char* filename);
  /*!
   * @function	writeDom
   *		Write down a copy of the XML tree to the stream given.
   * @param	file Stream were the XML will be written.
   * @result	A boolean set to true if no error occurs.
   */
  bool			writeDom(FILE* file);
  /*!
   * @function	addNode
   *		Add an XML node at the top level of the DOM document.
   * @param	node A pointer to a StyxDomNode previously created.
   */
  void			addNode(StyxDomNode* node);
  /*!
   * @function	getFromXpath
   *		Search nodes in the DOM representation matching a given XPath
   *		expression.
   * @param	path The XPath expression.
   * @result	An array of pointers to the matching nodes.
   */
  vector<StyxDomNode*>	getFromXpath(string path);
  /*!
   * @function	getNodesFromXpath
   *		Process an XPath expression with a set of nodes.
   * @param	l The set of nodes used to process the XPath expression.
   * @param	path The XPath expression.
   * @result	An array of pointers to StyxDomNode.
   */
  vector<StyxDomNode*>	getNodesFromXpath(vector<StyxDomNode*> l, string path);
  /*!
   * @function	StyxDom
   *		Constructor
   */
  StyxDom(void);
  /*!
   * @function	~StyxDom
   *		Destructor
   */
  ~StyxDom(void);
  /*!
   * @function	_rm_equals
   *		Create a new array of pointers to StyxDomNode, by copying an
   *		existing one, without the double elements.
   * @param	l The inital array.
   * @result	The resulting array.
   */
  static vector<StyxDomNode*>	_rm_equals(vector<StyxDomNode*> l);
  /*!
   * @function	_merge_vectors
   *		Create a new array of pointers to StyxDomNode, by merging two
   *		existing ones.
   * @param	v1 The first array.
   * @param	v2 The second array.
   * @result	The resulting array.
   */
  static vector<StyxDomNode*>	_merge_vectors(vector<StyxDomNode*> v1,
				       vector<StyxDomNode*> v2);
private:
  /*! @var documentElement Pointer to the root document node. */
  StyxDomNode		*documentElement;
  /*! @var currentParsedNode Pointer to the node currently parsed. */
  StyxDomNode		*currentParsedNode;
  /*! @var error Set to true if a parse error occurs. */
  bool			error;
  /*! @var xmlVersion XML version readed in the file. */
  string		xmlVersion;
  /*! @var encoding Character set encoding readed in the file. */
  string		encoding;
  /*! @var standalone Set the using of a DTD. */
  string		standalone;
  /*!
   * @function	openTagHandler
   *		Method called when an open tag is founded by the SAX parser.
   * @param	name Name of the tag.
   * @param	attr All attributes of the node.
   */
  void			openTagHandler(string name, vector<StyxSaxAttr*> attr);
  /*!
   * @function	insideTextHandler
   *		Method called when a character is founded b the SAX parser
   *		between an open and a close tag.
   * @param	c The founded character.
   */
  void			insideTextHandler(char c);
  /*!
   * @function	closeTagHandler
   *		Method called by the SAX parser when a close tag is founded.
   * @param	tagName Name of the tag.
   */
  void			closeTagHandler(string tagName);
  /*!
   * @function	commentHandler
   *		Method called when the SAX parser find an XML comment tag.
   * @param	content The content of the tag.
   */
  void			commentHandler(string content);
  /*!
   * @function	processingInstructionHandler
   *		Method called when a processing instruction tag is founded by
   *		the SAX parser.
   * @param	target Name of the processing instruction's target.
   * @param	content Content of the instruction.
   */
  void			processingInstructionHandler(string target,
						     string content);
  /*!
   * @function	cdataHandler
   *		Method called when a CDATA tag is founded by the SAX parser.
   * @param	content Content of the tag.
   */
  void			cdataHandler(string content);
  /*!
   * @function	errorHandler
   *		Method called by the SAX parser when a parse error occurs.
   * @param	line Line number where the error is placed.
   */
  void			errorHandler(int line);
  /*!
   * @function	_xpathContainsPipe
   *		Used by XPath functions to know if a string contains a '|'.
   * @param	str The string where the pipe is searched.
   * @result	A boolean set to true if a pipe is founded.
   */
  bool			_xpathContainsPipe(string str);
  /*!
   * @function	_getNextXpathName
   *		Used by XPath functions to get the next expression's token.
   * @param	A pointer to the string.
   * @result	A string which contains the token.
   */
  string		_getNextXpathName(const char **str);
};

/*!
 * @class	StyxDomNode
 *		XML node for DOM representation.
 */
class			StyxDomNode
{
public:
  /*!
   * @function	getRoot
   *		Return the older grand-parent node of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getRoot(void);
  /*!
   * @function	getParent
   *		Return the closer parent of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getParent(void);
  /*!
   * @function	getFirstChild
   *		Return a pointer to the first child node of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getFirstChild(void);
  /*!
   * @function	getLastChild
   *		Return a pointer to the last child node of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getLastChild(void);
  /*!
   * @function	nextSibling
   *		Return a pointer to the next sibling node of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		nextSibling(void);
  /*!
   * @function	prevSibling
   *		Return a pointer to the previous sibling node of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		prevSibling(void);
  /*!
   * @function	getName
   *		Return the name of this node.
   * @result	Name string.
   */
  string		getName(void);
  /*!
   * @function	getValue
   *		Return the value of this node.
   * @result	Value string.
   */
  string		getValue(void);
  /*!
   * @function	setValue
   *		Change the value string of this node.
   * @param	value The new value string.
   */
  void			setValue(string value);
  /*!
   * @function	getType
   *		Return the type of the node.
   * @result	A DomNodeType value.
   */
  DomNodeType		getType(void);
  /*!
   * @function	getComplete
   *		Return the complete state of this node. If the value is false,
   *		the tag isn't closed.
   * @result	The current complete state.
   */
  bool			getComplete(void);
  /*!
   * @function	setComplete
   *		Change the value of the complete state of this node. When set
   *		to true, the node is considerate closed.
   * @param	complete The new complete state.
   */
  void			setComplete(bool complete);
  /*!
   * @function	getNextAttribute
   *		Return the next attribute of this node.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getNextAttribute(void);
  /*!
   * @function	addAttribute
   *		Add an attribute node to the attribute's list of this node.
   * @param	name Name of the new attribute.
   * @param	value Value of the new attribute.
   * @result	A pointer to the created StyxDomNode.
   */
  StyxDomNode*		addAttribute(string name, string value);
  /*!
   * @function	addText
   *		Add a text node to the child's list of this node.
   * @param	text The text string of the new node.
   * @result	A pointer to the created StyxDomNode.
   */
  StyxDomNode*		addText(string text);
  /*!
   * @function	addNextNode
   *		Add an existing node as last sibling of this node.
   * @param	node Previously created node which must be added.
   */
  void			addNextNode(StyxDomNode* node);
  /*!
   * @function	addChildNode
   *		Add an existing node as last child of this node.
   * @param	node Previously created node which must be added.
   */
  void			addChildNode(StyxDomNode* node);
  /*!
   * @function	addNamespace
   *		Add a namespace attribute to this node.
   * @param	name Name of the new namespace.
   * @param	uri Universal ressource identifier of the namespace.
   */
  void			addNamespace(string name, string uri);
  /*!
   * @function	setNamespace
   *		Search from the given ancestor the namespace which match the
   *		name of this node, and set the namespace of it.
   * @param	ancestor The node where the searching begins. If set to NULL,
   *		the searching begins with this node.
   */
  void			setNamespace(StyxDomNode* ancestor);
  /*!
   * @function	writeDom
   *		Write this representation of this node to the given file.
   * @param	file Stream where the node will be written.
   * @param	nbTab Number of tabulations at the beginning of the tag.
   */
  void			writeDom(FILE* file, int nbTab);
  /*!
   * @function	getDescendants
   *		Return all descendants of this node.
   * @result	Array of pointers to StyxDomNode.
   */
  vector<StyxDomNode*>	getDescendants(void);
  /*!
   * @function	getDescendantsOrSelf
   *		Return all descendants of this node, plus this node itself.
   * @result	Array of pointers to StyxDomNode.
   */
  vector<StyxDomNode*>	getDescendantsOrSelf(void);
  /*!
   * @function	getAttributes
   *		Return all matching attributes of this node.
   * @param	attrName Name of searched attributes. If set to an empty
   *		string, all attributes will be returned.
   * @result	Array of pointers to StyxDomNode.
   */
  vector<StyxDomNode*>	getAttributes(string attrName);
  /*!
   * @function	getChilds
   *		Return all matching childs of this node.
   * @param	childName Name of searched childs. If set to an empty string,
   *		all childs will be returned.
   * @result	Array of pointers to StyxDomNode.
   */
  vector<StyxDomNode*>	getChilds(string childName);
  /*!
   * @function	StyxDomNode
   *		Constructor
   */
  StyxDomNode(DomNodeType type, string name, string value, bool isComplete);
  /*!
   * @function	~StyxDomNode
   *		Destructor
   */
  ~StyxDomNode(void);
private:
  /*! @var type DomNodeType representing the node type. */
  DomNodeType		type;
  /*! @var complete Boolean showing if the tag is closed or not. */
  bool			complete;
  /*! @var name Character string containing the node name. */
  string		name;
  /*! @var value Character string containing the node value. */
  string		value;
  /*! @var parent Pointer to the parent node of this node. */
  StyxDomNode		*parent;
  /*! @var prev Pointer to the previous sibling node of this node. */
  StyxDomNode		*prev;
  /*! @var next Pointer to the next sibling node of this node. */
  StyxDomNode		*next;
  /*! @var attributes List of the attributes node of this node. */
  StyxDomNode*		attributes;
  /*! @var firstChild Pointer to the first child node of this node. */
  StyxDomNode		*firstChild;
  /*! @var lastChild Pointer to the last child node of this node. */
  StyxDomNode		*lastChild;
  /*! @var document Pointer to the root document node. */
  StyxDomNode		*document;
  /*! @var namingspace Namespace associated to this node. */
  StyxDomNamespace	*namingspace;
  /*! @var xmlnsAttributes List of namespaces declared in this node. */
  StyxDomNamespace	*xmlnsAttributes;
  /*!
   * @function	writeNamespace
   *		Function used by writeDOM() to write this node on a stream.
   * @param	file Stream to write the namespace.
   */
  void			writeNamespace(FILE* file);
  /*!
   * @function	writeAttr
   *		Function used by writeDom() to write this node on a stream.
   * @param	file Stream to write the attributes.
   */
  void			writeAttr(FILE* file);
};

/*!
 * @class	StyxDomNamespace
 *		XML node for namespace representation.
 */
class			StyxDomNamespace
{
public:
  /*!
   * @function	getName
   *		Return the namespace's name.
   * @result	Namespace's name.
   */
  string		getName(void);
  /*!
   * @function	getUri
   *		Return the namespace's uri.
   * @result	Namespace's uri.
   */
  string		getUri(void);
  /*!
   * @function	getNextSibling
   *		Return a pointer to the next sibling of this node in the
   *		namespace list.
   * @result	A pointer to a StyxDomNamespace.
   */
  StyxDomNamespace*	getNextSibling(void);
  /*!
   * @function	addSibling
   *		Add an existing StyxDomNamespace as last sibling of this node.
   * @param	ns A pointer to a previously created StyxDomNamespace.
   */
  void			addSibling(StyxDomNamespace* ns);
  /*!
   * @function	getRootNode
   *		Return a pointer to the node where is declared this namespace.
   * @result	A pointer to a StyxDomNode.
   */
  StyxDomNode*		getRootNode(void);
  /*!
   * @function	StyxDomNamespace
   *		Constructor
   */
  StyxDomNamespace(StyxDomNode* root, string name, string uri);
private:
  /*! @var name Namespace's name. */
  string		name;
  /*! @var uri Namespace's uri. */
  string		uri;
  /*! @var rootNode Pointer to the node where this namespace was declared. */
  StyxDomNode*		rootNode;
  /*! @var prev Pointer to the previous sibling namespace. */
  StyxDomNamespace*	prev;
  /*! @var next Pointer to the next sibling namespace. */
  StyxDomNamespace	*next;
};

#endif /* __STYX_DOM_H__ */
