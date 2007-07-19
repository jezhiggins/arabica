<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
 
<xsl:output method='html'/>  
<xsl:template match="/">  
<xsl:value-of select="//TEXT[1]"/>  
&#160;&#160;&#160;&#160;&#160;  
<xsl:value-of select="//TEXT[2]"/>  
</xsl:template>  
</xsl:stylesheet>  
