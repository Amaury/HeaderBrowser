#ifndef   __HEADERS_LIST_H__
#define   __HEADERS_LIST_H__

static char *headers_list_begin = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n";

static char *headers_list_file =
"<tr valign=\"middle\">\n\t<td align=\"left\">\n\t\t<a href=\"%s.dir/index.html\"\n\t\tonClick=\"top.go('%s.dir/description.html');top.clear(-2)\"\t\ttarget=\"col2\">%s</a>\n\t</td>\n\t<td align=\"right\">\n\t<a href=\"%s.dir/index.html\"\n\t\tonClick=\"top.go('%s.dir/description.html');top.clear(-2)\"\t\ttarget=\"col2\"><img src=\"../view.gif\" width=\"16\" height=\"16\" border=\"0\"></a>\n\t</td>\n</tr>\n";

static char *headers_list_end = "</table>\n\
</body>\n\
</html>";

#endif /* __HEADERS_LIST_H__ */
