<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns="http://www.w3.org/TR/REC-html40"
  result-ns="">

<xsl:strip-space elements="document"/>

<xsl:template match="document">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="section">
  <xsl:text>Position:</xsl:text><xsl:value-of select="position()"/>
  <xsl:text>,Last:</xsl:text><xsl:value-of select="last()"/>
</xsl:template>

</xsl:stylesheet>

