#include "styx_sax.hh"

StyxSax::StyxSax()
{
  line = 1;
  charac = 1;
}

StyxSax::~StyxSax()
{
  if (file)
    fclose(file);
}

void	StyxSax::saxStop() { saxStatus = SAX_STATUS_STOPPED; }

void	StyxSax::setStatus(StyxSaxStatus newStatus) { saxStatus = newStatus; }

char	StyxSax::getChar()
{
  char	c;

  if ((c = (char)fgetc(file)) == STYX_CR)
    {
      charac = 1;
      line++;
    }
  else if (c != EOF)
    charac++;
  return (c);
}

void	StyxSax::ungetChar(char c)
{
  ungetc(c, file);
  charac--;
  if (!charac)
    line--;
}

StyxSaxStatus	StyxSax::saxParse(char* filename)
{
  char	c;
  char	last = 0;
  bool	insideChar = false;

  if ((file = fopen(filename, "r")) == NULL)
    return (saxStatus = SAX_STATUS_NO_FILE);
  saxStatus = SAX_STATUS_OK;
  while ((c = getChar()) != EOF && saxStatus == SAX_STATUS_OK)
    {
      if (STYX_IS_SPACE(c))
	last = c;
      else if (c == STYX_INF)
	{
	  doOpenTag();
	  insideChar = false;
	  last = 0;
	}
      else if (c == STYX_SUP)
	{
	  setStatus(SAX_STATUS_ERR_PARSE);
	  errorHandler(line);
	  return (SAX_STATUS_ERR_PARSE);
	}
      else
	{
	  if (insideChar && STYX_IS_SPACE(last))
	    insideTextHandler(last);
	  insideChar = true;
	  insideTextHandler(c);
	  last = c;
	}
    }
  return (saxStatus);
}

/*
** doOpenTag()
** function called when an open tag is found
*/
void	StyxSax::doOpenTag()
{
  char	c;

  if ((c = getChar()) == EOF)
    SAX_ERR_RETURN;
  if (c == STYX_INTERROG)
    parseProcessingInstruction();
  else if (c == STYX_EXCLAM)
    {
      if ((c = getChar()) == EOF)
	SAX_ERR_RETURN;
      if (c == STYX_MINUS)
	parseComment();
      else if (c == STYX_LEFT_BRACE)
	parseCdata();
    }
  else if (c == STYX_SLASH)
    parseCloseTag();
  else
    {
      ungetChar(c);
      parseOpenTag();
    }
}

void			StyxSax::parseOpenTag()
{
  string		nameBuff;
  string		attrNameBuff;
  string		attrValueBuff;
  vector<StyxSaxAttr*>	attrs;
  char			c;
  bool			getName = true;
  bool			getAttrName = false;
  bool			getAttrValue = false;

  while ((c = getChar()) != EOF)
    {
      if (!STYX_IS_SPACE(c))
	{
	  if (c == STYX_INF)
	    SAX_ERR_RETURN
	  else if (c == STYX_SLASH)
	    {
	      if ((c = getChar()) == EOF || c != STYX_SUP)
		SAX_ERR_RETURN;
	      openTagHandler(nameBuff, attrs);
	      closeTagHandler(nameBuff);
	      return ;
	    }
	  else if (c == STYX_SUP)
	    {
	      if (!nameBuff.size())
		SAX_ERR_RETURN;
	      openTagHandler(nameBuff, attrs);
	      return ;
	    }
	  else if (c == STYX_EQUAL)
	    {
	      if (!getName && getAttrName && !getAttrValue)
		{
		  getAttrName = false;
		  getAttrValue = true;
		  while ((c = getChar()) != EOF)
		    if (!STYX_IS_SPACE(c))
		      break;
		  if (c != STYX_DOUBLE_QUOTE)
		    SAX_ERR_RETURN;
		}
	      else
		SAX_ERR_RETURN;
	    }
	  else
	    {
	      if (getName)
		nameBuff += c;
	      else if (getAttrName)
		attrNameBuff += c;
	      else if (getAttrValue)
		{
		  ungetChar(c);
		  while ((c = getChar()) != EOF &&
			 c != STYX_DOUBLE_QUOTE)
		    attrValueBuff += c;
		  attrs.push_back(new StyxSaxAttr(attrNameBuff, attrValueBuff));
		}
	    }
	}
      else
	{
	  if (nameBuff.size() && getName && !getAttrName)
	    {
	      getName = false;
	      getAttrName = true;
	      attrNameBuff = "";
	      attrValueBuff = "";
	    }
	  else if (!getAttrName && getAttrValue)
	    {
	      getAttrName = true;
	      getAttrValue = false;
	      attrNameBuff = "";
	      attrValueBuff = "";
	    }
	}
    }
  SAX_ERR_RETURN;
}

