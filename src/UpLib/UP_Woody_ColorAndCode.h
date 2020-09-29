#ifndef _UP_WoodyColorAndCode_H_
#define _UP_WoodyColorAndCode_H_
extern void UP_Woody_StartUp(u32 command);
extern void UP_Woody_ColorRecLetIssue();
extern void UP_Woody_ColorRecForbidIssue();
extern u16 UP_Woody_ColorRec_ID_Judge(void);
extern void UP_Woody_Display_ColorID(void);

extern void UP_Woody_BarCodeRecLetIssue();
extern void UP_Woody_BarCodeRecForbidIssue();
extern u16 UP_Woody_BarCodeRec_ID_Judge(void);
extern void UP_Woody_Display_BarCodeID(void);

extern void UP_Woody_QrCodeRecLetIssue();
extern void UP_Woody_QrCodeRecForbidIssue();
extern u16 UP_Woody_QrCodeRec_ID_Judge(void);
extern void UP_Woody_Display_QrCodeID(void);
#endif