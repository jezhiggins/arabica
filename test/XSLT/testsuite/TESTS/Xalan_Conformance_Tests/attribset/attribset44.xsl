<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset44 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Creator: David Bertoni -->
  <!-- Purpose: Only top-level variables and params are visible within
     the declaration of an attribute set. -->

<xsl:output indent="yes"/>

<xsl:variable name="foo" select="'correct'"/>

<xsl:template match="/">
  <xsl:variable name="foo" select="'incorrect'"/>
  <out xsl:use-attribute-sets="attrs"/>
</xsl:template>

<xsl:attribute-set name="attrs">
  <xsl:attribute name="test"><xsl:value-of select="$foo"/></xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>
