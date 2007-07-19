<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test of two occurrences of the decimal-separator. -->
<!-- ExpectedException: Format cannot have two decimal separators. -->
<!-- Malformed format string: ##,000.000.0000 -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="format-number(1886.201,'##,000.000.0000')"/>
  </out>
</xsl:template>

</xsl:stylesheet>
