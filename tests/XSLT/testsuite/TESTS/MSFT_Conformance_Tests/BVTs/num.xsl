<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com" exclude-result-prefixes="my">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">

        <xsl:text>Document Root Tests&#10;</xsl:text>

        <!-- xsl:number at the document root -->
        <x><xsl:number/></x>
        <x><xsl:number level="any"/></x>
        <x><xsl:number level="multiple" from="/"/></x>

        <xsl:text>&#10;&#10;Value Tests&#10;</xsl:text>

        <!-- Test value attribute -->
        <x><xsl:number value="1999"/></x>
        <x><xsl:number value="1999.499999999"/></x>
        <x><xsl:number value="'1999'"/></x>
        <x><xsl:number value="'1999.5'"/></x>
        <x><xsl:number value=".00000000000000000000000000001"/></x>
        <x><xsl:number value="-2147483648"/></x>
        <x><xsl:number value="2147483647"/></x>
        <x><xsl:number value="10000000000000000000000" grouping-separator="," grouping-size="3"/></x>
        <x><xsl:number value="-10000000000000000000000" grouping-separator="," grouping-size="3"/></x>

        <xsl:text>&#10;&#10;Formatting Tests&#10;</xsl:text>
        <xsl:apply-templates select="//last-name" mode="formatting-tests"/>

        <xsl:text>&#10;&#10;Counting Tests&#10;</xsl:text>
        <xsl:apply-templates select="//title | //my:title" mode="counting-tests"/>
        <xsl:apply-templates select="processing-instruction() | comment() | //book/@style" mode="nodetype-tests"/>

        <xsl:call-template name="grouping"/>
        <xsl:call-template name="zero-padding"/>
        <xsl:call-template name="avts"/>

    </xsl:template>

    <xsl:template name="avts">

        <xsl:text>&#10;&#10;AVT Tests&#10;</xsl:text>

        <xsl:variable name="grouping-size" select="'2'"/>
        <xsl:variable name="grouping-separator" select="','"/>
        <xsl:variable name="letter-val" select="'trad'"/>
        <xsl:variable name="format" select="'&#x05d0;'"/>
        <xsl:variable name="lang" select="'k'"/>

        <!-- Test AVT attributes -->
        <x><xsl:number value="99999" grouping-size="{$grouping-size + 1}" grouping-separator="{concat($grouping-separator, '')}"/></x>
        <x><xsl:number value="3999" format="{$format}" letter-value="{concat($letter-val, 'itional')}"/></x>
        <x><xsl:number value="99999" format="{''}"/></x>
        <x><xsl:number value="1000" format="{'&#x4e00;'}" lang="{concat($lang, 'o')}"/></x>

    </xsl:template>

    <xsl:template name="zero-padding">

        <xsl:text>&#10;&#10;Zero-padding Tests&#10;</xsl:text>

        <!-- Test zero padding -->
        <x><xsl:number value="999" format="000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"/></x>
        <x><xsl:number value="999" format="000010"/></x>
        <x><xsl:number value="999" format="000002"/></x>
        <x><xsl:number value="999" format="2"/></x>
    
    </xsl:template>

    <xsl:template name="grouping">

        <xsl:text>&#10;&#10;Grouping Tests&#10;</xsl:text>

        <!-- Test grouping-separator and grouping-size attributes -->
        <x><xsl:number value="2147483648" grouping-separator="," grouping-size="3"/></x>
        <x><xsl:number value="100000" grouping-separator=" " grouping-size="2"/></x>
        <x><xsl:number value="100000" grouping-separator="," grouping-size="0"/></x>
        <x><xsl:number value="2147483648" grouping-separator="," grouping-size="-15"/></x>
        <x><xsl:number value="2147483648" grouping-separator="," grouping-size="10000000000"/></x>
    
    </xsl:template>

    <xsl:template match="last-name" mode="formatting-tests">

        <xsl:text>&#10;</xsl:text>

        <!-- Test various formatting combinations -->
        <xsl:number level="multiple" count="last-name | publication | author | book"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format=""/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format="A"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format=";1"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format="A="/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format="*"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format="A 1 A 1 A 1 A 1 A"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="last-name | publication | author | book" format="A.1"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="unknown" format="="/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="unknown" format=".1."/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="unknown" format=".1.1"/><xsl:text>, </xsl:text>

        <xsl:value-of select="concat(../first-name, ' ', .)"/>

    </xsl:template>

    <xsl:template match="title | my:title" mode="counting-tests">

        <xsl:text>&#10;</xsl:text>

        <!-- Test level, count, from attributes -->
        <xsl:number level="single" count="book | my:book | magazine | my:magazine"/><xsl:text>, </xsl:text>
        <xsl:number level="single" count="title | my:title" from="my:book"/><xsl:text>, </xsl:text>
        <xsl:number level="single"/><xsl:text>, </xsl:text>
        <xsl:number level="single" count="unknown"/><xsl:text>, </xsl:text>

        <xsl:number level="multiple" count="book | my:book | magazine | my:magazine | title | bookstore | /"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="book | my:book | magazine | my:magazine | title | bookstore | /" from="bookstore"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="book | my:book | magazine | my:magazine | title | bookstore | /" from="unknown"/><xsl:text>, </xsl:text>

        <xsl:number level="any" count="*"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="*" from="book"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="title" from="title"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="*/first-name[1]"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="*" from="unknown"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="unknown" from="*"/><xsl:text>, </xsl:text>

    </xsl:template>

    <xsl:template match="node() | @*" mode="nodetype-tests">

        <xsl:text>&#10;</xsl:text>

        <!-- Test counting where original node is not an element -->
        <xsl:number level="any" count="node() | / | @*"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="node() | / | @*" from="*"/><xsl:text>, </xsl:text>
        <xsl:number level="any" count="node() | / | @*" from="@*"/><xsl:text>, </xsl:text>

        <xsl:number level="multiple" count="node() | / | @*"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="node() | / | @*" from="bookstore"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="node() | / | @*" from="@*"/><xsl:text>, </xsl:text>
        <xsl:number level="multiple" count="@*" from="book"/><xsl:text>, </xsl:text>
    
    </xsl:template>

</xsl:stylesheet>
