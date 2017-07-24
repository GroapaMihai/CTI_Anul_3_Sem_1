/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/student/Desktop/334CA_BOSPY_SI_Alina/schelet/decode_unit.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {0, 0};
static unsigned int ng3[] = {15U, 0U};
static int ng4[] = {1, 0};
static unsigned int ng5[] = {31U, 0U};
static int ng6[] = {2, 0};
static unsigned int ng7[] = {74U, 0U};
static int ng8[] = {3, 0};
static unsigned int ng9[] = {64U, 0U};
static int ng10[] = {9, 0};
static unsigned int ng11[] = {4U, 0U};
static int ng12[] = {4, 0};
static unsigned int ng13[] = {10U, 0U};
static int ng14[] = {5, 0};
static unsigned int ng15[] = {9U, 0U};
static int ng16[] = {6, 0};
static unsigned int ng17[] = {6U, 0U};
static int ng18[] = {7, 0};
static unsigned int ng19[] = {11U, 0U};
static int ng20[] = {13, 0};
static unsigned int ng21[] = {20U, 0U};
static int ng22[] = {10, 0};
static unsigned int ng23[] = {21U, 0U};
static int ng24[] = {11, 0};
static unsigned int ng25[] = {14U, 0U};
static int ng26[] = {12, 0};
static int ng27[] = {8, 0};



static void Always_10_0(char *t0)
{
    char t4[8];
    char t18[8];
    char t19[8];
    char t20[8];
    char t27[8];
    char t38[8];
    char t39[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    int t15;
    char *t16;
    char *t17;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    char *t36;
    char *t37;

LAB0:    t1 = (t0 + 2664U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(10, ng0);
    t2 = (t0 + 3232);
    *((int *)t2) = 1;
    t3 = (t0 + 2696);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(10, ng0);

LAB5:    xsi_set_current_line(11, ng0);
    t5 = (t0 + 1184U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t4 + 4);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t6);
    t9 = (t8 >> 0);
    *((unsigned int *)t4) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 0);
    *((unsigned int *)t5) = t11;
    t12 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t12 & 65535U);
    t13 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t13 & 65535U);

LAB6:    t14 = ((char*)((ng1)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 16, t14, 16);
    if (t15 == 1)
        goto LAB7;

LAB8:
LAB10:
LAB9:    xsi_set_current_line(15, ng0);

LAB12:    xsi_set_current_line(17, ng0);
    t2 = (t0 + 1184U);
    t3 = *((char **)t2);
    memset(t19, 0, 8);
    t2 = (t19 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 0);
    *((unsigned int *)t19) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 0);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t12 & 15U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 15U);
    t6 = (t0 + 1184U);
    t7 = *((char **)t6);
    memset(t20, 0, 8);
    t6 = (t20 + 4);
    t14 = (t7 + 4);
    t21 = *((unsigned int *)t7);
    t22 = (t21 >> 9);
    *((unsigned int *)t20) = t22;
    t23 = *((unsigned int *)t14);
    t24 = (t23 >> 9);
    *((unsigned int *)t6) = t24;
    t25 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t25 & 127U);
    t26 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t26 & 127U);
    xsi_vlogtype_concat(t18, 11, 11, 2U, t20, 7, t19, 4);

LAB13:
LAB15:
LAB14:    xsi_set_current_line(18, ng0);

LAB17:    xsi_set_current_line(20, ng0);
    t16 = (t0 + 1184U);
    t17 = *((char **)t16);
    memset(t27, 0, 8);
    t16 = (t27 + 4);
    t28 = (t17 + 4);
    t29 = *((unsigned int *)t17);
    t30 = (t29 >> 8);
    *((unsigned int *)t27) = t30;
    t31 = *((unsigned int *)t28);
    t32 = (t31 >> 8);
    *((unsigned int *)t16) = t32;
    t33 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t33 & 255U);
    t34 = *((unsigned int *)t16);
    *((unsigned int *)t16) = (t34 & 255U);

LAB18:    t35 = ((char*)((ng3)));
    t15 = xsi_vlog_unsigned_case_compare(t27, 8, t35, 8);
    if (t15 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng5)));
    t15 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 8);
    if (t15 == 1)
        goto LAB21;

LAB22:
LAB24:
LAB23:    xsi_set_current_line(27, ng0);

LAB26:    xsi_set_current_line(29, ng0);
    t2 = (t0 + 1184U);
    t3 = *((char **)t2);
    memset(t19, 0, 8);
    t2 = (t19 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 9);
    *((unsigned int *)t19) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 9);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t12 & 127U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 127U);

