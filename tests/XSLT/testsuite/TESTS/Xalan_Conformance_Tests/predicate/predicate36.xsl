<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: PREDICATE36 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of association of inequality symbols. -->

<xsl:template match="doc">
  <out>
  <xsl:for-each select = "a[1 &lt; 3 &lt; 2]">
    <xsl:value-of select="."/>
    <!-- Always true; (1 &lt; 3 ) converts to true; true converts to 1; and (1 &lt; 2) is true. -->
  </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
