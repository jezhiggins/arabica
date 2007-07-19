<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES84 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Purpose: Compound test going "vertically" in the tree. -->
  <!-- Creator: David Marston -->
  <!-- The expression selects the set of all grandparents.
       "//*[count(ancestor::*) &gt;= 2]" is the set of all grandchildren. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="//*[count(ancestor::*) &gt;= 2]/../parent::*"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:text> </xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

</xsl:stylesheet>
