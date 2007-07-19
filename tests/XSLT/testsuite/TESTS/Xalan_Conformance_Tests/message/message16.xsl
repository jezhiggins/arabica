<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message16 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Purpose: Test xsl:message inside xsl:param instead of xsl:template -->
  <!-- Creator: David Marston -->

<xsl:param name="foo">
  <xsl:message>This message came from the MESSAGE16 test.</xsl:message>
  <xsl:value-of select="/docs/a"/>
</xsl:param>

<xsl:template match="docs">
  <out>
    <xsl:value-of select="$foo"/>
  </out>
</xsl:template>

</xsl:stylesheet>
