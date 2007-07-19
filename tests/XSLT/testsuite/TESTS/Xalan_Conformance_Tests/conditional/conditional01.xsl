<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Purpose: General test of choose, with otherwise -->

<xsl:template match="/doc">
  <out>
    <xsl:for-each select="person">
      <xsl:choose>
        <xsl:when test="sex='M'">&#xa;Male: </xsl:when>
        <xsl:when test="sex='F'">&#xa;Female: </xsl:when>
        <xsl:otherwise>&#xa;Who knows?: </xsl:otherwise>
      </xsl:choose>
      <xsl:value-of select="name"/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
