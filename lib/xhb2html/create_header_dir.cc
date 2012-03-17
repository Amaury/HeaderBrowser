#include "hbresult_void.hh"
#include "headers_index.hh"
#include "headerdir_title.hh"
#include "headerdir_list.hh"
#include "headerdir_content.hh"
#include "headerdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createHeaderDir(const char* lang, string headerName,
				  StyxDom* dom, StyxDomNode* node)
{
  string				headerDir = headerName + ".dir";
  string				tmp, path, name, code;
  FILE*					file;
  int					langId = 0;

  chdir("headers");
  mkdir(headerDir.c_str(), 0755);
  chdir(headerDir.c_str());
  if (this->currentNbrObjects)
    mkdir("objects", 0755);
  if (this->currentNbrFunctions)
    mkdir("functions", 0755);
  if (this->currentNbrGlobals)
    mkdir("globals", 0755);
  if (this->currentNbrTypedefs)
    mkdir("typedefs", 0755);
  if (this->currentNbrStructs)
    mkdir("structs", 0755);
  if (this->currentNbrUnions)
    mkdir("unions", 0755);
  if (this->currentNbrEnums)
    mkdir("enums", 0755);
  if (this->currentNbrEnumConsts)
    mkdir("enum-constants", 0755);
  if (this->currentNbrConstMacros)
    mkdir("macro-constants", 0755);
  if (this->currentNbrFuncMacros)
    mkdir("macro-functions", 0755);

  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  fprintf(file, headerdir_title, headerName.c_str());
  fclose(file);

  file = fopen("list.html", "w");
  if (!strcmp(lang, LANG_FR))
    langId = 1;
  else
    langId = 0;
  fprintf(file, headerdir_list[langId],
	  this->currentNbrObjects ? DIRLIST_OBJECTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrObjects ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrObjects ? DIRLIST_OBJECTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrObjects ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrObjects ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrFunctions ? DIRLIST_FUNCTIONS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrFunctions ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrFunctions ? DIRLIST_FUNCTIONS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrFunctions ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrFunctions ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrGlobals ? DIRLIST_GLOBALS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrGlobals ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrGlobals ? DIRLIST_GLOBALS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrGlobals ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrGlobals ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrTypedefs ? DIRLIST_TYPEDEFS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrTypedefs ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrTypedefs ? DIRLIST_TYPEDEFS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrTypedefs ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrTypedefs ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrStructs ? DIRLIST_STRUCTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrStructs ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrStructs ? DIRLIST_STRUCTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrStructs ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrStructs ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrUnions ? DIRLIST_UNIONS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrUnions ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrUnions ? DIRLIST_UNIONS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrUnions ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrUnions ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrEnums ? DIRLIST_ENUMS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrEnums ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrEnums ? DIRLIST_ENUMS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrEnums ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrEnums ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrEnumConsts ? DIRLIST_ENUMCONSTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrEnumConsts ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrEnumConsts ? DIRLIST_ENUMCONSTS_INDEX : DIRLIST_NOTHING,
	  this->currentNbrEnumConsts ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrEnumConsts ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrConstMacros ? DIRLIST_CONSTMACRO_INDEX : DIRLIST_NOTHING,
	  this->currentNbrConstMacros ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrConstMacros ? DIRLIST_CONSTMACRO_INDEX : DIRLIST_NOTHING,
	  this->currentNbrConstMacros ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrConstMacros ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrFuncMacros ? DIRLIST_FUNCMACRO_INDEX : DIRLIST_NOTHING,
	  this->currentNbrFuncMacros ? "</A>" : DIRLIST_NOTHING,
	  this->currentNbrFuncMacros ? DIRLIST_FUNCMACRO_INDEX : DIRLIST_NOTHING,
	  this->currentNbrFuncMacros ? DIRLIST_VIEW_IMG_PATH : DIRLIST_NOTHING,
	  this->currentNbrFuncMacros ? "</A>" : DIRLIST_NOTHING);
  fclose(file);

  file = fopen("content.html", "w");
  tmp = (*((node->getAttributes(XHB_CONTENT_ATTR)).begin()))->getValue();
  if (!strcmp(lang, LANG_FR))
    fprintf(file, headerdir_content[1], headerName.c_str(), tmp.c_str());
  else
    fprintf(file, headerdir_content[0], headerName.c_str(), tmp.c_str());
  fclose(file);

  if (!createHeaderDirDescription(lang, headerName, dom, node))
    return (0);

  return (1);
}

