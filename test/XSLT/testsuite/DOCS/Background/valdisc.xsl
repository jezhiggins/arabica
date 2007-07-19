<?xml version="1.0" encoding="utf-8"?>
<!--Script to validate discretion documents against test suite configuration-->
<!--$Date: 2001/11/16 17:46:40 $(UTC)-->

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

<xsl:variable name="configuration" 
           select="document(doc/@configuration-href,doc/@configuration-href)"/>
<xsl:variable name="doc" select="/doc"/>

<xsl:output indent="yes"/>

<xsl:template match="/">
  <problems>
    <xsl:if test="not($configuration)">
      <xsl:variable name="err">
        <xsl:text>Configuration file '</xsl:text>
        <xsl:value-of select="/doc/@configuration-href"/>
        <xsl:text>' not found.</xsl:text>
      </xsl:variable>
      <problem><xsl:copy-of select="$err"/></problem>
      <xsl:message terminate="yes"><xsl:copy-of select="$err"/></xsl:message>
    </xsl:if>
    <xsl:for-each select="/doc/verbiage/group-intro">
      <xsl:variable name="status" select="@status"/>
      <xsl:for-each select="$configuration">
        <xsl:if test="name(id(string($status))) != 'discretion-status'">
          <problem value="{$status}">bad discretion status value</problem>
        </xsl:if>
      </xsl:for-each>
    </xsl:for-each>
    <xsl:for-each select="$configuration/suite/
                          discretion-statuses/discretion-status/@id">
      <xsl:if test="not($doc/verbiage/group-intro/@status=.)">
        <problem value="{.}">missing group-intro definition <xsl:text/>
                  <xsl:text/>for status value</problem>
      </xsl:if>
    </xsl:for-each>
    <xsl:for-each select="/doc/items/item">
      <xsl:variable name="citation-types" select="spec-citation/@type"/>
      <xsl:for-each select="$configuration">
        <xsl:if test="not(id($citation-types)/@method='human'
                      and id($citation-types)/@method='machine')">
          <problem value="{$citation-types/ancestor::item/@id}">
            <xsl:text>each item must have at least one human </xsl:text>
            <xsl:text>and one machine citation</xsl:text>
          </problem>
        </xsl:if>
      </xsl:for-each>
    </xsl:for-each>
    <xsl:for-each select="/doc/items/item/spec-citation">
      <xsl:variable name="spec" select="@spec"/>
      <xsl:for-each select="$configuration">
        
        <xsl:if test="name(id(string($spec))) != 'cite-spec'">
          <problem value="{$spec}">unexpected specification cited</problem>
        </xsl:if>
      </xsl:for-each>
    </xsl:for-each>
  </problems>
</xsl:template>

</xsl:stylesheet>
