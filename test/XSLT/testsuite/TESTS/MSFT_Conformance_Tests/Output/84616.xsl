<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output omit-xml-declaration="yes"/>
  <!--<xsl:output method="xml" omit-xml-declaration="yes"/> -->
  <xsl:template match="/">
  	<UL>
  	  <xsl:for-each select="SALAD/SALAD_INGREDIENTS/*">
  	    <LI><xsl:value-of select="name()"/>: <xsl:value-of select="."/></LI>
    	</xsl:for-each>
  	</UL>
  </xsl:template>
</xsl:stylesheet>