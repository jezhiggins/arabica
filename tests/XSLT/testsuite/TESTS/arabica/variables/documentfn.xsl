<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output indent="yes" omit-xml-declaration="yes" />

    <!-- Variable containing original xml document-->
    <xsl:variable name="original" select="document('documentfn2.xml')"/>

    <!-- Check to see if its root node -->
    <xsl:template match="/">
	<xsl:copy-of select="($original)" />
    </xsl:template>


</xsl:stylesheet>
