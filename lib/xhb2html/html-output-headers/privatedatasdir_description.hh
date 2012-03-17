#ifndef   __PRIVATEDATASDIR_DESCRIPTION_H__
#define   __PRIVATEDATASDIR_DESCRIPTION_H__

static char *privatedatasdir_description_begin[] = {
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Objects&nbsp;/\
&nbsp;%s&nbsp;/&nbsp;Private Datas&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Private Datas</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Objets&nbsp;/\
&nbsp;%s&nbsp;/&nbsp;Donn&eacute;es priv&eacute;es&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Donn&eacute;es priv&eacute;es</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>"
};

static char *privatedatasdir_description_inside =
"		<hr width=\"100%%\" />\n\
		<a name=\"%s\"></a>\n\
		<h3>%s</h3>\n\
		%s\n\
		<blockquote><pre>%s</pre></blockquote>\n\
		%s<br /><br />\n";

static char *privatedatasdir_description_end =
"		<hr width=\"100%%\" />\n\
	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __PRIVATEDATASDIR_DESCRIPTION_H__ */
