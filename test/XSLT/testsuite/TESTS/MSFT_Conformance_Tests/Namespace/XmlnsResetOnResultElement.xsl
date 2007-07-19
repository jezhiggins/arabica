<?xml version='1.0'?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:n='urn:foo' >

    <!-- This stylesheet is a regression test case for bug 71781. -->

    <xsl:output encoding="UTF-8" indent="no" omit-xml-declaration='no' />

    <xsl:template match="//n:book/n:chapter[2]/foo">
	<result>
	<xsl:for-each select='namespace::*'>
	   <f><xsl:value-of select='string()' /></f>
	</xsl:for-each>
	</result>
    </xsl:template>

    <xsl:template match='text()' />

</xsl:stylesheet>
