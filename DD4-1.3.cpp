// DD4-1.3.cpp : main project file.

//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <conio.h> // getch();

using namespace System;


//using namespace std;

//Solution set :
//
// k= k=199,..234..., 269
// a10: -(a1 + a2) - (a3 + a4) - (a5 + a6 + a7 + a8 + a9) - (a11 + a12) + k = 
// a25: (a1 + a2) + (a11 + a12)  - (a26 + a27 + a28 + a29 + a30) - 3*k + 741, = 
// a24: -(a1 + a2) - (a3 + a4) - (a11 + a12) - (a21 + a22 + a23)  + 4*k - 741, = 
// a15: -(a11 + a12 + a13 + a14 + a16 + a17 + a18 + a19 +a20+a21 + a22)  +k = 
// a31: a3 + a4 + (a11 + a12) +( a2+a22) - (a32 + a33 + a34 + a35 + a36 + a37 + a38) -3*k +741 


//a1,...,a9  free
//a11, a12 free
//a10
//a26 ,...,a30 free
//a25
//a21,...,a23 free
//a24
//a13,a14,a16,.,a19, a20
//a15
//a32,..,a38 free
//a31


int main() // (array<System::String ^> ^args)
{

	// int a1, a3, a4, a5, a6, a7, a8, a9, 
    // a11,a12,
    // a13,a14,a16, a17, a18, a19, a21,a22,
    // a23, a24, a25, a26, a27, a28, a30, 
    // a32,a33,a34,a35,a36,a37,a38 ; // free
	// int a10, a15, a20, a33, a31; // dependant

	unsigned int NxM = 38;
	unsigned int N = 5; // dependant
	unsigned int M = NxM - N; // free
	  // Complementarity:
	unsigned int P = 12; // number of unknowns in each equation of the system
						//{ NxM + 1 - a1, NxM + 1 - a2, ...} is a solution associated to k_comp = P*(NxM + 1) - k 

	int sol[38]; // = NxM
	bool OKa10, OKa25, OKa24, OKa15, OKa31;   // dependant in order of calculation

																					  // these two are meant to be used together
	bool just100records = true; // limit the output to file to first 100 records, a1_value=0
	bool just_a1 = true; //skip all a1 except a1_value

	int a1_value = 0;
	int numSolutions_a1 = 0;
	if (just100records && just_a1) {
		std::cout << " 100 records in file will have a1= ";
		std::cin >> a1_value;
	};
	if (just100records && !just_a1) {
		std::cout << " Only first 100 occuring records will be stored in file" << std::endl;
	};


	int k;// = 129;
	std::cout << "k=199,..234..., 269: ";
	std::cin >> k;
    int kComp = P*(NxM + 1) - k;

	//int length = snprintf(NULL, 0, "%d", k);
	//char* kStr = (char*)malloc(length + 1);
	//snprintf(kStr, length + 1, "%d", k);
	// alternative:
	std::string kStr = std::to_string(k);

	FILE *result;		/* file pointer of ndp */
	std::string out_filename("DD4-1.");

	FILE *result2;		/* file pointer of ndp */
	std::string out_filename2("DD4-1.complement");

	//out_filename.append("k=");
	//out_filename.append(kStr);
	//out_filename.append(".csv");
	//result = fopen(out_filename.c_str(), "w");

	if (just100records) {
		out_filename = "DD4-1.100Records.a1=";
		std::string a1_str = std::to_string(a1_value);

		out_filename.append(a1_str);
		out_filename.append(".");

		out_filename2.append(a1_str);
		out_filename2.append(".");
	}

	out_filename.append("k=");
	out_filename.append(kStr);
	out_filename.append(".csv");
	result = fopen(out_filename.c_str(), "w");

	// complement:
	out_filename2.append("k=");
	kStr = std::to_string(kComp);
	out_filename2.append(kStr);
	out_filename2.append(".csv");
    
    
	//char *out_filename = "result.csv";
	//result = fopen(out_filename, "w");

	//header: 	a1,a2,a3,a4,a5,....,k  
	result = fopen(out_filename.c_str(), "w");
	result2 = fopen(out_filename2.c_str(), "w");
	for (int i = 0; i < NxM - 1; i++) {
		fprintf(result, "a%d,", (i + 1));
		fprintf(result2, "a%d,", (i + 1));
	};
	fprintf(result, "a%d,k\n", NxM);
	fprintf(result2, "a%d,k\n", NxM);
	fclose(result);
	fclose(result2);

	// to 18,446,744,073,709,551,615
	long long unsigned numSolutions = 0;
	long long unsigned numTrials = 0;

	/* Record CPU time and elapsed time */
	double cpu_time_used, elapsedtime;
	clock_t starttime, endtime;
	time_t startelapsed, endelapsed;
	starttime = clock();
	startelapsed = time(NULL);

	OKa25 = OKa10 = OKa15 = OKa24 = OKa31 = false;
	//int aux = 5 * k - 465;

	printf("Solutions found from trials:\n");

	for (int a1 = 1; a1 <= NxM; a1++) {
		//for (a1 = 2; a1 <= NxM; a1++) {
		//for (a1 = 3; a1 <= NxM; a1++) {
				// ignore all a1 except  a1_value
		if (just_a1) {
			if (a1 != a1_value) continue;
		}


		for (int a2 = 1; a2 <= NxM; a2++) {
			if (a1 == a2)	continue;


			for (int a3 = 1; a3 <= NxM; a3++) {
				if (a1 == a3 || a2 == a3)	continue;
				for (int a4 = 1; a4 <= NxM; a4++) {
					if (a1 == a4 || a2 == a4 || a3 == a4)	continue;
					for (int a5 = 1; a5 <= NxM; a5++) {
						if (a1 == a5 || a2 == a5 || a3 == a5 || a4 == a5)	continue;
						for (int a6 = 1; a6 <= NxM; a6++) {
							if (a1 == a6 || a2 == a6 || a3 == a6 || a4 == a6 || a5 == a6)	continue;
							for (int a7 = 1; a7 <= NxM; a7++) {
								if (a1 == a7 || a2 == a7 || a3 == a7 || a4 == a7 || a5 == a7 || a6 == a7)	continue;
								for (int a8 = 1; a8 <= NxM; a8++) {
									if (a1 == a8 || a2 == a8 || a3 == a8 || a4 == a8 || a5 == a8 || a6 == a8 || a7 == a8)	continue;
									for (int a9 = 1; a9 <= NxM; a9++) {
										if (a1 == a9 || a2 == a9 || a3 == a9 || a4 == a9 || a5 == a9 || a6 == a9 || a7 == a9 || a8 == a9)	continue;
										for (int a11 = 1; a11 <= NxM; a11++) {
											if (a1 == a11 || a2 == a11 || a3 == a11 || a4 == a11 || a5 == a11 || a6 == a11 || a7 == a11 || a8 == a11 || a9 == a11)	continue;
											for (int a12 = 1; a12 <= NxM; a12++) {
												if (a1 == a12 || a2 == a12 || a3 == a12 || a4 == a12 || a5 == a12 || a6 == a12 || a7 == a12 || a8 == a12 || a9 == a12 || a11 == a12)	continue;

												// additional test to avoid dependent aNM being equal
												int a1a2 = a1 + a2;
												int a3a4 = a3 + a4;
												int a11a12 = a11 + a12;
												int a5_a9 = (a5 + a6 + a7 + a8 + a9);

												numTrials++;
												int a10 = -a1a2 - a3a4 - a5_a9 - a11a12 + k; if (a10 > NxM || a10 < 1) continue;
												if (a1 == a10 || a2 == a10 || a3 == a10 || a4 == a10 || a5 == a10 || a6 == a10 || a7 == a10 || a8 == a10 || a9 == a10 || a11 == a10 || a12 == a10)	continue;

												OKa10 = true;
												if (!OKa25) { // latest correct seq. a1,...,a9, a11, a12, a10
													sol[0] = a1; sol[1] = a2; sol[2] = a3; sol[3] = a4; sol[4] = a5; sol[5] = a6; sol[6] = a7; sol[7] = a8; sol[8] = a9;
													sol[9] = a11; sol[10] = a12; sol[11] = a10;

													// console output to track the evolution of the program every 10 seconds
													if (numSolutions == 0) {
														endelapsed = time(NULL);
														elapsedtime = (double)endelapsed - startelapsed;     // elapsed seconds
														long long unsigned seconds = elapsedtime;
														if (seconds / 10 * 10 == seconds) std::cout << "up to dependent a10 checked OK from " << numTrials << " trials" << "\r";
													}
												}

												for (int a26 = 1; a26 <= NxM; a26++) {
													if (a1 == a26 || a2 == a26 || a3 == a26 || a4 == a26 || a5 == a26 || a6 == a26 || a7 == a26 || a8 == a26 || a9 == a26 || a11 == a26 || a12 == a26)	continue;
													if (a10 == a26)	continue;
													for (int a27 = 1; a27 <= NxM; a27++) {
														if (a1 == a27 || a2 == a27 || a3 == a27 || a4 == a27 || a5 == a27 || a6 == a27 || a7 == a27 || a8 == a27 || a9 == a27 || a11 == a27 || a12 == a27 || a26 == a27)	continue;
														if (a10 == a27)	continue;
														for (int a28 = 1; a28 <= NxM; a28++) {
															if (a1 == a28 || a2 == a28 || a3 == a28 || a4 == a28 || a5 == a28 || a6 == a28 || a7 == a28 || a8 == a28 || a9 == a28 || a11 == a28 || a12 == a28 || a26 == a28 || a27 == a28)	continue;
															if (a10 == a28)	continue;
															for (int a29 = 1; a29 <= NxM; a29++) {
																if (a1 == a29 || a2 == a29 || a3 == a29 || a4 == a29 || a5 == a29 || a6 == a29 || a7 == a29 || a8 == a29 || a9 == a29 || a11 == a29 || a12 == a29 || a26 == a29 || a27 == a29 || a28 == a29)	continue;
																if (a10 == a29)	continue;
																for (int a30 = 1; a30 <= NxM; a30++) {
																	if (a1 == a30 || a2 == a30 || a3 == a30 || a4 == a30 || a5 == a30 || a6 == a30 || a7 == a30 || a8 == a30 || a9 == a30 || a11 == a30 || a12 == a30 || a26 == a30 || a27 == a30 || a28 == a30 || a29 == a30)	continue;
																	if (a10 == a30)	continue;
                                                                            //int a5_a9 = a5 + a6 + a7 + a8 + a9;
                                                                            int a26_a30 = a26 + a27 + a28 + a29 + a30;
                                                                            numTrials++;
																			//int a25 = -a10 - a3a4 - a5_a9 - a26_a30 - 2 * k + 741; if (a25 > NxM || a25 < 1) continue;
																			int a25 = (a1a2) + (a11a12) - (a26_a30) - 3 * k + 741; if (a25 > NxM || a25 < 1) continue;
																			if (a1 == a25 || a2 == a25 || a3 == a25 || a4 == a25 || a5 == a25 || a6 == a25 || a7 == a25 || a8 == a25 || a9 == a25 || a11 == a25 || a12 == a25 || a26 == a25 || a27 == a25 || a28 == a25 || a29 == a25|| a30 == a25)	continue;
																	if (a10 == a25)	continue;
                                                                    OKa25 = true;
                                                                    if (!OKa24) { // latest correct seq. a1,...,a9, a11, a12, a10,  a26,...,,a30,a25
                                                                        sol[0] = a1; sol[1] = a2; sol[2] = a3; sol[3] = a4; sol[4] = a5; sol[5] = a6; sol[6] = a7; sol[7] = a8; sol[8] = a9;
                                                                        sol[9] = a11; sol[10] = a12; sol[11] = a10;
                                                                        sol[12] = a26; sol[13] = a27; sol[14] = a28; sol[15] = a29; sol[16] = a30; sol[17] = a25;

                                                                        // console output to track the evolution of the program every 10 seconds
                                                                        if (numSolutions == 0) {
                                                                            endelapsed = time(NULL);
                                                                            elapsedtime = (double)endelapsed - startelapsed;     // elapsed seconds
                                                                            long long unsigned seconds = elapsedtime;
                                                                            if (seconds / 10 * 10 == seconds) std::cout << "up to dependent a25 checked OK from " << numTrials << " trials" << "\r";
                                                                        }
                                                                    }
                                                                    
																	for (int a21 = 1; a21 <= NxM; a21++) {
																	if (a1 == a21 || a2 == a21 || a3 == a21 || a4 == a21 || a5 == a21 || a6 == a21 || a7 == a21 || a8 == a21 || a9 == a21 || a11 == a21 || a12 == a21 || a26 == a21 || a27 == a21 || a28 == a21 || a29 == a21|| a30 == a21)	continue;
																	if (a10 == a21 || a25 == a21)	continue;
																	for (int a22 = 1; a22 <= NxM; a22++) {
																	if (a1 == a22 || a2 == a22 || a3 == a22 || a4 == a22 || a5 == a22 || a6 == a22 || a7 == a22 || a8 == a22 || a9 == a22 || a11 == a22 || a12 == a22 || a26 == a22 || a27 == a22 || a28 == a22 || a29 == a22|| a30 == a22|| a21 == a22)	continue;
																	if (a10 == a22 || a25 == a22)	continue;
																	for (int a23 = 1; a23 <= NxM; a23++) {
																	if (a1 == a23 || a2 == a23 || a3 == a23 || a4 == a23 || a5 == a23 || a6 == a23 || a7 == a23 || a8 == a23 || a9 == a23 || a11 == a23 || a12 == a23 || a26 == a23 || a27 == a23 || a28 == a23 || a29 == a23|| a30 == a23|| a21 == a23|| a22 == a23)	continue;
																	if (a10 == a23 || a25 == a23)	continue;
																	
																	// for (int a24 = 1; a24 <= NxM; a24++) {
																	// if (a1 == a24 || a2 == a24 || a3 == a24 || a4 == a24 || a5 == a24 || a6 == a24 || a7 == a24 || a8 == a24 || a9 == a24 || a11 == a24 || a12 == a24 || a26 == a24 || a27 == a24 || a28 == a24 || a29 == a24|| a30 == a24|| a21 == a24|| a22 == a24|| a23 == a24)	continue;
																	// if (a10 == a24 || a25 == a24)	continue;

																	int a21a22 = a21+a22;
																	//int a23a24 = a23+a24;
																	numTrials++;
																	//int a20 = a10 + a5_a9 - a21a22 - a23a24 + 3 * k - 741; if (a20 > NxM || a20 < 1) continue;
																	int a24 = -(a1a2) - (a3a4) - (a11a12) - (a21a22) - a23 + 4 * k - 741; if (a24 > NxM || a24 < 1) continue;
																	if (a1 == a24 || a2 == a24 || a3 == a24 || a4 == a24 || a5 == a24 || a6 == a24 || a7 == a24 || a8 == a24 || a9 == a24 || a11 == a24 || a12 == a24 || a26 == a24 || a27 == a24 || a28 == a24 || a29 == a24|| a30 == a24|| a21 == a24|| a22 == a24|| a23 == a24)	continue;
																	if (a10 == a24 || a25 == a24)	continue;
                                                                    OKa24 = true;
                                                                    if (!OKa15) { // latest correct seq. a1,...,a9, a11, a12, a10,  a26,...,,a30,a25,a21,..,a24 
                                                                        sol[0] = a1; sol[1] = a2; sol[2] = a3; sol[3] = a4; sol[4] = a5; sol[5] = a6; sol[6] = a7; sol[7] = a8; sol[8] = a9;
                                                                        sol[9] = a11; sol[10] = a12; sol[11] = a10;
                                                                        sol[12] = a26; sol[13] = a27; sol[14] = a28; sol[15] = a29; sol[16] = a30; sol[17] = a25;
                                                                        sol[18] = a21;sol[19] = a22; sol[20] = a23; sol[21] = a24;  

                                                                        // console output to track the evolution of the program every 10 seconds
                                                                        if (numSolutions == 0) {
                                                                            endelapsed = time(NULL);
                                                                            elapsedtime = (double)endelapsed - startelapsed;     // elapsed seconds
                                                                            long long unsigned seconds = elapsedtime;
                                                                            if (seconds / 10 * 10 == seconds) std::cout << "up to dependent a24 checked OK from " << numTrials << " trials" << "\r";
                                                                        }
                                                                    }

                                                                    for (int a13 = 1; a13 <= NxM; a13++) {
																	if (a1 == a13 || a2 == a13 || a3 == a13 || a4 == a13 || a5 == a13 || a6 == a13 || a7 == a13 || a8 == a13 || a9 == a13 || a11 == a13 || a12 == a13 || a26 == a13 || a27 == a13 || a28 == a13 || a29 == a13|| a30 == a13|| a21 == a13|| a22 == a13|| a23 == a13|| a24 == a13)	continue;
																	if (a10 == a13 || a25 == a13|| a24 == a13)	continue;
                                                                    for (int a14 = 1; a14 <= NxM; a14++) {
																	if (a1 == a14 || a2 == a14 || a3 == a14 || a4 == a14 || a5 == a14 || a6 == a14 || a7 == a14 || a8 == a14 || a9 == a14 || a11 == a14 || a12 == a14 || a26 == a14 || a27 == a14 || a28 == a14 || a29 == a14|| a30 == a14|| a21 == a14|| a22 == a14|| a23 == a14|| a24 == a14)	continue;
																	if (a13 == a14)	continue;
																	if (a10 == a14 || a25 == a14|| a24 == a14)	continue;
//for (int a15 = 1; a15 <= NxM; a15++) {
//																	if (a1 == a15 || a2 == a15 || a3 == a15 || a4 == a15 || a5 == a15 || a6 == a15 || a7 == a15 || a8 == a15 || a9 == a15 || a11 == a15 || a12 == a15 || a26 == a15 || a27 == a15 || a28 == a15 || a29 == a15|| a30 == a15|| a21 == a15|| a22 == a15|| a23 == a15|| a24 == a15)	continue;
//																	if (a13 == a15 ||a14 == a15)	continue;
//																	if (a10 == a15 || a25 == a15|| a20 == a15)	continue;
for (int a16 = 1; a16 <= NxM; a16++) {
																	if (a1 == a16 || a2 == a16 || a3 == a16 || a4 == a16 || a5 == a16 || a6 == a16 || a7 == a16 || a8 == a16 || a9 == a16 || a11 == a16 || a12 == a16 || a26 == a16 || a27 == a16 || a28 == a16 || a29 == a16|| a30 == a16|| a21 == a16|| a22 == a16|| a23 == a16|| a24 == a16)	continue;
																	if (a13 == a16 ||a14 == a16)	continue;
																	if (a10 == a16 || a25 == a16|| a24 == a16)	continue;
for (int a17 = 1; a17 <= NxM; a17++) {
																	if (a1 == a17 || a2 == a17 || a3 == a17 || a4 == a17 || a5 == a17 || a6 == a17 || a7 == a17 || a8 == a17 || a9 == a17 || a11 == a17 || a12 == a17 || a26 == a17 || a27 == a17 || a28 == a17 || a29 == a17|| a30 == a17|| a21 == a17|| a22 == a17|| a23 == a17|| a24 == a17)	continue;
																	if (a13 == a17 ||a14 == a17||a16 == a17)	continue;
																	if (a10 == a17 || a25 == a17|| a24 == a17)	continue;
for (int a18 = 1; a18 <= NxM; a18++) {
																	if (a1 == a18 || a2 == a18 || a3 == a18 || a4 == a18 || a5 == a18 || a6 == a18 || a7 == a18 || a8 == a18 || a9 == a18 || a11 == a18 || a12 == a18 || a26 == a18 || a27 == a18 || a28 == a18 || a29 == a18|| a30 == a18|| a21 == a18|| a22 == a18|| a23 == a18|| a24 == a18)	continue;
																	if (a13 == a18 ||a14 == a18||a16 == a18||a17 == a18)	continue;
																	if (a10 == a18 || a25 == a18|| a24 == a18)	continue;
for (int a19 = 1; a19 <= NxM; a19++) {
																	if (a1 == a19 || a2 == a19 || a3 == a19 || a4 == a19 || a5 == a19 || a6 == a19 || a7 == a19 || a8 == a19 || a9 == a19 || a11 == a19 || a12 == a19 || a26 == a19 || a27 == a19 || a28 == a19 || a29 == a19|| a30 == a19|| a21 == a19|| a22 == a19|| a23 == a19|| a24 == a19)	continue;
																	if (a13 == a19 ||a14 == a19||a16 == a19||a17 == a19||a18 == a19)	continue;
																	if (a10 == a19 || a25 == a19|| a24 == a19)	continue;
for (int a20 = 1; a20 <= NxM; a20++) {
																	if (a1 == a20 || a2 == a20 || a3 == a20 || a4 == a20 || a5 == a20 || a6 == a20 || a7 == a20 || a8 == a20 || a9 == a20 || a11 == a20 || a12 == a20 || a26 == a20 || a27 == a20 || a28 == a20 || a29 == a20|| a30 == a20|| a21 == a20|| a22 == a20|| a23 == a20|| a24 == a20)	continue;
																	if (a13 == a20 ||a14 == a20||a16 == a20||a17 == a20||a18 == a20)	continue;
																	if (a10 == a20 || a25 == a20|| a24 == a20)	continue;

																	numTrials++;
																	int a13_a19 = a13+a14+a16+a17+a18+a19;
																	//int a15 = -a20 - a11a12 - a21a22 - a13_a19 + k; if (a15 > NxM || a15 < 1) continue;
																	int a15 = -(a11a12) - a13_a19 - a20 - a21a22  +k; if (a15 > NxM || a15 < 1) continue;
																	if (a1 == a15 || a2 == a15 || a3 == a15 || a4 == a15 || a5 == a15 || a6 == a15 || a7 == a15 || a8 == a15 || a9 == a15 || a11 == a15 || a12 == a15 || a26 == a15 || a27 == a15 || a28 == a15 || a29 == a15|| a30 == a15|| a21 == a15|| a22 == a15|| a23 == a15|| a24 == a15)	continue;
																	if (a13 == a15 ||a14 == a15||a16 == a15||a17 == a15||a18 == a15||a19 == a15||a20 == a15)	continue;
																	if (a10 == a15 || a25 == a15|| a24 == a15)	continue;
                                                                    OKa15 = true;
                                                                    if (!OKa31) { // latest correct seq. a1,...,a9, a11, a12, a10,  a26,...,,a30,a25,a21,..,a24,a13,a14,a16,..,a19,a20,a15
                                                                        sol[0] = a1; sol[1] = a2; sol[2] = a3; sol[3] = a4; sol[4] = a5; sol[5] = a6; sol[6] = a7; sol[7] = a8; sol[8] = a9;
                                                                        sol[9] = a11; sol[10] = a12; sol[11] = a10;
                                                                        sol[12] = a26; sol[13] = a27; sol[14] = a28; sol[15] = a29; sol[16] = a30; sol[17] = a25;
                                                                        sol[18] = a21;sol[19] = a22; sol[20] = a23; sol[21] = a24;  
                                                                        sol[22] = a13;sol[23] = a14;sol[24] = a16;sol[25] = a17;sol[26] = a18;sol[27] = a19;sol[28] = a20;sol[29] = a15; 

                                                                        // console output to track the evolution of the program every 10 seconds
                                                                        if (numSolutions == 0) {
                                                                            endelapsed = time(NULL);
                                                                            elapsedtime = (double)endelapsed - startelapsed;     // elapsed seconds
                                                                            long long unsigned seconds = elapsedtime;
                                                                            if (seconds / 10 * 10 == seconds) std::cout << "up to dependent a15 checked OK from " << numTrials << " trials" << "\r";
                                                                        }
                                                                    }
for (int a32 = 1; a32 <= NxM; a32++) {
																	if (a1 == a32 || a2 == a32 || a3 == a32 || a4 == a32 || a5 == a32 || a6 == a32 || a7 == a32 || a8 == a32 || a9 == a32 || a11 == a32 || a12 == a32 || a26 == a32 || a27 == a32 || a28 == a32 || a29 == a32|| a30 == a32|| a21 == a32|| a22 == a32|| a23 == a32|| a24 == a32)	continue;
																	if (a13 == a32 ||a14 == a32||a16 == a32||a17 == a32||a18 == a32||a19 == a32||a20 == a32)	continue;
																	if (a10 == a32 || a25 == a32|| a24 == a32|| a15 == a32)	continue;

for (int a33 = 1; a33 <= NxM; a33++) {
																	if (a1 == a33 || a2 == a33 || a3 == a33 || a4 == a33 || a5 == a33 || a6 == a33 || a7 == a33 || a8 == a33 || a9 == a33 || a11 == a33 || a12 == a33 || a26 == a33 || a27 == a33 || a28 == a33 || a29 == a33|| a30 == a33|| a21 == a33|| a22 == a33|| a23 == a33|| a24 == a33)	continue;
																	if (a13 == a33 ||a14 == a33||a16 == a33||a17 == a33||a18 == a33||a19 == a33||a20 == a33||a32 == a33)	continue;
																	if (a10 == a33 || a25 == a33|| a24 == a33|| a15 == a33)	continue;
for (int a34 = 1; a34 <= NxM; a34++) {
																	if (a1 == a34 || a2 == a34 || a3 == a34 || a4 == a34 || a5 == a34 || a6 == a34 || a7 == a34 || a8 == a34 || a9 == a34 || a11 == a34 || a12 == a34 || a26 == a34 || a27 == a34 || a28 == a34 || a29 == a34|| a30 == a34|| a21 == a34|| a22 == a34|| a23 == a34|| a24 == a34)	continue;
																	if (a13 == a34 ||a14 == a34||a16 == a34||a17 == a34||a18 == a34||a19 == a34||a20 == a34||a32 == a34||a33 == a34)	continue;
																	if (a10 == a34 || a25 == a34|| a24 == a34|| a15 == a34)	continue;

for (int a35 = 1; a35 <= NxM; a35++) {
																	if (a1 == a35 || a2 == a35 || a3 == a35 || a4 == a35 || a5 == a35 || a6 == a35 || a7 == a35 || a8 == a35 || a9 == a35 || a11 == a35 || a12 == a35 || a26 == a35 || a27 == a35 || a28 == a35 || a29 == a35|| a30 == a35|| a21 == a35|| a22 == a35|| a23 == a35|| a24 == a35)	continue;
																	if (a13 == a35 ||a14 == a35||a16 == a35||a17 == a35||a18 == a35||a19 == a35||a20 == a35||a32 == a35||a33 == a35||a34 == a35)	continue;
																	if (a10 == a35 || a25 == a35|| a24 == a35|| a15 == a35)	continue;
for (int a36 = 1; a36 <= NxM; a36++) {
																	if (a1 == a36 || a2 == a36 || a3 == a36 || a4 == a36 || a5 == a36 || a6 == a36 || a7 == a36 || a8 == a36 || a9 == a36 || a11 == a36 || a12 == a36 || a26 == a36 || a27 == a36 || a28 == a36 || a29 == a36|| a30 == a36|| a21 == a36|| a22 == a36|| a23 == a36|| a24 == a36)	continue;
																	if (a13 == a36 ||a14 == a36||a16 == a36||a17 == a36||a18 == a36||a19 == a36||a20 == a36||a32 == a36||a33 == a36||a34 == a36||a35 == a36)	continue;
																	if (a10 == a36 || a25 == a36|| a24 == a36|| a15 == a36)	continue;
for (int a37 = 1; a37 <= NxM; a37++) {
																	if (a1 == a37 || a2 == a37 || a3 == a37 || a4 == a37 || a5 == a37 || a6 == a37 || a7 == a37 || a8 == a37 || a9 == a37 || a11 == a37 || a12 == a37 || a26 == a37 || a27 == a37 || a28 == a37 || a29 == a37|| a30 == a37|| a21 == a37|| a22 == a37|| a23 == a37|| a24 == a37)	continue;
																	if (a13 == a37 ||a14 == a37||a16 == a37||a17 == a37||a18 == a37||a19 == a37||a20 == a37||a32 == a37||a33 == a37||a34 == a37||a35 == a37||a36 == a37)	continue;
																	if (a10 == a37 || a25 == a37|| a24 == a37|| a15 == a37)	continue;
for (int a38 = 1; a38 <= NxM; a38++) {
																	if (a1 == a38 || a2 == a38 || a3 == a38 || a4 == a38 || a5 == a38 || a6 == a38 || a7 == a38 || a8 == a38 || a9 == a38 || a11 == a38 || a12 == a38 || a26 == a38 || a27 == a38 || a28 == a38 || a29 == a38|| a30 == a38|| a21 == a38|| a22 == a38|| a23 == a38|| a24 == a38)	continue;
																	if (a13 == a38 ||a14 == a38||a16 == a38||a17 == a38||a18 == a38||a19 == a38||a20 == a38||a32 == a38||a33 == a38||a34 == a38||a35 == a38||a36 == a38||a37 == a38)	continue;
																	if (a10 == a38 || a25 == a38|| a24 == a38|| a15 == a38)	continue;

																	int a32_a38 = a32 + a33 + a34 + a35 + a36 + a37 + a38;
																	
																	numTrials++;

//																	int a31 = a20 + (a3a4)+(a11a12)+(a21a22)-(a32_a38)-3 * k + 741; if (a31 > NxM || a31 < 1) continue;
																	int a31 = a3a4 + (a11a12) +( a21a22) - (a32_a38) -3*k +741; if (a31 > NxM || a31 < 1) continue;

																	if (a1 == a31 || a2 == a31 || a3 == a31 || a4 == a31 || a5 == a31 || a6 == a31 || a7 == a31 || a8 == a31 || a9 == a31 || a11 == a31 || a12 == a31 || a26 == a31 || a27 == a31 || a28 == a31 || a29 == a31|| a30 == a31|| a21 == a31|| a22 == a31|| a23 == a31|| a24 == a31)	continue;
																	if (a13 == a31 ||a14 == a31||a16 == a31||a17 == a31||a18 == a31||a19 == a31||a20 == a31||a32 == a31||a33 == a31||a34 == a31||a35 == a31||a36 == a31||a37 == a31||a38 == a31)	continue;
																	if (a10 == a31 || a25 == a31|| a24 == a31|| a15 == a31)	continue;


                                                                    OKa31 = true;
                                                                    // latest correct seq. a1,...,a9, a11, a12, a10,  a26,...,,a30,a25,a21,..,a24,a13,a14,a16,..,a19,a20, a15, a32,..,a38, a31
                                                                        sol[0] = a1; sol[1] = a2; sol[2] = a3; sol[3] = a4; sol[4] = a5; sol[5] = a6; sol[6] = a7; sol[7] = a8; sol[8] = a9;
                                                                        sol[9] = a11; sol[10] = a12; sol[11] = a10;
                                                                        sol[12] = a26; sol[13] = a27; sol[14] = a28; sol[15] = a29; sol[16] = a30; sol[17] = a25;
                                                                        sol[18] = a21;sol[19] = a22; sol[20] = a23; sol[21] = a24;  
                                                                        sol[22] = a13;sol[23] = a14;sol[24] = a16;sol[25] = a17;sol[26] = a18;sol[27] = a19; sol[28] = a20; sol[29] = a15; 
																		sol[30] = a32;sol[31] = a33;  sol[32] = a34;sol[33] = a35; sol[34] = a36; sol[35] = a37; sol[36] = a38; sol[37] = a31;

                                                                        // console output to track the evolution of the program every 10 seconds
                                                                        if (numSolutions == 0) {
                                                                            endelapsed = time(NULL);
                                                                            elapsedtime = (double)endelapsed - startelapsed;     // elapsed seconds
                                                                            long long unsigned seconds = elapsedtime;
                                                                            if (seconds / 10 * 10 == seconds) std::cout << "up to dependent a31 checked OK from " << numTrials << " trials" << "\r";
                                                                        }
                                                                    

																																																													// check if the sum 1+2+...+NxM is NxM*(NxM+1)/2, a condition for a1,..,a31 to be a permuatation
																																			if (a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29 + a30 + a31 + a32 + a33 + a34 + a35 + a36 + a37 + a38 != NxM*(NxM + 1) / 2) {
																																				printf("\n a1+a2+...+a%d is not a permutation! \n", NxM);
																																				printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30);
																																				printf("%d,%d,%d,%d,%d,%d,%d,%d\n", a31, a32, a33, a34, a35, a36, a37, a38);
																																				std::cout << "Press <CR> to end...";
																																				getch();
																																				return 0;
																																			}

																																			//Optional double-ckeck:
																																			if (a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 - k != 0) {
																																				printf("eq1:a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12-k != 0 \na1=%d a2=%d a3=%d a4=%d  a5=%d  a6=%d a7=%d a8=%d a9=%d  a10=%d a11=%d a12=%d  k=%d \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, k);
																																				getch();
																																			}
																																			if (a1 + a2 + a23 + a24 + a31 + a32 + a33 + a34 + a35 + a36 + a37 + a38 - k != 0) {
																																				printf("eq2:a1+a2+a23+a24+a31+a32+a33+a34+a35+a36+a37+a38 - k != 0 \n a1=%d a2=%d a23=%d a24=%d  a31=%d  a32=%d  a33=%d a34=%d a35=%d a36=%d  a37=%d a38=%d  k=%d \n", a1, a2, a23, a24, a31, a32, a33, a34, a35, a36, a37, a38, k);
																																				getch();
																																			}
																																			if (a3 + a4 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29 + a30 - k != 0) {
																																				printf("eq3:a3+a4+a21+a22+a23+a24+a25+a26+a27+a28+a29+a30 - k != 0 \n a3=%d a4=%d a21=%d  a22=%d  a23=%d  a24=%d  a25=%d a26=%d a27=%d a28=%d  a29=%d a30=%d k=%d \n", a3, a4,  a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, k);
																																				getch();
																																			}
																																			if (a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 - k != 0) {
																																				printf("eq4:a11+a12+a13+a14+a15+a16+a17+a18+a19+a20+a21+a22 - k != 0 \n a11=%d a12=%d a13=%d a14=%d  a15=%d  a16=%d  a17=%d a18=%d a19=%d a20=%d  a21=%d a22=%d  k=%d \n", a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, k);
																																				getch();
																																			}

																																			numSolutions++;

																																			if (just100records) {
																																				//if (numSolutions > 1000) continue;
																																				if (numSolutions_a1 > 100) continue;

																																				if (just_a1) { // only a1=a1_value will bestored in file
																																					if (a1 != a1_value) continue;
																																				}
																																				numSolutions_a1++;

																																				printf("%llu from %llu \r", numSolutions, numTrials);

																																				result = fopen(out_filename.c_str(), "a"); // append mode
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25,a26,a27,a28,a29,a30);
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", a31, a32, a33, a34, a35, a36, a37, a38,k);
																																				fclose(result);

																																				result2 = fopen(out_filename2.c_str(), "a"); // append mode
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", NxM + 1 - a1, NxM + 1 - a2, NxM + 1 - a3, NxM + 1 - a4, NxM + 1 - a5, NxM + 1 - a6, NxM + 1 - a7, NxM + 1 - a8, NxM + 1 - a9, NxM + 1 - a10, NxM + 1 - a11, NxM + 1 - a12, NxM + 1 - a13, NxM + 1 - a14, NxM + 1 - a15, NxM + 1 - a16, NxM + 1 - a17, NxM + 1 - a18, NxM + 1 - a19, NxM + 1 - a20, NxM + 1 - a21, NxM + 1 - a22, NxM + 1 - a23, NxM + 1 - a24, NxM + 1 - a25, NxM + 1 - a26, NxM + 1 - a27, NxM + 1 - a28, NxM + 1 - a29, NxM+1-a30);
																																				fprintf(result2, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", NxM + 1 - a31, NxM + 1 - a32, NxM + 1 - a33, NxM + 1 - a34, NxM + 1 - a35, NxM + 1 - a36, NxM + 1 - a37, NxM + 1 - a38,kComp);
																																				fclose(result2);

																																			}
																																			else { // all souutions to file:
																																				printf("%llu from %llu \r", numSolutions, numTrials);

																																				result = fopen(out_filename.c_str(), "a"); // append mode
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30);
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", a31, a32, a33, a34, a35, a36, a37, a38,k);
																																				fclose(result);

																																				result2 = fopen(out_filename2.c_str(), "a"); // append mode
																																				fprintf(result, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", NxM + 1 - a1, NxM + 1 - a2, NxM + 1 - a3, NxM + 1 - a4, NxM + 1 - a5, NxM + 1 - a6, NxM + 1 - a7, NxM + 1 - a8, NxM + 1 - a9, NxM + 1 - a10, NxM + 1 - a11, NxM + 1 - a12, NxM + 1 - a13, NxM + 1 - a14, NxM + 1 - a15, NxM + 1 - a16, NxM + 1 - a17, NxM + 1 - a18, NxM + 1 - a19, NxM + 1 - a20, NxM + 1 - a21, NxM + 1 - a22, NxM + 1 - a23, NxM + 1 - a24, NxM + 1 - a25, NxM + 1 - a26, NxM + 1 - a27, NxM + 1 - a28, NxM + 1 - a29, NxM + 1 - a30);
																																				fprintf(result2, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", NxM + 1 - a31, NxM + 1 - a32, NxM + 1 - a33, NxM + 1 - a34, NxM + 1 - a35, NxM + 1 - a36, NxM + 1 - a37, NxM + 1 - a38,kComp);
																																				fclose(result2);
																																			}


																																		} //a19
																																	} //a18
																																} //a17
																															} //a16
																														} //a15
																													} //a14
																												} //a13
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	

	/* Stop the clock. Sort and print results.*/
	endtime = clock();
	endelapsed = time(NULL);
	cpu_time_used = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;
	elapsedtime = (double)endelapsed - startelapsed;

	printf("\n%llu from %llu \n", numSolutions, numTrials);
	result = fopen(out_filename.c_str(), "a"); // append mode
	fprintf(result, "\n Solutions found: \n %llu \n", numSolutions);
	fprintf(result, "from %llu trials \n", numTrials);

	//printf("\n---\n\t%10.2f CPU seconds\n", cpu_time_used); fprintf(result, "\n---\n\t%10.2f CPU seconds\n", cpu_time_used);
	printf("\t%10.2f elapsed seconds\n", elapsedtime);
	fprintf(result, "\t%10.2f elapsed seconds\n", elapsedtime);
	fclose(result);

	std::cout << std::endl << "dependent vars: " << "OKa10:" << OKa10 << " OKa25:" << OKa25 << " OKa24:" << OKa24 <<
		" OKa15:" << OKa15 << " OKa31:" << OKa31 << 
		std::endl << std::endl;

	//printf("a6,a7,a8,a5,a3,a2,a9,a11,a15,a27,a30,a29,a26,a31,a31,a18,a20,a14,a17: \n");
	printf("a1,...,a9, a11, a12, a10,  a26,...,,a30,a25,a21,..,a24,a13,a14,a16,..,a19,a20, a15, a32,..,a38, a31: \n");
	for (int i = 0; i < NxM; i++)
		printf("%d,", sol[i]);
	std::cout << std::endl;


	std::cout << "Solutions in file'" << out_filename << "'" << std::endl << std::endl;

	std::cout << "Press <CR> to end...";
	getch();


	return 0;
}
