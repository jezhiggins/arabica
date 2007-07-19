<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: node18 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 Node Tests -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for node test in argument to count() function. -->

<xsl:template match="/doc">
  <out><xsl:value-of select="count(.//comment())"/></out>
</xsl:template>

</xsl:stylesheet>
