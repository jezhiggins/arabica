<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: position86 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 -->
  <!-- Creator: Mukund Raghavachari -->
  <!-- Purpose: "The Predicate filters the node-set with respect to the child axis"
     means that the descendant(-or-self) axes must be internally segregated so that
     the position is among one group of children. -->

<xsl:output method="xml" encoding="utf-8"/>

<xsl:template match="/">
  <out>
    <xsl:for-each select="chapter//footnote[1]">
      <xsl:copy>
        <xsl:value-of select="."/>
      </xsl:copy>
      <xsl:text>
</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>


