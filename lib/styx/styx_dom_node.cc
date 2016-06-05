#include "styx_dom.hh"

StyxDomNode*	StyxDomNode::getRoot()
{
  StyxDomNode*	pt;

  for (pt = this; pt->getParent(); pt = pt->getParent())
    ;
  return (pt);
}

StyxDomNode*	StyxDomNode::getParent() { return (parent); }
StyxDomNode*	StyxDomNode::getFirstChild() { return (firstChild); }
StyxDomNode*	StyxDomNode::getLastChild() { return (lastChild); }
StyxDomNode*	StyxDomNode::nextSibling() { return (next); }
StyxDomNode*	StyxDomNode::prevSibling() { return (prev); }
string		StyxDomNode::getName() { return (name); }
void		StyxDomNode::setValue(string value) { this->value = value; }
DomNodeType	StyxDomNode::getType() { return (type); }
bool		StyxDomNode::getComplete() { return (complete); }

void		StyxDomNode::setComplete(bool complete)
{ this->complete = complete; }

string		StyxDomNode::getValue()
{
  string	result;
  int		i;
  bool		flag = false;

  result = value;
  while ((int)(i = result.find('\\')) != -1)
    {
      if (flag)
	flag = false;
      else
	{
	  if (result[i] == '\\')
	    flag = true;
	  result = result.substr(0, i) +
	    result.substr(i + 1, result.size() - i - 1);
	}
    }
  return (result);
}

StyxDomNode*	StyxDomNode::getNextAttribute()
{
  static StyxDomNode*	pt = attributes;
  StyxDomNode*		pt2;

  if (!attributes)
    return (NULL);
  if (!pt)
    {
      pt = this->attributes;
      return (NULL);
    }
  pt2 = pt;
  pt = pt->next;
  return (pt2);
}

StyxDomNode*	StyxDomNode::addAttribute(string name, string value)
{
  StyxDomNode*	attr;
  StyxDomNode*	pt;

  if (name == XMLNS)
    {  
      addNamespace(name, value);
      setNamespace(this);
      return (NULL);
    }
  attr = new StyxDomNode(ATTRIBUTE_NODE, name, value, true);
  if (!attributes)
    attributes = attr;
  else
    {
      for (pt = attributes; pt->next; pt = pt->next)
        ;
      pt->next = attr;
      attr->prev = pt;
    }
  return (attr);
}

StyxDomNode*	StyxDomNode::addText(string text)
{
  StyxDomNode	*node;

  if (type == TEXT_NODE)
    {
      value += text;
      return (this);
    }
  else
    {
      node = new StyxDomNode(TEXT_NODE, TEXT_NODE_NAME, text, false);
      addChildNode(node);
      return (node);
    }  
}

void	StyxDomNode::addNextNode(StyxDomNode* node)
{
  StyxDomNode*	pt;

  for (pt = this; pt->next; pt = pt->next)
    ;
  pt->next = node;
  node->prev = pt;
  node->parent = this->parent;
  node->document = this->document;
  if (pt->parent)
    pt->parent->lastChild = node;
}

void	StyxDomNode::addChildNode(StyxDomNode* node)
{
  node->parent = this;
  node->document = this->document;
  if (firstChild == NULL)
    {
      firstChild = lastChild = node;
      node->prev = node->next = NULL;
    }
  else
    {
      lastChild->next = node;
      node->prev = lastChild;
      node->next = NULL;
      lastChild = node;
    }
}

StyxDomNode::StyxDomNode(DomNodeType type, string name, string value,
			 bool isComplete)
{
  this->type = type;
  this->name = name;
  this->value = value;
  complete = isComplete;
  next = prev = attributes = firstChild = lastChild = document = NULL;
  namingspace = xmlnsAttributes = NULL;
}

StyxDomNode::~StyxDomNode()
{
  StyxDomNode*	pt;

  while (attributes)
    {
      pt = attributes;
      attributes = pt->next;
      pt->next = pt->prev = NULL;
      if (attributes)
	attributes->prev = NULL;
      delete(pt);
    }
  while (firstChild)
    {
      pt = firstChild;
      firstChild = pt->next;
      pt->next = pt->prev = NULL;
      if (firstChild)
	firstChild->prev = NULL;
      delete(pt);
    }
}

void	StyxDomNode::addNamespace(string name, string uri)
{
  int			index;
  StyxDomNamespace*	ns;
  string		tmp2("");
  string		subname(name, strlen(XMLNS),
				name.size() - strlen(XMLNS));

  if ((index = subname.find(STYX_COLON)) != -1)
    name = name.replace(0, strlen(XMLNS) + 1, tmp2);
  else
    name = "";
  ns = new StyxDomNamespace(this, name, uri);
  if (xmlnsAttributes == NULL)
    xmlnsAttributes = ns;
  else
    xmlnsAttributes->addSibling(ns);
}

void	StyxDomNode::setNamespace(StyxDomNode* ancestor)
{
  StyxDomNamespace*	ns;
  string		tmp;
  string		tmp2;
  int			index;

  if ((index = name.find(STYX_COLON)) == -1)
    index = 0;
  if (ancestor == NULL)
    ancestor = this;
  if (ancestor->xmlnsAttributes)
    {
      for (ns = ancestor->xmlnsAttributes; ns; ns = ns->getNextSibling())
	{
	  tmp = name.substr(0, index);
	  tmp2 = ns->getName().substr(0, index);
	  if (tmp == tmp2)
	    {
	      namingspace = ns;
	      return ;
	    }
	}
    }
  if (ancestor->parent)
    setNamespace(ancestor->getParent());
}

