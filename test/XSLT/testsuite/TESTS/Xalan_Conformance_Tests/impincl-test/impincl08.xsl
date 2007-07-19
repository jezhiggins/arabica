<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>

<xsl:variable name="testfile.xml" select="document('testfile.xml')"/>

<xsl:template name="TestInclude">
  <xsl:value-of select="$testfile.xml/doc/node"/>
</xsl:template>

</xsl:stylesheet>