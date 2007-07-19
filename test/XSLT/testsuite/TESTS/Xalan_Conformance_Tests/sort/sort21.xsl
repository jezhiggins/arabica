<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: sort21 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for xsl:sort using a numeric expression for the select. -->

<xsl:template match="/">
  <out>
     <xsl:for-each select="doc/alpha">
         <xsl:sort select="position()" data-type="number" order="descending"/>
         <xsl:value-of select="@key"/><xsl:text>,</xsl:text>
     </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>