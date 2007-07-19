<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output method="html"/>  
<xsl:template match="/">  
<xsl:copy-of select="/pitest"/>  

- <xsl:processing-instruction name="a">
  <xsl:element name="x">1</xsl:element> 
  </xsl:processing-instruction>
  </xsl:template>
  
</xsl:stylesheet>  
