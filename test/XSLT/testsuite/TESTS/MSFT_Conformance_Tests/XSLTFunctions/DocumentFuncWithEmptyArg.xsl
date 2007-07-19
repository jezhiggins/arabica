<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:my="http://my.com">

<xsl:output indent="yes" method="xml" omit-xml-declaration="yes" encoding="UTF-8"/>

      <xsl:template match="/">
            <xsl:copy-of select="document('')//my:data" />
      </xsl:template>

      <my:data>123</my:data>

</xsl:stylesheet>
