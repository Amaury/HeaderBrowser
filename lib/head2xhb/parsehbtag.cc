#include "parsehbtag.hh"

char	ParseHBTag::getChar() { return (parser->getChar()); }
void	ParseHBTag::seekCur(int offset) { parser->seekCur(offset); }

void	ParseHBTag::parse()
{
  char		c, tmp;
  bool		doLoop = true, endOK = false;

  node = new StyxDomNode(ELEMENT_NODE, tagName, "", true);
  readName();
  node->addAttribute(XHB_ID_ATTR, name);
  while (doLoop)
    {
      if (oneline && name.size() && discussion.size())
	break ;
      while (doLoop &&
	     (c = getChar()) != EOF && (IS_SPACE(c) || c == STAR))
	{
	  if (c == STAR)
	    {
	      if ((tmp = getChar()) == SLASH && discussion != "")
		doLoop = false, endOK = true;
	      else if (tmp == SLASH)
		{
		  addWarning(HBERROR_HBTAG_LESS_DISCUSSION);
		  doLoop = false, endOK = true;
		}
	      else
		seekCur(-1);
	    }
	}
      if (c == EOF)
	{
	  addWarning(HBERROR_HBCOMMENT_NOT_ENDED);
	  doLoop = false;
	}
      else if (c == AT)
	readTag();
      else if (!endOK)
	{
	  seekCur(-1);
	  readDiscussion();
	}
    }
  readCode();
  extension();
  if (abstract.size())
    node->addAttribute(XHB_ABSTRACT_ATTR, abstract);
  if (discussion.size())
    node->addAttribute(XHB_DISCUSSION_ATTR, discussion);
  if (code.size())
    node->addAttribute(XHB_CODE_ATTR, code);
  if (superNode == NULL)
    {
      parser->fileNode->addChildNode(node);
      //      node->setNamespace(node);
    }
  else
    {
      superNode->addChildNode(node);
      //      node->setNamespace(superNode);
    }
}

ParseHBTag::ParseHBTag(string tagName, ParseHeaderfile* parser,
		       StyxDomNode* superNode)
{
  oneline = false;
  this->parser = parser;
  this->tagName = tagName;
  this->superNode = superNode;
}

ParseHBTag::ParseHBTag(string tagName, ParseHeaderfile* parser,
		       StyxDomNode* superNode, bool oneline)
{
  this->oneline = oneline;
  this->parser = parser;
  this->tagName = tagName;
  this->superNode = superNode;
}

ParseHBTag::~ParseHBTag()
{}

void	ParseHBTag::readName() { name = readWord(); }

void	ParseHBTag::readDiscussion() { readText(discussion); }

void	ParseHBTag::readAbstract() { readText(abstract); }

string	ParseHBTag::readWord()
{
  string	word;
  char		c;
  bool		isBegin = true;

  while ((c = getChar()) != EOF)
    {
      if (IS_SPACE(c) && isBegin)
	continue ;
      if (IS_SPACE(c) && word != "")
	return (word);
      isBegin = false;
      if (c == DOUBLE_QUOTE)
	word += BACKSLASH;
      word += c;
      if (word == COMMENT_C_START || word == COMMENT_C_END ||
	  word == COMMENT_CPP)
	{
	  addWarning(HBERROR_EMPTY_HBCOMMENT);
	  return ("");
	}
    }
  return ("");
}

void	ParseHBTag::readText(string& dest)
{
  char		c, tmp;
  string	res;
  bool		firstChar = false;
  bool		lastIsSpace = false;

  dest = (dest == "") ? "" : (dest + " ");
  while ((c = getChar()) != EOF)
    {
      if (IS_SPACE(c) && c == CR)
	{
	  tmp = getChar();
	  seekCur(-1);
	  if (tmp == AT)
	    return ;
	  firstChar = true;
	  continue ;
	}
      else if (IS_SPACE(c))
	{
	  tmp = getChar();
	  seekCur(-1);
	  if (tmp == AT)
	    return ;
	  if (firstChar || lastIsSpace)
	    continue ;
	}
      else if (c == STAR)
	{
	  if ((tmp = getChar()) == SLASH || (tmp == AT && firstChar))
	    {
	      seekCur(-2);
	      return ;
	    }
	  seekCur(-1);
	  if (firstChar)
	    continue ;
	}
      lastIsSpace = (IS_SPACE(c)) ? true : false;
      if (c == DOUBLE_QUOTE)
	res = BACKSLASH;
      else
	res = "";
      res += c;
      dest = (firstChar) ? (dest + " " + res) : (dest + res);
      firstChar = false;
    }
  addWarning(HBERROR_HBCOMMENT_NOT_ENDED);
}

void	ParseHBTag::readTag()
{
  string	s = readWord();

  if (s == HB_DISCUSSION)
    readDiscussion();
  else if (s == HB_ABSTRACT || s == HB_SHORT)
    readAbstract();
  else if (s == HB_SEE || s == HB_REF)
    readSee();
  else
    {
      addWarning(HBERROR_BAD_TAG_PRESENT);
      readText(s);
    }
}

void	ParseHBTag::readSee()
{
  StyxDomNode*	seeNode;
  string	seeContent;

  seeNode = new StyxDomNode(ELEMENT_NODE, XHB_SEE_TAG, "", true);
  readText(seeContent);
  seeNode->addAttribute(XHB_DISCUSSION_ATTR, seeContent);
  node->addChildNode(seeNode);
  //  seeNode->setNamespace(node);
}

void	ParseHBTag::readCode()
{
}

void	ParseHBTag::addWarning(string warning)
{
  parser->addWarning(warning);
}

void	ParseHBTag::extension()
{}
