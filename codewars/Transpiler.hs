module Transpiler where

import Data.List (intercalate)
import Data.Maybe (maybeToList)
import Text.Parsec

data AST
    = Sym String
    | Num Integer
    | App AST [AST]
    | Lam [AST] [AST]  -- actually first list is [Sym|Num]

type Parser a = Parsec String () a

opt :: Parser a -> Parser [a]
opt p = maybeToList <$> optionMaybe p

parseKotlin :: String -> Either String AST
parseKotlin s =
  case parse (ws *> mainP <* ws <* eof) "input" s of
    Left err   -> Left "Hugh?" -- (s ++ "      " ++ show err)
    Right ast  -> Right ast
  where
    mainP = appP

    appP = App <$> (exprP <* ws) <*> afterAppP

    afterAppP = choice [ (:[]) <$> lambdaP
                       , (++) <$> (argsP <* ws) <*> opt lambdaP
                       ]

    exprP = atomP <|> lambdaP

    atomP = nameP <|> numberP

    numberP :: Parser AST
    numberP = Num . read <$> many1 (oneOf ['0'..'9'])

    nameP :: Parser AST
    nameP = Sym <$> ((:) <$> symX <*> symXS)

    argsP :: Parser [AST]
    argsP = char '(' *> ws *> (exprP <* ws) `sepBy` (char ',' <* ws) <* char ')'

    lambdaP :: Parser AST
    lambdaP = char '{' *> (Lam <$> paramsP <*> bodyP) <* char '}'

    paramsP :: Parser [AST]
    paramsP = try ((ws *> atomP <* ws) `sepBy1` char ',' <* string "->")
           <|> pure []

    bodyP = ws *> atomP `sepEndBy` ws

    ws   = many (oneOf " \n")
    symX  = letter <|> char '_'
    symXS = many (alphaNum <|> char '_')

formatDart :: AST -> String
formatDart node =
  case node of
    Sym s -> s
    Num x -> show x

    App f args -> formatDart f ++ "(" ++ intercalate "," (map formatDart args) ++ ")"
    
    Lam params body ->
      "("
      ++ intercalate "," (map formatDart params)
      ++ "){"
      ++ concatMap (\e -> formatDart e ++ ";") body
      ++ "}"

transpile :: String -> Either String String
transpile s = formatDart <$> parseKotlin s
