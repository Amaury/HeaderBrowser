#ifndef   __OBJECTSDIR_LIST_H__
#define   __OBJECTSDIR_LIST_H__

static char *objectsdir_list_begin =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">";

static char *objectsdir_list_inside =
"<tr valign=\"middle\"><td align=\"left\">\n\
	<a href=\"%s/index.html\" \n\
	onClick=\"top.go('%s/description.html');top.clear(-4)\" \n\
	target=\"col4\">%s</a><br />\n\
</td><td align=\"right\">\
	<a href=\"%s/index.html\" \n\
	onClick=\"top.go('%s/description.html');top.clear(-4)\" \n\
	target=\"col4\"><img src=\"../../../view.gif\" border=\"0\" /></a></td>\
</tr>";

static char *objectsdir_list_end =
"</table>\n\
</body>\n\
</html>";

#endif /* __OBJECTSDIR_LIST_H__ */
