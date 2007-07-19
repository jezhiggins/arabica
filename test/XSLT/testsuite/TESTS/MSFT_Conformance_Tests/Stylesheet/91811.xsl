<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
extension-element-prefixes="xsl #default" xmlns:foo="http://my.com" xmlns="http://default">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">		
	<myelement>
		<xsl:fallback><xsl:text>An element is instantiated whose prefix has no namespace declared </xsl:text></xsl:fallback>
	</myelement>	
</xsl:template>

</xsl:stylesheet>
