<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Regression case for bug 77025 -->

<!-- XSLT: Should not escape numeric entity references in attribute value when output method is HTML -->

<xsl:output method="html"/>

<xsl:template match="/">
  <out>
     <xsl:attribute name="a">x
y</xsl:attribute>
  </out>
</xsl:template>

</xsl:stylesheet>
