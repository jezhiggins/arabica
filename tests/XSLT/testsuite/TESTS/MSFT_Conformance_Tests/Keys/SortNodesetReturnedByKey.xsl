<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template match="/">
	<out>
	<xsl:apply-templates select="key('prices','1')">
		<xsl:sort select="@attr"/>
	</xsl:apply-templates>
	</out>
    </xsl:template>

    <xsl:template match="price">
	<xsl:value-of select="."/>,
    </xsl:template>

    <xsl:key name="prices" match="price" use="@foo"/>

</xsl:stylesheet>