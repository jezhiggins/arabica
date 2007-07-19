<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math88 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Mini stress of x-way multiply and divide. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="(n1*n2*n3*n4*n5*n6)div n7 div n8 div n9 div n10"/>
  </out>
</xsl:template>

</xsl:stylesheet>
