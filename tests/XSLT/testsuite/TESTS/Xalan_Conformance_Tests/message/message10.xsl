<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:element and xsl:attribute inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE10: </xsl:text>
      <xsl:element name="how">
        <xsl:attribute name="when">now</xsl:attribute>
        <xsl:value-of select="a"/>
      </xsl:element>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
