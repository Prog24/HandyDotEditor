#include <stdio.h>
#include <time.h>
#include <handy.h>

#define FILE_NAME "dot.png"

typedef struct RGBColor{
    int R,G,B;
} RGBColor;
RGBColor color[25] = {};

void getColorData();
void saveColorData();
int startMouseEvent(int main);
int renderStartWindow(int main);
void renderSelectDotNum();
int selectDotNum();
long getTime();
long makeFileName();
int renderSelectColorWindow(int main, int setting, int col);

void saveDotsFile(int dots[32][32], long tName);

int main(){
    // メインウィンドウ
    int main;
    int widStatus;
    getColorData();
    main = HgOpen(800,800);
    while(1){
        widStatus = startMouseEvent(main);
        if(widStatus == 0){
            renderStartWindow(main);
        }else if(widStatus == 1){
            printf("再編集(未実装)\n");
            break;
        }else if(widStatus == 2){
            // setting(main);
        }
    }
    HgClose();
    return 0;
}

/**
 * 色情報の読み込み
 */
void getColorData(){
    FILE *fp;
    int i;
    fp = fopen("color.txt", "r");
    if(fp == NULL) {
        printf("[error] not open color.txt\n");
    }else{
        // printf("カラー情報を読み込みます\n");
    }
    // カラー情報読み込み
    for(i=0; i<25; i++){
        fscanf(fp, "%d", &color[i].R);
        fscanf(fp, "%d", &color[i].G);
        fscanf(fp, "%d", &color[i].B);
    }
    fclose(fp);
    // printf("カラー情報を読み込み終えました")
}

/**
 * カラー情報保存
 */
void saveColorData(){
    FILE *fp2;
    int i,j;
    fp2 = fopen("color.txt", "w");
    if(fp2 == NULL){
        printf("[error] not open color.txt\n");
    }else{
        //  printf("[success] open color.txt\n");
    }
    for(i=0; i<25; i++){
        fprintf(fp2, "%d\n", color[i].R);
        fprintf(fp2, "%d\n", color[i].G);
        fprintf(fp2, "%d\n", color[i].B);
    }
    fclose(fp2);
    //  printf("[success] save color.txt\n");
}

 /**
  * 初期ウィンドウ描画
  */
int renderStartWindow(int main){
    int widStatus;
    // 各ボタン描画
    HgSetFont(HG_UTF8_CODE, 50);
    HgBox(50,400,300,120);
    HgText(150,425,"新規");
    HgBox(450,400,300,120);
    HgText(550,425,"編集");
    HgBox(50,150,700,120);
    HgText(310,175,"設定画面");
    // 初期ウィンドウボタンイベント
    widStatus = startMouseEvent(main);
    return widStatus;
}

/**
 * 初期画面でのクリックイベント
 */
int startMouseEvent(int main){
    int widStatus = -1;
    int x,y;
    hgevent * event;
    HgSetEventMask(HG_MOUSE_DOWN);
    for(;;){
        event = HgEvent();
        x = event->x;
        y = event->y;
        // 作成ボタン
        if ((50<x&&x<350)&&(400<y&&y<520)) {
            widStatus = 0;
            break;
        }
        // 編集ボタンクリック
        else if ((450<x&&x<750)&&(400<y&&y<520)) {
            widStatus = 1;
            break;
        }
        // 設定ボタンクリック
        else if ((50<x&&x<750)&&(150<y&&y<270)) {
            widStatus = 2;
            break;
        }
    }
    HgClear();
    return widStatus;
}

/**
 * 新規作成画面
 */
