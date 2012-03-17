#ifndef   __CLASSESDIR_DESCRIPTION_H__
#define   __CLASSESDIR_DESCRIPTION_H__

static char *classesdir_description_begin[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Objects&nbsp;/\
&nbsp;%s&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>%s</h1>\n\
	<br />\n\
	<table width=\"80%%\"><TR><TD>\n",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Objets&nbsp;/\
&nbsp;%s&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>%s</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>\n"
};

static char *classesdir_description_abstract[] = {
"		<b>Abstract:</b> %s\n\
		<hr width=\"100%%\" />\n\
		<br />",
"		<b>R&eacute;sum&eacute; :</b> %s\n\
		<hr width=\"100%%\" />\n\
		<br />"
};

static char *classesdir_description_discussion = 
"		%s<br /><br />\n\
		<hr width=\"100%%\" />";

static char *classesdir_description_super[] = {
"<b>Super-classes:</b> <code>%s</code>",
"<b>Super-classes :</b> <code>%s</code>"
};

static char *classesdir_description_super_none[] = {
"<b>Super-classes:</b> <code>None</code>",
"<b>Super-classes :</b> <code>Aucune</code>"
};

static char *classesdir_description_end =
"	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __CLASSESDIR_DESCRIPTION_H__ */
