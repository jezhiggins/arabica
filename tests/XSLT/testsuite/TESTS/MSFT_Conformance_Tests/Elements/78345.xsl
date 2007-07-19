<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
>

	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

   	<!-- Test various combinations of name and namespace AVT's -->
	<xsl:template match="/">
    		<xsl:element name="foo" namespace="bar">
			<xsl:element name="x"/>
    		</xsl:element>
	</xsl:template >

</xsl:stylesheet>
