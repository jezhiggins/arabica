<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: reluri10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Testing document() function with two arguments: node-set, node-set: 
       verifying that a relative URL specified in first argument is resolved based
	   on base URI of document in second argument nodeset. -->

<xsl:output indent="yes"/>

<xsl:template match="doc">
  <out>
    <xsl:copy-of select="document(filename,document('level1/level2/xreluri10b.xml'))/*/body"/>
    <!-- xsl:copy-of select="document('level1/level2/xreluri10b.xml')/*/body"/ -->
  </out>
</xsl:template>

</xsl:stylesheet>
