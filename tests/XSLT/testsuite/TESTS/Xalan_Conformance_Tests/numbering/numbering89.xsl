<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- CaseName: numbering89 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show discrepancies between number and position. -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[2]/item[1]/p[1]/text()[5]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[2]/item[3]/p[1]/text()[6]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[2]/p[1]/text()[3]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[3]/p[1]/text()[1]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(convert)/p[2]/text()[3]" -->
  <!-- Scenario: operation="standard-XML" -->
  <!-- Elaboration: While xsl:number always shows the number of the chapter among all chapters,
       position() in the outer case is the position of the chapter among all children of doc,
       position() in the inner case (repeat mode) is the position of the chapter/text within the select set
       that contains the chapter and all its siblings. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="chapter">
  <xsl:element name="chap">
    <xsl:attribute name="number">
      <xsl:number/>
    </xsl:attribute>
    <xsl:attribute name="position">
      <xsl:value-of select="position()"/>
    </xsl:attribute>
    <xsl:value-of select="note[1]"/>
    <xsl:apply-templates select="../node()" mode="repeat"/>
  </xsl:element>
</xsl:template>

<xsl:template match="chapter" mode="repeat">
  <xsl:element name="sel">
    <xsl:attribute name="number">
      <xsl:number/>
    </xsl:attribute>
    <xsl:attribute name="position">
      <xsl:value-of select="position()"/>
    </xsl:attribute>
  </xsl:element>
</xsl:template>

<xsl:template match="text()" mode="repeat">
  <xsl:text>&#10;</xsl:text>
  <xsl:element name="text">
    <xsl:attribute name="number">
      <xsl:number/>
    </xsl:attribute>
    <xsl:attribute name="position">
      <xsl:value-of select="position()"/>
    </xsl:attribute>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>
