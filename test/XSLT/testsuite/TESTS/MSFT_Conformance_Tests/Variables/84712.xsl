<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
<!-- Variable casting. -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->

<xsl:output method="html"/>

<xsl:param name="var1" select="123" />
<xsl:param name="var2">text</xsl:param>
<xsl:param name="var3" select="sold_books/book/name" />
<xsl:param name="var4" select="0" />
<xsl:param name="var5" />

<xsl:template match="/">
	<html>	
		<head>
			<h1>Variable casting.</h1>
			<h4>string(123) = "<xsl:value-of select="string($var1)"/>"</h4>
			<h4>number("text") = <xsl:value-of select="number($var2)"/></h4>
			<h4>string("sold_books/book") = <xsl:value-of select="string($var3)"/></h4>
			<h4>boolean("sold_books/book") = <xsl:value-of select="boolean($var3)"/></h4>
			<h4>boolean("") = <xsl:value-of select="boolean($var5)"/></h4>
			<h4>boolean(0) = <xsl:value-of select="boolean($var4)"/></h4>
			<h4>boolean(123) = <xsl:value-of select="boolean($var1)"/></h4>
			<h4>string(123/0) = <xsl:value-of select="string($var1 div $var4)"/></h4>

		</head>
		<xsl:apply-templates/>
	</html>
</xsl:template>

<xsl:template match = "book" />


</xsl:stylesheet>