int	Xhb2Html::createHeaderDirDescription(const char* lang, string headerName,
				   StyxDom* dom, StyxDomNode* node)
{
  vector<StyxDomNode*>	l;
  StyxDomNode*		headerNode;
  StyxDomNode*		pt;
  FILE*			file;
  string		id, abstract, discussion;
  string		seeStr, linkStr, authorStr, tmpStr;
  int			i, j;

  l.push_back(node);
  l = dom->getNodesFromXpath(l, XHB_HEADER_TAG);
  file = fopen("description.html", "w");
  if (l.size() == 0)
    {
      if (!strcmp(lang, LANG_FR))
	fprintf(file, headerdir_description_null[1], headerName.c_str(),
		headerName.c_str());
      else
	fprintf(file, headerdir_description_null[0], headerName.c_str(),
		headerName.c_str());
      fclose(file);
      return (1);
    }
  headerNode = *(l.begin());
  id = (*((headerNode->getAttributes(XHB_ID_ATTR)).begin()))->getValue();
  l = headerNode->getAttributes(XHB_ABSTRACT_ATTR);
  if (l.size())
    abstract = (*(l.begin()))->getValue();
  l = headerNode->getAttributes(XHB_DISCUSSION_ATTR);
  if (l.size())
    discussion = (*(l.begin()))->getValue();
  fprintf(file, headerdir_description_begin, headerName.c_str(),
	  headerName.c_str());
  if (abstract.size())
    {
      if (!strcmp(lang, LANG_FR))
	fprintf(file, headerdir_description_abstract[1], abstract.c_str());
      else
	fprintf(file, headerdir_description_abstract[0], abstract.c_str());
    }
  if (discussion.size())
    fprintf(file, headerdir_description_discussion, discussion.c_str());
  
  for (pt = headerNode->getFirstChild(); pt; pt = pt->nextSibling())
    {
      if (pt->getName() == XHB_VERSION_TAG)
	{
	  l = pt->getAttributes(XHB_DISCUSSION_ATTR);
	  if (l.size() && !strcmp(lang, LANG_FR))
	    fprintf(file, headerdir_description_version[1],
		    (*(l.begin()))->getValue().c_str());
	  else if (l.size())
	    fprintf(file, headerdir_description_version[0],
		    (*(l.begin()))->getValue().c_str());
	  break ;
	}
    }

  for (pt = headerNode->getFirstChild(); pt; pt = pt->nextSibling())
    {
      if (pt->getName() == XHB_SEE_TAG)
	{
	  l = pt->getAttributes(XHB_DISCUSSION_ATTR);
	  if (l.size())
	    seeStr = seeStr + (*(l.begin()))->getValue() + "<BR>\n";
	}
      else if (pt->getName() == XHB_LINK_TAG)
	{
	  l = pt->getAttributes(XHB_DISCUSSION_ATTR);
	  if (l.size())
	    {
	      tmpStr = (*(l.begin()))->getValue();
	      if ((int)(i = tmpStr.find(INF)) != -1 &&
		  (j = tmpStr.rfind(SUP)) > i)
		{
		  tmpStr = "<A HREF=\"" +
		    tmpStr.substr(i + 1, j - i - 1) + "\">" +
		    tmpStr.substr(0, i) + "</A>\n";
		}
	      linkStr = linkStr + tmpStr + "<BR>";
	    }
	}
      else if (pt->getName() == XHB_AUTHOR_TAG)
	{
	  l = pt->getAttributes(XHB_DISCUSSION_ATTR);
	  if (l.size())
	    {
	      tmpStr = (*(l.begin()))->getValue();
	      if ((int)(i = tmpStr.find(INF)) != -1 &&
		  (j = tmpStr.rfind(SUP)) > i)
		{
		  tmpStr = tmpStr.substr(0, i) + "<A HREF=\"mailto:" +
		    tmpStr.substr(i + 1, j - i - 1) + "\">" +
		    tmpStr.substr(i + 1, j - i - 1) + "</A>\n";
		}
	      authorStr = authorStr + tmpStr + "<BR>\n";
	    }
	}
    }
  if (seeStr.size() && !strcmp(lang, LANG_FR))
    fprintf(file, headerdir_description_see[1], seeStr.c_str());
  else if (seeStr.size())
    fprintf(file, headerdir_description_see[0], seeStr.c_str());
  if (linkStr.size())
    {
      if (!strcmp(lang, LANG_FR))
	fputs(headerdir_description_link_begin[1], file);
      else
	fputs(headerdir_description_link_begin[0], file);
      fputs(linkStr.c_str(), file);
      fputs(headerdir_description_link_end, file);
    }
  if (authorStr.size())
    {
      if (!strcmp(lang, LANG_FR))
	fputs(headerdir_description_author[1], file);
      else
	fputs(headerdir_description_author[0], file);
      fputs(authorStr.c_str(), file);
    }

  fputs(headerdir_description_end, file);
  fclose(file);
  return (1);
}
