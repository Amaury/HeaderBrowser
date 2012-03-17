#include "parsehbtagvar.hh"

ParseHBTagVar::ParseHBTagVar(string tagName, ParseHeaderfile* parser,
			     StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagVar::ParseHBTagVar(string tagName, ParseHeaderfile* parser,
			     StyxDomNode* superNode, string right)
  : ParseHBTag(tagName, parser, superNode)
{
  this->right = right;
}

ParseHBTagVar::~ParseHBTagVar()
{}

void	ParseHBTagVar::readCode(void)
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
	  code += c;
	  if ((int)code.find(name) != -1)
	    isFounded = true;
	}
    }
}

void	ParseHBTagVar::extension()
{
  if (right.size())
    node->addAttribute(XHB_PERMISSION_ATTR, right);
}
