<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" indent="yes" omit-xml-declaration="yes"/>


	<xsl:template match="/">
                <xsl:for-each select="sorting/data">
                    <xsl:sort lang="sv" data-type="number"/>
                    <xsl:value-of select="."/><xsl:text>, </xsl:text>
                </xsl:for-each>
	</xsl:template>

</xsl:stylesheet>