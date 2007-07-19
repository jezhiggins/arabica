<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY16 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use id(node-set) to try to create a set of nodes in random order.
      Either id() or xsl:copy is arranging them in document order. -->

<xsl:template match="/">
  <out>
    <xsl:copy>
      <xsl:apply-templates select="id(main/b)"/>
    </xsl:copy>
  </out>
</xsl:template>

</xsl:stylesheet>
