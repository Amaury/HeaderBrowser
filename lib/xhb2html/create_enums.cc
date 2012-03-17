#include "hbresult_void.hh"
#include "headers_index.hh"
#include "enumsdir_title.hh"
#include "properties_list.hh"
#include "enumsdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createEnums(const char *lang, string headerName,
			      StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allStructs, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				structName, structAbs;
  string				structDisc, structCode;
  int					i;
  StyxDomNode*				pt;
  bool					isFirstParam = true;
  string				paramName, paramValue;

  chdir("enums");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(enumsdir_title[1], file);
  else
    fputs(enumsdir_title[0], file);
  fclose(file);

  allStructs.push_back(node);
  allStructs = dom->getNodesFromXpath(allStructs, XHB_ENUM_TAG);
  file = fopen("list.html", "w");
  if (allStructs.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(properties_list_begin, file);
      for (it = allStructs.begin(); it != allStructs.end(); it++)
	{
	  attrs = (*it)->getAttributes(XHB_ID_ATTR);
	  if (attrs.size())
	    fprintf(file, properties_list_inside,
		    (*(attrs.begin()))->getValue().c_str(),
		    (*(attrs.begin()))->getValue().c_str());
	}
      fputs(properties_list_end, file);
    }
  fclose(file);

  file = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file, enumsdir_description_begin[1], headerName.c_str());
  else
    fprintf(file, enumsdir_description_begin[0], headerName.c_str());
  if (allStructs.size())
    {
      for (it = allStructs.begin(); it != allStructs.end(); it++)
	{
	  attrs = (*it)->getAttributes("");
	  structName = structAbs = structDisc = structCode = "";
	  for (at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		structName = (*at)->getValue();
	      else if ((*at)->getName() == XHB_ABSTRACT_ATTR)
		structAbs = (*at)->getValue();
	      else if ((*at)->getName() == XHB_DISCUSSION_ATTR)
		structDisc = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		structCode = (*at)->getValue();
	    }
	  if (structCode.size() && structName.size())
	    {
	      if ((i = structCode.find(structName)) != -1)
		structCode = structCode.substr(0, i) + "<B>" +
		  structCode.substr(i, structName.size()) + "</B>" +
		  structCode.substr(i + structName.size(), structCode.size() -
				    (structName.size() + 1));
	    }
	  fprintf(file, enumsdir_description_inside, structName.c_str(),
		  structName.c_str(), structAbs.c_str(), structCode.c_str(),
		  structDisc.c_str());
	  // get the constants
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_CONSTANT_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(enumsdir_description_constant_begin[1], file);
		  else if (isFirstParam)
		    fputs(enumsdir_description_constant_begin[0], file);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file, enumsdir_description_constant_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(enumsdir_description_constant_end, file);
	}
    }
  fputs(enumsdir_description_end, file);
  fclose(file);

  chdir("..");
  return (1);
}
