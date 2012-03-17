#ifndef   __XHB2HTML_H__
#define   __XHB2HTML_H__

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "styx.hh"
#include "xhb.hh"
#include "head2xhb.hh"

#define	LANG_ENG	"eng"
#define	LANG_FR		"fr"

#define	ROOT_HB_DIRECTORY	"hbresult"
#define	HEADERS_DIRECTORY	"headers"

class	Xhb2Html
{
public:
  Xhb2Html(void);
  int	go(StyxDom* dom, const char* outputPath, const char* lang);
private:
  int	currentNbrObjects, currentNbrFunctions, currentNbrGlobals;
  int	currentNbrTypedefs, currentNbrStructs, currentNbrUnions;
  int	currentNbrEnums, currentNbrEnumConsts, currentNbrFuncMacros;
  int	currentNbrConstMacros, currentNbrPublicMethods;
  int	currentNbrPublicData, currentNbrProtectedMethods;
  int	currentNbrProtectedData, currentNbrPrivateMethods;
  int	currentNbrPrivateData;
  int	createDir(const char *lang, vector<StyxDomNode*> nodes,
		  const char* path);
  int	createHeaderDir(const char* lang, string headerName,
			StyxDom* dom, StyxDomNode* node);
  int	createHeaderDirDescription(const char *lang, string headerName,
				   StyxDom* dom, StyxDomNode* node);
  int	createGlobals(const char* lang, string headerName,
		      StyxDom* dom, StyxDomNode* node);
  int	createFunctions(const char* lang, string headerName,
			StyxDom* dom, StyxDomNode* node);
  int	createTypedefs(const char* lang, string headerName,
		       StyxDom* dom, StyxDomNode* node);
  int	createStructs(const char* lang, string headerName,
		      StyxDom* dom, StyxDomNode* node);
  int	createUnions(const char* lang, string headerName,
		     StyxDom* dom, StyxDomNode* node);
  int	createEnums(const char* lang, string headerName,
		     StyxDom* dom, StyxDomNode* node);
  int	createEnumConstants(const char* lang, string headerName,
			    StyxDom* dom, StyxDomNode* node);
  int	createMacroConstants(const char* lang, string headerName,
			     StyxDom* dom, StyxDomNode* node);
  int	createMacroFunctions(const char* lang, string headerName,
			     StyxDom* dom, StyxDomNode* node);
  int	createObjects(const char* lang, string headerName,
		      StyxDom* dom, StyxDomNode* node);
  int	createClass(const char* lang, string headerName, string className,
		    StyxDom* dom, StyxDomNode* node);
  int	createClassPublicMethods(const char *lang, string headerName,
				 string className, StyxDom* dom,
				 StyxDomNode* node);
  int	createClassPublicDatas(const char *lang, string headerName,
			       string className, StyxDom* dom,
			       StyxDomNode* node);
  int	createClassProtectedMethods(const char *lang, string headerName,
				    string className, StyxDom* dom,
				    StyxDomNode* node);
  int	createClassProtectedDatas(const char *lang, string headerName,
				  string className, StyxDom* dom,
				  StyxDomNode* node);
  int	createClassPrivateMethods(const char *lang, string headerName,
				  string className, StyxDom* dom,
				  StyxDomNode* node);
  int	createClassPrivateDatas(const char *lang, string headerName,
				string className, StyxDom* dom,
				StyxDomNode* node);
};

#endif /* __XHB2HTML_H__ */
