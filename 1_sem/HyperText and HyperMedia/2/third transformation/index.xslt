<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" indent="yes"/>
	
	<xsl:template match="/">
		<xsl:element name="tennis">
			<xsl:element name="creator">
				<xsl:apply-templates select="tennis/author"/>
			</xsl:element>
			<xsl:apply-templates select="tennis/players"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="author">
		<xsl:element name="{name}">
			<xsl:text>Name</xsl:text>
		</xsl:element>
		<xsl:element name="{surname}">
			<xsl:text>Surname</xsl:text>
		</xsl:element>
		<xsl:copy-of select="indexNumber"/>
	</xsl:template>

	<xsl:template match="//players">
		<xsl:copy>
			<xsl:attribute name="count"><xsl:value-of select="count(player)"/></xsl:attribute>
			<xsl:apply-templates select="player"/>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="player">
		<xsl:element name="{@sex}">
			<xsl:attribute name="{playerData/hand}"><xsl:text>true</xsl:text></xsl:attribute>
			<xsl:element name="firstName">
				<xsl:value-of select="playerData/name"/>
			</xsl:element>
			<xsl:element name="lastName">
				<xsl:value-of select="playerData/surname"/>
			</xsl:element>
			<xsl:element name="nationality">
				<xsl:value-of select="playerData/country"/>
			</xsl:element>
			<xsl:element name="data">
				<xsl:element name="age">
					<xsl:value-of select="playerData/age"/>
				</xsl:element>
				<xsl:element name="height">
					<xsl:value-of select="playerData/height"/>
				</xsl:element>
				<xsl:element name="careerStart">
					<xsl:value-of select="playerData/turnedPro"/>
				</xsl:element>
			</xsl:element>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>
