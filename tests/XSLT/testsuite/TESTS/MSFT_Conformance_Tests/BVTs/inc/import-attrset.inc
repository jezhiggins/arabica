<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:import href="import-attrset2.inc"/>

    <xsl:attribute-set name="merge">
        <xsl:attribute name="attr1">attr1 pri -1</xsl:attribute>
        <xsl:attribute name="attr4">attr4 pri -1</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="merge-import">
        <xsl:attribute name="merge-import-1"/>
    </xsl:attribute-set>

</xsl:stylesheet>