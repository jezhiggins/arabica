<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="text"/>

  <!-- FileName: OUTP25 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.3 Text Output Method -->
  <!-- Purpose: ??? -->

<xsl:template match="Sprs">
<s3 title="Known bugs:">
 <p>We are aware of the following bugs (SPR ID# and description):</p><xsl:text>
</xsl:text>
   <ul>
	<xsl:apply-templates select="Spr/State[. = 'Open']"/><xsl:text>&#010;</xsl:text>
   </ul></s3>
</xsl:template>

<xsl:template match="*">
	<li>
	<xsl:value-of select="preceding-sibling::*[2]"/><xsl:text>: </xsl:text>
	<xsl:value-of select="following-sibling::*[2]"/><xsl:text>. ( </xsl:text>
	<xsl:value-of select="following-sibling::*[1]"/><xsl:text>)
</xsl:text>
	<br/><br/></li>
</xsl:template>
 
</xsl:stylesheet>
