<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns="http://default.com">

  <!-- FileName: namespace125 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: See what happens to attribute when default namespace is declared. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:element name="inner">
      <xsl:attribute name="Attr1">true</xsl:attribute>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>