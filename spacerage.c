#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SpeedP1 4
#define MAXTIRO 30
int musica = 0;
typedef struct inimigo_
{
	SDL_Rect inimigo_frame;
	SDL_Rect inimigo_position;
	int health;
	int ativo;
	int pontuei;
} inimigo;
typedef struct tiro_
{
	int TvelX;
	int TvelY;
	SDL_Rect tiro_frame;
	int ativo;
} tiro;
int MAXINIMIGO1 = 5;
int contadortiro = 0;
int inimigoSom=1;
int gerarnome = 1;                                                                //gerarnome: controle de geração de nomes de planeta
int invulneravel;                                                                 //invulneravel e contadorinvulneravel: controle da invulnerabilidade 
int contadorinvulneravel = 0;
int spawn;                                                                        //spawn: controle do spawn aleatorio entre as portas
int estado = 1;                                                                   //estado: controle do menu
int gamestate = 0;                                                                //gamestate: controle do estado atual do jogo
int running = 1;                                                                  //running: controle do loop principal do jogo
int velX=0, velY=0;                                                               //velX e velY: controle da velocidade do player
int evelX=0, evelY=0;                                                             //evelX e evelY: controle da velocidade do inimigo
int bvelX = 0, bvelY = 0;
int sprite=1;                                                                     //sprite: animação da nave
int contador = 0;                                                                 //contador: controle das estrelas
int health = 200;                                                                 //health: HP da nave                                                                   
int pauseVelX, pauseVelY, pauseEvelX, pauseEvelY, pauseTiroX, pauseTiroY;         //pause: controle do pause
int contadorraio=0;                                                               //contadorraio: controle da borda da fase
int contadorhistoria=0;                                                           //contadorhistoria: controle do scroll da historia                                                            
int contadorinimigo = 0;                                                          //contadorinimigo: controle das ações dos inimigos
int contadorinimigo_2 = 0;
int boolPause=0;                                                                  //boolPause: controle do pause
int VidasP1=3;                                                                    //VidasP1: controle de vidas da nave
int contadorrural = 0;                                                            //contadorrural e contadorrural 2: controle da intro "rural"
int contadorrural2 = 0;
int r, g, b;                                                                      //r, g, b: controle das cores dos planetas
int pontuacao = 0;
int ponto = 0;
time_t t;                                                                         //t: seed para a geração de r, g, b
char r3_nome_imagem[100];
int contador_intror3 = 0;
int contador_trocafase = 0;
int contador_animacao_player_intro = 0;
int primeira_vez = 1;
char nome_planeta[20];
char recordes_nomes[4][20];
int recordes_pontos[4], recordes_planetas[4];
char recordes_planetas_str0, recordes_planetas_str1, recordes_planetas_str2, recordes_pontos_str0, recordes_pontos_str1, recordes_pontos_str2;
int primeira_vez_recordes = 1;
int wave;
int spawnboss = 0;
int setbossposition = 1;
int bossup = 1;
int bossdown = 0;
int bateu_recorde;
char nome_jogador[5];
int pontuacao_planetas = 0;
int primeira_vez_final_recordes = 1;
int probHealth = 0;
int probShield = 0;
int probMult = 0;
int probBass = 0;
int probLaser = 0;
int HealthTela = 1;
int ShieldTela = 1;
int MultTela = 1;
int BassTela = 1;
int LaserTela = 1;
int dropAtivo = 0;
int kills = 0;
int contador_animacao_player_final = 0;
int contador_troca_cutscene = 0;
int estado_recorde = 1;
int storyBMG = 0;
int gameBMG = 0;

inimigo monstro[50];                                                     //monstro[MAXINIMIGO1]: declaração dos inimigos
inimigo boss;
tiro bullet[MAXTIRO];

//DECLARAÇÃO DE TEXTURAS, RECTS, ETC. GLOBAIS(USADAS EM MAIS DE UMA FUNÇÕES)
//-------------------------------------------------------------//
SDL_Event event;
SDL_Renderer * renderer;
SDL_Window * screen;
SDL_Texture * PlayerOneUp;
SDL_Texture * PlayerOneDown;
SDL_Texture * PlayerOneLeft;
SDL_Texture * PlayerOneRight;
SDL_Texture * PlayerOneAccUp;
SDL_Texture * PlayerOneAccDown;
SDL_Texture * PlayerOneAccLeft;
SDL_Texture * PlayerOneAccRight;
SDL_Texture * PlayerOneAcc2Up;
SDL_Texture * PlayerOneAcc2Down;
SDL_Texture * PlayerOneAcc2Left;
SDL_Texture * PlayerOneAcc2Right;
SDL_Texture * PlayerOneShieldUp;
SDL_Texture * PlayerOneShieldDown;
SDL_Texture * PlayerOneShieldLeft;
SDL_Texture * PlayerOneShieldRight;
SDL_Texture * PlayerOneShieldAccUp;
SDL_Texture * PlayerOneShieldAccDown;
SDL_Texture * PlayerOneShieldAccLeft;
SDL_Texture * PlayerOneShieldAccRight;
SDL_Texture * PlayerOneShieldAcc2Up;
SDL_Texture * PlayerOneShieldAcc2Down;
SDL_Texture * PlayerOneShieldAcc2Left;
SDL_Texture * PlayerOneShieldAcc2Right;
SDL_Texture * Historia;
SDL_Texture * Tiro1;
SDL_Texture * Tiro1Up;
SDL_Texture * Tiro1Down;
SDL_Texture * Tiro1Left;
SDL_Texture * Tiro1Right;
SDL_Texture * PlayerOne;
SDL_Rect historia = {0, 0, 450, 1200};
SDL_Rect player = {0,0,64,64};
SDL_Rect hud = {10, 0, 854, 40};
SDL_Rect pause = {999, 999, 854, 450};
SDL_Rect gameover = {0, 0, 854, 450};
//-----------------------------------------------------------//

//FUNÇÕES
//---------------------------------------------------------------------------------//
void controlesmenu();
void controlesjogo(int *inimigox, int *inimigoy);
void criaTiro(void);
int sort_nomes(void);
int recordes_list(void);
int calcular_recorde(int nova_pontuacao, int pontos_planetas);
void organizar_recordes(int pontos, int pontos_planetas);
void controles_recorde(void);
//---------------------------------------------------------------------------------//

