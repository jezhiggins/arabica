<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:attribute-set name="foo">
        <xsl:attribute name="attr"><xsl:copy use-attribute-sets="bar"/></xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="bar">
        <xsl:attribute name="attr"><xsl:copy use-attribute-sets="foo"/></xsl:attribute>
    </xsl:attribute-set>

</xsl:stylesheet>
