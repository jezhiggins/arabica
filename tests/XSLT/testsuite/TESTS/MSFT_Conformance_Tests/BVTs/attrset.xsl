<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:attribute-set name="empty"/>

    <xsl:attribute-set name="simple">
        <!-- Comment -->
        <?my-pi?>
        <xsl:attribute name="attr"><xsl:copy/>simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="empty-use" use-attribute-sets="empty"/>

    <xsl:attribute-set name="simple-use" use-attribute-sets="simple">
        <xsl:attribute name="attr2">simple-use</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="multiple-use" use-attribute-sets="  empty  simple  empty-use simple-use   ">
        <xsl:attribute name="attr3">multiple-use</xsl:attribute>
        <xsl:attribute name="attr4">multiple-use</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="fwd-use" use-attribute-sets="fwd">
        <xsl:attribute name="attr5">fwd-use</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="xsl:ns-use" use-attribute-sets="xsl:ns"/>

    <xsl:attribute-set name="xsl:ns" use-attribute-sets="fwd">
        <xsl:attribute name="attr7">ns</xsl:attribute>
    </xsl:attribute-set>

	<xsl:template match="/">

        <!-- use-attribute-sets within a literal element.  Override a couple attributes. -->
        <x attr="{'override-attr'}" xsl:use-attribute-sets="multiple-use" attr4="'override-attr4'" use-attribute-sets="not-recognized">
            <y/>
        </x>

        <x xsl:use-attribute-sets="xsl:ns-use">
            <y/>
        </x>

        <!-- use-attribute-sets within xsl:element and xsl:copy -->
        <xsl:for-each select="bookstore">
            <xsl:copy use-attribute-sets="simple-use">
                <xsl:attribute name="attr2">override-attr2</xsl:attribute>
                <xsl:element name="elem" use-attribute-sets="fwd-use fwd"/>
            </xsl:copy>
        </xsl:for-each>
    </xsl:template>

    <!-- Declare a forward attribute-set and use a variable reference within the set -->
    <xsl:attribute-set name="fwd" use-attribute-sets="simple">
        <xsl:attribute name="{$attr6-name}">fwd</xsl:attribute>
    </xsl:attribute-set>

    <xsl:variable name="attr6-name" select="'attr6'"/>

</xsl:stylesheet>
