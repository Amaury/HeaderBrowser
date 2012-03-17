#include "hbresult_void.hh"
#include "headers_index.hh"
#include "classesdir_title.hh"
#include "classesdir_list.hh"
#include "classesdir_description.hh"
#include "publicmethodsdir_title.hh"
#include "publicdatasdir_title.hh"
#include "protectedmethodsdir_title.hh"
#include "protecteddatasdir_title.hh"
#include "privatemethodsdir_title.hh"
#include "privatedatasdir_title.hh"
#include "properties_list.hh"
#include "publicmethodsdir_description.hh"
#include "publicdatasdir_description.hh"
#include "protectedmethodsdir_description.hh"
#include "protecteddatasdir_description.hh"
#include "privatemethodsdir_description.hh"
#include "privatedatasdir_description.hh"
#include "xhb2html.hh"

int	Xhb2Html::createClass(const char *lang, string headerName, string className,
			      StyxDom* dom, StyxDomNode *node)
{
  FILE*			file;
  vector<StyxDomNode*>	l;
  int			langId;

  mkdir(className.c_str(), 0755);
  chdir(className.c_str());

  if (this->currentNbrPublicMethods)
    mkdir("public-methods", 0755);
  if (this->currentNbrPublicData)
    mkdir("public-datas", 0755);
  if (this->currentNbrProtectedMethods)
    mkdir("protected-methods", 0755);
  if (this->currentNbrProtectedData)
    mkdir("protected-datas", 0755);
  if (this->currentNbrPrivateMethods)
    mkdir("private-methods", 0755);
  if (this->currentNbrPrivateData)
    mkdir("private-datas", 0755);

  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  fprintf(file, classesdir_title, className.c_str());
  fclose(file);

  file = fopen("list.html", "w");
  if (!strcmp(lang, LANG_FR))
    langId = 1;
  else
    langId = 0;
  fprintf(file, classesdir_list[langId],
	  this->currentNbrPublicMethods ? CLASSLIST_PUBLIC_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPublicMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPublicMethods ? CLASSLIST_PUBLIC_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPublicMethods ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrPublicMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPublicData ? CLASSLIST_PUBLIC_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPublicData ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPublicData ? CLASSLIST_PUBLIC_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPublicData ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrPublicData ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrProtectedMethods ? CLASSLIST_PROTECT_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrProtectedMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrProtectedMethods ? CLASSLIST_PROTECT_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrProtectedMethods ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrProtectedMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrProtectedData ? CLASSLIST_PROTECT_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrProtectedData ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrProtectedData ? CLASSLIST_PROTECT_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrProtectedData ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrProtectedData ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPrivateMethods ? CLASSLIST_PRIVATE_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPrivateMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPrivateMethods ? CLASSLIST_PRIVATE_METHODS_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPrivateMethods ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrPrivateMethods ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPrivateData ? CLASSLIST_PRIVATE_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPrivateData ? "</A>" : CLASSLIST_NOTHING,
	  this->currentNbrPrivateData ? CLASSLIST_PRIVATE_DATA_INDEX : CLASSLIST_NOTHING,
	  this->currentNbrPrivateData ? CLASSLIST_VIEW_IMG_PATH : CLASSLIST_NOTHING,
	  this->currentNbrPrivateData ? "</A>" : CLASSLIST_NOTHING
	  );
  fclose(file);

  file = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file, classesdir_description_begin[1], headerName.c_str(),
	    className.c_str(), className.c_str());
  else
    fprintf(file, classesdir_description_begin[0], headerName.c_str(),
	    className.c_str(), className.c_str());

  l = node->getAttributes(XHB_ABSTRACT_ATTR);
  if (l.size() && !strcmp(lang, LANG_FR))
    fprintf(file, classesdir_description_abstract[1],
	    (*(l.begin()))->getValue().c_str());
  else if (l.size())
    fprintf(file, classesdir_description_abstract[0],
	    (*(l.begin()))->getValue().c_str());

  l = node->getAttributes(XHB_DISCUSSION_ATTR);
  if (l.size())
    fprintf(file, classesdir_description_discussion,
	    (*(l.begin()))->getValue().c_str());

  l = node->getAttributes(XHB_INHERITS_ATTR);
  if (l.size() && !strcmp(lang, LANG_FR))
    fprintf(file, classesdir_description_super[1],
	    (*(l.begin()))->getValue().c_str());
  else if (l.size())
    fprintf(file, classesdir_description_super[0],
	    (*(l.begin()))->getValue().c_str());
  else if (!strcmp(lang, LANG_FR))
    fputs(classesdir_description_super_none[1], file);
  else
    fputs(classesdir_description_super_none[0], file);

  fputs(classesdir_description_end, file);
  fclose(file);

  if (this->currentNbrPublicMethods &&
      !createClassPublicMethods(lang, headerName, className, dom, node))
    return (0);
  if (this->currentNbrPublicData &&
      !createClassPublicDatas(lang, headerName, className, dom, node))
    return (0);
  if (this->currentNbrProtectedMethods &&
      !createClassProtectedMethods(lang, headerName, className, dom, node))
    return (0);
  if (this->currentNbrProtectedData &&
      !createClassProtectedDatas(lang, headerName, className, dom, node))
    return (0);
  if (this->currentNbrPrivateMethods &&
      !createClassPrivateMethods(lang, headerName, className, dom, node))
    return (0);
  if (this->currentNbrPrivateData &&
      !createClassPrivateDatas(lang, headerName, className, dom, node))
    return (0);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassPublicMethods(const char *lang, string headerName,
					   string className, StyxDom* dom,
					   StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			all, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				funcName, funcAbs, funcDisc, funcCode;
  int					i;
  string				paramName, paramValue, funcResult;
  StyxDomNode*				pt;
  bool					isFirstParam = true;

  chdir("public-methods");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(publicmethodsdir_title[1], file);
  else
    fputs(publicmethodsdir_title[0], file);
  fclose(file);

  all.push_back(node);
  all = dom->getNodesFromXpath(all, XHB_FUNCTION_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, publicmethodsdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, publicmethodsdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  fputs(properties_list_begin, file);
  for (it = all.begin(); it != all.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "public")
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
	  if (!funcName.size())
	    continue ;
	  if (funcCode.size() && funcName.size())
	    {
	      if ((i = funcCode.find(funcName)) != -1)
		funcCode = funcCode.substr(0, i) + "<B>" +
		  funcCode.substr(i, funcName.size()) + "</B>" +
		  funcCode.substr(i + funcName.size(),
				  funcCode.size() - (funcName.size() + 1));
	    }
	  fprintf(file, properties_list_inside, funcName.c_str(),
		  funcName.c_str());
	  fprintf(file2, publicmethodsdir_description_inside, funcName.c_str(),
		  funcName.c_str(), funcAbs.c_str(), funcCode.c_str(),
		  funcDisc.c_str());
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_PARAM_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(publicmethodsdir_description_param_begin[1], file2);
		  else if (isFirstParam)
		    fputs(publicmethodsdir_description_param_begin[0], file2);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file2, publicmethodsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(publicmethodsdir_description_param_end, file2);
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      if (pt->getName() == XHB_RESULT_TAG)
		{
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    funcResult = (*(attrs.begin()))->getValue();
		  if (funcResult.size() && !strcmp(lang, LANG_FR))
		    fprintf(file2, publicmethodsdir_description_result[1],
			    funcResult.c_str());
		  else if (funcResult.size())
		    fprintf(file2, publicmethodsdir_description_result[0],
			    funcResult.c_str());
		  break ;
		}
	    }
	}
    }
  fputs(properties_list_end, file);
  fputs(publicmethodsdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassPublicDatas(const char *lang, string headerName,
					 string className, StyxDom* dom,
					 StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			allVars;
  vector<StyxDomNode*>::iterator	it, at;
  vector<StyxDomNode*>			attrs;
  string				str, varName, varAbs, varDisc, varCode;
  int					i;

  chdir("public-datas");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(publicdatasdir_title[1], file);
  else
    fputs(publicdatasdir_title[0], file);
  fclose(file);

  allVars.push_back(node);
  allVars = dom->getNodesFromXpath(allVars, XHB_VAR_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  fputs(properties_list_begin, file);
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, publicdatasdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, publicdatasdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  for (it = allVars.begin(); it != allVars.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "public")
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
	  if (!varName.size())
	    continue ;
	  if (varCode.size() && varName.size())
	    {
	      if ((i = varCode.find(varName)) != -1)
		varCode = varCode.substr(0, i) + "<B>" +
		  varCode.substr(i, varName.size()) + "</B>" +
		  varCode.substr(i + varName.size(),
				 varCode.size() - (varName.size() + 1));
	    }
	  fprintf(file, properties_list_inside,
		  (*(attrs.begin()))->getValue().c_str(),
		  (*(attrs.begin()))->getValue().c_str());
	  fprintf(file2, publicdatasdir_description_inside, varName.c_str(),
		  varName.c_str(), varAbs.c_str(), varCode.c_str(),
		  varDisc.c_str());
	}
    }
  fputs(properties_list_end, file);
  fputs(publicdatasdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassProtectedMethods(const char *lang, string headerName,
					      string className, StyxDom* dom,
					      StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			all, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				funcName, funcAbs, funcDisc, funcCode;
  int					i;
  string				paramName, paramValue, funcResult;
  StyxDomNode*				pt;
  bool					isFirstParam = true;

  chdir("protected-methods");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(protectedmethodsdir_title[1], file);
  else
    fputs(protectedmethodsdir_title[0], file);
  fclose(file);

  all.push_back(node);
  all = dom->getNodesFromXpath(all, XHB_FUNCTION_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, protectedmethodsdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, protectedmethodsdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  fputs(properties_list_begin, file);
  for (it = all.begin(); it != all.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "protected")
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
	  if (!funcName.size())
	    continue ;
	  if (funcCode.size() && funcName.size())
	    {
	      if ((i = funcCode.find(funcName)) != -1)
		funcCode = funcCode.substr(0, i) + "<B>" +
		  funcCode.substr(i, funcName.size()) + "</B>" +
		  funcCode.substr(i + funcName.size(),
				  funcCode.size() - (funcName.size() + 1));
	    }
	  fprintf(file, properties_list_inside, funcName.c_str(),
		  funcName.c_str());
	  fprintf(file2, protectedmethodsdir_description_inside, funcName.c_str(),
		  funcName.c_str(), funcAbs.c_str(), funcCode.c_str(),
		  funcDisc.c_str());
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_PARAM_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(protectedmethodsdir_description_param_begin[1], file2);
		  else if (isFirstParam)
		    fputs(protectedmethodsdir_description_param_begin[0], file2);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file2, protectedmethodsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(protectedmethodsdir_description_param_end, file2);
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      if (pt->getName() == XHB_RESULT_TAG)
		{
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    funcResult = (*(attrs.begin()))->getValue();
		  if (funcResult.size() && !strcmp(lang, LANG_FR))
		    fprintf(file2, protectedmethodsdir_description_result[1],
			    funcResult.c_str());
		  else if (funcResult.size())
		    fprintf(file2, protectedmethodsdir_description_result[0],
			    funcResult.c_str());
		  break ;
		}
	    }
	}
    }
  fputs(properties_list_end, file);
  fputs(protectedmethodsdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassProtectedDatas(const char *lang, string headerName,
					    string className, StyxDom* dom,
					    StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			allVars;
  vector<StyxDomNode*>::iterator	it, at;
  vector<StyxDomNode*>			attrs;
  string				str, varName, varAbs, varDisc, varCode;
  int					i;

  chdir("protected-datas");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(protecteddatasdir_title[1], file);
  else
    fputs(protecteddatasdir_title[0], file);
  fclose(file);

  allVars.push_back(node);
  allVars = dom->getNodesFromXpath(allVars, XHB_VAR_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  fputs(properties_list_begin, file);
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, protecteddatasdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, protecteddatasdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  for (it = allVars.begin(); it != allVars.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "protected")
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
	  if (!varName.size())
	    continue ;
	  if (varCode.size() && varName.size())
	    {
	      if ((i = varCode.find(varName)) != -1)
		varCode = varCode.substr(0, i) + "<B>" +
		  varCode.substr(i, varName.size()) + "</B>" +
		  varCode.substr(i + varName.size(),
				 varCode.size() - (varName.size() + 1));
	    }
	  fprintf(file, properties_list_inside,
		  (*(attrs.begin()))->getValue().c_str(),
		  (*(attrs.begin()))->getValue().c_str());
	  fprintf(file2, protecteddatasdir_description_inside, varName.c_str(),
		  varName.c_str(), varAbs.c_str(), varCode.c_str(),
		  varDisc.c_str());
	}
    }
  fputs(properties_list_end, file);
  fputs(protecteddatasdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassPrivateMethods(const char *lang, string headerName,
					    string className, StyxDom* dom,
					    StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			all, attrs;
  vector<StyxDomNode*>::iterator	it, at;
  string				funcName, funcAbs, funcDisc, funcCode;
  int					i;
  string				paramName, paramValue, funcResult;
  StyxDomNode*				pt;
  bool					isFirstParam = true;

  chdir("private-methods");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(privatemethodsdir_title[1], file);
  else
    fputs(privatemethodsdir_title[0], file);
  fclose(file);

  all.push_back(node);
  all = dom->getNodesFromXpath(all, XHB_FUNCTION_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, privatemethodsdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, privatemethodsdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  fputs(properties_list_begin, file);
  for (it = all.begin(); it != all.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "private")
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
	  if (!funcName.size())
	    continue ;
	  if (funcCode.size() && funcName.size())
	    {
	      if ((i = funcCode.find(funcName)) != -1)
		funcCode = funcCode.substr(0, i) + "<B>" +
		  funcCode.substr(i, funcName.size()) + "</B>" +
		  funcCode.substr(i + funcName.size(),
				  funcCode.size() - (funcName.size() + 1));
	    }
	  fprintf(file, properties_list_inside, funcName.c_str(),
		  funcName.c_str());
	  fprintf(file2, privatemethodsdir_description_inside, funcName.c_str(),
		  funcName.c_str(), funcAbs.c_str(), funcCode.c_str(),
		  funcDisc.c_str());
	  isFirstParam = true;
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      paramName = paramValue = "";
	      if (pt->getName() == XHB_PARAM_TAG)
		{
		  if (isFirstParam && !strcmp(lang, LANG_FR))
		    fputs(privatemethodsdir_description_param_begin[1], file2);
		  else if (isFirstParam)
		    fputs(privatemethodsdir_description_param_begin[0], file2);
		  isFirstParam = false;
		  attrs = pt->getAttributes(XHB_ID_ATTR);
		  if (attrs.size())
		    paramName = (*(attrs.begin()))->getValue();
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    paramValue = (*(attrs.begin()))->getValue();
		  if (paramName.size() && paramValue.size())
		    fprintf(file2, privatemethodsdir_description_param_inside,
			    paramName.c_str(), paramValue.c_str());
		}
	    }
	  if (!isFirstParam)
	    fputs(privatemethodsdir_description_param_end, file2);
	  for (pt = (*it)->getFirstChild(); pt; pt = pt->nextSibling())
	    {
	      if (pt->getName() == XHB_RESULT_TAG)
		{
		  attrs = pt->getAttributes(XHB_DISCUSSION_ATTR);
		  if (attrs.size())
		    funcResult = (*(attrs.begin()))->getValue();
		  if (funcResult.size() && !strcmp(lang, LANG_FR))
		    fprintf(file2, privatemethodsdir_description_result[1],
			    funcResult.c_str());
		  else if (funcResult.size())
		    fprintf(file2, privatemethodsdir_description_result[0],
			    funcResult.c_str());
		  break ;
		}
	    }
	}
    }
  fputs(properties_list_end, file);
  fputs(privatemethodsdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}

int	Xhb2Html::createClassPrivateDatas(const char *lang, string headerName,
					  string className, StyxDom* dom,
					  StyxDomNode* node)
{
  FILE					*file, *file2;
  vector<StyxDomNode*>			allVars;
  vector<StyxDomNode*>::iterator	it, at;
  vector<StyxDomNode*>			attrs;
  string				str, varName, varAbs, varDisc, varCode;
  int					i;

  chdir("private-datas");
  file = fopen("index.html", "w");
  fputs(headers_index, file);
  fclose(file);

  file = fopen("void.html", "w");
  fputs(hbresult_void, file);
  fclose(file);

  file = fopen("title.html", "w");
  if (!strcmp(lang, LANG_FR))
    fputs(privatedatasdir_title[1], file);
  else
    fputs(privatedatasdir_title[0], file);
  fclose(file);

  allVars.push_back(node);
  allVars = dom->getNodesFromXpath(allVars, XHB_VAR_TAG);
  file = fopen("list.html", "w");
  file2 = fopen("description.html", "w");
  fputs(properties_list_begin, file);
  if (!strcmp(lang, LANG_FR))
    fprintf(file2, privatedatasdir_description_begin[1], headerName.c_str(),
	    className.c_str());
  else
    fprintf(file2, privatedatasdir_description_begin[0], headerName.c_str(),
	    className.c_str());
  for (it = allVars.begin(); it != allVars.end(); it++)
    {
      attrs = (*it)->getAttributes(XHB_PERMISSION_ATTR);
      if (attrs.size() && (*(attrs.begin()))->getValue() == "private")
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
	  if (!varName.size())
	    continue ;
	  if (varCode.size() && varName.size())
	    {
	      if ((i = varCode.find(varName)) != -1)
		varCode = varCode.substr(0, i) + "<B>" +
		  varCode.substr(i, varName.size()) + "</B>" +
		  varCode.substr(i + varName.size(),
				 varCode.size() - (varName.size() + 1));
	    }
	  fprintf(file, properties_list_inside,
		  (*(attrs.begin()))->getValue().c_str(),
		  (*(attrs.begin()))->getValue().c_str());
	  fprintf(file2, privatedatasdir_description_inside, varName.c_str(),
		  varName.c_str(), varAbs.c_str(), varCode.c_str(),
		  varDisc.c_str());
	}
    }
  fputs(properties_list_end, file);
  fputs(privatedatasdir_description_end, file2);
  fclose(file);
  fclose(file2);

  chdir("..");
  return (1);
}