void	StyxSax::parseCloseTag()
{
  string	nameBuff;
  bool		findSpace = false;
  bool		findChar = false;
  char		c;

  while ((c = getChar()) != EOF)
    {
      if (STYX_IS_SPACE(c))
	findSpace = true;
      else if (c == STYX_INF)
	SAX_ERR_RETURN
      else if (c == STYX_SUP)
	{
	  if (!nameBuff.size())
	    SAX_ERR_RETURN;
	  closeTagHandler(nameBuff);
	  return ;
	}
      else
	{
	  if (findChar && findSpace)
	    SAX_ERR_RETURN;
	  findChar = true;
	  nameBuff += c;
	}
    }
  SAX_ERR_RETURN;
}

void	StyxSax::parseProcessingInstruction()
{
  char		c;
  string	target;
  string	content;

  while ((c = getChar()) != EOF && c != STYX_INTERROG && !STYX_IS_SPACE(c))
    target += c;

  if (c == STYX_INTERROG && (c = getChar()) != EOF && c == STYX_SUP)
    {
      processingInstructionHandler(target, "");
      return ;
    }

  while ((c = getChar()) != EOF && c != STYX_INTERROG)
    content += c;

  if (c == EOF)
    SAX_ERR_RETURN;
  if ((c = getChar()) == EOF || c != STYX_SUP)
    SAX_ERR_RETURN;
  processingInstructionHandler(target, content);
}

void	StyxSax::parseComment()
{
  char		c, next;
  string	s;

  if ((c = getChar()) == EOF || c != STYX_MINUS)
    SAX_ERR_RETURN;
  while ((c = getChar()) != EOF)
    {
      if (c != STYX_MINUS)
	s += c;
      else if (c == STYX_MINUS && (next = getChar()) != EOF &&
	       next == STYX_MINUS)
	break ;
      else
	s = s + c + next;
    }
  if ((c = getChar()) == EOF || c != STYX_SUP)
    SAX_ERR_RETURN;
  commentHandler(s);
}

void	StyxSax::parseCdata()
{
  char		c;
  char*		pt;
  unsigned int	i;
  string	content;

  pt = CDATA;
  for (i = 0; i < strlen(CDATA); i++)
    if ((c = getChar()) == EOF || c != *(pt + i))
      SAX_ERR_RETURN;
  if ((c = getChar()) == EOF || c != STYX_LEFT_BRACE)
    SAX_ERR_RETURN;

  while ((c = getChar()) != EOF && c != STYX_RIGHT_BRACE)
    content +=  c;
  if ((c = getChar()) == EOF || c != STYX_RIGHT_BRACE ||
      (c = getChar()) == EOF || c != STYX_SUP)
    SAX_ERR_RETURN;
  cdataHandler(content);
}

void	StyxSax::openTagHandler(string name, vector<StyxSaxAttr*> attrs)
{
  vector<StyxSaxAttr*>::iterator	it = attrs.begin();

  cout << "<" << name;
  for (; it != attrs.end(); it++)
    {
      cout << " " << (*it)->getName();
      cout << "=\"" << (*it)->getValue() << "\"";
    }
  cout << ">" << endl;
}

void	StyxSax::closeTagHandler(string name)
{
  cout << "</" << name << ">" << endl;
}

void	StyxSax::insideTextHandler(char c)
{
  cout << c;
}

void	StyxSax::commentHandler(string content)
{
  cout << "<!-- " << content << " -->" << endl;
}

void	StyxSax::processingInstructionHandler(string target, string content)
{
}

void	StyxSax::cdataHandler(string content)
{
}

void	StyxSax::errorHandler(int line)
{
  cout << "Error line " << line << endl;
}
