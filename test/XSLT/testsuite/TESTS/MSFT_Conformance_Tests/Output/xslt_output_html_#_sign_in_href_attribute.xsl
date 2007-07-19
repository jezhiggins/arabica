<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="no"/>

<xsl:template match="/">
	<html><head><title>XSLT Output of A</title></head><body>

	<a href="foo.htm#bookmark">
		foo.htm#bookmark
	</a><br/>
	<a>
		<xsl:attribute name="href">foo.htm<xsl:text disable-output-escaping="yes">#</xsl:text>bookmark<xsl:value-of select="@Name"/></xsl:attribute>
		foo.htm#bookmark (explicitly disabled output escaping)
	</a><br/>

	<p>
		<xsl:attribute name="href">foo.htm#bookmark</xsl:attribute>
		foo.htm#bookmark (in a P tag)
	</p><br/>

	</body></html>
</xsl:template>

</xsl:stylesheet>
