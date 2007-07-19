<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
 
<xsl:template match="/">  
<xsl:call-template name="generateTable">  
<xsl:with-param name="inRow" select="3"/>  
</xsl:call-template>  
<xsl:call-template name="generateTable">  
<xsl:with-param name="inRow" select="4"/>  
</xsl:call-template>  
<xsl:call-template name="generateTable">  
<xsl:with-param name="inRow" select="5"/>  
</xsl:call-template>  
</xsl:template>  
 
<xsl:template name="generateTable">  
<xsl:param name="inRow"/>  
<xsl:variable name="text">  
<xsl:for-each select="//item">  
<xsl:sort order="ascending" select="."/>  
<xsl:value-of select="."/>  
<xsl:choose>  
<xsl:when test='position()=last()'>  
<xsl:text> XCELLSXXROWSX</xsl:text>  
</xsl:when>  
<xsl:when test='position() mod $inRow'>  
<xsl:text> XCELLSX</xsl:text>  
</xsl:when>  
<xsl:otherwise>  
<xsl:text> XCELLSXXROWSX</xsl:text>  
</xsl:otherwise>  
</xsl:choose>  
</xsl:for-each>  
</xsl:variable>  
 
<TABLE border="1">  
<xsl:call-template name="rows">  
<xsl:with-param name="string" select="$text"/>  
</xsl:call-template>  
</TABLE>  
</xsl:template>  
 
<xsl:template name="rows">  
<xsl:param name="string"/>  
<TR>  
<xsl:call-template name="cells">  
<xsl:with-param name='string'><xsl:value-of select="substring-before($string,'XROWSX')"/>  
</xsl:with-param>  
</xsl:call-template>  
</TR>  
<xsl:if test="string-length($string)">  
<xsl:call-template name="rows">  
<xsl:with-param name='string'><xsl:value-of select="substring-after($string,'XROWSX')"/>  
</xsl:with-param>  
</xsl:call-template>  
</xsl:if>  
</xsl:template>  
 
<xsl:template name="cells">  
<xsl:param name="string"/>  
<TD>  
<xsl:value-of select="substring-before($string,'XCELLSX')"/>  
</TD>  
<xsl:if test="string-length($string)">  
<xsl:call-template name="cells">  
<xsl:with-param name='string'><xsl:value-of select="substring-after($string,'XCELLSX')"/>  
</xsl:with-param>  
</xsl:call-template>  
</xsl:if>  
</xsl:template>  
 
</xsl:stylesheet>  
