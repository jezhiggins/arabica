
<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:template match="/bookstore/*">  
	<xsl:call-template name="book" />  
 
</xsl:template>  
 
<xsl:template name="book" match="book">  
<xsl:value-of select="name()"/>  
<xsl:text> </xsl:text>  
</xsl:template>
<xsl:template name="book" match="magazine">  
<xsl:value-of select="name()"/>  
<xsl:text> </xsl:text>  
</xsl:template>

</xsl:stylesheet>  

