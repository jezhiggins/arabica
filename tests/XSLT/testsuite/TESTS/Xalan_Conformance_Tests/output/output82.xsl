<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


  <!-- FileName: output82 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Creator: Ito Kazumitsu -->
  <!-- Purpose: Generic test, verifies that DOCTYPE gets generated correctly,
  	   and that the default namespace xml is in scope for LRE use. -->

<xsl:output method="xml"
            doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"
            doctype-system="xhtml1-transitional.dtd"
            indent="yes"
            encoding="UTF-8"/>


<xsl:template match='/'>
  <html>
    <xsl:attribute name="lang">ja</xsl:attribute>
    <xsl:attribute name="xml:lang">ja</xsl:attribute>
    <head><title>test</title></head><body>test</body>
  </html>
</xsl:template>

</xsl:stylesheet>
