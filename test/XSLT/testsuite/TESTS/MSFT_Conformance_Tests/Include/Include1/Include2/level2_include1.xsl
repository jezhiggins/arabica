<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:import href="level2_import1.xsl"/>

<xsl:template match="two-tag">
  inside level2_include1.xsl, importing level2_import1.xsl
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>