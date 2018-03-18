module ApplicativeParser where

import Data.Char
import Prelude hiding (fmap)

-- | An ambiguous parser.
newtype Parser a = P { unP :: String -> [(String, a)] }

msnd :: (b -> c) -> (a, b) -> (a, c)
msnd f (x, y) = (x, f y)

-- | Change the result of a parser.
pmap :: (a -> b) -> Parser a -> Parser b
pmap f p = P (\s -> map (msnd f) (unP p s))

-- | Operator version of 'pmap'.
(<#>) :: (a -> b) -> Parser a -> Parser b
(<#>) = pmap

-- | Parse a value and replace it.
(<#) :: a -> Parser b -> Parser a
(<#) = \x -> pmap (const x)

infixl 4 <#>
infixl 4 <#

-- | Parse a character only when a predicate matches.
predP :: (Char -> Bool) -> Parser Char
predP p = P go
  where
    go [] = []
    go (c:cs)
      | p c       = [(cs, c)]
      | otherwise = []

-- | Succeed only when parsing the given character.
charP :: Char -> Parser Char
charP c = predP (c ==)

-- | Inject a value into an identity parser.
inject :: a -> Parser a
inject x = P (\s -> [(s, x)])

-- | Given a parser with a function value and another parser, parse the function
-- first and then the value, return a parser which applies the function to the
-- value.
(<@>) :: Parser (a -> b) -> Parser a -> Parser b
pf <@> px = P go
  where
    go s = concatMap sub (unP pf s)
    sub (s', f) = unP (pmap (f $) px) s'

(<@) :: Parser a -> Parser b -> Parser a
pa <@ pb = pmap const pa <@> pb

(@>) :: Parser a -> Parser b -> Parser b
pa @> pb = pmap (flip const) pa <@> pb

infixl 4 <@
infixl 4 @>
infixl 4 <@>

-- | Parse a whole string.
stringP :: String -> Parser String
stringP []     = inject []
stringP (c:cs) = (:) <#> charP c <@> stringP cs

-- | Construct a parser that never parses anything.
emptyP :: Parser a
emptyP = P (\_ -> [])

-- | Combine two parsers: When given an input, provide the results of both parser run on the input.
(<<>>) :: Parser a -> Parser a -> Parser a
pa <<>> pb = P (\s -> unP pa s ++ unP pb s)

infixl 3 <<>>

-- | Apply the parser zero or more times.
many :: Parser a -> Parser [a]
many p = (:) <#> p <@> many p <<>> inject []

-- | Apply the parser one or more times.
some :: Parser a -> Parser [a]
some p = (:) <#> p <@> many p

-- | Apply a parser and return all ambiguous results, but only those where the input was fully consumed.
runParser :: Parser a -> String -> [a]
runParser p cs = map snd $ filter (null . fst) (unP p cs)

-- | Apply a parser and only return a result, if there was only one unambiguous result with output fully consumed.
runParserUnique :: Parser a -> String -> Maybe a
runParserUnique p cs =
  case runParser p cs of
    [x]       -> Just x
    otherwise -> Nothing

-- | Kinds of binary operators.
data BinOp = AddBO | MulBO deriving (Eq, Show)

-- | Some kind of arithmetic expression.
data Expr = ConstE Int
          | BinOpE BinOp Expr Expr
          | NegE Expr
          | ZeroE
          deriving (Eq, Show)

binOp :: BinOp -> (Int -> Int -> Int)
binOp AddBO = (+)
binOp MulBO = (*)

evalExpr :: Expr -> Int
evalExpr e =
  case e of
    ConstE x          -> x
    NegE sub          -> negate (evalExpr sub)
    ZeroE             -> 0
    BinOpE op lhs rhs -> binOp op (evalExpr lhs) (evalExpr rhs)

-- | Parse arithmetic expressions, with the following grammar:
--
--     expr         ::= const | binOpExpr | neg | zero
--     const        ::= int
--     binOpExpr    ::= '(' expr ' ' binOp ' ' expr ')'
--     binOp        ::= '+' | '*'
--     neg          ::= '-' expr
--     zero         ::= 'z'
-- 
parseExpr :: String -> Maybe Expr
parseExpr = runParserUnique exprP
  where
    exprP = constP <<>> binOpExprP <<>> negP <<>> zeroP

    constP = ConstE . read <#> some (anyOfP "0123456789")

    binOpExprP = bin <#> (charP '(' @> exprP)
                     <@> (charP ' ' @> binOpP)
                     <@> (charP ' ' @> exprP)
                     <@   charP ')'
    
    binOpP = (charP '+' @> inject AddBO) <<>> (charP '*' @> inject MulBO)

    negP = charP '-' @> (NegE <#> exprP)

    zeroP = charP 'z' @> inject ZeroE

    bin lhs op rhs = BinOpE op lhs rhs

    anyOfP cs = predP (`elem` cs)
