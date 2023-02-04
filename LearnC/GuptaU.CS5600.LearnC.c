/*
 * GuptaU.CS5600.LearnC.c
 *
 *  Created on: Feb 4, 2023 Spring 2023
 *  Northeastern University
 *  Author: ujwal gupta
 */

#include <stdio.h>

// Convert miles per gallon (mpg) to kilometers per liter (kml)
double mpg2kml(double mpg) {
    return mpg * 4.54609 / 1.609344;
}

// Convert miles per gallon (mpg) to liters per 100 kilometers (lphm)
double mpg2lphm(double mpg) {
    return 235.215 / mpg;
}

// Convert kilometers per liter (kml) to miles per gallon (mpg)
double kml2mpg(double kml) {
    return 1.609344 / 4.54609 * kml;
}

int main() {
    double mpg = 10.0;
    double kml = mpg2kml(mpg);
    double lphm = mpg2lphm(mpg);

	printf("MPG: %.2f, KML: %.2f, LP100KM: %.2f\n", mpg, kml, lphm);

	kml = 5;
	mpg = kml2mpg(kml);
	lphm = mpg2lphm(mpg);
	printf("KML: %.2f, MPG: %.2f, LP100KM: %.2f\n", kml, mpg, lphm);

	mpg = -10;
	kml = mpg2kml(mpg);
	lphm = mpg2lphm(mpg);
	printf("MPG: %.2f, KML: %.2f, LP100KM: %.2f\n", mpg, kml, lphm);
    return 0;
}

