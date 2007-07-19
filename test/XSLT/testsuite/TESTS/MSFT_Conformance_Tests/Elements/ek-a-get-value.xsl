<?xml version='1.0'?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:apply-templates select="//deep" />
</xsl:template>

<xsl:template match="*">
	<xsl:value-of select="." />
</xsl:template>
</xsl:stylesheet>

<!-- Extra comment, should be harmless -->
<?Extra PI, should be harmless ?>
