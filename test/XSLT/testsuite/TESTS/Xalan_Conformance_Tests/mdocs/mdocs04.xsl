<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: mdocs04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test document() function with one argument: node-set. -->

<xsl:template match="defaultcontent">
  <out>
    <xsl:copy-of select="document(places)"/>
  </out>
</xsl:template>

</xsl:stylesheet>