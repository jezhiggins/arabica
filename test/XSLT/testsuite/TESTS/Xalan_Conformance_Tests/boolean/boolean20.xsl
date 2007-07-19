<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean20 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Booleans -->
  <!-- Purpose: Test of boolean "and" operator with two strings;
       strings are evaluated to True if there length > 1.    -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="'foo' and 'fop'"/>
  </out>
</xsl:template>

</xsl:stylesheet>
