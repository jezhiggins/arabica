<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">

  <!-- FileName: variable33 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 Top-level Variables and Parameters  -->
  <!-- Purpose: Set top-level variable with a forward reference to see what happens. -->
  <!-- Author: David Marston -->

  <xsl:variable name="tata" select="$toto"/>

  <xsl:param name="toto" select="'titi'"/>

  <xsl:template match="/">
    <out>
      <xsl:value-of select="$tata"/>
    </out>
  </xsl:template>

</xsl:stylesheet>
