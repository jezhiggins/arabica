<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
extension-element-prefixes="foo xsl #default" xmlns:foo="http://my.com" xmlns="http://default">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">

	<foo:myelement>
		<xsl:fallback>foo:myelement is not available</xsl:fallback>
	</foo:myelement>

</xsl:template>

</xsl:stylesheet>
