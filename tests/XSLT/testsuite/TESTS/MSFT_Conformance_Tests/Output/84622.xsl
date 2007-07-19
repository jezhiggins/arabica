<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:user="http://foo">
 
  <!--DEFAULT TO <xsl:output method="xml" /> -->
  <xsl:template match="/">
 <user:html>

<UL>
  	  <xsl:for-each select="SALAD/SALAD_INGREDIENTS/*">
  	    <LI><xsl:value-of select="name()"/>: <xsl:value-of select="."/></LI>
    	</xsl:for-each>
  	</UL></user:html>
  </xsl:template>
</xsl:stylesheet>