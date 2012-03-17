#include "styx_dom.hh"

string			StyxDomNamespace::getName() { return (name); }
string			StyxDomNamespace::getUri() { return (uri); }
StyxDomNamespace*	StyxDomNamespace::getNextSibling() { return (next); }

void	StyxDomNamespace::addSibling(StyxDomNamespace* ns)
{
  StyxDomNamespace*	pt;

  for (pt = this; pt->next; pt = pt->next)
    ;
  pt->next = ns;
  ns->prev = pt;
}

StyxDomNode*	StyxDomNamespace::getRootNode() { return (rootNode); }

StyxDomNamespace::StyxDomNamespace(StyxDomNode* root, string name, string uri)
{
  rootNode = root;
  this->name = name;
  this->uri = uri;
}
