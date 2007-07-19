<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean43 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.3 -->
  <!-- Purpose: Test of boolean() function, converting an empty result tree fragment -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:variable name="emptyResultTreeFragTest"></xsl:variable>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="boolean($emptyResultTreeFragTest)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
