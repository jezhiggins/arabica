<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean86 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test =, !=, and not, comparing empty node-set to boolean. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:variable name="x" select="avj/none"/><!-- empty -->
    <e><xsl:value-of select="$x=true()"/></e>
    <ne><xsl:value-of select="not($x=true())"/></ne>
    <n><xsl:value-of select="$x!=true()"/></n>
    <nn><xsl:value-of select="not($x!=true())"/></nn><xsl:text>
</xsl:text><!-- Now reverse the order of the comparands -->
    <e><xsl:value-of select="true()=$x"/></e>
    <ne><xsl:value-of select="not(true()=$x)"/></ne>
    <n><xsl:value-of select="true()!=$x"/></n>
    <nn><xsl:value-of select="not(true()!=$x)"/></nn>
  </out>
</xsl:template>

</xsl:stylesheet>