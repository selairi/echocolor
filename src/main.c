/****************************************************************************
**
**   Copyright (C) 2024 P.L. Lucas
**
**
** LICENSE: BSD
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of developers or companies in the above copyright, Digia Plc and its 
**     Subsidiary(-ies) nor the names of its contributors may be used to 
**     endorse or promote products derived from this software without 
**     specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void print_help(char *command)
{
  printf("%s [--help] [-c color] [-bg color] [-b] [-u] [-i] [-r] Text...\n", command);
  printf("\nPrints color text on Linux/UNIX terminal.\n");
  printf("\n  --help      Prints help.\n");
  printf("  -c color    Set text color to color\n");
  printf("  -bg color   Set background color\n");
  printf("  -b          Set bold text\n");
  printf("  -i          Interchanges text and background colors\n");
  printf("  -u          Set underlined text\n");
  printf("  -r          Set default text\n");
  printf("Available colors:\n");
  printf("    black\n");
  printf("    blue\n");
  printf("    cyan\n");
  printf("    green\n");
  printf("    magenta\n");
  printf("    red\n");
  printf("    white\n");
  printf("    yellow\n");
  printf("\nExamples:\n  %s -b -c red 'Error:' -r 'Syntax error'\n", command);
  printf("  %s '[' -b -c green 'OK' -r ']' 'Example' -b 'Hello world'\n", command);
}

/**
 * Returns true if output is a terminal.
 * @return true if output is a terminal.
 */
bool is_terminal() 
{
  return isatty(1);
}

/**
 * Returns terminal color number for color string.
 *
 * Available colors:
 * - black
 * - blue
 * - cyan
 * - green
 * - magenta
 * - red
 * - white
 * - yellow
 *
 * @param arg Color string
 *
 * @return The terminal color number
*/
int get_color(char *arg)
{
  if(arg[0] == 'b' && arg[1] == 'l') {
    if(arg[2] == 'a') { // Black
      return 30; 
    } else if(arg[2] == 'u') { // Blue
      return 34;
    }
  } else if(arg[0] == 'c') { // Cyan
    return 36;
  } else if(arg[0] == 'g') { // Green
    return 32;
  } else if(arg[0] == 'm') { // Magenta
    return 35;
  } else if(arg[0] == 'r') { // Red
    return 31;
  } else if(arg[0] == 'w') { // White
    return 37;
  } else if(arg[0] == 'y') { // Yellow
    return 33;
  }
  return -1;
}

int main(int argc, char *argv[])
{
  bool need_space = false;
  int color = -1;
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    // Is an option
    if(arg[0] == '-') {
      if(!strcmp(arg, "--help")) {
        print_help(argv[0]);
        return 0;
      } else if(!strcmp(arg, "-c")) {
        // Is a color
        if((i+1) < argc) {
          arg = argv[++i];
          color = get_color(arg);
        }
      } else if(!strcmp(arg, "-bg")) {
        // Is a background
        if((i+1) < argc) {
          arg = argv[++i];
          color = get_color(arg);
          if(color > 0) color += 10;
        }
      } else if(!strcmp(arg, "-b")) {
        color = 1; // Bold
      } else if(!strcmp(arg, "-i")) {
        color = 7; // Inverted
      } else if(!strcmp(arg, "-u")) {
        color = 4; // Underline
      } else if(!strcmp(arg, "-r")) {
        color = 0; // Reset
      }
      if(color >= 0) {
        if(need_space) {
          printf(" ");
          need_space = false;
        }
        if(is_terminal()) printf("\033[%dm", color);
        color = -1;
      }
    } else {
      if(need_space) printf(" ");
      else need_space = true;
      printf("%s", arg);
    }
  }

  if(is_terminal()) printf("\033[0m");
  printf("\n");
  return 0;  
}
