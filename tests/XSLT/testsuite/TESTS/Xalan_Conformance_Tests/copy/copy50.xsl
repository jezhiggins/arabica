<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY50 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Joerg Heinicke (joerg.heinicke@gmx.de) -->
  <!-- Purpose: Attribute encountered before first copied node must not be copied. -->
  <!-- Discretionary: add-attribute-to-non-element="ignore" -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match="test">
  <xsl:copy-of select="*|@*"/>
</xsl:template>

</xsl:stylesheet>