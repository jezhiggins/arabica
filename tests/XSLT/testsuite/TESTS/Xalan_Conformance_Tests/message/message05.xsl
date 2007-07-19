<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test if and copy-of inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE05: </xsl:text>
      <xsl:if test="a">
        <xsl:copy-of select="a"/>
      </xsl:if>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
