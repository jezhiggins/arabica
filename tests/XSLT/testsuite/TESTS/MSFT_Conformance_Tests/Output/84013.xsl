<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 <!-- output method="text" with foo attribute -->
<xsl:output foo="bar" method="text"  />  
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
