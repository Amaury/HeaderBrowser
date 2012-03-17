#include "hbresult_void.hh"
#include "headers_index.hh"
#include "functionsdir_title.hh"
#include "properties_list.hh"
#include "functionsdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createFunctions(const char *lang, string headerName,
				  StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allFuncs, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				funcName, funcAbs, funcDisc, funcCode;
  int					i;
  string				paramName, paramValue, funcResult;
  StyxDomNode*				pt;
  bool					isFirstParam = true;

  chdir("functions");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(functionsdir_title[1], file);
  else
    fputs(functionsdir_title[0], file);
  fclose(file);

  allFuncs.push_back(node);
  allFuncs = dom->getNodesFromXpath(allFuncs, XHB_FUNCTION_TAG);
  file = fopen("list.html", "w");
  if (allFuncs.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(properties_list_begin, file);
      for (it = allFuncs.begin(); it != allFuncs.end(); it++)
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
    fprintf(file, functionsdir_description_begin[1], headerName.c_str());
  else
    fprintf(file, functionsdir_description_begin[0], headerName.c_str());
  if (allFuncs.size())
    {
      for (it = allFuncs.begin(); it != allFuncs.end(); it++)
	{
	  attrs = (*it)->getAttributes("");
	  funcName = funcAbs = funcDisc = funcCode = "";
	  for (at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		funcName = (*at)->getValue();
	      else if ((*at)->getName() == XHB_ABSTRACT_ATTR)
		funcAbs = (*at)->getValue();
	      else if ((*at)->getName() == XHB_DISCUSSION_ATTR)
		funcDisc = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		funcCode = (*at)->getValue();
	    }
	  if (funcCode.size() && funcName.size())
	    {
	      if ((i = funcCode.find(funcName)) != -1)
		funcCode = funcCode.substr(0, i) + "<B>" +
		  funcCode.substr(i, funcName.size()) + "</B>" +
		  funcCode.substr(i + funcName.size(),
				  funcCode.size() - (funcName.size() + 1));
	    }
	  fprintf(file, functionsdir_description_inside, funcName.c_str(),
		  funcName.c_str(), funcAbs.c_str(), funcCode.c_str(),
		  funcDisc.c_str());
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_PARAM_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(functionsdir_description_param_begin[1], file);
		  else if (isFirstParam)
		    fputs(functionsdir_description_param_begin[0], file);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file, functionsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(functionsdir_description_param_end, file);
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      if (pt->getName() == XHB_RESULT_TAG)
		{
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    funcResult = (*(attrs.begin()))->getValue();
		  if (funcResult.size() && !strcmp(lang, LANG_FR))
		    fprintf(file, functionsdir_description_result[1],
			    funcResult.c_str());
		  else if (funcResult.size())
		    fprintf(file, functionsdir_description_result[0],
			    funcResult.c_str());
		  break ;
		}
	    }
	}
    }
  fputs(functionsdir_description_end, file);
  fclose(file);

  chdir("..");
  return (1);
}
