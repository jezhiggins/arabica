<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<root>
		<xsl:element name="child1"> abc </xsl:element>
		<xsl:attribute name="aa" namespace="abc">abc</xsl:attribute >
	</root>
</xsl:template>

</xsl:stylesheet>
