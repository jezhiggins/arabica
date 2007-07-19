<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace21 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for whitespace handling with comments in literal sections -->

<xsl:template match="/">
  <out>x
    <!-- this is a comment -->y
    <!-- this is another comment -->
    <z><!-- this is another comment --> </z>
  </out>
</xsl:template>

</xsl:stylesheet>