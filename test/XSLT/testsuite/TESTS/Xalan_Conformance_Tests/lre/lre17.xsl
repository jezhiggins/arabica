<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
				xmlns:ped="http://tester.com"
				xmlns:ljh="http://buster.com"
				xmlns:jad="http://administrator.com">

<xsl:output method="xml" indent="yes"/>

  <!-- FileName: lre17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements-->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: xsl:exclude-result-prefixes should 
       only work to omit namespace declarations that are not actually used. -->

<xsl:template match="doc">
  <sits x="little jack horner" xsl:exclude-result-prefixes="ped jad"/>
</xsl:template>

</xsl:stylesheet>
