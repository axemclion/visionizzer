10 CLS : KEY OFF: SCREEN 9: x = 320: y = 170: vvv = 750: col = 15: Col1 = 15
20 LOCATE 10, 10: INPUT "Start a new session (Y/N)"; an$: DIM ch(7561.5)
30 LOCATE 11, 10: INPUT "give the resolution          :", res: IF res = 0 THEN res = 10
40 IF an$ <> "n" THEN OPEN "line.$$$" FOR OUTPUT AS #1: OPEN "Circ.$$$" FOR OUTPUT AS #2: CLOSE : OPEN "text.$$$" FOR OUTPUT AS #1: CLOSE : OPEN "box.$$$" FOR OUTPUT AS #1: CLOSE : OPEN "paint.$$$" FOR OUTPUT AS #1: CLOSE
50 CLOSE : OPEN "line.$$$" FOR APPEND AS #1: OPEN "circ.$$$" FOR APPEND AS #2: CLOSE : OPEN "text.$$$" FOR APPEND AS #1: OPEN "box.$$$" FOR APPEND AS #2: CLOSE : OPEN "paint.$$$" FOR APPEND AS #1: CLOSE : CLS : GOSUB 60: GOTO 100
60 FOR q = 1 TO 640 STEP 20: LINE (q, 0)-(q, 350), 2: NEXT q
70 FOR q = 1 TO 350 STEP 20: LINE (0, q)-(640, q), 2: NEXT q
80 LINE (9, 9)-(632, 342), 12, B: LINE (8, 8)-(631, 341), 15, B: PAINT (1, 1), 8, 15
90 RETURN
100 DIM pnt(100): GET (1, 1)-(2, 2), pnt:
110 CLS : GOSUB 60: GOSUB 820
120 WHILE a$ <> CHR$(27)
130 a$ = INKEY$: x1 = x: y1 = y
140 IF a$ = "" THEN ssver = ssver + .01:  ELSE ssver = 0
150 IF ssver >= vvv THEN GOSUB 1760
160 IF a$ = "2" THEN y = y + res
170 IF a$ = "8" THEN y = y - res
180 IF a$ = "6" THEN x = x + res
190 IF a$ = "4" THEN x = x - res
200 IF a$ = "7" THEN x = x - res: y = y - res
210 IF a$ = "9" THEN x = x + res: y = y - res
220 IF a$ = "1" THEN x = x - res: y = y + res
230 IF a$ = "3" THEN x = x + res: y = y + res
240 IF x >= 630 THEN x = 630
250 IF x < 10 THEN x = 10
260 IF y >= 340 THEN y = 340
270 IF y < 10 THEN y = 10
280 LOCATE 1, 1: PRINT USING "Position -( ### | ### )"; x; y
290 PUT (x1 - 1, y1 - 1), pnt, PSET
300 GET (x - 1, y - 1)-(x + 1, y + 1), pnt
310 CIRCLE (x, y), 1, 10 + RND * 5
320 IF a$ = "?" THEN GOSUB 2210
330 IF a$ = "o" THEN SCREEN 0: SHELL: SCREEN 9: CLS : a$ = "9"
340 IF a$ = "s" THEN lsx = x: lsy = y
350 IF a$ = "e" THEN lex = x: ley = y
360 IF a$ = "l" THEN LINE (lsx, lsy)-(lex, ley), 15: c = 15: GOSUB 800
370 IF a$ = "d" THEN LINE (lsx, lsy)-(lex, ley), 0: c = 0: GOSUB 1030
380 IF a$ = "c" THEN GOSUB 490
390 IF a$ = "p" THEN lex = x: ley = y: c = 15: GOSUB 800: LINE (lsx, lsy)-(x, y), 15: lsx = x: lsy = y
400 IF a$ = "r" THEN GOSUB 60: GOSUB 820
410 IF a$ = "w" THEN GOSUB 1180
420 IF a$ = "f" THEN GOSUB 1710
430 IF a$ = "g" THEN GOSUB 820
440 IF a$ = "a" THEN GOSUB 1760
450 IF a$ = "b" THEN GOSUB 2090
460 IF a$ = CHR$(17) THEN END
470 IF a$ = "t" THEN GOSUB 1870
480 WEND: END
490 l1 = 0: l2 = 0: r = 140 / 192: an2 = 359.6: an1 = 0: q$ = "+": r = 480 / 640
500 WHILE q$ <> "c"
510 LOCATE 1, 1: PRINT USING "Circle - (### | ###) : ### ; ####.##"; x; y; r; ar: an11 = an1: an22 = an2: r1 = r
520 q$ = INPUT$(1): r1 = r: car1 = car
530 IF q$ = "+" THEN r = r + 1
540 IF q$ = "-" THEN r = r - 1
550 IF q$ = "8" THEN an1 = an1 + 1
560 IF q$ = "2" THEN an1 = an1 - 1
570 IF q$ = "6" THEN an2 = an2 + 1
580 IF q$ = "4" THEN an2 = an2 - 1
590 IF q$ = "]" THEN l1 = 1
600 IF q$ = "[" THEN l2 = 1
610 IF q$ = "{" THEN l2 = 0
620 IF q$ = "}" THEN l1 = 0
630 IF q$ = "/" THEN car = car + .5
640 IF q$ = "*" THEN car = car - .1
650 IF q$ = "5" THEN car = 1
660 IF q$ = "?" THEN GOSUB 490
670 IF an1 > 359.6 THEN an1 = 359.6
680 IF an2 > 359.6 THEN an2 = 359.6
690 IF an1 < 0 THEN an1 = 0
700 IF an2 < 0 THEN an2 = 0
710 IF r <= 0 THEN r = 1
720 IF l1 = 1 AND l2 = 1 THEN CIRCLE (x, y), r1, 0, -(22 / 7 / 180) * an11, -(22 / 7 / 180) * an22, car1: CIRCLE (x, y), r, 15, -(22 / 7 / 180) * an1, -(22 / 7 / 180) * an2, car:
730 IF l1 = 0 AND l2 = 1 THEN CIRCLE (x, y), r1, 0, (22 / 7 / 180) * an11, -(22 / 7 / 180) * an22, car1: CIRCLE (x, y), r, 15, (22 / 7 / 180) * an1, -(22 / 7 / 180) * an2, car:
740 IF l1 = 1 AND l2 = 0 THEN CIRCLE (x, y), r1, 0, -(22 / 7 / 180) * an11, (22 / 7 / 180) * an22, car1: CIRCLE (x, y), r, 15, -(22 / 7 / 180) * an1, (22 / 7 / 180) * an2, car:
750 IF l1 = 0 AND l2 = 0 THEN CIRCLE (x, y), r1, 0, (22 / 7 / 180) * an11, (22 / 7 / 180) * an22, car1: CIRCLE (x, y), r, 15, (22 / 7 / 180) * an1, (22 / 7 / 180) * an2, car:
760 GOSUB 820: WEND: CLOSE
770 OPEN "circ.$$$" FOR APPEND AS #1
780 PRINT #1, x, y, r, 15, (22 / 7 / 180) * an1, (22 / 7 / 180) * an2, l1, l2, car
790 CLOSE : RETURN
800 OPEN "line.$$$" FOR APPEND AS #1:
810 PRINT #1, lsx, lsy, lex, ley, c: CLOSE : RETURN
820 CLOSE : OPEN "line.$$$" FOR INPUT AS #1
830 WHILE NOT EOF(1)
840 INPUT #1, qlsx, qlsy, qlex, qley, qc
850 LINE (qlsx, qlsy)-(qlex, qley), qc
860 WEND: CLOSE
870 OPEN "box.$$$" FOR INPUT AS #1: WHILE NOT EOF(1): INPUT #1, bx1, by1, bx2, by2: LINE (bx1, by1)-(bx2, by2), 15, B: WEND: CLOSE
880 OPEN "text.$$$" FOR INPUT AS #1: WHILE NOT EOF(1): INPUT #1, lx, ly, t$: LOCATE ly, lx: PRINT t$: WEND: CLOSE
890 OPEN "circ.$$$" FOR INPUT AS #1:
900 WHILE NOT EOF(1)
910 INPUT #1, qx, qy, qr, qc, qa1, qa2, ql1, ql2, ar
920 IF ql1 = 1 AND ql2 = 1 THEN CIRCLE (qx, qy), qr, qc, -qa1, -qa2, ar
930 IF ql1 = 1 AND ql2 = 0 THEN CIRCLE (qx, qy), qr, qc, -qa1, qa2, ar
940 IF ql1 = 0 AND ql2 = 1 THEN CIRCLE (qx, qy), qr, qc, qa1, -qa2, ar
950 IF ql1 = 0 AND ql2 = 0 THEN CIRCLE (qx, qy), qr, qc, qa1, qa2, ar
960 WEND: CLOSE
970 OPEN "paint.$$$" FOR INPUT AS #1:
980 WHILE NOT EOF(1)
990 INPUT #1, ccx, ccy, ccc
1000 PAINT (ccx, ccy), ccc, 15
1010 WEND:
1020 CLOSE : RETURN
1030 OPEN "line.$$$" FOR INPUT AS #1
1040 OPEN "tmp.$$$" FOR OUTPUT AS #2
1050 WHILE NOT EOF(1)
1060 INPUT #1, qlsx, qlsy, qlex, qley, qc
1070 IF (qlsx = lsx AND qley = ley AND qlsy = lsy AND qlex = lex) OR (qlsx = lex AND qley = lsy AND qley = lsy AND qlsx = lex) THEN GOTO 1090
1080 PRINT #2, qlsx, qlsy, qlex, qley, qc
1090 WEND
1100 CLOSE #1: CLOSE #2
1110 KILL "line.$$$"
1120 NAME "tmp.$$$" AS "line.$$$"
1130 RETURN
1140 FOR q = 1 TO LEN(n$)
1150 PRINT MID$(n$, q, 1);
1160 FOR qq = 1 TO 100: NEXT qq
1170 NEXT q: PRINT " ": RETURN
1180 CLS : n$ = "You have chosen a command to print the program for": LOCATE 23, 1: GOSUB 1140
1190 n$ = "Drawing Graphics in BASIC": GOSUB 1140
1200 n$ = "So, here it is": GOSUB 1140
1210 OPEN "program.bas" FOR OUTPUT AS #1
1220 wr$ = "10 Rem Graphics Program generated using DRAW"
1230 PRINT #1, wr$
1240 n$ = wr$: GOSUB 1140
1250 n$ = "20 Screen 9 : key off :cls ": GOSUB 1140
1260 PRINT #1, n$: lno = 40
1270 n$ = "30 rem ***************LINES PART************": PRINT #1, n$: GOSUB 1140
1280 OPEN "line.$$$" FOR INPUT AS #2
1290 WHILE NOT EOF(2)
1300 INPUT #2, qlsx, qlsy, qlex, qley, qc
1310 n$ = STR$(lno) + " line (" + STR$(qlsx) + " ," + STR$(qlsy) + ")-(" + STR$(qlex) + "," + STR$(qley) + ")," + STR$(qc)
1320 GOSUB 1140
1330 PRINT #1, n$
1340 lno = lno + 10: WEND
1350 CLOSE #2
1360 n$ = STR$(lno) + " rem **************CIRCLE AND ARCS *************": GOSUB 1140
1370 PRINT #1, n$: lno = lno + 10
1380 OPEN "circ.$$$" FOR INPUT AS #2
1390 WHILE NOT EOF(2)
1400 INPUT #2, qx, qy, qr, qc, qa1, qa2, ql1, ql2, ar
1410 IF ql1 = 1 AND ql2 = 1 THEN n$ = STR$(lno) + " circle (" + STR$(qx) + "," + STR$(qy) + ")," + STR$(qr) + ", -" + STR$(qa1) + ",-" + STR$(qa2) + " , " + STR$(ar)
1420 IF ql1 = 0 AND ql2 = 1 THEN n$ = STR$(lno) + " circle (" + STR$(qx) + "," + STR$(qy) + ")," + STR$(qr) + ",-" + STR$(qa1) + "," + STR$(qa2) + " , " + STR$(ar)
1430 IF ql1 = 1 AND ql2 = 0 THEN n$ = STR$(lno) + " circle (" + STR$(qx) + "," + STR$(qy) + ")," + STR$(qr) + ", -" + STR$(qa1) + ",-" + STR$(qa2) + " , " + STR$(ar)
1440 IF ql1 = 0 AND ql2 = 0 THEN n$ = STR$(lno) + " circle (" + STR$(qx) + "," + STR$(qy) + ")," + STR$(qr) + ", " + STR$(qa1) + "," + STR$(qa2) + " , " + STR$(ar)
1450 GOSUB 1140: PRINT #1, n$
1460 lno = lno + 10
1470 WEND: CLOSE #2
1475 REM ****************************Text Part ***********************
1480 OPEN "text.$$$" FOR INPUT AS #2
1490 WHILE NOT EOF(2)
1500 INPUT #2, lx, ly, c$
1510 lno = lno + 10
1520 n$ = STR$(lno) + " Locate " + STR$(ly) + "," + STR$(lx) + ": print" + CHR$(34) + c$ + CHR$(34)
1530 GOSUB 1150: PRINT #1, n$
1540 WEND
1550 CLOSE #2
1560 n$ = STR$(lno) + " end"
1570 GOSUB 1140
1580 CLOSE
1590 n$ = "------------------------------------------------------------------------------": GOSUB 1140
1600 n$ = "This program is stored under the current": GOSUB 1140
1610 n$ = "directory under the filename program.bas . ": GOSUB 1140
1620 n$ = "To run the program, start BASIC": GOSUB 1140
1630 n$ = "Load the program": GOSUB 1140
1640 n$ = "Rename this file before creating another program": GOSUB 1140
1650 n$ = "from this DRAW software": GOSUB 1140
1660 n$ = "An advanced GUI version of this software is ": GOSUB 1140
1661 n$ = "now available. To obtain it mail to ------": GOSUB 1140
1662 n$ = "axemcclion@yahoo.com": GOSUB 1140
1670 n$ = "-------------------Press a Key to continue------------------------": GOSUB 1140
1680 fool$ = INPUT$(1): CLS :
1690 GOSUB 60: GOSUB 820:
1700 CLOSE : RETURN
1710 LOCATE 1, 1: GOSUB 2570
1720 GOSUB 820: CIRCLE (x, y), 1, 15: PAINT (x + 2, y + 2), col, 15
1730 OPEN "paint.$$$" FOR APPEND AS #1
1740 WRITE #1, x, y, col
1750 CLOSE : GOSUB 820: RETURN
1760 ssx = RND * 100: ssy = RND * 100: ay = 1: ax = 1: WHILE qqqq$ = INKEY$
1770 ssx = ssx + ax: ssy = ssy + ay: sax = sax + qx: say = say + qy
1780 GET (ssx, ssy)-(ssx + 34, ssy + 44), ch
1790 PUT (ssx, ssy), ch, PRESET
1800 PUT (ssx, ssy), ch, PRESET
1810 IF ssx < 3 THEN ax = RND * 3
1820 IF ssx > 600 THEN ax = -RND * 3
1830 IF ssy < 3 THEN ay = RND * 3
1840 IF ssy > 300 THEN ay = -RND * 3
1850 WEND: ssver = 0: COLOR 15
1860 CLS : GOSUB 60: GOSUB 820: RETURN
1870 tx = 37: ty = 11: LOCATE 1, 1: PRINT "Text Mode"
1880 qq$ = " ": WHILE qq$ <> CHR$(27): tx1 = tx: ty1 = ty
1890 qq$ = INPUT$(1): LOCATE 1, 1: PRINT USING " Row - ## | Col - ##"; tx1; ty1
1900 IF qq$ = "4" THEN tx = tx - 1: GOTO 1980
1910 IF qq$ = "2" THEN ty = ty + 1: GOTO 1980
1920 IF qq$ = "6" THEN tx = tx + 1: GOTO 1980
1930 IF qq$ = "8" THEN ty = ty - 1: GOTO 1980
1940 IF qq$ = CHR$(8) THEN GOTO 2030
1950 IF qq$ <> CHR$(27) AND qq$ <> CHR$(8) THEN LOCATE ty, tx: PRINT qq$: tx = tx1: IF tx > 79 THEN tx = 0: ty = ty + 1
1960 IF qq$ <> CHR$(27) AND qq$ <> CHR$(8) THEN CLOSE : OPEN "text.$$$" FOR APPEND AS #1: WRITE #1, ty, tx, qq$
1970 WEND: CLOSE : LOCATE ty1, tx1: PRINT " ": GOSUB 60: RETURN
1980 IF tx < 1 THEN tx = 1
1990 IF ty < 1 THEN ty = 1
2000 IF tx > 79 THEN tx = 79
2010 IF tx > 23 THEN tx = 23
2020 LOCATE ty1, tx1: PRINT " ": LOCATE ty, tx: PRINT "-": GOSUB 820: GOTO 1970
2030 OPEN "text.$$$" FOR INPUT AS #1: OPEN "tmp.tmp" FOR OUTPUT AS #2
2040 WHILE NOT EOF(1)
2050 INPUT #1, cx, cy, c$
2060 IF ty = cy AND tx + 1 = cx THEN GOTO 2080 ELSE WRITE #2, cx, cy, c$
2070 WEND
2080 CLOSE : KILL "text.$$$": NAME "tmp.tmp" AS "text.$$$": GOTO 1970
2090 B$ = "a": WHILE B$ <> "b"
2100 bx1 = x1: by1 = y1: LOCATE 1, 1: PRINT USING "Box ( ### | ###) - (### | ###) "; x; y; x1; y1
2110 B$ = INPUT$(1)
2120 IF B$ = "4" THEN x1 = x1 - res
2130 IF B$ = "6" THEN x1 = x1 + res
2140 IF B$ = "8" THEN y1 = y1 - res
2150 IF B$ = "2" THEN y1 = y1 + res
2160 LINE (x, y)-(bx1, by1), 0, B
2170 LINE (x, y)-(x1, y1), 15, B
2180 GOSUB 820: WEND
2190 CLOSE : OPEN "box.$$$" FOR APPEND AS #1
2200 WRITE #1, x, y, x1, y1: CLOSE : RETURN
2210 GET (150, 50)-(471, 231), ch: LOCATE 1, 1: PRINT "HELP MENU ACTIVATED"
2220 LINE (150, 60)-(470, 230), 7, BF: LINE (150, 60)-(470, 230), 15, B
2230 LOCATE 5, 31: n$ = " Help Menu ": GOSUB 1140
2240 LOCATE 7, 22: PRINT "S - Mark the starting of a line "
2250 LOCATE 8, 22: PRINT "E - Mark the ending of a line  "
2260 LOCATE 9, 22: PRINT "L - Draw a line                           "
2270 LOCATE 10, 22: PRINT "D - Delete a line                        "
2280 LOCATE 11, 22: PRINT "C - Draw a circle                       "
2290 LOCATE 12, 22: PRINT "P - Draw a series of lines         "
2300 LOCATE 13, 22: PRINT "G - Redraw the Graph              "
2310 LOCATE 14, 22: PRINT "W - Write a program                "
2320 LOCATE 15, 22: PRINT " F - Fill a part with a color      ": q$ = INPUT$(1)
2330 LINE (150, 60)-(470, 230), 7, BF: LINE (150, 60)-(470, 230), 15, B
2340 LOCATE 7, 22: PRINT "A - Activate Screen Saver      "
2350 LOCATE 8, 22: PRINT "B - Draw a Box                          "
2360 LOCATE 9, 22: PRINT "T  - Text mode (Esc for return"
2370 LOCATE 10, 22: PRINT "Q - Quit the Draw Execution mode                       "
2380 LOCATE 11, 22: PRINT "R - Redraw the entire picture "
2390 LOCATE 13, 21: PRINT "To activate a command, press the "
2400 LOCATE 14, 21: PRINT "coresponding key                               "
2410 q$ = INPUT$(1)
2420 PUT (150, 50), ch, PSET: a$ = q$
2430 RETURN
2440 GET (199, 59)-(430, 240), ch: LOCATE 1, 1: PRINT "Circle HELP ACTIVATED"
2450 LINE (200, 60)-(430, 240), 7, BF: LINE (200, 60)-(430, 240), 8, B:
2460 LOCATE 6, 13: PRINT " CIRCLE HELP MENU"
2470 LOCATE 8, 27: PRINT " +  = increase radius"
2480 LOCATE 9, 27: PRINT " -  = decrease radius"
2490 LOCATE 10, 27: PRINT "5  = drop a perfect circle radius"
2500 LOCATE 11, 27: PRINT "[ ] = draw lines form centre  "
2510 LOCATE 12, 27: PRINT "{} = erase the above lines"
2520 LOCATE 13, 27: PRINT "* = increase aspect ratio "
2530 LOCATE 14, 27: PRINT "/ = decrease aspect ratio "
2540 LOCATE 15, 27: PRINT "arrow keys for arcs"
2550 w$ = INPUT$(1)
2560 q$ = w$: PUT (199, 59), ch, PSET: RETURN
2570 DIM aaa(2674):
2580 LOCATE 1, 1: PRINT "Use arrows to change, space to select"
2590 GET (250, 70)-(360, 260), aaa
2600 LINE (250, 70)-(360, 260), 0, BF: LINE (250, 70)-(360, 260), 15, B:
2610 FOR q = 260 TO 350 STEP 30
2620 LINE (q, 100)-(q, 250), 15
2630 NEXT q
2640 FOR q = 100 TO 250 STEP 30
2650 LINE (260, q)-(350, q), 15
2660 NEXT q
2670 a = 0: FOR q = 261 TO 351 - 30 STEP 30
2680 FOR q1 = 101 TO 251 - 30 STEP 30
2690 a = a + 1: PAINT (q, q1), a, 15
2700 NEXT q1: NEXT q
2710 cx = 1: cy = 1
2720 WHILE a$ <> CHR$(32)
2730 cx1 = cx: cy1 = cy
2740 a$ = INKEY$
2750 IF a$ = "6" THEN cx = cx + 1
2760 IF a$ = "4" THEN cx = cx - 1
2770 IF a$ = "2" THEN cy = cy + 1
2780 IF a$ = "8" THEN cy = cy - 1
2790 IF cx > 3 THEN cx = 1
2800 IF cy > 5 THEN cy = 1
2810 IF cx < 1 THEN cx = 3
2820 IF cy < 1 THEN cy = 5
2830 ccx = 260 + 30 * (cx - 1)
2840 ccy = 100 + 30 * (cy - 1)
2850 ccx1 = 260 + 30 * (cx1 - 1)
2860 ccy1 = 100 + 30 * (cy1 - 1)
2870 LINE (ccx1 + 10, ccy1 + 10)-(ccx1 + 20, ccy1 + 20), col, BF
2880 LINE (ccx + 10, ccy + 10)-(ccx + 20, ccy + 20), 15 - col, BF
2890 col = cy + (cx - 1) * 5:
2900 COLOR (col): LOCATE 7, 34: PRINT USING " Color = ##"; col
2910 WEND
2920 PUT (250, 70), aaa, PSET: RETURN


