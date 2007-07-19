<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output omit-xml-declaration="yes"/>

    <xsl:template match="/">
	<xsl:apply-templates select="bookstore/book | document('functions.xml')/functions"/>
    </xsl:template>

    <xsl:template match="book">
	--BOOK: <xsl:value-of select="@style"/>
    </xsl:template>

    <xsl:template match="functions">
	--FUNCTIONS: <xsl:value-of select="count(function)"/>
    </xsl:template>

</xsl:stylesheet>