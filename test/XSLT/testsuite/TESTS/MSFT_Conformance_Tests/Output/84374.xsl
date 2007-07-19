<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
  
<xsl:output method="html" encoding="UTF-8"/>  
<xsl:template match="/">  
<xsl:copy-of select="/xslTutorial/*"/>  
</xsl:template>  
</xsl:stylesheet>  
