<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes"/>

	<xsl:template match="/">
		<xsl:apply-templates />
	</xsl:template>

	<xsl:template match="//foo[true()]">
		Correct text
	</xsl:template>

	<xsl:template name="never" match="never">
		<xsl:variable name="var" select="*[1]" />
	</xsl:template>

</xsl:stylesheet>