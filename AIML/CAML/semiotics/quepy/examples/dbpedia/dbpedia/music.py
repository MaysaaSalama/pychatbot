#!/usr/bin/env python
# coding: utf-8

# Copyright (c) 2012, Machinalis S.R.L.
# This file is part of quepy and is distributed under the Modified BSD License.
# You should have received a copy of license in the LICENSE file.
#
# Authors: Rafael Carrascosa <rcarrascosa@machinalis.com>
#          Gonzalo Garcia Berrotaran <ggarcia@machinalis.com>

"""
Music related regex
"""

from refo import Plus, Question
from quepy.semantics import HasKeyword
from quepy.regex import Lemma, Lemmas, Pos, RegexTemplate, Particle
from AIML.CAML.semiotics.quepy.examples.dbpedia.dbpedia.semantics import IsBand, LabelOf, IsMemberOf, ActiveYears, \
                      MusicGenereOf, NameOf, IsAlbum, ProducedBy


class Band(Particle):
    regex = Question(Pos("DT")) + Plus(Pos("NN") | Pos("NNP"))

    def semantics(self, match):
        name = match.words.tokens.title()
        return IsBand() + HasKeyword(name)


class BandMembersRegex(RegexTemplate):
    """
    Regex for questions about band member.
    Ex: "Radiohead members"
        "What are the members of Metallica?"
    """

    regex1 = Band() + Lemma("member")
    regex2 = Lemma("member") + Pos("IN") + Band()
    regex3 = Pos("WP") + Lemma("be") + Pos("DT") + Lemma("member") + \
        Pos("IN") + Band()

    regex = (regex1 | regex2 | regex3) + Question(Pos("."))

    def semantics(self, match):
        member = IsMemberOf(match.band)
        label = LabelOf(member)
        return label, "enum"


class FoundationRegex(RegexTemplate):
    """
    Regex for questions about the creation of a band.
    Ex: "When was Pink Floyd founded?"
        "When was Korn formed?"
    """

    regex = Pos("WRB") + Lemma("be") + Band() + \
        (Lemma("form") | Lemma("found")) + Question(Pos("."))

    def semantics(self, match):
        active_years = ActiveYears(match.band)
        return active_years, "literal"


class GenreRegex(RegexTemplate):
    """
    Regex for questions about the genre of a band.
    Ex: "What is the music genre of Gorillaz?"
        "Music genre of Radiohead"
    """

    optional_opening = Question(Pos("WP") + Lemma("be") + Pos("DT"))
    regex = optional_opening + Question(Lemma("music")) + Lemma("genre") + \
        Pos("IN") + Band() + Question(Pos("."))

    def semantics(self, match):
        genere = MusicGenereOf(match.band)
        label = LabelOf(genere)
        return label, "enum"


class AlbumsOfRegex(RegexTemplate):
    """
    Ex: "List albums of Pink Floyd"
        "What albums did Pearl Jam record?"
        "Albums by Metallica"
    """

    regex = (Question(Lemma("list")) + (Lemma("album") | Lemma("albums")) + \
             Pos("IN") + Band()) | \
            (Lemmas("what album do") + Band() +
             (Lemma("record") | Lemma("make")) + Question(Pos("."))) | \
            (Lemma("list") + Band() + Lemma("album"))

    def semantics(self, match):
        album = IsAlbum() + ProducedBy(match.band)
        name = NameOf(album)
        return name, "enum"
