module SimpleInteractiveInterpreter where

import Control.Monad
import Control.Monad.State
import Data.Fixed (mod')
import Data.List ((\\))
import Text.Parsec as P hiding (State)

import qualified Data.Map as M

---

type Name = String

data Expr
  = Lam [Name] Expr
  | App [Expr]
  | Ass Expr Expr
  | Var Name
  | Lit Double
  deriving Show

data Ty
  = FunTy [Ty] Ty
  | RefTy Ty
  | NumTy

-- TODO: replace arity in Func with type-checking

data Value
  = Func Int ([Value] -> Value)
  | Numb Double
  | Erro String

sameType :: Value -> Value -> Bool
sameType Func{} Func{} = True
sameType Numb{} Numb{} = True
sameType _ _ = False

instance Show Value where
  show (Func i _) = "Func{i=" ++ show i ++ "}"
  show (Numb x) = show x
  show (Erro s) = "Erro{" ++ s ++ "}"

---

type Parser a = Parsec String () a

-- TODO: do proper tokenizing to get rid of ugly `spaces[1]`

letters, digits :: [Char]
letters = ['a'..'z'] ++ ['A'..'Z']
digits  = ['0'..'9']

binop :: String -> Parser (Expr -> Expr -> Expr)
binop name =
  let op a b = App [Var name, a, b]
    in symbol name *> pure op

spaces1 :: Parser ()
spaces1 = P.many1 (P.char ' ') *> pure ()

symbol :: String -> Parser ()
symbol s = P.string s *> spaces *> pure ()

parens :: Parser a -> Parser a
parens p = char '(' *> spaces *> p <* char ')'

parseLineOrBlank :: Parser a -> Parser (Maybe a)
parseLineOrBlank p = ((Just <$> p) <|> (pure Nothing <* spaces)) <* P.eof

fromDecimalDigits :: [Char] -> Double
fromDecimalDigits ds = read ds * 10 ^^ (-length ds)

app :: [Expr] -> Expr
app [x] = x
app xs  = App xs

stmtP :: Parser Expr
stmtP = funcP <|> exprP
  where
    funcP = do
      -- the `try` is ugly but necessary. proper tokenizing would get rid of it
      P.try (P.string "fn" <* spaces1)
      name <- identifierP <* spaces1
      args <- P.many (identifierP <* spaces)
      P.string "=>" <* spaces
      body <- exprP
      pure $ Ass (Var name) $ Lam args body
    
    exprP  = valueP  `P.chainr1` assOP
    valueP = termP   `P.chainl1` addOP
    termP  = factorP `P.chainl1` mulOP
    
    factorP = app <$> P.sepEndBy1 atomP spaces1
    
    atomP = parens exprP
        <|> litP
        <|> varP
    
    litP = Lit <$> numberP

    varP = Var <$> identifierP

    ---
    
    assOP = symbol "=" *> pure Ass
    
    addOP = binop "+"
        <|> binop "-"
    
    mulOP = binop "*"
        <|> binop "/"
        <|> binop "%"
    
    ---

    identifierP = (:) <$> identFirstP <*> identRestP
    
    identFirstP = P.oneOf ("_" ++ letters)

    identRestP = P.many $ P.oneOf ("_" ++ letters ++ digits)

    ---
    
    numberP = (+) <$> numberWholeP <*> numberDecimalP
    
    numberWholeP = read <$> P.many1 (P.oneOf digits)
    
    numberDecimalP = P.option 0 $ do
      char '.'
      fromDecimalDigits <$> P.many1 (P.oneOf digits)

---

type Context = M.Map Name Value

type Eval a = State Context a

-- TODO: replace `Erro` value with ExceptT monad

freeVars :: Expr -> [Name]
freeVars (App es) = concatMap freeVars es
freeVars (Ass a b) = freeVars a ++ freeVars b
freeVars (Var n) = [n]
freeVars (Lit x) = []
freeVars (Lam ns body) = freeVars body \\ ns

makeFunc :: [Name] -> Expr -> Context -> Value
makeFunc ns body ctx = Func (length ns) run
  where
    run params =
      let paramsBinds = M.fromList $ zip ns params
          ctx' = M.union paramsBinds ctx
        in evalState (eval body) ctx'

readVar :: Name -> Eval Value
readVar name = do
  ctx <- get
  case M.lookup name ctx of
    Nothing -> pure $ Erro $ "name not found: " ++ name
    -- invoke nullary function 'implicitly':
    Just (Func 0 f) -> pure (f [])
    Just v  -> pure v

writeVar :: Name -> Value -> Eval Value
writeVar name e@Erro{} = pure e
writeVar name v = do
  ok <- sameType v <$> gets (M.findWithDefault v name)
  if ok
    then modify (M.insert name v) *> pure v
    else pure $ Erro $ "assignment changes type"

contextVars :: Eval [Name]
contextVars = gets M.keys

eval :: Expr -> Eval Value
eval (Lit x) = pure $ Numb x
eval (Var n) = readVar n
eval (Lam ns body) = do
  let known = ns ++ stdlibVars
  let unknown = freeVars body \\ known
  if null unknown
    then makeFunc ns body <$> get
    else pure $ Erro $ "lam unknowns" ++ show unknown
eval (Ass a b) =
  case a of
    Var n -> writeVar n =<< eval b
    _     -> pure $ Erro $ "assigning to non-Var"
eval (App es) = go [] $ reverse es
  where
    go [v] [] = pure $ v
    go vs  [] = pure $ Erro $ "bad application"
    go ps (x:xs) = do
      v <- eval x
      case v of
        Func i f ->
          if i > length ps
            then pure $ Erro $ "ArityError"
            else go (f (take i ps) : drop i ps) xs
        _ -> go (v:ps) xs

---

type Result = Maybe Double

data Interpreter = I Context

stdlib :: Context
stdlib = M.fromList
  [ numbin "+" (+)
  , numbin "-" (-)
  , numbin "*" (*)
  , numbin "/" (/)
  , numbin "%" (mod')
  ]
  where
    numbin name f = (name, Func 2 wrapped)
      where
        wrapped [Numb x, Numb y] = Numb (f x y)
        wrapped _ = Erro $ "bad args for: " ++ name

stdlibVars :: [String]
stdlibVars = M.keys stdlib

newInterpreter :: Interpreter
newInterpreter = I stdlib

debugREPL :: IO ()
debugREPL = go stdlib
  where
    go ctx = do
      print ctx
      src <- getLine
      case parse stmtP "<stdin>" src of
        Left  err  -> print err *> go ctx
        Right stmt -> do
          print stmt
          let (val, ctx') = runState (eval stmt) ctx
          print val
          go ctx'

input :: String -> Interpreter -> Either String (Result, Interpreter)
input src (I ctx) =
  case parse (parseLineOrBlank stmtP) "<stdin>" src of
    Left  err  -> Left (show err)
    Right Nothing -> Right (Nothing, I ctx)
    Right (Just stmt) ->
      let (val, ctx') = runState (eval stmt) ctx in
        case val of
          Func{} -> Right (Nothing, I ctx')
          Numb x -> Right (Just x, I ctx')
          Erro s -> Left s
