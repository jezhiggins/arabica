<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        
Sort by @d,@e,@c,@b, and then a3 

        <xsl:for-each select="xslSort/Sort/a3">
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3[d]"></xsl:sort>
            <xsl:sort select="a3[e]"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a3[b]"></xsl:sort>
            <xsl:sort select="a3"></xsl:sort>
            <xsl:value-of select="a3"></xsl:value-of>
            
	-name:
            <xsl:value-of select="name()"></xsl:value-of>
            
	-d:
            <xsl:value-of select="@d"></xsl:value-of>
            
	-e:
            <xsl:value-of select="@e"></xsl:value-of>
            
	-c:
            <xsl:value-of select="@c"></xsl:value-of>
            
	-b:
            <xsl:value-of select="@b"></xsl:value-of>
            	
	=
            <xsl:value-of select="."></xsl:value-of>
        </xsl:for-each>
        

Sort by a1 - a16
 
        <xsl:for-each select="xslSort/Sort">
            <xsl:sort select="a1"></xsl:sort>
            <xsl:sort select="a2"></xsl:sort>
            <xsl:sort select="a3[c]"></xsl:sort>
            <xsl:sort select="a4"></xsl:sort>
            <xsl:sort select="a5"></xsl:sort>
            <xsl:sort select="a6"></xsl:sort>
            <xsl:sort select="a7[c]"></xsl:sort>
            <xsl:sort select="a8"></xsl:sort>
            <xsl:sort select="a9"></xsl:sort>
            <xsl:sort select="a10"></xsl:sort>
            <xsl:sort select="a11[c]"></xsl:sort>
            <xsl:sort select="a12"></xsl:sort>
            <xsl:sort select="a13"></xsl:sort>
            <xsl:sort select="a14"></xsl:sort>
            <xsl:sort select="a15[c]"></xsl:sort>
            <xsl:sort select="a16"></xsl:sort>
             

	-name:
            <xsl:value-of select="name()"></xsl:value-of>
            
	
	=
            <xsl:value-of select="."></xsl:value-of>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
