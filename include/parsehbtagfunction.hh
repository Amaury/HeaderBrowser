#ifndef   __PARSEHBTAGFUNCTION_H__
#define   __PARSEHBTAGFUNCTION_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagFunction : public ParseHBTag
{
public:
  ParseHBTagFunction(string tagName, ParseHeaderfile* parser,
		     StyxDomNode* superNode);
  ParseHBTagFunction(string tagName, ParseHeaderfile* parser,
		     StyxDomNode* superNode, string right);
  virtual ~ParseHBTagFunction(void);
private:
  string	right;
  void		readTag(void);
  void		readParam(void);
  void		readResult(void);
  void		readCode(void);
  void		extension(void);
};

#endif /* __PARSEHBTAGFUNCTION_H__ */
