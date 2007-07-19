<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
<xsl:output method="xml" omit-xml-declaration="yes" />  
 
<xsl:template match="/xslTutorial/*">  
<p>  
<xsl:call-template name="for">  
<xsl:with-param name="stop">  
<xsl:value-of select="@repeat"/>  
</xsl:with-param>  
</xsl:call-template>  
</p>  
</xsl:template>  
 
<xsl:template name="for">  
<xsl:param name="start">1</xsl:param>  
<xsl:param name="stop">1</xsl:param>  
<xsl:param name="step">1</xsl:param>  
 
<xsl:value-of select="name()"/>  
<xsl:text> </xsl:text>  
 
<xsl:if test="$start &lt; $stop">  
<xsl:call-template name="for">  
<xsl:with-param name="stop">  
<xsl:value-of select="$stop"/>  
</xsl:with-param>  
<xsl:with-param name="start">  
<xsl:value-of select="$start + $step"/>  
</xsl:with-param>  
</xsl:call-template>  
</xsl:if>  
</xsl:template>  
</xsl:stylesheet>  

  
