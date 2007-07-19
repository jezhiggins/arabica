<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
BEFORE
   <xsl:element name="foo-element"><xsl:attribute name="A1">yow!</xsl:attribute>
content goes here
   </xsl:element>
AFTER
</xsl:template></xsl:stylesheet>