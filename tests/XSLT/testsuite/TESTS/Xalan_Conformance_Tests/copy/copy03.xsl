<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Use identity transformation to put document tree into result tree fragment,
   then use xsl:copy-of to move to result -->                

<xsl:template match="/">
  <xsl:variable name="var1">
    <xsl:apply-templates/>
  </xsl:variable>
  <out>
    <xsl:copy-of select="$var1"/>
  </out>
</xsl:template>

<xsl:template match="*|@*|comment()|processing-instruction()|text()">
  <xsl:copy>
    <xsl:apply-templates select="*|@*|comment()|processing-instruction()|text()"/>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>
