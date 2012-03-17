#include "parsehbtagdefine.hh"

ParseHBTagDefine::ParseHBTagDefine(string tagName, ParseHeaderfile* parser,
				   StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagDefine::~ParseHBTagDefine()
{}

void	ParseHBTagDefine::readCode()
{
  char  c, tmp;
  bool  isBegin = false, isFounded = false;
 
  for (isBegin = true; (c = getChar()) != EOF; )
    {
      if (IS_SPACE(c) && isBegin)
        continue ;
      if (c == CR && isFounded)
        break ;
      if (c == BACKSLASH)
        {
          if ((tmp = getChar()) == EOF)
            {
              c = tmp;
              break ;
            }
          else if (tmp == CR)
            {
              this->code = this->code + c + tmp;
              continue;
            }
          else
            seekCur(-1);
        }
      isBegin = false;
      code = (c == DOUBLE_QUOTE) ? code + BACKSLASH + DOUBLE_QUOTE : code + c;
      if ((int)code.find(name) != -1)
        isFounded = true;
    }
}
