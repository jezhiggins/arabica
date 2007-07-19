<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select27 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.7 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: NCName after :: must be treated as part of path -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="attribute :: div"/>
  </out>
</xsl:template>

</xsl:stylesheet>
