<?xml version="1.0" encoding="utf-8"?>
<!--$Id: disc2htm.xsl,v 1.7 2001/11/17 22:31:12 Administrator Exp $-->
<!DOCTYPE xsl:stylesheet [
<!ENTITY nbsp "&#xA0;">
]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:data="dummy"
                exclude-result-prefixes="data"
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
<xsl:output doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

<xsl:variable name="configuration" 
              select="document(/doc/@configuration-href,
                               /doc/@configuration-href)"/>

<xsl:template match="doc">             <!--main body of the report-->
  <xsl:if test="not($configuration)">
    <xsl:variable name="err">
      <xsl:text>Configuration file '</xsl:text>
      <xsl:value-of select="/doc/@configuration-href"/>
      <xsl:text>' not found.</xsl:text>
    </xsl:variable>
    <xsl:message terminate="yes"><xsl:copy-of select="$err"/></xsl:message>
  </xsl:if>
  <html><head><title><xsl:value-of select="verbiage/title"/></title></head>
    <body>
      <xsl:apply-templates select="verbiage/title"/>      
      <a href="#introduction">1. Introduction</a><br/>
      <a href="#statuses">2. Status</a><br/>
      <xsl:for-each select="verbiage/group-intro">
        <a href="#{@status}">
          <xsl:text/>2.<xsl:number/>
          <xsl:text> </xsl:text>
          <xsl:value-of select="@status"/></a><br/>
        </xsl:for-each>
        <a href="#tocs">3. Tables of Content</a><br/>
        <a href="#history">4. Change History</a><br/>
      <xsl:apply-templates select="verbiage"/>
      <hr/>
      <h1><a name="statuses">2. Status</a></h1>
      <xsl:apply-templates select="verbiage/group-intro"/>
      <xsl:call-template name="tocs"/>
      <xsl:apply-templates select="changes"/>
      <hr/>
      <small><strong><xsl:value-of select="@date"/></strong></small>
    </body>
  </html>
</xsl:template>

<xsl:template match="verbiage/title">       <!--title and TOC of report-->
  <h1><xsl:copy-of select="node()"/></h1>
  <p>Revised: <xsl:value-of select="/doc/@date"/></p>
</xsl:template>

<!--========================================================================-->
<!--each section of the report-->

<xsl:template match="verbiage">
  <hr/>
  <h1><a name="introduction">1. Introduction</a></h1>
  <xsl:apply-templates select="intro" mode="specialist"/>
</xsl:template>

