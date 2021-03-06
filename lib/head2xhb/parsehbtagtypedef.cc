#include "parsehbtagtypedef.hh"

ParseHBTagTypedef::ParseHBTagTypedef(string tagName, ParseHeaderfile* parser,
				     StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagTypedef::~ParseHBTagTypedef()
{}

void	ParseHBTagTypedef::readTag()
{
  string	s = readWord();

  if (s == HB_DISCUSSION)
    readDiscussion();
  else if (s == HB_ABSTRACT)
    readAbstract();
  else if (s == HB_FIELD)
    readField();
  else if (s == HB_CONSTANT)
    readConstant();
  else if (s == HB_PARAM)
    readParam();
  else
    {
      addWarning(HBERROR_BAD_TAG_PRESENT);
      readText(s);
    }
}

void	ParseHBTagTypedef::readField()
{
  ParseHBTag*	tagParse;

  tagParse = new ParseHBTag(XHB_FIELD_TAG, parser, node, true);
  tagParse->parse();
  delete(tagParse);
}

void	ParseHBTagTypedef::readConstant()
{
  ParseHBTag*	tagParse;

  tagParse = new ParseHBTag(XHB_CONSTANT_TAG, parser, node, true);
  tagParse->parse();
  delete(tagParse);
}

void	ParseHBTagTypedef::readParam()
{
  ParseHBTag*	tagParse;

  tagParse = new ParseHBTag(XHB_PARAM_TAG, parser, node, true);
  tagParse->parse();
  delete(tagParse);
}

void	ParseHBTagTypedef::readCode()
{
  char  c;
  int   nbAccolades = 0;
  bool  isBegin = false, isFounded = false;
 
  for (isBegin = true; (c = getChar()) != EOF; )
    {
      if (IS_SPACE(c) && isBegin)
        continue ;
      if (c == SEMI_COLON && isFounded && !nbAccolades)
        {
          this->code += c;
          break ;
        }
      else
        {
          if (c == LEFT_ACCOLADE)
            nbAccolades++;
          else if (c == RIGHT_ACCOLADE)
            nbAccolades--;
          isBegin = false;
          code = (c == DOUBLE_QUOTE) ? code + BACKSLASH + c : code + c;
          if ((int)code.find(name) != -1)
            isFounded = true;
        }
    }
}
