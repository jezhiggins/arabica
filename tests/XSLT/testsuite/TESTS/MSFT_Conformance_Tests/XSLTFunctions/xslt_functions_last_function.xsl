<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Pupose: test for last() function. [bug 71223] last() function returns wrong result if it is applied to a node-set bound to a variable -->
	<xsl:template match="/">
	<out>
		<xsl:variable name="bookstore" select="bookstore"/>
		<xsl:variable name="book" select="$bookstore/book"/>
	
		<xsl:for-each select="$book">
			<xsl:value-of select="last()"/>
		</xsl:for-each>
	</out>
	</xsl:template>
</xsl:stylesheet>