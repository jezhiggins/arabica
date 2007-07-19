<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math104 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Purpose: Test of is-a-number technique. -->
  <!-- Creator: David Marston -->

<xsl:template match="doc">
  <out>
    <xsl:for-each select="n">
      <xsl:choose>
        <xsl:when test="contains(number(.),'NaN')">
          <xsl:value-of select="."/><xsl:text> is not a number
</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="."/><xsl:text> is a number
</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
