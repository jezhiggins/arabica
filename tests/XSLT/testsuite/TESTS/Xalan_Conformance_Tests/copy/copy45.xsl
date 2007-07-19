<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy45 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Make an RTF on the fly and watch for incorrect xml-decl placement. -->

<xsl:output method="xml" encoding="UTF-8" standalone="yes" />

<xsl:template match="/">
  <xsl:variable name="var1"><rtf>abc<in x="yz">def</in>ghi</rtf></xsl:variable>
  <out>
    <xsl:copy-of select="$var1"/>
  </out>
</xsl:template>

</xsl:stylesheet>