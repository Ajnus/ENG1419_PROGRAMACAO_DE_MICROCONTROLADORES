from json import load
from turtle import *


# Copie as funções que você fez na Implementação aqui embaixo
def desenha_retangulo(x, y, comprimento, altura, cor):
    #posiciona
    setheading(0)
    penup()
    goto(x,y)
    pendown()
    #colore
    fillcolor(cor)
    begin_fill()
    
    #for i in range(1,2):
    forward(comprimento)
    right(90)
    forward(altura)
    right(90)
    forward(comprimento)
    right(90)
    forward(altura)
        
    end_fill()
    
    return
    
    
def desenha_circulo(x, y, raio, cor):
    #posiciona
    setheading(0)
    penup()
    goto(x,y-raio)
    pendown()
    #colore
    fillcolor(cor)
    begin_fill()
    #desenhacirculo
    circle(raio)
    
    end_fill()
    
    return
    
    
def desenha_poligono(lista_pontos, cor):
    #posiciona
    penup()
    goto(lista_pontos[0]["x"], lista_pontos[0]["y"])
    pendown()
    #colore
    fillcolor(cor)
    begin_fill()
    #pecorre pontos
    for i in range(1, len(lista_pontos)):
        goto(lista_pontos[i]["x"], lista_pontos[i]["y"])
    #volta ao ponto inicial
    goto(lista_pontos[0]["x"], lista_pontos[0]["y"])
    end_fill()
    
    return
    


# Faça a primeira parte do Aperfeiçoamento aqui

def desenha_bandeira(dicionario_do_pais):
    
    for elemento in dicionario_do_pais["elementos"]:
        if elemento["tipo"] == "retângulo":
            desenha_retangulo(elemento["x"], elemento["y"], elemento["comprimento"], elemento["altura"], elemento["cor"])
        if elemento["tipo"] == "polígono":
            desenha_poligono(elemento["pontos"], elemento["cor"])
        if elemento["tipo"] == "círculo":
            desenha_circulo(elemento["x"], elemento["y"], elemento["raio"], elemento["cor"])
    
    penup()
    goto(0, 200)

    return



lista_de_paises = load(open('paises.json', encoding="UTF-8"))


# Faça a segunda parte do Aperfeiçoamento aqui

def uma_funcao_minha(x,y):
    o_pais = textinput("País", "Digite o nome do país");
    
    for pais in lista_de_paises:
        if o_pais == pais["nome"]:
            desenha_bandeira(pais)
            
        

onscreenclick(uma_funcao_minha)



# O desafio deve ser feito diretamente no JSON, não aqui!


# Mantém a janela do Turtle aberta
mainloop()