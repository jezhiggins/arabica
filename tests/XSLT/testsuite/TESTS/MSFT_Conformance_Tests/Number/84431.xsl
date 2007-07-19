<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
<xsl:output method="xml" omit-xml-declaration="yes" />
 
<xsl:template match="number">  
<DIV><xsl:value-of select="."/>  
<xsl:if test= "string(number(.))='NaN'"> is not a number</xsl:if> </DIV>  
</xsl:template>  
</xsl:stylesheet>  

 


