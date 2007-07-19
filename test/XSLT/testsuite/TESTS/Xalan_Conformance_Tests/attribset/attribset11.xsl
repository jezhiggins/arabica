<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset11 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- SECTION: 7.1.4 Named Attribute Sets -->
  <!-- Creator: Paul Dick -->
  <!-- PURPOSE: Set attributes of an LRE, using one attribute set with 
       multiple attributes, and one overriding LRE attribute. -->

<xsl:attribute-set name="set1">
  <xsl:attribute name="color">black</xsl:attribute>
  <xsl:attribute name="font-size">14pt</xsl:attribute>
  <xsl:attribute name="font-weight">bold</xsl:attribute>
</xsl:attribute-set>

<xsl:template match="/">
  <out>
    <test1 xsl:use-attribute-sets="set1" font-size="10pt"></test1>
  </out>
</xsl:template>

</xsl:stylesheet>