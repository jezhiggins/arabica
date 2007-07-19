<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<root>
		<xsl:processing-instruction name="pppppppp" xmlns="aa" namespace="aa"> pi node 
			<xsl:element name="aa" namespace="abc">abc</xsl:element>
			<xsl:attribute name="aa" namespace="abc">abc</xsl:attribute >
			<xsl:element name="aa" namespace="abc">abc</xsl:element>
			<xsl:attribute name="aa" namespace="abc">abc</xsl:attribute >
		</xsl:processing-instruction>
		<xsl:comment name="xxxxxxxxx" xmlns="aa" namespace="aa"> comment 1 
			<xsl:element name="aa" namespace="abc">abc</xsl:element>
			<xsl:attribute name="aa" namespace="abc">abc</xsl:attribute >
			<xsl:element name="aa" namespace="abc">abc</xsl:element>
			<xsl:attribute name="aa" namespace="abc">abc</xsl:attribute >
		</xsl:comment>
	</root>

</xsl:template>
</xsl:stylesheet>
