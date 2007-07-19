<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  
<xsl:template match="/">

<xsl:processing-instruction 
			name='biteme' select="*" 
			comment='no' 
			xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			foo='bar'>
bitemebitemebiteme bitemebiteme

</xsl:processing-instruction>

</xsl:template>
</xsl:stylesheet>

<!-- Extra comment, should be harmless -->
<?Extra Processing Instruction, should be harmless ?>