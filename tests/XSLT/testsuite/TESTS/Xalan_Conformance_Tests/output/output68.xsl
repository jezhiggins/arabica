<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP68 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Test for-each inside xsl:comment. -->

<xsl:template match="docs">
  <out>
    <xsl:comment>
      <xsl:for-each select="a">
        <xsl:value-of select="."/>
      </xsl:for-each>
    </xsl:comment>
  </out>
</xsl:template>

</xsl:stylesheet>