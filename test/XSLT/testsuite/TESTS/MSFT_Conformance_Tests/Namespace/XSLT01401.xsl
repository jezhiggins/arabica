<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 
<xsl:template match="/">  
<TABLE border="1">  
<TR><TH>text</TH><TH>boolean</TH></TR>  
<xsl:for-each select="//text">  
<TR>  
<TD><xsl:value-of select="."/>  
<xsl:text> </xsl:text>  
</TD>  
<TD><xsl:value-of select="boolean(text())"/></TD>  
</TR>  
</xsl:for-each>  
</TABLE>  
 
</xsl:template>  
</xsl:stylesheet>  


