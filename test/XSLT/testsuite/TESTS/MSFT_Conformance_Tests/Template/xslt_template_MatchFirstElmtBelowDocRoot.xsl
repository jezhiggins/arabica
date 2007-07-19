<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- This stylesheet is a regression test for bug 59216. It tests to make sure an 
infinite recursion is not performed by the xpath expression below the first
template below. The expression is to evaluate to match the elements below the 
root node. It is not to match the root node itself. -->

    <xsl:output omit-xml-declaration="yes" />

    <xsl:template match="/">
	<xsl:apply-templates select="document('xslt_template_MatchFirstInclude.xml')/*" />
    </xsl:template>

    <xsl:template match="*">
	<xsl:copy/>
    </xsl:template>

</xsl:stylesheet>