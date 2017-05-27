# 4t45e_interface
Allow a 2003 m/y GM PCM to control a 2004 m/y 4t45e transaxle.

Case study involves a 2004 m/y GM N body 3.4L V6/LA1, 4t45e/MN5 transaxle.  PCM/BCM rolled back to 2003 m/y modules from like-equipped donor to allow compatibility with DHP tuning suite.  2004 revisions of the 4t45e included elimination of three pressure switches in the valvebody; 2003 m/y PCM will set P1810, raise line pressure and exhibit various anomalies.
This project utilizes an Arduino Uno and a board of MOSFETs to monitor transmission range switch (TRS) signals A/B/C/P and deduce tranmission manual valve position.  Arduino can then control a dedicated ground on PCM pins 17 and 22 to simulate high/low signals from the missing valvebody pressure switches.
