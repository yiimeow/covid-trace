//CHONG YIK SOON DIA1S1G15

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning (disable:4996)
int stateTable();
int countryTable();
int continentTable();
int selection();
void red();
void cyan();
void magenta();
void boldGreen();
void yellow();
void boldYellow();
void reset();

void main()
{
	//Variable declaration
	int const PREVIOUS_NEW_CASES = 9;
	int const PREVIOUS_TOTAL_CASES = 100;
	int const PREVIOUS_TOTAL_DEATHS = 2;
	int const PREVIOUS_TOTAL_RECOVERED = 10;
	int const PREVIOUS_UNDER_TREATMENT = 88;

	int todayNewCases[30], localCases[30] = { 0 }, importedCases[30], todayDeaths[30], todayRecovered[30],
		totalCases[30], totalDeathCases[30], totalRecoveredCases[30], totalUnderTreatment[30],
		newCasesDifference[30], totalCasesDifference[30], option;

	int highestCases = 0, lowestCases = 0, dayHighestCases, dayLowestCases;

	int state, country, continent;

	int stateCases[15] = { 0 }, stateDeathsCases[15] = { 0 }, stateRecoveredCases[15] = { 0 }, importedCountryCases[15] = { 0 }, importedContinentCases[8] = { 0 };

	int localCasesLeft, importedCountryCasesLeft, importedContinentCasesLeft, deathsCasesLeft, recoveredCasesLeft;

	int stateCasesDetails[15] = { 0 }; int importedCasesDetails[15] = { 0 }, continentCasesDetails[7] = { 0 }, stateDeathsCasesDetails[15], stateRecoveredCasesDetails[15];

	float percentageOfDeathCases[30], percentageOfRecoveredCases[30], percentageOfUnderTreatment[30];
	float previousPercentageOfDeathCases = (float)PREVIOUS_TOTAL_DEATHS / PREVIOUS_TOTAL_CASES * 100.0;
	float previousPercentageOfRecoveredCases = (float)PREVIOUS_TOTAL_RECOVERED / PREVIOUS_TOTAL_CASES * 100.0;
	float deathRateDifference[30], recoveryRateDifference[30];

	char ans;

	int day = 1, yesterday, i = 0;

	//cases UI
	magenta();
	printf("                   ----------------------------------------------\n");
	printf("                   |                 COVID-19                   |\n");
	printf("                   |              CASES-TRACKING                |\n");
	printf("                   |                  SYSTEM                    |\n");
	printf("                   ----------------------------------------------\n\n");
	printf("  System is genarating information......\n\n");
	printf(" --------------------------------------------------------------------------------\n");
	printf(" |                         Previous COVID-19 CASES SUMMARY                      |\n");
	printf(" |------------------------------------------------------------------------------|\n");
	printf(" |                  |   New   |   Total   |   Total    |   Total   |    Under   |\n");
	printf(" |                  |  Cases  |   Cases   |   Deaths   | Recovered |  Treatment |\n");
	printf(" |------------------------------------------------------------------------------|\n");
	printf(" | Previous Day     |  %-5d  |   %-5d   |    %-5d   |  %-5d    |   %-5d    |\n", PREVIOUS_NEW_CASES, PREVIOUS_TOTAL_CASES, PREVIOUS_TOTAL_DEATHS, PREVIOUS_TOTAL_RECOVERED, PREVIOUS_UNDER_TREATMENT);
	printf(" |    -DAY1-        |         |           |            |           |            |\n");
	printf(" --------------------------------------------------------------------------------\n");
	reset();
	day++;
	yesterday = day - 1;
	//Getting user input for cases today.

	boldGreen();
	printf("\n  Hi,user.Can you let me know the situation of day 2 of Covid-19 in Malaysia?\n\n");
	printf("  Today number of new cases  (local)   :");
	scanf("%d", &localCases[i]);

	//while statement used to exclude unnecessary values.

	while (localCases[i] < 0) {
		rewind(stdin);
		red();
		printf(" \n\a It's an invalid number.Please try again.\n\n");
		boldGreen();
		printf("  Today number of new cases  (local)   :");
		scanf("%d", &localCases[i]);
		reset();
	}

	//check which state has cases.
	if (localCases[i] > 0) {
		boldYellow();
		printf("\n  Which state has cases occurs?");
		magenta();
		state = stateTable();

		for (int i = 1; i <= 13; i++) {
			if (i == state) {
				boldYellow();
				printf("\n  How many cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateCasesDetails[i]); //15

				while (stateCasesDetails[i] > localCases[yesterday - 1]) {
					red();
					printf("\n  Please enter a valid value!\n");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateCasesDetails[i]);
				}
				stateCases[i] += stateCasesDetails[i];
				localCasesLeft = localCases[yesterday - 1] - stateCasesDetails[i];
			}
		}
		while (localCasesLeft > 0) {
			boldYellow();
			printf("\n  There are %d cases left.Which state did they come from?", localCasesLeft);
			state = stateTable();
			boldYellow();
			printf("\n  How many cases the state had?\n  __\b\b");
			cyan();
			scanf("%d", &stateCasesDetails[state]);
			reset();

			while (stateCasesDetails[state] > localCasesLeft) {
				red();
				printf("\n  It's an invalid number.Please type again.");
				cyan();
				printf("\n  __\b\b");
				scanf("%d", &stateCasesDetails[state]);
				reset();
			}
			localCasesLeft -= stateCasesDetails[state];
			stateCases[state] += stateCasesDetails[state];
		}
	}
	boldGreen();
	printf("\n  Today number of new cases (imported) :");
	scanf("%d", &importedCases[i]);

	while (importedCases[i] < 0)
	{
		rewind(stdin);
		red();
		printf(" \n\a It's an invalid number.Please try again.\n\n");
		cyan();
		printf("  Today number of new cases (imported) :");
		scanf("%d", &importedCases[i]);
		reset();
	}

	if (importedCases[i] > 0) {

		boldYellow();
		printf("\n  Imported cases from which country? (Please choose the country in the name list first then only select others.)");
		country = countryTable();
		reset();

		if (country >= 1 && country < 12) {

			for (int i = 1; i <= 11; i++) {

				if (i == country) {
					boldYellow();
					printf("\n  How many imported cases from the country?\n  __\b\b");
					cyan();
					scanf("%d", &importedCasesDetails[i]);
					reset();

					while (importedCasesDetails[i] > importedCases[yesterday - 1]) {
						red();
						printf("  Please enter a valid value!\n  __\b\b");
						cyan();
						scanf("%d", &importedCasesDetails[i]);
					}
					importedCountryCases[i] += importedCasesDetails[i];
					importedCountryCasesLeft = importedCases[yesterday - 1] - importedCasesDetails[i];
				}
			}
			if (importedCountryCasesLeft > 0) {
				boldYellow();
				printf("\n  There are %d cases left.Which country did the imported cases come from?", importedCountryCasesLeft);
				country = countryTable();

				if (country >= 1 && country < 12) {
					boldYellow();
					printf("\n  How many imported cases the country had?\n  __\b\b");
					cyan();
					scanf("%d", &importedCasesDetails[country]);
					while (importedCasesDetails[country] > importedCountryCasesLeft) {
						red();
						printf("\n  It's an invalid number.Please type again.");
						printf("\n  __\b\b");
						scanf("%d", &importedCasesDetails[country]);
						reset();
					}
					importedCountryCasesLeft -= importedCasesDetails[country];
					importedCountryCases[country] += importedCasesDetails[country];

					while (importedCountryCasesLeft > 0) {
						printf("\n  There are %d cases left.Which country did the imported cases come from?\n", importedCountryCasesLeft);
						country = countryTable();
						boldYellow();
						printf("\n  How many imported cases the country had?\n  __\b\b");
						cyan();
						scanf("%d", &importedCasesDetails[country]);
						importedCountryCasesLeft -= importedCasesDetails[country];
						importedCountryCases[country] += importedCasesDetails[country];
					}
				}
				else if (country == 12) {
					continent = continentTable();

					for (int i = 1; i <= 11; i++) {
						if (i == continent) {
							boldYellow();
							printf("\n  How many imported cases from the continent?\n  __\b\b");
							cyan();
							scanf("%d", &continentCasesDetails[i]);
							reset();

							while (continentCasesDetails[i] > importedCountryCasesLeft) {
								red();
								printf("  Please enter a valid value!\n  __\b\b");
								reset();
								scanf("%d", &continentCasesDetails[i]);
							}
							importedContinentCasesLeft = importedCountryCasesLeft - continentCasesDetails[i];
							importedContinentCases[i] += continentCasesDetails[i];
						}
					}
					while (importedContinentCasesLeft > 0) {
						boldYellow();
						printf("\n  There are %d cases left.Which continent did the imported cases come from?\n", importedContinentCasesLeft);
						continent = continentTable();
						boldYellow();
						printf("\n  How many imported cases the continent had?\n  __\b\b");
						cyan();
						scanf("%d", &continentCasesDetails[continent]);
						reset();

						while (continentCasesDetails[continent] > importedContinentCasesLeft) {
							red();
							printf("\n  It's an invalid number.Please type again.");
							printf("\n  __\b\b");
							scanf("%d", &continentCasesDetails[continent]);
							reset();
						}
						importedContinentCasesLeft -= continentCasesDetails[continent];
						importedContinentCases[continent] += continentCasesDetails[continent];
					}
				}
			}
		}
		// europe / asia / SA / Africa...(continent)
		else if (country == 12) {
			continent = continentTable();
			for (int i = 1; i <= 11; i++) {

				if (i == continent) {
					boldYellow();
					printf("\n  How many imported cases from the continent?\n  __\b\b");
					cyan();
					scanf("%d", &continentCasesDetails[i]);
					reset();

					while (continentCasesDetails[i] > importedCases[yesterday - 1]) {
						red();
						printf("  Please enter a valid value!\n  __\b\b");
						reset();
						scanf("%d", &continentCasesDetails[i]);
					}
					importedContinentCases[i] += continentCasesDetails[i];
					importedContinentCasesLeft = importedCases[yesterday - 1] - continentCasesDetails[i];
				}
			}
			while (importedContinentCasesLeft > 0) {
				boldYellow();
				printf("\n  There are %d cases left.Which country did the imported cases come from?\n", importedContinentCasesLeft);
				magenta();
				continent = continentTable();
				reset();
				boldYellow();
				printf("\n  How many imported cases the continent had?\n  __\b\b");
				cyan();
				scanf("%d", &continentCasesDetails[continent]);
				reset();

				while (continentCasesDetails[continent] > importedContinentCasesLeft) {
					red();
					printf("\n  It's an invalid number.Please type again.");
					printf("\n  __\b\b");
					scanf("%d", &continentCasesDetails[continent]);
					reset();
				}
				importedContinentCasesLeft -= continentCasesDetails[continent];
				importedContinentCases[continent] += continentCasesDetails[continent];
			}
		}
	}
	boldGreen();
	printf("\n  Number of deaths                     :");
	scanf("%d", &todayDeaths[i]);

	while (todayDeaths[i] < 0)
	{
		rewind(stdin);
		red();
		printf(" \n\a  It's an invalid number.Please try again.\n\n");
		cyan();
		printf("  Number of deaths                     :");
		scanf("%d", &todayDeaths[i]);
	}

	if (todayDeaths[i] > 0) {
		boldYellow();
		printf("\n  Which state has death cases occurs?");
		magenta();
		state = stateTable();
		reset();


		for (int i = 1; i <= 13; i++) {
			if (i == state) {
				boldYellow();
				printf("\n  How many death cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateDeathsCasesDetails[i]);

				while (stateDeathsCasesDetails[i] > todayDeaths[yesterday - 1]) {
					red();
					printf("\n  Please enter a valid value!\n");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateDeathsCasesDetails[i]);
					reset();
				}
				stateDeathsCases[i] += stateDeathsCasesDetails[i];
				deathsCasesLeft = todayDeaths[yesterday - 1] - stateDeathsCasesDetails[i];
			}
		}

		while (deathsCasesLeft > 0) {
			boldYellow();
			printf("\n  There are %d death cases left.Which state did they come from?", deathsCasesLeft);
			state = stateTable();
			boldYellow();
			printf("\n  How many cases the state had?\n  __\b\b");
			cyan();
			scanf("%d", &stateDeathsCasesDetails[state]);
			reset();

			while (stateDeathsCasesDetails[state] > deathsCasesLeft) {
				red();
				printf("\n  It's an invalid number.Please type again.");
				cyan();
				printf("\n  __\b\b");
				scanf("%d", &stateDeathsCasesDetails[state]);
				reset();
			}
			deathsCasesLeft -= stateDeathsCasesDetails[state];
			stateDeathsCases[state] += stateDeathsCasesDetails[state];
		}
	}
	boldGreen();
	printf("\n  Number of recovered and discharged   :");
	scanf("%d", &todayRecovered[i]);
	printf("\n");

	while (todayRecovered[i] < 0)
	{
		rewind(stdin);
		red();
		printf(" \n\a  It's an invalid number.Please try again.\n\n");
		cyan();
		printf("  Number of deaths                     :");
		scanf("%d", &todayRecovered[i]);
	}

	if (todayRecovered[i] > 0) {
		boldYellow();
		printf("\n  Which state has recovered cases occurs?");
		magenta();
		state = stateTable();
		reset();

		for (int i = 1; i <= 13; i++) {
			if (i == state) {
				boldYellow();
				printf("\n  How many recovered cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateRecoveredCasesDetails[i]);

				while (stateRecoveredCasesDetails[i] > todayRecovered[yesterday - 1]) {
					red();
					printf("\n  Please enter a valid value!\n");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateRecoveredCasesDetails[i]);
					reset();
				}
				stateRecoveredCases[i] += stateRecoveredCasesDetails[i];
				recoveredCasesLeft = todayRecovered[yesterday - 1] - stateRecoveredCasesDetails[i];
			}
		}

		while (recoveredCasesLeft > 0) {
			boldYellow();
			printf("\n  There are %d recovered cases left.Which state did they come from?", recoveredCasesLeft);
			state = stateTable();
			boldYellow();
			printf("\n  How many cases the state had?\n  __\b\b");
			cyan();
			scanf("%d", &stateRecoveredCasesDetails[state]);
			reset();

			while (stateRecoveredCasesDetails[state] > recoveredCasesLeft) {
				red();
				printf("\n  It's an invalid number.Please type again.");
				cyan();
				printf("\n  __\b\b");
				scanf("%d", &stateRecoveredCasesDetails[state]);
				reset();
			}
			recoveredCasesLeft -= stateRecoveredCasesDetails[state];
			stateRecoveredCases[state] += stateRecoveredCasesDetails[state];
		}
	}

	//calculation for both table
	todayNewCases[i] = localCases[i] + importedCases[i];
	totalCases[i] = PREVIOUS_TOTAL_CASES + todayNewCases[i];
	totalDeathCases[i] = PREVIOUS_TOTAL_DEATHS + todayDeaths[i];
	totalRecoveredCases[i] = PREVIOUS_TOTAL_RECOVERED + todayRecovered[i];
	totalUnderTreatment[i] = totalCases[i] - totalDeathCases[i] - totalRecoveredCases[i];

	//calculation percentage for daily comparative report
	percentageOfDeathCases[i] = totalDeathCases[i] * 100.0 / totalCases[i];
	percentageOfRecoveredCases[i] = totalRecoveredCases[i] * 100.0 / totalCases[i];
	percentageOfUnderTreatment[i] = totalUnderTreatment[i] * 100.0 / totalCases[i];

	//user decide which table to see
	system("cls");
	option = selection();

	//Daily Summary Report
	if (option == 1) {
		magenta();
		printf("\t\t\t\t\t\t\t\t    DAY%d\n", day);
		printf(" ---------------------------------------------------------------------------\n");
		printf(" |                       Today COVID-19 CASES SUMMARY                      |\n");
		printf(" |-------------------------------------------------------------------------|\n");
		printf(" |       New       |    Total    |    Total    |    Total    |    Under    |\n");
		printf(" |      Cases      |    Cases    |    Death    |  Recovered  |  Treatment  |\n");
		printf(" |-------------------------------------------------------------------------|\n");
		printf(" |Local      %3d   |             |             |             |             |\n", localCases[i]);
		printf(" |Imported   %3d   |             |             |             |             |\n", importedCases[i]);
		printf(" |         =====   |             |             |             |             |\n");
		printf(" |Total    %5d   |     %-4d    |     %-4d    |     %-4d    |     %-4d    |\n", todayNewCases[i], totalCases[i], totalDeathCases[i], totalRecoveredCases[i], totalUnderTreatment[i]);
		printf(" |         =====   |             |             |             |             |\n");
		printf(" |-------------------------------------------------------------------------|\n");
		printf(" |                 |             |  %6.1f %%   |  %6.1f %%   |  %6.1f %%   |\n", percentageOfDeathCases[i], percentageOfRecoveredCases[i], percentageOfUnderTreatment[i]);
		printf(" ---------------------------------------------------------------------------\n");
		printf("    ");

	}
	else if (option == 2) {
		//calculation
		newCasesDifference[i] = todayNewCases[i] - PREVIOUS_NEW_CASES;
		totalCasesDifference[i] = totalCases[i] - PREVIOUS_TOTAL_CASES;
		deathRateDifference[i] = (percentageOfDeathCases[i] - previousPercentageOfDeathCases);
		recoveryRateDifference[i] = (percentageOfRecoveredCases[i] - previousPercentageOfRecoveredCases);

		//Daily Comparative Report
		magenta();
		printf("\n\n");
		printf("                        DAILY COMPARATIVE REPORT                    \n");
		printf("   ----------------------------------------------------------------\n");
		printf("   |                 |   YESTERDAY   |    TODAY    |  DIFFERENCE  |\n");
		printf("   |                 |    -DAY%2d-    |   -DAY%2d-   |              |\n", yesterday, day);
		printf("   |--------------------------------------------------------------|\n");
		printf("   | New Cases       |     % 3d       |     %3d     |", PREVIOUS_NEW_CASES, todayNewCases[i]);

		if (newCasesDifference[i] > 0)
			printf("    [+%-3d]    |\n", newCasesDifference[i]);
		else printf("    [ %-3d]    |\n", newCasesDifference[i]);

		printf("   |--------------------------------------------------------------|\n");
		printf("   | Total Cases     |     % 4d      |    % 4d     |    [+%-3d]    |\n", PREVIOUS_TOTAL_CASES, totalCases[i], totalCasesDifference[i]);
		printf("   |--------------------------------------------------------------|\n");
		printf("   | Death Rate      |    % 4.1f %%     |   %4.1f %%    |", previousPercentageOfDeathCases, percentageOfDeathCases[i]);

		if (deathRateDifference[i] > 0)
			printf("    [+%-4.1f%%]  |\n", deathRateDifference[i]);
		else printf("    [ %-4.1f%%]  |\n", deathRateDifference[i]);

		printf("   |--------------------------------------------------------------|\n");
		printf("   | Recovery Rate   |    % 2.1f %%    |   %4.1f %%    |", previousPercentageOfRecoveredCases, percentageOfRecoveredCases[i]);

		if (recoveryRateDifference[i] > 0)
			printf("    [+%-4.1f%%]  |\n", recoveryRateDifference[i]);
		else printf("    [ %-4.1f%%]  |\n", recoveryRateDifference[i]);

		printf("   ----------------------------------------------------------------\n\n");

	}
	printf("      -------------------END OF DAY%d REPORTING------------------\n\n", day);
	reset();

	highestCases = todayNewCases[i];
	lowestCases = todayNewCases[i];
	dayHighestCases = day;
	dayLowestCases = day;

	do {
		//user decision continue for next day data
		boldYellow();
		printf("   Continue to next day?");
		printf("('Y'=Yes, 'N'=No)\n\n");
		cyan();
		printf("   Your option:_\b");
		rewind(stdin);
		scanf("%c", &ans);
		rewind(stdin);
		printf("\n");
		reset();

		while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
			rewind(stdin);
			red();
			printf("   Invalid option.Please type again.\n");
			cyan();
			printf("   Your option:_\b");
			rewind(stdin);
			scanf("%c", &ans);
			rewind(stdin);
			printf("\n\n");
			reset();
		}

		if (ans == 'N' || ans == 'n') {
			yellow();
			printf("   Total days recorded       = %d days (Day 2 to Day %d)", day - 1, day);
			printf("\n\n   Highest number of cases   = %d      (Day%d)", highestCases, dayHighestCases);
			printf("\n\n   Lowest  number of cases   = %d      (Day%d)", lowestCases, dayLowestCases);
			reset();

			magenta();
			printf("\n\n\n\t                          Situation of Every State                      ");
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        State         |       Total Cases      |  Deaths  |   Recovered   |");
			printf("\n\t |                      | (from user input date) |  Cases   |     Cases     |");
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Johor         |          %3d           |   %3d    |     %3d       |", stateCases[1], stateDeathsCases[1], stateRecoveredCases[1]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Kedah         |          %3d           |   %3d    |     %3d       |", stateCases[2], stateDeathsCases[2], stateRecoveredCases[2]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |       Kelantan       |          %3d           |   %3d    |     %3d       |", stateCases[3], stateDeathsCases[3], stateRecoveredCases[3]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |       Malacca        |          %3d           |   %3d    |     %3d       |", stateCases[4], stateDeathsCases[4], stateRecoveredCases[4]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |      Terengganu      |          %3d           |   %3d    |     %3d       |", stateCases[5], stateDeathsCases[5], stateRecoveredCases[5]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Pahang        |          %3d           |   %3d    |     %3d       |", stateCases[6], stateDeathsCases[6], stateRecoveredCases[6]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Peanng        |          %3d           |   %3d    |     %3d       |", stateCases[7], stateDeathsCases[7], stateRecoveredCases[7]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Perak         |          %3d           |   %3d    |     %3d       |", stateCases[8], stateDeathsCases[8], stateRecoveredCases[8]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Perlis        |          %3d           |   %3d    |     %3d       |", stateCases[9], stateDeathsCases[9], stateRecoveredCases[9]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |        Sabah         |          %3d           |   %3d    |     %3d       |", stateCases[10], stateDeathsCases[10], stateRecoveredCases[10]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |       Sarawak        |          %3d           |   %3d    |     %3d       |", stateCases[11], stateDeathsCases[11], stateRecoveredCases[11]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |       Selangor       |          %3d           |   %3d    |     %3d       |", stateCases[12], stateDeathsCases[12], stateRecoveredCases[12]);
			printf("\n\t ----------------------------------------------------------------------------");
			printf("\n\t |   Negeri Sembilan    |          %3d           |   %3d    |     %3d       |", stateCases[13], stateDeathsCases[13], stateRecoveredCases[13]);
			printf("\n\t ----------------------------------------------------------------------------");
			reset();

			boldYellow();
			printf("\n\n\t  Do you want to view the imported cases table from different country? ('Y'=Yes, 'N'=No)");
			cyan();
			printf("\n\n\t  Your option:[ ]\b\b");
			rewind(stdin);
			scanf("%c", &ans);
			rewind(stdin);

			if (ans == 'Y' || ans == 'y') {
				rewind(stdin);
				yellow();
				printf("\n\n\t  Table below shows the imported cases from different country.");
				printf("\n\t  Please note that imported cases of a country in name list won't include in its continent.");
				magenta();
				printf("\n\n\t\t       Imported Cases from different country / continent   ");
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |        Country / Continent        |    Imported Cases    |");
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Singapore             |         %3d          |", importedCountryCases[1]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Indonesia             |         %3d          |", importedCountryCases[2]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |              Egypt                |         %3d          |", importedCountryCases[3]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Thailand              |         %3d          |", importedCountryCases[4]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |            Philippines            |         %3d          |", importedCountryCases[5]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Vietnam               |         %3d          |", importedCountryCases[6]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Brunei                |         %3d          |", importedCountryCases[7]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Myanmar               |         %3d          |", importedCountryCases[8]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |            Cambodia               |         %3d          |", importedCountryCases[9]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Laos                  |         %3d          |", importedCountryCases[10]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |             Japan                 |         %3d          |", importedCountryCases[11]);
				printf("\n\t\t ------------------------------------------------------------");
				printf("\n\t\t |          | 1. Africa              |         %3d          |", importedContinentCases[1]);
				printf("\n\t\t |          -------------------------------------------------");
				printf("\n\t\t |          | 2. Europe              |         %3d          |", importedContinentCases[2]);
				printf("\n\t\t |          -------------------------------------------------");
				printf("\n\t\t |  Others  | 3. South America       |         %3d          |", importedContinentCases[3]);
				printf("\n\t\t |          -------------------------------------------------");
				printf("\n\t\t |          | 4. Asia                |         %3d          |", importedContinentCases[4]);
				printf("\n\t\t |          -------------------------------------------------");
				printf("\n\t\t |          | 5. North America       |         %3d          |", importedContinentCases[5]);
				printf("\n\t\t |          -------------------------------------------------");
				printf("\n\t\t |          | 6. Oceania             |         %3d          |", importedContinentCases[6]);
				printf("\n\t\t ------------------------------------------------------------");
			}
			yellow();
			printf("\n\n\n\tHave a great day! Thank you!!!\n\n");
			break;
		}
		day++;
		i++;
		yesterday = day - 1;
		system("cls");

		yellow();
		printf("\n\t---------Day %d---------\n", day);

		boldGreen();
		printf("\n  Today number of new cases  (local)   :");
		scanf("%d", &localCases[i]);

		//while statement used to exclude unnecessary values.

		while (localCases[i] < 0) {
			rewind(stdin);
			red();
			printf(" \n\a It's an invalid number.Please try again.\n\n");
			boldGreen();
			printf("  Today number of new cases  (local)   :");
			scanf("%d", &localCases[i]);
			reset();
		}

		//check which state has cases.
		if (localCases[i] > 0) {
			boldYellow();
			printf("\n  Which state has cases occurs?");
			magenta();
			state = stateTable();
			reset();

			for (int i = 1; i <= 13; i++) {
				if (i == state) {
					boldYellow();
					printf("\n  How many cases the state had?\n  __\b\b");
					cyan();
					scanf("%d", &stateCasesDetails[i]); //15

					while (stateCasesDetails[i] > localCases[yesterday - 1]) {
						red();
						printf("\n  Please enter a valid value!\n");
						cyan();
						printf("\n  __\b\b");
						scanf("%d", &stateCasesDetails[i]);
						reset();
					}
					stateCases[i] += stateCasesDetails[i];
					localCasesLeft = localCases[yesterday - 1] - stateCasesDetails[i];
				}
			}
			while (localCasesLeft > 0) {
				boldYellow();
				printf("\n  There are %d cases left.Which state did they come from?", localCasesLeft);
				state = stateTable();
				boldYellow();
				printf("\n  How many cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateCasesDetails[state]);
				reset();

				while (stateCasesDetails[state] > localCasesLeft) {
					red();
					printf("\n  It's an invalid number.Please type again.");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateCasesDetails[state]);
					reset();
				}
				localCasesLeft -= stateCasesDetails[state];
				stateCases[state] += stateCasesDetails[state];
			}
		}
		boldGreen();
		printf("\n  Today number of new cases (imported) :");
		scanf("%d", &importedCases[i]);

		while (importedCases[i] < 0)
		{
			rewind(stdin);
			red();
			printf(" \n\a It's an invalid number.Please try again.\n\n");
			cyan();
			printf("  Today number of new cases (imported) :");
			scanf("%d", &importedCases[i]);
			reset();
		}

		if (importedCases[i] > 0) {

			boldYellow();
			printf("\n  Imported cases from which country? (Please choose the country in the name list first then only select others.)");
			country = countryTable();
			reset();

			if (country >= 1 && country < 12) {

				for (int i = 1; i <= 11; i++) {

					if (i == country) {
						boldYellow();
						printf("\n  How many imported cases from the country?\n  __\b\b");
						cyan();
						scanf("%d", &importedCasesDetails[i]);
						reset();

						while (importedCasesDetails[i] > importedCases[yesterday - 1]) {
							red();
							printf("  Please enter a valid value!\n  __\b\b");
							cyan();
							scanf("%d", &importedCasesDetails[i]);
						}
						importedCountryCases[i] += importedCasesDetails[i];
						importedCountryCasesLeft = importedCases[yesterday - 1] - importedCasesDetails[i];
					}
				}
				if (importedCountryCasesLeft > 0) {
					boldYellow();
					printf("\n  There are %d cases left.Which country did the imported cases come from?", importedCountryCasesLeft);
					country = countryTable();

					if (country >= 1 && country < 12) {
						boldYellow();
						printf("\n  How many imported cases the country had?\n  __\b\b");
						cyan();
						scanf("%d", &importedCasesDetails[country]);
						while (importedCasesDetails[country] > importedCountryCasesLeft) {
							red();
							printf("\n  It's an invalid number.Please type again.");
							printf("\n  __\b\b");
							scanf("%d", &importedCasesDetails[country]);
							reset();
						}
						importedCountryCasesLeft -= importedCasesDetails[country];
						importedCountryCases[country] += importedCasesDetails[country];

						while (importedCountryCasesLeft > 0) {
							printf("\n  There are %d cases left.Which country did the imported cases come from?\n", importedCountryCasesLeft);
							country = countryTable();
							boldYellow();
							printf("\n  How many imported cases the country had?\n  __\b\b");
							cyan();
							scanf("%d", &importedCasesDetails[country]);
							importedCountryCasesLeft -= importedCasesDetails[country];
							importedCountryCases[country] += importedCasesDetails[country];
						}
					}
					else if (country == 12) {
						continent = continentTable();

						for (int i = 1; i <= 11; i++) {
							if (i == continent) {
								boldYellow();
								printf("\n  How many imported cases from the continent?\n  __\b\b");
								cyan();
								scanf("%d", &continentCasesDetails[i]);
								reset();

								while (continentCasesDetails[i] > importedCountryCasesLeft) {
									red();
									printf("  Please enter a valid value!\n  __\b\b");
									reset();
									scanf("%d", &continentCasesDetails[i]);
								}
								importedContinentCasesLeft = importedCountryCasesLeft - continentCasesDetails[i];
								importedContinentCases[i] += continentCasesDetails[i];
							}
						}
						while (importedContinentCasesLeft > 0) {
							boldYellow();
							printf("\n  There are %d cases left.Which continent did the imported cases come from?\n", importedContinentCasesLeft);
							continent = continentTable();
							boldYellow();
							printf("\n  How many imported cases the continent had?\n  __\b\b");
							cyan();
							scanf("%d", &continentCasesDetails[continent]);
							reset();

							while (continentCasesDetails[continent] > importedContinentCasesLeft) {
								red();
								printf("\n  It's an invalid number.Please type again.");
								printf("\n  __\b\b");
								scanf("%d", &continentCasesDetails[continent]);
								reset();
							}
							importedContinentCasesLeft -= continentCasesDetails[continent];
							importedContinentCases[continent] += continentCasesDetails[continent];
						}
					}
				}
			}
			// europe / asia / SA / Africa...(continent)
			else if (country == 12) {
				continent = continentTable();
				for (int i = 1; i <= 11; i++) {

					if (i == continent) {
						boldYellow();
						printf("\n  How many imported cases from the continent?\n  __\b\b");
						cyan();
						scanf("%d", &continentCasesDetails[i]);
						reset();

						while (continentCasesDetails[i] > importedCases[yesterday - 1]) {
							red();
							printf("  Please enter a valid value!\n  __\b\b");
							reset();
							scanf("%d", &continentCasesDetails[i]);
						}
						importedContinentCases[i] += continentCasesDetails[i];
						importedContinentCasesLeft = importedCases[yesterday - 1] - continentCasesDetails[i];
					}
				}
				while (importedContinentCasesLeft > 0) {
					boldYellow();
					printf("\n  There are %d cases left.Which country did the imported cases come from?\n", importedContinentCasesLeft);
					magenta();
					continent = continentTable();
					reset();
					boldYellow();
					printf("\n  How many imported cases the continent had?\n  __\b\b");
					cyan();
					scanf("%d", &continentCasesDetails[continent]);
					reset();

					while (continentCasesDetails[continent] > importedContinentCasesLeft) {
						red();
						printf("\n  It's an invalid number.Please type again.");
						printf("\n  __\b\b");
						scanf("%d", &continentCasesDetails[continent]);
						reset();
					}
					importedContinentCasesLeft -= continentCasesDetails[continent];
					importedContinentCases[continent] += continentCasesDetails[continent];
				}
			}
		}
		boldGreen();
		printf("\n  Number of deaths                     :");
		scanf("%d", &todayDeaths[i]);

		while (todayDeaths[i] < 0)
		{
			rewind(stdin);
			red();
			printf(" \n\a  It's an invalid number.Please try again.\n\n");
			cyan();
			printf("  Number of deaths                     :");
			scanf("%d", &todayDeaths[i]);
		}

		if (todayDeaths[i] > 0) {
			boldYellow();
			printf("\n  Which state has death cases occurs?");
			magenta();
			state = stateTable();
			reset();


			for (int i = 1; i <= 13; i++) {
				if (i == state) {
					boldYellow();
					printf("\n  How many death cases the state had?\n  __\b\b");
					cyan();
					scanf("%d", &stateDeathsCasesDetails[i]);

					while (stateDeathsCasesDetails[i] > todayDeaths[yesterday - 1]) {
						red();
						printf("\n  Please enter a valid value!\n");
						cyan();
						printf("\n  __\b\b");
						scanf("%d", &stateDeathsCasesDetails[i]);
						reset();
					}
					stateDeathsCases[i] += stateDeathsCasesDetails[i];
					deathsCasesLeft = todayDeaths[yesterday - 1] - stateDeathsCasesDetails[i];
				}
			}

			while (deathsCasesLeft > 0) {
				boldYellow();
				printf("\n  There are %d death cases left.Which state did they come from?", deathsCasesLeft);
				state = stateTable();
				boldYellow();
				printf("\n  How many cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateDeathsCasesDetails[state]);
				reset();

				while (stateDeathsCasesDetails[state] > deathsCasesLeft) {
					red();
					printf("\n  It's an invalid number.Please type again.");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateDeathsCasesDetails[state]);
					reset();
				}
				deathsCasesLeft -= stateDeathsCasesDetails[state];
				stateDeathsCases[state] += stateDeathsCasesDetails[state];
			}
		}
		boldGreen();
		printf("\n Number of recovered and discharged   :");
		scanf("%d", &todayRecovered[i]);
		printf("\n");

		while (todayRecovered[i] < 0)
		{
			rewind(stdin);
			red();
			printf(" \n\a  It's an invalid number.Please try again.\n\n");
			cyan();
			printf("  Number of deaths                     :");
			scanf("%d", &todayRecovered[i]);
		}

		if (todayRecovered[i] > 0) {
			boldYellow();
			printf("\n  Which state has recovered cases occurs?");
			magenta();
			state = stateTable();
			reset();

			for (int i = 1; i <= 13; i++) {
				if (i == state) {
					boldYellow();
					printf("\n  How many recovered cases the state had?\n  __\b\b");
					cyan();
					scanf("%d", &stateRecoveredCasesDetails[i]);

					while (stateRecoveredCasesDetails[i] > todayRecovered[yesterday - 1]) {
						red();
						printf("\n  Please enter a valid value!\n");
						cyan();
						printf("\n  __\b\b");
						scanf("%d", &stateRecoveredCasesDetails[i]);
						reset();
					}
					stateRecoveredCases[i] += stateRecoveredCasesDetails[i];
					recoveredCasesLeft = todayRecovered[yesterday - 1] - stateRecoveredCasesDetails[i];
				}
			}

			while (recoveredCasesLeft > 0) {
				boldYellow();
				printf("\n  There are %d recovered cases left.Which state did they come from?", recoveredCasesLeft);
				state = stateTable();
				boldYellow();
				printf("\n  How many cases the state had?\n  __\b\b");
				cyan();
				scanf("%d", &stateRecoveredCasesDetails[state]);
				reset();

				while (stateRecoveredCasesDetails[state] > recoveredCasesLeft) {
					red();
					printf("\n  It's an invalid number.Please type again.");
					cyan();
					printf("\n  __\b\b");
					scanf("%d", &stateRecoveredCasesDetails[state]);
					reset();
				}
				recoveredCasesLeft -= stateRecoveredCasesDetails[state];
				stateRecoveredCases[state] += stateRecoveredCasesDetails[state];
			}
		}

		system("cls");
		option = selection();

		todayNewCases[i] = localCases[i] + importedCases[i];
		totalCases[i] = totalCases[i - 1] + todayNewCases[i];
		totalDeathCases[i] = totalDeathCases[i - 1] + todayDeaths[i];
		totalRecoveredCases[i] = totalRecoveredCases[i - 1] + todayRecovered[i];
		totalUnderTreatment[i] = totalCases[i] - totalDeathCases[i] - totalRecoveredCases[i];

		percentageOfDeathCases[i] = totalDeathCases[i] * 100.0 / totalCases[i];
		percentageOfRecoveredCases[i] = totalRecoveredCases[i] * 100.0 / totalCases[i];

		percentageOfUnderTreatment[i] = totalUnderTreatment[i] * 100.0 / totalCases[i];

		if (option == 1) {
			magenta();
			printf("\t\t\t\t\t\t\t\t    DAY%d \n", day);
			printf(" ---------------------------------------------------------------------------\n");
			printf(" |                       Today COVID-19 CASES SUMMARY                      |\n");
			printf(" |-------------------------------------------------------------------------|\n");
			printf(" |       New       |    Total    |    Total    |    Total    |    Under    |\n");
			printf(" |      Cases      |    Cases    |    Death    |  Recovered  |  Treatment  |\n");
			printf(" |-------------------------------------------------------------------------|\n");
			printf(" |Local      %3d   |             |             |             |             |\n", localCases[i]);
			printf(" |Imported   %3d   |             |             |             |             |\n", importedCases[i]);
			printf(" |         =====   |             |             |             |             |\n");
			printf(" |Total    %5d   |     %-4d    |     %-4d    |     %-4d    |     %-4d    |\n", todayNewCases[i], totalCases[i], totalDeathCases[i], totalRecoveredCases[i], totalUnderTreatment[i]);
			printf(" |         =====   |             |             |             |             |\n");
			printf(" |-------------------------------------------------------------------------|\n");
			printf(" |                 |             |  %6.1f %%   |  %6.1f %%   |  %6.1f %%   |\n", percentageOfDeathCases[i], percentageOfRecoveredCases[i], percentageOfUnderTreatment[i]);
			printf(" ---------------------------------------------------------------------------\n");
			printf("    ");
		}
		else if (option == 2) {
			//calculation
			newCasesDifference[i] = todayNewCases[i] - todayNewCases[i - 1];
			totalCasesDifference[i] = totalCases[i] - totalCases[i - 1];

			deathRateDifference[i] = percentageOfDeathCases[i] - percentageOfDeathCases[i - 1];
			recoveryRateDifference[i] = percentageOfRecoveredCases[i] - percentageOfRecoveredCases[i - 1];

			//Daily Comparative Report
			magenta();
			printf("\n\n");
			printf("\t                        DAILY COMPARATIVE REPORT                    \n");
			printf("\t   ----------------------------------------------------------------\n");
			printf("\t   |                 |   YESTERDAY   |    TODAY    |  DIFFERENCE  |\n");
			printf("\t   |                 |     -DAY%d-    |   -DAY%d-    |              |\n", yesterday, day);
			printf("\t   |--------------------------------------------------------------|\n");
			printf("\t   | New Cases       |     % 3d       |     %3d     |", todayNewCases[i - 1], todayNewCases[i], newCasesDifference[i]);

			//symbol to change positive or negative value difference
			if (newCasesDifference[i] > 0)
				printf("    [+%-3d]    |\n", newCasesDifference[i]);
			else printf("    [%-3d ]    |\n", newCasesDifference[i]);

			printf("\t   |--------------------------------------------------------------|\n");
			printf("\t   | Total Cases     |     % 4d      |    % 4d     |    [+%-3d]    |\n", totalCases[i - 1], totalCases[i], totalCasesDifference[i]);
			printf("\t   |--------------------------------------------------------------|\n");
			printf("\t   | Death Rate      |    %4.1f %%     |   %4.1f %%    |", percentageOfDeathCases[i - 1], percentageOfDeathCases[i]);

			//symbol to change positive or negative value difference
			if (deathRateDifference[i] > 0)
				printf("    [+%-4.1f%%]  |\n", deathRateDifference[i]);
			else printf("    [%-4.1f%% ]  |\n", deathRateDifference[i]);

			printf("\t   |--------------------------------------------------------------|\n");
			printf("\t   | Recovery Rate   |    %4.1f %%     |   %4.1f %%    |", percentageOfRecoveredCases[i - 1], percentageOfRecoveredCases[i]);

			//symbol to change positive or negative value difference
			if (recoveryRateDifference[i] > 0)
				printf("    [+%-4.1f%%]  |\n", recoveryRateDifference[i]);
			else printf("    [%-4.1f%% ]  |\n", recoveryRateDifference[i]);

			//indicate which day has the highest cases
			if (highestCases < todayNewCases[i]) {
				highestCases = todayNewCases[i];
				dayHighestCases = day;
			}

			//indicate which day has the lowest cases
			else if (lowestCases > todayNewCases[i]) {
				lowestCases = todayNewCases[i];
				dayLowestCases = day;
			}

			printf("\t   ----------------------------------------------------------------\n\n");
		}
		printf("\t      -------------------END OF DAY%d REPORTING------------------\n\n", day);
		reset();

	} while (ans == 'Y' || ans == 'y'); //looping system when user want to continue


	system("pause");
}

