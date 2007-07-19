<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <STRING>
            <xsl:for-each select="//string">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS9="http://www.w3.org/XML/1998/namespace" NS9:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </STRING>
        <INT>
            <xsl:for-each select="//int">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS10="http://www.w3.org/XML/1998/namespace" NS10:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </INT>
        <dateTime>
            <xsl:for-each select="//dateTime">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS11="http://www.w3.org/XML/1998/namespace" NS11:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </dateTime>
        <ui4 order="descending">
            <xsl:for-each select="//ui4">
                <xsl:sort select="." order="descending"></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS12="http://www.w3.org/XML/1998/namespace" NS12:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </ui4>
        <uri>
            <xsl:for-each select="//uri">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS13="http://www.w3.org/XML/1998/namespace" NS13:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </uri>
        <INTasSTRING>
            <xsl:for-each select="//int">
                <xsl:sort select="." data-type="text"></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS14="http://www.w3.org/XML/1998/namespace" NS14:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </INTasSTRING>
        <MIXED asTYPE="none">
            <xsl:for-each select="//MIXED">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS15="http://www.w3.org/XML/1998/namespace" NS15:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </MIXED>
        <MIXED asTYPE="text">
            <xsl:for-each select="//MIXED">
                <xsl:sort select="." data-type="text"></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS16="http://www.w3.org/XML/1998/namespace" NS16:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </MIXED>
        <MIXED asTYPE="text" order="descending">
            <xsl:for-each select="//MIXED">
                <xsl:sort select="." data-type="text" order="descending"></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS17="http://www.w3.org/XML/1998/namespace" NS17:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </MIXED>
        <WHOLEDOC asTYPE="number">
            <xsl:for-each select="//*">
                <xsl:sort select="."></xsl:sort>
                <xsl:value-of select="name()"></xsl:value-of>
                <xsl:text xmlns:NS18="http://www.w3.org/XML/1998/namespace" NS18:space="preserve"></xsl:text>
                <xsl:value-of select="."></xsl:value-of>
            </xsl:for-each>
        </WHOLEDOC>
    </xsl:template>
</xsl:stylesheet>
