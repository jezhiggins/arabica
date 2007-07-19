<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Attempt to reference a variable within itself -->
    <xsl:variable name="foo">
        <xsl:value-of select="$foo"/>
    </xsl:variable>

</xsl:stylesheet>
