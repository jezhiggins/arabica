<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string107 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of string() function on an RTF with sub-nodes. -->

<xsl:variable name="ResultTreeFragTest">
  <xsl:value-of select="doc/av"/>
</xsl:variable>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="string($ResultTreeFragTest)"/>
  </out>
</xsl:template>

</xsl:stylesheet>