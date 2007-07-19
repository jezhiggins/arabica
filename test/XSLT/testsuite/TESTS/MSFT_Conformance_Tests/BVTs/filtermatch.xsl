<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
        <xsl:comment>bookstore[@specialty='novel'][1]/book[position() &lt; 4][title != 'Book 1']</xsl:comment><xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="bookstore/book" mode="mode1"/><xsl:text>&#xA;</xsl:text>

        <xsl:comment>bookstore[1][@specialty='novel']/book[title != 'Book 1'][position() &lt; 4]</xsl:comment><xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="bookstore/book" mode="mode2"/><xsl:text>&#xA;</xsl:text>

        <xsl:comment>node()[position() = last()][name() = 'bookstore']/book[title != 'Book 1'][position() &lt; last()][position() &lt; last()]</xsl:comment><xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="bookstore/book" mode="mode3"/><xsl:text>&#xA;</xsl:text>

        <xsl:comment>node()[position() = last()][position() = last()][name() = 'bookstore']/book[author/last-name = 'Bob' or author/first-name = 'Hack'][position() = last() or position() = last() - 1]</xsl:comment><xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="bookstore/book" mode="mode4"/><xsl:text>&#xA;</xsl:text>

        <xsl:comment>node()[name() = 'bookstore'][1]/book[title = 'Book 2'][1][title = 'Book 2'][1][title = 'Book 2']</xsl:comment><xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="bookstore/book" mode="mode5"/><xsl:text>&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="bookstore[@specialty='novel'][1]/book[position() &lt; 4][title != 'Book 1']" mode="mode1">
        <xsl:text>Book </xsl:text><xsl:value-of select="position()"/><xsl:text>, </xsl:text>
    </xsl:template>

    <xsl:template match="bookstore[1][@specialty='novel']/book[title != 'Book 1'][position() &lt; 4]" mode="mode2">
        <xsl:text>Book </xsl:text><xsl:value-of select="position()"/><xsl:text>, </xsl:text>
    </xsl:template>

    <xsl:template match="node()[position() = last()][name() = 'bookstore']/book[title != 'Book 1'][position() &lt; last()][position() &lt; last()]" mode="mode3">
        <xsl:text>Book </xsl:text><xsl:value-of select="position()"/><xsl:text>, </xsl:text>
    </xsl:template>

    <xsl:template match="node()[position() = last()][position() = last()][name() = 'bookstore']/book[author/last-name = 'Bob' or author/first-name = 'Hack'][position() = last() or position() = last() - 1]" mode="mode4">
        <xsl:text>Book </xsl:text><xsl:value-of select="position()"/><xsl:text>, </xsl:text>
    </xsl:template>

    <xsl:template match="node()[name() = 'bookstore'][1]/book[title = 'Book 2'][1][title = 'Book 2'][1][title = 'Book 2']" mode="mode5">
        <xsl:text>Book </xsl:text><xsl:value-of select="position()"/><xsl:text>, </xsl:text>
    </xsl:template>

    <xsl:template match="*" mode="mode1"/>
    <xsl:template match="*" mode="mode2"/>
    <xsl:template match="*" mode="mode3"/>
    <xsl:template match="*" mode="mode4"/>
    <xsl:template match="*" mode="mode5"/>

</xsl:stylesheet>
