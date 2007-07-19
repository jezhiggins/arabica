<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string123 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of string() function with no arguments. -->
  <!-- "If the argument is omitted, it defaults to a node-set
        with the context node as its only member."
    BUT this node has text and element children, all of which get concatenated. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="string()"/>
  </out>
</xsl:template>

</xsl:stylesheet>