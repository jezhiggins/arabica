<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <!-- This stylesheet is a regression test case for bug 66580 -->

    <xsl:template match="/">

    	<xsl:variable name="x" select="$y"></xsl:variable>
    	<xsl:variable name="y" select="foo"></xsl:variable>
	
    </xsl:template>
    

</xsl:stylesheet>
