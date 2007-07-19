<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test that number() with no argument applies to context node. [Bug 71690] -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="number()"/>
  </out>
</xsl:template>

</xsl:stylesheet>