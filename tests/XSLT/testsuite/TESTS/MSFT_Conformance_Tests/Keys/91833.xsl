<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>


<!-- 
    xsl:key : Example from xslt spec : to generate hyper links
    
    - bcity only match twice
    - the first '.' of //place is 'seattle' so have no match from key()
    -   thus, the generated-id is empty
    - the second time '.' of //place is 'bellevue' so generate an id
        wihci is then used for the fist match of "bcity"'s generate-id()
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

<xsl:template match="bcity">
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

<xsl:key name="func" match="bcity" use="@name"/>

</xsl:stylesheet>
