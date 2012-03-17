#ifndef   __PARSEHEADERFILE_H__
#define   __PARSEHEADERFILE_H__

#include <stdio.h>
#include "styx.hh"
#ifndef __PARSEHBTAG_H__
# include "parsehbtag.hh"
# include "parsehbtagclass.hh"
# include "parsehbtagdefine.hh"
# include "parsehbtagenum.hh"
# include "parsehbtagfunction.hh"
# include "parsehbtagheader.hh"
# include "parsehbtagstruct.hh"
# include "parsehbtagtypedef.hh"
# include "parsehbtagvar.hh"
#endif

#define	HBERROR_CCOMMENT_NOT_ENDED	"C comment not ended"
#define	HBERROR_HBCOMMENT_NOT_ENDED	"HB comment not ended"
#define	HBERROR_EMPTY_HBCOMMENT		"Empty HB comment"
#define	HBERROR_UNKNOWN_TAG		"Unknown tag"
#define	HBERROR_HBTAG_LESS_DISCUSSION	"HB tag without discussion"
#define	HBERROR_BAD_TAG_PRESENT		"Bad HB tag present"
#define	HBERROR_CLASS_NOT_FIND		"Class definition not find"
#define	HBERROR_CLASS_NOT_ENDED		"Class definition not ended"

class	ParseHBTag;

class	ParseHeaderfile
{
  friend	ParseHBTag;
public:
  void		parse(string filename);
  ParseHeaderfile(StyxDomNode* documentNode);
private:
  StyxDomNode*	xmlDocumentNode;
  string	filename;
  FILE*		file;
  StyxDomNode*	fileNode;
  int		nbChar;
  int		nbLine;
  char		getChar(void);
  void		seekCur(int offset);
  void		parseGeneral(void);
  void		parseHBComment(void);
  void		parseHBCComment(void);
  void		parseHBCppComment(void);
  void		addWarning(string warning);
  void		readInsideFile(void);
};

#endif /* __PARSEHEADERFILE_H__ */
