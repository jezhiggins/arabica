<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP32 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: ESC of non-ASCII chars in URI attribute
  	   values using method sited in Section B.2.1 of 
  	   HTML 4.0 Spec. -->

  <!-- test for SCRIPT handling -->
  <xsl:output method="html" indent="no"/>

  <xsl:template match="/">
    <HTML>
       <Q cite="bë.xml"/>
    </HTML>
  </xsl:template>

</xsl:stylesheet>
