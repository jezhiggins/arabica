<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">

  <!-- FileName: variable32 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 Top-level Variables and Parameters  -->
  <!-- Purpose: Test passing value from top-level param to top-level variable via value-of. -->
  <!-- Author: David Marston -->

  <xsl:param name="toto" select="'titi'"/>

  <xsl:variable name="tata" select="$toto"/>

  <xsl:template match="/">
    <out>
      <xsl:value-of select="$tata"/>
    </out>
  </xsl:template>

</xsl:stylesheet>
