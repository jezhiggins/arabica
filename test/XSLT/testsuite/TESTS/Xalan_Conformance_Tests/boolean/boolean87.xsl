<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean87 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test = and !=, comparing RTF to boolean. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:variable name="normalRTF">
  <xsl:value-of select="/doc/avj"/>
</xsl:variable>
<xsl:variable name="emptyRTF"></xsl:variable>

<xsl:template match="doc">
  <out>
    <nt><xsl:value-of select="$normalRTF=true()"/></nt>
    <nnt><xsl:value-of select="$normalRTF!=true()"/></nnt>
    <tn><xsl:value-of select="true()=$normalRTF"/></tn>
    <tnn><xsl:value-of select="true()!=$normalRTF"/></tnn><xsl:text>
</xsl:text>
    <et><xsl:value-of select="$emptyRTF=true()"/></et>
    <ent><xsl:value-of select="$emptyRTF!=true()"/></ent>
    <te><xsl:value-of select="true()=$emptyRTF"/></te>
    <tne><xsl:value-of select="true()!=$emptyRTF"/></tne>
  </out>
</xsl:template>

</xsl:stylesheet>