#ifndef   __CLASSESDIR_LIST_H__
#define   __CLASSESDIR_LIST_H__

#define	CLASSLIST_NOTHING		""
#define	CLASSLIST_VIEW_IMG_PATH		"<img src=\"../../../../view.gif\" border=\"0\" />"
#define	CLASSLIST_PUBLIC_METHODS_INDEX	"<a href=\"public-methods/index.html\" onClick=\"top.go('public-methods/description.html')\" target=\"col5\">"
#define	CLASSLIST_PUBLIC_DATA_INDEX	"<a href=\"public-datas/index.html\" onClick=\"top.go('public-datas/description.html')\" target=\"col5\">"
#define	CLASSLIST_PROTECT_METHODS_INDEX	"<a href=\"protected-methods/index.html\" onClick=\"top.go('protected-methods/description.html')\" target=\"col5\">"
#define	CLASSLIST_PROTECT_DATA_INDEX	"<a href=\"protected-datas/index.html\" onClick=\"top.go('protected-datas/description.html')\" target=\"col5\">"
#define	CLASSLIST_PRIVATE_METHODS_INDEX	"<a href=\"private-methods/index.html\" onClick=\"top.go('private-methods/description.html')\" target=\"col5\">"
#define	CLASSLIST_PRIVATE_DATA_INDEX	"<a href=\"private-datas/index.html\" onClick=\"top.go('private-datas/description.html')\" target=\"col5\">"

static char *classesdir_list[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"description.html\" target=\"content\">Description</a><br />\n\
	</td><td>&nbsp;</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sPublic Methods%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sPublic Datas%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sProtected Methods%s</a><br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sProtected Datas%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sPrivate Methods%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sPrivate Datas%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
</table>\n\
</body>\n\
</html>",
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"description.html\" target=\"content\">Description</a><br />\n\
	</td><td>&nbsp;</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sM&eacute;thodes publiques%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sDonn&eacute;es publiques%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sM&eacute;thodes prot&eacute;g&eacute;es%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sDonn&eacute;es prot&eacute;g&eacute;es%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sM&eacute;thodes priv&eacute;es%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sDonn&eacute;es priv&eacute;es%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
</table>\n\
</body>\n\
</html>"
};

#endif /* __CLASSESDIR_LIST_H__ */
