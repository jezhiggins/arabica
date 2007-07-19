<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset49 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Attempt to set an empty or null attribute in various ways. -->

<xsl:template match="doc">
  <out>
    <xsl:element name="e">
      <xsl:attribute name="NoContent"/>
      <xsl:attribute name="String0t"><xsl:text></xsl:text></xsl:attribute>
      <xsl:attribute name="String0v"><xsl:value-of select="''"/></xsl:attribute>
      <xsl:attribute name="String0f"><xsl:value-of select="substring('x',2,1)"/></xsl:attribute>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>