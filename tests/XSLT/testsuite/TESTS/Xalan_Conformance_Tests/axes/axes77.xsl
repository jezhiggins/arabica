<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES77 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Compound test for following-sibling:: and preceding-sibling:: conjoined,
       with positional predicates on both axes. Reverse document order applies. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="following-sibling::*[2]/preceding-sibling::*[4]"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:text> </xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

</xsl:stylesheet>
