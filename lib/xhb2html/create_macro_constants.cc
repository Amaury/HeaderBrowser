#include "hbresult_void.hh"
#include "headers_index.hh"
#include "macroconstantsdir_title.hh"
#include "properties_list.hh"
#include "macroconstantsdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createMacroConstants(const char *lang, string headerName,
				       StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  FILE					*file2;
  vector<StyxDomNode*>			allDefs, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				defName, defAbs, defDisc, defCode;
  int					i;

  chdir("macro-constants");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(macroconstantsdir_title[1], file);
  else
    fputs(macroconstantsdir_title[0], file);
  fclose(file);

  allDefs.push_back(node);
  allDefs = dom->getNodesFromXpath(allDefs, XHB_DEFINE_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, macroconstantsdir_description_begin[1], headerName.c_str());
  else
    fprintf(file2, macroconstantsdir_description_begin[0], headerName.c_str());
  if (allDefs.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(properties_list_begin, file);
      for (it = allDefs.begin(); it != allDefs.end(); it++)
	{
	  attrs = (*it)->getAttributes("");
	  defName = defAbs = defDisc = defCode = "";
	  for (at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		defName = (*at)->getValue();
	      else if ((*at)->getName() == XHB_ABSTRACT_ATTR)
		defAbs = (*at)->getValue();
	      else if ((*at)->getName() == XHB_DISCUSSION_ATTR)
		defDisc = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		defCode = (*at)->getValue();
	    }
	  if (defCode.size() && defName.size() &&
	      (i = defCode.find(defName)) != -1 && 
	      defCode[i + defName.size()] != OPEN_PAR)
	    {
	      fprintf(file, properties_list_inside,
		      defName.c_str(), defName.c_str());
	      defCode = defCode.substr(0, i) + "<B>" +
		defCode.substr(i, defName.size()) + "</B>" +
		defCode.substr(i + defName.size(),
			       defCode.size() - (defName.size() + 1));
	      fprintf(file2, macroconstantsdir_description_inside,
		      defName.c_str(), defName.c_str(), defAbs.c_str(),
		      defCode.c_str(), defDisc.c_str());
	    }
	}
      fputs(properties_list_end, file);
    }
  fputs(macroconstantsdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}
