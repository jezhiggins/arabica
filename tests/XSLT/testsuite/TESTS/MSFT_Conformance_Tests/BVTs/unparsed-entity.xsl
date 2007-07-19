<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

	<xsl:template match="/">

        <no-entities><xsl:value-of select="unparsed-entity-uri('unk')"/></no-entities>

        <xsl:for-each select="document('unparsed-entity.xml')">
            <relative><xsl:value-of select="substring(unparsed-entity-uri('pic'), string-length(unparsed-entity-uri('pic')) - 19)"/></relative>
            <absolute><xsl:value-of select="unparsed-entity-uri('pic2')"/></absolute>
            <name-expr><xsl:value-of select="unparsed-entity-uri(concat('p', 'i', 'c', '2'))"/></name-expr>
            <not-found><xsl:value-of select="unparsed-entity-uri('unk')"/></not-found>
        </xsl:for-each>

    </xsl:template>

</xsl:stylesheet>
