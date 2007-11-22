<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output method="xml"/>

  <xsl:template match="/">
    <yes>
      <xsl:processing-instruction name="xmlish">woo</xsl:processing-instruction>
    </yes>
  </xsl:template>

</xsl:stylesheet>
