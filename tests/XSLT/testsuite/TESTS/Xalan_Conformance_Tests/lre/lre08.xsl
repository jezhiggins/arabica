<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: lre08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: The name attribute of xsl:element is interpreted as an 
       attribute value template. -->

<xsl:template match="/">
  <out>
    <xsl:element name="{.//doc2/doc3/a/@level}"/>
    <xsl:element name="{.//*[starts-with(name(.),'ba')]}"/>
  </out>
</xsl:template>

</xsl:stylesheet>
