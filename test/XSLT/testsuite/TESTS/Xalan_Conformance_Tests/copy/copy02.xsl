<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for simple tree copy, in main template via copy-of naming the document element -->                

<xsl:template match="/">
  <out>
    <xsl:copy-of select="OL"/>
  </out>
</xsl:template>

</xsl:stylesheet>
