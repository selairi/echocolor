# echocolor
Prints color text on Linux/UNIX terminal.

# Usage
echocolor [--help] [-c color] [-bg color] [-b] [-u] [-i] [-r] Text...
  --help      Prints help.
  -c color    Set text color to color
  -bg color   Set background color
  -b          Set bold text
  -i          Interchanges text and background colors
  -u          Set underlined text
  -r          Set default text
Available colors:
    black
    blue
    cyan
    green
    magenta
    red
    white
    yellow

Examples:
  echocolor -b -c red 'Error:' -r 'Syntax error'
  echocolor '[' -b -c green 'OK' -r ']' 'Example' -b 'Hello world'

