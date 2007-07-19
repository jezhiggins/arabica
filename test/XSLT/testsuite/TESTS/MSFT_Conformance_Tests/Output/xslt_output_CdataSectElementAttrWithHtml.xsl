<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

    <!-- This stylesheet is a regression test case for bug 66801. -->

    <xsl:output method="html" cdata-section-elements="foo span" omit-xml-declaration="yes" encoding='utf-8' indent='no' />

    <xsl:template match="/">

	    <foo>bar</foo>
	    <span>bar</span>

    </xsl:template>

</xsl:stylesheet>
