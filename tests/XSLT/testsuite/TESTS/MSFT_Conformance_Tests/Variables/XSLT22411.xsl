<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:variable name="X" select="bookstore/book/@style"/>
    <xsl:template match="/">
	<Level1>
	    <BookStore>
		<xsl:attribute name="book_count">
		    <xsl:variable name="X" select="bookstore/book"/>
        	    <xsl:value-of select="count($X)"/>
		</xsl:attribute>
		<xsl:variable name="X" select="bookstore/@specialty"/>
		<xsl:value-of select="$X"/>
	    </BookStore>
	    <xsl:variable name="X" select="bookstore/book"/>
            <xsl:apply-templates select="$X"></xsl:apply-templates>
	</Level1>
    </xsl:template>
    <xsl:template match="book">
        <title>
            <xsl:variable name="X" select="title"/>
	    <xsl:value-of select="$X"></xsl:value-of>
        </title>
	<xsl:element name="style">
		<xsl:value-of select="$X"/>
	</xsl:element>
    </xsl:template>
    <xsl:template match="text()"/>
</xsl:stylesheet>
