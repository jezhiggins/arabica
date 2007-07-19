<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:processing-instruction inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE12: </xsl:text>
      <xsl:processing-instruction name="junk">
        <xsl:value-of select="a"/>
      </xsl:processing-instruction>
      <xsl:text>Anything between the colon and this?</xsl:text>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
