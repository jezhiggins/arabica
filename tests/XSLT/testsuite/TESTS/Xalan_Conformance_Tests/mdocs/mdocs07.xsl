<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: mdocs07 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test document() function: Mini Stress test. The many 'a' elements
     contain repeats of the file names. Union should not contain duplicate nodes. -->

<xsl:template match="doc">
  <out>
    <xsl:copy-of select="document(a)//body"/>
  </out>
</xsl:template>

</xsl:stylesheet>