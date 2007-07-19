<?xml version='1.0'?>
<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0" 

xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
 


 <template match="/">
	
		<apply-templates/>
	
 </template>

<template match="*|comment()|processing-instruction()|node()">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

  <template match="*" priority="-51">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="@*" priority="-.49">
	<my:SPAN style="color=black" > 
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

  <template match="@*">
	<my:SPAN style="color=yellow" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="text()" priority="-20">
<my:SPAN style="color:blue"><apply-templates/></my:SPAN>
</template>




</stylesheet>
