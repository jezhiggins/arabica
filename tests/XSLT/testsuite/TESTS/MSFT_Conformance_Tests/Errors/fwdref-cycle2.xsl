<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Cycle in foo and bar's content -->
    <xsl:variable name="foo">
        <xsl:value-of select="$bar"/>
    </xsl:variable>

    <!-- Cycle is not direct -->
    <xsl:variable name="intermediate">
        <xsl:value-of select="$foo"/>
    </xsl:variable>

    <xsl:variable name="bar">
        <xsl:value-of select="$intermediate"/>
    </xsl:variable>

</xsl:stylesheet>
