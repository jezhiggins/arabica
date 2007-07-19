<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
>
	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
	<root>
		<xsl:apply-templates/>
	</root>
	</xsl:template> 

	<xsl:template match="book">
		<xsl:element name="a7:a:b" xmlns="aaa" namespace="a:b"  />
	</xsl:template >

	<xsl:template match="text()" />


</xsl:stylesheet>
