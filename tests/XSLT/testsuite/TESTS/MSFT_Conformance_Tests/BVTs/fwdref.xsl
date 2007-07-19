<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <!-- Global variables should be evaluated in this order (or equivalent): non-fwd, val, bar, ref-bar, foo -->

    <xsl:variable name="non-fwd" select="'non-fwd'"/>

    <!-- Two global variables referencing same forward variable -->
    <xsl:variable name="ref-bar" select="concat('ref-bar: ', $bar)"/>

    <xsl:template match="/">
        <!-- Get value of forward variable -->
        <val1><xsl:value-of select="$foo"/></val1>

        <xsl:variable name="foo">

            <!-- Should get forward variable (shadowing foo not visible within itself) -->
            <xsl:value-of select="concat('shadow foo: ', $foo)"/>

        </xsl:variable>

        <!-- Should get shadowed foo -->
        <val2><xsl:value-of select="$foo"/></val2>

        <!-- Print value of ref-bar -->
        <val3><xsl:value-of select="$ref-bar"/></val3>
    </xsl:template>

    <!-- Forward variable contains another forward reference -->
    <xsl:variable name="foo" select="concat('global foo: ', $bar, ' ', $non-fwd)"/>

    <xsl:variable name="val" select="concat('val: ', $non-fwd)"/>

    <!-- Forward variable references a variable already declared -->
    <xsl:variable name="bar" select="concat('bar: ', $val)"/>

</xsl:stylesheet>
