<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: expression06 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.3 -->
  <!-- Purpose: Test of lang() function in a for-each -->

<xsl:template match="doc">
  <out>
    <xsl:for-each select="//para[lang('en')]">
      <xsl:value-of select="@id"/>
      <xsl:text>:</xsl:text>
      <xsl:value-of select="ancestor-or-self::*[@xml:lang]/@xml:lang"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
