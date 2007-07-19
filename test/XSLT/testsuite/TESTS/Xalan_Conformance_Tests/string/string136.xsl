<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string136 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Ensure that 'translate()' doesn't loop on characters that get repositioned -->

<xsl:template match="/doc">
  <out>
    <xsl:value-of select='translate(a,"abe","bao")'/>
  </out>
</xsl:template>

</xsl:stylesheet>