// zhizhu.c ֩��

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("֩��", ({ "zhi zhu" }) );
	set_weight(30);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ�������֩�롣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 10,
		"maximum": 10,
	]));

	set("combat_exp", 100);

	setup();
}
