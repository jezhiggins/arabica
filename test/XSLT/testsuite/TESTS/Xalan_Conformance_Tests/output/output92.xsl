<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

  <!-- FileName: OUTPUT92 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test effect of cdata-section-elements on xsl:element. -->

<xsl:output method="xml" cdata-section-elements="example" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:element name="example">Text that should be enclosed</xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>