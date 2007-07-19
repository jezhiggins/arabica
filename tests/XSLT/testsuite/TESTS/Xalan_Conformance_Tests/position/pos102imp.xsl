<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: pos102imp -->
  <!-- Purpose: To be imported by position102. -->

<xsl:template match="b">
  <xsl:text>
</xsl:text>
  <direct>
    <xsl:text>Item </xsl:text>
    <xsl:value-of select="@mark"/>
    <xsl:text> is in position </xsl:text>
    <xsl:value-of select="position()"/>
  </direct>
</xsl:template>

<xsl:template match="c">
  <xsl:text>
</xsl:text>
  <apply level="import">
    <xsl:text>Item </xsl:text>
    <xsl:value-of select="@mark"/>
    <xsl:text> is in position </xsl:text>
    <xsl:value-of select="position()"/>
  </apply>
</xsl:template>

</xsl:stylesheet>
