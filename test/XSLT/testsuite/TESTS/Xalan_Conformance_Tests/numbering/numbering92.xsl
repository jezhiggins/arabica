<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:z="http://z.test.com" exclude-result-prefixes="z">

  <!-- CaseName: numbering92 -->
  <!-- Creator: Ilene Seelemann -->
  <!-- Purpose: If the source document has a named default namespace, the counting (on xsl:number) should still work. -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[2]/item[1]/p[1]/text()[5]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[2]/p[1]/text()[3]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[3]/p[1]/text()[1]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(convert)/p[2]/text()[3]" -->
  <!-- Scenario: operation="standard-XML" -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="z:doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="z:note">
  <xsl:element name="znote">
    <xsl:attribute name="number">
      <xsl:number level="single" from="z:chapter"/>
    </xsl:attribute>
    <xsl:value-of select="."/>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>
