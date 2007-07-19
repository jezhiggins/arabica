<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"
  doctype-public="-//W3C//DTD HTML 4.0 Transitional"/>

  <!-- FileName: OUTP40 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Test of indent -->

<xsl:template match="/">
  <root>
  <Out> this tests nothing </Out>
  <Out> this tests something </Out>
  <HEAD><Body></Body></HEAD>
  </root>
</xsl:template>

</xsl:stylesheet>