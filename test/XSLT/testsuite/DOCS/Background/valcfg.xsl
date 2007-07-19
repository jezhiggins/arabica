<?xml version="1.0" encoding="utf-8"?>
<!--Script to validate discretion documents against test suite configuration-->
<!--$Date: 2001/12/05 20:24:02 $(UTC)-->

<!--not documented yet-->
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

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:output indent="yes"/>

<xsl:template match="/">
  <problems>
    <xsl:for-each select="/suite/citations/citation-specifications/
                          cite-spec/version-spec/spec">
      <xsl:variable name="type" select="@type"/>
      <xsl:if test="name(id(string($type))) != 'cite-type'">
        <problem value="{$type}">bad citation type value</problem>
      </xsl:if>
    </xsl:for-each>
    <xsl:if test="not( 
                 /suite/citations/citation-types/cite-type/@method='human'
             and /suite/citations/citation-types/cite-type/@method='machine')">
      <problem>must have at least one citation type for each of <xsl:text/>
      <xsl:text/>the human and machine methods.</problem>
    </xsl:if>
    <xsl:for-each select="/suite/gray-areas/gray-area">
      <xsl:variable name="citation-types" select="spec-citation/@type"/>
      <xsl:if test="not(id($citation-types)/@method='human'
                    and id($citation-types)/@method='machine')">
        <problem value="{$citation-types/ancestor::item/@id}">
          <xsl:text>each gray area must have at least one human </xsl:text>
          <xsl:text>and one machine citation</xsl:text>
        </problem>
      </xsl:if>
    </xsl:for-each>
    <xsl:for-each select="//spec-citation">
      <xsl:variable name="spec" select="id(string(@spec))"/>
      <xsl:choose>
        <xsl:when test="not(name($spec)='cite-spec')">
          <problem value="{@spec}">
            <xsl:text>Specification citation is not to a </xsl:text>
            <xsl:text>specification description.</xsl:text>
          </problem>
        </xsl:when>
        <xsl:otherwise>
          <xsl:if test="not($spec/version-spec[@version=current()/@version])">
            <problem value="{@version}">
              <xsl:text>Given version not found for specification </xsl:text>
              <xsl:text/>id="<xsl:value-of select="@spec"/>"<xsl:text/>
            </problem>
          </xsl:if>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
  </problems>
</xsl:template>

</xsl:stylesheet>
