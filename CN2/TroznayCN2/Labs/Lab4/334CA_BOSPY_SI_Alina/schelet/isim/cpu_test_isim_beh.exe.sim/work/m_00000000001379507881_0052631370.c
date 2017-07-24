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
static const char *ng0 = "C:/Users/student/Desktop/334CA_BOSPY_SI_Alina/schelet/alu.v";
static int ng1[] = {0, 0};
static const char *ng2 = "Executing ADD operation! Operands are: RR - %2d, RD - %2d";
static const char *ng3 = "ADD operation completed with result: %2d";
static int ng4[] = {1, 0};
static const char *ng5 = "Executing SUB operation! Operands are: RR - %2d, RD - %2d";
static const char *ng6 = "SUB operation completed with result: %2d";
static int ng7[] = {2, 0};
static const char *ng8 = "Executing AND operation! Operands are: RR - %2d, RD - %2d";
static const char *ng9 = "AND operation completed with result: %2d";
static int ng10[] = {3, 0};
static const char *ng11 = "Executing XOR operation! Operands are: RR - %2d, RD - %2d";
static const char *ng12 = "XOR operation completed with result: %2d";
static int ng13[] = {4, 0};
static const char *ng14 = "Executing OR operation! Operands are: RR - %2d, RD - %2d";
static const char *ng15 = "OR operation completed with result: %2d";
static int ng16[] = {5, 0};
static const char *ng17 = "Executing NEG operation! Operands are: RR - %2d, RD - %2d";
static const char *ng18 = "NEG operation completed with result: %2d";
static int ng19[] = {6, 0};
static const char *ng20 = "Executing NONE operation! Operands are: RR - %2d, RD - %2d";
static const char *ng21 = "NONE operation completed with result: %2d";
static unsigned int ng22[] = {255U, 255U};
static unsigned int ng23[] = {0U, 255U};



