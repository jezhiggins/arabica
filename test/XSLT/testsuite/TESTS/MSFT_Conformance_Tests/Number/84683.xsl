<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting - count - format = "A." -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/04/2000 -->


<xsl:template match="book">
    <html><h1>The Book of Chapters</h1>
    <xsl:apply-templates select="chapter|./chapter/section"/>
	</html>
</xsl:template>
    
<xsl:template match="chapter|section|name">
  <xsl:number count="section" format = "A."/>
  <xsl:value-of select= "name"/><br/>
</xsl:template>
        
</xsl:stylesheet>

