#ifndef   __HEADERDIR_LIST_H__
#define   __HEADERDIR_LIST_H__

#define DIRLIST_NOTHING			""
#define	DIRLIST_VIEW_IMG_PATH		"<img src=\"../../view.gif\" border=\"0\" />"
#define	DIRLIST_OBJECTS_INDEX		"<a href=\"objects/index.html\" onClick=\"top.go('description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_FUNCTIONS_INDEX		"<a href=\"functions/index.html\" onClick=\"top.go('functions/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_GLOBALS_INDEX		"<a href=\"globals/index.html\" onClick=\"top.go('globals/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_TYPEDEFS_INDEX		"<a href=\"typedefs/index.html\" onClick=\"top.go('typedefs/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_STRUCTS_INDEX		"<a href=\"structs/index.html\" onClick=\"top.go('structs/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_UNIONS_INDEX		"<a href=\"unions/index.html\" onClick=\"top.go('unions/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_ENUMS_INDEX		"<a href=\"enums/index.html\" onClick=\"top.go('enums/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_ENUMCONSTS_INDEX	"<a href=\"enum-constants/index.html\" onClick=\"top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_CONSTMACRO_INDEX	"<a href=\"macro-constants/index.html\" onClick=\"top.go('macro-constants/description.html');top.clear(-3)\" target=\"col3\">"
#define	DIRLIST_FUNCMACRO_INDEX		"<a href=\"macro-functions/index.html\" onClick=\"top.go('macro-functions/description.html');top.clear(-3)\" target=\"col3\">"

static char *headerdir_list[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<body bgcolor=\"#ffffff\">\n\
<table width=\"100%%\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"description.html\" target=\"content\">Description</a><br />\n\
	</td><td>&nbsp;</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sObjects%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sFunctions%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sGlobals%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sType Definitions%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sStructures%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sUnions%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sEnumerations%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sEnum Constants%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sConstant-like Macros%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sFunction-like Macros%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"content.html\" target=\"content\">Content</a><br />\n\
	</td><td>&nbsp;</td></tr>\n\
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
		%sObjets%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sFonctions%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sGlobales%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sDefinitions de types%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sStructures%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sUnions%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sEnum&eacute;rations%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sConstantes d'&eacute;num&eacute;ration%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sConstantes de macro%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		%sFonctions de macro%s<br />\n\
	</td><td align=\"right\">%s%s%s</td></tr>\n\
	<tr valign=\"middle\"><td align=\"left\">\n\
		<a href=\"content.html\" target=\"content\">Contenu</a><br />\n\
	</td><td>&nbsp;</td></tr>\n\
</table>\n\
</body>\n\
</html>"
};

#endif /* __HEADERDIR_LIST_H__ */
