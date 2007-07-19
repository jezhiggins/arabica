<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: PROP03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.4 -->
  <!-- Purpose: Test the xsl:vendor-url system property -->

<xsl:template match="doc">
  <out>
	<xsl:if test="contains(system-property('xsl:vendor-url'), 'http://xml.apache.org/xalan-')">
		<xsl:value-of select="'Xalan_URL_found'"/>
	</xsl:if>
  </out>
</xsl:template>
 
</xsl:stylesheet>
