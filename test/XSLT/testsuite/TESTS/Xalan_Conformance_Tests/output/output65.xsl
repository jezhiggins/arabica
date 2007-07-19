<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns="http://www.w3.org/1999/xhtml">

<xsl:output doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
  doctype-system="DTD/xhtml1-strict.dtd"/>

  <!-- FileName: OUTP65 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Purpose: Test for special case for XHTML -->

<xsl:template match="/">
  <html><xsl:value-of select="doc/foo"/></html>
</xsl:template>

</xsl:stylesheet>
