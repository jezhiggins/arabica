<xsl:stylesheet version="1.0"
                      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                      xmlns:myxsl="http://www.myxsl.com">

<!-- Regression case for bug 73638 -->

<xsl:output indent="yes" encoding="utf-8"/>

<xsl:template match="/">
   <stylesheet version="1.0" />
</xsl:template>

<xsl:namespace-alias stylesheet-prefix="#default" result-prefix="myxsl"/>

</xsl:stylesheet>