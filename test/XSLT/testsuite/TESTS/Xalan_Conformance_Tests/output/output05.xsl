<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


  <!-- FileName: OUTP05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Purpose: Test for "whitespace sensitive" html tags; <img>, <applet>, <object> -->

<xsl:template match="/">
  <HTML><TABLE><tr><td><img src="image1.gif"/></td></tr><tr><td><img src="image2.gif"/></td></tr>
  <tr><td><applet code="clock.class"/></td></tr><tr><td><object/></td></tr></TABLE></HTML>
</xsl:template>
 
</xsl:stylesheet>
