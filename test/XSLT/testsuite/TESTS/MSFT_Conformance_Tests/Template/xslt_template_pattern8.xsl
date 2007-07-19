<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test a match patttern with a group expression. -->

<xsl:template match="doc[(element1/foo)[bar]]">
  <out>
    <xsl:value-of select = "."/>
  </out>
</xsl:template>

</xsl:stylesheet>
