#include "hbresult_void.hh"
#include "headers_index.hh"
#include "typedefsdir_title.hh"
#include "properties_list.hh"
#include "typedefsdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createTypedefs(const char *lang, string headerName,
				 StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allTyps, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				typName, typAbs, typDisc, typCode;
  int					i;
  StyxDomNode*				pt;
  bool					isFirstParam = true;
  string				paramName, paramValue;

  chdir("typedefs");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(typedefsdir_title[1], file);
  else
    fputs(typedefsdir_title[0], file);
  fclose(file);

  allTyps.push_back(node);
  allTyps = dom->getNodesFromXpath(allTyps, XHB_TYPEDEF_TAG);
  file = fopen("list.html", "w");
  if (allTyps.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(properties_list_begin, file);
      for (it = allTyps.begin(); it != allTyps.end(); it++)
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
    fprintf(file, typedefsdir_description_begin[1], headerName.c_str());
  else
    fprintf(file, typedefsdir_description_begin[0], headerName.c_str());
  if (allTyps.size())
    {
      for (it = allTyps.begin(); it != allTyps.end(); it++)
	{
	  attrs = (*it)->getAttributes("");
	  typName = typAbs = typDisc = typCode = "";
	  for (at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		typName = (*at)->getValue();
	      else if ((*at)->getName() == XHB_ABSTRACT_ATTR)
		typAbs = (*at)->getValue();
	      else if ((*at)->getName() == XHB_DISCUSSION_ATTR)
		typDisc = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		typCode = (*at)->getValue();
	    }
	  if (typCode.size() && typName.size())
	    {
	      if ((i = typCode.find(typName)) != -1)
		typCode = typCode.substr(0, i) + "<B>" +
		  typCode.substr(i, typName.size()) + "</B>" +
		  typCode.substr(i + typName.size(),
				 typCode.size() - (typName.size() + 1));
	    }
	  fprintf(file, typedefsdir_description_inside, typName.c_str(),
		  typName.c_str(), typAbs.c_str(), typCode.c_str(),
		  typDisc.c_str());
	  // get the fields
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_FIELD_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(typedefsdir_description_field_begin[1], file);
		  else if (isFirstParam)
		    fputs(typedefsdir_description_field_begin[0], file);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file, typedefsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(typedefsdir_description_param_end, file);
	  // get the constants
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_CONSTANT_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(typedefsdir_description_constant_begin[1], file);
		  else if (isFirstParam)
		    fputs(typedefsdir_description_constant_begin[0], file);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file, typedefsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(typedefsdir_description_param_end, file);
	  // get the parameters
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_PARAM_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(typedefsdir_description_param_begin[1], file);
		  else if (isFirstParam)
		    fputs(typedefsdir_description_param_begin[0], file);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file, typedefsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(typedefsdir_description_param_end, file);
	}
    }
  fputs(typedefsdir_description_end, file);
  fclose(file);

  chdir("..");
  return (1);
}
