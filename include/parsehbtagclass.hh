#ifndef   __PARSEHBTAGCLASS_H__
#define   __PARSEHBTAGCLASS_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagClass : public ParseHBTag
{
public:
  ParseHBTagClass(string tagName, ParseHeaderfile* parser,
		  StyxDomNode* superNode);
  virtual ~ParseHBTagClass(void);
private:
  void		readCode(void);
  void		parseHBComment(string right);
};

#endif /* __PARSEHBTAGCLASS_H__ */
