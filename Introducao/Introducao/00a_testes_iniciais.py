from turtle import *


# Desenhe o que foi solicitado no enunciado do PDF aqui embaixo

def imprime_coordenadas(x,y):
    penup()
    goto(x,y)
    pendown()
    write("x =  "+ str(x)+", y = "+ str(y))
    

# posição inicial retângulo
penup()
goto(-50,300)
pendown()
# desenha retângulo
forward(100)
right(90)
forward(50)
right(90)
forward(100)
right(90)
forward(50)
right(90)
forward(100)
# posição inicial triângulo
penup()
goto(330,30)
pendown()
# desenha triângulo
setheading(-60)
forward(100)
setheading(180)
forward(100)
setheading(60)
forward(100)
# posição inicial círculo
penup()
goto(40,-280)
pendown()
# desenha círculo
circle(50)
# posição inicial espiral
penup()
goto(-300,0)
pendown()
# desenha espiral
setheading(110)
circle(10, 180)
circle(20, 180)
circle(30, 180)
circle(40, 180)
circle(50, 180)
circle(60, 180)
# posição texto inicial(?)
penup()
goto(-128,-146)
pendown()
#
#write("Home = ", True, align="center")
#write((0,0), True)
onscreenclick(imprime_coordenadas)



# Mantém a janela do Turtle aberta
mainloop()