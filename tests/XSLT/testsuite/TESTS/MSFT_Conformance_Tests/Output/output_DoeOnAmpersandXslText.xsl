<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
 
<xsl:output method="html"/>  
 
<xsl:template match="/">  
<root>
<xsl:text> &amp;</xsl:text>
<xsl:text disable-output-escaping="yes">&amp;amp;</xsl:text>  
</root>
</xsl:template>  
</xsl:stylesheet>  

