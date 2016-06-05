#include "styx_dom.hh"

bool	StyxDom::readFile(char* filename)
{
  if (saxParse(filename) != SAX_STATUS_OK)
    return (false);
  return (true);
}

bool	StyxDom::writeDom(FILE* file)
{
  if (error)
    return (false);
  fprintf(file, "<?xml");
  if (xmlVersion.size())
    fprintf(file, " version=\"%s\"", xmlVersion.c_str());
  if (encoding.size())
    fprintf(file, " encoding=\"%s\"", encoding.c_str());
  if (standalone.size())
    fprintf(file, " standalone=\"%s\"", standalone.c_str());
  fprintf(file, "?>\n");
  documentElement->writeDom(file, 0);
  return (true);
}

void	StyxDom::addNode(StyxDomNode* node)
{
  documentElement->addChildNode(node);
}

StyxDom::StyxDom()
{
  StyxDomNode*	node;

  node = new StyxDomNode(DOCUMENT_NODE, DOCUMENT_NODE_NAME, "", true);
  documentElement = currentParsedNode = node;
  error = false;
}

StyxDom::~StyxDom()
{
  delete(documentElement);
}

vector<StyxDomNode*>	StyxDom::getFromXpath(string path)
{
  vector<StyxDomNode*>	l;

  l.push_back(documentElement->getFirstChild());
  return (getNodesFromXpath(l, path));
}

void	StyxDom::openTagHandler(string name, vector<StyxSaxAttr*> attr)
{
  StyxDomNode*				node;
  vector<StyxSaxAttr*>::iterator	pt;

  node = new StyxDomNode(ELEMENT_NODE, name, "", false);
  for (pt = attr.begin(); pt != attr.end(); pt++)
    {
      node->addAttribute((*pt)->getName(), (*pt)->getValue());
      delete(*pt);
    }

  if (currentParsedNode->getType() == TEXT_NODE)
    {
      currentParsedNode->setComplete(true);
      currentParsedNode->addNextNode(node);
    }
  else
    currentParsedNode->addChildNode(node);
  node->setNamespace(node);
  currentParsedNode = node;
}

void	StyxDom::closeTagHandler(string tagName)
{
  if (currentParsedNode->getType() == TEXT_NODE)
    {
      currentParsedNode->setComplete(true);
      currentParsedNode = currentParsedNode->getParent();
    }
  if (currentParsedNode->getName() != tagName)
    error = true;
  else
    {
      currentParsedNode->setComplete(true);
      currentParsedNode = currentParsedNode->getParent();
    }
  if (error)
    saxStop();
}

void	StyxDom::insideTextHandler(char	c)
{
  StyxDomNode*	node;
  string	s = string("");

  s += c;
  if (currentParsedNode->getType() == TEXT_NODE)
    currentParsedNode->addText(s);
  else
    {
      node = new StyxDomNode(TEXT_NODE, TEXT_NODE_NAME, s, false);
      currentParsedNode->addChildNode(node);
      currentParsedNode = node;
    }
//  currentParsedNode = currentParsedNode->addText(s);
}

void	StyxDom::commentHandler(string content)
{
  StyxDomNode	*node;

  node = new StyxDomNode(COMMENT_NODE, COMMENT_NODE_NAME, content, true);
  if (currentParsedNode->getType() == TEXT_NODE)
    {
      currentParsedNode->setComplete(true);
      currentParsedNode->addNextNode(node);
      currentParsedNode = currentParsedNode->getParent();
    }
  else
    currentParsedNode->addChildNode(node);
}

