<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math85 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of nesting of parentheses. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="((((((n3+5)*(3)+(((n2)+2)*(n1 - 6)))-(n4 - n2))+(-(4-6)))))"/>
  </out>
</xsl:template>

</xsl:stylesheet>
