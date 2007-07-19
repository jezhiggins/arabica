<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AttribSet37 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 -->
  <!-- Purpose: Set some attributes from an imported definition. -->
  <!-- Creator: David Marston -->

<xsl:import href="impattset37a.xsl"/><!-- defines colorset -->
<xsl:import href="impattset37t.xsl"/>

<xsl:template match="/">
  <out>
    <xsl:element name="test" use-attribute-sets="colorset decoset"/>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:attribute-set name="decoset">
  <xsl:attribute name="text-decoration">underline</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>
