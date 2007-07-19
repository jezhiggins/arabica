<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

  <xsl:template match="//firstname/pic">
	<xsl:value-of select="unparsed-entity-uri(name())"/>
  </xsl:template>
  <xsl:template match="text()"/>
</xsl:stylesheet>