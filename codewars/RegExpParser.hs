module RegExpParser
       ( RegExp(..)
       , parseRegExp
       ) where

import qualified Text.Parsec as P

data RegExp = Normal Char       -- ^ A character that is not in "()*|."
            | Any               -- ^ Any charater
            | ZeroOrMore RegExp -- ^ Zero or more occurances of the same regexp
            | Or RegExp RegExp  -- ^ A choice between 2 regexps
            | Str [RegExp]      -- ^ A sequence of regexps.
  deriving (Show, Eq)

type Parser a = P.Parsec String () a

specials = "()*|."

regexp :: Parser RegExp
regexp = reg <* P.eof
  where
    reg = do
      x <- str
      P.option x (pipe x)
    
    pipe x = do
      P.char '|'
      y <- str
      return (Or x y)
    
    str = do
      xs <- P.many1 item
      case xs of
        [x] -> pure x
        xs  -> pure (Str xs)
    
    item = do
      x <- atom
      starred <- P.optionMaybe (P.char '*')
      case starred of
        Nothing   -> pure x
        otherwise -> pure (ZeroOrMore x)
    
    atom = P.choice
      [ parens
      , letter
      , dot
      ]
    
    parens =
      P.char '(' *> reg <* P.char ')'
    
    letter =
      Normal <$> P.noneOf specials
    
    dot =
      P.char '.' *> pure Any

parseRegExp :: String -> Maybe RegExp
parseRegExp s =
  case P.parse regexp "" s of
    Left  _ -> Nothing
    Right r -> Just r
