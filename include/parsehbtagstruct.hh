#ifndef   __PARSEHBTAGSTRUCT_H__
#define   __PARSEHBTAGSTRUCT_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagStruct : public ParseHBTag
{
public:
  ParseHBTagStruct(string tagName, ParseHeaderfile* parser,
		   StyxDomNode* superNode);
  virtual ~ParseHBTagStruct(void);
private:
  void		readTag(void);
  void		readField(void);
  void		readCode(void);
};

#endif /* __PARSEHBTAGSTRUCT_H__ */
