<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditionalerr01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Purpose: Test for xsl:choose with no when or otherwise clauses. -->
  <!-- Creator: David Marston -->
  <!-- ExpectedException: xsl:choose requires an xsl:when -->

<xsl:template match="/doc">
  <out>
    <xsl:for-each select="critter">
      <xsl:choose>
      </xsl:choose>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
