<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output method="html" version='4'/>  
<xsl:template match="/">  
COPY-OF:
<xsl:copy-of select="/xslTutorial"/>  
GET TEXT:
<xsl:apply-templates select="//script"/>
</xsl:template>  
<xsl:template match="//script">
<script>
<xsl:value-of select="."/>
</script>
<foo>
<xsl:value-of select="."/>
</foo>
</xsl:template>
</xsl:stylesheet>  
