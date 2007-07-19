<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output cdata-section-elements="example"/>

  <!-- FileName: OUTP30 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Purpose: Test cdata-section-elements that looks like end of CDATA. -->

<xsl:template match="/">
  <out>
    <example>]]&gt;</example>
  </out>
</xsl:template>

</xsl:stylesheet>
