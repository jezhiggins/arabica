<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">

  <!-- FileName: variable31 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 Top-level Variables and Parameters  -->
  <!-- Purpose: Test passing value from top-level param to top-level variable via value-of. -->
  <!-- Author: Benoit Cerrina, adapted by David Marston -->

  <xsl:param name="toto" select="'titi'"/>

  <xsl:variable name="tata">
    <xsl:call-template name="set-tata"/>
  </xsl:variable>

  <xsl:template match="/">
    <out>
      <xsl:value-of select="$tata"/>
    </out>
  </xsl:template>

  <xsl:template name="set-tata">
    <xsl:value-of select="$toto"/>
  </xsl:template>

</xsl:stylesheet>
