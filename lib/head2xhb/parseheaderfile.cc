#include "xhb.hh"
#include "definitions.h"
#include "parseheaderfile.hh"

void	ParseHeaderfile::parse(string filename)
{
  int	i;

  this->filename = "";
  file = NULL;
  fileNode = NULL;
  nbChar = 1;
  nbLine = 1;
  if ((file = fopen(filename.c_str(), "r")) == NULL)
    {
      fileNode = new StyxDomNode(ELEMENT_NODE, XHB_ERROR_TAG, "", true);
      fileNode->addAttribute(XHB_ID_ATTR, "No file");
      fileNode->addAttribute(XHB_FILE_ATTR, filename);
    }
  else
    {
      this->filename = filename;
      if ((i = (int)filename.rfind("/")) != -1)
	filename = filename.substr(i + 1, filename.size() - i - 1);
      fileNode = new StyxDomNode(ELEMENT_NODE, XHB_HEADERFILE_TAG, "", true);
      fileNode->addAttribute(XHB_ID_ATTR, filename);
      parseGeneral();
      readInsideFile();
    }
  xmlDocumentNode->addChildNode(fileNode);
  //  fileNode->setNamespace(xmlDocumentNode);
}

void	ParseHeaderfile::readInsideFile()
{
  FILE*		file;
  char		c, c2, c3;
  string	res;

  file = fopen(filename.c_str(), "r");
  while ((c = fgetc(file)) != EOF)
    {
      if (c == SLASH)
	{
	  if ((c2 = fgetc(file)) == STAR)
	    {
	      if ((c3 = fgetc(file)) == EXCLAM)
		{
		  while (1)
		    {
		      if ((c = fgetc(file)) == EOF)
			break ;
		      else if (c == STAR)
			{
			  if ((c2 = fgetc(file)) == EOF)
			    break;
			  else if (c2 == SLASH)
			    break ;
			  else
			    ungetc(c2, file);
			}
		    }
		}
	      else
		{
		  res += c;
		  res += c2;
		  res += c3;
		}
	    }
	  else
	    {
	      res += c;
	      res += c2;
	    }
	}
      else if (c == DOUBLE_QUOTE)
	res = res + BACKSLASH + c;
      else if (c == BACKSLASH)
	res = res + c + c;
      else
	res += c;
    }
  fclose(file);
  fileNode->addAttribute(XHB_CONTENT_ATTR, res);
}

ParseHeaderfile::ParseHeaderfile(StyxDomNode* documentNode)
{
  xmlDocumentNode = documentNode;
}

char	ParseHeaderfile::getChar()
{
  char		c;

  if (!file || (c = (char)fgetc(file)) == EOF)
    return (EOF);
  if (c == CR)
    {
      nbLine++;
      nbChar = 1;
    }
  else
    nbChar++;
  return (c);
}

void	ParseHeaderfile::seekCur(int offset)
{
  if (!file)
    return ;
  fseek(file, offset, SEEK_CUR);
  nbChar += offset;
  if (nbChar <= 0)
    nbLine--;
}

void	ParseHeaderfile::parseGeneral()
{
  string	word;
  char		c;

  while ((c = getChar()) != EOF)
    {
      if (!IS_SPACE(c))
	{
	  word += c;
	  continue ;
	}
      else if (word == COMMENT_C_START)
	parseHBCComment();
      else if (word == COMMENT_HB_START || word == COMMENT_JAVADOC_START)
	parseHBComment();
      else if (word == COMMENT_CPP)
	parseHBCppComment();
      word = "";
    }
}

void	ParseHeaderfile::parseHBComment()
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
	  if (word == HB_HEADER || word == HB_PACKAGE)
	    hbTagParser = new ParseHBTagHeader(XHB_HEADER_TAG, this, NULL);
	  else if (word == HB_VAR)
	    hbTagParser = new ParseHBTagVar(XHB_VAR_TAG, this, NULL);
	  else if (word == HB_FUNCTION)
	    hbTagParser = new ParseHBTagFunction(XHB_FUNCTION_TAG, this, NULL);
	  else if (word == HB_STRUCT)
	    hbTagParser = new ParseHBTagStruct(XHB_STRUCT_TAG, this, NULL);
	  else if (word == HB_UNION)
	    hbTagParser = new ParseHBTagStruct(XHB_UNION_TAG, this, NULL);
	  else if (word == HB_ENUM)
	    hbTagParser = new ParseHBTagEnum(XHB_ENUM_TAG, this, NULL);
	  else if (word == HB_TYPEDEF)
	    hbTagParser = new ParseHBTagTypedef(XHB_TYPEDEF_TAG, this, NULL);
	  else if (word == HB_DEFINED || word == HB_DEFINE)
	    hbTagParser = new ParseHBTagDefine(XHB_DEFINE_TAG, this, NULL);
	  else if (word == HB_CLASS)
	    hbTagParser = new ParseHBTagClass(XHB_CLASS_TAG, this, NULL);
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

void	ParseHeaderfile::parseHBCComment()
{
  char		c;
  string	word;

  while ((c = getChar()) != EOF)
    {
      if (IS_SPACE(c) && word == COMMENT_C_END)
	return ;
      if (IS_SPACE(c))
	word = "";
      else
	word += c;
    }
  if (word == COMMENT_C_END)
    return ;
  addWarning(HBERROR_CCOMMENT_NOT_ENDED);
}

void	ParseHeaderfile::parseHBCppComment()
{
  char	c;

  while ((c = getChar()) != EOF && c != CR)
    ;
}

void	ParseHeaderfile::addWarning(string warning)
{
  StyxDomNode*	node;
  char		buff[9];

  sprintf(buff, "%d", nbLine);
  node = new StyxDomNode(ELEMENT_NODE, XHB_WARNING_TAG, "", true);
  node->addAttribute(XHB_ID_ATTR, warning);
  node->addAttribute(XHB_FILE_ATTR, filename);
  node->addAttribute(XHB_LINE_ATTR, buff);
  xmlDocumentNode->addChildNode(node);
  //  node->setNamespace(xmlDocumentNode);
}
