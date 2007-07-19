<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
 
<xsl:output method="xml" omit-xml-declaration="yes"/>  
<xsl:template match="/">  
<xsl:text> &amp;</xsl:text>  
<xsl:text disable-output-escaping="yes">&amp;</xsl:text>  
</xsl:template>  
</xsl:stylesheet>  


