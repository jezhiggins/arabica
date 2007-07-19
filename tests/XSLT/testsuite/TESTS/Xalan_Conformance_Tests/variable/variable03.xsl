<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Test xsl:variable inside a template set to be an RTF  -->
  <!-- Author: Paul Dick -->

<xsl:template match="doc">
   <out>
      <xsl:variable name="ResultTreeFragTest">
        <B><xsl:value-of select="a"/></B>
      </xsl:variable>
      <xsl:value-of select="$ResultTreeFragTest"/>
   </out>
</xsl:template>

</xsl:stylesheet>
