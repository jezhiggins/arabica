<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
	xmlns:x="urn:foo"   
>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<xsl:template match="//bookstore">
        <xsl:for-each select="book">
		<a xmlns="{@style}"/>
		<a xmlns:x="{@style}"/>
		<a x:xmlns="{@style}"/>
        </xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
