<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">

<!-- This is a test for bug # 70832 -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:key name="authors" match="author" use="first-name"/>

<xsl:template match="/">
	<first-name>
	<xsl:value-of select="key('authors', 'Mary')[1]/first-name"/>
	</first-name>
</xsl:template>

</xsl:stylesheet>