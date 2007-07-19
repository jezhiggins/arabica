<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATCH10 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of functions in predicate. -->

<xsl:template match="letter[position()=last()]">
  <out>
    <xsl:value-of select="."/>
  </out>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>
