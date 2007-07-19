<?xml version="1.0"?>
<xsl:stylesheet version="1.0" 
	xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
	xmlns:my='urn:http//www.placeholder-name-here.com/schema/' >  

<xsl:template match="/">
<xsl:variable name="x" select="/bookstore/book"/>
<xsl:copy-of select="$x"/>
</xsl:template>

</xsl:stylesheet>  
