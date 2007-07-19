<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Set attribute of a LRE from single attribute set. -->

<xsl:attribute-set name="set1">
  <xsl:attribute name="color">black</xsl:attribute>
</xsl:attribute-set>

<xsl:template match="/">
  <out>
    <test1 xsl:use-attribute-sets="set1"></test1>
  </out>
</xsl:template>

</xsl:stylesheet>