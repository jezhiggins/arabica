<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: LRE14 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for-each inside xsl:element -->

<xsl:template match="docs">
  <out>
    <xsl:element name="all">
      <xsl:for-each select="a">
        <xsl:value-of select="."/>
      </xsl:for-each>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>
