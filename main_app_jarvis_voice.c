#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

/* ── Windows platform headers ── */
#include <windows.h>      /* Sleep, HANDLE, console, BOOL, DWORD     */
#include <conio.h>        /* _getch, _kbhit                           */

// ===== ALL MACROS (consolidated - no duplicates) =====

// Quiz / game counts
#define TOTAL_Q          58
#define QUESTIONS_PER_RUN 10
#define TOTAL            50
#define ASK              10
#define OPTIONS          4
#define FULL_MARKS       50

// Typing speed test
#define MAX              300
#define TOTAL_SENTENCES  20
#define MAX_WORDS        50

// Snake game
#define WIDTH            60
#define HEIGHT           20

// Platform-independent clear
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Base ANSI colors
#define RED      "\033[1;31m"
#define ORANGE   "\033[38;5;208m"
#define YELLOW   "\033[1;33m"
#define GREEN    "\033[1;32m"
#define BLUE     "\033[1;34m"
#define INDIGO   "\033[38;5;54m"
#define VIOLET   "\033[1;35m"
#define CYAN     "\033[1;36m"
#define RESET    "\033[0m"
#define MAGENTA  "\033[1;35m"

// Tollywood quiz colors
#define BOLD       "\033[1m"
#define DIM        "\033[2m"
#define FG_RED     "\033[91m"
#define FG_GREEN   "\033[92m"
#define FG_YELLOW  "\033[93m"
#define FG_MAGENTA "\033[95m"
#define FG_CYAN    "\033[96m"
#define FG_WHITE   "\033[97m"
#define FG_GOLD    "\033[38;5;220m"
#define FG_ORANGE  "\033[38;5;208m"
#define BG_DARK    "\033[48;5;235m"

// Soft colors for typing speed test
#define SOFT_BLUE    "\033[38;5;111m"
#define SOFT_GREEN   "\033[38;5;120m"
#define SOFT_YELLOW  "\033[38;5;229m"
#define SOFT_PINK    "\033[38;5;218m"
#define SOFT_CYAN    "\033[38;5;159m"
#define SOFT_ORANGE  "\033[38;5;215m"

// Sudoku-specific colors
#define WHITE        "\033[1;37m"
#define BG_SELECT    "\033[48;5;24m"
#define BG_SAME_RC   "\033[48;5;236m"
#define BG_BLOCK     "\033[48;5;234m"

// ===== FUNCTION PROTOTYPES =====
void loadingAnimation();
void removeNewline(char str[]);
int  countWords(char str[]);
void compareText(char original[], char typed[], int *mistakes, int *correct);

typedef struct {
    char question[150];
    char answer[80];
    int level;
} SIQuestion;

void shuffle(int *array, int n)
{
    for(int i=n-1;i>0;i--)
    {
        int j=rand()%(i+1);
        int temp=array[i];
        array[i]=array[j];
        array[j]=temp;
    }
}

void si_quiz()
{
    SIQuestion q[TOTAL] = {

        // EASY (25)
        {"SI unit of Force?","newton",1},
        {"SI unit of Work?","joule",1},
        {"SI unit of Power?","watt",1},
        {"SI unit of Pressure?","pascal",1},
        {"SI unit of Current?","ampere",1},
        {"SI unit of Charge?","coulomb",1},
        {"SI unit of Voltage?","volt",1},
        {"SI unit of Resistance?","ohm",1},
        {"SI unit of Frequency?","hertz",1},
        {"SI unit of Temperature?","kelvin",1},
        {"SI unit of Mass?","kilogram",1},
        {"SI unit of Length?","meter",1},
        {"SI unit of Time?","second",1},
        {"SI unit of Energy?","joule",1},
        {"SI unit of Capacitance?","farad",1},
        {"SI unit of Inductance?","henry",1},
        {"SI unit of Magnetic Field?","tesla",1},
        {"SI unit of Magnetic Flux?","weber",1},
        {"SI unit of Luminous Intensity?","candela",1},
        {"SI unit of Amount of Substance?","mole",1},
        {"SI unit of Area?","square meter",1},
        {"SI unit of Volume?","cubic meter",1},
        {"SI unit of Speed?","meter per second",1},
        {"SI unit of Acceleration?","meter per second square",1},
        {"SI unit of Density?","kilogram per cubic meter",1},

        // HARD (25)
        {"SI unit of Entropy?","joule per kelvin",2},
        {"SI unit of Specific Heat Capacity?","joule per kilogram kelvin",2},
        {"SI unit of Conductance?","siemens",2},
        {"SI unit of Radioactivity?","becquerel",2},
        {"SI unit of Absorbed Dose?","gray",2},
        {"SI unit of Dose Equivalent?","sievert",2},
        {"SI unit of Catalytic Activity?","katal",2},
        {"SI unit of Angular Velocity?","radian per second",2},
        {"SI unit of Angular Acceleration?","radian per second square",2},
        {"SI unit of Plane Angle?","radian",2},
        {"SI unit of Solid Angle?","steradian",2},
        {"SI unit of Surface Tension?","newton per meter",2},
        {"SI unit of Dynamic Viscosity?","pascal second",2},
        {"SI unit of Kinematic Viscosity?","square meter per second",2},
        {"SI unit of Stress?","pascal",2},
        {"SI unit of Heat Flux?","watt per square meter",2},
        {"SI unit of Thermal Conductivity?","watt per meter kelvin",2},
        {"SI unit of Electric Field?","volt per meter",2},
        {"SI unit of Momentum?","kilogram meter per second",2},
        {"SI unit of Impulse?","newton second",2},
        {"SI unit of Torque?","newton meter",2},
        {"SI unit of Electric Power?","watt",2},
        {"SI unit of Specific Volume?","cubic meter per kilogram",2},
        {"SI unit of Pressure Gradient?","pascal per meter",2},
        {"SI unit of Energy Density?","joule per cubic meter",2}
    };

    int mode;
    printf(VIOLET"\n=====================================\n"RESET);
    printf(RED"        S I  U N I T S  Q U I Z\n"RESET);
    printf(ORANGE"=====================================\n"RESET);
    printf(CYAN"1. Easy (MCQ)\n2. Hard (Type Answer)\nChoose Mode: "RESET);
    scanf("%d",&mode);

    if(mode!=1 && mode!=2) return;

    srand(time(NULL));

    int score=0, asked=0, wrong=0;
    int used[TOTAL]={0};

    while(asked < ASK)
    {
        int r = rand()%TOTAL;
        if(used[r] || q[r].level!=mode) continue;

        used[r]=1;
        asked++;

        printf(CYAN"\nQ%d: %s\n"RESET,asked,q[r].question);
        printf(YELLOW"Press 0 = Stop | 1 = Skip\n"RESET);

        if(mode==1)
        {
            char options[OPTIONS][80];
            strcpy(options[0],q[r].answer);

            int count=1;
            while(count<OPTIONS)
            {
                int x=rand()%TOTAL;
                if(q[x].level==1 && strcmp(q[x].answer,q[r].answer)!=0)
                {
                    int dup=0;
                    for(int i=0;i<count;i++)
                        if(strcmp(options[i],q[x].answer)==0)
                            dup=1;

                    if(!dup)
                    {
                        strcpy(options[count],q[x].answer);
                        count++;
                    }
                }
            }

            int order[OPTIONS]={0,1,2,3};
            shuffle(order,OPTIONS);

            char correct='A';

            for(int i=0;i<OPTIONS;i++)
            {
                printf(GREEN"%c) %s\n"RESET,'A'+i,options[order[i]]);
                if(strcmp(options[order[i]],q[r].answer)==0)
                    correct='A'+i;
            }

            char choice;
            printf(BLUE"Your Choice: "RESET);
            scanf(" %c",&choice);
            choice=toupper(choice);

            if(choice=='0') break;

            if(choice=='1')
            {
                printf(BLUE"Skipped! (-1)\n"RESET);
                score-=1;
                continue;
            }

            if(choice==correct)
            {
                printf(GREEN"Correct! (+5)\n"RESET);
                score+=5;
            }
            else
            {
                printf(RED"Wrong! (-2)\n"RESET);
                printf(YELLOW"Correct Answer: %c\n"RESET,correct);
                score-=2;
                wrong++;
            }
        }
        else
        {
            char ans[100];
            printf(BLUE"Answer: "RESET);
            scanf(" %[^\n]",ans);

            if(strcmp(ans,"0")==0) break;

            if(strcmp(ans,"1")==0)
            {
                printf(BLUE"Skipped! (-1)\n"RESET);
                score-=1;
                continue;
            }

            if(strcasecmp(ans,q[r].answer)==0)
            {
                printf(GREEN"Correct! (+5)\n"RESET);
                score+=5;
            }
            else
            {
                printf(RED"Wrong! (-2)\n"RESET);
                printf(YELLOW"Correct: %s\n"RESET,q[r].answer);
                score-=2;
                wrong++;
            }
        }
    }

    if(score<0) score=0;

    printf(VIOLET"\n======================================\n"RESET);
    printf(RED"               RESULT\n"RESET);
    printf(VIOLET"\n======================================\n"RESET);

    printf(CYAN"Total Questions: 10\n"RESET);
    printf(CYAN"Maximum Marks: 50\n"RESET);
    printf(BLUE"Your Score: %d\n"RESET,score);
    printf(RED"Wrong Answers: %d\n"RESET,wrong);

    printf(GREEN"Grade: "RESET);

    if(score>=40)
        printf(GREEN"A\n"RESET);
    else if(score>=25)
        printf(BLUE"B\n"RESET);
    else if(score>=15)
        printf(ORANGE"C\n"RESET);
    else
        printf(RED"D\n"RESET);
}
void genz_quiz()
{
    

    char shortForms[25][15] = {
        "idk","iykyk","aka","brb","tbh",
        "imo","rn","omg","btw","ttyl",
        "fomo","yolo","lmao","rofl","smh",
        "bff","bae","sus","dm","irl",
        "jk","wyd","hbu","np","asap"
    };

    char fullForms[25][60] = {
        "i dont know","if you know you know","also known as","be right back","to be honest",
        "in my opinion","right now","oh my god","by the way","talk to you later",
        "fear of missing out","you only live once","laughing my ass off","rolling on floor laughing","shaking my head",
        "best friends forever","before anyone else","suspicious","direct message","in real life",
        "just kidding","what you doing","how about you","no problem","as soon as possible"
    };

    int used[25] = {0};
    int score = 0, right = 0, wrong = 0;
    char answer[100];

    srand(time(NULL));

    printf(CYAN "\n=========== GENZ QUIZ ===========\n" RESET);
    printf(YELLOW "Correct +5 | Wrong -2 | Skip(0) -1 | Exit(1)\n");
    printf("==================================\n\n" RESET);

    for(int q = 0; q < 10; )
    {
        int index = rand() % 25;

        if(used[index] == 1)
            continue;

        used[index] = 1;
        q++;

        printf(CYAN "Q%d: Full form of '%s' ?\n" RESET, q, shortForms[index]);
        printf("Your answer: ");
        scanf(" %[^\n]", answer);

        if(strcmp(answer,"1")==0)
        {
            printf(RED "\nQuiz exited.\n" RESET);
            break;
        }

        if(strcmp(answer,"0")==0)
        {
            printf(YELLOW "Skipped (-1)\n\n" RESET);
            score -= 1;
            wrong++;
            continue;
        }

        char userLower[100], correctLower[100];
        strcpy(userLower, answer);
        strcpy(correctLower, fullForms[index]);

        for(int i=0; userLower[i]; i++)
            userLower[i] = tolower(userLower[i]);
        for(int i=0; correctLower[i]; i++)
            correctLower[i] = tolower(correctLower[i]);

        if(strcmp(userLower, correctLower) == 0)
        {
            printf(GREEN "Correct! (+5)\n\n" RESET);
            score += 5;
            right++;
        }
        else
        {
            printf(RED "Wrong! (-2)\n" RESET);
            printf("Correct: %s\n\n", fullForms[index]);
            score -= 2;
            wrong++;
        }
    }

    printf(CYAN "\n========= FINAL RESULT =========\n" RESET);
    printf("Right   : %d\n", right);
    printf("Wrong   : %d\n", wrong);
    printf("Score   : %d\n", score);
    printf("================================\n");

    if(score >= 40)
        printf(GREEN "?? Slang Master! Full GenZ vibes!\n" RESET);
    else if(score >= 25)
        printf(YELLOW "?? Nice! You know your slang.\n" RESET);
    else if(score >= 10)
        printf("?? Not bad! Improve a little.\n");
    else
        printf(RED "?? Need more GenZ practice!\n" RESET);
}



// Box-drawing chars for Tollywood banner


#define TL "+"
#define TR "+"
#define BL "+"
#define BR "+"
#define HL "="
#define VL "|"
#define SL "-"







void print_line(const char *color, int width) {
    printf("%s", color);
    for (int i = 0; i < width; i++) printf("%s", HL);
    printf("%s\n", RESET);
}

void print_thin_line(const char *color, int width) {
    printf("%s", color);
    for (int i = 0; i < width; i++) printf("%s", SL);
    printf("%s\n", RESET);
}

void print_banner(void) {
    printf("\n");
    printf(FG_GOLD BOLD "  +");
    for (int i = 0; i < 68; i++) printf("=");
    printf("+\n");

    printf("  |" BG_DARK FG_GOLD BOLD
           "        ** TOLLYWOOD  ULTIMATE  QUIZ **  10 QUESTIONS          "
           RESET FG_GOLD BOLD "|\n");

    printf("  |" DIM FG_GOLD
           "    Stars | Directors | Dialogues | Music | Awards | Films     "
           RESET FG_GOLD BOLD "|\n");

    printf("  +");
    for (int i = 0; i < 68; i++) printf("=");
    printf("+\n" RESET);
    printf("\n");
}

