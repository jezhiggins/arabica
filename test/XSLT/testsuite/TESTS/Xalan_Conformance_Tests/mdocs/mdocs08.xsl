<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: mdocs08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test document() function: Generating nodeset based on 
       ancestors of document() union. -->

<xsl:template match="defaultcontent">
  <!-- Two 'places' elements contain names of the other two files as text. -->
  <out>
    <xsl:apply-templates select="document(places)//body">
      <xsl:with-param name="arg1">ok</xsl:with-param>
    </xsl:apply-templates>
  </out>
</xsl:template>

<xsl:template match="body">
  <xsl:param name="arg1">not ok</xsl:param>
  1 <xsl:value-of select="."/><xsl:text> </xsl:text>
  2 <xsl:value-of select="$arg1"/>

</xsl:template>

</xsl:stylesheet>