int main(void)
{
	for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
	{
		bullet[contadortiro].tiro_frame.x = 0;
		bullet[contadortiro].tiro_frame.y = 0;
		bullet[contadortiro].tiro_frame.w = 10;
		bullet[contadortiro].tiro_frame.h = 10;
		bullet[contadortiro].ativo = 0;
		bullet[contadortiro].TvelX = 0;
		bullet[contadortiro].TvelY = 0;
	}
	int matei = 0;
	int mortos = 0;
	int spawnarinimigos = 1;
	//incializa vídeo
	SDL_Init(SDL_INIT_VIDEO);
	//incializa áudio
	SDL_Init(SDL_INIT_AUDIO);
	//incializa fonte
	TTF_Init();
	//cria janela
	screen = SDL_CreateWindow("Space Rage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 450, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//cria renderer
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 854, 450);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	//carrega imagens, músicas e fontes
	TTF_Font * upheaval = TTF_OpenFont("media/font/UpheavalPro.ttf", 50);
	TTF_Font * adine = TTF_OpenFont("media/font/adinekir.ttf", 80);
	Mix_Music * music = Mix_LoadMUS("media/music/solo_game.mp3");
	Mix_Chunk * morrePlayer = Mix_LoadWAV("media/sfx/playerExplosion.wav");
	Mix_Chunk * birl = Mix_LoadWAV("media/sfx/birl.wav");
	SDL_Surface * nomePlaneta1;
	SDL_Texture * nomePlanetaF;
	SDL_Texture * PauseScreen = IMG_LoadTexture(renderer, "media/outros/pause.png");
	SDL_Texture * GameOver = IMG_LoadTexture(renderer, "media/outros/gameOver.png");
	SDL_Texture * raiomedio = IMG_LoadTexture(renderer, "media/scenarios/SpriteSheet-Small-Lightning-Blue.png");
	SDL_Texture * raiogrande = IMG_LoadTexture(renderer, "media/scenarios/SpriteSheet-Big-Lightning-Blue.png");
	SDL_Texture * raiopequeno = IMG_LoadTexture(renderer, "media/scenarios/SpriteSheet-Medium-Lightning-Blue.png");
	SDL_Texture * coisa = IMG_LoadTexture(renderer, "media/scenarios/thing.png");
	SDL_Texture * intro = IMG_LoadTexture(renderer, "media/scenarios/intro.png");
	SDL_Texture * stars_1 = IMG_LoadTexture(renderer, "media/scenarios/stars_1.png");
	SDL_Texture * stars_2 = IMG_LoadTexture(renderer, "media/scenarios/stars_2.png");
	SDL_Texture * stars_11 = IMG_LoadTexture(renderer, "media/scenarios/stars_1.png");
	SDL_Texture * stars_22 = IMG_LoadTexture(renderer, "media/scenarios/stars_2.png");
	SDL_Texture * stars_3 = IMG_LoadTexture(renderer, "media/scenarios/stars_3.png");
	SDL_Texture * logo = IMG_LoadTexture(renderer, "media/scenarios/menu/sp.png");
	SDL_Texture * novojogo = IMG_LoadTexture(renderer, "media/scenarios/menu/novo.png");
	SDL_Texture * creditos = IMG_LoadTexture(renderer, "media/scenarios/menu/creditos.png");
	SDL_Texture * scores = IMG_LoadTexture(renderer, "media/scenarios/menu/scores.png");
	SDL_Texture * quit = IMG_LoadTexture(renderer, "media/scenarios/menu/quit.png");
	SDL_Texture * historia = IMG_LoadTexture(renderer, "media/scenarios/menu/historiaTexto.png");
	SDL_Texture * cursor = IMG_LoadTexture(renderer, "media/sprites/player/p1basic.png");
	SDL_Texture * Planet = IMG_LoadTexture(renderer, "media/scenarios/planet.png");
	SDL_Texture * Hud1 = IMG_LoadTexture(renderer, "media/hud/hud1vidas.png");
	SDL_Texture * Hud2 = IMG_LoadTexture(renderer, "media/hud/hud2vidas.png");
	SDL_Texture * Hud3 = IMG_LoadTexture(renderer, "media/hud/hud3vidas.png");
	SDL_Texture * lifeFull = IMG_LoadTexture(renderer, "media/hud/lifefull.png");
	SDL_Texture * lifeMed = IMG_LoadTexture(renderer, "media/hud/lifemed.png");
	SDL_Texture * lifeLow = IMG_LoadTexture(renderer, "media/hud/lifelow.png");
	SDL_Texture * lifeKill = IMG_LoadTexture(renderer, "media/hud/lifekill.png");
	SDL_Texture * telacreditos = IMG_LoadTexture(renderer, "media/outros/creditos.png");
	SDL_Texture * dropHealthIcon = IMG_LoadTexture(renderer, "media/sprites/drops/health.png");
	SDL_Texture * dropShieldIcon = IMG_LoadTexture(renderer, "media/sprites/drops/shield.png");
	SDL_Texture * dropMultIcon = IMG_LoadTexture(renderer, "media/sprites/drops/multiplier.png");
	SDL_Texture * dropBassIcon = IMG_LoadTexture(renderer, "media/sprites/drops/bass.png");
	SDL_Texture * dropLaserIcon = IMG_LoadTexture(renderer, "media/sprites/drops/laser.png");
	SDL_Texture * HighscoreHeader = IMG_LoadTexture(renderer, "media/outros/highscore.png");
	PlayerOneUp = IMG_LoadTexture(renderer, "media/sprites/player/p1basic.png");
	PlayerOneDown = IMG_LoadTexture(renderer, "media/sprites/player/p1basicdown.png");
	PlayerOneLeft = IMG_LoadTexture(renderer, "media/sprites/player/p1basicleft.png");
	PlayerOneRight = IMG_LoadTexture(renderer, "media/sprites/player/p1basicright.png");
	PlayerOneAccUp = IMG_LoadTexture(renderer, "media/sprites/player/p1acc1.png");
	PlayerOneAccDown = IMG_LoadTexture(renderer, "media/sprites/player/p1acc1down.png");
	PlayerOneAccLeft = IMG_LoadTexture(renderer, "media/sprites/player/p1acc1left.png");
	PlayerOneAccRight = IMG_LoadTexture(renderer, "media/sprites/player/p1acc1right.png");
	PlayerOneAcc2Up = IMG_LoadTexture(renderer, "media/sprites/player/p1acc2up.png");
	PlayerOneAcc2Down = IMG_LoadTexture(renderer, "media/sprites/player/p1acc2down.png");
	PlayerOneAcc2Left = IMG_LoadTexture(renderer, "media/sprites/player/p1acc2left.png");
	PlayerOneAcc2Right = IMG_LoadTexture(renderer, "media/sprites/player/p1acc2right.png");
	PlayerOneShieldUp = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldbasic.png");
	PlayerOneShieldDown = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldbasicdown.png");
	PlayerOneShieldLeft = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldbasicleft.png");
	PlayerOneShieldRight = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldbasicright.png");	
	PlayerOneShieldAccUp = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc1.png");
	PlayerOneShieldAccDown = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc1down.png");
	PlayerOneShieldAccLeft = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc1left.png");
	PlayerOneShieldAccRight = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc1right.png");
	PlayerOneShieldAcc2Up = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc2up.png");
	PlayerOneShieldAcc2Down = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc2down.png");
	PlayerOneShieldAcc2Left = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc2left.png");
	PlayerOneShieldAcc2Right = IMG_LoadTexture(renderer, "media/sprites/player/p1shieldacc2right.png");
	Tiro1Right = IMG_LoadTexture(renderer, "media/sprites/bullet/Tiro2P1.png");
	Tiro1Up = IMG_LoadTexture(renderer, "media/sprites/bullet/Tiro2P1.png");
	Tiro1Down = IMG_LoadTexture(renderer, "media/sprites/bullet/Tiro2P1.png");
	Tiro1Left = IMG_LoadTexture(renderer, "media/sprites/bullet/Tiro2P1.png");
	SDL_Texture * Foe = IMG_LoadTexture (renderer, "media/sprites/foe/BasicFoe1.png");
	SDL_Texture * Boss_ = IMG_LoadTexture(renderer, "media/sprites/foe/Boss.png");
	SDL_Texture * player_intro1 = IMG_LoadTexture(renderer, "media/sprites/player/p1acc1right.png");
	SDL_Texture * player_intro2 = IMG_LoadTexture(renderer, "media/sprites/player/p1acc2right.png");
	SDL_Texture * nave_cutscene_final1 = IMG_LoadTexture(renderer, "media/outros/nave1.png");
	SDL_Texture * nave_cutscene_final2 = IMG_LoadTexture(renderer, "media/outros/nave2.png");
	SDL_Texture * nave_cutscene_final3 = IMG_LoadTexture(renderer, "media/outros/nave3.png");
	SDL_Texture * nave_cutscene_final4 = IMG_LoadTexture(renderer, "media/outros/nave4.png");
	SDL_Texture * nave_cutscene_final5 = IMG_LoadTexture(renderer, "media/outros/nave5.png");
	SDL_Texture * nave_cutscene_final6 = IMG_LoadTexture(renderer, "media/outros/nave6.png");
	SDL_Texture * telahighscore = IMG_LoadTexture(renderer, "media/scenarios/menu/highscore.png");
	SDL_Texture * recorde_ponteiro = IMG_LoadTexture(renderer, "media/sprites/player/p1basic.png");
	PlayerOne = PlayerOneRight;
	

	
	//cria retângulos
	SDL_Rect stars1 = {0, 0, 854, 450};
	SDL_Rect stars2 = {0, 0, 854, 450};
	SDL_Rect stars11 = {-854, 0, 854, 450};
	SDL_Rect stars22 = {-854, 0, 854, 450};
	SDL_Rect stars3 = {0, 0, 854, 450};
	SDL_Rect novo_jogo = {690, 250, 200, 40};
	SDL_Rect creditos_ = {690, 290, 200, 40};
	SDL_Rect scores_ = {690, 330, 200, 40};
	SDL_Rect quit_ = {690, 370, 200, 40};
	SDL_Rect cursor_ = {630, 240, 64, 64};
	SDL_Rect planet = {592, 188, 262, 262};
	SDL_Rect planetp = {0, 0, 500, 500};
	SDL_Rect biglight1pos = {35, 40, 258, 25};
	SDL_Rect biglight1_ = {0, 0, 258, 25};
	SDL_Rect biglight2pos = {293, 40, 258, 25};
	SDL_Rect biglight2_ = {0, 0, 258, 25};
	SDL_Rect biglight3pos = {551, 40, 258, 25};
	SDL_Rect biglight3_ = {0, 0, 258, 25};
	SDL_Rect biglight4pos = {35, 410, 258, 25};
	SDL_Rect biglight4_ = {0, 0, 258, 25};
	SDL_Rect biglight5pos = {293, 410, 258, 25};
	SDL_Rect biglight5_ = {0, 0, 258, 25};
	SDL_Rect biglight6pos = {551, 410, 258, 25};
	SDL_Rect biglight6_ = {0, 0, 258, 25};
	SDL_Rect smalllight1pos = {10, 65, 25, 106};
	SDL_Rect smalllight1_ = {0, 0, 25, 106};
	SDL_Rect mediumlight1pos = {10, 195, 25, 130};
	SDL_Rect mediumlight1_ = {0, 0, 25, 130};
	SDL_Rect smalllight2pos = {10, 326, 25, 106};
	SDL_Rect smalllight2_ = {0, 0, 25, 106};
	SDL_Rect smalllight3pos = {809, 65, 25, 106};
	SDL_Rect smalllight3_ = {0, 0, 25, 106};
	SDL_Rect mediumlight2pos = {809, 195, 25, 130};
	SDL_Rect mediumlight2_ = {0, 0, 25, 130};
	SDL_Rect smalllight4pos = {809, 326, 25, 106};
	SDL_Rect smalllight4_ = {0, 0, 25, 106};
	SDL_Rect thing1 = {10, 40, 25, 25};
	SDL_Rect thing2 = {293, 40, 25, 25};
	SDL_Rect thing3 = {551, 40, 25, 25};
	SDL_Rect thing4 = {809, 40, 25, 25};
	SDL_Rect thing5 = {10, 410, 25, 25}; 
	SDL_Rect thing6 = {293, 410, 25, 25}; 
	SDL_Rect thing7 = {551, 410, 25, 25}; 
	SDL_Rect thing8 = {809, 410, 25, 25};
	SDL_Rect thing9 = {10, 170, 25, 25}; 
	SDL_Rect thing10 = {10, 303, 25, 25};
	SDL_Rect thing11 = {809, 170, 25, 25};
	SDL_Rect thing12 = {809, 303, 25, 25};
	SDL_Rect story = {0, 450, 854, 1200};
	SDL_Rect rural_ = {0, 0, 854, 450};
	SDL_Rect life = {590, 0, 250, 40};
	SDL_Rect lifekill = {845, 0, 350, 40};
	SDL_Rect telaCreditos = {0, 0, 854, 450};
	SDL_Rect pontos = {320, 0, 150, 40};
	SDL_Rect BemVindo = {175, 175, 300, 40}; 
	SDL_Rect textoNomePlaneta = {480, 175, 50, 40};
	SDL_Rect intro_r3_rect = {0, 0, 854, 450};
	SDL_Rect player_intro_rect = {395,193,64,64};
	SDL_Rect stars1_intro = {0, 0, 854, 450};
	SDL_Rect stars2_intro = {0, 0, 854, 450};
	SDL_Rect stars11_intro = {+854, 0, 854, 450};
	SDL_Rect stars22_intro = {+854, 0, 854, 450};
	SDL_Rect texto_intro1_rect = {60, 267, 350, 50};
	SDL_Rect texto_intro2_rect = {330, 327, 200, 80};
	SDL_Rect dropHealth = {999, 0, 15, 15};
	SDL_Rect dropShield = {999, 0, 15, 15};
	SDL_Rect dropMult = {999, 0, 15, 15};
	SDL_Rect dropBass = {999, 0, 15, 15};
	SDL_Rect dropLaser = {999, 0, 15, 15};
	SDL_Color white = {255, 255, 255, 255};
	SDL_Color gold = {255, 196, 18, 255};
	SDL_Color silver = {168, 168, 168, 255};
	SDL_Color bronze = {194, 100, 2, 255};
	SDL_Rect texto_esc_rect = {20, 420, 350, 25};
	SDL_Rect recordes_nomes_text0_rect = {90, 180, 150, 30};
	SDL_Rect recordes_planetas_text0_rect = {280, 180, 150, 30};
	SDL_Rect recordes_pontos_text0_rect = {470, 180, 300, 30};
	SDL_Rect recordes_nomes_text1_rect = {90, 230, 150, 30};
	SDL_Rect recordes_planetas_text1_rect = {280, 230, 150, 30};
	SDL_Rect recordes_pontos_text1_rect = {470, 230, 300, 30};
	SDL_Rect recordes_nomes_text2_rect = {90, 280, 150, 30};
	SDL_Rect recordes_planetas_text2_rect = {280, 280, 150, 30};
	SDL_Rect recordes_pontos_text2_rect = {470, 280, 300, 30};
	SDL_Rect recordes_nomes_text_rect = {90, 130, 150, 30};
	SDL_Rect recordes_planetas_text_rect = {280, 130, 150, 30};
	SDL_Rect recordes_pontos_text_rect = {470, 130, 300, 30};
	SDL_Rect nave_cutscene_final = {350, 209, 80, 64};
	SDL_Rect texto_cutscene_final_rect = {252, 100, 350, 50}; 
	SDL_Rect telahighscore_rect = {0, 0, 854, 450}; 
	SDL_Rect opcao1_rect = {352, 220, 150, 30};
	SDL_Rect opcao2_rect = {352, 270, 150, 30};
	SDL_Rect opcao3_rect = {352, 320, 150, 30};
	SDL_Rect opcao4_rect = {352, 370, 150, 30};
	SDL_Rect opcao_rect = {227, 150, 400, 30};
	SDL_Rect opcao_titulo_rect = {207, 60, 440, 50};
	SDL_Rect recorde_ponteiro_rect1 = {265, 205, 64, 64};
	SDL_Rect recorde_ponteiro_rect2 = {265, 255, 64, 64};
	SDL_Rect recorde_ponteiro_rect3 = {265, 305, 64, 64};
	SDL_Rect recorde_ponteiro_rect4 = {265, 355, 64, 64};


	SDL_Surface * texto_intro1_sur = TTF_RenderText_Blended(upheaval, "Indo para o planeta...", white);
	SDL_Texture * texto_intro1 = SDL_CreateTextureFromSurface(renderer, texto_intro1_sur);
	SDL_Surface * texto_intro2_sur = TTF_RenderText_Blended(adine, "Atepalus", white);
	SDL_Texture * texto_intro2 = SDL_CreateTextureFromSurface(renderer, texto_intro2_sur);
	SDL_Surface * recordes_nomes_sur = TTF_RenderText_Blended(upheaval, "Nomes", white);
	SDL_Texture * recordes_nomes_text = SDL_CreateTextureFromSurface(renderer, recordes_nomes_sur);
	SDL_Surface * recordes_planetas_sur = TTF_RenderText_Blended(upheaval, "Planetas", white);
	SDL_Texture * recordes_planetas_text = SDL_CreateTextureFromSurface(renderer, recordes_planetas_sur);
	SDL_Surface * recordes_pontos_sur = TTF_RenderText_Blended(upheaval, "Pontuacoes", white);
	SDL_Texture * recordes_pontos_text = SDL_CreateTextureFromSurface(renderer, recordes_pontos_sur);
	SDL_Surface * texto_cutscene_final_sur = TTF_RenderText_Blended(upheaval, "Planeta salvo!", white);
	SDL_Texture * texto_cutscene_final = SDL_CreateTextureFromSurface(renderer, texto_cutscene_final_sur);

	SDL_Surface * opcao1_sur = TTF_RenderText_Blended(upheaval, "PRU", white);
	SDL_Texture * opcao1 = SDL_CreateTextureFromSurface(renderer, opcao1_sur);
	SDL_Surface * opcao2_sur = TTF_RenderText_Blended(upheaval, "KEY", white);
	SDL_Texture * opcao2 = SDL_CreateTextureFromSurface(renderer, opcao2_sur);
	SDL_Surface * opcao3_sur = TTF_RenderText_Blended(upheaval, "YOU", white);
	SDL_Texture * opcao3 = SDL_CreateTextureFromSurface(renderer, opcao3_sur);
	SDL_Surface * opcao4_sur = TTF_RenderText_Blended(upheaval, "MAD", white);
	SDL_Texture * opcao4 = SDL_CreateTextureFromSurface(renderer, opcao4_sur);
	SDL_Surface * opcao_sur = TTF_RenderText_Blended(upheaval, "Escolha seu nickname", white);
	SDL_Texture * opcao = SDL_CreateTextureFromSurface(renderer, opcao_sur);
	SDL_Surface * opcao_titulo_sur = TTF_RenderText_Blended(upheaval, "Voce bateu um recorde!", gold);
	SDL_Texture * opcao_titulo = SDL_CreateTextureFromSurface(renderer, opcao_titulo_sur);

	
	//Define cor RGB aleatória para o planeta
	srand((unsigned) time(&t));
	r=rand()%255;
	g=rand()%255;
	b=rand()%255;

	//Define tamanho e posição aleatória para o planeta
	planet.x=rand()%750;
	planet.y=rand()%400;
	planet.w=rand()%400;
	planet.h=planet.w;

	//Gera probabilidades para os drops
	probHealth=rand()%4;
	probShield=rand()%4;
	probMult=rand()%4;
	probBass=rand()%4;
	probLaser=rand()%4;
	
	//contador para aparecimento da logo com as opções do menu

	for(contadorinimigo = 1; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
	{
		monstro[contadorinimigo].ativo = 0;
		monstro[contadorinimigo].pontuei = 1;
	}

	while(running)
	{
		SDL_RenderClear(renderer);
		// Tela do Menu
		while(gamestate == 0)
		{
																																																				
			if(contador_intror3 < 115)
					{
					SDL_RenderClear(renderer);
					sprintf(r3_nome_imagem, "media/intro/r3/intro-r3_%06d.png", contador_intror3);
					SDL_Texture * intro_r3 = IMG_LoadTexture(renderer, r3_nome_imagem);
					SDL_RenderCopy(renderer, intro_r3, NULL, &intro_r3_rect);
					contador_intror3++;
					SDL_DestroyTexture(intro_r3);
					}
			else
			{
				SDL_RenderClear(renderer);

					controlesmenu();
				if (contador == 2)
				{
					stars1.x += 1;
					stars2.x += 2;
					stars11.x += 1;
					stars22.x += 2;
					if (stars22.x == 0)
						{
							stars2.x = 0;
							stars22.x = -854;
						}
					if(stars11.x == 0)
						{
							stars1.x = 0;
							stars11.x = -854;
						}		
				}
				if (estado == 1)
					cursor_.y = 240;
				if (estado == 2)
					cursor_.y = 280;
				if (estado == 3)
					cursor_.y = 320;
				if (estado == 4)
					cursor_.y = 360;
				contador++;
				if(contador > 2)
					contador = 0;
				SDL_RenderCopy(renderer, intro, NULL, NULL);
				SDL_RenderCopy(renderer, stars_1, NULL, &stars1);
				SDL_RenderCopy(renderer, stars_2, NULL, &stars2);
				SDL_RenderCopy(renderer, stars_11, NULL, &stars11);
				SDL_RenderCopy(renderer, stars_22, NULL, &stars22);
				SDL_RenderCopy(renderer, stars_3, NULL, &stars3);
				SDL_RenderCopy(renderer, logo, NULL, NULL);
				SDL_RenderCopy(renderer, novojogo, NULL, &novo_jogo);
				SDL_RenderCopy(renderer, creditos, NULL, &creditos_);
				SDL_RenderCopy(renderer, scores, NULL, &scores_);
				SDL_RenderCopy(renderer, quit, NULL, &quit_);
				SDL_RenderCopy(renderer, cursor, NULL, &cursor_);
				while(musica == 0)
				{
					Mix_PlayMusic(music, -1);
					musica = 1;
				}
			}
			SDL_RenderPresent(renderer);
			SDL_Delay(1000/60);
		}

		// Tela de Game Over
		while(gamestate == -2)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
				}
				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_BACKSPACE:
							gamestate = 0;
							break;
					}
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, GameOver, NULL, &gameover);
			SDL_RenderPresent(renderer);
		}
		// Tela de Historia
		while(gamestate == 2)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
				}

				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
							contador_trocafase = 0;
							primeira_vez = 1;
							gamestate = 3;
							story.y = 450;
							break;
					}
				}
			}
			SDL_RenderClear(renderer);
			if (contadorhistoria == 30)
				story.y -= 1;
			if (story.y == -1200)
			{
				story.y = 450;
				gamestate = 3;
				ponto = 0;
				pontuacao_planetas = 0;
			}
			contadorhistoria++;
			if (contadorhistoria > 30)
				contadorhistoria = 0;
			SDL_RenderCopy(renderer, historia, NULL, &story);
			SDL_RenderPresent(renderer);
		}
		
		while(gamestate == 3)
		{
			SDL_RenderClear(renderer);

			if(primeira_vez == 1)
			{
				//vai sortear o nome do planeta
				sort_nomes();
			}

			SDL_Surface * texto_intro2_sur = TTF_RenderText_Blended(adine, nome_planeta, white);
			SDL_Texture * texto_intro2 = SDL_CreateTextureFromSurface(renderer, texto_intro2_sur);
		

			primeira_vez = 0;
			
			if(contador_trocafase < 500)
			{
				stars1_intro.x -= 1;
				stars2_intro.x -= 2;
				stars11_intro.x -= 1;
				stars22_intro.x -= 2;
				if (stars22_intro.x == 0)
				{
					stars2_intro.x = 0;
					stars22_intro.x = +854;
				}
				if(stars11_intro.x == 0)
				{
				stars1_intro.x = 0;
				stars11_intro.x = +854;
				}		

				SDL_RenderCopy(renderer, stars_1, NULL, &stars1_intro);
				SDL_RenderCopy(renderer, stars_2, NULL, &stars2_intro);
				SDL_RenderCopy(renderer, stars_11, NULL, &stars11_intro);
				SDL_RenderCopy(renderer, stars_22, NULL, &stars22_intro);
				SDL_RenderCopy(renderer, stars_3, NULL, &stars3);

				if(contador_trocafase > 40)
					SDL_RenderCopy(renderer, texto_intro1, NULL, &texto_intro1_rect);
				
				if(contador_trocafase > 100)
					SDL_RenderCopy(renderer, texto_intro2, NULL, &texto_intro2_rect);



				if(contador_animacao_player_intro < 5)
				{
					SDL_RenderCopy(renderer, player_intro1, NULL, &player_intro_rect);
					contador_animacao_player_intro++;
				}
				if(contador_animacao_player_intro >= 5)
				{
					SDL_RenderCopy(renderer, player_intro2, NULL, &player_intro_rect);
					contador_animacao_player_intro++;
				}
				if(contador_animacao_player_intro == 10)
				contador_animacao_player_intro = 0;

				contador_trocafase++;
			}

			else{
			srand((unsigned) time(&t));
			r=rand()%255;
			g=rand()%255;
			b=rand()%255;

			//Define tamanho e posição aleatória para o planeta
			planet.x=rand()%750;
			planet.y=rand()%400;
			planet.w=rand()%400;
			planet.h=planet.w;
			if(planet.h < 70)
				planet.h = 70;
			if(planet.w < 70)
				planet.w = 70;
			gamestate = 1;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(1000/60);
		}
		// OPÇÃO NOVO JOGO!
		
		while (gamestate == 1)
		{
			if(spawnboss)
			{
				if(setbossposition)
				{
					boss.inimigo_frame.x = 904;
					boss.inimigo_frame.y = 225;
					boss.inimigo_frame.w = 96;
					boss.inimigo_frame.h = 96;
					boss.health = 1200;
					setbossposition = 0;
				}
			}
			if(contadorinimigo_2 < MAXINIMIGO1)
			{
				if(monstro[contadorinimigo_2].ativo == 0)
				{	
					monstro[contadorinimigo_2].pontuei = 1;
					spawn = rand()%4;
					if(spawn==0)
					{
						monstro[contadorinimigo_2].inimigo_frame.x = 500;
						monstro[contadorinimigo_2].inimigo_frame.y = 500;
						monstro[contadorinimigo_2].inimigo_frame.w = 32;
						monstro[contadorinimigo_2].inimigo_frame.h = 32;
						monstro[contadorinimigo_2].ativo = 1;
						monstro[contadorinimigo_2].health = 100;
					}
					if(spawn==1)
					{
						monstro[contadorinimigo_2].inimigo_frame.x = 500;
						monstro[contadorinimigo_2].inimigo_frame.y = -50;
						monstro[contadorinimigo_2].inimigo_frame.w = 32;
						monstro[contadorinimigo_2].inimigo_frame.h = 32;
						monstro[contadorinimigo_2].ativo = 1;
						monstro[contadorinimigo_2].health = 100;
					}
					if(spawn==2)
					{
						monstro[contadorinimigo_2].inimigo_frame.x = -50;
						monstro[contadorinimigo_2].inimigo_frame.y = 225;
						monstro[contadorinimigo_2].inimigo_frame.w = 32;
						monstro[contadorinimigo_2].inimigo_frame.h = 32;
						monstro[contadorinimigo_2].ativo = 1;
						monstro[contadorinimigo_2].health = 100;
					}
					if(spawn==3)
					{
						monstro[contadorinimigo_2].inimigo_frame.x = 904;
						monstro[contadorinimigo_2].inimigo_frame.y = 225;
						monstro[contadorinimigo_2].inimigo_frame.w = 32;
						monstro[contadorinimigo_2].inimigo_frame.h = 32;
						monstro[contadorinimigo_2].ativo = 1;
						monstro[contadorinimigo_2].health = 100;
					}
				}
				else
					contadorinimigo_2++;
			}
				SDL_RenderClear(renderer);
				for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
					controlesjogo(&(monstro[contadorinimigo]).inimigo_frame.x, &(monstro[contadorinimigo]).inimigo_frame.y);
				if (contador == 2)
				{
					stars1.x += 1;
					stars2.x += 2;
					stars11.x += 1;
					stars22.x += 2;
					if (stars22.x == 0)
						{
							stars2.x = 0;
							stars22.x = -854;
						}
					if(stars11.x == 0)
						{
							stars1.x = 0;
							stars11.x = -854;
						}		
				}
				if (contadorraio == 8)
				{
					biglight1_.y += 25;
					biglight2_.y += 25;
					biglight3_.y += 25;
					biglight4_.y += 25;
					biglight5_.y += 25;
					biglight6_.y += 25;
					smalllight1_.x += 25;
					smalllight2_.x += 25;
					smalllight3_.x += 25;
					smalllight4_.x += 25;
					mediumlight1_.x += 25;
					mediumlight2_.x += 25;
				}
				if(boolPause==0)
				{
					player.x=player.x+velX;
					player.y=player.y+velY;
					for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
					{
						if(bullet[contadortiro].ativo == 1)
						{
							bullet[contadortiro].tiro_frame.x += bullet[contadortiro].TvelX;
							bullet[contadortiro].tiro_frame.y += bullet[contadortiro].TvelY;
						}
					}
					for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
					{	
						if (monstro[contadorinimigo].inimigo_frame.x > player.x)
							evelX = -1;
						if (monstro[contadorinimigo].inimigo_frame.x < player.x)
							evelX = 1;
						if (monstro[contadorinimigo].inimigo_frame.y < player.y)
							evelY = 1;
						if (monstro[contadorinimigo].inimigo_frame.y > player.y)
							evelY = -1;
						if(monstro[contadorinimigo].inimigo_frame.x != player.x)
							monstro[contadorinimigo].inimigo_frame.x += evelX;
						if(monstro[contadorinimigo].inimigo_frame.y != player.y)
							monstro[contadorinimigo].inimigo_frame.y += evelY;
					}
					if(invulneravel != 1)
					{
						if(SDL_HasIntersection(&player, &biglight1pos) == SDL_TRUE)
						{
							player.y += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &biglight2pos) == SDL_TRUE)
						{
							player.y += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &biglight3pos) == SDL_TRUE)
						{
							player.y += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &biglight4pos) == SDL_TRUE)
						{
							player.y -= SpeedP1;
						}
						if(SDL_HasIntersection(&player, &biglight5pos) == SDL_TRUE)
						{
							player.y -= SpeedP1;
						}
						if(SDL_HasIntersection(&player, &biglight6pos) == SDL_TRUE)
						{
							player.y -= SpeedP1;
						}
						if(SDL_HasIntersection(&player, &smalllight1pos) == SDL_TRUE)
						{
							player.x += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &smalllight2pos) == SDL_TRUE)
						{
							player.x += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &mediumlight1pos) == SDL_TRUE)
						{
							player.x += SpeedP1;
						}
						if(SDL_HasIntersection(&player, &smalllight3pos) == SDL_TRUE)
						{
							player.x -= SpeedP1;
						}
						if(SDL_HasIntersection(&player, &smalllight4pos) == SDL_TRUE)
						{
							player.x -= SpeedP1;
						}
						if(SDL_HasIntersection(&player, &mediumlight2pos) == SDL_TRUE)
						{
							player.x -= SpeedP1;
						}
						for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
						{
							if(SDL_HasIntersection(&player, &monstro[contadorinimigo].inimigo_frame) == SDL_TRUE)
							{
								health -= 1;
							}
						}
					}
					for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
					{
						for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
						{
							if(SDL_HasIntersection(&monstro[contadorinimigo].inimigo_frame, &bullet[contadortiro].tiro_frame) == SDL_TRUE)
							{
								monstro[contadorinimigo].health -= 40;
								bullet[contadortiro].ativo = 0;
								bullet[contadortiro].TvelX = 0;
								bullet[contadortiro].TvelY = 0;
								bullet[contadortiro].tiro_frame.x = 0;
								bullet[contadortiro].tiro_frame.y = 0;
							}
						}
					}
					for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
					{
						if(monstro[contadorinimigo].health < 0)
						{
							kills++;
							if(HealthTela==1)
							{
								if(kills==1)
								{
									dropHealth.x=monstro[contadorinimigo].inimigo_frame.x;
									dropHealth.y=monstro[contadorinimigo].inimigo_frame.y;
								}
								HealthTela=0;
							}

						
							if(ShieldTela==1)
							{
								if(kills==2)
								{
									dropShield.x=monstro[contadorinimigo++].inimigo_frame.x;
									dropShield.y=monstro[contadorinimigo++].inimigo_frame.y;
								}
								ShieldTela=0;
							}
						
							if(MultTela==1)
							{
								if(kills==3)
								{
									dropMult.x=monstro[contadorinimigo].inimigo_frame.x;
									dropMult.y=monstro[contadorinimigo].inimigo_frame.y;
								}
								MultTela=0;
							}
		
							if(BassTela==1)
							{
								if(kills==4)
								{
									dropBass.x=monstro[contadorinimigo].inimigo_frame.x;
									dropBass.y=monstro[contadorinimigo].inimigo_frame.y;
								}
								BassTela=0;
							}
				
							if(LaserTela==1)
							{
								if(kills==5)
								{
									dropLaser.x=monstro[contadorinimigo].inimigo_frame.x;
									dropLaser.y=monstro[contadorinimigo].inimigo_frame.y;
								}
								LaserTela=0;
							}
							kills++;
							monstro[contadorinimigo].ativo = 0;
							monstro[contadorinimigo].inimigo_frame.x = 0;
							monstro[contadorinimigo].inimigo_frame.y = 0;
							if(monstro[contadorinimigo].pontuei == 1 )
							{
								ponto += 50;
								monstro[contadorinimigo].pontuei = 0;
								matei++;
							}
							inimigoSom=1;
						}
					}
					for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
					{
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight1pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight2pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight3pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight4pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight5pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &biglight6pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &smalllight1pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &smalllight2pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &mediumlight1pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &smalllight3pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &smalllight4pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &mediumlight2pos) == SDL_TRUE)
						{
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
					}
					if(SDL_HasIntersection(&player, &dropHealth) == SDL_TRUE)
					{
						health+=50;
						HealthTela=1;
						dropHealth.x = -200;
						dropHealth.y = -200;
					}
					if(invulneravel == 1)
					{
						contadorinvulneravel++;
						if(contadorinvulneravel == 180)
						{
							contadorinvulneravel = 0;
							invulneravel = 0;
						}

					}
				}
				if(biglight1_.y == 125)
				{
					biglight1_.y = 0;
					biglight2_.y = 0;
					biglight3_.y = 0;
					biglight4_.y = 0;
					biglight5_.y = 0;
					biglight6_.y = 0;
					smalllight1_.x = 0;
					smalllight2_.x = 0;
					smalllight3_.x = 0;
					smalllight4_.x = 0;
					mediumlight1_.x = 0;
					mediumlight2_.x = 0;
				}
				if(health<0)
				{
						velX=0;
						velY=0;
						player.x=100;
						player.y=100;
						VidasP1--;
						health=200;
						invulneravel = 1;
						Mix_PlayChannel(-1, morrePlayer, 0);
				}
				if(VidasP1==0)
				{
					SDL_RenderCopy(renderer, GameOver, NULL, &gameover);
					recordes_list();
					bateu_recorde = calcular_recorde(ponto, pontuacao_planetas);
					if(bateu_recorde == 1)
					{
						primeira_vez_final_recordes = 1;
						gamestate = 6;
					}
					else
						gamestate = -2;
					
					VidasP1=3;
					health=200;

				}
				contadorraio++;
				if(contadorraio > 8)
					contadorraio = 0;
				contador++;
				if(contador > 2)
					contador = 0;
				SDL_RenderCopy(renderer, intro, NULL, NULL);
				SDL_RenderCopy(renderer, stars_1, NULL, &stars1);
				SDL_RenderCopy(renderer, stars_2, NULL, &stars2);
				SDL_RenderCopy(renderer, stars_11, NULL, &stars11);
				SDL_RenderCopy(renderer, stars_22, NULL, &stars22);
				SDL_RenderCopy(renderer, stars_3, NULL, &stars3);
				//muda a cor do planeta
				SDL_SetTextureColorMod(Planet, r, g, b);
				SDL_RenderCopy(renderer, Planet, NULL, &planet);
				SDL_RenderCopy(renderer, raiogrande, &biglight1_, &biglight1pos);
				SDL_RenderCopy(renderer, raiogrande, &biglight2_, &biglight2pos);
				SDL_RenderCopy(renderer, raiogrande, &biglight3_, &biglight3pos);
				SDL_RenderCopy(renderer, raiogrande, &biglight4_, &biglight4pos);
				SDL_RenderCopy(renderer, raiogrande, &biglight5_, &biglight5pos);
				SDL_RenderCopy(renderer, raiogrande, &biglight6_, &biglight6pos);
				SDL_RenderCopy(renderer, raiopequeno, &smalllight1_, &smalllight1pos);
				SDL_RenderCopy(renderer, raiopequeno, &smalllight2_, &smalllight2pos);
				SDL_RenderCopy(renderer, raiomedio, &mediumlight1_, &mediumlight1pos);
				SDL_RenderCopy(renderer, raiopequeno, &smalllight3_, &smalllight3pos);
				SDL_RenderCopy(renderer, raiopequeno, &smalllight4_, &smalllight4pos);
				SDL_RenderCopy(renderer, raiomedio, &mediumlight2_, &mediumlight2pos);
				SDL_RenderCopy(renderer, coisa, NULL, &thing1);
				SDL_RenderCopy(renderer, coisa, NULL, &thing2);
				SDL_RenderCopy(renderer, coisa, NULL, &thing3);
				SDL_RenderCopy(renderer, coisa, NULL, &thing4);
				SDL_RenderCopy(renderer, coisa, NULL, &thing5);
				SDL_RenderCopy(renderer, coisa, NULL, &thing6);
				SDL_RenderCopy(renderer, coisa, NULL, &thing7);
				SDL_RenderCopy(renderer, coisa, NULL, &thing8);
				SDL_RenderCopy(renderer, coisa, NULL, &thing9);
				SDL_RenderCopy(renderer, coisa, NULL, &thing10);
				SDL_RenderCopy(renderer, coisa, NULL, &thing11);
				SDL_RenderCopy(renderer, coisa, NULL, &thing12);
				SDL_RenderCopy(renderer, dropHealthIcon, NULL, &dropHealth);
				SDL_RenderCopy(renderer, dropShieldIcon, NULL, &dropShield);
				SDL_RenderCopy(renderer, dropMultIcon, NULL, &dropMult);
				SDL_RenderCopy(renderer, dropBassIcon, NULL, &dropBass);
				SDL_RenderCopy(renderer, dropLaserIcon, NULL, &dropLaser);

				//controla o tamanho da barra de health
				lifekill.x=health+630;
				//carrega hud: vidas e health
				if(VidasP1==3)
				{
					SDL_RenderCopy(renderer, Hud3, NULL, &hud);	
				}
				else if(VidasP1==2)
				{
					SDL_RenderCopy(renderer, Hud2, NULL, &hud);	
				}
				else if(VidasP1==1)
				{
					SDL_RenderCopy(renderer, Hud1, NULL, &hud);	
				}
				if(health>150)
				{
					SDL_RenderCopy(renderer, lifeFull, NULL, &life);	
				}
				else if(health>75 && health<=150)
				{
					SDL_RenderCopy(renderer, lifeMed, NULL, &life);
				}
				else if(health>0 && health<=75)
				{
					SDL_RenderCopy(renderer, lifeLow, NULL, &life);
				}
				if(spawnboss)
				{
					if(boss.inimigo_frame.x > 675)
						bvelX = -2;
					else
						bvelX = 0;
					if(boss.inimigo_frame.y <= 100)
					{
						bossup = 0;
						bossdown = 1;
					}
					if(boss.inimigo_frame.y >= 290)
					{
						bossup = 1;
						bossdown = 0;
					}
					if(bossup)
						bvelY = -2;
					if(bossdown)
						bvelY = 2;
					boss.inimigo_frame.x += bvelX;
					boss.inimigo_frame.y += bvelY;
				}
				
				if(spawnboss)
				{
					for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
					{
						if(SDL_HasIntersection(&bullet[contadortiro].tiro_frame, &boss.inimigo_frame) == SDL_TRUE)
						{
							boss.health -= 40;
							bullet[contadortiro].ativo = 0;
							bullet[contadortiro].TvelX = 0;
							bullet[contadortiro].TvelY = 0;
							bullet[contadortiro].tiro_frame.x = 0;
							bullet[contadortiro].tiro_frame.y = 0;
						}
					}
				}
				if(SDL_HasIntersection(&player, &boss.inimigo_frame) == SDL_TRUE)
				{
					health-=50;
				}
				if(boss.health < 0)
				{
					spawnboss = 0;
					boss.inimigo_frame.x = -400;
					boss.inimigo_frame.y = -400;
					gamestate = 8;
					contadorinimigo_2 = 0;
					MAXINIMIGO1 += 2;
					primeira_vez = 1;
					contador_trocafase = 0;
					wave = 0;
					matei = 0;
					boss.health = 1200;
					pontuacao_planetas++;
				}
				for(contadorinimigo = 0; contadorinimigo < MAXINIMIGO1; contadorinimigo++)
					if(monstro[contadorinimigo].ativo == 1)
						SDL_RenderCopy(renderer, Foe, NULL, &(monstro[contadorinimigo]).inimigo_frame);
				for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
				{
					if(bullet[contadortiro].ativo == 1)
					{
						SDL_RenderCopy(renderer, Tiro1, NULL, &(bullet[contadortiro]).tiro_frame);
					}
				}
				SDL_RenderCopy(renderer, Boss_, NULL, &boss.inimigo_frame);
				//Pontuação
				pontuacao=ponto;
				char pontuacaoTexto[15];
				sprintf(pontuacaoTexto, "%08d", pontuacao);	
				SDL_Surface * textoPontos = TTF_RenderText_Blended(upheaval, pontuacaoTexto, white);
				SDL_Texture * pontosJogo = SDL_CreateTextureFromSurface(renderer, textoPontos);
				if (matei == MAXINIMIGO1 && wave == 0)
				{
					contadorinimigo_2 = 0;
					wave++;
					matei = 0;
					MAXINIMIGO1 += 5;
				}
				if (matei == MAXINIMIGO1 && wave == 1)
				{
					matei = 0;
					spawnboss = 1;
					wave++;
				}
				SDL_RenderCopy(renderer, lifeKill, NULL, &lifekill);
				SDL_RenderCopy(renderer, pontosJogo, NULL, &pontos);
				SDL_RenderCopy(renderer, PlayerOne, NULL, &player);
				SDL_RenderCopy(renderer, PauseScreen, NULL, &pause);
				SDL_RenderPresent(renderer);
				SDL_Delay(1000/60);
		}
		//OPÇÃO CREDITOS!
		while(gamestate == 4)
		{

			SDL_Surface * texto_esc_sur = TTF_RenderText_Blended(upheaval, "Pressione Esc para voltar", white);
			SDL_Texture * texto_esc = SDL_CreateTextureFromSurface(renderer, texto_esc_sur);

			while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
				}
				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							gamestate = 0;
							break;
					}
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, telacreditos, NULL, &telaCreditos);
			SDL_RenderCopy(renderer, texto_esc, NULL, &texto_esc_rect);
			SDL_RenderPresent(renderer);
		}
		//OPÇÃO RECORDES
		while(gamestate == 5)
		{

			
			if(primeira_vez_recordes == 1)
			{
				SDL_RenderClear(renderer);
				recordes_list();
				
				sprintf(&recordes_planetas_str0, "%03d", recordes_planetas[0]);
				sprintf(&recordes_planetas_str1, "%03d", recordes_planetas[1]);
				sprintf(&recordes_planetas_str2, "%03d", recordes_planetas[2]);
				sprintf(&recordes_pontos_str0, "%08d", recordes_pontos[0]);
				sprintf(&recordes_pontos_str1, "%08d", recordes_pontos[1]);
				sprintf(&recordes_pontos_str2, "%08d", recordes_pontos[2]);
				

				SDL_Surface * texto_esc_sur = TTF_RenderText_Blended(upheaval, "Pressione Esc para voltar", white);
				SDL_Texture * texto_esc = SDL_CreateTextureFromSurface(renderer, texto_esc_sur);



				SDL_Surface * recordes_nomes_sur0 = TTF_RenderText_Blended(upheaval, recordes_nomes[0], gold);
				SDL_Texture * recordes_nomes_text0 = SDL_CreateTextureFromSurface(renderer, recordes_nomes_sur0);
				SDL_Surface * recordes_planetas_sur0 = TTF_RenderText_Blended(upheaval, &recordes_planetas_str0, gold);
				SDL_Texture * recordes_planetas_text0 = SDL_CreateTextureFromSurface(renderer, recordes_planetas_sur0);
				SDL_Surface * recordes_pontos_sur0 = TTF_RenderText_Blended(upheaval, &recordes_pontos_str0, gold);
				SDL_Texture * recordes_pontos_text0 = SDL_CreateTextureFromSurface(renderer, recordes_pontos_sur0);
				SDL_Surface * recordes_nomes_sur1 = TTF_RenderText_Blended(upheaval, recordes_nomes[1], silver);
				SDL_Texture * recordes_nomes_text1 = SDL_CreateTextureFromSurface(renderer, recordes_nomes_sur1);
				SDL_Surface * recordes_planetas_sur1 = TTF_RenderText_Blended(upheaval, &recordes_planetas_str1, silver);
				SDL_Texture * recordes_planetas_text1 = SDL_CreateTextureFromSurface(renderer, recordes_planetas_sur1);
				SDL_Surface * recordes_pontos_sur1 = TTF_RenderText_Blended(upheaval, &recordes_pontos_str1, silver);
				SDL_Texture * recordes_pontos_text1 = SDL_CreateTextureFromSurface(renderer, recordes_pontos_sur1);
				SDL_Surface * recordes_nomes_sur2 = TTF_RenderText_Blended(upheaval, recordes_nomes[2], bronze);
				SDL_Texture * recordes_nomes_text2 = SDL_CreateTextureFromSurface(renderer, recordes_nomes_sur2);
				SDL_Surface * recordes_planetas_sur2 = TTF_RenderText_Blended(upheaval, &recordes_planetas_str2, bronze);
				SDL_Texture * recordes_planetas_text2 = SDL_CreateTextureFromSurface(renderer, recordes_planetas_sur2);
				SDL_Surface * recordes_pontos_sur2 = TTF_RenderText_Blended(upheaval, &recordes_pontos_str2, bronze);
				SDL_Texture * recordes_pontos_text2 = SDL_CreateTextureFromSurface(renderer, recordes_pontos_sur2);
				
				SDL_RenderCopy(renderer, telahighscore, NULL, &telahighscore_rect);
				SDL_RenderCopy(renderer, recordes_nomes_text, NULL, &recordes_nomes_text_rect);
				SDL_RenderCopy(renderer, recordes_planetas_text, NULL, &recordes_planetas_text_rect);
				SDL_RenderCopy(renderer, recordes_pontos_text, NULL, &recordes_pontos_text_rect);
				SDL_RenderCopy(renderer, recordes_nomes_text0, NULL, &recordes_nomes_text0_rect);
				SDL_RenderCopy(renderer, recordes_planetas_text0, NULL, &recordes_planetas_text0_rect);
				SDL_RenderCopy(renderer, recordes_pontos_text0, NULL, &recordes_pontos_text0_rect);
				SDL_RenderCopy(renderer, recordes_nomes_text1, NULL, &recordes_nomes_text1_rect);
				SDL_RenderCopy(renderer, recordes_planetas_text1, NULL, &recordes_planetas_text1_rect);
				SDL_RenderCopy(renderer, recordes_pontos_text1, NULL, &recordes_pontos_text1_rect);
				SDL_RenderCopy(renderer, recordes_nomes_text2, NULL, &recordes_nomes_text2_rect);
				SDL_RenderCopy(renderer, recordes_planetas_text2, NULL, &recordes_planetas_text2_rect);
				SDL_RenderCopy(renderer, recordes_pontos_text2, NULL, &recordes_pontos_text2_rect);
				SDL_RenderCopy(renderer, texto_esc, NULL, &texto_esc_rect);
				SDL_RenderPresent(renderer);

			}
			
		
			primeira_vez_recordes = 0;

			while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
				}
				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							gamestate = 0;
							break;
					}
				}
			}
			
			
			SDL_RenderPresent(renderer);
		}

		// ler nome do jogador com a variavel nome_jogador
		while(gamestate == 6)
		{
			
			SDL_RenderClear(renderer);
			controles_recorde();

			SDL_RenderCopy(renderer, opcao, NULL, &opcao_rect);
			SDL_RenderCopy(renderer, opcao1, NULL, &opcao1_rect);
			SDL_RenderCopy(renderer, opcao2, NULL, &opcao2_rect);
			SDL_RenderCopy(renderer, opcao3, NULL, &opcao3_rect);
			SDL_RenderCopy(renderer, opcao4, NULL, &opcao4_rect);
			SDL_RenderCopy(renderer, opcao_titulo, NULL, &opcao_titulo_rect);

			if(estado_recorde == 1)
				SDL_RenderCopy(renderer, recorde_ponteiro, NULL, &recorde_ponteiro_rect1);
			if(estado_recorde == 2)
				SDL_RenderCopy(renderer, recorde_ponteiro, NULL, &recorde_ponteiro_rect2);
			if(estado_recorde == 3)
				SDL_RenderCopy(renderer, recorde_ponteiro, NULL, &recorde_ponteiro_rect3);
			if(estado_recorde == 4)
				SDL_RenderCopy(renderer, recorde_ponteiro, NULL, &recorde_ponteiro_rect4);

			SDL_RenderPresent(renderer);
		}


		while(gamestate == 7)
		{
			if(primeira_vez_final_recordes == 1)
			{

				SDL_RenderClear(renderer);
				organizar_recordes(ponto, pontuacao_planetas);
			}

			primeira_vez_recordes = 0;
			gamestate = 5;
			primeira_vez_recordes = 1;

			while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
				}
				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							gamestate = 0;
							break;
					}
				}
			}
			
			
			SDL_RenderPresent(renderer);
		}

		while(gamestate == 8)
		{
			SDL_RenderClear(renderer);

			if(contador_troca_cutscene < 300)
			{
				stars1_intro.x -= 1;
				stars2_intro.x -= 2;
				stars11_intro.x -= 1;
				stars22_intro.x -= 2;
				if (stars22_intro.x == 0)
				{
					stars2_intro.x = 0;
					stars22_intro.x = +854;
				}
				if(stars11_intro.x == 0)
				{
				stars1_intro.x = 0;
				stars11_intro.x = +854;
				}		

				SDL_RenderCopy(renderer, stars_1, NULL, &stars1_intro);
				SDL_RenderCopy(renderer, stars_2, NULL, &stars2_intro);
				SDL_RenderCopy(renderer, stars_11, NULL, &stars11_intro);
				SDL_RenderCopy(renderer, stars_22, NULL, &stars22_intro);
				SDL_RenderCopy(renderer, stars_3, NULL, &stars3);

				if(contador_troca_cutscene > 40)
					SDL_RenderCopy(renderer, texto_cutscene_final, NULL, &texto_cutscene_final_rect);
			

				if(contador_troca_cutscene >= 0 && contador_troca_cutscene < 50)
					SDL_RenderCopy(renderer, nave_cutscene_final1, NULL, &nave_cutscene_final);
				
				if(contador_troca_cutscene >= 50 && contador_troca_cutscene < 60)
					SDL_RenderCopy(renderer, nave_cutscene_final2, NULL, &nave_cutscene_final);
				
				if(contador_troca_cutscene >= 60 && contador_troca_cutscene < 70)
					SDL_RenderCopy(renderer, nave_cutscene_final3, NULL, &nave_cutscene_final);
				
				if(contador_troca_cutscene >= 70 && contador_troca_cutscene < 80)
					SDL_RenderCopy(renderer, nave_cutscene_final4, NULL, &nave_cutscene_final);
				
				if(contador_troca_cutscene >= 80 && contador_troca_cutscene < 90)
					SDL_RenderCopy(renderer, nave_cutscene_final5, NULL, &nave_cutscene_final);
				
				if(contador_troca_cutscene >= 90 && contador_troca_cutscene < 300)
					SDL_RenderCopy(renderer, nave_cutscene_final6, NULL, &nave_cutscene_final);

				if(contador_troca_cutscene >= 100)
				{
					nave_cutscene_final.x += 5;
				}
	

				contador_troca_cutscene++;
			}
			else
			{
				gamestate = 3;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(1000/60);
		}
	}

	Mix_FreeMusic(music);

	Mix_Quit();
	SDL_Quit();
	return 0;
}



