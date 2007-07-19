<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: SORT39 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Try to set lang from an expression. -->

<xsl:output method="xml" indent="no"/>
<xsl:template match="data">
  <xsl:variable name="language" select="'en'"/>
  <xsl:variable name="country" select="'US'"/>
  <out><xsl:text>
  </xsl:text>
    <xsl:for-each select="row">
      <xsl:sort lang="{concat($language,'-',$country)}"/>
      <xsl:copy-of select="."/><xsl:text>
  </xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>