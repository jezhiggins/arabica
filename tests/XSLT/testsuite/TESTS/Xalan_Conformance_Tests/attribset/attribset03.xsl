<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Use xsl:element with multiple attribute sets. -->

<xsl:template match="/">
  <out>
    <xsl:element name="test" use-attribute-sets="set1 set2"/>
  </out>
</xsl:template>

<xsl:attribute-set name="set2">
  <xsl:attribute name="text-decoration">underline</xsl:attribute>
</xsl:attribute-set>

<xsl:attribute-set name="set1">
  <xsl:attribute name="color">black</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>
