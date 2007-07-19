<?xml version="1.0" ?>
<xsl:stylesheet 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/" >
  <HTML>
  <BODY>
  <H3>Plants in file:</H3>
  <OL>
  <xsl:for-each select="node()//item">
  	<xsl:apply-templates select="*"/>
  </xsl:for-each>
  </OL>
  </BODY>
  </HTML>

<xsl:define-template-set>
	<xsl:template match="common">
		<LI><xsl:value-of /></LI>
	</xsl:template>
</xsl:define-template-set>
</xsl:template>
</xsl:stylesheet>
