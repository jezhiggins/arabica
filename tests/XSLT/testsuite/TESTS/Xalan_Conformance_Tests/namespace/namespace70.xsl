<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
		xmlns:ped="http://bubba.com"
		xmlns:bdd="http://bubba.com"
		xmlns:bub="http://bubba.com"
	exclude-result-prefixes="bub">

  <!-- FileName: namespace70 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements  -->
  <!-- Creator: David Marston -->
  <!-- Purpose: When there two prefixes for an NS URI, exclude-result-prefixes of one prefix excludes all for that URI. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="."/>
  </out>
</xsl:template>

</xsl:stylesheet>