<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>
  <xsl:strip-space elements="*"/>

  <!-- FileName: OUTP52 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: html output method should not output white space after 
       the image tag within the anchor tag. -->

<xsl:template match="/">
  <html><body>
    <a href="#">
      <img src="image.jpg"/>
    </a>
  </body></html>
</xsl:template>

</xsl:stylesheet>