void newGrid(int main){
    int draw1,draw2,
        box,settingColor,col,
        dots[32][32],
        i,j,k,
        x,y,
        n=0,
        l,
        dotNum[3]={8,16,32},
        dotLong,
        endFlag=0;
    long startTime, endTime,
         tName;
    char fName[30];
    // ドット情報初期化
    for(i=0;i<32;i++){
        for(j=0;j<32;j++){
            dots[i][j]=-1;
        }
    }
    // ウィンドウ準備
    draw1 = HgWAddLayer(main);
    draw2 = HgWAddLayer(main);
    box   = HgWAddLayer(main);
    // マス目数指定表示
    renderSelectDotNum();
    // マス目数クリックイベント
    l = selectDotNum();
    // 開始時間
    startTime = getTime();
    // ファイル名作成
    tName = makeFileName();
    // マス目1辺の長さ
    dotLong = 800 / dotNum[l];

    // boxにマス目を描く
    HgClear();
    HgWSetWidth(box,1);
    for (i = 0; i < dotNum[l]-1; i++) {
        HgWLine(box, 0, dotLong+dotLong*i, 800, dotLong+dotLong*i);
        HgWLine(box, dotLong+dotLong*i, 0, dotLong+dotLong*i, 800);
    }
    // 色設定表示
    settingColor = HgWOpen(50,50,600,500);
    col = HgWAddLayer(settingColor);
    // カラーウィンドウ準備
    col = renderSelectColorWindow(main, settingColor, col);
    // エディタ動作関係
    HgSetEventMask(HG_MOUSE_DOWN | HG_KEY_DOWN);
    for(;;){
        hgevent *event = HgEvent();
        if (event->type == HG_KEY_DOWN) {
            switch (event->ch) {
                case '1':
                    n=0;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col,25,420,80,20);
                    break;
                case '2':
                    n=1;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col,115,420,80,20);
                    break;
                case '3':
                    n=2;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 205,420,80,20);
                    break;
                case '4':
                    n=3;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 295,420,80,20);
                    break;
                case '5':
                    n=4;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 385,420,80,20);
                    break;
                case '6':
                    n=5;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 475,420,80,20);
                    break;
                case 'q':
                    n=6;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 25,390,80,20);
                    break;
                case 'w':
                    n=7;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 115,390,80,20);
                    break;
                case 'e':
                    n=8;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 205,390,80,20);
                    break;
                case 'r':
                    n=9;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 295,390,80,20);
                    break;
                case 't':
                    n=10;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 385,390,80,20);
                    break;
                case 'y':
                    n=11;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 475,390,80,20);
                    break;
                case 'a':
                    n=12;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 25,360,80,20);
                    break;
                case 's':
                    n=13;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 115,360,80,20);
                    break;
                case 'd':
                    n=14;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 205,360,80,20);
                    break;
                case 'f':
                    n=15;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 295,360,80,20);
                    break;
                case 'g':
                    n=16;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 385,360,80,20);
                    break;
                case 'h':
                    n=17;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 475,360,80,20);
                    break;
                case 'z':
                    n=18;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 25,330,80,20);
                    break;
                case 'x':
                    n=19;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 115,330,80,20);
                    break;
                case 'c':
                    n=20;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 205,330,80,20);
                    break;
                case 'v':
                    n=21;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 295,330,80,20);
                    break;
                case 'b':
                    n=22;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 385,330,80,20);
                    break;
                case 'n':
                    n=23;
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col, 475,330,80,20);
                    break;
                case 0x20:
                    HgLClear(col);
                    HgWSetColor(col,HG_BLACK);
                    HgWBox(col,150,250,300,50);
                    n=-1;
                    break;
                case 0x09:
                    time(&endTime);
                    endTime = endTime - startTime;
                    printf("かかった時間 : %ld\n", endTime);
                    sprintf(fName, "img/%ld", tName);
                    HgLSave(draw2, fName);
                    saveDotsFile(dots, tName);
                    break;
                case 0x7f:
                    HgLClear(draw2);
                    for (i = 0; i < dotNum[l]; i++) {
                        for (j = 0; j < dotNum[l]; j++) {
                            dots[i][j] = -1;
                        }
                    }
                    break;
                case 0x1b:
                    endFlag = 1;
            }
        }
        //
        else if (event->type == HG_MOUSE_DOWN) {
            x = event->x;
            y = event->y;
            //
            for (i = 0; i < dotNum[l]; i++) {
                for (j = 0; j < dotNum[l]; j++) {
                    if ((0+dotLong*j)<x && x<(dotLong+dotLong*j) && ((800-dotLong)-dotLong*i)<y && y<(800-dotLong*i)) {
                        dots[i][j] = n;
                    }
                }
            }
            //
            // 描く１
            for (i = 0; i < dotNum[l]; i++) {
                for (j = 0; j < dotNum[l]; j++) {
                    for (k = 0; k < 25; k++) {
                        if (dots[i][j] == -1) {
                            // 何もしない
                        }
                        else if (dots[i][j] == k) {
                            HgWSetFillColor(draw1, HgRGB((float)color[k].R/255, (float)color[k].G/255, (float)color[k].B/255));
                            HgWBoxFill(draw1, 0+dotLong*j, (800-dotLong)-dotLong*i, dotLong, dotLong, 0);
                            k++;
                        }
                    }
                }
            }
            //
            HgLClear(draw2);
            //
            // 描く２
            for (i = 0; i < dotNum[l]; i++) {
                for (j = 0; j < dotNum[l]; j++) {
                    for (k = 0; k < 25; k++) {
                        if (dots[i][j] == -1) {
                            // 何もしない
                        }
                        else if (dots[i][j] == k) {
                            HgWSetFillColor(draw2, HgRGB((float)color[k].R/255, (float)color[k].G/255, (float)color[k].B/255));
                            HgWBoxFill(draw2, 0+dotLong*j, (800-dotLong)-dotLong*i, dotLong, dotLong, 0);
                        }
                    }
                }
            }
            //
            HgLClear(draw1);
        }
        //
        if (endFlag == 1) {
            HgLClear(draw1);
            HgLClear(draw2);
            HgLClear(box);
            HgWClose(settingColor);
            break;
        }
    }
}

