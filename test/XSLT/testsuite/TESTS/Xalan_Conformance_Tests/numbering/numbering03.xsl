<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- CaseName: numbering03 -->
  <!-- Author: Paul Dick, based on example in spec -->
  <!-- Purpose: Test of level (multiple), count, format attributes. -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[2]/item[2]/p[1]/text()[1]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[2]/p[1]/text()[1]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(convert)/p[2]/text()[5]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(convert)/p[2]/text()[7]" -->
  <!-- Scenario: operation="standard-XML" -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>
  
<xsl:template match="title">
  <xsl:number level="multiple"
      count="chapter|section|subsection"
      format="1.1. "/>
  <xsl:value-of select="."/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="appendix//title" priority="1">
  <xsl:number level="multiple"
      count="appendix|section|subsection"
      format="A.1. "/>
  <xsl:value-of select="."/><xsl:text>
</xsl:text>
</xsl:template>
 
<xsl:template match="text()"><!-- To suppress empty lines --><xsl:apply-templates/></xsl:template>
 
</xsl:stylesheet>
