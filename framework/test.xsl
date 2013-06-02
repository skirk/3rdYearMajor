<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="text" indent="no" />

	<xsl:template match="/">
		<xsl:apply-templates select="root"/>
	</xsl:template>

	<xsl:template match="root">
		<xsl:apply-templates select="shader"/>
	</xsl:template>

	<xsl:template match="shader">
		<xsl:value-of select="string('#version 400 &#xA;')"/>
		<xsl:apply-templates select="import"/>
		<xsl:apply-templates select="export"/>
		<xsl:apply-templates select="uniforms"/>
		<xsl:apply-templates select="node" mode="declare"/>
		<xsl:value-of select="string('void main()&#xA;{&#xA; ')"/>
		<xsl:apply-templates select="node[position()=1]" mode="call"/>
		<!-- Export the slots -->
		<xsl:apply-templates select="export" mode="export"/>
		<xsl:value-of select="string('}&#xA; ')"/>
	</xsl:template>

	<!-- ====================== DECLARATIONS ===================== -->
	<!-- create a function call for diagram nodes -->
	<xsl:template match="node[@type='graph']" mode="declare">
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat (generate-id(), @id )"/>	
		</xsl:variable>
		<xsl:apply-templates select="node[@type='graph']" mode="declare"/>
		<xsl:value-of select="concat('void ', @name,$functionCallID, '( ')" />
		<xsl:apply-templates select="output" mode="declare" />
		<xsl:apply-templates select="input" mode="declare" />
		<xsl:value-of select="string(')&#xA;{&#xA;')" />
		<xsl:apply-templates select="node[position()=1]" mode="call" />
		<xsl:apply-templates select="output" mode="export" />
		<xsl:value-of select="string('}&#xA;')" />
	</xsl:template>
	<!-- function output parameters -->
	<xsl:template match="output" mode="declare">
		<xsl:if test="position()!=1">
			<xsl:value-of select="string(',')" />
		</xsl:if>
		<xsl:value-of select="concat('out ',@var, ' ', @name)" />
	</xsl:template>

	<!-- function input parameters -->
	<xsl:template match="input" mode="declare">
		<xsl:value-of select="concat(', in ',@var, ' ', @name)" />
	</xsl:template>
	<xsl:template match="output" mode="declareOutputVariables">
		<xsl:param name="functionCallID" />
		<xsl:value-of select="concat(@var,' ',@name, $functionCallID,';&#xA;')" />
	</xsl:template>


	<!-- ====================== CALLS ===================== -->
	<xsl:template match="node[@type='operator']" mode="call">
		<xsl:apply-templates select="following-sibling::node[position()=1]" mode="call" />
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat( generate-id(), @id )" />
		</xsl:variable>
		<xsl:variable name="result">
			<xsl:value-of select="output/@var" />
		</xsl:variable>
		<xsl:value-of select="concat($result, ' ')" />
		<xsl:apply-templates select="." mode="functionCall">
			<xsl:with-param name="functionCallID" select="$functionCallID" />
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="node[@type='function']" mode="call">
		<xsl:apply-templates select="following-sibling::node[position()=1]" mode="call" />
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat( generate-id(), @id )" />
		</xsl:variable>
		<xsl:variable name="result">
			<xsl:value-of select="output/@var" />
		</xsl:variable>
		<xsl:value-of select="concat($result, ' ')" />
		<xsl:apply-templates select="." mode="functionCall">
			<xsl:with-param name="functionCallID" select="$functionCallID" />
		</xsl:apply-templates>
	</xsl:template>
	<xsl:template match="node[@type='state']" mode="call">
		<xsl:apply-templates select="following-sibling::node[position()=1]" mode="call" />
	</xsl:template>


	<!-- create a function call for diagram nodes -->
	<xsl:template match="node[@type='graph']" mode="call">
		<xsl:apply-templates select="following-sibling::node[position()=1]" mode="call" />
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat(generate-id(),@id)" />
		</xsl:variable>
		<xsl:apply-templates select="output" mode="declareOutputVariables">
			<xsl:with-param name="functionCallID" select="$functionCallID" />
		</xsl:apply-templates>
		<xsl:apply-templates select="." mode="functionCall">
			<xsl:with-param name="functionCallID" select="$functionCallID"/>
		</xsl:apply-templates>
	</xsl:template>

	<!-- ====================== FUNCTION CALLS ===================== -->

	<xsl:template match="node[@type='operator']" mode="functionCall">
		<xsl:apply-templates select="." mode="getOutput" />
		<xsl:value-of select="string(' = ')" />
		<xsl:apply-templates select="input[position()=1]/source" mode="getOutput" />
		<xsl:apply-templates select="input[position()=1]/import" mode="getOutput" />
		<xsl:value-of select="document('./nodes/nodes/operators.xml')/operators/node[@name=@name]/symbol" />
		<xsl:apply-templates select="input[position()=2]/source" mode="getOutput" />
		<xsl:apply-templates select="input[position()=2]/import" mode="getOutput" />
		<xsl:value-of select="string(';&#xA;')" />
	</xsl:template>

	<xsl:template match="node[@type='graph']" mode="functionCall">
		<xsl:param name="functionCallID" />
		<xsl:value-of select="@name" />
		<xsl:value-of select="$functionCallID" />
		<xsl:value-of select="string('(')" />
		<xsl:apply-templates select="output" mode="functionCall">
			<xsl:with-param name="functionCallID" select="$functionCallID" />
		</xsl:apply-templates>
		<xsl:apply-templates select="input" mode="functionCall" />
		<xsl:value-of select="string(');&#xA;')" />
	</xsl:template>

	<xsl:template match="source" mode="functionCall">
		<xsl:value-of select="string(',')" />
		<xsl:apply-templates select="." mode="getOutput" />
	</xsl:template>

	<xsl:template match="output" mode="functionCall">
		<xsl:param name="functionCallID" />
		<xsl:if test="position()!=1">
			<xsl:value-of select="string(',')" />
		</xsl:if>
		<xsl:value-of select="concat( @name, $functionCallID )" />
	</xsl:template>

	<xsl:template match="input" mode="functionCall">
		<xsl:value-of select="string(',')" />
		<xsl:apply-templates select="source" mode="getOutput" />
	</xsl:template>

	<!-- ====================== GET OUTPUTS AND VALUES ===================== -->
	<xsl:template match="source" mode="getOutput">
		<xsl:variable name="node" select="@node" />		
		<xsl:variable name="id" select="@id" />		
		<xsl:apply-templates select="../../../node[@name=$node][@id=$id]" mode="getOutput">
			<xsl:with-param name="slot" select="@slot" />
		</xsl:apply-templates>
		<xsl:apply-templates select="../../../../node[@name=$node][@id=$id]" mode="getOutput">
			<xsl:with-param name="slot" select="@slot" />
		</xsl:apply-templates>
		<xsl:apply-templates select="../../../shader[@name=$node][@id=$id]" mode="getOutput">
			<xsl:with-param name="slot" select="@slot" />
		</xsl:apply-templates>
		<xsl:apply-templates select="../../../../shader[@name=$node][@id=$id]" mode="getOutput">
			<xsl:with-param name="slot" select="@slot" />
		</xsl:apply-templates>

	</xsl:template>
	<!-- lookup the corresponding node to the export and get the output value -->
	<!-- GET OUTPUTS -->
	<!-- get a output value out of a graph -->
	<xsl:template match="node[@type='graph']" mode="getOutput">
		<xsl:param name="slot" />
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat( generate-id(), @id)" />
		</xsl:variable>
		<xsl:apply-templates select="output[@name=$slot]" mode="getOutput">
			<xsl:with-param name="functionCallID" select="$functionCallID"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="input[@name=$slot]" mode="getValue">
			<xsl:with-param name="functionCallID" select="$functionCallID"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="shader" mode="getOutput">
		<xsl:param name="slot" />
		<xsl:apply-templates select="import[@name=$slot]" mode="getOutput"/>
		<xsl:apply-templates select="export[@name=$slot]" mode="getValue"/>
	</xsl:template>

	<xsl:template match="import" mode="getOutput">
		<xsl:value-of select="@name" />
	</xsl:template>
	<xsl:template match="export" mode="getOutput">
		<xsl:value-of select="@name" />
	</xsl:template>
	<!-- get value from a  input slot -->
	<xsl:template match="input" mode="getValue">
		<xsl:value-of select="@name" />
	</xsl:template>

	<!-- get output from a slot -->
	<xsl:template match="output" mode="getOutput">
		<xsl:param name="functionCallID" />
		<xsl:value-of select="concat(@name, $functionCallID)" />
	</xsl:template>

	<!-- get output from a function -->
	<xsl:template match="node[@type='function']" mode="getOutput">
		<xsl:value-of select="concat( @name, generate-id(), @id )" />
	</xsl:template>

	<!-- get output from state variable node -->
	<xsl:template match="node[@type='state']" mode="getOutput">
		<xsl:value-of select="@name" />
	</xsl:template>

	<!-- get output from constant node -->
	<xsl:template match="node[@type='constant']" mode="getOutput">
		<xsl:value-of select="string('getting constant value')" />
	</xsl:template>

	<!-- get output from a operator node -->
	<xsl:template match="node[@type='operator']" mode="getOutput">
		<xsl:variable name="functionCallID">
			<xsl:value-of select="concat( generate-id(), @id )" />
		</xsl:variable>
		<xsl:value-of select="concat( 'op', $functionCallID )" />
	</xsl:template>

	<!-- ====================== EXPORT ===================== -->
	<xsl:template match="output" mode="export">
		<xsl:value-of select="concat(@name,' = ')" />
		<xsl:apply-templates select="source" mode="export" />
		<xsl:value-of select="string(';&#xA;')" />
	</xsl:template>

	<xsl:template match="export" mode="export">
		<xsl:value-of select="concat(@name,' = ')" />
		<xsl:apply-templates select="source" mode="export" />
		<xsl:value-of select="string(';&#xA;')" />
	</xsl:template>


	<xsl:template match="source" mode="export">
		<xsl:variable name="node" select="@node" />
		<xsl:variable name="id" select="@id" />
		<xsl:choose>
			<xsl:when test="../../../node/@name = $node" >
				<xsl:apply-templates select="../../../node[@name=$node][@id=$id]" mode="getOutput">
					<xsl:with-param name="slot" select="@slot"/>
				</xsl:apply-templates>
			</xsl:when>	

			<xsl:when test="../../node/@name = $node" >
				<xsl:apply-templates select="../../node[@name=$node][@id=$id]" mode="getOutput">
					<xsl:with-param name="slot" select="@slot"/>
				</xsl:apply-templates>
			</xsl:when>
			<xsl:apply-templates select="source" mode="getOutput" />
		</xsl:choose>
	</xsl:template>

	<xsl:template match="uniforms">
		<xsl:variable name="type" select="@type"/>
		<xsl:variable name="node" as="string" select="@parent"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:variable name="slot" as="string" select="@name"/>
		<xsl:value-of select="concat('uniform ', $type ,' ',$node, ';&#xA;')"/>
	</xsl:template>

	<xsl:template match="export">
		<xsl:if test="@name!='gl_Position'">
			<xsl:text>out </xsl:text>
			<xsl:apply-templates select="@type"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="node" as="string" select="@parent"/>
			<xsl:variable name="id" as="string" select="@id"/>
			<xsl:variable name="slot" as="string" select="@name"/>
			<xsl:value-of select="concat($node, $id, $slot)"/>
			<xsl:text>;&#xA;</xsl:text>
		</xsl:if>
	</xsl:template>
	<xsl:template match="import">
		<xsl:text>in </xsl:text>
		<xsl:apply-templates select="@type"/>
		<xsl:text> </xsl:text>
		<xsl:variable name="node" as="string" select="@parent"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:variable name="slot" as="string" select="@name"/>
		<xsl:value-of select="concat($node, $id, $slot)"/>
		<xsl:text>;&#xA;</xsl:text>
	</xsl:template>

	<xsl:template match="*">
		<xsl:message terminate="no">
			WARNING: Unmatched element: <xsl:value-of select="name()"/>
		</xsl:message>
		<xsl:apply-templates/>
	</xsl:template>
	<xsl:template match="*|/" mode="m">
		<xsl:value-of select="string('mode match')"/>
		<xsl:apply-templates mode="m"/>
	</xsl:template>
	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
		<xsl:value-of select="string('node match')"/>
	</xsl:template>

</xsl:stylesheet>
