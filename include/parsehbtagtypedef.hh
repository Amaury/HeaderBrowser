#ifndef   __PARSEHBTAGTYPEDEF_H__
#define   __PARSEHBTAGTYPEDEF_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagTypedef : public ParseHBTag
{
public:
  ParseHBTagTypedef(string tagName, ParseHeaderfile* parser,
		    StyxDomNode* superNode);
  virtual ~ParseHBTagTypedef(void);
private:
  void		readTag(void);
  void		readField(void);
  void		readConstant(void);
  void		readParam(void);
  void		readCode(void);
};

#endif /* __PARSEHBTAGTYPEDEF_H__ */
