<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:txt="http://www.host.com"
    xmlns:new="http://www.host.com"
    exclude-result-prefixes="txt new">

  <!-- FileName: variable55 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11 Variables and Parameters -->
  <!-- Purpose: Show that name of variable acts like a real QName. -->
  <!-- Author: David Marston -->

<xsl:variable name="txt:me" select="'Wizard'"/>

<xsl:template match="/">
  <out>
    <xsl:value-of select="$new:me"/>
  </out>
</xsl:template>

</xsl:stylesheet>