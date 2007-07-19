<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="urn:bang" xmlns="urn:foo">

<xsl:import href="d.inc"/>

    <xsl:variable name="foo" select="'In style sheet b'"/>
    <xsl:variable name="bar" select="'In style sheet b'"/>
    <xsl:variable name="foobar" select="'In style sheet b'"/>
</xsl:stylesheet>

