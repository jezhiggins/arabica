<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- This is a regression test case for bug 65771. It validates that an exception is
         thrown when there is an invalid element in the stylesheet. -->

    <xsl:output omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
	<xsl:attribute name="foo">foo</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
	<literal xsl:use-attribute-sets="foo" />
    </xsl:template>

	text is not allowed

</xsl:stylesheet>

