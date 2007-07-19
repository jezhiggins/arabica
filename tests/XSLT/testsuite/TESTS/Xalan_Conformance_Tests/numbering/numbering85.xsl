<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- CaseName: numbering85 -->
  <!-- Author: Paul Dick -->
  <!-- Purpose: Test that value attribute gets rounded correctly w/various formats. -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/ulist[1]/item[1]/p[1]/text()[5]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(number)/p[1]/text()[3]" -->
  <!-- SpecCitation: Rec="XSLT" Version="1.0" type="OASISptr1" place="id(convert)/ulist[1]/item[1]/p[1]/text()[4]" -->
  <!-- Scenario: operation="standard-XML" -->

<xsl:template match="doc">
  <out>
  <!-- Round down to 1 -->
     <o><xsl:number format="1" value="1.1"/></o><xsl:text>&#10;</xsl:text>
     <o><xsl:number format="01" value="1.02"/></o><xsl:text>&#10;</xsl:text>
     <o><xsl:number format="A" value="1.003"/></o><xsl:text>&#10;</xsl:text>
     <o><xsl:number format="a" value="1.0004"/></o><xsl:text>&#10;</xsl:text>
     <o><xsl:number format="I" value="1.00005"/></o><xsl:text>&#10;</xsl:text>
	 <xsl:text>&#10;</xsl:text>

  <!-- Round up to 7 -->
     <s><xsl:number format="i" value="6.5000000000"/></s><xsl:text>&#10;</xsl:text>
     <s><xsl:number format="1" value="6.51"/></s><xsl:text>&#10;</xsl:text>
     <s><xsl:number format="01" value="6.501"/></s><xsl:text>&#10;</xsl:text>
     <s><xsl:number format="A" value="6.5001"/></s><xsl:text>&#10;</xsl:text>
     <s><xsl:number format="a" value="6.50001"/></s><xsl:text>&#10;</xsl:text>
     <s><xsl:number format="I" value="6.500001"/></s><xsl:text>&#10;</xsl:text>
	 <xsl:text>&#10;</xsl:text>
	 
  <!-- Round away two decimal places -->

    <n><xsl:number format="1" value="99.03"/></n><xsl:text>&#10;</xsl:text>
    <n><xsl:number format="01" value="99.13"/></n><xsl:text>&#10;</xsl:text>
    <n><xsl:number format="A" value="99.23"/></n><xsl:text>&#10;</xsl:text>
    <n><xsl:number format="a" value="99.33"/></n><xsl:text>&#10;</xsl:text>
    <n><xsl:number format="I" value="99.43"/></n><xsl:text>&#10;</xsl:text>
	 <xsl:text>&#10;</xsl:text>
    <h><xsl:number format="i" value="99.50"/></h><xsl:text>&#10;</xsl:text>
    <h><xsl:number format="1" value="99.53"/></h><xsl:text>&#10;</xsl:text>
    <h><xsl:number format="01" value="99.63"/></h><xsl:text>&#10;</xsl:text>
    <h><xsl:number format="A" value="99.73"/></h><xsl:text>&#10;</xsl:text>
    <h><xsl:number format="a" value="99.83"/></h><xsl:text>&#10;</xsl:text>
    <h><xsl:number format="I" value="99.93"/></h><xsl:text>&#10;</xsl:text>
      <xsl:text>&#10;</xsl:text>

  <!-- More edge cases -->

    <t><xsl:number format="01" value="2.499"/></t><xsl:text>&#10;</xsl:text>
    <t><xsl:number format="1" value="2.499999999"/></t><xsl:text>&#10;</xsl:text>
  </out>
</xsl:template>

</xsl:stylesheet>
