// duzhu.c ��֩��

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("��֩��", ({ "du zhu" }) );
	set_weight(40);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ�����а߰ߵ��ĵĻ�֩�룬�����о綾��\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 40,
		"maximum": 20,
	]));

	set("combat_exp", 100);

	setup();
}
