<xsl:stylesheet version="1.0"
                      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                      xmlns:myxsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="variable-name">v</xsl:param>
<xsl:param name="default-value"/>
<xsl:output indent="yes"/>

<xsl:template match="/">
   <myxsl:stylesheet version="1.0">
   <myxsl:variable name="{$variable-name}">
      <xsl:value-of select="$default-value"/>
   </myxsl:variable>
   </myxsl:stylesheet>
</xsl:template>

<xsl:namespace-alias stylesheet-prefix="myxsl" result-prefix="xsl"/>

</xsl:stylesheet>