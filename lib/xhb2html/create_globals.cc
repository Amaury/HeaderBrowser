#include "hbresult_void.hh"
#include "headers_index.hh"
#include "globalsdir_title.hh"
#include "properties_list.hh"
#include "globalsdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createGlobals(const char* lang, string headerName,
				StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allVars;
  vector<StyxDomNode*>::iterator	it, at;
  vector<StyxDomNode*>			attrs;
  string				str, varName, varAbs, varDisc, varCode;
  int					i;

  chdir("globals");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(globalsdir_title[1], file);
  else
    fputs(globalsdir_title[0], file);
  fclose(file);

  allVars.push_back(node);
  allVars = dom->getNodesFromXpath(allVars, XHB_VAR_TAG);
  file = fopen("list.html", "w");
  if (allVars.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(properties_list_begin, file);
      for (it = allVars.begin(); it != allVars.end(); it++)
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
    fprintf(file, globalsdir_description_begin[1], headerName.c_str());
  else
    fprintf(file, globalsdir_description_begin[0], headerName.c_str());
  if (allVars.size())
    {
      for (it = allVars.begin(); it != allVars.end(); it++)
	{
	  attrs = (*it)->getAttributes("");
	  varName = varAbs = varDisc = varCode = "";
	  for (at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		varName = (*at)->getValue();
	      else if ((*at)->getName() == XHB_ABSTRACT_ATTR)
		varAbs = (*at)->getValue();
	      else if ((*at)->getName() == XHB_DISCUSSION_ATTR)
		varDisc = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		varCode = (*at)->getValue();
	    }
	  if (varCode.size() && varName.size())
	    {
	      if ((i = varCode.find(varName)) != -1)
		varCode = varCode.substr(0, i) + "<B>" +
		  varCode.substr(i, varName.size()) + "</B>" +
		  varCode.substr(i + varName.size(),
				 varCode.size() - (varName.size() + 1));
	    }
	  fprintf(file, globalsdir_description_inside, varName.c_str(),
		  varName.c_str(), varAbs.c_str(), varCode.c_str(),
		  varDisc.c_str());
	}
    }
  fputs(globalsdir_description_end, file);
  fclose(file);

  chdir("..");
  return (1);
}
