<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset39 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test use of leading underscore in names. -->

<xsl:attribute-set name="_a_set">
  <xsl:attribute name="_a_color">black</xsl:attribute>
</xsl:attribute-set>

<xsl:template match="/">
  <out>
    <test xsl:use-attribute-sets="_a_set" />
  </out>
</xsl:template>

</xsl:stylesheet>