void print_option(char letter, const char *text, const char *fg) {
    printf("  %s%s %c.  %-55s%s\n", BG_DARK, fg, letter, text, RESET);
}

void print_correct_result(void) {
    printf("\n  \033[42m\033[30m" BOLD
           "  [CORRECT!]  Outstanding!                                      "
           RESET "\n");
}

void print_wrong_result(char correct,
                        const char *ca, const char *cb,
                        const char *cc, const char *cd) {
    const char *ans_text =
        (correct == 'a') ? ca :
        (correct == 'b') ? cb :
        (correct == 'c') ? cc : cd;

    printf("\n  \033[101m" FG_WHITE BOLD
           "  [WRONG!]                                                      "
           RESET "\n");
    printf("  " FG_YELLOW "  >>  Correct Answer: "
           BOLD FG_GREEN "(%c)  %s" RESET "\n", correct, ans_text);
}

void print_score_bar(int score, int asked) {
    int filled = (asked > 0) ? (score * 30 / asked) : 0;
    printf("  " FG_GOLD "Score  [" RESET FG_GREEN);
    for (int i = 0; i < 30; i++) printf("%s", i < filled ? "#" : " ");
    printf(RESET FG_GOLD "]  " BOLD "%d / %d" RESET "\n", score, asked);
}

void print_progress_bar(int done, int total) {
    int filled = done * 40 / total;
    printf("  " FG_CYAN "Progress [" RESET FG_MAGENTA);
    for (int i = 0; i < 40; i++)
        printf("%s", i < filled ? "#" : ".");
    printf(RESET FG_CYAN "]  " FG_WHITE "%d/%d" RESET "\n\n", done, total);
}


typedef struct {
    char question[200];
    char a[100];
    char b[100];
    char c[100];
    char d[100];
    char correct;
    char category[50];
    char movie[50];
} TQuestion;


static TQuestion qbank[TOTAL_Q] = {

    {"Complete the Pushpa dialogue: 'Pushpa... _____ mat samajhna!'",
     "Chota","Mota","Bada","Phool",
     'd',"Dialogues","Pushpa"},

    {"'Kattappa ne Baahubali ko kyun mara?' is the cliffhanger of which film?",
     "RRR","Magadheera","Baahubali: The Beginning","Eega",
     'c',"Dialogues","Baahubali"},

    {"The viral dialogue 'Thaggedhe Le!' became famous from which film?",
     "Baahubali 2","Akhanda","Pushpa: The Rise","RRR",
     'c',"Dialogues","Pushpa2"},

    {"'Jai Mahishmati!' is the battle cry from which Tollywood epic?",
     "RRR","Magadheera","Baahubali","Eega",
     'c',"Dialogues","BaahubaliBattle"},

    {"In 'Magadheera', Ram Charan's character says which famous line about destiny?",
     "Praanam nee kosam","Nee kosam jeevistanu","Oka kalam oka praanam","Marana shandam",
     'c',"Dialogues","Magadheera"},

    {"'Businessman lo oka dialogue untundi — Tiger is a tiger whether in jungle or a cage.' Who delivers it?",
     "Jr. NTR","Mahesh Babu","Allu Arjun","Ram Charan",
     'b',"Dialogues","Businessman"},

    {"'Idhi Naa Ishtam!' is a famous punch line strongly associated with which superstar?",
     "Chiranjeevi","Mahesh Babu","Balakrishna","Nagarjuna",
     'b',"Dialogues","MaheshDialog"},

    {"In Baahubali 2, who delivers the line 'When a cow enters a field, you build a fence — you don't kill the cow'?",
     "Baahubali","Bijjaladeva","Sivagami","Kattappa",
     'c',"Dialogues","Baahubali2Dialog"},

    {"'Antha Mana Manchike...' is a signature dialogue style of which actor?",
     "Chiranjeevi","Balakrishna","Pawan Kalyan","Nagarjuna",
     'b',"Dialogues","BalakrishnaDialog"},

    {"The emotional dialogue 'Oka praanam kaavali, oka premikudu kaavali, oka kaalam kaavali' is from?",
     "Geetha Govindam","Arjun Reddy","Fidaa","Shatamanam Bhavati",
     'b',"Dialogues","ArjunReddyDialog"},

    {"In RRR, Ram Charan's character Alluri tells Bheem: 'Mana ___ okate, kaani manam veru veru.' Fill the blank.",
     "Jeevitam","Lakshyam","Pranalu","Bhaasham",
     'b',"Dialogues","RRRDialog"},

    {"'Naalo unna manishi chanipovadam kaadu, naako unna manishi vellipovadame chaavalante samanam' — from which film?",
     "Fidaa","Jersey","Shatamanam Bhavati","Ninnu Kori",
     'c',"Dialogues","ShatamanamDialog"},

    {"Pawan Kalyan's iconic 'Power Star' dialogue from 'Gabbar Singh' is a remake of which Hindi film?",
     "Sholay","Dabangg","Singham","Rowdy Rathore",
     'b',"Dialogues","GabbarSingh"},

    
    {"Who delivers the iconic line 'Nenu chesindi correct' in the 2017 film 'Arjun Reddy'?",
     "Nani","Vijay Deverakonda","Rana Daggubati","Adivi Sesh",
     'b',"Dialogues","NenuCorrect"},

    {"The dialogue 'Okka mandu chettu nashipothe manaki telustundi, aa chettu maname nashipoyaam ani' is from?",
     "Temper","Baadshah","Janatha Garage","Nannaku Prematho",
     'c',"Dialogues","JanathaDialog"},

    {"'Naake bhayam ante paniki raadu — naadi bhayam ante pani avutundi!' Which Jr. NTR film has this line?",
     "Baadshah","Temper","Dammu","Jai Lava Kusa",
     'b',"Dialogues","TemperDialog"},

    {"'Naa peru Surya, naa illu India' is the powerful opening declaration of which Allu Arjun film?",
     "Sarrainodu","Julayi","Race Gurram","Naa Peru Surya Naa Illu India",
     'd',"Dialogues","NaaPeruSurya"},

    {"In 'Akhanda' (2021), Balakrishna's swami character delivers dialogues about which divine force?",
     "Brahma","Shakti","Vishnu","Agni",
     'b',"Dialogues","AkhandaDialog"},

    {"'Jalsa chesthe Jalsa — waste chesthe waste!' defines the carefree spirit of which Pawan Kalyan film?",
     "Gabbar Singh","Jalsa","Attarintiki Daredi","Vakeel Saab",
     'b',"Dialogues","JalsaDialog"},
    {"Which blockbuster features Prabhas as 'Amarendra Baahubali'?",
     "Arjun Reddy","Baahubali","Pushpa","RRR",
     'b',"Films","BaahubaliFact"},

    {"In which year was 'RRR' released?",
     "2021","2022","2023","2020",
     'b',"Films","RRR"},

    {"In which year was 'Pushpa: The Rise' released?",
     "2020","2021","2022","2019",
     'b',"Films","PushpaFact"},

    {"'Baahubali 2: The Conclusion' broke the all-time box office record of which Hindi film?",
     "Dangal","PK","3 Idiots","DDLJ",
     'a',"Films","Baahubali2"},

    {"'Sye Raa Narasimha Reddy' is based on which freedom fighter?",
     "Bhagat Singh","Uyyalawada Narasimha Reddy","Alluri Sitarama Raju","Komaram Bheem",
     'b',"Films","SyeRaa"},

    {"In 'Eega', the hero is reborn as which creature for revenge?",
     "Ant","Mosquito","Housefly","Butterfly",
     'c',"Films","Eega"},

    {"'Fidaa' (2017) starred which actress opposite Varun Tej?",
     "Samantha","Sai Pallavi","Pooja Hegde","Rakul Preet",
     'b',"Films","Fidaa"},

    {"'Bheemla Nayak' is the Telugu remake of which Malayalam film?",
     "Drishyam","Ayyappanum Koshiyum","Lucifer","Vikram",
     'b',"Films","BheemlaFact"},

    {"Which Tollywood film was remade in Hindi as 'Kabir Singh'?",
     "Geetha Govindam","Jersey","Arjun Reddy","Fidaa",
     'c',"Films","KabirSingh"},

    
    {"Who directed 'RRR' (2022)?",
     "Trivikram Srinivas","Sukumar","S. S. Rajamouli","Koratala Siva",
     'c',"Directors","RRRDir"},

    {"Who directed 'Pushpa: The Rise'?",
     "Trivikram Srinivas","Sukumar","S. S. Rajamouli","Boyapati Srinu",
     'b',"Directors","PushpaDir"},

    {"Who directed 'Ala Vaikunthapurramuloo'?",
     "Trivikram Srinivas","Sukumar","Boyapati Srinu","Harish Shankar",
     'a',"Directors","AVPMDir"},

    {"Who directed 'Magadheera'?",
     "Gunasekhar","Trivikram Srinivas","S. S. Rajamouli","Sukumar",
     'c',"Directors","MagadheeraDir"},

    {"SS Rajamouli's father is which famous Tollywood screenwriter?",
     "Vijayendra Prasad","Trivikram","Paruchuri Brothers","Gollapudi Maruti Rao",
     'a',"Directors","RajamouliFamily"},

    {"Who directed 'Bharat Ane Nenu'?",
     "Trivikram Srinivas","Sukumar","Koratala Siva","Vamsi Paidipally",
     'c',"Directors","BharatDir"},

    
    {"The song 'Naatu Naatu' from RRR won an Oscar in which category?",
     "Best Original Score","Best Sound","Best Original Song","Best Picture",
     'c',"Music","NaatuOscar"},

    {"Who composed the music for 'Baahubali: The Beginning'?",
     "A. R. Rahman","M. M. Keeravani","Devi Sri Prasad","Thaman S",
     'b',"Music","BaahubaliMusic"},

    {"Who composed music for 'Pushpa: The Rise'?",
     "M. M. Keeravani","Thaman S","Devi Sri Prasad","A. R. Rahman",
     'c',"Music","PushpaMusic"},

    {"Who composed music for 'Ala Vaikunthapurramuloo'?",
     "Thaman S","Devi Sri Prasad","M. M. Keeravani","Mani Sharma",
     'a',"Music","AVPMMusic"},

    {"The lyricist of 'Naatu Naatu' is?",
     "Chandrabose","Sirivennela Seetharama Shastri","Ramajogayya Sastry","Sri Mani",
     'a',"Music","NaatuLyricist"},

    {"'Oo Antava' item number from Pushpa: The Rise was performed by which actress?",
     "Sunidhi Chauhan","Shreya Ghoshal","Samantha","Mangli",
     'c',"Music","OoAntava"},

    {"Who sang the soulful 'Samajavaragamana' in Ala Vaikunthapurramuloo?",
     "Armaan Malik","Haricharan","Sid Sriram","Karthik",
     'c',"Music","SamajavaragamanaSong"},

    {"Who sang the hit 'Inkem Inkem Inkem Kaavaali' from Geetha Govindam?",
     "Karthik","Haricharan","Armaan Malik","Sid Sriram",
     'd',"Music","InkemSong"},

    {"Who sang the romantic track 'Srivalli' from Pushpa: The Rise?",
     "Haricharan","Armaan Malik","Sid Sriram","Javed Ali",
     'c',"Music","SrivalliSong"},

    {"Who provided the female vocals for 'Ramuloo Ramulaa' from Ala Vaikunthapurramuloo?",
     "Sunidhi Chauhan","Shreya Ghoshal","Anuradha Bhatia","Mangli",
     'd',"Music","RamuloSong"},

    {"The devotional classic 'Dandaalayyaa' from Baahubali 2 was sung by which legendary playback singer?",
     "K. J. Yesudas","P. Susheela","S. P. Balasubrahmanyam","Ghantasala",
     'c',"Music","DandaalayyaaSong"},

    {"The foot-tapping 'Seeti Maar' from DJ Duvvada Jagannadham (2017) was sung by which singer?",
     "Karthik","Devi Sri Prasad","Rahul Sipligunj","Armaan Malik",
     'c',"Music","SeetiMaarSong"},

    {"'Butta Bomma' from Ala Vaikunthapurramuloo is picturized on which actress as the female lead?",
     "Samantha","Rashmika Mandanna","Nayanthara","Pooja Hegde",
     'd',"Music","ButtaBommaSong"},

    {"In the film 'DJ Duvvada Jagannadham', who performs the high-energy title song 'DJ'?",
     "Jr. NTR","Ram Charan","Allu Arjun","Vijay Deverakonda",
     'c',"Music","DJTitleSong"},
    {"Who played 'Kattappa' in Baahubali?",
     "Sathyaraj","Rana Daggubati","Prabhas","Nassar",
     'a',"Characters","Kattappa"},

    {"Who played 'Bhallala Deva' in Baahubali?",
     "Rana Daggubati","Sathyaraj","Prabhas","Nasser",
     'a',"Characters","Bhallala"},

    {"Ram Charan played which real-life freedom fighter in 'RRR'?",
     "Komaram Bheem","Alluri Sitarama Raju","Uyyalawada Narasimha Reddy","Puli Thevar",
     'b',"Characters","RamCharanRole"},

    {"Who played the villain Shekhawat in 'Pushpa: The Rise'?",
     "Prakash Raj","Fahadh Faasil","Rao Ramesh","Jagapathi Babu",
     'b',"Characters","PushpaVillain"},

    {"Anushka Shetty played the warrior princess 'Devasena' in which film?",
     "Rudhramadevi","Baahubali","Bahubali 2","Size Zero",
     'b',"Characters","Devasena"},

    
    {"Savitri was known by which title in Telugu cinema?",
     "Mahanati","Abhinaya Saraswathi","Natakurathi","Lady Superstar",
     'b',"Legends","Savitri"},

    {"Jr. NTR is the grandson of which legendary actor?",
     "Akkineni Nageswara Rao","N. T. Rama Rao","S. V. Ranga Rao","Nagabhushanam",
     'b',"Legends","NTRFamily"},

    {"Pawan Kalyan is the brother of which Tollywood megastar?",
     "Nagarjuna","Balakrishna","Chiranjeevi","Venkatesh",
     'c',"Families","PawanFamily"},

    
    {"Which Tollywood actress won the National Award for 'Mahanati'?",
     "Samantha","Keerthy Suresh","Nayanthara","Pooja Hegde",
     'b',"Awards","MahanatiAward"},

    {"Allu Arjun won his first National Award for which film?",
     "Ala Vaikunthapurramuloo","Julayi","Arya","Pushpa: The Rise",
     'd',"Awards","AlluAward"},
};


