// xuexue.c ѩЫ��

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name(WHT "ѩЫ��" NOR, ({ "xue xie" }) );
	set_weight(180);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ��Ө��͸��Ы�ӡ�\n");
	set("attitude", "peaceful");
	set("str", 25);
	set("con", 22);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 80,
		"maximum": 45,
	]));

	set("combat_exp", 10000);

	setup();
}
