// wucaizhu.c �����

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name(HIR "��" HIG "��" HIW "��", ({ "wucai zhu" }) );
	set_weight(90);
	set("race", "Ұ��");
	set("age", 5);
	set("long", "һֻ�޴�ģ�������ɫ�Ĵ�֩�롣\n");
	set("attitude", "peaceful");
	set("str", 18);
	set("con", 25);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 90,
		"maximum": 45,
	]));

	set("combat_exp", 7000);

	setup();
}
