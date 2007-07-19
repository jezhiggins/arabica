<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- This is a regression test case for bug 60311. It passes a valid path to the document function
which should return a root node to that document -->

    <xsl:output indent="yes" omit-xml-declaration="yes" />

    <!-- Variable containing original xml document-->
    <xsl:variable name="original" select="document('\\\\webxtest\\managedshadow\\managed_b2\\testdata\\xslt\\element\\xslt_element_NSShared.xml')"/>

    <!-- Check to see if its root node -->
    <xsl:template match="/">
	<xsl:value-of select="($original)" />
    </xsl:template>


</xsl:stylesheet>