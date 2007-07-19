<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- This stylesheet is a regression test case for bug 61167. It validates
     that the document function returns a node set containing the root node
     of the Xml document, and that the document function can take a string
     argument. -->

    <xsl:output omit-xml-declaration="yes" />

    <xsl:template match="/">
	<xsl:apply-templates select="document('xslt_template_DocumentFnTakesStringParam2.xml')" mode="bar"/>
    </xsl:template>

    <xsl:template match="/" mode="bar">
	<foo/>
    </xsl:template>

</xsl:stylesheet>