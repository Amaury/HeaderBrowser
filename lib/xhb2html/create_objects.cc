#include "hbresult_void.hh"
#include "headers_index.hh"
#include "objectsdir_title.hh"
#include "objectsdir_list.hh"
#include "xhb2html.hh"

int	Xhb2Html::createObjects(const char* lang, string headerName, StyxDom* dom,
				StyxDomNode* node)
{
  FILE					*file;
  vector<StyxDomNode*>			allObjs, attrs, allMembers, membAt;
  vector<StyxDomNode*>::iterator	it, et;
  string				name, permission;

  chdir("objects");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(objectsdir_title[1], file);
  else
    fputs(objectsdir_title[0], file);
  fclose(file);

  allObjs.push_back(node);
  allObjs = dom->getNodesFromXpath(allObjs, XHB_CLASS_TAG);
  file = fopen("list.html", "w");
  if (allObjs.size() == 0)
    fputs(hbresult_void, file);
  else
    {
      fputs(objectsdir_list_begin, file);
      for (it = allObjs.begin(); it != allObjs.end(); it++)
	{
	  attrs = (*it)->getAttributes(XHB_ID_ATTR);
	  if (attrs.size())
	    {
	      // get the number of members of this class
	      this->currentNbrPublicMethods = this->currentNbrProtectedMethods =
		this->currentNbrPrivateMethods = this->currentNbrPublicData =
		this->currentNbrProtectedData = this->currentNbrPrivateData = 0;
	      allMembers.push_back(*it);
	      allMembers = dom->getNodesFromXpath(allMembers, "*");
	      for (et = allMembers.begin(); et != allMembers.end(); et++)
		{
		  name = (*et)->getName();
		  membAt = (*et)->getAttributes(XHB_PERMISSION_ATTR);
		  permission = (*(membAt.begin()))->getValue();
		  if (name == XHB_FUNCTION_TAG)
		    {
		      if (permission == "public")
			this->currentNbrPublicMethods++;
		      else if (permission == "protected")
			this->currentNbrProtectedMethods++;
		      else if (permission == "private")
			this->currentNbrPrivateMethods++;
		    }
		  else if (name == XHB_VAR_TAG)
		    {
		      if (permission == "public")
			this->currentNbrPublicData++;
		      else if (permission == "protected")
			this->currentNbrProtectedData++;
		      else if (permission == "private")
			this->currentNbrPrivateData++;
		    }
		}

	      fprintf(file, objectsdir_list_inside,
		      (*(attrs.begin()))->getValue().c_str(),
		      (*(attrs.begin()))->getValue().c_str(),
		      (*(attrs.begin()))->getValue().c_str(),
		      (*(attrs.begin()))->getValue().c_str(),
		      (*(attrs.begin()))->getValue().c_str());
	      createClass(lang, headerName, (*(attrs.begin()))->getValue(),
			  dom, *it);
	    }
	}
      fputs(objectsdir_list_end, file);
    }
  fclose(file);

  chdir("..");
  return (1);
}
