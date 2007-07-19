<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.5 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for copying attributes from source to result tree -->                

<xsl:template match="data">
  <out>
    <xsl:for-each select="*">
      <xsl:copy>
        <xsl:apply-templates select="@*|node()|text()"></xsl:apply-templates>
      </xsl:copy>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="@*">
  <xsl:attribute name="{name(.)}">
    <xsl:value-of select="."/>
  </xsl:attribute>
</xsl:template>

</xsl:stylesheet>
