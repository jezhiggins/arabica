<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 <!-- multilingual xml encoded to 1252, should trash some characters -->
<xsl:output method="xml" encoding="windows-1252"/>  
<xsl:template match="/">  
<xsl:copy-of select="/xslTutorial"/>  
</xsl:template>  

</xsl:stylesheet>  
