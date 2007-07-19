<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset25 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use xsl:element with for-each inside xsl:attribute -->

<xsl:template match="docs">
  <xsl:element name="out">
    <xsl:attribute name="test1">
      <xsl:for-each select="a">
        <xsl:value-of select="."/>
      </xsl:for-each>
    </xsl:attribute>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>