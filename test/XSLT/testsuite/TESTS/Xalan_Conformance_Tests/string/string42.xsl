<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: STR42 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'string()' function on a simple RTF. -->

<xsl:variable name="ResultTreeFragTest">
  <xsl:value-of select="doc"/>
</xsl:variable>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="string($ResultTreeFragTest)"/>
  </out>
</xsl:template>

</xsl:stylesheet>