void controlesmenu()
{
	while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
					gamestate = 2;
				}

				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_DOWN:
							if(estado < 4)
								estado += 1;
								break;

						case SDLK_UP:
							if(estado > 1)
								estado--;
								break;
					}
				}
				if(event.type==SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
						
						case SDLK_RETURN:
							if(estado == 1)
							{
								gamestate = 2;
								health = 200;
								contador = 0;
								player.x = 100;
								player.y = 100;
								ponto = 0;
								pontuacao_planetas = 0;
							}
							else if(estado == 2)
							{
								gamestate = 4;
							}
							else if(estado == 3)
							{
								primeira_vez_recordes = 1;
								gamestate = 5;
							}
							else if(estado == 4)
							{
								running = 0;
								gamestate = -1;
							}
							break;
					}
				}
			}
}
void controlesjogo(int *inimigox, int *inimigoy)
{
	Mix_Chunk * somTiro = Mix_LoadWAV("media/sfx/laser1.wav");
	while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				running = 0;
				gamestate = -1;
			}
			if(event.type==SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						if(boolPause==0)
							boolPause=1;
						else if(boolPause==1)
							boolPause=0;
						break;

					case SDLK_BACKSPACE:
						gamestate = 0;
						player.x = 0;
						player.y = 0;
						*inimigox = 500;
						*inimigoy = 500;
						break;

					case SDLK_RSHIFT:
						running = 0;
						gamestate = -1;
						break;

					case SDLK_w:
						velY=-SpeedP1;
						sprite++;
						if(invulneravel!=1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneAccUp;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneAcc2Up;
						}
						else if(invulneravel==1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneShieldAccUp;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneShieldAcc2Up;
						}
						break;

					case SDLK_s:
						velY=SpeedP1;
						sprite++;
						if(invulneravel!=1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneAccDown;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneAcc2Down;
						}
						else if(invulneravel==1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneShieldAccDown;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneShieldAcc2Down;
						}
						break;

					case SDLK_d:
						velX=SpeedP1;
						sprite++;
						if(invulneravel!=1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneAccRight;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneAcc2Right;
						}
						else if(invulneravel==1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneShieldAccRight;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneShieldAcc2Right;
						}
						break;

					case SDLK_a:
						velX=-SpeedP1;
						sprite++;
						if(invulneravel!=1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneAccLeft;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneAcc2Left;
						}
						else if(invulneravel==1)
						{
							if(sprite%2==0)
								PlayerOne=PlayerOneShieldAccLeft;
							else if(sprite%2!=0)
								PlayerOne=PlayerOneShieldAcc2Left;
						}
						break;

					case SDLK_RIGHT:
						Tiro1 = Tiro1Right;
						Mix_VolumeChunk(somTiro, 64);
						Mix_PlayChannel(-1, somTiro, 0);
						for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
						{
							if(bullet[contadortiro].ativo == 1)
								bullet[contadortiro].ativo = 1;								
							else
							{
								bullet[contadortiro].ativo = 1;
								bullet[contadortiro].tiro_frame.x = player.x + 25; 
								bullet[contadortiro].tiro_frame.y = player.y + 28;
								bullet[contadortiro].TvelX = 5;
								break;
							}
						}

						break;
						
					case SDLK_LEFT:
						Tiro1 = Tiro1Left;
						Mix_VolumeChunk(somTiro, 64);
						Mix_PlayChannel(-1, somTiro, 0);
						for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
						{
							if(bullet[contadortiro].ativo == 1)
								bullet[contadortiro].ativo = 1;
							else
							{
								bullet[contadortiro].ativo = 1;
								bullet[contadortiro].tiro_frame.x = player.x + 25; 
								bullet[contadortiro].tiro_frame.y = player.y + 28;
								bullet[contadortiro].TvelX = -5;
								break;
							}
						}
						break;
						
					case SDLK_UP:
						Tiro1 = Tiro1Up;
						Mix_VolumeChunk(somTiro, 64);
						Mix_PlayChannel(-1, somTiro, 0);
						for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
						{
							if(bullet[contadortiro].ativo == 1)
								bullet[contadortiro].ativo = 1;
							else
							{
								bullet[contadortiro].ativo = 1;
								bullet[contadortiro].tiro_frame.x = player.x + 25; 
								bullet[contadortiro].tiro_frame.y = player.y + 28;
								bullet[contadortiro].TvelY = -5;
								break;
							}
						}
						break;

					case SDLK_DOWN:
						Tiro1 = Tiro1Down;
						Mix_VolumeChunk(somTiro, 64);
						Mix_PlayChannel(-1, somTiro, 0);
						for(contadortiro = 0; contadortiro < MAXTIRO; contadortiro++)
						{
							if(bullet[contadortiro].ativo == 1)
								bullet[contadortiro].ativo = 1;
							else
							{
								bullet[contadortiro].ativo = 1;
								bullet[contadortiro].tiro_frame.x = player.x + 25; 
								bullet[contadortiro].tiro_frame.y = player.y + 28;
								bullet[contadortiro].TvelY = 5;
								break;
							}
						}
						break;
					
					default:
						break;
				}
			}
			if(event.type==SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						if(boolPause==0)
						{
							velX=0;
							velY=0;
							evelY=0;
							evelY=0;
							pause.x=999;
							pause.y=999;
						}

						if(boolPause==1)
						{
							velX=pauseVelX;
							velY=pauseVelY;
							evelX=pauseEvelX;
							evelY=pauseEvelY;
							pause.x=0;
							pause.y=0;
						}										
						break;

					case SDLK_w:
						velY=-1;
						if(invulneravel!=1)
							PlayerOne=PlayerOneUp;
						else if(invulneravel==1)
							PlayerOne=PlayerOneShieldUp;
						break;

					case SDLK_RETURN:
							velX=pauseVelX;
							velY=pauseVelY;
							evelX=pauseEvelX;
							evelY=pauseEvelY;
							break;

					case SDLK_s:
						velY=1;
						if(invulneravel!=1)
							PlayerOne=PlayerOneDown;
						else if(invulneravel==1)
							PlayerOne=PlayerOneShieldDown;
						break;

					case SDLK_d:
						velX=1;
						if(invulneravel!=1)
							PlayerOne=PlayerOneRight;
						else if(invulneravel==1)
							PlayerOne=PlayerOneShieldRight;
						break;

					case SDLK_a:
						velX=-1;
						if(invulneravel!=1)
							PlayerOne=PlayerOneLeft;
						else if(invulneravel==1)
							PlayerOne=PlayerOneShieldLeft;
						break;


					default:
						break;
				}
			}
		}
}

