<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
  
<xsl:output method="html"/>  
<xsl:template match="/">  
<xsl:apply-templates select="//doc"/>  
<HR/>  
<xsl:for-each select="//ref">  
<xsl:apply-templates select="id(@id)">  
<xsl:with-param name="nmbr"><xsl:value-of select="position()"/></xsl:with-param>  
</xsl:apply-templates>  
</xsl:for-each>  
</xsl:template>  
 
<xsl:template match="ref">  
<SUP><xsl:value-of select="count(//doc/*) - count(following::ref)"/></SUP>  
</xsl:template>  
 
<xsl:template match="note">  
<xsl:param name="nmbr">1</xsl:param>  
<DIV>  
<xsl:number value="$nmbr" format="1. "/>  
<xsl:value-of select="."/>  
</DIV>  
</xsl:template>  
 
</xsl:stylesheet>  

