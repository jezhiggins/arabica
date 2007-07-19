<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
<xsl:output method="xml" omit-xml-declaration="yes" />
 
 <xsl:template match="/xslTutorial/*">  
<p>  
<xsl:call-template name="while">  
<xsl:with-param name="test">  
<xsl:value-of select="@repeat"/>  
</xsl:with-param>  
</xsl:call-template>  
</p>  
</xsl:template>  
 
<xsl:template name="while">  
<xsl:param name="test"/>  
<xsl:value-of select="name()"/>  
<xsl:text> </xsl:text>  
 
<xsl:if test="not($test = 1)">  
<xsl:call-template name="while">  
<xsl:with-param name="test">  
<xsl:value-of select="$test - 1"/>  
</xsl:with-param>  
</xsl:call-template>  
</xsl:if>  
 
</xsl:template>  
</xsl:stylesheet>  
