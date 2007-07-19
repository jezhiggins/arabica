<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test one xsl:message inside another -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE09: </xsl:text>
      <xsl:message>This is a bulletin!</xsl:message>
      <xsl:text>This is the original message</xsl:text>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
