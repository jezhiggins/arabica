<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:import href="b.inc"/>
    <xsl:import href="c.inc"/>

<xsl:variable name="foo" select="'In style sheet a'"/>

<xsl:template match="/">
<out>
   -- This should read In style sheet a --
   <xsl:element name="e1"><xsl:value-of select="$foo"/></xsl:element>
   -- This should read In style sheet b --
   <xsl:element name="e2"><xsl:value-of select="$bar"/></xsl:element>
   -- This should read In style sheet c --
   <xsl:element name="e3"><xsl:value-of select="$foobar"/></xsl:element>
   -- This should read In style sheet d --
   <xsl:element name="e4"><xsl:value-of select="$barbar"/></xsl:element>
   -- This should read In style sheet e --
   <xsl:element name="e5"><xsl:value-of select="$barfoo"/></xsl:element>
</out>
</xsl:template>

</xsl:stylesheet>