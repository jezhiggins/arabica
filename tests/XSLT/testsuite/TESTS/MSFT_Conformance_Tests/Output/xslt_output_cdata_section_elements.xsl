<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output cdata-section-elements="cdata1"/>
    <xsl:output cdata-section-elements="cdata1"/>

    <xsl:template match="/foo">
    <out>
	<xsl:value-of select="text()"/>
    </out>
    </xsl:template>

</xsl:stylesheet>