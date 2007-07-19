<?xml version="1.0" encoding="utf-8"?>
<!--Sample extraction of questionnare information-->
<!--$Date: 2001/12/07 21:00:12 $(UTC)-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<!--
Copyright (C) The Organization for the Advancement of
Structured Information Standards [OASIS] (2001). All Rights
Reserved.

This document and translations of it may be copied and
furnished to others, and derivative works that comment on
or otherwise explain it or assist in its implementation may
be prepared, copied, published and distributed, in whole
or in part, without restriction of any kind, provided that the
above copyright notice and this paragraph are included on
all such copies and derivative works. However, this
document itself may not be modified in any way, such as by
removing the copyright notice or references to OASIS,
except as needed for the purpose of developing OASIS
specifications, in which case the procedures for copyrights
defined in the OASIS Intellectual Property Rights document
must be followed, or as required to translate it into
languages other than English.

The limited permissions granted above are perpetual and
will not be revoked by OASIS or its successors or assigns.

This document and the information contained herein is
provided on an "AS IS" basis and OASIS DISCLAIMS ALL
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO ANY WARRANTY THAT THE USE
OF THE INFORMATION HEREIN WILL NOT INFRINGE
ANY RIGHTS OR ANY IMPLIED WARRANTIES OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR
PURPOSE.
-->
<xsl:output doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"
  method="html" encoding="UTF-8"/>

<xsl:template match="/">
    <html><head><title>OASIS Developer Questionnaire</title></head>
    <body>
      <xsl:copy-of select="doc/verbiage/title"/><br/>
      <xsl:copy-of select="doc/verbiage/question-intro"/>
      <ul>
    <xsl:for-each select="doc/items/item[question]">
      <xsl:for-each select="question">
        <xsl:text>
</xsl:text>
        <li>
          <xsl:if test="@scope='Prototype'">
            <xsl:text>(Pattern for questions) </xsl:text>
          </xsl:if>
          <xsl:value-of select="."/>       
          <xsl:if test="spec-citation[@type='section']">
            <xsl:text>See section </xsl:text>
            <xsl:value-of select="spec-citation[@type='section']"/>       
            <xsl:text> for context.</xsl:text>
          </xsl:if>
          <xsl:if test="../choices and (@scope='Filter' or @scope='Configuration')">
            <xsl:text> 
(choices: </xsl:text>
            <xsl:for-each select="../choices/choice">
              <xsl:if test="position()!=1">, </xsl:if>
              <xsl:value-of select="@value"/>       
            </xsl:for-each>
            <xsl:text>)</xsl:text>
            <xsl:if test="../elaborator">
              <xsl:text>
If </xsl:text>
              <xsl:value-of select="../elaborator/@choice" />
              <xsl:text>: </xsl:text>
              <xsl:value-of select="../elaborator" />
              <xsl:text>
</xsl:text>
            </xsl:if>
          </xsl:if>
        </li>
      </xsl:for-each>
    </xsl:for-each>
    </ul>
  </body></html>
</xsl:template>

</xsl:stylesheet>