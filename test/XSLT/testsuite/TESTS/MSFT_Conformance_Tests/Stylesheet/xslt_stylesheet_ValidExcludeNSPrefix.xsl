<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		xmlns:foo="urn:bar"
		xmlns:big="urn:dog"
		exclude-result-prefixes="foo">

<xsl:output omit-xml-declaration="yes" />

<xsl:template match="/">
	<foo />
	<test xsl:exclude-result-prefixes="big" />
</xsl:template>

</xsl:stylesheet>