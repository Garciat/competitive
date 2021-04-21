-- https://www.codewars.com/kata/584daf7215ac503d5a0001ae/haskell
module Symbolic where

data Expr
  = Var -- x
  | Lit Double
  | BinOp BinOp Expr Expr
  | UnaOp UnaOp Expr
  deriving (Show, Eq)

data BinOp
  = Add
  | Sub
  | Mul
  | Div
  | Pow
  deriving (Show, Eq)

isCommut :: BinOp -> Bool
isCommut Add = True
isCommut Mul = True
isCommut _ = False

isAssoc :: BinOp -> Bool
isAssoc Add = True
isAssoc Mul = True
isAssoc _ = False

runBinOp :: BinOp -> Double -> Double -> Double
runBinOp Add = (+)
runBinOp Sub = (-)
runBinOp Mul = (*)
runBinOp Div = (/)
runBinOp Pow = (**)

data UnaOp
  = Cos
  | Sin
  | Tan
  | Exp
  | Log -- ln
  deriving (Show, Eq)

simp :: Expr -> Expr
simp Var = Var
simp (Lit n) = Lit n
--
simp (BinOp Add (Lit 0) x) = simp x
simp (BinOp Add x (Lit 0)) = simp x
--
simp (BinOp Sub x (Lit 0)) = simp x
--
simp (BinOp Mul (Lit 1) x) = simp x
simp (BinOp Mul x (Lit 1)) = simp x
simp (BinOp Mul (Lit 0) x) = Lit 0
simp (BinOp Mul x (Lit 0)) = Lit 0
--
simp (BinOp Div x (Lit 1)) = simp x
--
simp (BinOp Pow x (Lit 0)) = Lit 1
simp (BinOp Pow x (Lit 1)) = simp x
--
simp (BinOp op (Lit n) (BinOp op' (Lit m) x))
  | op == op' && isAssoc op = simp (BinOp op (Lit (runBinOp op n m)) x)
--
simp (BinOp op (Lit n) x) =
  case simp x of
    Lit m -> Lit (runBinOp op n m)
    x'    -> BinOp op (Lit n) x'
simp (BinOp op x (Lit m)) | isCommut op = simp (BinOp op (Lit m) x)
simp (BinOp op x (Lit m)) =
  case simp x of
    Lit n -> Lit (runBinOp op n m)
    x'    -> BinOp op x' (Lit m)
--
simp (BinOp op x y) = simp (BinOp op (simp x) (simp y))
--
simp x = x

dd :: Expr -> Expr
dd Var = Lit 1
dd (Lit _) = Lit 0
-- d(x + y) = dx + dy
dd (BinOp Add x y) = BinOp Add (dd x) (dd y)
-- d(x - y) = dx - dy
dd (BinOp Sub x y) = BinOp Sub (dd x) (dd y)
-- d(x * y) = x * dy + y * dx
dd (BinOp Mul x y) = BinOp Add (BinOp Mul (dd x) y) (BinOp Mul x (dd y))
-- d(d / y) = (x * dy - y * dx) / (y^2)
dd (BinOp Div x y) = BinOp Div (BinOp Sub (BinOp Mul (dd x) y) (BinOp Mul x (dd y))) (BinOp Pow y (Lit 2))
-- d(x ^ n) = n * x ^ (n - 1) * dx
dd (BinOp Pow x (Lit n)) = BinOp Mul (BinOp Mul (Lit n) (BinOp Pow x (Lit (n-1)))) (dd x)
-- d(f(x)) = f'(x) * dx
dd (UnaOp Cos x) = BinOp Mul (BinOp Mul (Lit (-1)) (UnaOp Sin x)) (dd x)
dd (UnaOp Sin x) = BinOp Mul (UnaOp Cos x) (dd x)
dd (UnaOp Tan x) = BinOp Mul (BinOp Add (Lit 1) (BinOp Pow (UnaOp Tan x) (Lit 2))) (dd x)
dd (UnaOp Exp x) = BinOp Mul (UnaOp Exp x) (dd x)
dd (UnaOp Log x) = BinOp Mul (BinOp Div (Lit 1) x) (dd x)
--

data Token
  = LParen
  | RParen
  | TSym String
  | TNum Double
  deriving (Show, Eq)

isSymChar :: Char -> Bool
isSymChar c = c `elem` (['a'..'z'] ++ "+-*/^")

tokens :: String -> [Token]
tokens [] = []
tokens cs =
  case cs of
    ' ':cs' -> tokens cs'
    '(':cs' -> LParen : tokens cs'
    ')':cs' -> RParen : tokens cs'
    _       ->
      case reads cs of
        [(n, cs')] -> TNum n : tokens cs'
        _ ->
          let (sym, cs') = span isSymChar cs
            in TSym sym : tokens cs'

type Parser a = [Token] -> Maybe (a, [Token])

andThen :: Parser a -> (a -> Parser b) -> Parser b
andThen pa fpb ts =
  case pa ts of
    Just (a, ts') -> fpb a ts'
    Nothing      -> Nothing

(<|>) :: Parser a -> Parser a -> Parser a
(<|>) first second ts =
  case first ts of
    Just res -> Just res
    Nothing  -> second ts

trivial :: a -> Parser a
trivial a ts = Just (a, ts)

token :: Token -> a -> Parser a
token target out ts =
  case ts of
    t:ts' | t == target -> Just (out, ts')
    _                   -> Nothing

sym :: String -> a -> Parser a
sym s = token (TSym s)

lit ts =
  case ts of
    TNum n : ts' -> Just (Lit n, ts')
    _            -> Nothing
var = sym "x" Var
lparen = token LParen ()
rparen = token RParen ()
binop =
  sym "+" (BinOp Add)
  <|> sym "-" (BinOp Sub)
  <|> sym "*" (BinOp Mul)
  <|> sym "/" (BinOp Div)
  <|> sym "^" (BinOp Pow)

unaop =
  sym "cos" (UnaOp Cos)
  <|> sym "sin" (UnaOp Sin)
  <|> sym "tan" (UnaOp Tan)
  <|> sym "exp" (UnaOp Exp)
  <|> sym "ln"  (UnaOp Log)

nested =
  (binop `andThen` \op -> expr `andThen` \x -> expr `andThen` \y -> trivial (op x y))
  <|> (unaop `andThen` \op -> expr `andThen` \x -> trivial (op x))

expr =
  var
  <|> lit
  <|> (lparen `andThen` \_ -> nested `andThen` \x -> rparen `andThen` \_ -> trivial x)

parse :: [Token] -> Expr
parse ts =
  case expr ts of
    Just (x, []) -> x
    Just (x, xx) -> error (show xx)
    _      -> error "sadness"

pretty :: Expr -> String
pretty Var = "x"
pretty (Lit n) =
  if n == fromIntegral (truncate n)
    then show (truncate n)
    else show n
pretty (BinOp Add x y) = "(+ " ++ pretty x ++ " " ++ pretty y ++ ")"
pretty (BinOp Sub x y) = "(- " ++ pretty x ++ " " ++ pretty y ++ ")"
pretty (BinOp Mul x y) = "(* " ++ pretty x ++ " " ++ pretty y ++ ")"
pretty (BinOp Div x y) = "(/ " ++ pretty x ++ " " ++ pretty y ++ ")"
pretty (BinOp Pow x y) = "(^ " ++ pretty x ++ " " ++ pretty y ++ ")"
pretty (UnaOp Cos x)  = "(cos " ++ pretty x ++ ")"
pretty (UnaOp Sin x)  = "(sin " ++ pretty x ++ ")"
pretty (UnaOp Tan x)  = "(tan " ++ pretty x ++ ")"
pretty (UnaOp Exp x)  = "(exp " ++ pretty x ++ ")"
pretty (UnaOp Log x)  = "(ln " ++ pretty x ++ ")"

diff :: String -> String
diff = pretty . simp . dd . parse . tokens
