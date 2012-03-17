#ifndef   __PARSEHBTAG_H__
#define   __PARSEHBTAG_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"

class	ParseHeaderfile;

class	ParseHBTag
{
public:
  void			parse(void);
  ParseHBTag(string tagName, ParseHeaderfile* parser, StyxDomNode* superNode);
  ParseHBTag(string tagName, ParseHeaderfile* parser, StyxDomNode* superNode,
	     bool oneline);
  virtual ~ParseHBTag(void);
protected:
  StyxDomNode*		superNode;
  StyxDomNode*		node;
  ParseHeaderfile*	parser;
  void			readDiscussion(void);
  void			readAbstract(void);
  void			readSee(void);
  virtual void		readTag(void);
  virtual void		readCode(void);
  virtual void		extension(void);
  string		readWord(void);
  void			readText(string& dest);
  void			addWarning(string warning);
  char			getChar(void);
  void			seekCur(int offset);
  string		name;
  string		code;
private:
  bool			oneline;
  string		tagName;
  string		discussion;
  string		abstract;
  void			readName(void);
};

#endif /* __PARSEHBTAG_H__ */