int sort_nomes(void)
{
	int contador_sorteio, quantidade_letras, silaba_sorteada;
	char silabas[32][5] = {"ba", "ta", "be", "ce", "su", "bla", "cri", "pe", "pro", "do", "po", "pru", "le", "la", "ra", "ro", "ri", "ci", "pra", "flu", "fla", "ma", "va", "no", "bra", "nox", "gu", "ji", "xo", "se", "for", "hum"};
	time_t t;

	srand((unsigned) time(&t));

	quantidade_letras = rand()%5;

	if(quantidade_letras < 2)
		quantidade_letras = 2;

	for(contador_sorteio = 0; contador_sorteio < quantidade_letras; contador_sorteio++)
	{
		silaba_sorteada = rand()%32;

		if(contador_sorteio == 0)
		{
			sprintf(nome_planeta, "%s", silabas[silaba_sorteada]);
		}
		else
		{
			sprintf(nome_planeta, "%s%s", nome_planeta, silabas[silaba_sorteada]);
		}
	}

	nome_planeta[0] = nome_planeta[0] + 'A' - 'a';

	return 0;
}

int recordes_list(void)
{
	int contador_recordes;

	FILE * arquivo_recordes;
	arquivo_recordes = fopen("media/recordes.txt", "r");

	for(contador_recordes = 0; contador_recordes < 3; contador_recordes++)
	{
		fscanf(arquivo_recordes, "%s %d %d\n", recordes_nomes[contador_recordes], &recordes_pontos[contador_recordes], &recordes_planetas[contador_recordes]);
	}

	return 0;
}

