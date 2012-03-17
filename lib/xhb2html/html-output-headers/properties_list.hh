#ifndef   __PROPERTIES_LIST_H__
#define   __PROPERTIES_LIST_H__

static char *properties_list_begin =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">";

static char *properties_list_inside = 
"	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"description.html#%s\" target=\"content\">%s</a><br />\n\
	</td></tr>";

static char *properties_list_end =
"</table>\n\
</body>\n\
</html>";

#endif /* __PROPERTIES_LIST_H__ */
