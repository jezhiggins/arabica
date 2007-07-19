<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable36 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Set variable to null string explicitly and implicitly, compare. -->
  <!-- Author: David Marston -->

<xsl:variable name="empty" />

<xsl:template match="doc">
  <xsl:param name="x" select="substring-before('a','z')" />
  <out>
    <xsl:value-of select="$x=$empty"/>
  </out>
</xsl:template>

</xsl:stylesheet>
