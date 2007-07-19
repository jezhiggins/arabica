<!-- import-doc.inc -->
<test3 xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<!-- Nodes from different document unioned together -->
	<xsl:for-each select="document('../doc-dtd.xml')/comment() | document('')/comment()">
		<xsl:sort select="."/>
		<xsl:copy-of select="."/>
	</xsl:for-each>
</test3>
