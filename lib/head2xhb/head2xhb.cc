#include "head2xhb.hh"

StyxDom*	Head2Xhb::getDom() { return (dom); }

Head2Xhb::Head2Xhb(vector<string> files)
{
  vector<string>::iterator	it;
  StyxDomNode*			hbNode;
  ParseHeaderfile*		parseHeader;

  dom = new StyxDom;
  hbNode = new StyxDomNode(ELEMENT_NODE, XHB_TOPLEVEL_TAG, "", true);
  hbNode->addAttribute(XHB_NAMESPACE_NAME, XHB_NAMESPACE_URI);
  dom->addNode(hbNode);
  parseHeader = new ParseHeaderfile(hbNode);
  for (it = files.begin(); it != files.end(); it++)
    parseHeader->parse(*it);
}

Head2Xhb::~Head2Xhb()
{
  delete(dom);
}
