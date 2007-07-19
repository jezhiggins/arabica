<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 
<xsl:template match="/xslTutorial">  
<TABLE border='1'>  
<xsl:apply-templates select="*[@cell='1']"/>  
</TABLE>  
</xsl:template>  
 
<xsl:template match="item/current()">  
<TR>  
<TD><xsl:value-of select="current()"/></TD>  
<TD><xsl:value-of select="//*[name()=name(current()) and @cell='2']"/></TD>  
</TR>  
</xsl:template>  
</xsl:stylesheet>  
