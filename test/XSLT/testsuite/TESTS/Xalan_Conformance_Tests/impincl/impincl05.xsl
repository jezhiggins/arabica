<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: IMPINCL05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6.2 -->
  <!-- Purpose: Two imports, each of which has an import, plus an
       apply-imports in main stylesheet. Precedence (low) DBECA (high) per spec. -->

<xsl:import href="b.xsl"/>
<xsl:import href="c.xsl"/>

<xsl:template match="/">
  <out><xsl:apply-templates select="doc/*" /></out>
</xsl:template>

<xsl:template match="title"><!-- This has import precedence over all others -->
  MAIN title matched<xsl:text>...</xsl:text>
  <xsl:apply-imports/>
</xsl:template>

</xsl:stylesheet>