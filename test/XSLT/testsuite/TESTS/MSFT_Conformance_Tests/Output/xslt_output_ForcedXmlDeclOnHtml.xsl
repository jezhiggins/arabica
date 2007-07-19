<?xml version="1.0"?> 

<!-- This is a regression case for bug 58690. This regression case tests whether an
XML declaration is output to a file that is supposed to be html (method="html"). This
is not supposed to happen, no XML declaration should occur -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" omit-xml-declaration="no" />

    <xsl:template match="/">
	<foo>bar</foo>
    </xsl:template>

</xsl:stylesheet>

