<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

  <!-- FileName: copy26 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Bob Morris -->
  <!-- Purpose: Should be able to copy the same tree fragment twice in succession. -->

<xsl:template match="/">
  <xsl:variable name ="theNode" select="//inc/node4"/>
  <out>
    <xsl:copy-of select="$theNode"/>
    <xsl:copy-of select="$theNode"/>
  </out>
</xsl:template>

</xsl:stylesheet>