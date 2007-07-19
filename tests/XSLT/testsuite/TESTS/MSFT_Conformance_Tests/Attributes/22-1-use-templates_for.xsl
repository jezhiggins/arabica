<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:apply-templates select="//item" />
</xsl:template>

<xsl:template match="item">
		<p>
		<xsl:value-of select="common"/>		
		<xsl:value-of select="latin"/>
		</p>
</xsl:template>
</xsl:stylesheet>
