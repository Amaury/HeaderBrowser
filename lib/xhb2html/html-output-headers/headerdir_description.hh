#ifndef   __HEADERDIR_DESCRIPTION_H__
#define   __HEADERDIR_DESCRIPTION_H__

static char *headerdir_description_null[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>No description for the file %s</h1>\n\
</center>\n\
</body>\n\
</html>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Pas de description pour le fichier %s</h1>\n\
</center>\n\
</body>\n\
</html>"
};

static char *headerdir_description_begin = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>%s</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>\n";

static char *headerdir_description_abstract[] = {
"		<b>Abstract:</b> %s\n\
		<hr width=\"100%%\" />\n\
		<br />",
"		<b>R&eacute;sum&eacute; :</b> %s\n\
		<hr width=\"100%%\" />\n\
		<br />"
};

static char *headerdir_description_discussion = 
"		%s<br /><br />\n\
		<hr width=\"100%%\" />";

static char *headerdir_description_version[] = {
  "		<b>Version:</b> %s\n\
		<hr width=\"100%%\" />",
  "		<b>Version :</b> %s\n\
		<hr width=\"100%%\" />"
};

static char *headerdir_description_see[] = {
  "		<b>See also:</b><br />\n\
		%s\n\
		<hr width=\"100%%\" />",
  "		<b>Voir aussi :</b><br />\n\
		%s\n\
		<hr width=\"100%%\" />"
};

static char *headerdir_description_link_begin[] = {
  "		<b>Links:</b><br />\n",
  "		<b>Liens :</b><br />\n"
};

static char *headerdir_description_link_end =
"		<hr width=\"100%%\" />\n";

static char *headerdir_description_author[] = {
  "		<b>Authors:</b><br />\n",
  "		<b>Auteurs :</b><br />\n"
};

static char *headerdir_description_end =
"	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __HEADERDIR_DESCRIPTION_H__ */