void	StyxDom::processingInstructionHandler(string target, string content)
{
  StyxDomNode	*node;
  char		*pt;
  char		*pt2;
  char		*res;

  if (target == XML)
    {
      if (content.size() && (pt = (char*)strstr(content.c_str(), XML_VERSION)))
	{
	  if ((pt = strchr(pt, STYX_EQUAL)) &&
	      (pt = strchr(pt, STYX_DOUBLE_QUOTE)) &&
	      (pt2 = strchr(pt + 1, STYX_DOUBLE_QUOTE)))
	    {
	      res = (char*)malloc(pt2 - pt);
	      memcpy(res, pt + 1, pt2 - pt - 1);
	      res[pt2 - pt - 1] = '\0';
	      xmlVersion = string(res);
	      free(res);
	    }
	}
      if (content.size() && (pt = (char*)strstr(content.c_str(), ENCODING)))
	{
	  if ((pt = strchr(pt, STYX_EQUAL)) &&
	      (pt = strchr(pt, STYX_DOUBLE_QUOTE)) &&
	      (pt2 = strchr(pt + 1, STYX_DOUBLE_QUOTE)))
	    {
	      res = (char*)malloc(pt2 - pt);
	      memcpy(res, pt + 1, pt2 - pt - 1);
	      res[pt2 - pt - 1] = '\0';
	      encoding = string(res);
	      free(res);
	    }
	}
      if (content.size() && (pt = (char*)strstr(content.c_str(), STANDALONE)))
	{
	  if ((pt = strchr(pt, STYX_EQUAL)) &&
	      (pt = strchr(pt, STYX_DOUBLE_QUOTE)) &&
	      (pt2 = strchr(pt + 1, STYX_DOUBLE_QUOTE)))
	    {
	      res = (char*)malloc(pt2 - pt);
	      memcpy(res, pt + 1, pt2 - pt - 1);
	      res[pt2 - pt - 1] = '\0';
	      standalone = string(res);
	      free(res);
	    }
	}
    }
  else
    {
      node = new StyxDomNode(PROCESSING_INSTRUCTION_NODE, target,
			     content, true);
      if (currentParsedNode->getType() == TEXT_NODE)
	{
	  currentParsedNode->setComplete(true);
	  currentParsedNode->addNextNode(node);
	  currentParsedNode = currentParsedNode->getParent();
	}
      else
	currentParsedNode->addChildNode(node);
    }
}

void	StyxDom::cdataHandler(string content)
{
  StyxDomNode	*node;

  node = new StyxDomNode(CDATA_SECTION_NODE, CDATA_SECTION_NODE_NAME,
			 content, true);
  if (currentParsedNode->getType() == TEXT_NODE)
    {
      currentParsedNode->setComplete(true);
      currentParsedNode->addNextNode(node);
      currentParsedNode = currentParsedNode->getParent();
    }
  else
    currentParsedNode->addChildNode(node);
}

void	StyxDom::errorHandler(int line)
{
  cout << "Parse error at line : " << line << endl;
  exit(1);
}

vector<StyxDomNode*>	StyxDom::getNodesFromXpath(vector<StyxDomNode*>	l,
						   string path)
{
  const char		*pt = NULL;
  bool			firstChar = true;
  vector<StyxDomNode*>	set;
  vector<StyxDomNode*>::iterator	it;
  string		tmpChar;
  vector<StyxDomNode*>	res;

  if (!l.size())
    return (res);
  for (pt = path.c_str(), firstChar = true; *pt; pt++, firstChar = false)
    {
      if (STYX_IS_SPACE(*pt))
	  continue;
      if (*pt == STYX_SLASH)
	{
	  if (*(pt + 1) == STYX_SLASH)
	    {
	      /* Xpath example : "//foo" */
	      pt++;
	      for (it = l.begin(); it != l.end(); it++)
		set = _merge_vectors(set, (*it)->getDescendantsOrSelf());
	      set = _rm_equals(set);
	      while (l.size()) l.pop_back();
	      l = set;
	      while (set.size()) set.pop_back();
	    }
	  else if (firstChar)
	    {
	      /* Xpath example : "/foo" */
	      for (it = l.begin(); it != l.end(); it++)
		set.push_back((*it)->getRoot());
	      set = _rm_equals(set);
	      while (l.size()) l.pop_back();
	      l = set;
	      while (set.size()) set.pop_back();
	    }
	}
      else if (*pt == STYX_DOT && *(pt + 1) == STYX_DOT)
	{
	  /* Xpath example : ".." */
	  pt++;
	  for (it = l.begin(); it != l.end(); it++)
	    if ((*it)->getParent() &&
		(*it)->getParent()->getType() == ELEMENT_NODE)
	      set.push_back((*it)->getParent());
	  set = _rm_equals(set);
	  while (l.size()) l.pop_back();
	  l = set;
	  while (set.size()) set.pop_back();
	}
      else if (*pt == STYX_AT)
	{
	  /* Xpath examples : "@attribute" or "@*" */
	  pt++;
	  tmpChar = _getNextXpathName(&pt);
	  pt--;
	  if (tmpChar == "")
	    continue;
	  for (it = l.begin(); it != l.end(); it++)
	    set = _merge_vectors(set, (*it)->getAttributes(tmpChar));
	  set = _rm_equals(set);
	  while (l.size()) l.pop_back();
	  l = set;
	  while (set.size()) set.pop_back();
	}
      else
	{
	  while (_xpathContainsPipe(string(pt)))
	    {
	      tmpChar = _getNextXpathName(&pt);
	      for (it = l.begin(); it != l.end(); it++)
		set = _merge_vectors(set, (*it)->getChilds(tmpChar));
	      set = _rm_equals(set);
	      while (*pt == STYX_PIPE || STYX_IS_SPACE(*pt))
		pt++;
	    }
	  tmpChar = _getNextXpathName(&pt);
	  pt--;
	  if (tmpChar == "")
	    return (l);
	  for (it = l.begin(); it != l.end(); it++)
	    set = (*it)->getChilds(tmpChar);
	  while (l.size()) l.pop_back();
	  set = _rm_equals(set);
	  l = set;
	  while (set.size()) set.pop_back();
	}
    }
  return (l);
}

