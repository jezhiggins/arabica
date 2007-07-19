<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Purpose: To be imported by ../ImpIncl16. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="aac|llh|oop|aah|ssb|iii|rre|eek|xxo|aar|sst|bbd|eeo|xxi|ddg|nne">
  <!-- Template for big union -->
  <xsl:value-of select="."/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="//yyj">
  <!-- Template for Absolute Location Path covering whole document. -->
  <xsl:text>Middle: </xsl:text><xsl:value-of select="."/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="aaa[@val]">
  <!-- Template for attribute -->
  <xsl:text>@val=</xsl:text><xsl:value-of select="@val"/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="*[.=117]">
  <!-- Template for element's value -->
  <xsl:text>The node containing 117 is </xsl:text><xsl:value-of select="name(.)"/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="*[(not(.=117) and ((position() &gt; 225) and (position() &lt; 375))) and ((@century='yes') or (@foo='nope'))]">
  <!-- Template for compound boolean expression -->
  <xsl:text>A century node is </xsl:text><xsl:value-of select="name(.)"/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="text()"/><!-- suppress extraneous text -->

</xsl:stylesheet>
