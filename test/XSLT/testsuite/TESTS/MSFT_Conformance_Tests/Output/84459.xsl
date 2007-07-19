<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output method="html" omit-xml-declaration="yes"/>
<xsl:template match="/">  
COPY-OF:
<xsl:copy-of select="/html"/>  
GET TEXT:
<xsl:apply-templates select="//FORM"/>
</xsl:template>  
<xsl:template match="//FORM">
<FORM>
<xsl:attribute name = "action">
<xsl:value-of select="."/>
</xsl:attribute>
</FORM>
</xsl:template>
</xsl:stylesheet>  
