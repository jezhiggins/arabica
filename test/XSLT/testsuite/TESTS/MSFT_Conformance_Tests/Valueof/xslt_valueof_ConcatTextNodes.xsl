<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output omit-xml-declaration="yes" />

    <xsl:template match="/">
        <root>
	<xsl:apply-templates></xsl:apply-templates>
	</root>
    </xsl:template>

    <xsl:template match="Summary">
	<xsl:for-each select="text()">
		<xsl:element name="e{position()}">
			<xsl:value-of select="."/>
		</xsl:element>
	</xsl:for-each>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
