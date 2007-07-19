<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Purpose: Test choose with no matches and missing otherwise clause. -->
  <!-- No expected output. -->

<xsl:template match="/doc">
  <out>
    <xsl:for-each select="critter">
      <xsl:choose>
        <xsl:when test="@type='horse'">&#xa;Horse: </xsl:when>
        <xsl:when test="@type='cow'">&#xa;Cow: </xsl:when>
      </xsl:choose>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