void tollywood(void) {
    srand((unsigned)time(NULL));

    int order[TOTAL_Q];
    for (int i = 0; i < TOTAL_Q; i++) order[i] = i;
    shuffle(order, TOTAL_Q);

    int score   = 0;   
    int wrong   = 0;   
    int skipped = 0;   
    char ans;
    int used_movies[TOTAL_Q];
    memset(used_movies, 0, sizeof(used_movies));
    int asked = 0;
    int exited = 0;    

    print_banner();
    printf("  " FG_CYAN "You will be asked " BOLD FG_GOLD "%d random questions"
           RESET FG_CYAN " from the %d-question bank.\n",
           QUESTIONS_PER_RUN, TOTAL_Q);
    printf("  " FG_CYAN "No duplicate movie/topic questions will appear in the same run.\n");
    printf("  " FG_CYAN "Type " BOLD "a" RESET FG_CYAN "/" BOLD "b" RESET FG_CYAN
           "/" BOLD "c" RESET FG_CYAN "/" BOLD "d" RESET FG_CYAN " to answer  |  "
           BOLD FG_YELLOW "s" RESET FG_CYAN " to skip  |  "
           BOLD FG_RED "e" RESET FG_CYAN " to exit\n\n" RESET);
    print_thin_line(FG_GOLD, 72);
    printf("\n  " FG_WHITE "Press " BOLD FG_GOLD "Enter" RESET FG_WHITE " to begin..." RESET "\n");
    getchar();

    for (int i = 0; i < TOTAL_Q && asked < QUESTIONS_PER_RUN && !exited; i++) {
       TQuestion *cur = &qbank[order[i]];

        
        int skip = 0;
        for (int j = 0; j < TOTAL_Q; j++) {
            if (used_movies[j] && strcmp(cur->movie, qbank[j].movie) == 0) {
                skip = 1;
                break;
            }
        }
        if (skip) continue;

        used_movies[order[i]] = 1;
        asked++;

        const char *cat_colors[] = {
            FG_GOLD, FG_CYAN, FG_MAGENTA, FG_GREEN, FG_ORANGE, FG_YELLOW
        };
        const char *cc = cat_colors[asked % 6];

        printf("\n");
        print_line(FG_GOLD, 72);
        printf("  " BOLD FG_WHITE "Q %02d / %02d" RESET
               "   %s[ %-12s]" RESET "   "
               FG_GREEN "[OK] %d" RESET "  "
               FG_RED "[X] %d" RESET "  "
               FG_YELLOW "[~] %d" RESET "  "
               FG_GOLD "Score: " BOLD "%d\n" RESET,
               asked, QUESTIONS_PER_RUN, cc, cur->category,
               score, wrong, skipped, score);
        print_thin_line(FG_GOLD, 72);
        print_progress_bar(asked - 1, QUESTIONS_PER_RUN);

        printf("  " BOLD FG_WHITE "?  %s" RESET "\n\n", cur->question);
        print_thin_line(FG_MAGENTA, 72);

        print_option('A', cur->a, FG_CYAN);
        print_option('B', cur->b, FG_YELLOW);
        print_option('C', cur->c, FG_MAGENTA);
        print_option('D', cur->d, FG_GREEN);
        print_thin_line(FG_MAGENTA, 72);

        
        int valid = 0;
        while (!valid) {
            printf("\n  " BOLD FG_GOLD "Your answer (a/b/c/d  |  s=skip  e=exit): " RESET);
            if (scanf(" %c", &ans) != 1) ans = '?';
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            ans = (char)(ans | 32);   

            if (ans >= 'a' && ans <= 'd') {
                valid = 1;
            } else if (ans == 's') {
                valid = 1;
            } else if (ans == 'e') {
                valid = 1;
                exited = 1;
            } else {
                printf("  " FG_RED "[!]  Invalid -- enter a/b/c/d, s to skip, or e to exit.\n" RESET);
            }
        }

        if (exited) {
            printf("\n  " FG_ORANGE BOLD "  [!]  Quiz exited early.  Results below.\n" RESET);
            break;
        }

        if (ans == 's') {
            skipped++;
            printf("\n  \033[43m\033[30m" BOLD
                   "  [SKIP]  The answer was: (%c) %s" ,
                   cur->correct,
                   (cur->correct=='a') ? cur->a :
                   (cur->correct=='b') ? cur->b :
                   (cur->correct=='c') ? cur->c : cur->d);
            printf("%-*s" RESET "\n", 1, "");
        } else if (ans == cur->correct) {
            score++;
            print_correct_result();
        } else {
            wrong++;
            print_wrong_result(cur->correct, cur->a, cur->b, cur->c, cur->d);
        }

        printf("\n  ");
        print_score_bar(score, asked);

        if (asked < QUESTIONS_PER_RUN && !exited) {
            printf("\n  " DIM FG_WHITE "Press Enter for the next question..." RESET "\n");
            getchar();
        }
    }

    
    printf("\n");
    print_line(FG_GOLD, 72);
    printf("\n");

    int attempted = score + wrong;   

    const char *verdict, *color;
    if      (score == QUESTIONS_PER_RUN) { color = FG_GOLD;    verdict = "PERFECT TOLLYWOOD LEGEND! Absolute Flawless Victory!"; }
    else if (score >= 8)                 { color = FG_YELLOW;  verdict = "MEGASTAR LEVEL!  Extraordinary knowledge!";             }
    else if (score >= 6)                 { color = FG_GREEN;   verdict = "SUPERSTAR FAN!   Truly impressive!";                    }
    else if (score >= 4)                 { color = FG_CYAN;    verdict = "TOLLYWOOD FOLLOWER!  Solid effort!";                    }
    else if (score >= 2)                 { color = FG_MAGENTA; verdict = "RISING VIEWER!   Keep watching more films!";            }
    else                                 { color = FG_ORANGE;  verdict = "BEGINNER!  Time for a Tollywood marathon!";             }

    printf("  " BOLD FG_WHITE "QUESTIONS   :  " RESET BOLD FG_WHITE "Asked %-2d  |  Attempted %-2d  |  Remaining %-2d%s\n",
           asked, attempted, QUESTIONS_PER_RUN - asked, RESET);
    printf("  " BOLD FG_WHITE "FINAL SCORE :  " RESET BOLD "%s%d / %d%s\n",
           color, score, QUESTIONS_PER_RUN, RESET);
    printf("  " BOLD FG_WHITE "ACCURACY    :  " RESET BOLD "%s%d%%%s\n",
           color, attempted > 0 ? score * 100 / attempted : 0, RESET);
    printf("  " BOLD FG_WHITE "VERDICT     :  " RESET BOLD "%s%s%s\n\n",
           color, verdict, RESET);

    
    int bar_c = score   * 40 / QUESTIONS_PER_RUN;
    int bar_w = wrong   * 40 / QUESTIONS_PER_RUN;
    int bar_s = skipped * 40 / QUESTIONS_PER_RUN;

    printf("  " FG_WHITE "[OK] Correct  [" FG_GREEN);
    for (int i = 0; i < 40; i++) printf("%s", i < bar_c ? "#" : ".");
    printf(RESET FG_WHITE "]  " BOLD FG_GREEN "%d\n" RESET, score);

    printf("  " FG_WHITE "[X]  Wrong    [" FG_RED);
    for (int i = 0; i < 40; i++) printf("%s", i < bar_w ? "#" : ".");
    printf(RESET FG_WHITE "]  " BOLD FG_RED "%d\n" RESET, wrong);

    printf("  " FG_WHITE "[~]  Skipped  [" FG_YELLOW);
    for (int i = 0; i < 40; i++) printf("%s", i < bar_s ? "#" : ".");
    printf(RESET FG_WHITE "]  " BOLD FG_YELLOW "%d\n\n" RESET, skipped);

    printf("  " FG_CYAN "[OK] Correct : " BOLD FG_GREEN  "%-4d" RESET
           "  " FG_CYAN "[X]  Wrong   : " BOLD FG_RED    "%-4d" RESET
           "  " FG_CYAN "[~]  Skipped : " BOLD FG_YELLOW "%-4d" RESET
           "  " FG_CYAN "[!]  Exited  : " BOLD FG_ORANGE "%s\n\n" RESET,
           score, wrong, skipped, exited ? "Yes" : "No");

    print_line(FG_GOLD, 72);
    printf("\n  " FG_CYAN "** Thank you for playing the Tollywood Quiz! **\n\n" RESET);
}
void current_affairs_quiz()
{
    typedef struct {
        char question[200];
        char a[100];
        char b[100];
        char c[100];
        char d[100];
        char correct;
    } CAQuestion;

    CAQuestion qbank[] = {

    {"Who is the Prime Minister of India?","Rahul Gandhi","Narendra Modi","Amit Shah","Arvind Kejriwal",'b'},
    {"Who is the President of India?","Droupadi Murmu","Pratibha Patil","Ram Nath Kovind","APJ Abdul Kalam",'a'},
    {"Capital of Australia?","Sydney","Canberra","Melbourne","Perth",'b'},
    {"Headquarters of UN?","Geneva","Paris","New York","London",'c'},
    {"Currency of Japan?","Won","Yuan","Yen","Dollar",'c'},
    {"Largest democracy?","USA","India","Brazil","UK",'b'},
    {"RBI Governor?","Raghuram Rajan","Shaktikanta Das","Urjit Patel","Arvind Panagariya",'b'},
    {"National animal of India?","Lion","Elephant","Tiger","Leopard",'c'},
    {"FIFA 2022 host?","Russia","Qatar","USA","France",'b'},
    {"ISRO HQ?","Chennai","Bangalore","Hyderabad","Delhi",'b'},
    {"Largest planet?","Earth","Jupiter","Mars","Saturn",'b'},
    {"Smallest planet?","Mercury","Mars","Venus","Earth",'a'},
    {"Fastest land animal?","Lion","Tiger","Cheetah","Horse",'c'},
    {"National flower of India?","Rose","Lotus","Lily","Sunflower",'b'},
    {"Who wrote National Anthem?","Tagore","Gandhi","Nehru","Ambedkar",'a'},
    {"Largest ocean?","Indian","Pacific","Atlantic","Arctic",'b'},
    {"India Independence year?","1945","1946","1947","1950",'c'},
    {"First President of India?","Rajendra Prasad","Nehru","APJ Abdul Kalam","Indira Gandhi",'a'},
    {"Currency of USA?","Euro","Dollar","Pound","Yen",'b'},
    {"Currency of UK?","Euro","Dollar","Pound","Yuan",'c'},
    {"Who discovered gravity?","Newton","Einstein","Tesla","Edison",'a'},
    {"Who invented telephone?","Edison","Bell","Tesla","Newton",'b'},
    {"Largest continent?","Africa","Asia","Europe","Australia",'b'},
    {"Smallest continent?","Australia","Europe","Antarctica","Africa",'a'},
    {"Which gas plants absorb?","Oxygen","Hydrogen","Carbon Dioxide","Nitrogen",'c'},
    {"Largest country by area?","USA","China","Russia","India",'c'},
    {"Smallest country?","Monaco","Vatican City","Maldives","Bhutan",'b'},
    {"Red Planet?","Mars","Venus","Mercury","Saturn",'a'},
    {"Land of Rising Sun?","China","Japan","Thailand","Korea",'b'},
    {"Liquid metal at room temp?","Iron","Gold","Mercury","Silver",'c'},
    {"Environment Day?","June 5","July 5","May 5","April 5",'a'},
    {"National tree of India?","Neem","Banyan","Mango","Peepal",'b'},
    {"Largest desert?","Sahara","Gobi","Thar","Arabian",'a'},
    {"Silicon Valley of India?","Tamil Nadu","Karnataka","Kerala","Telangana",'b'},
    {"National river of India?","Yamuna","Godavari","Ganga","Krishna",'c'},
    {"G20 2023 host country?","India","Japan","Germany","Brazil",'a'},
    {"Current Home Minister?","Amit Shah","Rajnath Singh","Gadkari","Piyush Goyal",'a'},
    {"Finance Minister?","Smriti Irani","Nirmala Sitharaman","Arun Jaitley","Rajnath Singh",'b'},
    {"External Affairs Minister?","S Jaishankar","Amit Shah","Rajnath Singh","Piyush Goyal",'a'},
    {"UN Secretary General?","Ban Ki Moon","Antonio Guterres","Joe Biden","Macron",'b'},
    {"First PM of India?","Nehru","Gandhi","Patel","Rajendra Prasad",'a'},
    {"National sport (traditional)?","Cricket","Hockey","Kabaddi","Football",'b'},
    {"Indian Space Agency?","NASA","ISRO","ESA","JAXA",'b'},
    {"Capital of France?","Paris","London","Berlin","Rome",'a'},
    {"Capital of USA?","New York","Washington DC","Chicago","LA",'b'},
    {"Capital of China?","Shanghai","Beijing","Wuhan","Shenzhen",'b'},
    {"Capital of Germany?","Munich","Berlin","Frankfurt","Hamburg",'b'},
    {"Capital of Italy?","Rome","Milan","Venice","Naples",'a'},
    {"Capital of Canada?","Toronto","Ottawa","Vancouver","Montreal",'b'},
    {"Capital of Russia?","Moscow","Kyiv","Minsk","Tashkent",'a'}

    };


   int TOTALQ = sizeof(qbank) / sizeof(qbank[0]);
    int ASK_Q = 10;

    int CORRECT_MARK = 5;
    int WRONG_MARK = -2;
    int SKIP_MARK = -1;

    int used[TOTALQ];
    for(int i=0;i<TOTALQ;i++)
        used[i] = 0;

    int count=0, score=0, wrong=0, attempted=0, skip=0;
    char ans;

    srand(time(NULL));
    system("cls");   

    printf(CYAN "=========================================\n");
    printf("         CURRENT AFFAIRS QUIZ\n");
    printf("=========================================\n" RESET);

    printf(YELLOW "a/b/c/d -> Answer\n1 -> Skip (-1)\n0 -> Exit\n\n" RESET);

    while(count < ASK_Q)
    {
        int index = rand() % TOTALQ;
        if(used[index]) continue;

        used[index] = 1;
        count++;

        CAQuestion *q = &qbank[index];

        printf(BLUE "\n-----------------------------------------\n" RESET);
        printf(CYAN "Q%d: %s\n" RESET, count, q->question);

        printf("a) %s\nb) %s\nc) %s\nd) %s\n",
               q->a, q->b, q->c, q->d);

        printf(YELLOW "Your answer: " RESET);
        scanf(" %c",&ans);

        if(ans=='0') break;

        if(ans=='1')
        {
            printf(YELLOW "Skipped! -1 mark\n" RESET);
            score += SKIP_MARK;
            skip++;
            continue;
        }

        attempted++;

        if(ans == q->correct)
        {
            printf(GREEN "Correct! +5 marks\n" RESET);
            score += CORRECT_MARK;
        }
        else
        {
            printf(RED "Wrong! -2 marks | Correct: %c\n" RESET, q->correct);
            score += WRONG_MARK;
            wrong++;
        }
    }

    printf(CYAN "\n=========================================\n");
    printf("              QUIZ RESULT\n");
    printf("=========================================\n" RESET);

    printf(GREEN "Score      : %d\n" RESET, score);
    printf(RED   "Wrong      : %d\n" RESET, wrong);
    printf(YELLOW "Skipped    : %d\n" RESET, skip);
    printf(CYAN  "Attempted  : %d\n" RESET, attempted);

    if(attempted > 0)
        printf(BLUE "Percentage : %.2f%%\n" RESET,
               (score * 100.0) / (ASK_Q * CORRECT_MARK));

    printf(CYAN "=========================================\n" RESET);
}
// ===== C QUIZ =====

