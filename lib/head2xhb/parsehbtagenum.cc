#include "parsehbtagenum.hh"

ParseHBTagEnum::ParseHBTagEnum(string tagName, ParseHeaderfile* parser,
			       StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagEnum::~ParseHBTagEnum()
{}

void	ParseHBTagEnum::readTag()
{
  string	s = readWord();

  if (s == HB_DISCUSSION)
    readDiscussion();
  else if (s == HB_ABSTRACT)
    readAbstract();
  else if (s == HB_CONSTANT)
    readConstant();
  else
    {
      addWarning(HBERROR_BAD_TAG_PRESENT);
      readText(s);
    }
}

void	ParseHBTagEnum::readConstant()
{
  ParseHBTag*	tagParse;

  tagParse = new ParseHBTag(XHB_CONSTANT_TAG, parser, node, true);
  tagParse->parse();
  delete(tagParse);
}

void	ParseHBTagEnum::readCode()
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
