// xiezi.c Ы��

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("Ы��", ({ "xie zi" }) );
	set_weight(180);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ������צ��Ы�ӡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 30,
		"maximum": 25,
	]));

	set("combat_exp", 100);

	setup();
}