/**
 * マス目数選択画面描画
 */
void renderSelectDotNum(){
    HgSetWidth(3);
    HgBox(214,70,400,80);
    HgBox(214,170,400,80);
    HgBox(214,270,400,80);
    HgSetFont(HG_UTF8_CODE, 50);
    HgText(350,80,"8 × 8");
    HgText(330,180,"16 × 16");
    HgText(330,280,"32 × 32");
    HgSetFont(HG_UTF8_CODE, 30);
    HgText(160,380,"下記から描くマス目を選んでください");
}

/**
 * マス目選択
 */
int selectDotNum(){
    int l,x,y;
    hgevent *event;
    HgSetEventMask(HG_MOUSE_DOWN);
    for(;;){
        event = HgEvent();
        x = event->x;
        y = event->y;
        if (214<x&&x<614 && 70<y&&y<150) {
            l = 0;
            break;
        }
        else if (214<x&&x<614 && 170<y&&y<250) {
            l = 1;
            break;
        }
        else if (214<x&&x<614 && 270<y&&y<350) {
            l = 2;
            break;
        }
    }
    return l;
}

/**
 * 時間取得
 */
long getTime(){
    long startTime;
    return time(&startTime);
}

/**
 * ファイル名作成
 */
long makeFileName(){
    time_t timer;
    struct tm *local;
    long name;
    /* 現在時刻を取得 */
    timer = time(NULL);
    local = localtime(&timer); /* 地方時に変換 */
    name = (local->tm_year+1900)*10000000000 + (local->tm_mon+1)*100000000 + (local->tm_mday)*1000000 + (local->tm_hour)*10000 + (local->tm_min)*100 + (local->tm_sec);
    return name;
}

/**
 * カラーウィンドウ表示
 */
int renderSelectColorWindow(int main, int setting, int col){
    int i,j,k;
    // サンプルの色表示
    k=0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            HgWSetFillColor(1, HgRGB((float)color[k].R/255, (float)color[k].G/255, (float)color[k].B/255));
            HgWBoxFill(1, 25+90*j, 420-30*i, 80, 20, 1);
            k++;
        }
    }
    // １つめを囲む
    HgWSetWidth(col, 5);
    HgWSetColor(col,HG_BLACK);
    HgWBox(col, 25,420,80,20);
    // 透明ボタン表示
    HgWBox(setting, 150,250,300,50);
    HgWSetFont(setting, HG_UTF8_CODE, 40);
    HgWText(setting, 270,250,"透明");
    // 使い方
    HgWSetFont(setting, HG_UTF8_CODE, 27);
    HgWText(setting,30,10,"<<使い方>>\n・色の変更はキー入力で行う(1→左上の色)\n・スペースキーは透明色\n・deleteキーで今まで書いたドット全てを削除\n・tabキーを押すと描いたドットを保存する\n\t\t\t\t\t\t\t\t\t\t\t\t(ping形式で保存)\n・Escキーで終了");

    HgWSetTitle(main,"main");
    HgWSetTitle(setting,"setting");
    return col;
}


/**
 * ドット情報保存
 */
void saveDotsFile(int dots[32][32], long tName){
    FILE *fp3;
    int i,j;
    char dotName[30];
    sprintf(dotName, "dats/%ld.dat",tName);
    fp3 = fopen(dotName, "w+");
    if (fp3 == NULL) {
        // printf("[error] not open file\n");
    }
    else{
        // printf("[success] open file\n");
    }
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            fprintf(fp3, "%d\n", dots[i][j]);
        }
    }
    fclose(fp3);
    // printf("[success] save file\n");
}