<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="no" />

    <xsl:variable name="foo" select="'global'"/>

    <xsl:template match="/">
	<xsl:variable name="foo">
		<xsl:variable name="foo" select="concat('local from ', $foo)"/>
		<xsl:value-of select="$foo"/>
	</xsl:variable>

      <root>
	<xsl:value-of select="$foo"/>
      </root>

    </xsl:template>

</xsl:stylesheet>
