<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	
<!-- Purpose: Test case for bug 71216. Namespace nodes on different elements should have different generate-ids. -->

	<xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="no" indent="yes"/>

	<xsl:template match="/">
		<not-equals><xsl:value-of select="generate-id(/bookstore/namespace::my) != generate-id(/bookstore/book/namespace::my)" /></not-equals>
	</xsl:template>
</xsl:stylesheet>