<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: expression02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.4 -->
  <!-- Purpose: Invoke unparsed-entity-uri function -->
  <!-- To avoid dealing with the top of the file path,
     we just look for the part of the returned value that's in the supplied data. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="contains(
      unparsed-entity-uri('hatch-pic'),'grafix/OpenHatch.gif')"/>
  </out>
</xsl:template>

</xsl:stylesheet>