struct CQuestion {
    char question[150];
    char optionA[60];
    char optionB[60];
    char optionC[60];
    char optionD[60];
    char correct;
};

struct CQuestion q[TOTAL] = {
    {"Who developed C language?","Dennis Ritchie","James Gosling","Bjarne Stroustrup","Guido van Rossum",'A'},
    {"C language was developed in?","1972","1985","1995","2000",'A'},
    {"Which header file is used for input/output?","stdio.h","math.h","stdlib.h","string.h",'A'},
    {"Array index starts from?","0","1","-1","Depends",'A'},
    {"Which loop executes at least once?","do-while","for","while","switch",'A'},
    {"Which symbol is address operator?","&","*","#","@",'A'},
    {"Which function prints output?","printf()","scanf()","display()","print()",'A'},
    {"Which keyword is used to exit loop?","break","exit","stop","return",'A'},
    {"Which data type stores decimal?","float","int","char","void",'A'},
    {"Which operator is used for modulus?","%","/","*","+",'A'},
    {"Which keyword is used for structure?","struct","class","record","define",'A'},
    {"Which library is used for memory allocation?","stdlib.h","stdio.h","math.h","conio.h",'A'},
    {"Which function allocates memory?","malloc()","calloc()","free()","alloc()",'A'},
    {"Which function frees memory?","free()","malloc()","delete()","remove()",'A'},
    {"Which keyword is used for constant?","const","final","static","define",'A'},
    {"Which operator is logical AND?","&&","||","&","and",'A'},
    {"Which operator is logical OR?","||","&&","|","or",'A'},
    {"Which operator checks equality?","==","=","!=","<>",'A'},
    {"Which function finds string length?","strlen()","strcmp()","strcpy()","size()",'A'},
    {"Which function compares strings?","strcmp()","strlen()","strcpy()","concat()",'A'},
    {"Which loop is best for known iterations?","for","while","do-while","switch",'A'},
    {"Which keyword skips iteration?","continue","skip","break","pass",'A'},
    {"Which header file is for math?","math.h","stdio.h","string.h","ctype.h",'A'},
    {"Which function finds square root?","sqrt()","pow()","log()","abs()",'A'},
    {"Which operator is ternary?","?:","??","::","//",'A'},
    {"Which header file handles strings?","string.h","math.h","stdio.h","stdlib.h",'A'},
    {"Which keyword returns value?","return","exit","break","stop",'A'},
    {"Which data type is 1 byte?","char","int","float","double",'A'},
    {"Which operator increments value?","++","--","+","+=",'A'},
    {"Which operator decrements value?","--","++","-","-=",'A'},
    {"Which keyword defines macro?","#define","#include","const","macro",'A'},
    {"Which function converts string to int?","atoi()","itoa()","strlen()","abs()",'A'},
    {"Which storage class retains value?","static","auto","extern","register",'A'},
    {"Which keyword declares external variable?","extern","static","auto","register",'A'},
    {"Which header file for character functions?","ctype.h","stdio.h","math.h","string.h",'A'},
    {"Which function checks uppercase?","isupper()","islower()","isdigit()","toupper()",'A'},
    {"Which function converts to uppercase?","toupper()","tolower()","isupper()","isdigit()",'A'},
    {"Which keyword is used for union?","union","struct","class","enum",'A'},
    {"Which keyword defines enumeration?","enum","struct","define","typedef",'A'},
    {"What is usual size of int?","4 bytes","2 bytes","8 bytes","1 byte",'A'},
    {"Which function clears memory?","memset()","memcpy()","free()","malloc()",'A'},
    {"Which function copies memory?","memcpy()","memset()","copy()","move()",'A'},
    {"Which function opens file?","fopen()","open()","read()","file()",'A'},
    {"Which function closes file?","fclose()","close()","end()","stop()",'A'},
    {"Which mode opens file for reading?","r","w","a","rw",'A'},
    {"Which mode opens file for writing?","w","r","a","rw",'A'},
    {"Which mode appends file?","a","w","r","rw",'A'},
    {"Which symbol ends statement?",";",";",":",".",'A'},
    {"Which function reads formatted input?","scanf()","printf()","gets()","puts()",'A'},
    {"Which function prints formatted output?","printf()","scanf()","puts()","gets()",'A'}
};

void showTitle(){
    printf(RED   "=====================================\n" RESET);
    printf(YELLOW"        WELCOME TO QUIZ GAME\n" RESET);
    printf(GREEN "=====================================\n" RESET);
    printf(CYAN  "Correct : +5\n" RESET);
    printf(CYAN   "Wrong   : -2\n" RESET);
    printf(CYAN"Skip(1) : -1   Exit(0)\n" RESET);
    printf(CYAN   "=====================================\n\n" RESET);
}

char askQuestion(struct CQuestion q, int number){

    char options[4][60];
    char labels[4]={'A','B','C','D'};

    strcpy(options[0],q.optionA);
    strcpy(options[1],q.optionB);
    strcpy(options[2],q.optionC);
    strcpy(options[3],q.optionD);

    // Shuffle options
    int correctIndex=q.correct-'A';
    for(int i=0;i<4;i++){
        int r=rand()%4;
        char temp[60];
        strcpy(temp,options[i]);
        strcpy(options[i],options[r]);
        strcpy(options[r],temp);

        if(i==correctIndex) correctIndex=r;
        else if(r==correctIndex) correctIndex=i;
    }

    printf(CYAN "\nQuestion %d of %d\n" RESET,number,ASK);
    printf(YELLOW "%s\n\n" RESET,q.question);

    // All options in MAGENTA (pink)
    printf(MAGENTA "A) %s\n" RESET,options[0]);
    printf(MAGENTA "B) %s\n" RESET,options[1]);
    printf(MAGENTA "C) %s\n" RESET,options[2]);
    printf(MAGENTA "D) %s\n" RESET,options[3]);

    printf("\nYour Answer : ");
    return labels[correctIndex];
}

void showResult(int score){
    printf(GREEN "\n=====================================\n" RESET);
    printf(YELLOW "Final Score: %d / %d\n" RESET,score,FULL_MARKS);

    // Talent comment based on score
    if(score <= 10){
        printf(MAGENTA "Keep practicing! More practice, better play!\n" RESET);
    } else if(score <= 30){
        printf(CYAN "Good job! Keep improving!\n" RESET);
    } else{
        printf(GREEN "Excellent! Your talent is shining!\n" RESET);
    }

    printf(GREEN "=====================================\n" RESET);
}

void quiz(){

    int used[TOTAL]={0};
    int score=0;
    char answer;

    srand(time(0));
    showTitle();

    for(int i=0;i<ASK;i++){

        int index;
        do{
            index=rand()%TOTAL;
        }while(used[index]);

        used[index]=1;

        char correctAnswer=askQuestion(q[index],i+1);

        scanf(" %c",&answer);
        answer=toupper(answer);

        if(answer=='0'){
            printf(RED "\nExiting Quiz...\n" RESET);
            break;
        }

        if(answer=='1'){
            printf(MAGENTA "Skipped! -1 Mark\n" RESET);
            score-=1;
            continue;
        }

        if(answer==correctAnswer){
            printf(GREEN "Correct! +5 Marks\n" RESET);
            score+=5;
        }else{
            printf(RED "Wrong! -2 Marks\n" RESET);
            printf("Correct answer was %c\n",correctAnswer);
            score-=2;
        }
    }

    showResult(score);
}
// ===== SNAKE GAME =====

// ===== GLOBAL VARIABLES =====
int x, y, fruitX, fruitY;
int score, highScore;
int tailX[500], tailY[500];
int nTail;
int gameOver;
int speed = 60;

int difficulty;
int obstacleX[20], obstacleY[20];
int obstacleDirX[20], obstacleDirY[20];
int obstacleColor[20];
int obstacleCount = 0;

int i, j, k;
int prevX, prevY, prev2X, prev2Y;

enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum direction dir;

