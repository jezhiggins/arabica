<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:myxsl="temp_namespace">

    <xsl:preserve-space elements="foo"/>

    <xsl:strip-space elements="*"/>

    <xsl:template match="root">
	<xsl:copy-of select="foo"/>
	<xsl:copy-of select="bar"/>
    </xsl:template>
</xsl:stylesheet>