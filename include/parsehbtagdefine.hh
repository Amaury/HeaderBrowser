#ifndef   __PARSEHBTAGDEFINE_H__
#define   __PARSEHBTAGDEFINE_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagDefine : public ParseHBTag
{
public:
  ParseHBTagDefine(string tagName, ParseHeaderfile* parser,
		   StyxDomNode* superNode);
  virtual ~ParseHBTagDefine();
private:
  void		readCode(void);
};

#endif /* __PARSEHBTAGDEFINE_H__ */
