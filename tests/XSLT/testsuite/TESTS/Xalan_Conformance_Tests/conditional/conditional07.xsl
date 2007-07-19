<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test single when by itself, fail. -->

<xsl:template match="doc">
  <out>
    <xsl:choose>
      <xsl:when test="blah">2</xsl:when>
    </xsl:choose>
  </out>
</xsl:template>

</xsl:stylesheet>
