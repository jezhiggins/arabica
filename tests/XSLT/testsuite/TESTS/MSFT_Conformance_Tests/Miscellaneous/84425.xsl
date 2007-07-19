<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
  
 
<xsl:template match="/">  
<xsl:for-each select="/descendant::*">  
<xsl:variable name="pos" select="position()"/>  
<xsl:variable name="name" select="name()"/>  
<xsl:if test="not(/descendant::*[position() &lt; $pos and name()= $name])">  
<P><xsl:value-of select="$name"/>  
<xsl:text> [</xsl:text>  
<xsl:for-each select="//*[name()=$name]/*">  
<xsl:variable name="p" select="position()"/>  
<xsl:if test="not(//*[name()=$name]/*[position()&lt; $p and name()=name(current())])">  
<xsl:value-of select="name()"/><xsl:text> , </xsl:text>  
</xsl:if>  
</xsl:for-each>  
<xsl:text> ]</xsl:text>  
</P>  
</xsl:if>  
</xsl:for-each>  
</xsl:template>  
</xsl:stylesheet>  
