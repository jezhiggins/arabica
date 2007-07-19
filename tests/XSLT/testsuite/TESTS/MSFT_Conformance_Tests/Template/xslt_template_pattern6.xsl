<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test of functions in predicate. -->

<xsl:template match="letter[position()=last()] | letter[position()=1]">
  <out>
    <xsl:value-of select="."/>
  </out>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>
