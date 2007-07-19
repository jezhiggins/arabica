<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH105 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test what value-of does to a large number. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="9876543210"/>
  </out>
</xsl:template>

</xsl:stylesheet>