LAB27:    t6 = ((char*)((ng7)));
    t15 = xsi_vlog_unsigned_case_compare(t19, 7, t6, 7);
    if (t15 == 1)
        goto LAB28;

LAB29:    t2 = ((char*)((ng9)));
    t15 = xsi_vlog_unsigned_case_compare(t19, 7, t2, 7);
    if (t15 == 1)
        goto LAB30;

LAB31:
LAB33:
LAB32:    xsi_set_current_line(36, ng0);

LAB35:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1184U);
    t3 = *((char **)t2);
    memset(t20, 0, 8);
    t2 = (t20 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 10);
    *((unsigned int *)t20) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 10);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t12 & 63U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 63U);

LAB36:    t6 = ((char*)((ng11)));
    t15 = xsi_vlog_unsigned_case_compare(t20, 6, t6, 6);
    if (t15 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng13)));
    t15 = xsi_vlog_unsigned_case_compare(t20, 6, t2, 6);
    if (t15 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng15)));
    t15 = xsi_vlog_unsigned_case_compare(t20, 6, t2, 6);
    if (t15 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng17)));
    t15 = xsi_vlog_unsigned_case_compare(t20, 6, t2, 6);
    if (t15 == 1)
        goto LAB43;

LAB44:    t2 = ((char*)((ng19)));
    t15 = xsi_vlog_unsigned_case_compare(t20, 6, t2, 6);
    if (t15 == 1)
        goto LAB45;

LAB46:
LAB48:
LAB47:    xsi_set_current_line(54, ng0);

LAB50:    xsi_set_current_line(55, ng0);
    t2 = (t0 + 1184U);
    t3 = *((char **)t2);
    memset(t38, 0, 8);
    t2 = (t38 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 11);
    *((unsigned int *)t38) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 11);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t12 & 31U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 31U);

LAB51:    t6 = ((char*)((ng21)));
    t15 = xsi_vlog_unsigned_case_compare(t38, 5, t6, 5);
    if (t15 == 1)
        goto LAB52;

LAB53:    t2 = ((char*)((ng23)));
    t15 = xsi_vlog_unsigned_case_compare(t38, 5, t2, 5);
    if (t15 == 1)
        goto LAB54;

LAB55:
LAB57:
LAB56:    xsi_set_current_line(62, ng0);

LAB59:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 1184U);
    t3 = *((char **)t2);
    memset(t39, 0, 8);
    t2 = (t39 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 12);
    *((unsigned int *)t39) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 12);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t39);
    *((unsigned int *)t39) = (t12 & 15U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 15U);

LAB60:    t6 = ((char*)((ng25)));
    t15 = xsi_vlog_unsigned_case_compare(t39, 4, t6, 4);
    if (t15 == 1)
        goto LAB61;

LAB62:
LAB64:
LAB63:    xsi_set_current_line(67, ng0);

LAB66:    xsi_set_current_line(68, ng0);
    t2 = ((char*)((ng27)));
    t3 = (t0 + 1584);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);

LAB65:
LAB58:
LAB49:
LAB34:
LAB25:
LAB16:
LAB11:    goto LAB2;

LAB7:    xsi_set_current_line(14, ng0);
    t16 = ((char*)((ng2)));
    t17 = (t0 + 1584);
    xsi_vlogvar_assign_value(t17, t16, 0, 0, 8);
    goto LAB11;

LAB19:    xsi_set_current_line(23, ng0);
    t36 = ((char*)((ng4)));
    t37 = (t0 + 1584);
    xsi_vlogvar_assign_value(t37, t36, 0, 0, 8);
    goto LAB25;

