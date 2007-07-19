<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
<!-- Forward variables. -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->

<xsl:output method="html"/>

<xsl:variable name="var" select="$ForwardVar"/>

<xsl:template match="/">
	<html>	
		<head>
			<h1>Forward variables</h1>
			<h3>Sold Books</h3>
		</head>
		<xsl:apply-templates/>
	</html>
</xsl:template>

<xsl:template match="book">
	<xsl:value-of select = "." />
	<h4>Position:<xsl:value-of select="$var+position()"/></h4>
</xsl:template>

<xsl:variable name="ForwardVar" select="0"/>

<xsl:template match="text()"/>

</xsl:stylesheet>