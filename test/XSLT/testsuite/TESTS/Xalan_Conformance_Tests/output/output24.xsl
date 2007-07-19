<?xml version="1.0" encoding="ISO-8859-1"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml"/>

  <!-- FileName: OUTP24 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Escape of non-ASCII chars in URI attribute values using method 
       cited in Section B.2.1 of HTML 4.0 Spec. This test is a duplicate of
       OUTP31, except that the output is XML.  -->

<xsl:template match="/">
  <out>
    1. "&#165;"  <A attr="&#165;"/>
    2. "&quot;"  <A attr="&quot;"/>
    3. "&lt;"    <A attr="&lt;"/>
    4. "&gt;"    <A attr="&gt;"/>
    5. "&amp;"   <A attr="&amp;"/>
    6. "&#035;"  <A attr="&#035;"/>
    7. "&#039;"  <A attr="&#039;"/>
    8. "&#032;"  <A attr="&#032;"/>	<img src="Test 31 Gif.gif"/>
    9. "&#169;"  <A attr="&#169;"/>
  </out>
</xsl:template>

</xsl:stylesheet>