LAB21:    xsi_set_current_line(26, ng0);
    t3 = ((char*)((ng6)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB25;

LAB28:    xsi_set_current_line(32, ng0);
    t7 = ((char*)((ng8)));
    t14 = (t0 + 1584);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 8);
    goto LAB34;

LAB30:    xsi_set_current_line(35, ng0);
    t3 = ((char*)((ng10)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB34;

LAB37:    xsi_set_current_line(41, ng0);
    t7 = ((char*)((ng12)));
    t14 = (t0 + 1584);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 8);
    goto LAB49;

LAB39:    xsi_set_current_line(44, ng0);
    t3 = ((char*)((ng14)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB49;

LAB41:    xsi_set_current_line(47, ng0);
    t3 = ((char*)((ng16)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB49;

LAB43:    xsi_set_current_line(50, ng0);
    t3 = ((char*)((ng18)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB49;

LAB45:    xsi_set_current_line(53, ng0);
    t3 = ((char*)((ng20)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB49;

LAB52:    xsi_set_current_line(58, ng0);
    t7 = ((char*)((ng22)));
    t14 = (t0 + 1584);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 8);
    goto LAB58;

LAB54:    xsi_set_current_line(61, ng0);
    t3 = ((char*)((ng24)));
    t5 = (t0 + 1584);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 8);
    goto LAB58;

LAB61:    xsi_set_current_line(66, ng0);
    t7 = ((char*)((ng26)));
    t14 = (t0 + 1584);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 8);
    goto LAB65;

}

static void Always_85_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    char *t9;
    char *t10;
    int t11;
    int t12;
    int t13;
    int t14;
    int t15;
    char *t16;

LAB0:    t1 = (t0 + 2912U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(85, ng0);
    t2 = (t0 + 3248);
    *((int *)t2) = 1;
    t3 = (t0 + 2944);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(86, ng0);
    t4 = (t0 + 1584);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);

LAB5:    t7 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 8, t7, 32);
    if (t8 == 1)
        goto LAB6;

LAB7:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 8, t2, 32);
    if (t8 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng18)));
    t11 = xsi_vlog_unsigned_case_compare(t6, 8, t3, 32);
    if (t11 == 1)
        goto LAB10;

LAB11:    t4 = ((char*)((ng12)));
    t12 = xsi_vlog_unsigned_case_compare(t6, 8, t4, 32);
    if (t12 == 1)
        goto LAB12;

LAB13:    t5 = ((char*)((ng16)));
    t13 = xsi_vlog_unsigned_case_compare(t6, 8, t5, 32);
    if (t13 == 1)
        goto LAB14;

LAB15:    t7 = ((char*)((ng14)));
    t14 = xsi_vlog_unsigned_case_compare(t6, 8, t7, 32);
    if (t14 == 1)
        goto LAB16;

LAB17:    t9 = ((char*)((ng10)));
    t15 = xsi_vlog_unsigned_case_compare(t6, 8, t9, 32);
    if (t15 == 1)
        goto LAB18;

LAB19:    t2 = ((char*)((ng22)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 8, t2, 32);
    if (t8 == 1)
        goto LAB20;

LAB21:    t3 = ((char*)((ng24)));
    t11 = xsi_vlog_unsigned_case_compare(t6, 8, t3, 32);
    if (t11 == 1)
        goto LAB22;

LAB23:    t4 = ((char*)((ng20)));
    t12 = xsi_vlog_unsigned_case_compare(t6, 8, t4, 32);
    if (t12 == 1)
        goto LAB24;

LAB25:    t2 = ((char*)((ng26)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 8, t2, 32);
    if (t8 == 1)
        goto LAB26;

LAB27:
LAB29:
LAB28:    xsi_set_current_line(94, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 1744);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);

LAB30:    goto LAB2;

LAB6:    xsi_set_current_line(88, ng0);
    t9 = ((char*)((ng2)));
    t10 = (t0 + 1744);
    xsi_vlogvar_assign_value(t10, t9, 0, 0, 8);
    goto LAB30;

LAB8:    goto LAB6;

LAB10:    goto LAB6;

LAB12:    goto LAB6;

LAB14:    goto LAB6;

LAB16:    goto LAB6;

LAB18:    xsi_set_current_line(90, ng0);
    t10 = ((char*)((ng6)));
    t16 = (t0 + 1744);
    xsi_vlogvar_assign_value(t16, t10, 0, 0, 8);
    goto LAB30;

LAB20:    goto LAB18;

LAB22:    goto LAB18;

LAB24:    xsi_set_current_line(92, ng0);
    t5 = ((char*)((ng4)));
    t7 = (t0 + 1744);
    xsi_vlogvar_assign_value(t7, t5, 0, 0, 8);
    goto LAB30;

LAB26:    goto LAB24;

}


extern void work_m_00000000000296787360_0266380040_init()
{
	static char *pe[] = {(void *)Always_10_0,(void *)Always_85_1};
	xsi_register_didat("work_m_00000000000296787360_0266380040", "isim/cpu_test_isim_beh.exe.sim/work/m_00000000000296787360_0266380040.didat");
	xsi_register_executes(pe);
}
