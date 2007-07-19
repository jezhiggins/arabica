<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

  <!-- FileName: OUTP04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Test for numbered character entities -->

<xsl:template match="/">
  <HTML>
    <P>&#064;</P>
    <P>&#160;</P>
    <P>&#126;</P>
    <P>&#169;</P>
    <P>&#200;</P>
  </HTML>
</xsl:template>
 
</xsl:stylesheet>
