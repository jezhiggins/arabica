<?xml version='1.0'?>
<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0" 

xmlns:my="urn:http//www.placeholder-name-here.com/schema/" 
exclude-result-prefixes="my">
 
<template match="magazine/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br exclude-result-prefixes="my:" /><apply-templates/>
  </template>
<template match="magazine[@style='glossy']" priority="-500">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

  <template match="magazine[@style='glossy']" priority="-500">
	<my:SPAN style="color=red" > BUG
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="magazine/title" priority="-1000">
	<my:SPAN style="color=brown" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="text()" priority="-500">
<apply-templates/>
</template>
<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
  <template match="magazine[@style='glossy']" priority="-1000">
	<my:SPAN style="color=blue" > 
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="my:book/my:title" priority="-50">
	<my:SPAN style="color=brown" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
:
<apply-templates/>
</template>

<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="my:magazine" priority="-50">
	<my:SPAN style="color=blue" > 
<value-of select="name()"/>: <value-of select="*"/> </my:SPAN>
:
<apply-templates/>
</template>

<template match="book/title" priority="-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/price" priority = "-1000">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" priority="-500">
	<my:SPAN style="color=green"  exclude-result-prefixes="my:">
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="book/price" priority = "-1000">
	<my:SPAN style="color=orange" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br exclude-result-prefixes="my"/><apply-templates/></template>

<template match="*" priority="-100">
	<my:BUG></my:BUG>
	<apply-templates/>
</template>

<include href="lowpribooks17.xsl"/>

</stylesheet>
