// jinwugong.c �����

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("�����", ({ "jin wu gong" }) );
	set_weight(100);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ��Ӳӵ���򼣬����Ư����\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 55,
		"maximum": 40,
	]));

	set("combat_exp", 100);

	setup();
}
