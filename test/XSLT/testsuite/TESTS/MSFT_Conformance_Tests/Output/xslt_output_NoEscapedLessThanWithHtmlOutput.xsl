<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>

    <xsl:template match="/">
	<foo bar="&lt;bar&gt;"/>
    </xsl:template>

</xsl:stylesheet>

