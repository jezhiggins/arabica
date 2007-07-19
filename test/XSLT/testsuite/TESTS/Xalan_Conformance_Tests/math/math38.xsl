<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH38 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.4 -->
  <!-- Purpose: Test of ceiling() on a non-integer. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="ceiling(1.1)=2"/>
  </out>
</xsl:template>

</xsl:stylesheet>
