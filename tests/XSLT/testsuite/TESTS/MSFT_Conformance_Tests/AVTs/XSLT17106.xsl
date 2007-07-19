<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<foo bar="{blar}"/>
	<xsl:template match="/" foo="{blar}">
        <xsl:for-each select="child::processing-instruction()">
		<a href="attribute value template at top level elementi are ignored, should not cause error"/>
        </xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
