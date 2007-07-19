<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 Using Variables and Parameters with xsl:copy-of -->
  <!-- Purpose: Test for using xsl:copy-of with empty (null string) variable. -->
  <!-- Author: Paul Dick -->

<xsl:template match="doc">
  <xsl:variable name="x"/>
  <out>
    <xsl:copy-of select="$x"/>
  </out>
</xsl:template>

</xsl:stylesheet>
