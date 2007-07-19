<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select57 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: test union operator at different nesting levels (different elements) -->
  <!-- Creator: Carmelo Montanez --><!-- Expression017 in NIST suite -->

<xsl:template match = "doc">
  <out><xsl:text>
</xsl:text>
    <xsl:for-each select = "book">
      <xsl:apply-templates select= "author/name|author/bibliography/author/chapters"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:value-of select="."/><xsl:text>
    </xsl:text>
</xsl:template>

</xsl:stylesheet>