// ===== CONSOLE FUNCTIONS =====
void HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GotoXY(int xPos, int yPos)
{
    COORD coord;
    coord.X = xPos;
    coord.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ===== HIGH SCORE =====
void LoadHighScore()
{
    FILE *fp = fopen("highscore.txt","r");
    if(fp == NULL) highScore = 0;
    else { fscanf(fp,"%d",&highScore); fclose(fp); }
}

void SaveHighScore()
{
    FILE *fp = fopen("highscore.txt","w");
    if(fp != NULL){ fprintf(fp,"%d",highScore); fclose(fp);}
}

// ===== SUDDEN OBSTACLE =====
void GenerateSuddenObstacle()
{
    if(obstacleCount < 20)
    {
        obstacleX[obstacleCount] = rand() % WIDTH;
        obstacleY[obstacleCount] = rand() % HEIGHT;

        obstacleDirX[obstacleCount] = (rand()%2==0)?1:-1;
        obstacleDirY[obstacleCount] = (rand()%2==0)?1:-1;

        obstacleColor[obstacleCount] = 1 + rand()%14;
        obstacleCount++;
    }
}

// ===== INTERFACE =====
void ShowIntro()
{
    system("cls");

    SetColor(11); // Cyan border
    int w=60, h=15;
    for(int i=0;i<=h;i++)
    {
        for(int j=0;j<=w;j++)
        {
            if(i==0 || i==h) printf("*");
            else if(j==0 || j==w) printf("*");
            else printf(" ");
        }
        printf("\n");
    }

    GotoXY(5,2);
    SetColor(14); // Yellow text
    printf("Welcome to");

    GotoXY(20,3);
    SetColor(10); // Green snake art
    printf(" S N A K E   G A M E ");

    // Small ASCII Snake
    GotoXY(20,5);
    SetColor(12); // Red snake
    printf("   __");
    GotoXY(20,6);
    printf("  /  \\__");
    GotoXY(20,7);
    printf(" |      \\__");
    GotoXY(20,8);
    printf("  \\__/");

    GotoXY(5,10);
    SetColor(14);
    printf("Select difficulty:");
    GotoXY(5,11);
    printf("1. EASY");
    GotoXY(5,12);
    printf("2. MEDIUM");
    GotoXY(5,13);
    printf("3. HARD");
    GotoXY(5,14);
    printf("Enter choice: ");
    SetColor(15);
}

// ===== DIFFICULTY =====
void SelectDifficulty()
{
    ShowIntro();
    scanf("%d",&difficulty);

    if(difficulty == 1){ speed = 120; obstacleCount = 0;}
    else if(difficulty == 2){ speed = 80; obstacleCount = 5;}
    else{ speed = 40; obstacleCount = 10;}
}

// ===== GAME SETUP =====
void Setup()
{
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;

    for(i=0;i<obstacleCount;i++)
    {
        obstacleX[i] = rand() % WIDTH;
        obstacleY[i] = rand() % HEIGHT;
        obstacleDirX[i] = (rand()%2==0)?1:-1;
        obstacleDirY[i] = (rand()%2==0)?1:-1;
        obstacleColor[i] = 1 + rand()%14;
    }

    LoadHighScore();
}

// ===== DRAW GAME =====
void Draw()
{
    GotoXY(0,0);
    SetColor(11);
    printf("\n\n                    S N A K E   G A M E\n\n");

    SetColor(14);
    printf("     +");
    for(i=0;i<WIDTH;i++) printf("-");
    printf("+\n");

    for(i=0;i<HEIGHT;i++)
    {
        printf("     |");
        for(j=0;j<WIDTH;j++)
        {
            if(i==y && j==x){ SetColor(10); printf("O"); }
            else if(i==fruitY && j==fruitX){ SetColor(12); printf("*"); }
            else
            {
                int printed = 0;
                for(k=0;k<obstacleCount;k++)
                    if(obstacleX[k]==j && obstacleY[k]==i)
                    { SetColor(obstacleColor[k]); printf("@"); printed=1; break; }

                if(!printed)
                {
                    int print=0;
                    for(k=0;k<nTail;k++)
                        if(tailX[k]==j && tailY[k]==i)
                        { SetColor(2); printf("o"); print=1; break; }
                    if(!print) printf(" ");
                }
            }
        }
        SetColor(14); printf("|\n");
    }

    printf("     +");
    for(i=0;i<WIDTH;i++) printf("-");
    printf("+\n");

    SetColor(11);
    printf("\n              SCORE : %d",score);
    printf("\n              HIGH SCORE : %d\n",highScore);
}

// ===== INPUT =====
void Input()
{
    if(kbhit())
    {
        char ch = getch();
        if(ch==0 || ch==-32){ ch=getch();
            switch(ch){ case 72: dir=UP; break; case 80: dir=DOWN; break; case 75: dir=LEFT; break; case 77: dir=RIGHT; break; }
        }
        else if(ch=='x') gameOver=1;
    }
}

// ===== LOGIC =====
void Logic()
{
    // Tail movement
    prevX=tailX[0]; prevY=tailY[0];
    tailX[0]=x; tailY[0]=y;
    for(i=1;i<nTail;i++)
    {
        prev2X=tailX[i]; prev2Y=tailY[i];
        tailX[i]=prevX; tailY[i]=prevY;
        prevX=prev2X; prevY=prev2Y;
    }

    // Snake move
    switch(dir){ case LEFT:x--; break; case RIGHT:x++; break; case UP:y--; break; case DOWN:y++; break; }

    // Move Obstacles
    for(i=0;i<obstacleCount;i++)
    {
        obstacleX[i]+=obstacleDirX[i]; obstacleY[i]+=obstacleDirY[i];
        if(obstacleX[i]>=WIDTH || obstacleX[i]<0) obstacleDirX[i]*=-1;
        if(obstacleY[i]>=HEIGHT || obstacleY[i]<0) obstacleDirY[i]*=-1;
        obstacleColor[i]=1+rand()%14;
    }

    // Collisions
    if(x>=WIDTH || x<0 || y>=HEIGHT || y<0) gameOver=1;
    for(i=0;i<nTail;i++) if(tailX[i]==x && tailY[i]==y) gameOver=1;
    for(i=0;i<obstacleCount;i++) if(x==obstacleX[i] && y==obstacleY[i]) gameOver=1;

    // Fruit
    if(x==fruitX && y==fruitY)
    {
        score+=10;
        fruitX=rand()%WIDTH; fruitY=rand()%HEIGHT;
        nTail++;
        if(score%30==0) GenerateSuddenObstacle();
        if(score>highScore){ highScore=score; SaveHighScore(); }
    }
}

// ===== GAME OVER =====
void BigGameOver()
{
    system("cls");
    SetColor(12);
    printf("\n\n\n\n");
    printf("                    G A M E   O V E R\n\n");

    SetColor(14);
    printf("                    FINAL SCORE : %d\n",score);
    printf("                    HIGH SCORE  : %d\n",highScore);

    Beep(800,600); Sleep(200); Beep(600,900);
}
// ===== SUDOKU GAME =====

/* ---------- Sudoku Globals ---------- */
int  SDK_MODE;
int  SDK_ROWS, SDK_COLS, SDK_BLK;
int  sdk_board[9][9];
int  sdk_solved[9][9];
bool sdk_isClue[9][9];
int  sdk_curR = 0, sdk_curC = 0;
int  sdk_mistakes = 0;
bool sdk_wrong[9][9];
time_t sdk_startTime;
char sdk_statusMsg[256] = "";

/* --- Platform helpers (Windows, ANSI already enabled by main) --- */
#define SDK_KEY_UP    1000
#define SDK_KEY_DOWN  1001
#define SDK_KEY_LEFT  1002
#define SDK_KEY_RIGHT 1003

void sdk_enableRaw()  { printf("\033[?25l"); fflush(stdout); }
void sdk_disableRaw() { printf("\033[?25h"); fflush(stdout); }

int sdk_readKey() {
    int c = _getch();
    if (c == 0 || c == 224) {
        int c2 = _getch();
        switch (c2) {
            case 72: return SDK_KEY_UP;
            case 80: return SDK_KEY_DOWN;
            case 75: return SDK_KEY_LEFT;
            case 77: return SDK_KEY_RIGHT;
        }
        return c;
    }
    return c;
}

/* --- Generation --- */
void sdk_shuffleArr(int *a, int n) {
    for (int i=n-1; i>0; i--) {
        int j = rand()%(i+1);
        int t = a[i]; a[i]=a[j]; a[j]=t;
    }
}

void sdk_fillBlock(int sr, int sc) {
    int nums[9] = {1,2,3,4,5,6,7,8,9};
    sdk_shuffleArr(nums, 9);
    int k=0;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            sdk_solved[sr+i][sc+j] = nums[k++];
}

bool sdk_safe9(int r, int c, int n) {
    for (int x=0;x<9;x++)
        if (sdk_solved[r][x]==n || sdk_solved[x][c]==n) return false;
    int sr=r-r%3, sc=c-c%3;
    for (int i=0;i<3;i++) for (int j=0;j<3;j++)
        if (sdk_solved[sr+i][sc+j]==n) return false;
    return true;
}

bool sdk_solve9(int r, int c) {
    if (r==9) return true;
    if (c==9) return sdk_solve9(r+1,0);
    if (sdk_solved[r][c]!=0) return sdk_solve9(r,c+1);
    int nums[9]={1,2,3,4,5,6,7,8,9};
    sdk_shuffleArr(nums,9);
    for (int i=0;i<9;i++) {
        if (sdk_safe9(r,c,nums[i])) {
            sdk_solved[r][c]=nums[i];
            if (sdk_solve9(r,c+1)) return true;
            sdk_solved[r][c]=0;
        }
    }
    return false;
}

void sdk_generateSolution() {
    memset(sdk_solved,0,sizeof(sdk_solved));
    if      (SDK_MODE==1) { sdk_fillBlock(0,0); }
    else if (SDK_MODE==2) { sdk_fillBlock(0,0); sdk_fillBlock(0,3); sdk_fillBlock(3,0); sdk_fillBlock(3,3); }
    else                  { sdk_solve9(0,0); }
}

void sdk_makePuzzle(int rmv) {
    for (int i=0;i<SDK_ROWS;i++) for (int j=0;j<SDK_COLS;j++) {
        sdk_board[i][j]  = sdk_solved[i][j];
        sdk_isClue[i][j] = true;
        sdk_wrong[i][j]  = false;
    }
    int removed=0, att=0;
    while (removed<rmv && att<10000) {
        int r=rand()%SDK_ROWS, c=rand()%SDK_COLS;
        if (sdk_board[r][c]!=0) { sdk_board[r][c]=0; sdk_isClue[r][c]=false; removed++; }
        att++;
    }
}

/* --- Display --- */
const char* sdk_cellBg(int r, int c) {
    if (r==sdk_curR && c==sdk_curC) return BG_SELECT;
    int bsr=(sdk_curR/3)*3, bsc=(sdk_curC/3)*3;
    if (r>=bsr&&r<bsr+3&&c>=bsc&&c<bsc+3) return BG_BLOCK;
    if (r==sdk_curR||c==sdk_curC) return BG_SAME_RC;
    return "";
}

void sdk_printHBorder() {
    printf("   ");
    for (int j=0; j<SDK_COLS; j++) {
        if (j%3==0) printf(YELLOW "+" RESET);
        printf(YELLOW "---" RESET);
    }
    printf(YELLOW "+\n" RESET);
}

void sdk_printBoard() {
    time_t now = time(0);
    int elapsed = (int)(now - sdk_startTime);
    printf(MAGENTA "      ** S U D O K U **\n" RESET);
    printf(CYAN    "   Time: %d sec   Mistakes: %d/3\n\n" RESET, elapsed, sdk_mistakes);
    printf(DIM "   Arrows=move  1-9=place  0=clear  H=hint  M=menu  Q=quit\n\n" RESET);

    for (int i=0; i<SDK_ROWS; i++) {
        if (i%3==0) sdk_printHBorder();
        for (int j=0; j<SDK_COLS; j++) {
            if (j%3==0) printf(YELLOW "   |" RESET);
            const char *bg = sdk_cellBg(i,j);
            if (sdk_wrong[i][j]) {
                printf("\033[48;5;88m" RED " %d " RESET, sdk_board[i][j]);
            } else if (sdk_board[i][j]==0) {
                if (i==sdk_curR && j==sdk_curC)
                    printf(BG_SELECT "   " RESET);
                else
                    printf("%s " DIM "." RESET " ", bg);
            } else if (sdk_isClue[i][j]) {
                printf("%s" BOLD WHITE " %d " RESET, bg, sdk_board[i][j]);
            } else {
                printf("%s" CYAN " %d " RESET, bg, sdk_board[i][j]);
            }
        }
        printf(YELLOW "   |\n" RESET);
    }
    sdk_printHBorder();
    if (sdk_statusMsg[0]) {
        printf("\n   %s\n", sdk_statusMsg);
    } else {
        printf("\n\n");
    }
}

void sdk_redraw() {
    printf("\033[2J\033[H");
    sdk_printBoard();
    sdk_statusMsg[0] = '\0';
    fflush(stdout);
}

/* --- Game Logic --- */
bool sdk_numInRow(int r, int c, int n) {
    for (int j=0;j<SDK_COLS;j++) if (j!=c && sdk_board[r][j]==n) return true;
    return false;
}
bool sdk_numInCol(int r, int c, int n) {
    for (int i=0;i<SDK_ROWS;i++) if (i!=r && sdk_board[i][c]==n) return true;
    return false;
}
bool sdk_numInBlock(int r, int c, int n) {
    int sr=(r/3)*3, sc=(c/3)*3;
    for (int i=sr;i<sr+3;i++) for (int j=sc;j<sc+3;j++)
        if (!(i==r&&j==c) && sdk_board[i][j]==n) return true;
    return false;
}
bool sdk_isComplete() {
    for (int i=0;i<SDK_ROWS;i++) for (int j=0;j<SDK_COLS;j++)
        if (sdk_board[i][j]==0) return false;
    return true;
}
void sdk_giveHint() {
    for (int i=0;i<SDK_ROWS;i++) for (int j=0;j<SDK_COLS;j++)
        if (!sdk_isClue[i][j] && sdk_board[i][j]==0) {
            sdk_board[i][j] = sdk_solved[i][j];
            snprintf(sdk_statusMsg,sizeof(sdk_statusMsg),
                CYAN "  Hint revealed at row %d, col %d!" RESET, i+1, j+1);
            return;
        }
    snprintf(sdk_statusMsg,sizeof(sdk_statusMsg), YELLOW "  No empty cells left!" RESET);
}
void sdk_placeNumber(int num) {
    int r=sdk_curR, c=sdk_curC;
    if (sdk_isClue[r][c]) {
        snprintf(sdk_statusMsg,sizeof(sdk_statusMsg), RED "  X Cannot edit a clue cell!" RESET);
        return;
    }
    if (num==0) {
        if (sdk_wrong[r][c]) { sdk_wrong[r][c]=false; if(sdk_mistakes>0) sdk_mistakes--; }
        sdk_board[r][c]=0;
        snprintf(sdk_statusMsg,sizeof(sdk_statusMsg), DIM "  Cleared." RESET);
        return;
    }
    if (sdk_wrong[r][c]) { sdk_wrong[r][c]=false; sdk_board[r][c]=0; }
    bool conflict=false; char where[32]="";
    if (SDK_MODE==1) {
        if (sdk_numInBlock(r,c,num)) { conflict=true; strcpy(where,"block"); }
    } else {
        if      (sdk_numInRow(r,c,num))   { conflict=true; strcpy(where,"row");    }
        else if (sdk_numInCol(r,c,num))   { conflict=true; strcpy(where,"column"); }
        else if (sdk_numInBlock(r,c,num)) { conflict=true; strcpy(where,"block");  }
    }
    sdk_board[r][c]=num;
    if (conflict) {
        sdk_mistakes++;
        sdk_wrong[r][c]=true;
        snprintf(sdk_statusMsg,sizeof(sdk_statusMsg),
            RED "  X %d already in this %s! Mistakes: %d/3" RESET, num, where, sdk_mistakes);
    } else {
        sdk_wrong[r][c]=false;
        snprintf(sdk_statusMsg,sizeof(sdk_statusMsg), GREEN "  + Placed %d!" RESET, num);
    }
}

/* --- Post-Game Prompt: 0=quit, 1=back to menu, 2=play again --- */
int sdk_postGamePrompt() {
    printf("\n");
    printf(CYAN "   +----------------------------------+\n" RESET);
    printf(CYAN "   |  " YELLOW "P" CYAN " = Play Again (same mode)      |\n" RESET);
    printf(CYAN "   |  " YELLOW "M" CYAN " = Back to Games Menu          |\n" RESET);
    printf(CYAN "   |  " YELLOW "Q" CYAN " = Quit to Main Menu           |\n" RESET);
    printf(CYAN "   +----------------------------------+\n" RESET);
    printf("   Your choice: ");
    fflush(stdout);
    sdk_enableRaw();
    while (1) {
        int k = sdk_readKey();
        if (k=='p'||k=='P') { sdk_disableRaw(); return 2; }
        if (k=='m'||k=='M') { sdk_disableRaw(); return 1; }
        if (k=='q'||k=='Q') { sdk_disableRaw(); return 1; } /* back to menu */
    }
}

/* --- Game Loop: 0=quit, 1=back to menu, 2=play again --- */
int sdk_playGame() {
    sdk_startTime = time(0);
    sdk_curR=0; sdk_curC=0;
    sdk_mistakes=0;
    memset(sdk_wrong,0,sizeof(sdk_wrong));
    sdk_statusMsg[0]='\0';
    sdk_enableRaw();
    while (1) {
        sdk_redraw();
        if (sdk_mistakes>=3) {
            sdk_redraw();
            printf(RED "   GAME OVER! 3 mistakes reached.\n" RESET);
            fflush(stdout);
            sdk_disableRaw();
            return sdk_postGamePrompt();
        }
        if (sdk_isComplete()) {
            time_t end=time(0);
            sdk_redraw();
            printf(GREEN "   *** PUZZLE SOLVED! Time: %d sec  Mistakes: %d/3\n" RESET,
                   (int)(end-sdk_startTime), sdk_mistakes);
            fflush(stdout);
            sdk_disableRaw();
            return sdk_postGamePrompt();
        }
        int key = sdk_readKey();
        switch (key) {
            case SDK_KEY_UP:    if (sdk_curR>0)          sdk_curR--; break;
            case SDK_KEY_DOWN:  if (sdk_curR<SDK_ROWS-1) sdk_curR++; break;
            case SDK_KEY_LEFT:  if (sdk_curC>0)          sdk_curC--; break;
            case SDK_KEY_RIGHT: if (sdk_curC<SDK_COLS-1) sdk_curC++; break;
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                sdk_placeNumber(key-'0'); break;
            case '0': case 127: case '\b':
                sdk_placeNumber(0); break;
            case 'h': case 'H': sdk_giveHint(); break;
            case 'm': case 'M':
                sdk_disableRaw();
                printf("\033[2J\033[H");
                fflush(stdout);
                return 1;
            case 'q': case 'Q':
                sdk_disableRaw();
                printf("\033[2J\033[H");
                fflush(stdout);
                return 1;
        }
    }
}

/* --- Sudoku entry point called from Games menu --- */
void playSudoku() {
    /* Enable ANSI on Windows */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(65001);

    while (1) {
        system(CLEAR);
        printf(CYAN "\n   +==============================+\n");
        printf(     "   |    S U D O K U   G A M E    |\n");
        printf(     "   +==============================+\n\n" RESET);
        printf("   Choose mode:\n\n");
        printf("   " YELLOW "1" RESET " = 1x1  | 1 block  |  3x3 grid |  9 cells\n");
        printf("   " YELLOW "2" RESET " = 2x2  | 4 blocks |  6x6 grid | 36 cells\n");
        printf("   " YELLOW "3" RESET " = 3x3  | 9 blocks |  9x9 grid | 81 cells (Classic)\n");
        printf("   " YELLOW "0" RESET " = Back to Games Menu\n");
        printf("\n   Enter choice: ");
        fflush(stdout);

        /* Flush any leftover newline from previous scanf in main/games menu */
        { int ch; while ((ch = getchar()) != '\n' && ch != EOF); }

        int modeInput = 0;
        char modeChar = getchar();          /* read exactly one char */
        /* flush rest of line */
        { int ch; while ((ch = getchar()) != '\n' && ch != EOF); }

        if (modeChar == '0') return;        /* back to games menu */

        modeInput = modeChar - '0';
        if (modeInput < 1 || modeInput > 3) {
            printf(RED "\n   Invalid choice! Press Enter to try again..." RESET);
            fflush(stdout);
            continue;
        }
        SDK_MODE = modeInput;

        SDK_BLK  = 3;
        SDK_ROWS = (SDK_MODE==1)?3:(SDK_MODE==2)?6:9;
        SDK_COLS = SDK_ROWS;

        int result=2;
        while (result==2) {
            sdk_generateSolution();
            int rmv=(SDK_MODE==1)?5:(SDK_MODE==2)?18:45;
            sdk_makePuzzle(rmv);
            printf("\033[2J\033[H");
            printf("\n   " GREEN "Puzzle ready!" RESET
                   "  Arrows=move  1-9=place  0=clear  H=hint  M=menu  Q=quit\n");
            printf("   Press " YELLOW "Enter" RESET " to start... ");
            fflush(stdout);
            /* wait for Enter — buffer is already clean here */
            while (getchar() != '\n');
            result = sdk_playGame();
        }
        /* result==1 → back to sudoku mode picker (outer while) */
    }
}


// ===== J.A.R.V.I.S. — AI ASSISTANT =====
/* Platform macros required by Jarvis (not duplicated from main) */
#ifdef _WIN32
  #define CLEAR_CMD      "cls"
  #define TMP_PAYLOAD    "C:\\Windows\\Temp\\jarvis_payload.json"
  #define TMP_RESPONSE   "C:\\Windows\\Temp\\jarvis_response.json"
  #define TMP_TTS_TEXT   "C:\\Windows\\Temp\\jarvis_tts.txt"
  #define SLEEP_MS(ms)   Sleep(ms)
  #define PLATFORM_WIN   1
  #ifndef NO_READLINE
    #define NO_READLINE
  #endif
#else
  #define CLEAR_CMD      "clear"
  #define TMP_PAYLOAD    "/tmp/jarvis_payload.json"
  #define TMP_RESPONSE   "/tmp/jarvis_response.json"
  #define TMP_TTS_TEXT   "/tmp/jarvis_tts.txt"
  #define SLEEP_MS(ms)   usleep((ms)*1000)
  #define PLATFORM_WIN   0
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wformat-truncation"
#endif
#ifndef NO_READLINE
  #include <readline/readline.h>
  #include <readline/history.h>
  #define HAVE_READLINE 1
#endif
// Added from jarvis_w_1.c
// Note: Requires Ollama running: ollama serve

/* Jarvis-specific macros (BOLD, DIM already defined above) */
#ifndef RST
  #define RST  RESET
#endif
#define CYN  FG_CYAN
#define GRN  FG_GREEN
#define YLW  FG_YELLOW
#define WHT  FG_WHITE
#define GRY  "\033[90m"

/* ── Config ── */
#define MAX_HIST     32
#define MAX_MSG      8192
#define MAX_RESP     16384
#define MAX_CMD      4096
#define DEF_URL      "http://localhost:11434/api/chat"
#define DEF_MODEL    "gemma4:31b-cloud"

static char g_model[128] = DEF_MODEL;
static char g_url[256]   = DEF_URL;
static int  g_voice      = 1;   /* voice output ON by default — toggle with /voice */
static int  g_running    = 1;

typedef struct { char role[16]; char content[MAX_MSG]; } Msg;
static Msg g_hist[MAX_HIST];
static int g_hlen = 0;

static const char *SYS =
    "You are J.A.R.V.I.S, Tony Stark's AI assistant. "
    "Be concise, intelligent, and slightly witty. "
    "This system runs Windows. When the user asks for a terminal command, "
    "provide ONLY a Windows CMD command (not PowerShell, not Linux/bash). "
    "Put the command on its own line in this exact format: CMD: <command>\n"
    "Example: CMD: dir C:\\Users\n"
    "Never suggest Linux commands like ls, cat, grep, rm. "
    "Use dir, type, findstr, del, copy, move, mkdir, tasklist instead. "
    "Answer in 1-3 sentences. Never break character.";

/* ── Enable Windows ANSI ── */
static void enable_ansi(void) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    if (GetConsoleMode(h, &m))
        SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(65001);
#endif
}

