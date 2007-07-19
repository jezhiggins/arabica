<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position07 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of last() in predicate, all spelled out. -->

<xsl:key name="k" match="a" use="@test"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="*[last()=position()]"/>
  </out>
</xsl:template>

</xsl:stylesheet>
