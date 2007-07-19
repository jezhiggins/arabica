<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:attribute-set name="merge" use-attribute-sets="foo">
        <xsl:attribute name="attr1">attr1 pri0 1</xsl:attribute>
        <xsl:attribute name="attr2">attr2 pri0</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="merge">
        <xsl:attribute name="attr1">attr1 pri0 2</xsl:attribute>
        <xsl:attribute name="attr3">attr3 pri0</xsl:attribute>
    </xsl:attribute-set>

    <!-- Include stylesheet that imports inc/import-attrset.inc -->
    <xsl:include href="inc/include-attrset.inc"/>

    <xsl:attribute-set name="foo">
        <!-- foo's import priority is higher than any "merge", but it shouldn't matter, "merge" attr1 pri0 2 should still win -->
        <xsl:attribute name="attr1">attr1 foo</xsl:attribute>
    </xsl:attribute-set>

	<xsl:template match="/">

        <x xsl:use-attribute-sets="foo merge merge2 merge-import"/>

    </xsl:template>

    <xsl:attribute-set name="merge2">
        <xsl:attribute name="merge2-1"/>
    </xsl:attribute-set>
    <xsl:attribute-set name="merge2"/>
    <xsl:attribute-set name="merge2"/>
    <xsl:attribute-set name="merge2"/>
    <xsl:attribute-set name="merge2">
        <xsl:attribute name="merge2-2"/>
    </xsl:attribute-set>

</xsl:stylesheet>
