<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
<xsl:output method="xml" omit-xml-declaration="yes" /> 
 
<xsl:template match="/">  
<TABLE>  
<xsl:for-each select="//*[@*]">  
<xsl:call-template name="elementTemplate"/>  
</xsl:for-each>  
</TABLE>  
</xsl:template>  
 
<xsl:template name="elementTemplate">  
<TR><TH><xsl:value-of select="name(.)"/></TH>  
<TD><xsl:call-template name="attributeTemplate"/></TD></TR>  
</xsl:template>  
 
<xsl:template name="attributeTemplate" match="attributeTemplate">  
<xsl:for-each select="@*">  
<xsl:value-of select="name()"/>  
<xsl:text> =</xsl:text>  
<xsl:value-of select="."/>  
<xsl:text> </xsl:text>  
</xsl:for-each>  
</xsl:template>  
</xsl:stylesheet>  
