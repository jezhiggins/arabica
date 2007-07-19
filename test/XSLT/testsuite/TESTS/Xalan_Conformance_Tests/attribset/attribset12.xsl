<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Paragraph: 3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Set attributes of an LRE, using one attribute set with 
       multiple attributes, and one overriding LRE attribute, and one 
       overriding xsl:attribute attribute. -->

<xsl:attribute-set name="set1">
  <xsl:attribute name="color">black</xsl:attribute>
  <xsl:attribute name="font-size">14pt</xsl:attribute>
  <xsl:attribute name="font-weight">bold</xsl:attribute>
</xsl:attribute-set>

<xsl:template match="/">
  <out>
    <test1 xsl:use-attribute-sets="set1" font-size="10pt">
      <xsl:attribute name="font-size">24pt</xsl:attribute>
    </test1>
  </out>
</xsl:template>

</xsl:stylesheet>