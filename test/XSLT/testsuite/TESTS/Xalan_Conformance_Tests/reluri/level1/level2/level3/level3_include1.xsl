<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:include href="../../../final_included.xsl"/>

<xsl:template match="three-tag">
  From stylesheet level3_include1.xsl: <xsl:value-of select="self::node()"/>
  Including final_included.xsl
</xsl:template>

</xsl:stylesheet>