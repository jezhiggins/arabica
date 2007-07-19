<?xml version="1.0"?> 

  <!-- FileName: OUTP27 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Purpose: Test of simple output, HTML with xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" -->

<HTML xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xsl:version="1.0">
  <BODY>
	<out>
    	<xsl:value-of select="doc/foo"/>
	</out>
  </BODY>
</HTML>