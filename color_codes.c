#include<stdio.h>
//Regular text
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

//Regular bold text
#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"

//Regular underline text
#define UNDERLINED_BLACK "\033[4;30m"
#define UNDERLINED_RED "\033[4;31m"
#define UNDERLINED_GREEN "\033[4;32m"
#define UNDERLINED_YELLOW "\033[4;33m"
#define UNDERLINED_BLUE "\033[4;34m"
#define UNDERLINED_MAGENTA "\033[4;35m"
#define UNDERLINED_CYAN "\033[4;36m"
#define UNDERLINED_WHITE "\033[4;37m"

//Regular background
#define BLACK_BACKGROUND "\033[40m"
#define RED_BACKGROUND "\033[41m"
#define GREEN_BACKGROUND "\033[42m"
#define YELLLOW_BACKGROUND "\033[43m"
#define BLUE_BACKGROUND "\033[44m"
#define MAGENTA_BACKGROUND "\033[45m"
#define CYAN_BACKGROUND "\033[46m"
#define WHITE_BACKGROUND "\033[47m"

//High intensty background 
#define BLACK_HIGH_BACKGROUND "\033[0;100m"
#define RED_HIGH_BACKGROUND "\033[0;101m"
#define GREEN_HIGH_BACKGROUND "\033[0;102m"
#define YELLLOW_HIGH_BACKGROUND "\033[0;103m"
#define BLUE_HIGH_BACKGROUND "\033[0;104m"
#define MAGENTA_HIGH_BACKGROUND "\033[0;105m"
#define CYAN_HIGH_BACKGROUND "\033[0;106m"
#define WHITE_HIGH_BACKGROUND "\033[0;107m"

//High intensty text
#define BLACK_HIGH_FOREGROUND "\033[0;90m"
#define RED_HIGH_FOREGROUND "\033[0;91m"
#define GREEN_HIGH_FOREGROUND "\033[0;92m"
#define YELLOW_HIGH_FOREGROUND "\033[0;93m"
#define BLUE_HIGH_FOREGROUND "\033[0;94m"
#define MAGENTA_HIGH_FOREGROUND "\033[0;95m"
#define CYAN_HIGH_FOREGROUND "\033[0;96m"
#define WHITE_HIGH_FOREGROUND "\033[0;97m"

//Bold high intensity text
#define BLACK_BOLD_HIGH_FOREGROUND "\033[1;90m"
#define RED_BOLD_HIGH_FOREGROUND "\033[1;91m"
#define GREEN_BOLD_HIGH_FOREGROUND "\033[1;92m"
#define YELLOW_BOLD_HIGH_FOREGROUND "\033[1;93m"
#define BLUE_BOLD_HIGH_FOREGROUND "\033[1;94m"
#define MAGENTA_BOLD_HIGH_FOREGROUND "\033[1;95m"
#define CYAN_BOLD_HIGH_FOREGROUND "\033[1;96m"
#define WHITE_BOLD_HIGH_FOREGROUND "\033[1;97m"

//Reset
#define RESET "\033[0m"

int main()
{
	printf(BLACK " BLACK" RED " RED" GREEN " GREEN" YELLOW " YELLOW" BLUE " BLUE" MAGENTA " MAGENTA" CYAN " CYAN" WHITE " WHITE" RESET);
}