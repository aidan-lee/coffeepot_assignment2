/*
 * SPI_GUI.h
 *
 *  Created on: Jul 7, 2014
 *      Author: eramirez
 */

#ifndef SPI_GUI_H_
#define SPI_GUI_H_


void InitSPIGUI_Fast(int whichPFline);
void SPI_UpdateString(char *upDateString);

void SaveOldSPISettings(void);
void RecoverOldSPISettings(void);
void SetNewSPISettings(void);

#endif /* SPI_GUI_H_ */
