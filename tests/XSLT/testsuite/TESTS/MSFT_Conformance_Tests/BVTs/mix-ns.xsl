<xslt:stylesheet version="1.0" xmlns:xslt="http://www.w3.org/1999/XSL/Transform" xmlns:xtl="http://www.w3.org/TR/WD-xsl">
        <xslt:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Old namespace should not be recognized -->
	<xslt:template match="/">
		<xtl:value-of select="."/>
	</xslt:template>
</xslt:stylesheet>
