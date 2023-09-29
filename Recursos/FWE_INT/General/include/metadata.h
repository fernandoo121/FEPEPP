/*
 * metadata.h	-	 Consult document  "Proyecto SARAPICO - Metadatos" https://trello.com/c/M6DWjpwr
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef METADATA_H_
#define METADATA_H_

 /* Binary Formats: Metadatos generados en EBPS. */
 #define SIZE_DATA_OPRC	7 //{a7'a6'a5'a4'a3'a2'm1'm0, m7'm6'd5'd4'd3'd2'd1'h0, h7'h6'h5'h4'm3'm2'm1'm0, m7'm6's5's4's3's2's1's0, oh7'oh6'oh5'oh4'oh3'oh2'oh1'oh0, ol7'ol6'ol5'ol4'ol3'ol2'ol1'ol0, p7'p6'f5'f4'o3'o2'm1'm0}
 #define SIZE_DATA_TLM_SPBP	4 //{r7'g6'r5'f4'r3'm2'n1'n0, t7't6't5't4't3't2't1'e0, d7'd6'd5'd4'i3'b2'b1'e0, d7'd6'd5'd4'i3'b2'b1'e0}
 #define SIZE_DATA_TLM_EBPS	1 //{r7'c6'c5'r4'f3'm2'n1'n0}
 #define SIZE_DATA_TLM (SIZE_DATA_TLM_SPBP + SIZE_DATA_TLM_EBPS)
 #define SIZE_ID_SPBP	4 //{l7'l6'l5'l4'l3'l2'l1'l0, i7'i6'i5'i4'i3'i2'i1'i0, i7'i6'i5'i4'i3'i2'i1'i0, .... , i7'i6'i5'i4'i3'i2'i1'i0}
 #define SIZE_ID_OPRR	5 //{l7'l6'l5'l4'l3'l2'l1'l0, i7'i6'i5'i4'i3'i2'i1'i0, i7'i6'i5'i4'i3'i2'i1'i0, .... , i7'i6'i5'i4'i3'i2'i1'i0}
 #define SIZE_ID_EBPS	4 //{l7'l6'l5'l4'l3'l2'l1'l0, i7'i6'i5'i4'i3'i2'i1'i0, i7'i6'i5'i4'i3'i2'i1'i0, .... , i7'i6'i5'i4'i3'i2'i1'i0}
 #define SIZE_ID_CDLL	5 //{l7'l6'l5'l4'l3'l2'l1'l0, i7'i6'i5'i4'i3'i2'i1'i0, i7'i6'i5'i4'i3'i2'i1'i0, .... , i7'i6'i5'i4'i3'i2'i1'i0}
 #define SIZE_RAW_GNSS	752 //{lh7'lh6'lh5'lh4'lh3'lh2'lh1'lh0, ll7'll6'll5'll4'll3'll2'll1'll0, r7'r6'r5'r4'r3'r2'r1'r0, .... , r7'r6'r5'r4'r3'r2'r1'r0}
 #define SIZE_METADATA_SPBP  (SIZE_DATA_OPRC + SIZE_DATA_TLM + SIZE_ID_SPBP + SIZE_ID_OPRR + SIZE_RAW_GNSS)
 #define SIZE_METADATA		(SIZE_METADATA_SPBP + SIZE_ID_EBPS + SIZE_ID_CDLL)

 /* Estructura DATA_OPRC */
 #define DATA_OPRC_CAHR0_Pos	(SIZE_DATA_OPRC - 1)	//p7'p6'f5'f4'o3'o2'm1'm0d
 #define DATA_OPRC_PT_Pos0		6
 #define DATA_OPRC_PT_Mask0		(0b11 << DATA_OPRC_PT_Pos0)
 #define DATA_OPRC_FT_Pos0		4
 #define DATA_OPRC_FT_Mask0		(0b11 << DATA_OPRC_FT_Pos0)
 #define DATA_OPRC_OR_Pos0		2
 #define DATA_OPRC_OR_Mask0		(0b11 << DATA_OPRC_OR_Pos0)
 #define DATA_OPRC_MO_Pos0		0
 #define DATA_OPRC_MO_Mask0		(0b11 << DATA_OPRC_MO_Pos0)

 #define DATA_OPRC_CAHR1_Pos	(SIZE_DATA_OPRC - 2)	//ol7'ol6'ol5'ol4'ol3'ol2'ol1'ol0_Pos
 #define DATA_OPRC_OPRC_Pos0		0
 #define DATA_OPRC_OPRC_Mask0		(0b11111111 << DATA_OPRC_OPRC_Pos0)

 #define DATA_OPRC_CAHR2_Pos	(SIZE_DATA_OPRC - 3)	//oh7'oh6'oh5'oh4'oh3'oh2'oh1'oh0
 #define DATA_OPRC_OPRC_Des			8
 #define DATA_OPRC_OPRC_Pos1		0
 #define DATA_OPRC_OPRC_Mask1	(0b11111111 << DATA_OPRC_OPRC_Pos1)

 #define DATA_OPRC_CAHR3_Pos	(SIZE_DATA_OPRC - 4)	//m7'm6's5's4's3's2's1's0
 #define DATA_OPRC_Minutes_Ind0		DATA_OPRC_CAHR3_Pos
 #define DATA_OPRC_Minutes_Pos0		6
 #define DATA_OPRC_Minutes_Mask0	(0b11 << DATA_OPRC_OPRC_Pos1)
 #define DATA_OPRC_Seconds_Ind0		DATA_OPRC_CAHR3_Pos
 #define DATA_OPRC_Seconds_Pos0		0
 #define DATA_OPRC_Seconds_Mask0	(0b111111 << DATA_OPRC_OPRC_Pos1)

 #define DATA_OPRC_CAHR4_Pos	(SIZE_DATA_OPRC - 5)	//h7'h6'h5'h4'm3'm2'm1'm0
 #define DATA_OPRC_Hour_Ind0		DATA_OPRC_CAHR4_Pos
 #define DATA_OPRC_Hour_Pos0		4
 #define DATA_OPRC_Hour_Mask0		(0b1111 << DATA_OPRC_OPRC_Pos1)
 #define DATA_OPRC_Minutes_Ind1		DATA_OPRC_CAHR4_Pos
 #define DATA_OPRC_Minutes_Des		2
 #define DATA_OPRC_Minutes_Pos1		0
 #define DATA_OPRC_Minutes_Mask1	(0b1111 << DATA_OPRC_OPRC_Pos1)

 #define DATA_OPRC_CAHR5_Pos	(SIZE_DATA_OPRC - 6)	//m7'm6'd5'd4'd3'd2'd1'h0
 #define DATA_OPRC_Month_Ind0	DATA_OPRC_CAHR5_Pos
 #define DATA_OPRC_Month_Pos0	6
 #define DATA_OPRC_Month_Mask0	(0b11 << DATA_OPRC_OPRC_Pos1)
 #define DATA_OPRC_Day_Ind0		DATA_OPRC_CAHR5_Pos
 #define DATA_OPRC_Day_Pos0		1
 #define DATA_OPRC_Day_Mask0	(0b11111 << DATA_OPRC_OPRC_Pos1)
 #define DATA_OPRC_Hour_Ind1	DATA_OPRC_CAHR5_Pos
 #define DATA_OPRC_Hour_Des		4
 #define DATA_OPRC_Hour_Pos1	0
 #define DATA_OPRC_Hour_Mask1	(0b01 << DATA_OPRC_OPRC_Pos1)

 #define DATA_OPRC_CAHR6_Pos (SIZE_DATA_OPRC - 7)	//a7'a6'a5'a4'a3'a2'm1'm0
 #define DATA_OPRC_Year_Pos0	2
 #define DATA_OPRC_Year_Mask0	(0b111111 << DATA_OPRC_OPRC_Pos1)
 #define DATA_OPRC_Month_Ind1	DATA_OPRC_CAHR6_Pos
 #define DATA_OPRC_Month_Des	2
 #define DATA_OPRC_Month_Pos1	0
 #define DATA_OPRC_Month_Mask1	(0b11 << DATA_OPRC_Month_Pos1)

 /* Estructura TLM_OPRC */
 #define DATA_TLM_CAHR0_Pos (0)	//r7'g6'r5'f4'r3'm2'n1'n0
 #define DATA_TLM_RF_Pos	7
 #define DATA_TLM_RF_Mask	(0b01 << DATA_TLM_RF_Pos)
 #define DATA_TLM_GNSS_Pos	6
 #define DATA_TLM_GNSS_Mask	(0b01 << DATA_TLM_GNSS_Pos)
 #define DATA_TLM_RFID_Pos	5
 #define DATA_TLM_RFID_Mask	(0b01 << DATA_TLM_RFID_Pos)
 #define DATA_TLM_FLASH_Pos	4
 #define DATA_TLM_FLASH_Mask	(0b01 << DATA_TLM_FLASH_Pos)
 #define DATA_TLM_RTCS_Pos	3
 #define DATA_TLM_RTCS_Mask	(0b01 << DATA_TLM_RTCS_Pos)
 #define DATA_TLM_MODE_Pos	2
 #define DATA_TLM_MODE_Mask	(0b01 << DATA_TLM_MODE_Pos)
 #define DATA_TLM_NBAT_Pos	0
 #define DATA_TLM_NBAT_Mask	(0b11 << DATA_TLM_NBAT_Pos)

 #define DATA_TLM_CAHR1_Pos (1)	//t7't6't5't4't3't2't1'e0
 #define DATA_TLM_TIME_AC_Pos	1
 #define DATA_TLM_TIME_AC_Mask	(0b1111111 << DATA_TLM_TIME_AC_Pos)
 #define DATA_TLM_EST_AC_Pos	0
 #define DATA_TLM_EST_AC_Mask	(0b1 << DATA_TLM_EST_AC_Pos)

 #define DATA_TLM_CAHR2_Pos (2)	//d7'd6'd5'd4'i3'b2'b1'e0
 #define DATA_TLM_DSTR_PT_Pos	4
 #define DATA_TLM_DSTR_PT_Mask	(0b1111 << DATA_TLM_DSTR_PT_Pos)
 #define DATA_TLM_INEST_PT_Pos	3
 #define DATA_TLM_INEST_PT_Mask	(0b1 << DATA_TLM_INEST_PT_Pos)
 #define DATA_TLM_OFFS_PT_Pos	2
 #define DATA_TLM_OFFS_PT_Mask	(0b1 << DATA_TLM_EST_OR_Pos)
 #define DATA_TLM_EST_MO_Pos	0
 #define DATA_TLM_EST_MO_Mask	(0b1 << DATA_TLM_EST_MO_Pos)

 #define DATA_TLM_CAHR3_Pos (3)	//d7'd6'd5'd4'i3'b2'b1'e0
 #define DATA_TLM_DSTR_FT_Pos	4
 #define DATA_TLM_DSTR_FT_Mask	(0b1111 << DATA_TLM_DSTR_FT_Pos)
 #define DATA_TLM_INEST_FT_Pos	3
 #define DATA_TLM_INEST_FT_Mask	(0b1 << DATA_TLM_INEST_FT_Pos)
 #define DATA_TLM_OFFS_FT_Pos	2
 #define DATA_TLM_OFFS_FT_Mask	(0b1 << DATA_TLM_EST_OR_Pos)
 #define DATA_TLM_EST_OR_Pos	1
 #define DATA_TLM_EST_OR_Mask	(0b1 << DATA_TLM_EST_OR_Pos)

 #define DATA_TLM_CAHR4_Pos (4)	//r7'c6'c5'r4'f3'm2'n1'n0
 #define DATA_TLM_RF_EBPS_Pos		7
 #define DATA_TLM_RF_EBPS_Mask		(0b01 << DATA_TLM_RF_EBPS_Pos)
 #define DATA_TLM_CEL_Pos			5
 #define DATA_TLM_CEL_Mask			(0b11 << DATA_TLM_CEL_Pos)
 #define DATA_TLM_RFID_EBPS_Pos		4
 #define DATA_TLM_RFID_EBPS_Mask	(0b01 << DATA_TLM_RFID_EBPS_Pos)
 #define DATA_TLM_FLASH_EBPS_Pos	3
 #define DATA_TLM_FLASH_EBPS_Mask	(0b01 << DATA_TLM_FLASH_Pos)
 #define DATA_TLM_MODE_EBPS_Pos		2
 #define DATA_TLM_MODE_EBPS_Mask	(0b01 << DATA_TLM_MODE_EBPS_Pos)
 #define DATA_TLM_NBAT_EBPS_Pos		0
 #define DATA_TLM_NBAT_EBPS_Mask	(0b11 << DATA_TLM_NBAT_EBPS_Pos)

 /* Estructura ID_SPBP */
 #define ID_SPBP_CAHRs_Leng 1
 #define ID_SPBP_CAHR0_Pos (SIZE_ID_SPBP - 1)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_SPBP_CAHR1_Pos (SIZE_ID_SPBP - 2)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_SPBP_CAHR2_Pos (SIZE_ID_SPBP - 3)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_SPBP_CAHR3_Pos (SIZE_ID_SPBP - 4)	//l7'l6'l5'l4'l3'l2'l1'l0

 /* Estructura ID_OPRR */
 #define ID_OPRR_CAHRs_Leng 1
 #define ID_OPRR_CAHR0_Pos  (SIZE_ID_OPRR - 1)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_OPRR_CAHR1_Pos  (SIZE_ID_OPRR - 2)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_OPRR_CAHR2_Pos  (SIZE_ID_OPRR - 3)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_OPRR_CAHR3_Pos  (SIZE_ID_OPRR - 4)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_OPRR_CAHR4_Pos  (SIZE_ID_OPRR - 5)	//l7'l6'l5'l4'l3'l2'l1'l0

 /* Estructura ID_EBPS */
 #define ID_EBPS_CAHRs_Leng 1
 #define ID_EBPS_CAHR0_Pos (SIZE_ID_EBPS - 1)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_EBPS_CAHR1_Pos (SIZE_ID_EBPS - 2)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_EBPS_CAHR2_Pos (SIZE_ID_EBPS - 3)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_EBPS_CAHR3_Pos (SIZE_ID_EBPS - 4)	//l7'l6'l5'l4'l3'l2'l1'l0

 /* Estructura ID_OPRR */
 #define ID_CDLL_CAHRs_Leng 1
 #define ID_CDLL_CAHR0_Pos  (SIZE_ID_CDLL - 1)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_CDLL_CAHR1_Pos  (SIZE_ID_CDLL - 2)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_CDLL_CAHR2_Pos  (SIZE_ID_CDLL - 3)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_CDLL_CAHR3_Pos  (SIZE_ID_CDLL - 4)	//i7'i6'i5'i4'i3'i2'i1'i0
 #define ID_CDLL_CAHR4_Pos  (SIZE_ID_CDLL - 5)	//l7'l6'l5'l4'l3'l2'l1'l0

 /* Estructura RAW_GNSS */
 #define DATA_RAW_GNSS_CAHRs_Leng 2

 #define DATA_RAW_GNSS_CAHRlength1_Pos  0	//lh7'lh6'lh5'lh4'lh3'lh2'lh1'lh0,
 #define DATA_RAW_GNSS_LENGTH_Pos1		0
 #define DATA_RAW_GNSS_LENGTH_Mask1		(0b11111111 << DATA_RAW_GNSS_LENGTH_Pos0)

 #define DATA_RAW_GNSS_CAHRlength0_Pos  1	//ll7'll6'll5'll4'll3'll2'll1'll0
 #define DATA_RAW_GNSS_LENGTH_Des		8
 #define DATA_RAW_GNSS_LENGTH_Pos0		0
 #define DATA_RAW_GNSS_LENGTH_Mask0		(0b11111111 << DATA_RAW_GNSS_LENGTH_Pos1)

 /*
 *	ESTRUCTURAS PARA COMUNICACIÓN INTERNA SOTR
 */

 // Estructura para comunicación task1 - task0 - task2
 struct data_task_0 {
	 
	 char solicitud_; // Para enviar solicitudes de usuario.
	 
	 unsigned char data_oprc[SIZE_DATA_OPRC];
	 unsigned char data_tlm[SIZE_DATA_TLM];
	 unsigned char id_spbp[SIZE_ID_SPBP];
	 unsigned char id_oprr[SIZE_ID_OPRR];
	 unsigned char id_ebps[SIZE_ID_EBPS];
	 unsigned char id_cdll[SIZE_ID_CDLL];
	 unsigned char raw_gnss[SIZE_RAW_GNSS];
 };
 
 // Estructura para comunicación task3 - task0 
 struct data_task_3 {
	 
	 unsigned int id_capataz;
	 
	 char tlm_[SIZE_DATA_TLM]; //{vinculado, no vinculado}
 };

 // Estructura para comunicación task4 - task0 
 struct data_task_4 {
	 
	 char tlm_[SIZE_DATA_TLM]; //{}
 };


#ifdef __cplusplus
extern "C" {
#endif

		
	void metadatos_al_puerto_serial_hexa(struct data_task_0 *metadatos);
	void metadatos_al_puerto_serial_ascii(struct data_task_0 *metadatos, unsigned char intentos_envio_con, float intentos_envio_max);
	void corrupcion_metadatos_unidad (struct data_task_0 *metadatos);
	
#ifdef __cplusplus
}
#endif

#endif /* METADATA_H_ */