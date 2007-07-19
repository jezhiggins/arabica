<!-- Test file for bug # 71029, the variable $test is defined within the imported file. This is valid and should not throw any error. -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:import href="xslt_nested_import_variable_scope.inc"/>

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="no" indent="yes"/>
    <xsl:variable name="test" select="doc"/>

    <xsl:template match="/">
    <out>
    	<xsl:value-of select="$test"/>
    </out>
    </xsl:template>
    
</xsl:stylesheet>