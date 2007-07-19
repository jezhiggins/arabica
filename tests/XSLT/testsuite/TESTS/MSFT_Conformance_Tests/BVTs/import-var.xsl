<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template name="forward-refs">

        <!-- Pri -2, -3, 0 -->
        <x><xsl:value-of select="$foo1"/></x>

        <!-- Pri 0, -2, -3 -->
        <x><xsl:value-of select="$foo3"/></x>

        <!-- Pri -3, 0, -1 -->
        <x><xsl:value-of select="$foo5"/></x>

        <!-- Pri -3, -2, -1 -->
        <x><xsl:value-of select="$foo7"/></x>

        <xsl:variable name="foo8">
            <xsl:variable name="foo8">
                <xsl:variable name="foo8" select="$foo8"/>
                <xsl:value-of select="$foo8"/>
            </xsl:variable>
            <xsl:value-of select="$foo8"/>
        </xsl:variable>

        <!-- Forward ref nested in template variable -->
        <x><xsl:value-of select="$foo8"/></x>

    </xsl:template>


    <xsl:variable name="foo3" select="concat('foo3 pri 0 depends on ', $foo3)"/>
    <xsl:variable name="foo4" select="concat('foo4 pri 0 depends on ', $foo4)"/>

    <xsl:include href="inc/include-var.inc"/>

    <xsl:variable name="foo1" select="concat('foo1 pri 0 depends on ', $foo1)"/>
    <xsl:variable name="foo2" select="concat('foo2 pri 0 depends on ', $foo2)"/>
    <xsl:variable name="foo5" select="concat('foo5 pri 0 depends on ', $foo5)"/>

    <xsl:include href="inc/include-var3.inc"/>

    <xsl:variable name="foo8" select="concat('foo8 pri 0 depends on ', $foo8)"/>

    <xsl:variable name="foo9" select="'foo9 pri 0'"/>

    <xsl:template match="/">

        <priority-scramble/>

        <!-- Pri -2, -3, 0 -->
        <x><xsl:value-of select="$foo1"/></x>

        <!-- Pri -3, -2, 0 -->
        <x><xsl:value-of select="$foo2"/></x>

        <!-- Pri 0, -2, -3 -->
        <x><xsl:value-of select="$foo3"/></x>

        <!-- Pri 0, -3, -2 -->
        <x><xsl:value-of select="$foo4"/></x>

        <!-- Pri -3, 0, -1 -->
        <x><xsl:value-of select="$foo5"/></x>

        <!-- Pri -2, -3, -1 -->
        <x><xsl:value-of select="$foo6"/></x>

        <!-- Pri -3, -2, -1 -->
        <x><xsl:value-of select="$foo7"/></x>

        <forward-refs/>

        <xsl:call-template name="forward-refs"/>

        <import-resolves-circular-ref/>

        <x><xsl:value-of select="$foo10"/></x>

        <import-overriden-with-new-type/>

        <!-- Imported $loop is a number.  Overriding variable is a nodeset. -->
        <xsl:for-each select="$loop">
            <x><xsl:value-of select="number($loop)"/></x>
        </xsl:for-each>

    </xsl:template>

    <xsl:variable name="loop" select="bookstore"/>

</xsl:stylesheet>
