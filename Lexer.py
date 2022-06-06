# -*- coding:utf-8 -*-
import traceback

from global_veriable import *


class Lexer:

    def __init__(self):
        self.words = {}
        self.peek = ' '
        self.line = 1
        self.reserve(Word("if", IF))
        self.reserve(Word("else", ELSE))
        self.reserve(Word("while", WHILE))
        self.reserve(Word("do", DO))
        self.reserve(Word("break", BREAK))
        self.reserve(true)
        self.reserve(false)
        self.reserve(Type.Int)
        self.reserve(Type.Char)
        self.reserve(Type.Bool)
        self.reserve(Type.Float)

    def reserve(self, w):
        self.words[w.lexeme] = w

    def readch(self):
        try:
            self.peek = input(">")
        except IOError:
            print(traceback.format_exc())

    def _readch(self, c):
        self.readch()
        if self.peek != c:
            return false
        self.peek = ' '
        return true

    def scan(self):
        """

        :return:
        """
        while self.readch():
            if self.peek == ' ' or self.peek == '\t':
                continue
            elif self.peek == '\n':
                self.line += 1
            else:
                break

        if self.peek == '&':
            if self._readch('&'):
                return _and_
            else:
                return Token('&')
        elif self.peek == "|":
            if self._readch('|'):
                return _or_
            else:
                return Token('|')
        elif self.peek == "=":
            if self._readch('='):
                return eq
            else:
                return Token('=')
        elif self.peek == "!":
            if self._readch('='):
                return ne
            else:
                return Token('!')
        elif self.peek == "<":
            if self._readch('='):
                return le
            else:
                return Token('<')
        elif self.peek == ">":
            if self._readch('='):
                return ge
            else:
                return Token('>')


class Token:
    def __init__(self, t):
        self.tag = t

    def tostring(self):
        return self.tag


class Num(Token):

    def __init__(self, v):
        super().__init__(NUM)
        self.value = v

    def tostring(self):
        return self.value


class Word(Token):
    """
    用于管理保留字，标识符和像&&这样的符合词法单元的词素，也可以用来管理在中间代码中运算符的书写形式，
    比如单目减号
    """
    def __init__(self, s, tag):
        super().__init__(tag)
        self.lexeme = s

    def tostring(self):
        return self.lexeme


class Real(Token):
    """
    处理浮点数
    """
    def __init__(self, v):
        super().__init__(REAL)
        self.value = v

    def tostring(self):
        return self.value


_and_ = Word("&&", AND)
_or_ = Word("||", OR)
eq = Word("==", EQ)
ne = Word("!=", NE)
le = Word("<=", LE)
ge = Word(">=", GE)
minus = Word("minus", MINUS)
true = Word("true", TRUE)
false = Word("false", FALSE)
temp = Word("t", TEMP)