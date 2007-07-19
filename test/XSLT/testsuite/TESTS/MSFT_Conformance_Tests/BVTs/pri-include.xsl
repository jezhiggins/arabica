<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/" priority=".5">ERROR</xsl:template>

	<!-- Include stylesheet having literal result element as stylesheet.  Default priority should be 0.5 -->
	<xsl:include href="xsl2.inc"/>

	<!-- Include many elements having same GI.  This test will also cause hashing to occur. -->
	<xsl:include href="pri.inc"/>

	<xsl:include href="pri.inc"/>

	<xsl:include href="pri.inc"/>

	<xsl:include href="pri.inc"/>

</xsl:stylesheet>
