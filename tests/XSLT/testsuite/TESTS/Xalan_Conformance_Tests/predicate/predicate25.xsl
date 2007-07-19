<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: PREDICATE25 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of implied conversion of node-set to boolean with !=, boolean last. -->

<xsl:template match="doc">
  <out>
    <xsl:for-each select="a[following-sibling::*!=false()]">
      <!-- Should match 1,2,3 because those nodes have non-empty following-sibling axis. -->
      <xsl:value-of select="."/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
