<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:myxsl="myxsl_uri" xmlns:axsl="axsl_uri">

<xsl:namespace-alias stylesheet-prefix="myxsl" result-prefix="axsl"/>

    <xsl:template match="/">
	<myxsl:bar/>
    </xsl:template>

</xsl:stylesheet>