<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<xsl:output method="xml" encoding="UTF-16"/>

	<xsl:variable name="foo">foo</xsl:variable>
	<xsl:variable name="default">xsl:default</xsl:variable>
	
	<xsl:template match="/">
	<test name="non-default">
		infinity =<xsl:value-of select="format-number(1 div 0, '2', $foo)"/>
		infinity =<xsl:value-of select="format-number(-1 div 0, '2', $foo)"/>
		decimal-separator =<xsl:value-of select="format-number(1.1, '2di', 'foo')"/>
		grouping-separator =<xsl:value-of select="format-number(1000111000.1, 'iiiiiiiii2diiiiiiiii', $foo)" />
		percent =<xsl:value-of select="format-number(1 div 1, 'i2p', $foo)" />
		per-mille =<xsl:value-of select="format-number(1000, 'iiigiiigii2diiim', $foo)" />
		pattern-separator =<xsl:value-of select="format-number(2-3.56, 'i2dii', $foo)" />
		nan =<xsl:value-of select="format-number(0 div 0, 'i2dii', $foo)" />
	</test>
	<p/>
	<test name="default">
		infinity =<xsl:value-of select="format-number(1 div 0, '0', $default)"/>
		infinity =<xsl:value-of select="format-number(-1 div 0, '0', $default)"/>
		decimal-separator =<xsl:value-of select="format-number(1.1, '0', 'xsl:default')"/>
		grouping-separator =<xsl:value-of select="format-number(1000111000.1, '#,##0.###', $default)" />
		percent =<xsl:value-of select="format-number(1 div 1, '0%', $default)" />
		per-mille =<xsl:value-of select="format-number(1, '#,000.00&#x2030;', $default)" />
		pattern-separator =<xsl:value-of select="format-number(2-3.56, 'iidii0', $default)" />
		nan =<xsl:value-of select="format-number(0 div 0, 'iidii0', $default)" />
	</test>
	<p/>
	<test name="default : possible bug, saxom output different from msxml.">
		per-mille =<xsl:value-of select="format-number(1, '#,000.00&#x2030;', 'default')" />
	</test>

	</xsl:template>

	<xsl:decimal-format name="foo" 
		decimal-separator="d" 
		grouping-separator="g" 
		percent="p"
		per-mille="m" 
		zero-digit="2" 
		digit="i" 
		pattern-separator="|" 
		infinity="~" 
		NaN=" nan " 
		minus-sign="+" 
	/>
	<xsl:decimal-format name="xsl:default" /> 
	<xsl:decimal-format name="default" /> 



</xsl:stylesheet>

