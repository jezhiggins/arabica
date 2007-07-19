<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: paramtest -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 Top-level Variables and Parameters  -->
  <!-- Purpose: Test of parameters to the stylesheet.  -->
  <!-- Comments: This test is within the embedded section because it requires
                 a special command line which is already developed for embed. -->

<xsl:param name="pv1" />
<xsl:param name="pv2" />
<xsl:param name="pv3" />
<xsl:param name="pv4">Oops, failed</xsl:param>
<xsl:param name="pv5">Oops, failed</xsl:param>
<xsl:param name="pv6">Oops, failed</xsl:param>

<xsl:template match="/">
 <out>
	<pv1Tag><xsl:value-of select="$pv1"/></pv1Tag>,
	<pv2Tag><xsl:value-of select="$pv2"/></pv2Tag>,
	<pv3Tag><xsl:value-of select="$pv3"/></pv3Tag>,
	<pv4Tag><xsl:value-of select="$pv4"/></pv4Tag>,
	<pv5Tag><xsl:value-of select="$pv5"/></pv5Tag>,
	<pv6Tag><xsl:value-of select="$pv6"/></pv6Tag>.
 </out>
</xsl:template>

</xsl:stylesheet>

