<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string122 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: string(nodeset) returns string value of the node in the
       node-set that is first in document order.'  -->

<xsl:template match="doc">
	<out>
		<xsl:value-of select="string(av//*)"/>
	</out>
</xsl:template>

</xsl:stylesheet>