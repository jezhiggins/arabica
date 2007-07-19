<!-- Test case for bug # 70863 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<xsl:apply-templates select="." mode="css"/>
	</xsl:template>

	<xsl:template match="/" mode="css">
		<hello/>
	</xsl:template>
</xsl:stylesheet>