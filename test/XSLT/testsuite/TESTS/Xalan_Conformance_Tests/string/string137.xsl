<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string137 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use 'translate()' to map several characters to the same one. -->

<xsl:template match="/doc">
  <out>
    <xsl:value-of select='translate(a,"aeiouy","******")'/>
  </out>
</xsl:template>

</xsl:stylesheet>