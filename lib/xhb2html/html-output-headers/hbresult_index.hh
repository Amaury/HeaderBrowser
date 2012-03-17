#ifndef   __HBRESULT_INDEX_H__
#define   __HBRESULT_INDEX_H__

static char *hbresult_index = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\n\
<html>\n\
<head>\n\
<title> Header Browser </title>\n\
<script>\n\
	function go(redirect) {\n\
		content.document.location.href = redirect;\n\
	}\n\
	function clear(col) {\n\
		if (col == 1)\n\
			col1.document.location.href = \"void.html\";\n\
		else if (col == 2)\n\
			col2.document.location.href = \"void.html\";\n\
		else if (col == 3)\n\
			col3.document.location.href = \"void.html\";\n\
		else if (col == 4)\n\
			col4.document.location.href = \"void.html\";\n\
		else if (col == 5)\n\
			col5.document.location.href = \"void.html\";\n\
		else if (col == -1) {\n\
			col2.document.location.href = \"void.html\";\n\
			col3.document.location.href = \"void.html\";\n\
			col4.document.location.href = \"void.html\";\n\
			col5.document.location.href = \"void.html\";\n\
		} else if (col == -2) {\n\
			col3.document.location.href = \"void.html\";\n\
			col4.document.location.href = \"void.html\";\n\
			col5.document.location.href = \"void.html\";\n\
		} else if (col == -3) {\n\
			col4.document.location.href = \"void.html\";\n\
			col5.document.location.href = \"void.html\";\n\
		} else if (col == -4)\n\
			col5.document.location.href = \"void.html\";\n\
	}\n\
</script>\n\
</head>\n\
<frameset rows=\"30%%,*\">\n\
	<frameset cols=\"20%%,20%%,20%%,20%%,20%%\">\n\
		<frame src=\"headers/index.html\" name=\"col1\" border=\"true\" />\n\
		<frame src=\"void.html\" name=\"col2\" border=\"true\" />\n\
		<frame src=\"void.html\" name=\"col3\" border=\"true\" />\n\
		<frame src=\"void.html\" name=\"col4\" border=\"true\" />\n\
		<frame src=\"void.html\" name=\"col5\" border=\"true\" />\n\
	</frameset>\n\
	<frame src=\"description.html\" name=\"content\" />\n\
</frameset>\n\
</html>";

#endif /* __HBRESULT_INDEX_H__ */
