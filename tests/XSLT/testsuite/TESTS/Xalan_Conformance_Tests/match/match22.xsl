<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATCH22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Creator: Scott Boag -->
  <!-- Purpose: Test of three predicates, all being positional. Different notation.
     First predicate reduces the set to {a,c,e,g,i,k}. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="root/x"/>
  </out>
</xsl:template>

<xsl:template match="x[(position() mod 2) &gt; 0][position() &gt; 3][2]">
  <xsl:value-of select="@spot"/>
  <xsl:text> </xsl:text>
</xsl:template>

</xsl:stylesheet>
