<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
>

	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	
   	<!-- Test various combinations of name and namespace AVT's -->
	<xsl:template match="/">
    <root>
    		<xsl:element name="展覧会情報ナーの徘徊レポートは" namespace="bar"/>
    		<xsl:element name="永恆千禧心" namespace="bar"/>
    </root>
	</xsl:template >

</xsl:stylesheet>
