<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo" select="bookstore"/>

    <!-- Attempt to use a variable within the use expression -->
    <xsl:key name="keyname" match="author" use="1 + $foo + 2"/>

</xsl:stylesheet>
