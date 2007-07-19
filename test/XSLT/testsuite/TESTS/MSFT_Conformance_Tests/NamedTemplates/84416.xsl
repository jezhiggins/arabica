<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
<xsl:output method="xml" omit-xml-declaration="yes" />
  
<xsl:template match="AAA">  
<DIV style="color:purple">  
<xsl:value-of select="name()"/>  
<xsl:text> id=</xsl:text>  
<xsl:value-of select="@id"/>  
</DIV>  
</xsl:template>  
 
</xsl:stylesheet>  
