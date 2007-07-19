<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
				xmlns:ora="http://www.oracle.com/XSL/Transform/java/"
				extension-element-prefixes="ora"
				exclude-result-prefixes="ora">

  <!-- FileName: extend01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 14 Extensions -->
  <!-- Purpose: Testing Conformance specific extension stuff. The top-level usage
       of a extension element is not really allowed and should be ignored. Therefore
       the first xsl:fallback should also be ignored.  -->
  <!-- Author: Paul Dick -->


<ora:output name="oout" method="html">
  <xsl:fallback>
	<xsl:text>THIS FALLBACK SHOULD BE IGNORED !! </xsl:text>
  </xsl:fallback>
</ora:output>

<xsl:template match="doc">
 <out>
	<xsl:variable name="filename" select="testfile.html"/>

	<ora:output  use="oout" href="{$filename}">
	  <xsl:fallback>
		<xsl:text>THIS FALLBACK OK !! </xsl:text>
  	  </xsl:fallback>
   	  <xsl:value-of select="element"/>
  	</ora:output>

 </out>
</xsl:template>

</xsl:stylesheet>
