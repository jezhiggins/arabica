<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace23 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: Scott Boag (in response to problem reported by "Carsten Ziegeler" <cziegeler@sundn.de>) -->
  <!-- Purpose: Another test for the normalize-space function, this one really testing handling of the newline. -->

<xsl:template match = "doc">
   <out>
	<xsl:for-each select="link">
		 <a>
		 		 <xsl:attribute name="href"><xsl:value-of
                                select="normalize-space(url)"/></xsl:attribute>
		 		 <xsl:value-of select="normalize-space(url)"/>
		 </a>
		 <xsl:text>&#10;</xsl:text>
	</xsl:for-each>

	<xsl:for-each select="link">
		 <a href="{normalize-space(url)}">
		 		 <xsl:value-of select="normalize-space(url)"/>
		 </a>
		 <xsl:text>&#10;</xsl:text>
	</xsl:for-each>

   </out>
</xsl:template>

</xsl:stylesheet>
