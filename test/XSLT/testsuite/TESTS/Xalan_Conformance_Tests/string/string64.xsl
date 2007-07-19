<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str64 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'contains()' function with node as 1st argument, string is in it. -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="contains(doc, 'CYCL')"/>
  </out>
</xsl:template>

</xsl:stylesheet>