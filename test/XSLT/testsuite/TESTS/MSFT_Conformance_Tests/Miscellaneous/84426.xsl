<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
  
 
<xsl:template match="/">  
<TABLE border='1' width="90%">  
<xsl:apply-templates select="//*"/>  
</TABLE>  
</xsl:template>  
 
<xsl:template match="*">  
<xsl:if test="not(descendant::*[name()=name(current())] | following::*[name()=name(current())])">  
<TR><TD><xsl:value-of select="name()"/></TD>  
<TD><xsl:apply-templates select="." mode='list'/></TD>  
</TR>  
</xsl:if>  
</xsl:template>  
 
<xsl:template match="*" mode='list'>  
 
<xsl:for-each select="//*[name()=name(current())]/*">  
<xsl:value-of select="name()"/>  
</xsl:for-each>  
</xsl:template>  
</xsl:stylesheet>  
  
