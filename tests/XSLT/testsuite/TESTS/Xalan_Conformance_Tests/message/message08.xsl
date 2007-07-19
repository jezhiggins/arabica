<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test call-template inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE08: </xsl:text>
      <xsl:call-template name="templ2"/>
    </xsl:message>
  </out>
</xsl:template>

<xsl:template name="templ2">
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
