<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output method="html"/>
<xsl:template match="/">  
COPY-OF:
<xsl:copy-of select="/html"/>  
GET TEXT:
<xsl:apply-templates select="//HEAD"/>
</xsl:template>  
<xsl:template match="//HEAD">
<HEAD>
<xsl:attribute name = "profile">
<xsl:value-of select="."/>
</xsl:attribute>
</HEAD>
</xsl:template>
</xsl:stylesheet>  
