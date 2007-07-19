<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable38 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 Using Variables and Parameters with xsl:copy-of -->
  <!-- Purpose: Test for using xsl:copy-of with variable set to a number. -->
  <!-- This should have the same result as xsl:value-of, stringified number. -->
  <!-- Author: David Marston -->

<xsl:template match="doc">
  <xsl:variable name="x" select="10+7"/><!-- Use of + causes it to be numeric -->
  <out>
    <xsl:copy-of select="$x"/>
  </out>
</xsl:template>

</xsl:stylesheet>
