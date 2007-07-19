<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
   <xsl:apply-templates select="//item"/>
	post apply-templates text
</xsl:template>

<xsl:template match="item">
		<hr/>
		<xsl:value-of select="common" />
		<xsl:value-of select="latin" />
		<xsl:value-of select="common" />
		<hr/>
	</xsl:template>
</xsl:stylesheet>
