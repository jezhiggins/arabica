<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:template match="/">
	<foo>
	    <xsl:number value="'1ab'"/> ; 
	    <xsl:number value="0.42"/>
	</foo>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
