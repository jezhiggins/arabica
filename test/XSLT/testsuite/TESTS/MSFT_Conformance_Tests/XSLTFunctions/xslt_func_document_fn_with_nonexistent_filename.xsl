<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="document('notfound.xml')/body">
      <xsl:with-param name="arg1">ok</xsl:with-param>
    </xsl:apply-templates>
  </out>
</xsl:template>

<xsl:template match="body">
  <xsl:param name="arg1">not ok</xsl:param>
  <xsl:value-of select="$arg1"/>
</xsl:template>

</xsl:stylesheet>