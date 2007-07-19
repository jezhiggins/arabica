<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:for-each select="//fruit">
		<xsl:sort select="elem/@a" order="ascending"/>
			<xsl:value-of select="@name" />,<value-of select="elem/@a" />;
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>

