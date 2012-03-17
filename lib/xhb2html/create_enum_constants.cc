#include "hbresult_void.hh"
#include "headers_index.hh"
#include "enumconstantsdir_title.hh"
#include "enumconstantsdir_content.hh"
#include "xhb2html.hh"

int	Xhb2Html::createEnumConstants(const char* lang, string headerName,
				      StyxDom* dom, StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allStructs, attrs;
  vector<StyxDomNode*>::iterator	it;
  string				enumName, enumCstName;
  StyxDomNode*				pt;

  chdir("enum-constants");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(enumconstantsdir_title[1], file);
  else
    fputs(enumconstantsdir_title[0], file);
  fclose(file);

  allStructs.push_back(node);
  allStructs = dom->getNodesFromXpath(allStructs, XHB_ENUM_TAG);
  file = fopen("list.html", "w");
  if (allStructs.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(enumconstants_list_begin, file);
      for (it = allStructs.begin(); it != allStructs.end(); it++)
	{
	  attrs = (*it)->getAttributes(XHB_ID_ATTR);
	  if (attrs.size())
	    {
	      enumName = (*(attrs.begin()))->getValue();
	      for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
		{
		  enumCstName = "";
		  if (pt->getName() == XHB_CONSTANT_TAG)
		    {
		      attrs = pt->getAttributes(XHB_ID_ATTR);
		      if (attrs.size())
			{
			  enumCstName = (*(attrs.begin()))->getValue();
			  fprintf(file, enumconstants_list_inside,
				  enumName.c_str(), enumCstName.c_str());
			}
		    }
		}
	    }
	}
      fputs(enumconstants_list_end, file);
    }
  fclose(file);

  chdir("..");
  return (1);
}
