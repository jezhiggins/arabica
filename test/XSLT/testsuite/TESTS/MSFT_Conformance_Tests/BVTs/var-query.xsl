<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:variable name="query" select=".//author"/>
	<xsl:variable name="query2" select="bookstore/book"/>
	<xsl:variable name="query3" select="$query/last-name"/>

	<xsl:template match="/">
		<q1>
		<xsl:for-each select="$query">
			<xsl:value-of select="last-name"/>
		</xsl:for-each>
		</q1>
		<xsl:apply-templates select="bookstore"/>
	</xsl:template>

	<xsl:template match="bookstore">
		<xsl:variable name="composed" select="$query/last-name"/>

		<!-- Compose variable within query -->
		<q2>
		<xsl:for-each select="$query/first-name">
			<xsl:value-of select="."/>
		</xsl:for-each>
		</q2>

		<!-- Test Query compare method & Nested variables -->
		<q3>
		<xsl:for-each select="book[$composed = ./author/last-name]">
			<xsl:value-of select="./title"/>
		</xsl:for-each>
		</q3>

		<!-- Test Query isTrue, Index, isEnd methods & Unioned variables-->
		<q4>
		<xsl:for-each select="($query | $query)[1]">
			<xsl:value-of select="$composed and $query"/>
			<xsl:for-each select="$query[1]">
				<xsl:value-of select="last-name"/>
			</xsl:for-each>
			<q5/>

			<xsl:for-each select="$query2[last() - 1]">
				<xsl:value-of select="author/last-name"/>
			</xsl:for-each>
		</xsl:for-each>
		</q4>

        <!-- Bug 48790: Test using variable within a loop that's using it -->
        <q6>
            <xsl:for-each select="$query3">
                <xsl:value-of select="$query3"/>
            </xsl:for-each>
        </q6>

        <!-- Bug 48909: Use "naked" position() function when context query is a variable reference -->
        <q7>
            <xsl:variable name="templ_var" select="(/bookstore/book/author/last-name)"/>
            <xsl:for-each select="$templ_var">
                <xsl:if test="true()">
                    <xsl:value-of select="position()"/>
                </xsl:if>
            </xsl:for-each>
        </q7>
	</xsl:template>

</xsl:stylesheet>
