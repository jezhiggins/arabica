<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method='xml' omit-xml-declaration='yes' />

  <xsl:template match="/root/foo[@attr !='Blah']">
	<FILTER/>
  </xsl:template>

  <xsl:template match="//foo">
	<NO-FILTER/>
  </xsl:template>

</xsl:transform>