<?xml version="1.0" ?>
<Schema xmlns="urn:schemas-microsoft-com:xml-data"
	xmlns:dt ="urn:schemas-microsoft-com:datatypes">

    <AttributeType name="type"/>
    <AttributeType name="made"/>

    <ElementType name="item" model="closed">
        <attribute type="type"/>
        <attribute type="made"/>
    </ElementType>

	<ElementType name="query" content="eltOnly" model="closed">
		<element type="item" /> 
		<element type="item" /> 
	</ElementType>

</Schema>
