<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:include href="level2/level2_include2.xsl"/>

<xsl:template match="one-tag">
  From stylesheet level1_include2.xsl: <xsl:value-of select="self::node()"/>
  Including level2_include2.xsl
</xsl:template>

</xsl:stylesheet>