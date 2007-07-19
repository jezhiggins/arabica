<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Purpose: Test of id('literal') as match pattern. Bug 71649 -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="id('b')">
  <xsl:value-of select="name(.)"/> = <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>