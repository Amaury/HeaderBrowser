#include "hbresult_index.hh"
#include "hbresult_description.hh"
#include "hbresult_void.hh"
#include "headers_index.hh"
#include "headers_title.hh"
#include "headers_list.hh"
#include "view.img"
#include "xhb2html.hh"

Xhb2Html::Xhb2Html()
{
  this->currentNbrObjects = this->currentNbrFunctions = this->currentNbrGlobals =
    this->currentNbrTypedefs = this->currentNbrStructs = this->currentNbrUnions =
    this->currentNbrEnums = this->currentNbrEnumConsts = this->currentNbrFuncMacros =
    this->currentNbrConstMacros = this->currentNbrPublicMethods =
    this->currentNbrPublicData = this->currentNbrProtectedMethods =
    this->currentNbrProtectedData = this->currentNbrPrivateMethods =
    this->currentNbrPrivateData = 0;
}

int	Xhb2Html::createDir(const char *lang, vector<StyxDomNode*> nodes,
			    const char* path)
{
  string				outputPath;
  int					fd;
  vector<StyxDomNode*>::iterator	it;
  FILE					*file;

  if (strlen(path) == 0)
    outputPath = "hbresult-html";
  else
    outputPath = outputPath + path + SLASH + "hbresult-html";
  if ((fd = open(outputPath.c_str(), O_RDONLY)) == -1)
    if (mkdir(outputPath.c_str(), 0755) == -1)
      return (0);
  close(fd);

  chdir(outputPath.c_str());

  fd = open("index.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, hbresult_index, strlen(hbresult_index));
  close(fd);

  fd = open("description.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (!strcmp(lang, LANG_FR))
    write(fd, hbresult_description[1], strlen(hbresult_description[1]));
  else
    write(fd, hbresult_description[0], strlen(hbresult_description[0]));
  close(fd);

  fd = open("void.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, hbresult_void, strlen(hbresult_void));
  close(fd);

  fd = open("view.gif", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, view_img, view_size);
  close(fd);

  mkdir("headers", 0755);
  fd = open("headers/index.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, headers_index, strlen(headers_index));
  close(fd);

  fd = open("headers/void.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, hbresult_void, strlen(hbresult_void));
  close(fd);

  fd = open("headers/title.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(fd, headers_title, strlen(headers_title));
  close(fd);

  file = fopen("headers/list.html", "w");
  fputs(headers_list_begin, file);
  for (it = nodes.begin(); it != nodes.end(); it++)
    {
      string	name = (*(((*it)->getAttributes("id")).begin()))->getValue();
      const char	*str = name.c_str();
      fprintf(file, headers_list_file, str, str, str, str, str);
    }
  fputs(headers_list_end, file);
  fclose(file);
  return (1);
}

int	Xhb2Html::go(StyxDom* dom, const char *outputPath, const char* lang)
{
  string				path, name, code;
  vector<StyxDomNode*>			headerNodes, attrNodes;
  vector<StyxDomNode*>			rootNode, elemNodes, attrs;
  vector<StyxDomNode*>::iterator	it, et, at;
  int					i;

  // path = "/hb:headerbrowser/hb:headerfile"
  path = path + SLASH + XHB_TOPLEVEL_TAG + SLASH + XHB_HEADERFILE_TAG;
  headerNodes = dom->getFromXpath(path);
  if (headerNodes.size() && !createDir(lang, headerNodes, outputPath))
    return (0);
  for (it = headerNodes.begin(); it != headerNodes.end(); it++)
    {
      // get the number of each elems in this header file
      rootNode.push_back(*it);
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_CLASS_TAG);
      this->currentNbrObjects = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_FUNCTION_TAG);
      this->currentNbrFunctions = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_VAR_TAG);
      this->currentNbrGlobals = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_TYPEDEF_TAG);
      this->currentNbrTypedefs = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_STRUCT_TAG);
      this->currentNbrStructs = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_UNION_TAG);
      this->currentNbrUnions = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_ENUM_TAG);
      this->currentNbrEnums = elemNodes.size();
      path = string("") + XHB_ENUM_TAG + SLASH + XHB_CONSTANT_TAG;
      elemNodes = dom->getNodesFromXpath(rootNode, path);
      this->currentNbrEnumConsts = elemNodes.size();
      elemNodes = dom->getNodesFromXpath(rootNode, XHB_DEFINE_TAG);
      this->currentNbrFuncMacros = this->currentNbrConstMacros = 0;
      for (et = elemNodes.begin(); et != elemNodes.end(); et++)
	{
	  attrs = (*et)->getAttributes("");
	  for (name = code = "", at = attrs.begin(); at != attrs.end(); at++)
	    {
	      if ((*at)->getName() == XHB_ID_ATTR)
		name = (*at)->getValue();
	      else if ((*at)->getName() == XHB_CODE_ATTR)
		code = (*at)->getValue();
	    }
	  if ((i = code.find(name)) != -1 &&
	      code[i + name.size()] == OPEN_PAR)
	    this->currentNbrFuncMacros++;
	  else
	    this->currentNbrConstMacros++;
	}
      rootNode.pop_back();

      attrNodes = (*it)->getAttributes(XHB_ID_ATTR);
      name = (*(attrNodes.begin()))->getValue();
      if (!createHeaderDir(lang, name, dom, *it))
	return (0);
      if (this->currentNbrGlobals && !createGlobals(lang, name, dom, *it))
	return (0);
      if (this->currentNbrFunctions && !createFunctions(lang, name, dom, *it))
	return (0);
      if (this->currentNbrTypedefs && !createTypedefs(lang, name, dom, *it))
	return (0);
      if (this->currentNbrStructs && !createStructs(lang, name, dom, *it))
	return (0);
      if (this->currentNbrUnions && !createUnions(lang, name, dom, *it))
	return (0);
      if (this->currentNbrEnums && !createEnums(lang, name, dom, *it))
	return (0);
      if (this->currentNbrEnumConsts && !createEnumConstants(lang, name, dom, *it))
	return (0);
      if (this->currentNbrConstMacros && !createMacroConstants(lang, name, dom, *it))
	return (0);
      if (this->currentNbrFuncMacros && !createMacroFunctions(lang, name, dom, *it))
	return (0);
      if (this->currentNbrObjects && !createObjects(lang, name, dom, *it))
	return (0);
      chdir("..");
    }
  return (1);
}
