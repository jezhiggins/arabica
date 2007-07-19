<?xml version="1.0" ?>
<Schema xmlns="urn:schemas-microsoft-com:xml-data"
	xmlns:dt ="urn:schemas-microsoft-com:datatypes">

    <AttributeType name="type"/>
    <AttributeType name="made"/>
    <AttributeType name="model"/>

    <ElementType name="item" model="closed">
        <attribute type="type"/>
        <attribute type="made"/>
        <attribute type="model" />
    </ElementType>

	<ElementType name="items" >
        <attribute type="type"/>
		<element type="item" /> 
	</ElementType>
	
</Schema>
