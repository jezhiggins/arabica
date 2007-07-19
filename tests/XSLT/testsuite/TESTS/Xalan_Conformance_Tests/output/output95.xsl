<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTPUT95 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method-->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test effect of cdata-section-elements when text-node children are created by xsl:value-of. -->

<xsl:output method="xml" cdata-section-elements="example" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <example><xsl:value-of select="'should be wrapped'"/></example>
  </out>
</xsl:template>

</xsl:stylesheet>
