<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a regression test case for bug 52357. -->

	<xsl:output omit-xml-declaration="yes" indent="no" />

	<xsl:template match='numbers'>
		<root>
		<xsl:for-each select='number'>
			<xsl:sort order='ascending' data-type='number' select='.' />
			<number>
			<xsl:value-of select='.' />
			</number>
		</xsl:for-each>
		<xsl:for-each select='number'>
			<xsl:sort order='descending' data-type='number' select='.' />
			<number>
			<xsl:value-of select='.' />
			</number>
		</xsl:for-each>
		</root>
	</xsl:template>	

</xsl:stylesheet>