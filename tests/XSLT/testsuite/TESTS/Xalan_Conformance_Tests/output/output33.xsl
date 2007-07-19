<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" indent="no"/>

  <!-- FileName: output33 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: html output method should not output an end-tag
  	   for designated empty elements. -->

<xsl:template match="/">
  <HTML>
    <area>
      <xsl:attribute name="tabindex">2</xsl:attribute>
    </area>	
    <base/>
    <basefont/>
    <br/>
    <col/>
    <frame/>
    <hr width="100"/>
    <img/>
    <input/>
    <isindex/>
    <link/>
    <meta/>
    <param/>
  </HTML>
</xsl:template>

</xsl:stylesheet>
