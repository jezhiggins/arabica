<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:attribute-set name="test">
    <!-- Comment should be allowed here -->
	<xsl:attribute name="foo">Comment<!-- Comment should be allowed here --></xsl:attribute>
	<xsl:attribute name="bar">Comment<!-- Comment should be allowed here --></xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
	<out>
    	<xsl:copy use-attribute-sets="test"/>
	</out>
    </xsl:template>

</xsl:stylesheet>