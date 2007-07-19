
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  
 
<xsl:template match="//SECTION">  
<xsl:choose>  
<xsl:when test='SUMMARY'>  
<P><xsl:text> SUMMARY: </xsl:text>  
<xsl:value-of select="SUMMARY"/></P>  
</xsl:when>  
<xsl:otherwise>  
<xsl:for-each select="DATA">  
<P><xsl:text> DATA: </xsl:text>  
<xsl:value-of select="."/></P>  
</xsl:for-each>  
</xsl:otherwise>  
</xsl:choose>  
</xsl:template>  
</xsl:stylesheet>  

