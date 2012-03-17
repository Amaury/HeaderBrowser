#ifndef   __MACROCONSTANTSDIR_DESCRIPTION_H__
#define   __MACROCONSTANTSDIR_DESCRIPTION_H__

static char *macroconstantsdir_description_begin[] = {
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Constant-like Macros&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Constant-like Macro</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Constantes de macro&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Constantes de macro</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>"
};

static char *macroconstantsdir_description_inside =
"		<hr width=\"100%%\" />\n\
		<a name=\"%s\"></a>\n\
		<h3>%s</h3>\n\
		%s\n\
		<blockquote><pre>%s</pre></blockquote>\n\
		%s<br /><br />\n";

static char *macroconstantsdir_description_end =
"		<hr width=\"100%%\" />\n\
	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __MACROCONSTANTSDIR_DESCRIPTION_H__ */
