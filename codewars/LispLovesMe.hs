module LispLovesMe where

import Data.Maybe (maybe)
import Data.List (intercalate)
import Text.Parsec

data AST = I32 Int
         | Sym String
         | Nul
         | Err
         | Lst [AST]
         | Boo Bool
         | Nod AST [AST]
         deriving (Eq, Show)

true  = Boo True
false = Boo False

isI32 I32{} = True
isI32 _     = False

i32 (I32 x) = x

type Parser a = Parsec String () a

white, symX, symXS :: Parser Char
white = oneOf  (" ,\n\t\r")
symX  = noneOf (" ,\n\t\r()" ++ [ '0' .. '9' ])
symXS = noneOf (" ,\n\t\r()")

parseLisp :: String -> Either ParseError AST
parseLisp = parse (ws *> mainP <* ws) "input"
  where
    mainP = exprP

    exprP =  i32P
         <|> try nullP
         <|> try trueP
         <|> try falseP
         <|> symP
         <|> nodeP

    nodeP = do
      char '('
      (f:args) <- ws *> many1 (exprP <* ws)
      char ')'
      return (Nod f args)

    i32P = I32 . read <$> many1 (oneOf ['0'..'9'])

    symP = Sym <$> ((:) <$> symX <*> many symXS)

    nullP :: Parser AST
    nullP  = (string "null" <|> emptyP) *> pure Nul
    emptyP = char '(' *> ws *> char ')' *> pure []

    trueP, falseP :: Parser AST
    trueP  = string "true"  *> pure true
    falseP = string "false" *> pure false

    ws :: Parser ()
    ws = many white *> pure ()

eval :: AST -> AST
eval (Nod (Sym fname) args)  = maybe Err ($ fmap eval args) (lookup fname preludeFunctions)
eval (Nod _ _) = Err  -- cannot apply to non-Sym
eval x = x

pretty :: AST -> String
pretty node =
  case node of
    I32 x  -> show x
    Sym s  -> s
    Nul    -> "null"
    Err    -> "ERROR"
    Lst xs -> pretty (Nod (Sym "list") xs)
    Boo b  -> if b then "true" else "false"

    Nod f args -> "(" ++ intercalate " " (fmap pretty $ [f] ++ args) ++ ")"

preludeFunctions :: [(String, [AST] -> AST)]
preludeFunctions =
  [ ("+", evalFoldI32 (+))
  , ("*", evalFoldI32 (*))
  , ("-", evalFoldI32 (-))
  , ("/", evalFoldI32 (div))
  , ("^", evalBinI32 (^))
  , (">", evalBinBoo (>))
  , ("<", evalBinBoo (<))
  , ("!", evalNot)
  , ("list", evalList)
  , ("size", evalSize)
  , ("reverse", evalReverse)
  , ("..", evalRange)
  , ("==", evalBinBoo (==))
  , (">=", evalBinBoo (>=))
  , ("<=", evalBinBoo (<=))
  , ("!=", evalBinBoo (/=))
  , ("if", evalIf)
  ]
  where
    evalFoldI32 op args@(x:xs)
      | all isI32 args = I32 $ foldl op (i32 x) (map i32 xs)
    evalFoldI32 _ _ = Err

    evalBinI32 op [I32 x, I32 y] = I32 (x `op` y)
    evalBinI32 _ _ = Err

    evalBinBoo op [I32 x, I32 y] = Boo (x `op` y)
    evalBinBoo _ _ = Err

    evalNot [Boo True]  = false
    evalNot [Boo False] = true
    evalNot _ = Err

    evalList xs = Lst xs

    evalSize [Lst xs] = I32 (length xs)
    evalSize _ = Err

    evalReverse [Lst xs] = Lst (reverse xs)
    evalReverse _ = Err

    evalRange [I32 a, I32 b] = Lst (fmap I32 [a..b])
    evalRange _ = Err

    evalIf [Boo True,  x] = x
    evalIf [Boo False, _] = Nul
    evalIf [Boo True,  x, _] = x
    evalIf [Boo False, _, y] = y
    evalIf _ = Err


lispPretty :: String -> Maybe String
lispPretty s =
  case parseLisp s of
    Right ast -> Just (pretty ast)
    Left err -> Nothing

lispEval :: String -> Maybe AST
lispEval s =
  case parseLisp s of
    Right ast -> Just (eval ast)
    Left err -> Nothing
