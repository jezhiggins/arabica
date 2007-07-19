<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

<!-- XSLT: Number formatting - xsl:number at the document root -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 04/18/2000 -->

	<xsl:template match="/">
	    <H2><xsl:text>Numbering at the document root</xsl:text></H2><BR/>
	    <xsl:text>xsl:number - </xsl:text><xsl:number/><BR/>
	    <xsl:text>level = "single" -</xsl:text><xsl:number level="single"/><BR/>
	    <xsl:text>level = "multiple" -</xsl:text><xsl:number level="multiple" from="/"/><BR/>
		<xsl:text>level = "any" - </xsl:text><xsl:number level="any"/><BR/>
	</xsl:template>
   
</xsl:stylesheet>  