int stateTable() {

	int stateOption;
	magenta();
	printf("\n\n-------------------------------------------------------------------------------------");
	printf("\n  1.Johor\t  2.Kedah\t  3.Kelantan\t  4.Malacca\n\n  5.Terengganu");
	printf("\t  6.Pahang\t  7.Penang\t  8.Perak\n\n  9.Perlis\t  10.Sabah\t  11.Sarawak\t  ");
	printf("12.Selangor\n\n  13.Negeri Sembilan");
	printf("\n-------------------------------------------------------------------------------------");

	cyan();
	printf("\n\n  OPTION:[  ]\b\b\b");
	scanf("%d", &stateOption);
	rewind(stdin);
	reset();

	while (stateOption < 1 || stateOption>13) {
		red();
		printf("\n Please key in available value.\n");
		cyan();
		printf("\n\n  OPTION:[ ]\b\b");
		scanf("%d", &stateOption);
		rewind(stdin);
	}


	return stateOption;
}

int countryTable() {

	int countryOption;

	magenta();
	printf("\n\n-------------------------------------------------------------------------------------");
	printf("\n  1.Singapore\t  2.Indonesia\t  3.Egypt\t  4.Thailand\n\n  5.Philippines");
	printf("\t  6.Vietnam\t  7.Brunei\t  8.Myanmar\n\n  9.Cambodia\t  10.Laos\t  11.Japan\t  ");
	printf("\n\n  12.Others");
	printf("\n-------------------------------------------------------------------------------------");

	cyan();
	printf("\n\n  OPTION:[  ]\b\b\b");
	scanf("%d", &countryOption);
	rewind(stdin);
	reset();

	while (countryOption < 1 || countryOption>12) {
		red();
		printf("\n Please key in available value.\n");
		cyan();
		printf("\n\n  OPTION:[ ]\b\b");
		scanf("%d", &countryOption);
		rewind(stdin);
		reset();
	}

	return countryOption;
}

