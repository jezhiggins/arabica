<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output method="text" media-type="text/plain"/>  

<xsl:template match="/">
    <xsl:apply-templates select="xslTutorial"/>
</xsl:template>

<xsl:template match="AAA">  
<xsl:text> &lt;!ELEMENT </xsl:text>  
<xsl:value-of select="name()"/>  
<xsl:text> ANY></xsl:text>  
 
<xsl:text> &lt;!ATTLIST </xsl:text>  
<xsl:value-of select="name()"/>  
<xsl:text> </xsl:text>  
<xsl:value-of select="name(@*)"/>  
<xsl:text> ID #REQUIRED></xsl:text>  
 
<xsl:text> Look at my source in your browser</xsl:text>  
</xsl:template>  
</xsl:stylesheet>  
