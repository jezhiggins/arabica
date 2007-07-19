<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:jsp="http://www.w3.org/jsp"
				xmlns="http://www.w3.org/TR/REC-html40"
                exclude-result-prefixes="jsp">

  <!-- FileName: OUTP63 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: The html output method should not output an element 
                differently from the xml output method unless the 
                expanded-name of the element has a null namespace URI; an 
                element whose expanded-name has a non-null namespace URI 
                should be output as XML. So the html tags <p>, <hr> and
                <br> in this case, due to the default html namespace will
                be output as xml not html. -->
  <!-- Creator: Paul Dick -->

<xsl:output method="html"/>

<xsl:template match="/">
  <HTML>
    <jsp:setProperty name="blah" property="blah" value="blah"/>
	<P></P>
	<p/>
	<P/>
	<hr size="8"></hr>
	<hr size="8"/>
	<br/>
	<br>
	</br>
  </HTML>
</xsl:template>

</xsl:stylesheet>