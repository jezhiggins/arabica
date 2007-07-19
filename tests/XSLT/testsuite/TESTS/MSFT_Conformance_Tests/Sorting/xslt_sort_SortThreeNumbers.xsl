<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a regression test case for bug 52357. -->

	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match='numbers'>
		<root>
		<xsl:for-each select='number'>
			<xsl:sort order='descending' data-type='number' select='.' />
			<xsl:value-of select='.' />
		</xsl:for-each>
		</root>
	</xsl:template>	

</xsl:stylesheet>