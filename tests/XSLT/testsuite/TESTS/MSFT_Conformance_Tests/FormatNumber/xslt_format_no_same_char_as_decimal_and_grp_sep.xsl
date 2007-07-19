<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Create a conflict in the use of the '!' character. -->

<xsl:decimal-format decimal-separator="!" grouping-separator="!" />

<xsl:template match="/">
  <out>
    <xsl:value-of select="format-number(931.4857,'###!###!###')"/>
  </out>
</xsl:template>

</xsl:stylesheet>