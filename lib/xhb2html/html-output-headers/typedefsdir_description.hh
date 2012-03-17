#ifndef   __TYPEDEFSDIR_DESCRIPTION_H__
#define   __TYPEDEFSDIR_DESCRIPTION_H__

static char *typedefsdir_description_begin[] = {
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;Type definitions&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>Type definitions</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<font size=\"-1\">/&nbsp;%s&nbsp;/&nbsp;D&eacute;finitions de types&nbsp;/&nbsp;Description</font>\n\
<center>\n\
	<h1>D&eacute;finitions de types</h1>\n\
	<br />\n\
	<table width=\"80%%\"><tr><td>"
};

static char *typedefsdir_description_inside =
"		<hr width=\"100%%\" />\n\
		<a name=\"%s\"></a>\n\
		<h3>%s</h3>\n\
		%s\n\
		<blockquote><pre>%s</pre></blockquote>\n\
		%s<br /><br />\n";

static char *typedefsdir_description_param_begin[] = {
  "		<b>Parameters</b>\n\
		<center><table border=\"1\" WIDTH=\"80%%\">\n",
  "		<b>Param&egrave;tres</b>\n\
		<center><table border=\"1\" width=\"80%%\">\n"
};

static char *typedefsdir_description_field_begin[] = {
  "		<b>Fields</b>\n\
		<center><table border=\"1\" width=\"80%%\">\n",
  "		<b>Champs</b>\n\
		<center><table border=\"1\" width=\"80%%\">\n"
};

static char *typedefsdir_description_constant_begin[] = {
  "		<b>Constants</b>\n\
		<center><table border=\"1\" width=\"80%%\">\n",
  "		<b>Constantes</b>\n\
		<center><table border=\"1\" width=\"80%%\">\n"
};

static char *typedefsdir_description_param_inside =
"\t\t\t<tr><td align=\"center\"><tt>%s</tt></td><td>&nbsp;%s</td></tr>\n";

static char *typedefsdir_description_param_end =
"		</table></center><br />\n";

static char *typedefsdir_description_end =
"		<hr width=\"100%%\" />\n\
	</td></tr></table>\n\
</center>\n\
</body>\n\
</html>";

#endif /* __TYPEDEFSDIR_DESCRIPTION_H__ */
