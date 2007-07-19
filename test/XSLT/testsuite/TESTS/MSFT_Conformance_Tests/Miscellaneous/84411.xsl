<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
<xsl:output method="xml" omit-xml-declaration="yes" />
  
<xsl:template match="/">  
<xsl:apply-templates select="//CCC"/>  
<xsl:apply-templates select="//AAA"/>  
</xsl:template>  
 
<xsl:template match="CCC">  
<H3 style="color:blue">  
<xsl:value-of select="name()"/>  
<xsl:text> (id=</xsl:text>  
<xsl:value-of select="@id"/>  
<xsl:text> )</xsl:text>  
</H3>  
</xsl:template>  
 
<xsl:template match="*">  
<H3 style="color:maroon">  
<xsl:value-of select="name()"/>  
<xsl:text> (id=</xsl:text>  
<xsl:value-of select="@id"/>  
<xsl:text> )</xsl:text>  
</H3>  
</xsl:template>  
 
 
</xsl:stylesheet>  
