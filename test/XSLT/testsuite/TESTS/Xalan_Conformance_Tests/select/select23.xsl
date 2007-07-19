<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select23 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.7 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: NCName after @ must not be treated as an operator -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="@div - 5"/>
  </out>
</xsl:template>

</xsl:stylesheet>