void	StyxDomNode::writeDom(FILE* file, int nbTab)
{
  int	i;

  if (type == DOCUMENT_NODE)
    firstChild->writeDom(file, nbTab);
  if (type == ELEMENT_NODE)
    {
      for (i = 0; i < nbTab; i++)
	fprintf(file, "\t");
      fprintf(file, "<%s", name.c_str());
      writeNamespace(file);
      writeAttr(file);
      if (!firstChild)
	fprintf(file, "/>\n");
      else
	{
	  fprintf(file, ">\n");
	  firstChild->writeDom(file, nbTab + 1);
	  for (i = 0; i < nbTab; i++)
	    fprintf(file, "\t");
	  fprintf(file, "</%s>\n", name.c_str());
	}
      if (next)
	next->writeDom(file, nbTab);
    }
  else if (type == TEXT_NODE)
    {
      for (i = 0; i < nbTab; i++)
	fprintf(file, "\t");
      fprintf(file, "%s\n", value.c_str());
      if (next)
	next->writeDom(file, nbTab);
    }
  else if (type == COMMENT_NODE)
    {
      for (i = 0; i < nbTab; i++)
	fprintf(file, "\t");
      fprintf(file, "<!-- %s -->\n", value.c_str());
      if (next)
	next->writeDom(file, nbTab);
    }
  else if (type == PROCESSING_INSTRUCTION_NODE)
    {
      for (i = 0; i < nbTab; i++)
	fprintf(file, "\t");
      fprintf(file, "<?%s %s?>\n", name.c_str(), value.c_str());
      if (next)
	next->writeDom(file, nbTab);
    }
  else if (type == CDATA_SECTION_NODE)
    {
      for (i = 0; i < nbTab; i++)
	fprintf(file, "\t");
      fprintf(file, "<![CDATA[[%s]]>\n", value.c_str());
      if (next)
	next->writeDom(file, nbTab);
    }
}

/*
** getDescendants()
** return a list of nodes which contains copies of each sons, sons of sons, ...
** of the node
*/
vector<StyxDomNode*>	StyxDomNode::getDescendants()
{
  StyxDomNode*		nodePt;
  vector<StyxDomNode*>	res;

  for (nodePt = firstChild; nodePt; nodePt = nodePt->nextSibling())
    if (nodePt->getType() == ELEMENT_NODE)
      {
	res.push_back(nodePt);
	StyxDom::_merge_vectors(res, nodePt->getDescendants());
      }
  return (res);
}

/*
** _getDescendantOrSelfList() -- INTERNAL FUNCTION
** return a list a nodes which contains a copy of the node, and copies of each
** sons, sons of sons, ... of the node
*/
vector<StyxDomNode*>	StyxDomNode::getDescendantsOrSelf()
{
  vector<StyxDomNode*>	res;

  res.push_back(this);
  StyxDom::_merge_vectors(res, getDescendants());
  return (res);
}

/*
** getAttributesOfNode()
** return a list of attributes matching a name
** if the attribute name parameter is equal to NULL, all attributes are returned
*/
vector<StyxDomNode*>	StyxDomNode::getAttributes(string attrName)
{
  StyxDomNode*		nodePt;
  vector<StyxDomNode*>	res;
  string		strStar;

  strStar += STYX_STAR;
  if (attrName == "" || attrName == strStar)
    attrName = "";
  for (nodePt = attributes; nodePt; nodePt = nodePt->nextSibling())
    if (attrName == "" || attrName == nodePt->getName())
      res.push_back(nodePt);
  return (res);
}

/*
** getChils()
** return a list of childs nodes matching a name
** if the child name parameter is equal to NULL, all childs are returned
** return an empty vector if the node doesn't have any child
*/
vector<StyxDomNode*>	StyxDomNode::getChilds(string childName)
{
  StyxDomNode*		nodePt;
  vector<StyxDomNode*>	res;
  string		strStar;

  strStar += STYX_STAR;
  if (childName == "" || childName == strStar)
    childName = "";
  for (nodePt = firstChild; nodePt; nodePt = nodePt->nextSibling())
    if (nodePt->getType() == ELEMENT_NODE &&
	(childName == "" || childName == nodePt->getName()))
      res.push_back(nodePt);
  return (res);
}

void	StyxDomNode::writeNamespace(FILE *file)
{
  if (namingspace && namingspace->getRootNode() == this)
    {
      fprintf(file, " xmlns");
      if (namingspace->getName().size())
	fprintf(file, ":%s", namingspace->getName().c_str());
      fprintf(file, "=\"%s\"", namingspace->getUri().c_str());
    }
}

void	StyxDomNode::writeAttr(FILE *file)
{
  StyxDomNode	*pt;

  if (attributes == NULL)
    return ;
  for (pt = attributes; pt; pt = pt->next)
    fprintf(file, " %s=\"%s\"", pt->getName().c_str(), pt->getValue().c_str());
}
