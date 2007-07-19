<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
<xsl:output method="xml" omit-xml-declaration="yes" />
 
<xsl:variable name="A" select="number(//number[1])"/>  
<xsl:variable name="B" select="number(//number[2])"/>  
<xsl:variable name="C" select="number(//number[3])"/>  
<xsl:variable name="D" select="number(//number[4])"/>  
 
<xsl:template match="/">  
<P><xsl:value-of select="string(number($A))"/></P>  
<P><xsl:value-of select="string(number($D))"/></P>  
<P>  
<xsl:value-of select="$A"/><xsl:text> /</xsl:text>  
<xsl:value-of select="$B"/><xsl:text> = </xsl:text>  
<xsl:value-of select="string($A div $B)"/></P>  
<P>  
<xsl:value-of select="$C"/><xsl:text> /</xsl:text>  
<xsl:value-of select="$B"/><xsl:text> = </xsl:text>  
<xsl:value-of select="string($C div $B)"/></P>  
<P>  
<xsl:value-of select="$B"/><xsl:text> /</xsl:text>  
<xsl:value-of select="$B"/><xsl:text> = </xsl:text>  
<xsl:value-of select="$B div $B"/></P>  
</xsl:template>  
</xsl:stylesheet>  