/* ── Utilities ── */
static char *trim(char *s) {
    while (isspace((unsigned char)*s)) s++;
    char *e = s + strlen(s) - 1;
    while (e > s && isspace((unsigned char)*e)) *e-- = '\0';
    return s;
}

static void json_esc(const char *src, char *dst, size_t n) {
    size_t j = 0;
    for (size_t i = 0; src[i] && j+4 < n; i++) {
        unsigned char c = src[i];
        if      (c=='"')  { dst[j++]='\\'; dst[j++]='"';  }
        else if (c=='\\') { dst[j++]='\\'; dst[j++]='\\'; }
        else if (c=='\n') { dst[j++]='\\'; dst[j++]='n';  }
        else if (c=='\r') { dst[j++]='\\'; dst[j++]='r';  }
        else if (c=='\t') { dst[j++]='\\'; dst[j++]='t';  }
        else if (c>=0x20) dst[j++]=c;
    }
    dst[j] = '\0';
}

static int json_get(const char *src, const char *key, char *dst, size_t n) {
    char pat[128]; snprintf(pat, sizeof(pat), "\"%s\":\"", key);
    const char *p = strstr(src, pat); if (!p) return 0;
    p += strlen(pat);
    size_t i = 0;
    while (*p && i+1 < n) {
        if (*p=='\\' && *(p+1)) {
            p++;
            if      (*p=='n')  dst[i++]='\n';
            else if (*p=='t')  dst[i++]='\t';
            else if (*p=='"')  dst[i++]='"';
            else if (*p=='\\') dst[i++]='\\';
            else               dst[i++]=*p;
            p++;
        } else if (*p=='"') break;
        else dst[i++]=*p++;
    }
    dst[i]='\0'; return i>0;
}

/* ── Run a command completely hidden — no window flash, no minimize ──────
 *  Uses CreateProcess with CREATE_NO_WINDOW instead of system().
 *  wait=1 → blocks until the process finishes (e.g. TTS, curl).
 *  wait=0 → fire-and-forget (not used currently).
 * ─────────────────────────────────────────────────────────────────────── */
static int run_hidden(const char *cmd, int wait) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb          = sizeof(si);
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;

    /* Redirect stdin/stdout/stderr to NUL so no console output appears */
    HANDLE hNul = CreateFileA("NUL", GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, 0, NULL);
    si.hStdInput  = hNul;
    si.hStdOutput = hNul;
    si.hStdError  = hNul;

    char buf[MAX_CMD * 2];
    strncpy(buf, cmd, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    BOOL ok = CreateProcessA(
        NULL, buf,
        NULL, NULL,
        TRUE,               /* inherit handles (for NUL redirect) */
        CREATE_NO_WINDOW,
        NULL, NULL,
        &si, &pi
    );

    if (hNul != INVALID_HANDLE_VALUE) CloseHandle(hNul);
    if (!ok) return -1;

    if (wait) WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exit_code = 0;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return (int)exit_code;
}

/* ── TTS — PowerShell System.Speech (built-in, no extra libs needed) ────
 *  Writes cleaned text to a temp file then calls PowerShell to speak it.
 *  Works with MinGW gcc — no sapi.lib / ole32.lib / COM required.
 *  Only needs: windows.h (already included above).
 *  Press ENTER at any time to stop Jarvis mid-speech.
 * ─────────────────────────────────────────────────────────────────────── */

/* ── Escape single quotes for PowerShell string literals ── */
static void ps_escape_single_quotes(const char *src, char *dst, size_t n) {
    size_t j = 0;
    if (n == 0) return;
    for (size_t i = 0; src[i] && j + 2 < n; i++) {
        if (src[i] == '\'') {
            dst[j++] = '\'';
            dst[j++] = '\'';
        } else {
            dst[j++] = src[i];
        }
    }
    dst[j] = '\0';
}

static int is_tts_available(void) {
#ifdef _WIN32
    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd),
        "powershell.exe -NoProfile -Command \""
        "try { Add-Type -AssemblyName System.Speech; $s = New-Object System.Speech.Synthesis.SpeechSynthesizer; $s.GetInstalledVoices() | Out-Null; exit 0 } catch { exit 1 } \"");
    return (run_hidden(cmd, 1) == 0);
#else
    return 0;
#endif
}

