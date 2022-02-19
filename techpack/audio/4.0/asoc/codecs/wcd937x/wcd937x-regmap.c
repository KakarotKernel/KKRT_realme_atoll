// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#include <linux/regmap.h>
#include <linux/device.h>
#include "wcd937x-registers.h"

extern const u8 wcd937x_reg_access[WCD937X_REGISTERS_MAX_SIZE];

static const struct reg_default wcd937x_defaults[] = {
	{ WCD937X_ANA_BIAS,                      0x00 },
	{ WCD937X_ANA_RX_SUPPLIES,               0x00 },
	{ WCD937X_ANA_HPH,                       0x0C },
	{ WCD937X_ANA_EAR,                       0x00 },
	{ WCD937X_ANA_EAR_COMPANDER_CTL,         0x02 },
	{ WCD937X_ANA_TX_CH1,                    0x20 },
	{ WCD937X_ANA_TX_CH2,                    0x00 },
	{ WCD937X_ANA_TX_CH3,                    0x20 },
	{ WCD937X_ANA_TX_CH3_HPF,                0x00 },
	{ WCD937X_ANA_MICB1_MICB2_DSP_EN_LOGIC,  0x00 },
	{ WCD937X_ANA_MICB3_DSP_EN_LOGIC,        0x00 },
	{ WCD937X_ANA_MBHC_MECH,                 0x39 },
	{ WCD937X_ANA_MBHC_ELECT,                0x08 },
	{ WCD937X_ANA_MBHC_ZDET,                 0x00 },
	{ WCD937X_ANA_MBHC_RESULT_1,             0x00 },
	{ WCD937X_ANA_MBHC_RESULT_2,             0x00 },
	{ WCD937X_ANA_MBHC_RESULT_3,             0x00 },
	{ WCD937X_ANA_MBHC_BTN0,                 0x00 },
	{ WCD937X_ANA_MBHC_BTN1,                 0x10 },
	{ WCD937X_ANA_MBHC_BTN2,                 0x20 },
	{ WCD937X_ANA_MBHC_BTN3,                 0x30 },
	{ WCD937X_ANA_MBHC_BTN4,                 0x40 },
	{ WCD937X_ANA_MBHC_BTN5,                 0x50 },
	{ WCD937X_ANA_MBHC_BTN6,                 0x60 },
	{ WCD937X_ANA_MBHC_BTN7,                 0x70 },
	{ WCD937X_ANA_MICB1,                     0x10 },
	{ WCD937X_ANA_MICB2,                     0x10 },
	{ WCD937X_ANA_MICB2_RAMP,                0x00 },
	{ WCD937X_ANA_MICB3,                     0x10 },
	{ WCD937X_BIAS_CTL,                      0x2A },
	{ WCD937X_BIAS_VBG_FINE_ADJ,             0x55 },
	{ WCD937X_LDOL_VDDCX_ADJUST,             0x01 },
	{ WCD937X_LDOL_DISABLE_LDOL,             0x00 },
	{ WCD937X_MBHC_CTL_CLK,                  0x00 },
	{ WCD937X_MBHC_CTL_ANA,                  0x00 },
	{ WCD937X_MBHC_CTL_SPARE_1,              0x00 },
	{ WCD937X_MBHC_CTL_SPARE_2,              0x00 },
	{ WCD937X_MBHC_CTL_BCS,                  0x00 },
	{ WCD937X_MBHC_MOISTURE_DET_FSM_STATUS,  0x00 },
	{ WCD937X_MBHC_TEST_CTL,                 0x00 },
	{ WCD937X_LDOH_MODE,                     0x2B },
	{ WCD937X_LDOH_BIAS,                     0x68 },
	{ WCD937X_LDOH_STB_LOADS,                0x00 },
	{ WCD937X_LDOH_SLOWRAMP,                 0x50 },
	{ WCD937X_MICB1_TEST_CTL_1,              0x1A },
	{ WCD937X_MICB1_TEST_CTL_2,              0x18 },
	{ WCD937X_MICB1_TEST_CTL_3,              0xA4 },
	{ WCD937X_MICB2_TEST_CTL_1,              0x1A },
	{ WCD937X_MICB2_TEST_CTL_2,              0x18 },
	{ WCD937X_MICB2_TEST_CTL_3,              0xA4 },
	{ WCD937X_MICB3_TEST_CTL_1,              0x1A },
	{ WCD937X_MICB3_TEST_CTL_2,              0x18 },
	{ WCD937X_MICB3_TEST_CTL_3,              0xA4 },
	{ WCD937X_TX_COM_ADC_VCM,                0x39 },
	{ WCD937X_TX_COM_BIAS_ATEST,             0xC0 },
	{ WCD937X_TX_COM_ADC_INT1_IB,            0x6F },
	{ WCD937X_TX_COM_ADC_INT2_IB,            0x4F },
	{ WCD937X_TX_COM_TXFE_DIV_CTL,           0x2E },
	{ WCD937X_TX_COM_TXFE_DIV_START,         0x00 },
	{ WCD937X_TX_COM_TXFE_DIV_STOP_9P6M,     0xC7 },
	{ WCD937X_TX_COM_TXFE_DIV_STOP_12P288M,  0xFF },
	{ WCD937X_TX_1_2_TEST_EN,                0xCC },
	{ WCD937X_TX_1_2_ADC_IB,                 0x09 },
	{ WCD937X_TX_1_2_ATEST_REFCTL,           0x0A },
	{ WCD937X_TX_1_2_TEST_CTL,               0x38 },
	{ WCD937X_TX_1_2_TEST_BLK_EN,            0xFF },
	{ WCD937X_TX_1_2_TXFE_CLKDIV,            0x00 },
	{ WCD937X_TX_1_2_SAR2_ERR,               0x00 },
	{ WCD937X_TX_1_2_SAR1_ERR,               0x00 },
	{ WCD937X_TX_3_TEST_EN,                  0xCC },
	{ WCD937X_TX_3_ADC_IB,                   0x09 },
	{ WCD937X_TX_3_ATEST_REFCTL,             0x0A },
	{ WCD937X_TX_3_TEST_CTL,                 0x38 },
	{ WCD937X_TX_3_TEST_BLK_EN,              0xFF },
	{ WCD937X_TX_3_TXFE_CLKDIV,              0x00 },
	{ WCD937X_TX_3_SPARE_MONO,               0x00 },
	{ WCD937X_TX_3_SAR1_ERR,                 0x00 },
	{ WCD937X_CLASSH_MODE_1,                 0x40 },
	{ WCD937X_CLASSH_MODE_2,                 0x3A },
	{ WCD937X_CLASSH_MODE_3,                 0x00 },
	{ WCD937X_CLASSH_CTRL_VCL_1,             0x70 },
	{ WCD937X_CLASSH_CTRL_VCL_2,             0x82 },
	{ WCD937X_CLASSH_CTRL_CCL_1,             0x31 },
	{ WCD937X_CLASSH_CTRL_CCL_2,             0x80 },
	{ WCD937X_CLASSH_CTRL_CCL_3,             0x80 },
	{ WCD937X_CLASSH_CTRL_CCL_4,             0x51 },
	{ WCD937X_CLASSH_CTRL_CCL_5,             0x00 },
	{ WCD937X_CLASSH_BUCK_TMUX_A_D,          0x00 },
	{ WCD937X_CLASSH_BUCK_SW_DRV_CNTL,       0x77 },
	{ WCD937X_CLASSH_SPARE,                  0x00 },
	{ WCD937X_FLYBACK_EN,                    0x4E },
	{ WCD937X_FLYBACK_VNEG_CTRL_1,           0x0B },
	{ WCD937X_FLYBACK_VNEG_CTRL_2,           0x45 },
	{ WCD937X_FLYBACK_VNEG_CTRL_3,           0x74 },
	{ WCD937X_FLYBACK_VNEG_CTRL_4,           0x7F },
	{ WCD937X_FLYBACK_VNEG_CTRL_5,           0x83 },
	{ WCD937X_FLYBACK_VNEG_CTRL_6,           0x98 },
	{ WCD937X_FLYBACK_VNEG_CTRL_7,           0xA9 },
	{ WCD937X_FLYBACK_VNEG_CTRL_8,           0x68 },
	{ WCD937X_FLYBACK_VNEG_CTRL_9,           0x64 },
	{ WCD937X_FLYBACK_VNEGDAC_CTRL_1,        0xED },
	{ WCD937X_FLYBACK_VNEGDAC_CTRL_2,        0xF0 },
	{ WCD937X_FLYBACK_VNEGDAC_CTRL_3,        0xA6 },
	{ WCD937X_FLYBACK_CTRL_1,                0x65 },
	{ WCD937X_FLYBACK_TEST_CTL,              0x00 },
	{ WCD937X_RX_AUX_SW_CTL,                 0x00 },
	{ WCD937X_RX_PA_AUX_IN_CONN,             0x00 },
	{ WCD937X_RX_TIMER_DIV,                  0x32 },
	{ WCD937X_RX_OCP_CTL,                    0x1F },
	{ WCD937X_RX_OCP_COUNT,                  0x77 },
	{ WCD937X_RX_BIAS_EAR_DAC,               0xA0 },
	{ WCD937X_RX_BIAS_EAR_AMP,               0xAA },
	{ WCD937X_RX_BIAS_HPH_LDO,               0xA9 },
	{ WCD937X_RX_BIAS_HPH_PA,                0xAA },
	{ WCD937X_RX_BIAS_HPH_RDACBUFF_CNP2,     0x8A },
	{ WCD937X_RX_BIAS_HPH_RDAC_LDO,          0x88 },
	{ WCD937X_RX_BIAS_HPH_CNP1,              0x82 },
	{ WCD937X_RX_BIAS_HPH_LOWPOWER,          0x82 },
	{ WCD937X_RX_BIAS_AUX_DAC,               0xA0 },
	{ WCD937X_RX_BIAS_AUX_AMP,               0xAA },
	{ WCD937X_RX_BIAS_VNEGDAC_BLEEDER,       0x50 },
	{ WCD937X_RX_BIAS_MISC,                  0x00 },
	{ WCD937X_RX_BIAS_BUCK_RST,              0x08 },
	{ WCD937X_RX_BIAS_BUCK_VREF_ERRAMP,      0x44 },
	{ WCD937X_RX_BIAS_FLYB_ERRAMP,           0x40 },
	{ WCD937X_RX_BIAS_FLYB_BUFF,             0xAA },
	{ WCD937X_RX_BIAS_FLYB_MID_RST,          0x14 },
	{ WCD937X_HPH_L_STATUS,                  0x04 },
	{ WCD937X_HPH_R_STATUS,                  0x04 },
	{ WCD937X_HPH_CNP_EN,                    0x80 },
	{ WCD937X_HPH_CNP_WG_CTL,                0x9A },
	{ WCD937X_HPH_CNP_WG_TIME,               0x14 },
	{ WCD937X_HPH_OCP_CTL,                   0x28 },
	{ WCD937X_HPH_AUTO_CHOP,                 0x16 },
	{ WCD937X_HPH_CHOP_CTL,                  0x83 },
	{ WCD937X_HPH_PA_CTL1,                   0x46 },
	{ WCD937X_HPH_PA_CTL2,                   0x50 },
	{ WCD937X_HPH_L_EN,                      0x80 },
	{ WCD937X_HPH_L_TEST,                    0xE0 },
	{ WCD937X_HPH_L_ATEST,                   0x50 },
	{ WCD937X_HPH_R_EN,                      0x80 },
	{ WCD937X_HPH_R_TEST,                    0xE0 },
	{ WCD937X_HPH_R_ATEST,                   0x54 },
	{ WCD937X_HPH_RDAC_CLK_CTL1,             0x99 },
	{ WCD937X_HPH_RDAC_CLK_CTL2,             0x9B },
	{ WCD937X_HPH_RDAC_LDO_CTL,              0x33 },
	{ WCD937X_HPH_RDAC_CHOP_CLK_LP_CTL,      0x00 },
	{ WCD937X_HPH_REFBUFF_UHQA_CTL,          0xA8 },
	{ WCD937X_HPH_REFBUFF_LP_CTL,            0x0E },
	{ WCD937X_HPH_L_DAC_CTL,                 0x20 },
	{ WCD937X_HPH_R_DAC_CTL,                 0x20 },
	{ WCD937X_HPH_SURGE_HPHLR_SURGE_COMP_SEL, 0x55 },
	{ WCD937X_HPH_SURGE_HPHLR_SURGE_EN,      0x19 },
	{ WCD937X_HPH_SURGE_HPHLR_SURGE_MISC1,   0xA0 },
	{ WCD937X_HPH_SURGE_HPHLR_SURGE_STATUS,  0x00 },
	{ WCD937X_EAR_EAR_EN_REG,                0x22 },
	{ WCD937X_EAR_EAR_PA_CON,                0x44 },
	{ WCD937X_EAR_EAR_SP_CON,                0xDB },
	{ WCD937X_EAR_EAR_DAC_CON,               0x80 },
	{ WCD937X_EAR_EAR_CNP_FSM_CON,           0xB2 },
	{ WCD937X_EAR_TEST_CTL,                  0x00 },
	{ WCD937X_EAR_STATUS_REG_1,              0x00 },
	{ WCD937X_EAR_STATUS_REG_2,              0x00 },
	{ WCD937X_ANA_NEW_PAGE_REGISTER,         0x00 },
	{ WCD937X_HPH_NEW_ANA_HPH2,              0x00 },
	{ WCD937X_HPH_NEW_ANA_HPH3,              0x00 },
	{ WCD937X_SLEEP_CTL,                     0x16 },
	{ WCD937X_SLEEP_WATCHDOG_CTL,            0x00 },
	{ WCD937X_MBHC_NEW_ELECT_REM_CLAMP_CTL,  0x00 },
	{ WCD937X_MBHC_NEW_CTL_1,                0x02 },
	#ifndef OPLUS_ARCH_EXTENDS
	/*Suresh.Alla@MULTIMEDIA.AUDIODRIVER.HEADSETDET, 2020/07/31, Modify for disable moisture detect. bit2~3*/
	{ WCD937X_MBHC_NEW_CTL_2,                0x05 },
	#else /*OPLUS_ARCH_EXTENDS*/
	{ WCD937X_MBHC_NEW_CTL_2,                0x01 },
	#endif /*OPLUS_ARCH_EXTENDS*/
	{ WCD937X_MBHC_NEW_PLUG_DETECT_CTL,      0xE9 },
	{ WCD937X_MBHC_NEW_ZDET_ANA_CTL,         0x0F },
	{ WCD937X_MBHC_NEW_ZDET_RAMP_CTL,        0x00 },
	{ WCD937X_MBHC_NEW_FSM_STATUS,           0x00 },
	{ WCD937X_MBHC_NEW_ADC_RESULT,           0x00 },
	{ WCD937X_TX_NEW_TX_CH2_SEL,             0x00 },
	{ WCD937X_AUX_AUXPA,                     0x00 },
	{ WCD937X_LDORXTX_MODE,                  0x0C },
	{ WCD937X_LDORXTX_CONFIG,                0x10 },
	{ WCD937X_DIE_CRACK_DIE_CRK_DET_EN,      0x00 },
	{ WCD937X_DIE_CRACK_DIE_CRK_DET_OUT,     0x00 },
	{ WCD937X_HPH_NEW_INT_RDAC_GAIN_CTL,     0x40 },
	{ WCD937X_HPH_NEW_INT_RDAC_HD2_CTL_L,    0x81 },
	{ WCD937X_HPH_NEW_INT_RDAC_VREF_CTL,     0x10 },
	{ WCD937X_HPH_NEW_INT_RDAC_OVERRIDE_CTL, 0x00 },
	{ WCD937X_HPH_NEW_INT_RDAC_HD2_CTL_R,    0x81 },
	{ WCD937X_HPH_NEW_INT_PA_MISC1,          0x22 },
	{ WCD937X_HPH_NEW_INT_PA_MISC2,          0x00 },
	{ WCD937X_HPH_NEW_INT_PA_RDAC_MISC,      0x00 },
	{ WCD937X_HPH_NEW_INT_HPH_TIMER1,        0xFE },
	{ WCD937X_HPH_NEW_INT_HPH_TIMER2,        0x02 },
	{ WCD937X_HPH_NEW_INT_HPH_TIMER3,        0x4E },
	{ WCD937X_HPH_NEW_INT_HPH_TIMER4,        0x54 },
	{ WCD937X_HPH_NEW_INT_PA_RDAC_MISC2,     0x00 },
	{ WCD937X_HPH_NEW_INT_PA_RDAC_MISC3,     0x00 },
	{ WCD937X_RX_NEW_INT_HPH_RDAC_BIAS_LOHIFI, 0x62 },
	{ WCD937X_RX_NEW_INT_HPH_RDAC_BIAS_ULP,  0x01 },
	{ WCD937X_RX_NEW_INT_HPH_RDAC_LDO_LP,    0x11 },
	{ WCD937X_MBHC_NEW_INT_MOISTURE_DET_DC_CTRL, 0x57 },
	{ WCD937X_MBHC_NEW_INT_MOISTURE_DET_POLLING_CTRL, 0x01 },
	{ WCD937X_MBHC_NEW_INT_MECH_DET_CURRENT,  0x00 },
	{ WCD937X_MBHC_NEW_INT_SPARE_2,           0x00 },
	{ WCD937X_EAR_INT_NEW_EAR_CHOPPER_CON,    0xA8 },
	{ WCD937X_EAR_INT_NEW_CNP_VCM_CON1,       0x42 },
	{ WCD937X_EAR_INT_NEW_CNP_VCM_CON2,       0x22 },
	{ WCD937X_EAR_INT_NEW_EAR_DYNAMIC_BIAS,   0x00 },
	{ WCD937X_AUX_INT_EN_REG,                 0x00 },
	{ WCD937X_AUX_INT_PA_CTRL,                0x06 },
	{ WCD937X_AUX_INT_SP_CTRL,                0xD2 },
	{ WCD937X_AUX_INT_DAC_CTRL,               0x80 },
	{ WCD937X_AUX_INT_CLK_CTRL,               0x50 },
	{ WCD937X_AUX_INT_TEST_CTRL,              0x00 },
	{ WCD937X_AUX_INT_STATUS_REG,             0x00 },
	{ WCD937X_AUX_INT_MISC,                   0x00 },
	{ WCD937X_LDORXTX_INT_BIAS,               0x6E },
	{ WCD937X_LDORXTX_INT_STB_LOADS_DTEST,    0x50 },
	{ WCD937X_LDORXTX_INT_TEST0,              0x1C },
	{ WCD937X_LDORXTX_INT_STARTUP_TIMER,      0xFF },
	{ WCD937X_LDORXTX_INT_TEST1,              0x1F },
	{ WCD937X_LDORXTX_INT_STATUS,             0x00 },
	{ WCD937X_SLEEP_INT_WATCHDOG_CTL_1,       0x0A },
	{ WCD937X_SLEEP_INT_WATCHDOG_CTL_2,       0x0A },
	{ WCD937X_DIE_CRACK_INT_DIE_CRK_DET_INT1, 0x02 },
	{ WCD937X_DIE_CRACK_INT_DIE_CRK_DET_INT2, 0x60 },
	{ WCD937X_DIGITAL_PAGE_REGISTER,          0x00 },
	{ WCD937X_DIGITAL_CHIP_ID0,               0x01 },
	{ WCD937X_DIGITAL_CHIP_ID1,               0x00 },
	{ WCD937X_DIGITAL_CHIP_ID2,               0x0A },
	{ WCD937X_DIGITAL_CHIP_ID3,               0x01 },
	{ WCD937X_DIGITAL_CDC_RST_CTL,            0x03 },
	{ WCD937X_DIGITAL_TOP_CLK_CFG,            0x00 },
	{ WCD937X_DIGITAL_CDC_ANA_CLK_CTL,        0x00 },
	{ WCD937X_DIGITAL_CDC_DIG_CLK_CTL,        0x00 },
	{ WCD937X_DIGITAL_SWR_RST_EN,             0x00 },
	{ WCD937X_DIGITAL_CDC_PATH_MODE,          0x55 },
	{ WCD937X_DIGITAL_CDC_RX_RST,             0x00 },
	{ WCD937X_DIGITAL_CDC_RX0_CTL,            0xFC },
	{ WCD937X_DIGITAL_CDC_RX1_CTL,            0xFC },
	{ WCD937X_DIGITAL_CDC_RX2_CTL,            0xFC },
	{ WCD937X_DIGITAL_DEM_BYPASS_DATA0,       0x55 },
	{ WCD937X_DIGITAL_DEM_BYPASS_DATA1,       0x55 },
	{ WCD937X_DIGITAL_DEM_BYPASS_DATA2,       0x55 },
	{ WCD937X_DIGITAL_DEM_BYPASS_DATA3,       0x01 },
	{ WCD937X_DIGITAL_CDC_COMP_CTL_0,         0x00 },
	{ WCD937X_DIGITAL_CDC_RX_DELAY_CTL,       0x66 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A1_0,       0x00 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A1_1,       0x01 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A2_0,       0x63 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A2_1,       0x04 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A3_0,       0xAC },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A3_1,       0x04 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A4_0,       0x1A },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A4_1,       0x03 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A5_0,       0xBC },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A5_1,       0x02 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A6_0,       0xC7 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_A7_0,       0xF8 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_C_0,        0x47 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_C_1,        0x43 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_C_2,        0xB1 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_C_3,        0x17 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R1,         0x4B },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R2,         0x26 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R3,         0x32 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R4,         0x57 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R5,         0x63 },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R6,         0x7C },
	{ WCD937X_DIGITAL_CDC_HPH_DSM_R7,         0x57 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A1_0,       0x00 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A1_1,       0x01 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A2_0,       0x96 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A2_1,       0x09 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A3_0,       0xAB },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A3_1,       0x05 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A4_0,       0x1C },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A4_1,       0x02 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A5_0,       0x17 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A5_1,       0x02 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A6_0,       0xAA },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_A7_0,       0xE3 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_C_0,        0x69 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_C_1,        0x54 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_C_2,        0x02 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_C_3,        0x15 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R1,         0xA4 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R2,         0xB5 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R3,         0x86 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R4,         0x85 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R5,         0xAA },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R6,         0xE2 },
	{ WCD937X_DIGITAL_CDC_AUX_DSM_R7,         0x62 },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_RX_0,      0x55 },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_RX_1,      0xA9 },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_DSD_0,     0x3D },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_DSD_1,     0x2E },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_DSD_2,     0x01 },
	{ WCD937X_DIGITAL_CDC_AUX_GAIN_DSD_0,     0x00 },
	{ WCD937X_DIGITAL_CDC_AUX_GAIN_DSD_1,     0xFC },
	{ WCD937X_DIGITAL_CDC_AUX_GAIN_DSD_2,     0x01 },
	{ WCD937X_DIGITAL_CDC_HPH_GAIN_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_AUX_GAIN_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_EAR_PATH_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_SWR_CLH,            0x00 },
	{ WCD937X_DIGITAL_SWR_CLH_BYP,            0x00 },
	{ WCD937X_DIGITAL_CDC_TX0_CTL,            0x68 },
	{ WCD937X_DIGITAL_CDC_TX1_CTL,            0x68 },
	{ WCD937X_DIGITAL_CDC_TX2_CTL,            0x68 },
	{ WCD937X_DIGITAL_CDC_TX_RST,             0x00 },
	{ WCD937X_DIGITAL_CDC_REQ_CTL,            0x01 },
	{ WCD937X_DIGITAL_CDC_AMIC_CTL,           0x07 },
	{ WCD937X_DIGITAL_CDC_DMIC_CTL,           0x00 },
	{ WCD937X_DIGITAL_CDC_DMIC1_CTL,          0x01 },
	{ WCD937X_DIGITAL_CDC_DMIC2_CTL,          0x01 },
	{ WCD937X_DIGITAL_CDC_DMIC3_CTL,          0x01 },
	{ WCD937X_DIGITAL_EFUSE_CTL,              0x2B },
	{ WCD937X_DIGITAL_EFUSE_PRG_CTL,          0x00 },
	{ WCD937X_DIGITAL_EFUSE_TEST_CTL_0,       0x00 },
	{ WCD937X_DIGITAL_EFUSE_TEST_CTL_1,       0x00 },
	{ WCD937X_DIGITAL_EFUSE_T_DATA_0,         0x00 },
	{ WCD937X_DIGITAL_EFUSE_T_DATA_1,         0x00 },
	{ WCD937X_DIGITAL_PDM_WD_CTL0,            0x00 },
	{ WCD937X_DIGITAL_PDM_WD_CTL1,            0x00 },
	{ WCD937X_DIGITAL_PDM_WD_CTL2,            0x00 },
	{ WCD937X_DIGITAL_INTR_MODE,              0x00 },
	{ WCD937X_DIGITAL_INTR_MASK_0,            0xFF },
	{ WCD937X_DIGITAL_INTR_MASK_1,            0xFF },
	{ WCD937X_DIGITAL_INTR_MASK_2,            0x0F },
	{ WCD937X_DIGITAL_INTR_STATUS_0,          0x00 },
	{ WCD937X_DIGITAL_INTR_STATUS_1,          0x00 },
	{ WCD937X_DIGITAL_INTR_STATUS_2,          0x00 },
	{ WCD937X_DIGITAL_INTR_CLEAR_0,           0x00 },
	{ WCD937X_DIGITAL_INTR_CLEAR_1,           0x00 },
	{ WCD937X_DIGITAL_INTR_CLEAR_2,           0x00 },
	{ WCD937X_DIGITAL_INTR_LEVEL_0,           0x00 },
	{ WCD937X_DIGITAL_INTR_LEVEL_1,           0x00 },
	{ WCD937X_DIGITAL_INTR_LEVEL_2,           0x00 },
	{ WCD937X_DIGITAL_INTR_SET_0,             0x00 },
	{ WCD937X_DIGITAL_INTR_SET_1,             0x00 },
	{ WCD937X_DIGITAL_INTR_SET_2,             0x00 },
	{ WCD937X_DIGITAL_INTR_TEST_0,            0x00 },
	{ WCD937X_DIGITAL_INTR_TEST_1,            0x00 },
	{ WCD937X_DIGITAL_INTR_TEST_2,            0x00 },
	{ WCD937X_DIGITAL_CDC_CONN_RX0_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_CONN_RX1_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_CONN_RX2_CTL,       0x00 },
	{ WCD937X_DIGITAL_CDC_CONN_TX_CTL,        0x00 },
	{ WCD937X_DIGITAL_LOOP_BACK_MODE,         0x00 },
	{ WCD937X_DIGITAL_SWR_DAC_TEST,           0x00 },
	{ WCD937X_DIGITAL_SWR_HM_TEST_RX_0,       0x40 },
	{ WCD937X_DIGITAL_SWR_HM_TEST_TX_0,       0x40 },
	{ WCD937X_DIGITAL_SWR_HM_TEST_RX_1,       0x00 },
	{ WCD937X_DIGITAL_SWR_HM_TEST_TX_1,       0x00 },
	{ WCD937X_DIGITAL_SWR_HM_TEST,            0x00 },
	{ WCD937X_DIGITAL_PAD_CTL_PDM_RX0,        0xF1 },
	{ WCD937X_DIGITAL_PAD_CTL_PDM_RX1,        0xF1 },
	{ WCD937X_DIGITAL_PAD_CTL_PDM_TX0,        0xF1 },
	{ WCD937X_DIGITAL_PAD_CTL_PDM_TX1,        0xF1 },
	{ WCD937X_DIGITAL_PAD_INP_DIS_0,          0x00 },
	{ WCD937X_DIGITAL_PAD_INP_DIS_1,          0x00 },
	{ WCD937X_DIGITAL_DRIVE_STRENGTH_0,       0x00 },
	{ WCD937X_DIGITAL_DRIVE_STRENGTH_1,       0x00 },
	{ WCD937X_DIGITAL_DRIVE_STRENGTH_2,       0x00 },
	{ WCD937X_DIGITAL_RX_DATA_EDGE_CTL,       0x1F },
	{ WCD937X_DIGITAL_TX_DATA_EDGE_CTL,       0x10 },
	{ WCD937X_DIGITAL_GPIO_MODE,              0x00 },
	{ WCD937X_DIGITAL_PIN_CTL_OE,             0x00 },
	{ WCD937X_DIGITAL_PIN_CTL_DATA_0,         0x00 },
	{ WCD937X_DIGITAL_PIN_CTL_DATA_1,         0x00 },
	{ WCD937X_DIGITAL_PIN_STATUS_0,           0x00 },
	{ WCD937X_DIGITAL_PIN_STATUS_1,           0x00 },
	{ WCD937X_DIGITAL_DIG_DEBUG_CTL,          0x00 },
	{ WCD937X_DIGITAL_DIG_DEBUG_EN,           0x00 },
	{ WCD937X_DIGITAL_ANA_CSR_DBG_ADD,        0x00 },
	{ WCD937X_DIGITAL_ANA_CSR_DBG_CTL,        0x48 },
	{ WCD937X_DIGITAL_SSP_DBG,                0x00 },
	{ WCD937X_DIGITAL_MODE_STATUS_0,          0x00 },
	{ WCD937X_DIGITAL_MODE_STATUS_1,          0x00 },
	{ WCD937X_DIGITAL_SPARE_0,                0x00 },
	{ WCD937X_DIGITAL_SPARE_1,                0x00 },
	{ WCD937X_DIGITAL_SPARE_2,                0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_0,            0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_1,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_2,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_3,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_4,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_5,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_6,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_7,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_8,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_9,            0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_10,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_11,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_12,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_13,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_14,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_15,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_16,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_17,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_18,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_19,           0xFF },
	{ WCD937X_DIGITAL_EFUSE_REG_20,           0x0E },
	{ WCD937X_DIGITAL_EFUSE_REG_21,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_22,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_23,           0xF8 },
	{ WCD937X_DIGITAL_EFUSE_REG_24,           0x16 },
	{ WCD937X_DIGITAL_EFUSE_REG_25,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_26,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_27,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_28,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_29,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_30,           0x00 },
	{ WCD937X_DIGITAL_EFUSE_REG_31,           0x00 },
};

