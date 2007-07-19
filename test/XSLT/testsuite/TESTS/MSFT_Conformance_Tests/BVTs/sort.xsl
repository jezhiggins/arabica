<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">

		<xsl:for-each select="//author">
			<xsl:sort select="last-name"/>
			<xsl:sort select="first-name"/>
			<name><xsl:value-of select="last-name"/><xsl:text>, </xsl:text><xsl:value-of select="first-name"/></name>
		</xsl:for-each>

		<xsl:for-each xml:space="preserve" select="//author">
			<!-- Comment, PI, and white space nodes -->
			<![CDATA[		]]>
            <?my-pi?>
			<xsl:sort select="last-name"/>
			Whitespace
		</xsl:for-each>

		<xsl:for-each select="//price">
			<xsl:sort order="descending" data-type="number"/>
			<price><xsl:value-of select="."/></price>
			<xsl:for-each select="../author">
				<xsl:sort select="." order="ascending" data-type="text"/>
				<by><xsl:value-of select="first-name"/></by>
			</xsl:for-each>
		</xsl:for-each>

        <xsl:apply-templates select="bookstore/book[1]"/>

        <xsl:call-template name="test-sort-query"/>

        <!-- Sort paths bug (bug 58394) -->
        <max-depth>
        <xsl:for-each select="//node()">
            <xsl:sort select="count(ancestor::node())" order="descending"/>
            <xsl:if test="position() = 1">
                <xsl:value-of select="count(ancestor::node())"/>
            </xsl:if>
        </xsl:for-each>
        </max-depth>

    </xsl:template>

    <!-- Recursive sorting (bug 46932) -->
    <xsl:template match="*">
        <name><xsl:value-of select="name()"/></name>
        <xsl:apply-templates select="*">
            <xsl:sort select="name()"/>
        </xsl:apply-templates>
    </xsl:template>

    <xsl:template name="test-sort-query">
        <xsl:for-each select="//title">
            <xsl:sort select="last()" data-type="number"/>
            <xsl:sort select="position()" data-type="number"/>
            <last><xsl:value-of select="last()"/></last><pos><xsl:value-of select="position()"/></pos><xsl:copy-of select="."/>
        </xsl:for-each>

        <xsl:for-each select="/bookstore/book/author/last-name">
            <xsl:sort select="self::node()[current() = .]"/>
            <last-name><xsl:value-of select="."/></last-name>
        </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>
