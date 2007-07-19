<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select62 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: union of two absolute (//) paths -->
  <!-- Creator: Carmelo Montanez --><!-- Expression022 in NIST suite -->

<xsl:template match = "doc">
  <out>
    <xsl:apply-templates select = "//child1|//child2"/>
  </out>
</xsl:template>

<xsl:template match = "*">
  <xsl:value-of select = "."/>
</xsl:template>

</xsl:stylesheet>

