<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" indent="yes"/>

	<xsl:variable name="authorInfo" select="tennis/author"/>
	<xsl:variable name="pageTitle">XSLT project, Name Surname</xsl:variable>
	<xsl:variable name="options">
		<ul>
			<li class="menu-option"><a href="#author">About me</a></li>
			<li class="menu-option"><a href="#definitionOfTenis">What is tennis?</a></li>
			<li class="menu-option"><a href="historyOfTenis">Brief history of tennis</a></li>
			<li class="menu-option"><a href="#rules">Rules</a></li>
			<li class="menu-option"><a href="#players">Players</a></li>
			<li class="menu-option"><a href="#gallery">Gallery</a></li>
		</ul>
	</xsl:variable>
	
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
					<h1><xsl:value-of select="$pageTitle"/></h1>
                    <xsl:call-template name="menu"/>
				</header>
				<div id="wrapper">
                    <xsl:apply-templates select="tennis/information"/>
					<xsl:apply-templates select="tennis/rules"/>

					<section id="players">
						<h2>Players</h2>
						<xsl:apply-templates select="tennis/players"/>
					</section>

					<xsl:apply-templates select="tennis/gallery"/>

					<h2>Quiz</h2>
					<form>
						<xsl:apply-templates select="tennis/quiz/question"/>
						<button type="submit">Submit</button>
						<button type="reset">Reset</button>
					</form>
				</div>
				<footer>
					<xsl:call-template name="author"/>
				</footer>
			</body>
		</html>

	</xsl:template>

	<xsl:template name="menu">
		<nav>
			<xsl:copy-of select="$options" />
		</nav>
	</xsl:template>

	<xsl:template name="author">
		<xsl:text>Copyright 2023 </xsl:text>
		<xsl:value-of select="$authorInfo/name"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="$authorInfo/surname"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select='format-number($authorInfo/indexNumber, "###,###")' />
	</xsl:template>

    <xsl:template match="//information">
        <section id="info">
            <xsl:for-each select="text">
				<xsl:sort select="@about"/>
                <article id="{@about}">
                    <h2><xsl:number value="position()" format="1. "/>Text about <xsl:apply-templates select="@about"/></h2>
                    <xsl:apply-templates select="."/>
                </article>
            </xsl:for-each>
        </section>
    </xsl:template>

	<xsl:template match="//text">
            <p><xsl:value-of select="description"/></p>
            <xsl:apply-templates select="image"/>
            <xsl:apply-templates select="link"/>
	</xsl:template>

	<xsl:template match="image">
		<img src="{@file}" alt="{.}"/>
	</xsl:template>

	<xsl:template match="ruleSource">
		<a href ="{@link}" target="_BLANK"><xsl:value-of select="current()/."/></a><br/>
	</xsl:template>

	<xsl:template match="rules">
		<h2 id="rules">Rules</h2>
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
	
	<xsl:template match="tennis/players">
		<h3>We have information about <xsl:value-of select="count(//player)"/> 
		<xsl:choose>
			<xsl:when test="count(//player) &gt; 1">
				players
			</xsl:when>
			<xsl:otherwise>
				player
			</xsl:otherwise>
		</xsl:choose>
		</h3>
		<table>
			<tr>
				<th>Player</th>
				<th>Sex</th>
				<th>Country</th>
				<th>Age</th>
				<th>Height</th>
			</tr>
			<xsl:apply-templates select="player"/>
		</table>
	</xsl:template>

	<xsl:template match="@about">
		<xsl:if test=".='definitionOfTenis'">
			<xsl:text>definition of tennis</xsl:text>
		</xsl:if>
		<xsl:if test=".='historyOfTenis'">
			<xsl:text>history of tennis</xsl:text>
		</xsl:if>
		<xsl:if test=".='author'">
			<xsl:value-of select="."/>
		</xsl:if>
    </xsl:template>

	<xsl:template match="player">
		<tr class="player-entry">
			<td><xsl:value-of select="playerData/name"/><xsl:text> </xsl:text><xsl:value-of select="playerData/surname"/></td>
			<td>
			<xsl:choose>
				<xsl:when test="@sex='female'">
					<xsl:text>Female</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:text>Male</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
			</td>
			<td><xsl:value-of select="playerData/country"/></td>
			<td><xsl:value-of select="playerData/age"/></td>
			<td><xsl:value-of select="format-number(playerData/height, '#.#')"/><xsl:text>m</xsl:text></td>
		</tr>
	</xsl:template>

	<xsl:template match="tennis/gallery">
		<div id="gallery">
		<xsl:for-each select="image">
			<div class="gallery-image">
				<xsl:apply-templates select="."/>
				<xsl:if test="@source='https://pixabay.com'">
					<a href="{@source}"><xsl:value-of select="."/> - free stock image</a>
				</xsl:if>
				<xsl:if test="@source='https://google.com'">
					<a href="{@source}"><xsl:value-of select="."/> - <xsl:value-of select="@source"/></a>
				</xsl:if>
			</div>
		</xsl:for-each>
		</div>
	</xsl:template>

	<xsl:template match="tennis/quiz/question">
		<xsl:choose>
			<xsl:when test="@type='single'">
				<fieldset>
					<legend><xsl:value-of select="questionText"/></legend>
					<xsl:apply-templates select="answersBank/answer"/>
            </fieldset>
			</xsl:when>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="//question[@type='single']/answersBank/answer">
		<input type="radio" id="{.}" name="playersAmount" value="{.}" />
		<label for="{.}"><xsl:value-of select="."/></label>
	</xsl:template>

</xsl:stylesheet>
