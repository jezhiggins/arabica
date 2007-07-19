<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
<xsl:output method="xml" omit-xml-declaration="yes" />
  
<xsl:template match="/">  
 
<xsl:for-each select="//BBB">  
<DIV style="color:red">  
<xsl:value-of select="name()"/>  
<xsl:text> id=</xsl:text>  
<xsl:value-of select="@id"/>  
</DIV>  
</xsl:for-each>  
 
<xsl:for-each select="xslTutorial/AAA/CCC">  
<DIV style="color:navy">  
<xsl:value-of select="name()"/>  
<xsl:text> id=</xsl:text>  
<xsl:value-of select="@id"/>  
</DIV>  
</xsl:for-each>  
</xsl:template>  
 
</xsl:stylesheet>  
