#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;
using namespace sf;

class Botao{
public:
	Botao(Vector2f posicao, Texture textura, String texto=String("")){
		this->posicao = posicao;
		this->textura = textura;
		this->texto = texto;
	}
	Botao(Vector2f posicao, Color cor, String texto=String("")){
		this->posicao = posicao;
		this->cor = cor;
		this->texto = texto;
		text.setString(texto);
	}
	Botao(ConvexShape shape, String texto=String("")){
		this->texto = texto;
		text.setString(texto);
		this->shape = shape;
	}
	Botao(){}
	~Botao(){}
	void setTextFont(Font& fonte){
		this->fonte = fonte;
		this->text.setFont(fonte);
	}
	void setTextForm(unsigned int size, Uint32 estilo=Text::Regular, Color cor=Color::White){
		this->text.setCharacterSize(size);
		this->text.setStyle(estilo);
		this->text.setFillColor(cor);
	}
	void setString(String& texto){
		this->texto = texto;
		this->text.setString(texto);
	}
	void setTexture(Texture& textura){
		this->textura=textura;
	}
	void setPosition(Vector2f posicao){
		this->posicao = posicao;
	}
	void setPosition(float x, float y){
		this->posicao = Vector2f(x,y);
	}
	void draw(RenderWindow& window){
		this->shape.setPosition(posicao);
		this->shape.setFillColor(cor);
		this->shape.setTexture(&textura);
	}
	Vector2f getPosition(){
		return posicao;
	}
	String getTextButton(){
		return texto;
	}
	Color getColor(){
		return cor;
	}
	void setShape(ConvexShape shape){
		this->shape = shape;
	}
protected:
	Vector2f posicao;
	ConvexShape shape;
	Texture textura;
	Font fonte;
	Text text;
	String texto;
	Color cor;
	//Shape forma;
};

class BotaoCircular : public Botao{
public:
	BotaoCircular(Vector2f posicao, float raio, Texture textura, String texto=String("")){
		this->raio = raio;
		this->textura = textura;
		this->texto = texto;
		this->posicao = posicao;
		this->posicao.x+=raio;
		this->posicao.y+=raio;
		this->botao.setTexture(&textura);
	}
	BotaoCircular(CircleShape c, String texto=String("")){
		this->botao = c;
		this->texto = texto;
		this->raio = c.getRadius();
		this->cor = c.getFillColor();
		this->posicao = c.getPosition();
	}
	BotaoCircular(Vector2f posicao, float raio, Color cor, String texto=String("")){
		this->posicao = posicao;
		this->posicao.x+=raio;
		this->posicao.y+=raio;
		this->cor = cor;
		this->texto = texto;
		this->raio = raio;
		this->botao.setFillColor(cor);
		this->botao.setRadius(raio);
		this->botao.setPosition(posicao);
		this->botao.setOrigin(raio,raio);
		this->text.setString(texto);
	}
	~BotaoCircular(){
	}
	void draw(RenderWindow& window){
		float w, h;
		text.setPosition(0,0);
		w = text.getGlobalBounds().width;
		h = text.getGlobalBounds().height;
		text.setPosition(botao.getPosition().x-w/2,botao.getPosition().y-h/1.2);
		botao.setTexture(&textura);
		botao.setPosition(posicao);
		window.draw(botao);
		window.draw(text);
	}
	float getRadius(){
		return raio;
	}
	bool foiClicado(RenderWindow& window){
		if(Mouse::isButtonPressed(Mouse::Left))
			if(sqrt(pow(Mouse::getPosition(window).x-posicao.x,2)+pow(Mouse::getPosition(window).y-posicao.y,2)) <= raio){
				return true;
			}
		return false;
	}
	void setOutline(float thickness, Color cor){
		botao.setOutlineThickness(thickness);
		botao.setOutlineColor(cor);
	}
protected:
	CircleShape botao;
	float raio;
};

class BotaoRetangular : public Botao{
public:
	BotaoRetangular(Vector2f posicao, Vector2f tamanho, Color cor, String texto=String("")){
		this->posicao = posicao;
		this->tamanho = tamanho;
		this->cor = cor;
		this->texto = texto;
		this->r.setFillColor(cor);
		this->r.setPosition(posicao);
		this->r.setSize(tamanho);
		this->text.setString(texto);
		this->r.setOrigin(Vector2f(tamanho.x,tamanho.y));
		this->rect = r.getGlobalBounds();
		this->posicao.x+=tamanho.x/2;
		this->posicao.y+=tamanho.y/2;
	}
	BotaoRetangular(RectangleShape r, String texto=String("")){
		this->r = r;
		this->texto = texto;
		this->cor = r.getFillColor();
		this->tamanho = r.getSize();
		this->posicao = r.getPosition();
		this->text.setString(texto);
		this->r.setOrigin(Vector2f(tamanho.x,tamanho.y));
		this->rect = r.getGlobalBounds();
	}
	BotaoRetangular(Vector2f posicao, Vector2f tamanho, Texture textura, String texto=String("")){
		this->posicao = posicao;
		this->tamanho = tamanho;
		this->textura = textura;
		this->texto = texto;
		this->r.setTexture(&textura);
		this->r.setPosition(posicao);
		this->r.setOrigin(Vector2f(tamanho.x,tamanho.y));
		this->r.setSize(tamanho);
		this->rect = r.getGlobalBounds();
		this->text.setString(texto);
		this->posicao.x+=tamanho.x/2;
		this->posicao.y+=tamanho.y/2;		
	}
	void setOutline(float thickness, Color cor){
		this->r.setOutlineColor(cor);
		this->r.setOutlineThickness(thickness);
	}
	void draw(RenderWindow& window){
		r.setPosition(posicao);
		r.setFillColor(cor);
		r.setSize(tamanho);
		r.setTexture(&textura);
		r.setOrigin(tamanho.x/2, tamanho.y/2);
		this->rect = r.getGlobalBounds();
		float h, w;
		w = text.getGlobalBounds().width;
		h = text.getGlobalBounds().height;
		text.setPosition(r.getPosition().x-w/2,r.getPosition().y-h/1.2);
		window.draw(r);
		window.draw(text);
	}
	bool foiClicado(RenderWindow& window){
		if(Mouse::isButtonPressed(Mouse::Left)){
			if(rect.contains(Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y))){
				return true;	
			}
			return false;
		}
		return false;
	}
	RectangleShape r;
	FloatRect rect;
	Vector2f tamanho;
};
