<!-- Regression test for bug 54101 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template match="/">
	<root> 3 <![CDATA[<]]> 5 </root>
    </xsl:template>

</xsl:stylesheet>