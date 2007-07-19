<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml"/>

  <!-- FileName: DFLT03 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.8 -->
  <!-- Purpose: Test of built-in template for elements. -->
  <!-- Creator: David Marston -->
  <!-- Use the built-in template for text to show that we hit each descendant -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>