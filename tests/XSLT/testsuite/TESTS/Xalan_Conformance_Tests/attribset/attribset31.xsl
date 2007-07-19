<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset31 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Purpose: Use xsl:element with multiple attribute sets with conflicting names
    (merge scenario), plus local override with xsl:attribute. -->
  <!-- Author: Carmelo Montanez --><!-- ResultTree008 in NIST suite -->

<xsl:template match="/">
  <out>
    <xsl:element name="element1" use-attribute-sets="set1">
      <xsl:attribute name="text-decoration">none</xsl:attribute>
    </xsl:element>
  </out>
</xsl:template>

<xsl:attribute-set name="set1">
  <xsl:attribute name="text-decoration">underline</xsl:attribute>
</xsl:attribute-set>

<xsl:attribute-set name="set1">
  <xsl:attribute name="color">black</xsl:attribute>
</xsl:attribute-set>

<xsl:attribute-set name="set1">
  <xsl:attribute name="font-size">14pt</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>