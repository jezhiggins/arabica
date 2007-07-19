<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string140 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of 'normalize-space()' function. Watch for space being removed when it shouldn't be -->

<xsl:template match="doc">
  <out>
    <xsl:for-each select="a">
      <xsl:text>
</xsl:text>
      <xsl:element name="A">
        <xsl:attribute name="size"><xsl:value-of select="string-length(normalize-space(.))"/></xsl:attribute>
        <xsl:value-of select="normalize-space(.)"/>
      </xsl:element>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>