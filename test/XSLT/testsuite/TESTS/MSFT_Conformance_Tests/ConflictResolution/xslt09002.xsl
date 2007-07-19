<?xml version='1.0'?>
<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0" 

xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
 
<output method="xml" omit-xml-declaration="yes"/>

 <template match="/">
	
		<apply-templates/>
	
 </template>
<template match="magazine/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="*">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

  <template match="*" priority="-1">
	<my:SPAN style="color=red" > BUG
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="magazine/title">
	<my:SPAN style="color=brown" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="text()" priority="-20">
<apply-templates/>
</template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>


<template match="*">
	<apply-templates/>
  </template>
</stylesheet>
