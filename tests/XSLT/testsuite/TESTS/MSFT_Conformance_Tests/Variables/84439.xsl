<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
 
<xsl:variable name="var1" select="//AAA/CCC/text()"/>  
<xsl:variable name="var2">//AAA/CCC/text()</xsl:variable>  
 
<xsl:template match="/">  
<xsl:call-template name="function">  
<xsl:with-param name='path1' select='//AAA/CCC/DDD'/>  
<xsl:with-param name='path2'>//AAA/CCC/DDD</xsl:with-param>  
</xsl:call-template>  
</xsl:template>  
 
<xsl:template name="function">  
<xsl:param name="path1"/>  
<xsl:param name="path2"/>  
<P><xsl:value-of select="$path2"/>  
<xsl:text> : </xsl:text>  
<xsl:value-of select="$path1"/>  
</P>  
<P><xsl:value-of select="$var2"/>  
<xsl:text> : </xsl:text>  
<xsl:for-each select="$var1">  
<xsl:value-of select="."/><xsl:text> </xsl:text>  
</xsl:for-each>  
</P>  
</xsl:template>  
</xsl:stylesheet>  



 


