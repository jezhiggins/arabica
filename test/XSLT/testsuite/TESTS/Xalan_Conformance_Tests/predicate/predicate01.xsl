<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: PREDICATE01 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of implied conversion to boolean. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="a[true()=4]"/>
    <!-- Always true; positive numbers convert to true. -->
  </out>
</xsl:template>

</xsl:stylesheet>
