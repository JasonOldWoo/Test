awk uses a dollar sign followed by a number to denote each field.
e.g. awk '{print $3}' xxxx.txt
the comma in the print statement tells AWK to insert a field seperator, by default, a single space, in the output.
NF is the number of field followed by dollar 0 the full line.
The slashes tell after the enclosed text is a regular expression and the action is applied to only those lines that match the expression or if you want to print only those lines that have exactly six words.
e.g. awk 'NF==6{print NF, $0}' xxxx.txt
In this case, it prints only those lines that have exactly six fields.


You can also use a pattern without an action. If you do this, the default action is just to print the input line.

You can specify multiple pattern action statements in a single awk program.
e.g.
awk '/up/{print "UP:", NF, $0} /down/{print "DOWN:", NF, $0}' xxxx.txt