static void Always_14_0(char *t0)
{
    char t17[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    int t13;
    char *t14;
    char *t15;
    char *t16;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;

LAB0:    t1 = (t0 + 3304U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(14, ng0);
    t2 = (t0 + 3624);
    *((int *)t2) = 1;
    t3 = (t0 + 3336);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(14, ng0);

LAB5:    xsi_set_current_line(15, ng0);
    t4 = (t0 + 1344U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(67, ng0);

LAB46:    xsi_set_current_line(68, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 2224);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(69, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 2384);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(16, ng0);
    t11 = (t0 + 1184U);
    t12 = *((char **)t11);

LAB9:    t11 = ((char*)((ng1)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t11, 32);
    if (t13 == 1)
        goto LAB10;

LAB11:    t2 = ((char*)((ng4)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB12;

LAB13:    t2 = ((char*)((ng7)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB14;

LAB15:    t2 = ((char*)((ng10)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB16;

LAB17:    t2 = ((char*)((ng13)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB18;

LAB19:    t2 = ((char*)((ng16)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB20;

LAB21:    t2 = ((char*)((ng19)));
    t13 = xsi_vlog_unsigned_case_compare(t12, 8, t2, 32);
    if (t13 == 1)
        goto LAB22;

LAB23:
LAB25:
LAB24:    xsi_set_current_line(62, ng0);

LAB45:    xsi_set_current_line(63, ng0);
    t2 = ((char*)((ng22)));
    t3 = (t0 + 2224);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(64, ng0);
    t2 = ((char*)((ng22)));
    t3 = (t0 + 2384);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);

LAB26:    goto LAB8;

LAB10:    xsi_set_current_line(18, ng0);

LAB27:    xsi_set_current_line(19, ng0);
    t14 = (t0 + 1664U);
    t15 = *((char **)t14);
    t14 = (t0 + 1504U);
    t16 = *((char **)t14);
    xsi_vlogfile_write(1, 0, 0, ng2, 3, t0, (char)118, t15, 8, (char)118, t16, 8);
    xsi_set_current_line(20, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    memset(t17, 0, 8);
    xsi_vlog_unsigned_add(t17, 8, t3, 8, t4, 8);
    t2 = (t0 + 2224);
    xsi_vlogvar_assign_value(t2, t17, 0, 0, 8);
    xsi_set_current_line(21, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng3, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB12:    xsi_set_current_line(24, ng0);

LAB28:    xsi_set_current_line(25, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(26, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    memset(t17, 0, 8);
    xsi_vlog_unsigned_minus(t17, 8, t3, 8, t4, 8);
    t2 = (t0 + 2224);
    xsi_vlogvar_assign_value(t2, t17, 0, 0, 8);
    xsi_set_current_line(27, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB14:    xsi_set_current_line(30, ng0);

LAB29:    xsi_set_current_line(31, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng8, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(32, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t4);
    t8 = (t6 & t7);
    *((unsigned int *)t17) = t8;
    t2 = (t3 + 4);
    t5 = (t4 + 4);
    t11 = (t17 + 4);
    t9 = *((unsigned int *)t2);
    t10 = *((unsigned int *)t5);
    t18 = (t9 | t10);
    *((unsigned int *)t11) = t18;
    t19 = *((unsigned int *)t11);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB30;

LAB31:
LAB32:    t16 = (t0 + 2224);
    xsi_vlogvar_assign_value(t16, t17, 0, 0, 8);
    xsi_set_current_line(33, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng9, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB16:    xsi_set_current_line(36, ng0);

LAB33:    xsi_set_current_line(37, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng11, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t4);
    t8 = (t6 ^ t7);
    *((unsigned int *)t17) = t8;
    t2 = (t3 + 4);
    t5 = (t4 + 4);
    t11 = (t17 + 4);
    t9 = *((unsigned int *)t2);
    t10 = *((unsigned int *)t5);
    t18 = (t9 | t10);
    *((unsigned int *)t11) = t18;
    t19 = *((unsigned int *)t11);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB34;

LAB35:
LAB36:    t14 = (t0 + 2224);
    xsi_vlogvar_assign_value(t14, t17, 0, 0, 8);
    xsi_set_current_line(39, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng12, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB18:    xsi_set_current_line(42, ng0);

LAB37:    xsi_set_current_line(43, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng14, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t4);
    t8 = (t6 | t7);
    *((unsigned int *)t17) = t8;
    t2 = (t3 + 4);
    t5 = (t4 + 4);
    t11 = (t17 + 4);
    t9 = *((unsigned int *)t2);
    t10 = *((unsigned int *)t5);
    t18 = (t9 | t10);
    *((unsigned int *)t11) = t18;
    t19 = *((unsigned int *)t11);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB38;

LAB39:
LAB40:    t16 = (t0 + 2224);
    xsi_vlogvar_assign_value(t16, t17, 0, 0, 8);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng15, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB20:    xsi_set_current_line(48, ng0);

LAB41:    xsi_set_current_line(49, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng17, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(50, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t17, 0, 8);
    t2 = (t17 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (~(t6));
    *((unsigned int *)t17) = t7;
    *((unsigned int *)t2) = 0;
    if (*((unsigned int *)t4) != 0)
        goto LAB43;

LAB42:    t19 = *((unsigned int *)t17);
    *((unsigned int *)t17) = (t19 & 255U);
    t20 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t20 & 255U);
    t5 = (t0 + 2224);
    xsi_vlogvar_assign_value(t5, t17, 0, 0, 8);
    xsi_set_current_line(51, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng18, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB22:    xsi_set_current_line(54, ng0);

LAB44:    xsi_set_current_line(55, ng0);
    t3 = (t0 + 1664U);
    t4 = *((char **)t3);
    t3 = (t0 + 1504U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng20, 3, t0, (char)118, t4, 8, (char)118, t5, 8);
    xsi_set_current_line(56, ng0);
    t2 = (t0 + 1664U);
    t3 = *((char **)t2);
    t2 = (t0 + 2224);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 8);
    xsi_set_current_line(57, ng0);
    t2 = (t0 + 2224);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng21, 2, t0, (char)118, t4, 8);
    goto LAB26;

LAB30:    t21 = *((unsigned int *)t17);
    t22 = *((unsigned int *)t11);
    *((unsigned int *)t17) = (t21 | t22);
    t14 = (t3 + 4);
    t15 = (t4 + 4);
    t23 = *((unsigned int *)t3);
    t24 = (~(t23));
    t25 = *((unsigned int *)t14);
    t26 = (~(t25));
    t27 = *((unsigned int *)t4);
    t28 = (~(t27));
    t29 = *((unsigned int *)t15);
    t30 = (~(t29));
    t13 = (t24 & t26);
    t31 = (t28 & t30);
    t32 = (~(t13));
    t33 = (~(t31));
    t34 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t34 & t32);
    t35 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t35 & t33);
    t36 = *((unsigned int *)t17);
    *((unsigned int *)t17) = (t36 & t32);
    t37 = *((unsigned int *)t17);
    *((unsigned int *)t17) = (t37 & t33);
    goto LAB32;

LAB34:    t21 = *((unsigned int *)t17);
    t22 = *((unsigned int *)t11);
    *((unsigned int *)t17) = (t21 | t22);
    goto LAB36;

LAB38:    t21 = *((unsigned int *)t17);
    t22 = *((unsigned int *)t11);
    *((unsigned int *)t17) = (t21 | t22);
    t14 = (t3 + 4);
    t15 = (t4 + 4);
    t23 = *((unsigned int *)t14);
    t24 = (~(t23));
    t25 = *((unsigned int *)t3);
    t13 = (t25 & t24);
    t26 = *((unsigned int *)t15);
    t27 = (~(t26));
    t28 = *((unsigned int *)t4);
    t31 = (t28 & t27);
    t29 = (~(t13));
    t30 = (~(t31));
    t32 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t32 & t29);
    t33 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t33 & t30);
    goto LAB40;

LAB43:    t8 = *((unsigned int *)t17);
    t9 = *((unsigned int *)t4);
    *((unsigned int *)t17) = (t8 | t9);
    t10 = *((unsigned int *)t2);
    t18 = *((unsigned int *)t4);
    *((unsigned int *)t2) = (t10 | t18);
    goto LAB42;

}


extern void work_m_00000000001379507881_0052631370_init()
{
	static char *pe[] = {(void *)Always_14_0};
	xsi_register_didat("work_m_00000000001379507881_0052631370", "isim/cpu_test_isim_beh.exe.sim/work/m_00000000001379507881_0052631370.didat");
	xsi_register_executes(pe);
}