/*
** _xpathContainsPipe()
** Return true if the string contains a '|' charactere, false otherwise
*/
bool	StyxDom::_xpathContainsPipe(string str)
{
  const char*	pt = str.c_str();

  while (STYX_IS_SPACE(*pt))
    pt++;
  while (*pt && *pt != STYX_INF && *pt != STYX_SUP && *pt != STYX_SLASH &&
	 *pt != STYX_INTERROG && *pt != STYX_EXCLAM && *pt != STYX_EQUAL &&
	 *pt != STYX_LEFT_BRACE && *pt != STYX_RIGHT_BRACE &&
	 *pt != STYX_AT && *pt != STYX_PIPE)
    pt++;
  if (*pt == STYX_PIPE)
    return (true);
  return (false);
}

/*
** _getNextXpathName()
** return a copy of the next name in an Xpath string, and put the string pointer
** at the end of the name
*/
string	StyxDom::_getNextXpathName(const char **str)
{
  string	buff;

  while (STYX_IS_SPACE(**str))
    (*str)++;
  while (**str && **str != STYX_INF && **str != STYX_SUP &&
	 **str != STYX_SLASH && **str != STYX_INTERROG &&
	 **str != STYX_EXCLAM && **str != STYX_EQUAL &&
	 **str != STYX_LEFT_BRACE && **str != STYX_RIGHT_BRACE &&
	 **str != STYX_AT && **str != STYX_PIPE)
    {
      if (**str == STYX_OPEN_PAR || **str == STYX_CLOSE_PAR)
	return ("");
      buff += **str;
      (*str)++;
    }
  while (STYX_IS_SPACE(**str))
    (*str)++;
  return (buff);
}

vector<StyxDomNode*>	StyxDom::_rm_equals(vector<StyxDomNode*> l)
{
  vector<StyxDomNode*>			res;
  vector<StyxDomNode*>::iterator	it1;
  vector<StyxDomNode*>::iterator	it2;
  bool					flag;

  if (!l.size())
    return (l);
  for (it1 = l.begin(); it1 != l.end(); it1++)
    {
      if ((it1 + 1) == l.end())
	{
	  res.push_back(*it1);
	  break ;
	}
      flag = false;
      for (it2 = (it1 + 1); it2 != l.end(); it2++)
	if ((*it1) == (*it2))
	  flag = true;
      if (!flag)
	res.push_back(*it1);
    }
  return (res);
}

vector<StyxDomNode*>	StyxDom::_merge_vectors(vector<StyxDomNode*> v1,
						vector<StyxDomNode*> v2)
{
  vector<StyxDomNode*>			res;
  vector<StyxDomNode*>::iterator	it;

  for (it = v1.begin(); it != v1.end(); it++)
    res.push_back(*it);
  for (it = v2.begin(); it != v2.end(); it++)
    res.push_back(*it);
  return (res);
}
