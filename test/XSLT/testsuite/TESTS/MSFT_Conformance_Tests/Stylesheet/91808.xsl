<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
extension-element-prefixes="xsl #default" xmlns:foo="http://my.com" xmlns="http://default">

<xsl:import href="91808a.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes"/>



<xsl:template match="/">
	<foo:myelement>
		
	</foo:myelement>
	<xsl:apply-imports/>
</xsl:template>

</xsl:stylesheet>
