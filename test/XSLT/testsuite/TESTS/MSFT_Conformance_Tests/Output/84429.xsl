<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
 
<xsl:output method='xml' omit-xml-declaration="yes"/>  
<xsl:template match="/">  
<xsl:value-of select="//TEXT[1]"/>  

163: &#163;
165: &#165;
174: &#174;
160: &#160;
916: &#916;
<xsl:value-of select="//TEXT[2]"/>  
</xsl:template>  
</xsl:stylesheet>  
