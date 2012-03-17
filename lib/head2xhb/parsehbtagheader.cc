#include "parsehbtagheader.hh"

ParseHBTagHeader::ParseHBTagHeader(string tagName, ParseHeaderfile* parser,
				   StyxDomNode* superNode)
  : ParseHBTag(tagName, parser, superNode)
{}

ParseHBTagHeader::~ParseHBTagHeader()
{}

void	ParseHBTagHeader::readTag()
{
  string	s;

  s = readWord();
  if (s == HB_DISCUSSION)
    readDiscussion();
  else if (s == HB_ABSTRACT)
    readAbstract();
  else if (s == HB_AUTHOR)
    readAuthor();
  else if (s == HB_VERSION)
    readVersion();
  else if (s == HB_LINK)
    readLink();
  else if (s == HB_SEE || s == HB_REF)
    readSee();
  else
    {
      addWarning(HBERROR_BAD_TAG_PRESENT);
      readText(s);
    }
}

void	ParseHBTagHeader::readAuthor()
{
  StyxDomNode*	authorNode;
  string	authorContent;

  authorNode = new StyxDomNode(ELEMENT_NODE, XHB_AUTHOR_TAG, "", true);
  readText(authorContent);
  authorNode->addAttribute(XHB_DISCUSSION_ATTR, authorContent);
  node->addChildNode(authorNode);
  //  authorNode->setNamespace(node);
}

void	ParseHBTagHeader::readVersion()
{
  StyxDomNode*	versionNode;
  string	versionContent;

  versionNode = new StyxDomNode(ELEMENT_NODE, XHB_VERSION_TAG, "", true);
  readText(versionContent);
  versionNode->addAttribute(XHB_DISCUSSION_ATTR, versionContent);
  node->addChildNode(versionNode);
  //  versionNode->setNamespace(node);
}

void	ParseHBTagHeader::readLink()
{
  StyxDomNode*	linkNode;
  string	linkContent;

  linkNode = new StyxDomNode(ELEMENT_NODE, XHB_LINK_TAG, "", true);
  readText(linkContent);
  linkNode->addAttribute(XHB_DISCUSSION_ATTR, linkContent);
  node->addChildNode(linkNode);
  //  linkNode->setNamespace(node);
}
