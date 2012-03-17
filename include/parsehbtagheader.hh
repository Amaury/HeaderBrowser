#ifndef   __PARSEHBTAGHEADER_H__
#define   __PARSEHBTAGHEADER_H__

#include "styx.hh"
#include "definitions.h"
#include "parseheaderfile.hh"
#include "xhb.hh"
#include "parsehbtag.hh"

class	ParseHBTag;
class	ParseHeaderfile;

class	ParseHBTagHeader : public ParseHBTag
{
public:
  ParseHBTagHeader(string tagName, ParseHeaderfile* parser,
		   StyxDomNode* superNode);
  virtual ~ParseHBTagHeader(void);
private:
  void		readTag(void);
  void		readAuthor(void);
  void		readVersion(void);
  void		readLink(void);
};

#endif /* __PARSEHBTAGHEADER_H__ */
