#ifndef   __MACROFUNCTIONSDIR_DESCRIPTION_H__
#define   __MACROFUNCTIONSDIR_DESCRIPTION_H__

static char *macrofunctionsdir_description_begin[] = {
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Function-like Macros&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Function-like Macro</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Fonctions de macro&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Fonctions de macro</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>"
};

static char *macrofunctionsdir_description_inside =
"		<hr width=\"100%%\" />\n\
		<a name=\"%s\"></a>\n\
		<h3>%s</h3>\n\
		%s\n\
		<blockquote><pre>%s</pre></blockquote>\n\
		%s<br /><br />\n";

static char *macrofunctionsdir_description_end =
"		<hr width=\"100%%\" />\n\
	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __MACROFUNCTIONSDIR_DESCRIPTION_H__ */
