/*
    課題
*/
#include <stdio.h>
#include <time.h>
#include <handy.h>
#define FILE_NAME "dot.png"
typedef struct RGBColor{
    int R,G,B;
} RGBColor;
RGBColor color[25] = {};
void fileOpen();
// 初期準備関係
int startStatus(int main);
int startMouseEvent(int main);
// 新規関係
void newGrid(int main);
long sTime();
long fileName();
void saveDotsFile(int dots[32][32], long tName);
void setSelectDotNum();
int selectDotNum();
int setColorWindow(int main,int settingColor,int col);
// 設定関係
void setting(int main);
void openSettingWindow(int main);
void backendSetting(int main);
void colorWrite();

int main(){
    int main,
        widStatus;
    fileOpen();
    main = HgOpen(800,800);
    while (1) {
        widStatus = startStatus(main);
        if (widStatus == 0) {
            newGrid(main);
        }
        else if (widStatus == 1) {
            printf("編集作業\n");
            break;
        }
        else if (widStatus == 2) {
            setting(main);
        }
    }
    HgClose();
    return 0;
}
// 色情報の読み込み
void fileOpen(){
    FILE *fp;
    int i;
    fp = fopen("color.txt", "r");
    if (fp == NULL) {
        printf("カラー情報を開けませんでした\n");
    }
    else {
        printf("カラー情報を開きました\n");
    }
    for (i = 0; i < 25; i++) {
        fscanf(fp, "%d", &color[i].R);
        fscanf(fp, "%d", &color[i].G);
        fscanf(fp, "%d", &color[i].B);
    }
    fclose(fp);
    printf("カラー情報を読み込みました\n");
}
// 初期ウィンドウ描画
int startStatus(int main){
    int widStatus;
    // 各ボタン描画
    HgSetFont(HG_UTF8_CODE, 50);
    HgBox(50,400,300,120);
    HgText(150,425,"新規");
    HgBox(450,400,300,120);
    HgText(550,425,"編集");
    HgBox(50,150,700,120);
    HgText(310,175,"設定画面");
    // 初期ボタンクリックイベント
    widStatus = startMouseEvent(main);
    return widStatus;
}
// 初期ウィンドウクリックイベント
int startMouseEvent(int main){
    int widStatus = -1,
        x,y;
    hgevent *event;
    HgSetEventMask(HG_MOUSE_DOWN);
    for(;;){
        event = HgEvent();
        x = event->x;
        y = event->y;
        // 作成ボタンクリック
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
//
// 新規関係
//
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
        endFlag = 0;
    long startTime, endTime,
         tName;
    char fName[30];
    // ドット情報初期化
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            dots[i][j] = -1;
        }
    }
    // ウィンドウ準備
    draw1 = HgWAddLayer(main);
    draw2 = HgWAddLayer(main);
    box   = HgWAddLayer(main);
    // マス目数指定表示
    setSelectDotNum();
    // マス目数クリックイベント
    l = selectDotNum();
    // 開始時間
    startTime = sTime();
    // ファイル名作成
    tName = fileName();

    dotLong = 800 / dotNum[l];
    // boxに線を描く
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
    col = setColorWindow(main,settingColor,col);
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
// 開始時間
long sTime(){
    long startTime;
    time(&startTime);
    return startTime;
}
// ファイル名作成
long fileName(){
    time_t timer;
    struct tm *local;
    long Name;
    /* 現在時刻を取得 */
    timer = time(NULL);
    local = localtime(&timer); /* 地方時に変換 */
    Name = (local->tm_year+1900)*10000000000 + (local->tm_mon+1)*100000000 + (local->tm_mday)*1000000 + (local->tm_hour)*10000 + (local->tm_min)*100 + (local->tm_sec);
    return Name;
}
// ドット情報保存
void saveDotsFile(int dots[32][32], long tName){
    FILE *fp3;
    int i,j;
    char dotName[30];
    sprintf(dotName, "dats/%ld.dat",tName);
    fp3 = fopen(dotName, "w+");
    if (fp3 == NULL) {
        //
    }
    else{
        //
    }
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            fprintf(fp3, "%d\n", dots[i][j]);
        }
    }
    fclose(fp3);
    printf("ドット情報を保存しました\n");
}
// マス目数選択画面描画
void setSelectDotNum(){
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
int selectDotNum(){
    int l,
        x,y;
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
int setColorWindow(int main, int setting, int col){
    int i,j,k;
    // サンプルの色表示
    k = 0;
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
//
// 設定関係
//
void setting(int main){
    HgSetWidth(1);
    openSettingWindow(main);
    backendSetting(main);
}
void openSettingWindow(int main){
    int i,j;
    HgBox(50,600,700,120);
    HgSetFont(HG_UTF8_CODE, 50);
    HgText(310,625,"設定画面");
    // 色用の空箱
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            HgBox(50+120*j, 530-40*i, 100, 30);
        }
    }
    // 赤
    HgSetFillColor(HG_RED);
    HgBoxFill(50,80,100,256,0);
    // 緑
    HgSetFillColor(HG_GREEN);
    HgBoxFill(170,80,100,256,0);
    // 青
    HgSetFillColor(HG_BLUE);
    HgBoxFill(290,80,100,256,0);
    // 戻るボタン
    HgBox(420, 80, 330, 110);
    HgText(540,100,"戻る");
    // 決定ボタン
    HgBox(580,220,170,80);
    HgText(620,225,"決定");
}
void backendSetting(int main){
    int x,y,
        i,j,k,
        layColorR,layColorG,layColorB,
        nowR,nowG,nowB,
        selectColor,makeColor,manyColor,
        setColor;
    float R,G,B;
    layColorR = HgWAddLayer(main);
    layColorG = HgWAddLayer(main);
    layColorB = HgWAddLayer(main);
    selectColor = HgWAddLayer(main);
    makeColor = HgWAddLayer(main);
    manyColor = HgWAddLayer(main);
    // カラーボックス塗り
    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            HgWSetFillColor(manyColor, HgRGB((float)color[k].R/255, (float)color[k].G/255, (float)color[k].B/255));
            HgWBoxFill(manyColor, 50+120*j, 530-40*i, 100,30,0);
            k++;
        }
    }
    HgSetEventMask(HG_MOUSE_DOWN | HG_MOUSE_DRAG);
    for(;;){
        hgevent *event = HgEvent();
        // クリック操作
        if (event->type == HG_MOUSE_DOWN) {
            x = event->x;
            y = event->y;
            // 戻るボタンクリック
            if ((420<x&&x<750) && (80<y&&y<190)) {
                printf("戻るボタンクリック\n");
                HgLClear(layColorR);
                HgLClear(layColorG);
                HgLClear(layColorB);
                HgLClear(selectColor);
                HgLClear(makeColor);
                HgLClear(manyColor);
                HgClear();
                break;
            }
            // 決定ボタンクリック
            else if ((580<x&&x<750) && (220<y&&y<300)) {
                color[setColor].R = R;
                color[setColor].G = G;
                color[setColor].B = B;
                k = 0;
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 6; j++) {
                        HgWSetFillColor(manyColor, HgRGB((float)color[k].R/255, (float)color[k].G/255, (float)color[k].B/255));
                        HgWBoxFill(manyColor, 50+120*j, 530-40*i, 100,30,0);
                        k++;
                    }
                }

                colorWrite();
            }
            // 各色をクリック
            k=0;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 6; j++) {
                    if ((50+120*j<x&&x<(50+120*j)+100) && ((530-40*i)<y&&y<(530-40*i)+30)) {
                        HgLClear(selectColor);
                        HgWSetWidth(selectColor,5);
                        HgWBox(selectColor, 50+120*j, 530-40*i, 100, 30);
                        // printf("(%d, %d)\n", i,j);
                        setColor = k;
                        nowR = color[setColor].R + 80;
                        nowG = color[setColor].G + 80;
                        nowB = color[setColor].B + 80;
                        R = color[setColor].R;
                        G = color[setColor].G;
                        B = color[setColor].B;
                        // printf("(%d, %d, %d)\n", nowR,nowG,nowB);

                        // カラーピッカーに線を描く
                        HgLClear(layColorR);
                        HgLClear(layColorG);
                        HgLClear(layColorB);
                        HgLClear(makeColor);
                        HgWLine(layColorR, 45,nowR,155,nowR);
                        HgWLine(layColorG, 165,nowG,275,nowG);
                        HgWLine(layColorB, 285,nowB,395,nowB);
                        HgWText(layColorR, 50,80,"%d",color[setColor].R);
                        HgWText(layColorG, 170,80,"%d",color[setColor].G);
                        HgWText(layColorB, 290,80,"%d",color[setColor].B);
                        // 完成後の色を描く
                        HgWSetFillColor(makeColor, HgRGB(((float)nowR-80)/255, ((float)nowG-80)/255, ((float)nowB-80)/255));
                        HgWBoxFill(makeColor, 420,220,100,100,0);
                    }
                    k++;
                }
            }
            // 使える色クリックここまで
        }
        // ドラッグ操作
        else if (event->type == HG_MOUSE_DRAG) {
            x = event->x;
            y = event->y;
            // Rの中
            if ((50<x&&x<150) && (80<=y&&y<336)) {
                R = y - 80;
                HgLClear(layColorR);
                HgWLine(layColorR, 45,R+80,155,R+80);
                HgWText(layColorR, 50,80,"%d",(int)R);
                HgLClear(makeColor);
                HgWSetFillColor(makeColor, HgRGB(R/255,G/255,B/255));
                HgWBoxFill(makeColor, 420,220,100,100,0);
            }
            // Gの中
            if ((170<x&&x<270) && (80<=y&&y<336)) {
                G = y - 80;
                HgLClear(layColorG);
                HgWLine(layColorG, 165,G+80,275,G+80);
                HgWText(layColorG, 170,80,"%d",(int)G);
                HgLClear(makeColor);
                HgWSetFillColor(makeColor, HgRGB(R/255,G/255,B/255));
                HgWBoxFill(makeColor, 420,220,100,100,0);
            }
            // Bの中
            if ((290<x&&x<390) && (80<=y&&y<336)) {
                B = y - 80;
                HgLClear(layColorB);
                HgWLine(layColorB, 285,B+80,395,B+80);
                HgWText(layColorB, 290,80,"%d",(int)B);
                HgLClear(makeColor);
                HgWSetFillColor(makeColor, HgRGB(R/255,G/255,B/255));
                HgWBoxFill(makeColor, 420,220,100,100,0);
            }
            //
        }
    }
}
// カラー情報保存
void colorWrite(){
    FILE *fp2;
    int i,j;
    fp2 = fopen("color.txt", "w");
    if (fp2 == NULL) {
        printf("カラー情報再読み込み失敗\n");
    }
    else {
        printf("カラー情報再読み込み\n");
    }
    for (i = 0; i < 25; i++) {
        fprintf(fp2, "%d\n", color[i].R);
        fprintf(fp2, "%d\n", color[i].G);
        fprintf(fp2, "%d\n", color[i].B);
    }
    fclose(fp2);
    printf("カラー情報編集完了\n");
}