int calcular_recorde(int nova_pontuacao, int pontos_planetas)
{
	int contador;

	for(contador = 0; contador < 3; contador++)
	{
		if(pontos_planetas > recordes_planetas[contador])
		{
			return 1;
		}
		else if(pontos_planetas == recordes_planetas[contador])
		{
			if(nova_pontuacao > recordes_pontos[contador])
			{
				return 1;
			}
		}
	}

	return 0;
}

void organizar_recordes(int pontos, int pontos_planetas)
{
	int contador_recordes, contador_recordes2, contador_recordes3, recordes[4], planetas[3], recordes_troca, planetas_troca;
	char nomes[4][20], nomes_troca[20];

	FILE * arquivo_recordes;
	arquivo_recordes = fopen("media/recordes.txt", "r");

	sprintf(nomes[3], "%s", nome_jogador);
	recordes[3] = pontos;
	planetas[3] = pontos_planetas;

	for(contador_recordes = 0; contador_recordes < 3; contador_recordes++)
	{
		fscanf(arquivo_recordes, "%s %d %d", nomes[contador_recordes], &recordes[contador_recordes], &planetas[contador_recordes]);
	}

	for(contador_recordes = 3; contador_recordes >= 0; contador_recordes--) // Verifica qual é o menor recorde
	{
		for(contador_recordes2 = 0; contador_recordes2 < contador_recordes; contador_recordes2++)
		{
			if(planetas[contador_recordes2] > planetas[contador_recordes2 + 1])
			{
					recordes_troca = recordes[contador_recordes2];
					recordes[contador_recordes2] = recordes[contador_recordes2 + 1];
					recordes[contador_recordes2 + 1] = recordes_troca;

					planetas_troca = planetas[contador_recordes2];
					planetas[contador_recordes2] = planetas[contador_recordes2 + 1];
					planetas[contador_recordes2 + 1] = planetas_troca;


					for(contador_recordes3 = 0; nomes[contador_recordes2][contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes_troca[contador_recordes3] = nomes[contador_recordes2][contador_recordes3];
					}

					nomes_troca[contador_recordes3] = '\0';

					for(contador_recordes3 = 0; nomes[contador_recordes2 + 1][contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes[contador_recordes2][contador_recordes3] = nomes[contador_recordes2 + 1][contador_recordes3];
					}

					nomes[contador_recordes2][contador_recordes3] = '\0';

					for(contador_recordes3 = 0; nomes_troca[contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes[contador_recordes2 + 1][contador_recordes3] = nomes_troca[contador_recordes3];
					}

					nomes[contador_recordes2 + 1][contador_recordes3] = '\0';
			}
			else
			{
				if(recordes[contador_recordes2] > recordes[contador_recordes2 + 1])
				{
					recordes_troca = recordes[contador_recordes2];
					recordes[contador_recordes2] = recordes[contador_recordes2 + 1];
					recordes[contador_recordes2 + 1] = recordes_troca;

					planetas_troca = planetas[contador_recordes2];
					planetas[contador_recordes2] = planetas[contador_recordes2 + 1];
					planetas[contador_recordes2 + 1] = planetas_troca;


					for(contador_recordes3 = 0; nomes[contador_recordes2][contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes_troca[contador_recordes3] = nomes[contador_recordes2][contador_recordes3];
					}

					nomes_troca[contador_recordes3] = '\0';

					for(contador_recordes3 = 0; nomes[contador_recordes2 + 1][contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes[contador_recordes2][contador_recordes3] = nomes[contador_recordes2 + 1][contador_recordes3];
					}

					nomes[contador_recordes2][contador_recordes3] = '\0';

					for(contador_recordes3 = 0; nomes_troca[contador_recordes3] != '\0'; contador_recordes3++)
					{
						nomes[contador_recordes2 + 1][contador_recordes3] = nomes_troca[contador_recordes3];
					}

					nomes[contador_recordes2 + 1][contador_recordes3] = '\0';
				}
			}
		}
	}

	printf("\n");

	fclose(arquivo_recordes);

	FILE * novo_arquivo_recordes;
	novo_arquivo_recordes = fopen("media/recordes.txt", "w");

	for(contador_recordes = 3; contador_recordes >= 0; contador_recordes--) // DEBUG
	{
		fprintf(novo_arquivo_recordes, "%s %d %d\n", nomes[contador_recordes], recordes[contador_recordes], planetas[contador_recordes]);
	}

	fclose(novo_arquivo_recordes);
}

void controles_recorde(void)
{
	while(SDL_PollEvent(&event))
			{
				if(event.type==SDL_QUIT)
				{
					running = 0;
					gamestate = 2;
				}

				if(event.type==SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_DOWN:
							if(estado_recorde < 4)
								estado_recorde += 1;
								break;

						case SDLK_UP:
							if(estado_recorde > 1)
								estado_recorde--;
								break;
					}
				}
				if(event.type==SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
						
						case SDLK_RETURN:
							if(estado_recorde == 1)
							{
								sprintf(nome_jogador, "PRO");
								gamestate = 7;
								primeira_vez_final_recordes = 1;
							}
							else if(estado_recorde == 2)
							{
								sprintf(nome_jogador, "KEY");
								gamestate = 7;
								primeira_vez_final_recordes = 1;
							}
							else if(estado_recorde == 3)
							{
								sprintf(nome_jogador, "YOU");
								gamestate = 7;
								primeira_vez_final_recordes = 1;
							}
							else if(estado_recorde == 4)
							{
								sprintf(nome_jogador, "MAD");
								gamestate = 7;
								primeira_vez_final_recordes = 1;
							}
							break;
					}
				}
			}
}