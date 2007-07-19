<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 
<xsl:output method="xml" encoding="shift_jis"/>  
<xsl:template match="/">  
<xsl:copy-of select="/xslTutorial"/>  
</xsl:template>  
<xsl:output method="xml" encoding="utF-8"/>  
<xsl:template match="/">  
<xsl:copy-of select="/xslTutorial"/>  
</xsl:template>  

</xsl:stylesheet>  
