<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset21 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 -->
  <!-- Purpose: Use xsl:copy with a single attribute set. -->
  <!-- Author: Carmelo Montanez --><!-- ResultTree002 in NIST suite -->

<xsl:template match="test">
  <out>
    <xsl:copy use-attribute-sets="set1"/>
  </out>
</xsl:template>

<xsl:attribute-set name="set1">
  <xsl:attribute name="format">bold</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>