int continentTable() {

	int continentOption;

	boldYellow();
	printf("\n  The country belongs to which continent?");
	magenta();
	printf("\n\n-----------------------------------------------------------------------------------");
	printf("\n  1.Africa  \t2.Europe\n\n  3.South America  4.Asia\n\n  5.North America  6.Oceania  ");
	printf("\n--------------------------------------------------------------------------------------");
	cyan();
	printf("\n\n  OPTION:[ ]\b\b");
	scanf("%d", &continentOption);
	rewind(stdin);
	reset();

	while (continentOption > 6 || continentOption < 1) {
		rewind(stdin);
		red();
		printf("\n  It's an invalid option.Please type again.");
		cyan();
		printf("\n\n  OPTION:[ ]\b\b");
		scanf("%d", &continentOption);
		rewind(stdin);
		reset();
	}

	return continentOption;
}

int selection() {

	int option;

	cyan();
	printf(" \n\t SELECT REPORT:\n\n");
	printf(" \n\n\t\t\t1.Daily Summary Report");
	printf(" \n\n\n\n\t\t\t2.Daily Comparative Report\n\n\n");
	printf(" \tOPTION:[ ]\b\b");
	scanf("%d", &option);
	rewind(stdin);
	reset();

	while (option != 1 && option != 2) {
		rewind(stdin);
		red();
		printf("\nIt's an invalid value.Please key in again.");
		reset();
		cyan();
		printf(" \n\n\tOPTION:[ ]\b\b");
		scanf("%d", &option);
		rewind(stdin);
		reset();
	}

	return option;
}

void red() {
	printf("\033[1;31m");
}

void cyan() {
	printf("\033[1;36m");
}

void magenta() {
	printf("\033[1;35m");
}

void boldGreen() {
	printf("\033[1;32m");
}

void yellow() {
	printf("\033[0;33m");
}

void boldYellow() {
	printf("\033[01;33m");
}

void reset() {
	printf("\033[0m");
}