<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select30 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.7 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: * after ( must not be treated as operator, but * after ) is,
     and being tokenized means following * is not (because it follows an operator) -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="(* - 4)**"/>
  </out>
</xsl:template>

</xsl:stylesheet>
