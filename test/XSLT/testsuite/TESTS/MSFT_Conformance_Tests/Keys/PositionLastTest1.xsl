<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:key name="foo" match="BBB" use="@bbb"/>

    <xsl:template match="AAA">
	<out>
        <xsl:for-each select="key('foo', '11')">
		Value: <xsl:value-of select="."/>,
	        Position: <xsl:value-of select="position()"/>,
	        Last: <xsl:value-of select="last()"/>,
        </xsl:for-each>
	</out>
    </xsl:template>
</xsl:stylesheet>
