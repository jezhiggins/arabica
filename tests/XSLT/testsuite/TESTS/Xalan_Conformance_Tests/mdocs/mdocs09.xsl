<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ped="http://ped.com"
                xmlns:bdd="http://bdd.com"
                exclude-result-prefixes="xsl ped bdd">

  <!-- FileName: MDocs09 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test that document("") refers to the root node of the stylesheet. -->
  <!-- Remember: every top-level node in the stylesheet must have a namespace. -->

<xsl:template match="doc">
  <out><xsl:text>
</xsl:text>
    <xsl:copy-of select='document("")/xsl:stylesheet/ped:test[@attrib="yeha"]'/><xsl:text>
</xsl:text>
  </out>
</xsl:template>

<ped:test attrib="yeha">YEE-HA</ped:test>
<ped:test attrib="haye">Test2</ped:test>
<bdd:test>Test3</bdd:test>
<bdd:test>Test4</bdd:test>

</xsl:stylesheet>