<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test xsl:output with indent. -->

<xsl:output indent="yes"/>

<xsl:strip-space elements="document"/>

<xsl:template match="document">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="section">
  <xsl:text>Position:</xsl:text><xsl:value-of select="position()"/>
  <xsl:text>,Last:</xsl:text><xsl:value-of select="last()"/><xsl:text>
</xsl:text>
</xsl:template>

</xsl:stylesheet>