<xsl:template match="group-intro">
  <h2><a name="{@status}">2.<xsl:number/><xsl:text> </xsl:text>
                          <xsl:value-of select="@status"/></a></h2>
  <xsl:copy-of select="node()"/>
  <xsl:for-each select="/doc/items/item[@status=current()/@status]">
    <xsl:variable name="item" select="."/>
    <hr/>
    <h2><a name="{@id}"><xsl:call-template name="item-ref"/>
      <xsl:text> </xsl:text>
      <xsl:value-of select="@id"/></a></h2>
    <xsl:if test="@expandable">
      <p><em>Expandable: </em>
         <strong><xsl:value-of select="@expandable"/></strong></p>
    </xsl:if>
    <xsl:copy-of select="excerpt/node()"/>
    <xsl:if test="question">
      <p><em>Question<xsl:if test="count(question)>1">s</xsl:if>: </em></p>
      <xsl:for-each select="question">
        <p>
          <xsl:number/>. 
          <xsl:if test="@scope">(<xsl:value-of select="@scope"/>) </xsl:if>
          <xsl:copy-of select="node()"/>
        </p>
      </xsl:for-each>
    </xsl:if>
    <xsl:choose>
      <xsl:when test="choices">
        <p><em>Valid choices: </em>
          <xsl:for-each select="choices/choice">
            <xsl:if test="position()!=1">, </xsl:if>
            <xsl:value-of select="@value"/>       
          </xsl:for-each>
        </p>
      </xsl:when>
      <xsl:otherwise>
        <p><strong><em>No choices available.</em></strong></p>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:for-each select="/doc/interlocks/interlock
                          [.//party/@idref=current()/@id]">
      <p><em>Interlock: </em><!--put first element in para only if is a para-->
        <xsl:apply-templates mode="specialist" select="*[1][self::p]/node()">
          <xsl:with-param name="item" select="$item"/>
        </xsl:apply-templates>
      </p>                             <!--follow with rest of documentation-->
      <xsl:apply-templates mode="specialist" select="*[1][not(self::p)] |
                                                     *[position()>1]">
        <xsl:with-param name="item" select="$item"/>
      </xsl:apply-templates>
    </xsl:for-each>

    <xsl:variable name="citations" select="spec-citation"/>
    <p><em>Specification citations (manual): </em></p>
    <ul>
      <xsl:for-each select="$citations">
        <xsl:variable name="spec" select="@spec"/>
        <xsl:variable name="version" select="@version"/>
        <xsl:variable name="type" select="@type"/>
        <xsl:variable name="place" select="@place"/>
        <xsl:for-each select="$configuration">
          <xsl:if test="id(string($type))/@method='human'">
            <xsl:for-each select="id(string($spec))/
                                  version-spec[@version=$version]/
                                  spec[@type=$type]">
              <li>
                <xsl:value-of select="@prefix"/>
                <xsl:choose>
                  <xsl:when test="@ref-linkable='yes'">
                    <a href="{@ref}"><xsl:value-of select="@ref"/></a>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="@ref"/>
                  </xsl:otherwise>
                </xsl:choose>
                <xsl:value-of select="concat(@infix,$place,@suffix)"/>
              </li>
            </xsl:for-each>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>
    </ul>
    <p><em>Specification citations (machine): </em></p>
    <ul>
      <xsl:for-each select="$citations">
        <xsl:variable name="spec" select="@spec"/>
        <xsl:variable name="version" select="@version"/>
        <xsl:variable name="type" select="@type"/>
        <xsl:variable name="place" select="@place"/>
        <xsl:for-each select="$configuration">
          <xsl:if test="id(string($type))/@method='machine'">
            <xsl:for-each select="id(string($spec))/
                                  version-spec[@version=$version]/
                                  spec[@type=$type]">
              <xsl:variable name="ref"
                          select="concat(@prefix,@ref,@infix,$place,@suffix)"/>
              <li>
                <a href="{$ref}"><xsl:value-of select="$ref"/></a>
              </li>
            </xsl:for-each>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>
    </ul>
  </xsl:for-each>
  <hr/>
</xsl:template>

<xsl:template match="items"/>             <!--already handled in group-intro-->

<!--========================================================================-->
<!--specialist element handling-->

<xsl:template mode="specialist" match="party">
  <xsl:param name="item" select="/.."/>
  <xsl:text/>'<a>
                <xsl:if test="$item/@id!=@idref">
                  <xsl:attribute name="href">
                    <xsl:text/>#<xsl:value-of select="@idref"/>
                  </xsl:attribute>
                </xsl:if>
                <xsl:value-of select="@idref"/>
              </a>'<xsl:text/>
</xsl:template>

<xsl:key name="choices" match="choice/@value" use="."/>

<xsl:template mode="specialist" match="all-choices">
  <xsl:for-each select="//choice/@value
                        [generate-id(.)=generate-id(key('choices',.))]">
    <xsl:sort/>
    <xsl:if test="position()!=1">, </xsl:if>
    <strong><xsl:value-of select="."/></strong>
  </xsl:for-each>
</xsl:template>

<xsl:template mode="specialist" match="*">
  <xsl:param name="item" select="/.."/>
  <xsl:copy>
    <xsl:copy-of select="@*"/>
    <xsl:apply-templates mode="specialist">
      <xsl:with-param name="item" select="$item"/>
    </xsl:apply-templates>
  </xsl:copy>
</xsl:template>

<xsl:template match="interlocks"/>       <!--interlocks handled individually-->

<!--========================================================================-->
<!--tables of content-->

<xsl:template name="tocs">
  <xsl:variable name="section" select="'3'"/>
  <h1><a name="tocs">
        <xsl:value-of select="$section"/>. Tables of Content</a></h1>
  <h2><a name="toc-alpha">
   <xsl:value-of select="$section"/>.1 Alphabetical by item identifier</a></h2>
  <ul>
    <xsl:for-each select="//item">
      <xsl:sort select="@id"/>
      <li>
        <a href="#{@id}"><xsl:value-of select="@id"/></a>
        <xsl:text/> (<xsl:call-template name="item-ref"/>)<xsl:text/>
      </li>
    </xsl:for-each>
  </ul>
  <h2><a name="toc-interlocks">
   <xsl:value-of select="$section"/>.2 Interlock summary</a></h2>
  <ol>
    <xsl:for-each select="//interlock">
      <li>
        <xsl:for-each select=".//party">
          <xsl:sort select="@idref"/>
          <xsl:if test="position()>1">, </xsl:if>  
          <a href="#{@idref}"><xsl:value-of select="@idref"/></a>
          <xsl:for-each select="id(@idref)">
            <xsl:text/> (<xsl:call-template name="item-ref"/>)<xsl:text/>
          </xsl:for-each>
        </xsl:for-each>
      </li>
    </xsl:for-each>
  </ol>
</xsl:template>

<xsl:template name="item-ref"> <!--the formatting of an item's ref in report-->
  <xsl:text>2.</xsl:text>
  <xsl:value-of select="count(id(@status)/preceding-sibling::group-intro)+1"/>
  <xsl:text>.</xsl:text>
  <xsl:value-of select="count(preceding-sibling::*
                              [@status=current()/@status]) + 1"/>
</xsl:template>

<!--========================================================================-->
<!--change history-->

<xsl:template match="changes">
  <h1>4. Change History</h1>
  <xsl:for-each select="change">
    <hr/>
    <p><strong><xsl:value-of select="@date"/>: </strong></p>
    <xsl:copy-of select="node()"/>
  </xsl:for-each>
</xsl:template>

<!--========================================================================-->
<!--default behaviours-->

<xsl:template match="*">
  <xsl:message>
    <xsl:text/>Element <xsl:value-of select="name(.)"/> not handled.<xsl:text/>
  </xsl:message>
</xsl:template>

</xsl:stylesheet>
