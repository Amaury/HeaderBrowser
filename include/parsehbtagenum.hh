#ifndef   __PARSEHBTAGENUM_H__
#define   __PARSEHBTAGENUM_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagEnum : public ParseHBTag
{
public:
  ParseHBTagEnum(string tagName, ParseHeaderfile* parser,
		 StyxDomNode* superNode);
  virtual ~ParseHBTagEnum(void);
private:
  void		readTag(void);
  void		readConstant(void);
  void		readCode(void);
};

#endif /* __PARSEHBTAGENUM_H__ */
