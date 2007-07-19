<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean73 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test != on two node-sets, where both are the same. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="j[@l='12'] != j[@w='33']"/>
  </out>
</xsl:template>

</xsl:stylesheet>