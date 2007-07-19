<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:snaz="http://baz.com">

  <!-- FileName: OUTPUT107 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use cdata-section-elements with xsl:copy-of, namespaces match URIs but prefixes are different. -->

<xsl:output method="xml" cdata-section-elements="snaz:out" encoding="UTF-8"/>

<xsl:template match="/">
  <xsl:copy-of select="*"/>
</xsl:template>

</xsl:stylesheet>