/* ── speak_async: launch TTS without waiting, return process handle ── */
static HANDLE speak_start(const char *text) {
    if (!g_voice) return INVALID_HANDLE_VALUE;
    if (!is_tts_available()) {
        printf(YLW "  [Voice unavailable: no Windows TTS voice detected. Check system sound or speech settings.]\n" RST);
        return INVALID_HANDLE_VALUE;
    }

    /* Strip ANSI escape codes and markdown symbols */
    char clean[MAX_MSG];
    size_t j = 0;
    for (size_t i = 0; text[i] && j + 1 < sizeof(clean); i++) {
        unsigned char c = (unsigned char)text[i];
        if (c == '*' || c == '_' || c == '`' || c == '#') continue;
        if (c == '\033') {
            while (text[i] && text[i] != 'm') i++;
            continue;
        }
        clean[j++] = (char)c;
    }
    clean[j] = '\0';

    char safe_text[MAX_MSG];
    ps_escape_single_quotes(clean, safe_text, sizeof(safe_text));

    /* Prefer SAPI.SpVoice; it is often more reliable than System.Speech on Windows.
       Fall back to System.Speech if SAPI is unavailable or the default voice is missing. */
    char ps[MAX_CMD * 3];
    snprintf(ps, sizeof(ps),
        "powershell.exe -NoProfile -WindowStyle Hidden -Command \""
        "try { $v = New-Object -ComObject SAPI.SpVoice; $v.Volume = 100; $v.Rate = 0; $v.Speak('%s'); exit 0 } "
        "catch { Add-Type -AssemblyName System.Speech; $s = New-Object System.Speech.Synthesis.SpeechSynthesizer; $s.Rate = 0; $s.Volume = 100; $s.Speak('%s'); } \"",
        safe_text, safe_text);

    char cmd[MAX_CMD * 3];
    snprintf(cmd, sizeof(cmd), "cmd.exe /c %s", ps);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); ZeroMemory(&pi, sizeof(pi));
    si.cb          = sizeof(si);
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;

    HANDLE hNul = CreateFileA("NUL", GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, 0, NULL);
    si.hStdInput  = hNul;
    si.hStdOutput = hNul;
    si.hStdError  = hNul;

    char buf[MAX_CMD * 3];
    strncpy(buf, cmd, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    BOOL ok = CreateProcessA(NULL, buf, NULL, NULL, TRUE,
                             CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    if (hNul != INVALID_HANDLE_VALUE) CloseHandle(hNul);
    if (!ok) return INVALID_HANDLE_VALUE;

    CloseHandle(pi.hThread);
    return pi.hProcess;
}

static void speak(const char *text) {
    if (!g_voice) return;

    /* Start TTS in background */
    HANDLE hProc = speak_start(text);

    printf(GRY "  [Speaking... press " RST YLW BOLD "/" RST GRY " to interrupt]" RST "\n");
    fflush(stdout);

    /* Poll: finish when TTS ends OR user presses '/' */
    while (hProc != INVALID_HANDLE_VALUE) {
        /* Check if TTS process finished on its own */
        DWORD state = WaitForSingleObject(hProc, 50); /* 50 ms timeout */
        if (state == WAIT_OBJECT_0) {
            /* TTS finished naturally */
            CloseHandle(hProc);
            hProc = INVALID_HANDLE_VALUE;
            break;
        }

        /* Check if user pressed '/' */
        if (_kbhit()) {
            int ch = _getch();
            if (ch == '/') {
                /* Kill the entire process tree (cmd.exe + powershell child).
                   TerminateProcess alone only kills cmd.exe; the spawned
                   powershell.exe keeps speaking and causes overlap. */
                DWORD pid = GetProcessId(hProc);
                if (pid) {
                    char kill_cmd[64];
                    snprintf(kill_cmd, sizeof(kill_cmd),
                             "taskkill /F /T /PID %lu >nul 2>&1", (unsigned long)pid);
                    system(kill_cmd);
                }
                WaitForSingleObject(hProc, 500);
                CloseHandle(hProc);
                hProc = INVALID_HANDLE_VALUE;
                printf(YLW "  [Interrupted]\n" RST);
                fflush(stdout);
                break;
            }
        }
    }
}

/* ── Build JSON payload ── */
static void build_payload(const char *input) {
    FILE *f = fopen(TMP_PAYLOAD, "w");
    if (!f) return;
    static char es[MAX_MSG*2], ec[MAX_MSG*2], er[64];
    json_esc(SYS, es, sizeof(es));
    fprintf(f,"{\n\"model\":\"%s\",\n\"stream\":false,\n\"messages\":[\n", g_model);
    fprintf(f,"{\"role\":\"system\",\"content\":\"%s\"}", es);
    for (int i=0; i<g_hlen; i++) {
        json_esc(g_hist[i].role,    er, sizeof(er));
        json_esc(g_hist[i].content, ec, sizeof(ec));
        fprintf(f,",\n{\"role\":\"%s\",\"content\":\"%s\"}", er, ec);
    }
    json_esc(input, ec, sizeof(ec));
    fprintf(f,",\n{\"role\":\"user\",\"content\":\"%s\"}\n]}\n", ec);
    fclose(f);
}

/* ── Query Ollama ── */
static int query(const char *input, char *reply, size_t rsz) {
    build_payload(input);
    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd),
        "curl -s -X POST \"%s\" "
        "-H \"Content-Type: application/json\" "
        "--data @\"%s\" -o \"%s\" --max-time 60",
        g_url, TMP_PAYLOAD, TMP_RESPONSE);

    printf(CYN "  Thinking " RST);
    fflush(stdout);

    /* run_hidden() — no window flash, no minimize */
#ifdef _WIN32
    int ret = run_hidden(cmd, 1);
    printf("\r                  \r"); fflush(stdout);
    if (ret) {
        snprintf(reply,rsz,"[ERROR] curl failed. Is Ollama running?\n  Run: ollama serve && ollama run %s", g_model);
        return 0;
    }
#else
    const char *spin[] = {"|","/","-","\\"};
    FILE *p = popen(cmd, "r"); int si=0;
    if (p) {
        char buf[64];
        while (fgets(buf, sizeof(buf), p)) { /* silent */ }
        /* spin while waiting */
        for (int i=0;i<40;i++) {
            printf("\r" CYN "  Thinking %s" RST "  ", spin[si++%4]);
            fflush(stdout); SLEEP_MS(80);
        }
        pclose(p);
    } else {
        system(cmd);
    }
    printf("\r                        \r"); fflush(stdout);
#endif

    FILE *f = fopen(TMP_RESPONSE, "r");
    if (!f) { snprintf(reply,rsz,"[ERROR] No response file."); return 0; }
    static char raw[MAX_RESP];
    size_t n = fread(raw,1,sizeof(raw)-1,f); fclose(f); raw[n]='\0';

    if (!json_get(raw,"content",reply,rsz))
        if (!json_get(raw,"response",reply,rsz)) {
            static char em[256];
            if (json_get(raw,"error",em,sizeof(em)))
                snprintf(reply,rsz,"[Ollama] %s", em);
            else
                snprintf(reply,rsz,"[ERROR] Bad response: %.200s", raw);
            return 0;
        }
    return 1;
}

/* ── Print reply + optional command block ── */
static void print_reply(const char *reply) {
    static char cmd[MAX_CMD], txt[MAX_RESP];
    int has_cmd = 0;

    /* Only match CMD: at the very start of a line (not mid-sentence) */
    const char *p = NULL;
    const char *search = reply;
    while (*search) {
        /* Match at start of string or after a newline */
        if (strncmp(search, "CMD:", 4) == 0 &&
            (search == reply || *(search-1) == '\n')) {
            p = search;
            break;
        }
        search++;
    }

    if (p) {
        /* Copy everything before CMD: line into txt */
        size_t pre = (size_t)(p - reply);
        if (pre >= sizeof(txt)) pre = sizeof(txt) - 1;
        memcpy(txt, reply, pre); txt[pre] = '\0';

        /* Extract the command after "CMD:" */
        p += 4;
        while (*p == ' ') p++;          /* skip spaces after CMD: */

        size_t i = 0;
        while (*p && *p != '\n' && i + 1 < sizeof(cmd))
            cmd[i++] = *p++;
        cmd[i] = '\0';

        /* Strip backticks and surrounding whitespace from the command */
        {
            char *s = cmd;
            /* Remove leading backticks/spaces */
            while (*s == '`' || *s == ' ') s++;
            if (s != cmd) memmove(cmd, s, strlen(s) + 1);
            /* Remove trailing backticks/spaces */
            size_t len = strlen(cmd);
            while (len > 0 && (cmd[len-1] == '`' || cmd[len-1] == ' '))
                cmd[--len] = '\0';
        }

        /* Append any text after the CMD: line */
        while (*p == '\n') p++;
        strncat(txt, "\n", sizeof(txt) - strlen(txt) - 1);
        strncat(txt, p,   sizeof(txt) - strlen(txt) - 1);

        /* Only flag as valid if command is non-empty */
        has_cmd = (cmd[0] != '\0');
    } else {
        size_t l = strlen(reply);
        if (l >= sizeof(txt)) l = sizeof(txt) - 1;
        memcpy(txt, reply, l); txt[l] = '\0';
    }

    time_t t=time(NULL); struct tm *tm=localtime(&t);
    printf(GRY "  [%02d:%02d:%02d] " RST CYN BOLD "JARVIS\n" RST,
           tm->tm_hour,tm->tm_min,tm->tm_sec);

    char *tt = trim(txt);
    if (tt&&*tt) printf(WHT "  %s\n" RST, tt);

    if (has_cmd) {
        char *c = trim(cmd);
        printf("\n" GRN BOLD
            "  +--[ TERMINAL COMMAND ]------------------------------\n"
            "  |  > %s\n"
            "  +----------------------------------------------------\n" RST, c);
        printf(YLW "  Run this command? [y/N] " RST); fflush(stdout);
        char ch[8]={0};
        if (fgets(ch,sizeof(ch),stdin) && (ch[0]=='y'||ch[0]=='Y')) {
            printf(DIM GRN "\n  -- Output ------------------------------------------\n" RST);
            fflush(stdout);
            int r = system(c);
            printf(DIM GRN "  -- Exit code: %d -----------------------------------\n\n" RST, r);
        } else { printf(DIM "  (Skipped)\n\n" RST); }
    } else { printf("\n"); }
}

/* ── History ── */
static void push(const char *role, const char *content) {
    int idx;
    if (g_hlen < MAX_HIST) idx = g_hlen++;
    else { memmove(g_hist,g_hist+1,sizeof(Msg)*(MAX_HIST-1)); idx=MAX_HIST-1; }
    strncpy(g_hist[idx].role,    role,    15); g_hist[idx].role[15]='\0';
    strncpy(g_hist[idx].content, content, MAX_MSG-1); g_hist[idx].content[MAX_MSG-1]='\0';
}

/* ── Banner ── */
static void banner(void) {
    printf(CYN BOLD
        "  +====================================================+\n"
        "  |   J . A . R . V . I . S                           |\n"
        "  |   Just A Rather Very Intelligent System  v3.2     |\n"
        "  |   Model : %-20s                    |\n"
        "  +====================================================+\n" RST
        DIM CYN
        "  Voice: %s  |  Platform: Windows\n"
        "  URL  : %s\n\n" RST,
        g_model,
        g_voice ? "ON  (/voice to toggle)" : "OFF (/voice to toggle)",
        g_url);
}

/* ── Built-ins ── */
static int builtin(const char *s) {
    if (!strcmp(s,"/quit")||!strcmp(s,"/exit")||!strcmp(s,"exit")) {
        printf(CYN BOLD "\n  Goodbye, sir.\n\n" RST); g_running=0; return 1; }
    if (!strcmp(s,"/clear"))   { (void)system(CLEAR_CMD); banner(); return 1; }
    if (!strcmp(s,"/reset"))   { g_hlen=0; printf(YLW "  Memory cleared.\n\n" RST); return 1; }
    if (!strcmp(s,"/voice"))   { g_voice=!g_voice; printf(YLW "  Voice: %s\n\n" RST,g_voice?"ON":"OFF"); return 1; }
    if (!strncmp(s,"/model ",7)){ strncpy(g_model,s+7,sizeof(g_model)-1); printf(YLW "  Model: %s\n\n" RST,g_model); return 1; }
    if (!strcmp(s,"/help")) {
        printf(CYN BOLD "\n  Commands:\n" RST DIM
            "  /voice   — toggle voice output (currently %s)\n"
            "  /model X — switch Ollama model\n"
            "  /clear   — clear screen\n"
            "  /reset   — clear conversation memory\n"
            "  /history — show conversation history\n"
            "  /quit    — exit Jarvis\n\n" RST,
            g_voice ? "ON" : "OFF");
        return 1; }
    if (!strcmp(s,"/history")) {
        for (int i=0;i<g_hlen;i++) printf(DIM "  [%d] %s: %.70s\n" RST,i+1,g_hist[i].role,g_hist[i].content);
        printf("\n"); return 1; }
    return 0;
}

/* ── Signal handler (Windows) ── */
static BOOL WINAPI winsig(DWORD t) {
    if (t==CTRL_C_EVENT){ printf(CYN "\n\n  Goodbye, sir.\n\n" RST); exit(0); }
    return FALSE; }

/* ── MAIN ── */

void runJarvis(void) {
    g_running = 1;   /* reset every launch — fixes "offline immediately" on reopen */
    enable_ansi();
    SetConsoleCtrlHandler(winsig, TRUE);

    srand((unsigned)time(NULL));
    (void)system(CLEAR_CMD);
    banner();
    printf(DIM
        "  Voice output is ON. Type your question below.\n"
        "  Type /help for all commands.\n"
        "  Make sure Ollama is running: ollama serve\n\n" RST);

    static char reply[MAX_RESP];
    if (query("Greet me as Jarvis in one sentence.", reply, sizeof(reply))) {
        print_reply(reply);
        speak(reply);
        push("assistant", reply);
    }
    printf(DIM CYN "  ------------------------------------------------------\n" RST);

    while (g_running) {
        static char buf[MAX_MSG];

        printf(YLW BOLD "  YOU: " RST); fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) { g_running = 0; break; }
        buf[strcspn(buf, "\n")] = '\0';

        char *inp = trim(buf);
        if (!inp || !*inp) continue;
        if (builtin(inp))  continue;

        printf("\n");
        push("user", inp);
        if (query(inp, reply, sizeof(reply))) {
            print_reply(reply);
            speak(reply);
            push("assistant", reply);
        } else {
            printf(FG_RED "  %s\n\n" RST, reply);
        }
        printf(DIM CYN "  ------------------------------------------------------\n" RST);
    }

    printf(CYN "\n  Jarvis offline.\n\n" RST);
}

// ===== END J.A.R.V.I.S. =====

// ===== APPS LAUNCHER =====

void pauseScreen() {
    printf(YELLOW "\nPress Enter to continue..." RESET);
    getchar();
}

void menu() {
    printf(CYAN);
    printf("=====================================\n");
    printf("            APPLICATION MENU         \n");
    printf("=====================================\n");
    printf(RESET);

    printf(GREEN " 1. ChatGPT\n");
    printf(" 2. Instagram\n");
    printf(" 3. WhatsApp\n");
    printf(" 4. YouTube\n");
    printf(" 5. Browser (Google)\n");
    printf(" 6. Netflix\n");
    printf(CYAN  " 7. Jarvis (AI Assistant)\n");
    printf(RED   " 8. Exit\n");
    printf(RESET);
    printf("=====================================\n");
    printf(YELLOW " Enter your choice: " RESET);
}

