#ifndef   __PARSEHBTAGVAR_H__
#define   __PARSEHBTAGVAR_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagVar : public ParseHBTag
{
public:
  ParseHBTagVar(string tagName, ParseHeaderfile* parser,
		StyxDomNode* superNode);
  ParseHBTagVar(string tagName, ParseHeaderfile* parser,
		StyxDomNode* superNode, string right);
  virtual ~ParseHBTagVar(void);
private:
  string	right;
  void		readCode(void);
  void		extension(void);
};

#endif /* __PARSEHBTAGVAR_H__ */
