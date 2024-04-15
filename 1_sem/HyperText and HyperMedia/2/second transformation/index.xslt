<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" indent="yes"/>

	<xsl:variable name="authorInfo" select="tennis/author"/>
	<xsl:variable name="pageTitle">Rules of tennis</xsl:variable>
	
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="UTF-8" />
				<title><xsl:value-of select="$pageTitle"/></title>
				<meta name="viewport" content="width=device-width, initial-scale=1.0" />
				<link rel="stylesheet" href="index.css" />
			</head>
			<body>
				<header>
					<h1 style="width: 100%;text-align: center; text-transform: uppercase;"><xsl:value-of select="$pageTitle"/></h1>
				</header>
				<div id="wrapper">
					<xsl:apply-templates select="tennis/rules"/>
				</div>
				<footer>
					<xsl:call-template name="author"/>
				</footer>
			</body>
		</html>
	</xsl:template>

	<xsl:template name="author">
		<xsl:text>Copyright 2023 </xsl:text>
		<xsl:value-of select="$authorInfo/name"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="$authorInfo/surname"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select='format-number($authorInfo/indexNumber, "###,###")' />
	</xsl:template>

	<xsl:template match="rules">
		<xsl:apply-templates select="rule"/>
	</xsl:template>

	<xsl:template match="rule">
		<h3><xsl:number value="@number" format="1. "/><xsl:value-of select="ruleName"/></h3>
		<p><xsl:value-of select="normalize-space(ruleDescription)"/></p>
		<xsl:apply-templates select="ruleSource"/>
	</xsl:template>

	<xsl:template match="ruleSource">
		<a href="{@link}"><xsl:value-of select="."/></a>
	</xsl:template>

</xsl:stylesheet>
