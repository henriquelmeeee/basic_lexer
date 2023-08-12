#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>

#include <vector>

#define cout std::cout
#define cin std::cin
#define endl '\n'

bool isNum(char ch) {
  if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
    return true; // =P lazy function xd
  return false;
}

enum SyntaxKind {
  Number,
  Plus,
  Minus,
  Times,
  Divide,
  Main,
};

class SyntaxToken {
  public:
    SyntaxToken* child;
    SyntaxToken* parent;
    SyntaxKind kind;
    int value;

    SyntaxToken(SyntaxKind _kind, int _value) : child(nullptr), parent(nullptr), kind(_kind), value(_value) {
      kind = _kind;
      value = _value;
    }

    bool SetChild(SyntaxToken* _child) {
      child = _child;
      child->parent = this;
      return true;
    }
    
};

class Lexer {
  public:

    const char* exp;
    SyntaxToken* actual_token;
    int position;

    Lexer(const char* _exp) {
      this->exp = _exp;
      this->position = 0;
      actual_token = new SyntaxToken(SyntaxKind::Main, 0);
    }

    bool Next() {
      position++;
      if(exp[position] == '\0')
        return false;
      cout << "Next()" << endl;
      return true;
    }

    char Current() {
      return exp[position];
    }

    bool NextToken() {
      switch(Current()) {
        case '+':
          {
            actual_token->SetChild(new SyntaxToken(SyntaxKind::Plus, 0));
            Next();
            return true;
          };
        case '-':
          {
            actual_token->SetChild(new SyntaxToken(SyntaxKind::Minus, 0));
            Next();
            return true;
          };
        case '*':
          {
            actual_token->SetChild(new SyntaxToken(SyntaxKind::Times, 0));
            Next();
            return true;
          };
        case '/':
          {
            actual_token->SetChild(new SyntaxToken(SyntaxKind::Divide, 0));
            Next();
            return true;
          };
        default:
          break;
      }

      if(Current() == '\0')
        return false;

      char val_buf[32];
      int val_bufi=0;
    
      std::memset(val_buf, 0, sizeof(val_buf));

      while(isNum(Current())) {
        val_buf[val_bufi] = Current();
        val_bufi++;
        Next();
      }
      val_buf[val_bufi] = '\0';
      SyntaxToken* newToken = new SyntaxToken(SyntaxKind::Number, std::atoi(val_buf));
      actual_token->SetChild(newToken);
      actual_token = newToken;

      return true;

    }
};

int main() {
  Lexer lex("1+2");
  while(lex.NextToken()) {
    cout << "Next Token" << endl;
  }
}
