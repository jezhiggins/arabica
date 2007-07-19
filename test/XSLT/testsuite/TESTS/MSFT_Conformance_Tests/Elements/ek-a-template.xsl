<?xml version='1.0'?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="*" />
</xsl:template>

<xsl:template match="*">true</xsl:template>

</xsl:stylesheet>

<!-- Extra PI, should be harmless -->
<?Extra PI, should be harmless ?>
