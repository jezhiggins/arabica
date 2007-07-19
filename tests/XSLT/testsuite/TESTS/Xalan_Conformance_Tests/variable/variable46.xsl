<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable46 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters -->
  <!-- Purpose: Test proper construction of an RTF containing multiple top level nodes. -->
  <!-- Creator: Felix Garcia Romero (felixgr@tdi.tudistrito.es) -->

<xsl:variable name="foo">
  <b>First element</b>
  Second element
  <FORM METHOD="post">
    <input type="length" size="30" />
  </FORM>
</xsl:variable>

<xsl:template match="/">
  <out><xsl:copy-of select="$foo"/></out>
</xsl:template>

</xsl:stylesheet>