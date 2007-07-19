<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting within templates - count - level = "any" - format = <any> -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/04/2000 -->

	<xsl:template match="book">
	    <html><h1>The Book of Chapters</h1>
	    <xsl:apply-templates select="chapter|./chapter/section|./chapter/section/subsection|chapter"/>
		</html>
	</xsl:template>
	    
	<xsl:template match="subsection|section|chapter">
	  <xsl:number count="section" level = "any" format = "i."/>
	  <xsl:value-of select= "name"/><br/>
	</xsl:template>
	        
</xsl:stylesheet>

