<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  

<!-- Circular referencing of an xsl:variable is not allowed -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->

<xsl:variable name="var1">7 
	<xsl:value-of select="$var2"/>
</xsl:variable>

<xsl:variable name="var2">
	<xsl:value-of select ="$var13" /> 
</xsl:variable>

</xsl:stylesheet>  
