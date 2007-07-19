<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

  <xsl:template match="firstname">
	<xsl:value-of select="unparsed-entity-uri(@nopic)"/>
  </xsl:template>
  <xsl:template match="text()"/>
</xsl:stylesheet>