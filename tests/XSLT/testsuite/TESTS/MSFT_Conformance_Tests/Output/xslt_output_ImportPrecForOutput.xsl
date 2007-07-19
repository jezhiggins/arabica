<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- This stylesheet is a regression test case for bug 65746. It validates import precedence
	 occuring namespace alias for the included/imported stylesheets is correct. -->

    <xsl:output indent="no" omit-xml-declaration="yes"/>

    <xsl:include href="xslt_output_ImportPrecForOutput1.xsl"/>

    <xsl:template match="/">
	<foo>
	  <bar/>
	  <bar> more text is here</bar>
        </foo>
    </xsl:template>

</xsl:stylesheet>