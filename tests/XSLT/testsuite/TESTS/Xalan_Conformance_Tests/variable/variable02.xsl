<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Test top-level xsl:variable set to be an RTF -->
  <!-- Author: Paul Dick -->

<xsl:variable name="ResultTreeFragTest">
    <B>ABC</B>
</xsl:variable>

<xsl:template match="doc">
   <out>
     <xsl:value-of select="$ResultTreeFragTest"/><xsl:text>,</xsl:text>
	 <xsl:copy-of select="$ResultTreeFragTest"/>
   </out>
</xsl:template>

</xsl:stylesheet>