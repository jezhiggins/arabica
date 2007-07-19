<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Test EBCDIC-CP-IT encoding. Avoid new-lines in output until XML 1.1
    addresses the EBCDIC-specific new-line issue. It all looks like gibberish on
    an ASCII/ISO/UTF platform anyway, so you won't notice the lack of an XML decl. -->

<xsl:output omit-xml-declaration="yes" encoding="EBCDIC-CP-IT"/>

<xsl:template match="/">
  <out>ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 abcdefghijklmnopqrstuvwxyz</out>
</xsl:template>

</xsl:stylesheet>
