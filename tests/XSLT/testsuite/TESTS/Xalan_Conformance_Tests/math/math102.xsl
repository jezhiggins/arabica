<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math102 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that number() with no argument applies to context node. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="number()"/>
  </out>
</xsl:template>

</xsl:stylesheet>
