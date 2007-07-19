<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a regression test case for bug 52357. -->

	<xsl:output omit-xml-declaration="yes" indent="no" encoding='utf-8' />

	<xsl:template match='words'>
		<root>
		<xsl:for-each select='text'>
			<xsl:sort order='ascending' lang='en' data-type='text' select='.' case-order='lower-first'/>
			<text>
			<xsl:value-of select='.' />
			</text>
		</xsl:for-each>
		Split Here
		<xsl:for-each select='text'>
			<xsl:sort order='descending' lang='en' data-type='text' select='.' case-order='lower-first'/>
			<text>
			<xsl:value-of select='.' />
			</text>
		</xsl:for-each>
		</root>
	</xsl:template>	

</xsl:stylesheet>