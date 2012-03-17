#include "parsehbtagclass.hh"

ParseHBTagClass::ParseHBTagClass(string tagName, ParseHeaderfile* parser,
				 StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagClass::~ParseHBTagClass()
{}

void	ParseHBTagClass::readCode()
{
  char		c;
  string	word, inherits;
  string	currentRight("private");
  int		nbAccolades = 0;

  // swap the first spaces
  while ((c = getChar()) != EOF && IS_SPACE(c))
    ;
  seekCur(-1);
  // search the declaration of the class
  while ((word = readWord()) != "" && word != name)
    ;
  if (word == "")
    {
      addWarning(HBERROR_CLASS_NOT_FIND);
      return ;
    }
  // swap spaces
  while ((c = getChar()) != EOF && IS_SPACE(c))
    ;
  if (c == COLON)
    {
      while ((c = getChar()) != EOF && IS_SPACE(c))
	;
      inherits += c;
      // get inheritance
      while ((c = getChar()) != EOF && c != LEFT_ACCOLADE)
	inherits += (IS_SPACE(c)) ? SPACE : c;
      if (inherits != "")
	node->addAttribute(XHB_INHERITS_ATTR, inherits);
    }
  if (c == EOF)
    {
      addWarning(HBERROR_CLASS_NOT_ENDED);
      return ;
    }
  if (c == LEFT_ACCOLADE)
    nbAccolades++;
  for (word = ""; (c = getChar()) != EOF; )
    {
      if (!IS_SPACE(c))
	{
	  if (c == SEMI_COLON && !nbAccolades)
	    break ;
	  else
	    {
	      if (c == COLON)
		currentRight = word;
	      else
		word = (c == DOUBLE_QUOTE) ? word + BACKSLASH + c : word + c;
	      if (c == LEFT_ACCOLADE)
		nbAccolades++;
	      else if (c == RIGHT_ACCOLADE)
		nbAccolades--;
	      if (c == COLON || c == LEFT_ACCOLADE || c == RIGHT_ACCOLADE)
		word = "";
	    }
	  continue ;
	}
      else if (word == COMMENT_HB_START || word == COMMENT_JAVADOC_START)
	parseHBComment(currentRight);
      word = "";
    }
}

void	ParseHBTagClass::parseHBComment(string right)
{
  string	word;
  char		c;
  ParseHBTag*	hbTagParser;

  while ((c = getChar()) != EOF)
    {
      if (c == AT)
	{
	  word = "";
	  while ((c = getChar()) != EOF && !IS_SPACE(c))
	    word += c;
	  if (word == HB_FUNCTION)
	    hbTagParser = new ParseHBTagFunction(XHB_FUNCTION_TAG, parser,
						 node, right);
	  else if (word == HB_VAR)
	    hbTagParser = new ParseHBTagVar(XHB_VAR_TAG, parser, node, right);
	  else
	    {
	      addWarning(HBERROR_UNKNOWN_TAG);
	      return ;
	    }
	  hbTagParser->parse();
	  delete(hbTagParser);
	  return ;
	}
      if (IS_SPACE(c))
	word = "";
      else
	word += c;
      if (word == COMMENT_C_END)
	{
	  addWarning(HBERROR_EMPTY_HBCOMMENT);
	  return ;
	}
    }
  addWarning(HBERROR_HBCOMMENT_NOT_ENDED);
}
