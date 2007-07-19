<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean79 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of "<" operator comparing real to integer, true result -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="1.9999999 &lt; 2"/>
  </out>
</xsl:template>

</xsl:stylesheet>