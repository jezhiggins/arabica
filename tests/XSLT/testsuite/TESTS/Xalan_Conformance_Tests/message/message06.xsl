<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Purpose: Test choose and variable inside xsl:message -->
  <!-- Creator: David Marston -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:variable name="foo" select="'condition true'"/>
      <xsl:variable name="tralse" select="'condition false'"/>
      <xsl:text>Message from MESSAGE06: </xsl:text>
      <xsl:choose>
        <xsl:when test="a">
          <xsl:value-of select="$foo"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$tralse"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
