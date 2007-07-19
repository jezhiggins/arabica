<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy59 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 Using Values of Variables & Parameters with xsl:copy-of. -->
  <!-- Creator: David Bertoni -->
  <!-- Purpose: Use copy-of to put a node-set and RTF in a comment, where some members are text nodes. -->
  <!-- Invalid nodes (non-text) and their content should be ignored. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:variable name="rTreeFrag">
  <xsl:copy-of select="/"/>
</xsl:variable>

<xsl:template match="doc">
  <out>
    <xsl:comment>
      <xsl:copy-of select="node()"/>
    </xsl:comment>
    <xsl:comment>
      <xsl:text> </xsl:text><!-- to separate delimiters -->
      <xsl:copy-of select="$rTreeFrag"/>
    </xsl:comment>
  </out>
</xsl:template>

</xsl:stylesheet>
