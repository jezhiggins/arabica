<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message14 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:number inside xsl:message; number should appear. -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE14: </xsl:text>
      <xsl:number value="17" format="(1) "/>
      <xsl:text>Anything between the colon and this?</xsl:text>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
