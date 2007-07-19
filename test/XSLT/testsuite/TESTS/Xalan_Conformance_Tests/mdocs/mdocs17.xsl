<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:months="http://monthnames.example.com"
                exclude-result-prefixes="months">

  <!-- FileName: MDocs17 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents  -->
  <!-- Creator: Doug Tidwell, adapted by David Marston -->
  <!-- Purpose: Use document('') to refer to the stylesheet, and have a local lookup table. -->

  <months:name sequence="01">January</months:name>
  <months:name sequence="02">February</months:name>
  <months:name sequence="03">March</months:name>
  <months:name sequence="04">April</months:name>
  <months:name sequence="05">May</months:name>
  <months:name sequence="06">June</months:name>
  <months:name sequence="07">July</months:name>
  <months:name sequence="08">August</months:name>
  <months:name sequence="09">September</months:name>
  <months:name sequence="10">October</months:name>
  <months:name sequence="11">November</months:name>
  <months:name sequence="12">December</months:name>

<xsl:output method="xml"/>

<xsl:variable name="newline">
<xsl:text>
</xsl:text>
</xsl:variable>

<xsl:template match="/">
  <out>
    <xsl:value-of select="$newline"/>
    <xsl:for-each select="/report/month">
      <month>
        <xsl:value-of select="document('')/xsl:stylesheet/months:name[@sequence=current()/@sequence]"/>
        <xsl:text> - </xsl:text>
        <xsl:value-of select="miles-earned"/>
        <xsl:text> miles earned.</xsl:text>
      </month>
      <xsl:value-of select="$newline"/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>