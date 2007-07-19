<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
        <xsl:call-template name="foo"><xsl:sort select="foo"/></xsl:call-template>
    </xsl:template>

</xsl:stylesheet>