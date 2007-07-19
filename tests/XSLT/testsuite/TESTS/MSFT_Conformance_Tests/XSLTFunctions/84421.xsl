<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
<xsl:output method="xml" omit-xml-declaration="yes"/> 
<xsl:template match="/">  
<xsl:for-each select="//SELECTEDPRODUCT">  
<P><xsl:text> NAME: </xsl:text>  
<xsl:value-of select="//PRODUCT/NAME[../ID=current()]"/></P>  
</xsl:for-each>  
</xsl:template>  
</xsl:stylesheet>  