static bool wcd937x_readable_register(struct device *dev, unsigned int reg)
{
	if(reg <= WCD937X_BASE_ADDRESS)
		return 0;
	return wcd937x_reg_access[WCD937X_REG(reg)] & RD_REG;
}

static bool wcd937x_writeable_register(struct device *dev, unsigned int reg)
{
	if(reg <= WCD937X_BASE_ADDRESS)
		return 0;
	return wcd937x_reg_access[WCD937X_REG(reg)] & WR_REG;
}

static bool wcd937x_volatile_register(struct device *dev, unsigned int reg)
{
	if(reg <= WCD937X_BASE_ADDRESS)
		return 0;
	if ((wcd937x_reg_access[WCD937X_REG(reg)] & RD_REG)
		&& !(wcd937x_reg_access[WCD937X_REG(reg)] & WR_REG))
		return true;
	return false;
}

struct regmap_config wcd937x_regmap_config = {
	.name = "wcd937x_csr",
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.reg_defaults = wcd937x_defaults,
	.num_reg_defaults = ARRAY_SIZE(wcd937x_defaults),
	.max_register = WCD937X_MAX_REGISTER,
	.readable_reg = wcd937x_readable_register,
	.writeable_reg = wcd937x_writeable_register,
	.volatile_reg = wcd937x_volatile_register,
	.can_multi_write = true,
};