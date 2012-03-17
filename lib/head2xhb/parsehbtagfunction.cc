#include "parsehbtagfunction.hh"

ParseHBTagFunction::ParseHBTagFunction(string tagName, ParseHeaderfile* parser,
				       StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagFunction::ParseHBTagFunction(string tagName, ParseHeaderfile* parser,
				       StyxDomNode* superNode, string right)
  : ParseHBTag(tagName, parser, superNode)
{ this->right = right; }

ParseHBTagFunction::~ParseHBTagFunction()
{}

void	ParseHBTagFunction::readTag()
{
  string	s = readWord();

  if (s == HB_DISCUSSION)
    readDiscussion();
  else if (s == HB_ABSTRACT)
    readAbstract();
  else if (s == HB_PARAM)
    readParam();
  else if (s == HB_RESULT || s == HB_RETURN)
    readResult();
  else
    {
      addWarning(HBERROR_BAD_TAG_PRESENT);
      readText(s);
    }
}

void	ParseHBTagFunction::readParam()
{
  ParseHBTag*	tagParse;

  tagParse = new ParseHBTag(XHB_PARAM_TAG, parser, node, true);
  tagParse->parse();
  delete(tagParse);
}

void	ParseHBTagFunction::readResult()
{
  StyxDomNode*	resNode;
  string	resContent;

  resNode = new StyxDomNode(ELEMENT_NODE, XHB_RESULT_TAG, "", true);
  readText(resContent);
  resNode->addAttribute(XHB_DISCUSSION_ATTR, resContent);
  node->addChildNode(resNode);
  //  resNode->setNamespace(node);
}

void	ParseHBTagFunction::readCode()
{
  char	c;
  bool	isBegin = true, isFounded = false, isComplete = false;

  while ((c = getChar()) != EOF)
    {
      if (IS_SPACE(c) && isBegin)
	continue ;
      if (c == SEMI_COLON && isFounded)
	{
	  code += c;
	  isComplete = true;
	  break ;
	}
      else
	{
	  isBegin = false;
	  code = (c == DOUBLE_QUOTE) ? code + BACKSLASH + c : code + c;
	  if ((int)code.find(name) != -1)
	    isFounded = true;
	}
    }
}

void	ParseHBTagFunction::extension()
{
  if (right.size())
    node->addAttribute(XHB_PERMISSION_ATTR, right);
}
