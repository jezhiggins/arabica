<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: STR105 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Special case of concat() with one argument.
       Strictly speaking, this should fail just like STRerr14. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="concat(/*, /*[@attr='whatsup'])"/>
  </out>
</xsl:template>

</xsl:stylesheet>