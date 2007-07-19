<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  

  <xsl:template match="/">
          <xsl:for-each select="EscapeChars">
				<xsl:apply-templates/>
          </xsl:for-each>
  </xsl:template>   

  <xsl:template match="EscapeChars/Char">
    <xsl:value-of select="Char" disable-output-escaping="yes"/>
  </xsl:template>

</xsl:stylesheet>


