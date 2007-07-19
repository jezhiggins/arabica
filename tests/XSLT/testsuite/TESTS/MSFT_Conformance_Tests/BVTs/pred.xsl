<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output encoding="utf-8" indent="yes" omit-xml-declaration="yes" />

	<xsl:template match="/">
        <xsl:call-template name="test1"/>
        <xsl:call-template name="test2"/>
    </xsl:template>

	<xsl:template name="test1">
        <!-- Regression case for bug 71497 -->
        <test1>
        <xsl:if test="bookstore[@specialty='novel']/book[author/last-name='Bob'] = bookstore[@specialty='novel']/book[not(author/last-name='Bob')]">
            <ERROR/>
        </xsl:if>
        </test1>
    </xsl:template>

	<xsl:template name="test2">
        <!-- Test convoluted boolean expressions -->
        <test2>
        <xsl:if test="bookstore[book[author[last-name][2] = 'Kimball'] or @specialty='novel' and (not(book[title[1]='Unknown']) or book[title[1]='Book 1'])]">
            <SUCCESS/>
        </xsl:if>
        </test2>
	</xsl:template>

</xsl:stylesheet>