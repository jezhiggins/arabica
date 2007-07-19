<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select73 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that entity does not cause splitting of one text node into many. -->

<xsl:output method="xml" encoding="ISO-8859-1"/>
<!-- With this output encoding, should get one byte of xE9 for the &eacute -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="A"/>
  </out>
</xsl:template>

<xsl:template match="A">
  <xsl:text>
</xsl:text>
  <xsl:for-each select="child::node()">
    <e>
      <xsl:value-of select="position()"/><xsl:text>. </xsl:text><xsl:value-of select="."/>
    </e>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
