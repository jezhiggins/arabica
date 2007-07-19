<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey04 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Purpose: Test for id(). -->

<xsl:template match="t04">
 <out>
    <xsl:value-of select="id('c')/@id"/>
 </out>
</xsl:template>

</xsl:stylesheet>