void apps() {
    int choice;

    while (1) {
        system(CLEAR);
        menu();

        if (scanf("%d", &choice) != 1) {
            printf(RED "\nInvalid input! Numbers only.\n" RESET);
            while (getchar() != '\n');
            pauseScreen();
            continue;
        }

        getchar(); // clear newline
        system(CLEAR);

        switch (choice) {
            case 1:
                printf(GREEN "Opening ChatGPT...\n" RESET);
                system("start https://chat.openai.com");
                break;
            case 2:
                printf(GREEN "Opening Instagram...\n" RESET);
                system("start https://www.instagram.com");
                break;
            case 3:
                printf(GREEN "Opening WhatsApp...\n" RESET);
                system("start https://web.whatsapp.com");
                break;
            case 4:
                printf(GREEN "Opening YouTube...\n" RESET);
                system("start https://www.youtube.com");
                break;
            case 5:
                printf(GREEN "Opening Browser...\n" RESET);
                system("start https://www.google.com");
                break;
            case 6:
                printf(GREEN "Opening Netflix...\n" RESET);
                system("start https://www.netflix.com");
                break;
            case 7:
                printf(CYAN "Launching J.A.R.V.I.S...\n" RESET);
                printf(YLW "Make sure Ollama is running: ollama serve\n" RESET);
                pauseScreen();
                runJarvis();
                break;
            case 8:
                printf(FG_RED "Goodbye!\n" RESET);
                return;
            default:
                printf(FG_RED "Invalid choice! Please enter 1-8.\n" RESET);
        }

        pauseScreen();
    }
}

// ===== WELCOME SCREEN =====

void loadingBar() {
    printf(YELLOW "\n\nLoading...\n" RESET);

    for(int i = 0; i <= 100; i++) {
        printf("\r");
        printf(CYAN "[");

        for(int j = 0; j < i/2; j++)
            printf(GREEN "#");

        for(int j = i/2; j < 50; j++)
            printf(" ");

        printf(CYAN "] %d%%" RESET, i);
        fflush(stdout);
        Sleep(40);
    }
}

void showWelcome() {
    system("cls");

    printf(RED "\n\n\t*********************************\n");
    printf(MAGENTA "\t        W E L C O M E\n");
    printf(RED "\t*********************************\n" RESET);

    loadingBar();

    printf(GREEN "\n\n\tSystem Ready! \n\n" RESET);
    Sleep(800);
    system("cls");
}

// ===== END WELCOME SCREEN =====

int main(int argc, char *argv[]){

    /* ── Open a new CMD window and run this exe inside it ──────────────
     * If launched without --child (e.g. double-click or from IDE), we
     * spawn a new visible cmd.exe window that reruns this exe with the
     * --child flag, then the original process exits immediately.
     * The new window runs the full program normally.
     * ------------------------------------------------------------------ */
    int isChild = 0;
    for(int i = 1; i < argc; i++)
        if(strcmp(argv[i], "--child") == 0) { isChild = 1; break; }

    if(!isChild) {
        char exePath[MAX_PATH];
        GetModuleFileNameA(NULL, exePath, MAX_PATH);   /* full path of this .exe */

        char args[MAX_PATH + 32];
        snprintf(args, sizeof(args), "\"%s\" --child", exePath);

        /* Try Windows Terminal (wt.exe) first — the modern terminal on Win10/11 */
        HINSTANCE res = ShellExecuteA(NULL, "open", "wt.exe", args, NULL, SW_SHOW);

        /* If wt.exe not found (older Windows), fall back to cmd.exe */
        if((INT_PTR)res <= 32) {
            char cmdArgs[MAX_PATH + 32];
            snprintf(cmdArgs, sizeof(cmdArgs), "/K \"%s\" --child", exePath);
            ShellExecuteA(NULL, "open", "cmd.exe", cmdArgs, NULL, SW_SHOW);
        }

        return 0;   /* exit the original/parent process */
    }

    int mainChoice;

    showWelcome();   /* welcome screen + loading bar, then cls */

    while(1){
    system(CLEAR);
    printf(CYAN "=====================================\n" RESET);
    printf(YELLOW "         MAIN MENU\n" RESET);
    printf(CYAN "=====================================\n" RESET);
    printf(GREEN " 1. Games\n 2. Quizzes\n 3. Apps\n" RESET);
    printf(RED   " 0. Exit\n" RESET);
    printf(CYAN "=====================================\n" RESET);
    printf(YELLOW "Enter choice: " RESET);
    scanf("%d",&mainChoice);

    switch(mainChoice){
        case 1: {
            int gameChoice;
            system(CLEAR);
            printf(CYAN "=====================================\n" RESET);
            printf(YELLOW "           GAMES MENU\n" RESET);
            printf(CYAN "=====================================\n" RESET);
            printf(GREEN " 1. Snake Game\n 2. Typing Speed Game\n 3. Sudoku\n" RESET);
            printf(RED   " 0. Back to Main Menu\n" RESET);
            printf(CYAN "=====================================\n" RESET);
            printf(YELLOW "Enter choice: " RESET);
            scanf("%d",&gameChoice);
            system(CLEAR);
            switch(gameChoice){
                case 3:
                    playSudoku();
                    break;
                case 2: {
                    char *sentences[TOTAL_SENTENCES] = {
                        "C programming is very powerful and flexible language",
                        "Practice every day to become a better programmer",
                        "Typing fast and accurate is a very useful skill",
                        "Functions make programs clean and reusable",
                        "Logic is more important than memorizing code",
                        "Pointers are one of the most powerful features in C",
                        "Arrays store multiple values in a single variable",
                        "Loops help repeat tasks efficiently",
                        "Debugging improves problem solving skills",
                        "Consistency is the key to mastery",
                        "Coding requires patience and logical thinking",
                        "Errors help programmers learn faster",
                        "Structure your code for better readability",
                        "Comments explain what the code does",
                        "Variables store data temporarily",
                        "Algorithms solve problems step by step",
                        "Understanding basics builds strong foundation",
                        "Practice makes programming easier",
                        "Never stop learning new concepts",
                        "Confidence grows with experience"
                    };
                    srand(time(NULL));
                    int sentIdx = rand() % TOTAL_SENTENCES;
                    char userText[MAX];

                    printf(SOFT_BLUE "\n======================================\n" RESET);
                    printf(SOFT_PINK  "          Typing Speed Test \n" RESET);
                    printf(SOFT_BLUE "======================================\n\n" RESET);
                    loadingAnimation();
                    printf(SOFT_YELLOW " Type the sentence below carefully:\n\n" RESET);
                    printf(SOFT_GREEN "   \"%s\"\n\n" RESET, sentences[sentIdx]);
                    printf(SOFT_CYAN "Press ENTER to start typing..." RESET);
                    fflush(stdout);
                    /* Step 1: Flush the leftover '\n' from the menu scanf */
                    { int ch; while((ch = getchar()) != '\n' && ch != EOF); }
                    /* Step 2: Now actually wait for the user to press Enter */
                    { int ch; while((ch = getchar()) != '\n' && ch != EOF); }
                    printf("\n" SOFT_ORANGE "Start Typing Below:\n\n" RESET);
                    fflush(stdout);

                    /* Use GetTickCount() for millisecond precision —
                       time_t on Windows only has 1-second resolution     */
                    DWORD tstart = GetTickCount();
                    fgets(userText, MAX, stdin);
                    DWORD tend   = GetTickCount();
                    removeNewline(userText);
                    double timeTaken = (tend - tstart) / 1000.0;  /* seconds */

                    int mistakes = 0;
                    int tcorrect = 0;
                    printf("\n\n");
                    printf(SOFT_BLUE "\n======================================\n" RESET);
                    printf(SOFT_PINK  "                Result " RESET);
                    printf(SOFT_BLUE "\n======================================\n" RESET);
                    compareText(sentences[sentIdx], userText, &mistakes, &tcorrect);
                    int totalOriginalWords = countWords(sentences[sentIdx]);
                    printf("\n\n");
                    printf(SOFT_CYAN "  Time Taken   : %.2f seconds\n", timeTaken);
                    {
                        int typedWords = countWords(userText);
                        double wpm = (timeTaken > 0.0)
                                     ? (typedWords * 60.0) / timeTaken
                                     : 0.0;
                        printf(" Typing Speed  : %.1f WPM\n", wpm);
                    }
                    double accuracy = (tcorrect * 100.0) / totalOriginalWords;
                    printf(" Mistakes      : %d\n", mistakes);
                    printf(" Accuracy      : %.2f%%\n", accuracy);
                    printf("\n" SOFT_BLUE "======================================\n" RESET);
                    printf(SOFT_PINK "         Test Completed \n" RESET);
                    printf(SOFT_BLUE  "======================================\n\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    { int ch; while((ch = getchar()) != '\n' && ch != EOF); }
                    break;
                }
                case 1: {
                    srand(time(0));
                    HideCursor();
                    SelectDifficulty();
                    Setup();
                    while(!gameOver){
                        Draw();
                        Input();
                        Logic();
                        Sleep(speed);
                    }
                    BigGameOver();
                    break;
                }
                case 0:
                    break; /* back to main menu */
                default:
                    printf(RED "Wrong choice\n" RESET);
            }
            break;
        }
        case 2: {
            int quizChoice;
            int quizBack = 0;
            while(1){
                system(CLEAR);
                printf(CYAN "=====================================\n" RESET);
                printf(YELLOW "         QUIZ MENU\n" RESET);
                printf(CYAN "=====================================\n" RESET);
                printf(GREEN " 1. SI Units\n 2. GenZ Quiz\n 3. Tollywood Quiz\n 4. Current Affairs\n 5. C Quiz\n" RESET);
                printf(RED   " 0. Back to Main Menu\n" RESET);
                printf(CYAN "=====================================\n" RESET);
                printf(YELLOW "Enter choice: " RESET);
                scanf("%d",&quizChoice);
                system(CLEAR);
                switch(quizChoice){
                    case 1: {
                        char restart;
                        do {
                            si_quiz();
                            printf(YELLOW "\nPress R to Play Again or Any Other Key to Exit: " RESET);
                            scanf(" %c",&restart);
                            restart=toupper(restart);
                        } while(restart=='R');
                        printf("\033[95m\nThank You For Playing!\n" RESET);
                        break;
                    }
                    case 2: {
                        char restart;
                        do {
                            genz_quiz();
                            printf(YELLOW "\nPress R to Play Again or Any Other Key to Exit: " RESET);
                            scanf(" %c",&restart);
                            restart=toupper(restart);
                        } while(restart=='R');
                        printf("\033[95m\nThank You For Playing!\n" RESET);
                        break;
                    }
                    case 3: {
                        char restart;
                        do {
                            tollywood();
                            printf(YELLOW "\nPress R to Play Again or Any Other Key to Exit: " RESET);
                            scanf(" %c",&restart);
                            restart=toupper(restart);
                        } while(restart=='R');
                        printf("\033[95m\nThank You For Playing!\n" RESET);
                        break;
                    }
                    case 4: {
                        char restart;
                        do {
                            current_affairs_quiz();
                            printf(YELLOW "\nPress R to Play Again or Any Other Key to Exit: " RESET);
                            scanf(" %c",&restart);
                            restart=toupper(restart);
                        } while(restart=='R');
                        printf("\033[95m\nThank You For Playing!\n" RESET);
                        break;
                    }
                    case 5: {
                        char restart;
                        do {
                            quiz();
                            printf(YELLOW "\nPress R to Play Again or Any Other Key to Exit: " RESET);
                            scanf(" %c",&restart);
                            restart=toupper(restart);
                        } while(restart=='R');
                        printf("\033[95m\nThank You For Playing!\n" RESET);
                        break;
                    }
                    case 0:
                        quizBack = 1;
                        break;
                    default:
                        printf(RED "Wrong choice\n" RESET);
                }
                if(quizBack) break;
            }
            break;
        }
        case 3:
            apps();
            break;
        case 0:
            printf(GREEN "Goodbye!\n" RESET);
            exit(0);
            break;
        default:
            printf(RED "Wrong choice\n" RESET);
    }
    } // end main while(1)
    return 0;
}

// ===== TYPING SPEED TEST HELPER FUNCTIONS =====

void loadingAnimation()
{
    printf(SOFT_YELLOW "Loading");
    for(int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(1000);   /* Windows API — milliseconds */
    }
    printf("\n\n" RESET);
}

void removeNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}

int countWords(char str[])
{
    int count = 0, inWord = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(!isspace(str[i]) && inWord == 0)
        {
            inWord = 1;
            count++;
        }
        else if(isspace(str[i]))
        {
            inWord = 0;
        }
    }
    return count;
}

void compareText(char original[], char typed[], int *mistakes, int *correct)
{
    char origCopy[MAX];
    char typedCopy[MAX];
    strcpy(origCopy, original);
    strcpy(typedCopy, typed);
    char *origWords[MAX_WORDS];
    char *typedWords[MAX_WORDS];
    int origCount = 0;
    int typedCount = 0;
    char *token = strtok(origCopy, " ");
    while(token != NULL && origCount < MAX_WORDS)
    {
        origWords[origCount++] = token;
        token = strtok(NULL, " ");
    }
    token = strtok(typedCopy, " ");
    while(token != NULL && typedCount < MAX_WORDS)
    {
        typedWords[typedCount++] = token;
        token = strtok(NULL, " ");
    }
    int max = origCount > typedCount ? origCount : typedCount;
    for(int i = 0; i < max; i++)
    {
        if(i < origCount && i < typedCount)
        {
            if(strcasecmp(origWords[i], typedWords[i]) == 0)
            {
                printf("%s ", typedWords[i]);
                (*correct)++;
            }
            else
            {
                printf(RED "%s " RESET, typedWords[i]);
                (*mistakes)++;
            }
        }
        else if(i < typedCount)
        {
            printf(RED "%s " RESET, typedWords[i]);
            (*mistakes)++;
        }
        else
        {
            printf(RED "[missing] " RESET);
            (*mistakes)++;
        }
    }
}
