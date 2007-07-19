<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
<xsl:output method="xml" omit-xml-declaration="yes" />
 
<xsl:template match="/">  
<xsl:apply-templates select="//value"/>  
</xsl:template>  
 
<xsl:template match="value">  
<P>  
<xsl:value-of select="."/>  
<xsl:if test="starts-with(translate(., '0123456789', '9999999999'), '9')">  
<xsl:text> (the text starts with a number)</xsl:text>  
</xsl:if>  
 
</P>  
</xsl:template>  
</xsl:stylesheet>  


 


