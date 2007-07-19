<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>


<!-- 
    xsl:key : Example from xslt spec : to generate hyper links

    -//place match 2 times
    - each time it match and id is generated because key('', 'seattle')  and 
        key('', 'bellevue') both exist

    -  city match 4 time with
    - all 4 times 'id' are generated, used the generated id for the 
        fist encounter of city(seattle) and city(bellevue)

-->

<xsl:template match="//place" >
[
<b>
BLAR
    <a href="#{generate-id(key('func', .))}">
        <xsl:apply-templates/>
    </a>
</b>
</xsl:template>

<xsl:template match="city">
[
<p> 
    <a name="{generate-id()}">
        <b>CITY: </b>
        this is a test <br/>
        this is a test <br/>
        this is a test <br/>
        this is a test <br/>
        this is a test <br/>
        this is a test <br/>
    </a>
</p>
</xsl:template>

<xsl:key name="func" match="city" use="@name"/>

</xsl:stylesheet>
